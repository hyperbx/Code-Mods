CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmUpdate, 0x140802DF0, "\x40\x53\x55\x48\x83\xEC\x28\x49", "xxxxxxxx");

struct TimeAttackData
{
	uint8_t Version = 1;

	csl::math::Vector3 StartPosition;
	csl::math::Vector3 EndPosition;

	float Time;
};

TimeAttackData m_CurrentData;

std::filesystem::path m_WorkingDirectory;

bool m_IsTimerStarted = false;

static app::player::Sonic* GetSonic()
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return nullptr;

	return pGameDocument->GetGameObject<app::player::Sonic>();
}

static app::player::GOCPlayerKinematicParams* GetKinematics()
{
	auto* pSonic = GetSonic();

	if (!pSonic)
		return nullptr;

	return pSonic->GetComponent<app::player::GOCPlayerKinematicParams>();
}

static bool IsGrounded()
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return false;

	auto* pLevelInfo = pGameDocument->GetService<app::level::LevelInfo>();

	if (!pLevelInfo)
		return false;

	return pLevelInfo->playerInfos[0]->IsGrounded;
}

static bool IsGroundedSpecial()
{
	return IsGrounded() ||
		BlackboardHelper::IsGrinding() ||
		BlackboardHelper::IsSpringJump() ||
		BlackboardHelper::IsWallClimbing();
}

static void LoadTimeAttackData()
{
	// TODO: unhardcode this.
	std::ifstream in(m_WorkingDirectory / "data.bin", std::ios::binary);

	if (!in)
	{
		printf("[Time Attack] Failed to load time attack data...\n");
		return;
	}

	in.read(reinterpret_cast<char*>(&m_CurrentData), sizeof(TimeAttackData));
	in.close();
}

static void SaveTimeAttackData()
{
	// TODO: unhardcode this.
	std::ofstream out(m_WorkingDirectory / "data.bin", std::ios::binary);

	if (!out)
	{
		printf("[Time Attack] Failed to save time attack data...\n");
		return;
	}

	out.write(reinterpret_cast<const char*>(&m_CurrentData), sizeof(TimeAttackData));
	out.close();
}

struct GOCEventTimerData
{
	INSERT_PADDING(0x04);
	float Duration = -1.0f;
	INSERT_PADDING(0x08);
	float TimeYellow{};
	float TimeRed{};
	INSERT_PADDING(0x08);
};

GOCEventTimerData m_TimerData;

HOOK(int64_t, __fastcall, SonicAddCallback, 0x1407D9120, hh::game::GameObject* in_pThis, int64_t in_pSonicContext)
{
	FUNCTION_PTR(hh::game::GOComponent*, __fastcall, fpAddComponent, 0x1502647B0, hh::game::GameObject* in_pThis, int64_t in_pComponentClass);
	FUNCTION_PTR(int64_t, __fastcall, fpInitComponent, 0x14FF22270, hh::game::GameObject* in_pThis, hh::game::GOComponent* in_pGOComponent);
	FUNCTION_PTR(char, __fastcall, fpGOCEventTimerCtor, 0x146E064E0, hh::game::GOComponent* in_pGOComponent, GOCEventTimerData* in_pGOCEventTimerData);

	auto pGOCEventTimer = fpAddComponent(in_pThis, 0x143B6E7C0);
	
	if (pGOCEventTimer)
	{
		fpGOCEventTimerCtor(pGOCEventTimer, &m_TimerData);
		fpInitComponent(in_pThis, pGOCEventTimer);
	}

	return originalSonicAddCallback(in_pThis, in_pSonicContext);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	auto pKinematics = GetKinematics();

	if (!pKinematics)
		return originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);

	auto pSonic = GetSonic();

	if (!pSonic)
		return originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);

	if (IsGroundedSpecial())
	{
		if (GetAsyncKeyState(VK_F1))
		{
			m_CurrentData.StartPosition = pKinematics->Position;
			m_IsTimerStarted = true;
		}

		if (GetAsyncKeyState(VK_F2))
		{
			m_CurrentData.EndPosition = pKinematics->Position;
			m_IsTimerStarted = false;

			SaveTimeAttackData();
		}

		if (GetAsyncKeyState(VK_F3))
		{
			LoadTimeAttackData();

			m_TimerData.Duration = m_CurrentData.Time;
			m_TimerData.TimeYellow = m_CurrentData.Time / 2.0f;
			m_TimerData.TimeRed = m_CurrentData.Time - (m_CurrentData.Time - 5.0f);

			auto pGOCEventTimer = pSonic->GetComponent("GOCEventTimer");

			FUNCTION_PTR(int64_t, __fastcall, fpStartEventTimer, 0x146DECC10, hh::game::GOComponent* in_pGOCEventTimer);

			if (pGOCEventTimer)
				fpStartEventTimer(pGOCEventTimer);
		}
	}
	else
	{
		printf("[Time Attack] Player must be grounded in order to save!\n");
	}

	if (m_IsTimerStarted)
	{
		m_CurrentData.Time += *in_pDeltaTime;

		PRINT_FLOAT(m_CurrentData.Time);
	}

	return originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

EXPORT void Init(ModInfo* in_modInfo)
{
	m_WorkingDirectory = StringHelper::GetSubstringBeforeLastChar(std::string(in_modInfo->CurrentMod->Path), '\\');

	INSTALL_HOOK(SonicAddCallback);
	INSTALL_HOOK(GOCPlayerHsmUpdate);
}