bool m_isSupremeBeast = false;
bool m_isCommittedLazyUpdate = false;

float m_glitchTimer = 0.0f;
float m_glitchTimerThreshold = 10.0f;

int m_glitchPhase = 0;

HOOK(void*, __fastcall, StatePluginBossBattleCtor, m_SigStatePluginBossBattleCtor(), void* a1, int64_t a2)
{
	BossListener::IsBoss = true;

	if (BattleRushListener::IsBattleRush || MasterTrialListener::IsBossRush)
		return originalStatePluginBossBattleCtor(a1, a2);

	auto stage = StageHelper::GetCurrentStageID();

	std::string name;
	std::string key;

	m_isSupremeBeast = false;

	if (stage == "w1r03")
	{
		name = LanguageHelper::Localise("StateBossGiganto");
		key  = "giganto";
	}
	else if (stage == "w2r01")
	{
		name = LanguageHelper::Localise("StateBossWyvern");
		key  = "wyvern";
	}
	else if (stage == "w3r01")
	{
		name = LanguageHelper::Localise("StateBossKnight");
		key  = "knight";
	}
	else if (stage == "w1r04")
	{
		name = LanguageHelper::Localise("StateBossSupreme");
		key  = "supreme";
	}
	else if (stage == "w1r06")
	{
		auto pGameManager = hh::game::GameManager::GetSingleton();

		if (pGameManager)
		{
			auto pBossRifleBeast = pGameManager->GetGameObject("TheEndBeast");

			if (pBossRifleBeast)
			{
				Discord::CommitState(LanguageHelper::Localise("StateBossSupremeBeast"));
				Discord::CommitLargeImage("supreme2");

				m_isSupremeBeast = true;

				return originalStatePluginBossBattleCtor(a1, a2);
			}
			else
			{
				name = LanguageHelper::Localise("StateBossSupreme");
				key  = "supreme";
			}
		}
	}

#if _DEBUG
	printf("[Discord Frontiers] Boss: %s\n", name.c_str());
#endif

	Discord::Commit(name, Discord::Details, key, Discord::SmallImageKey, TimeHelper::GetSystemEpoch());

	return originalStatePluginBossBattleCtor(a1, a2);
}

HOOK(void, __fastcall, BossListener_GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), hh::game::GOComponent* in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	originalBossListener_GOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);

	BossListener::Glitch(*in_pDeltaTime);

	auto pGOCPlayerBlackboard = in_pThis->pOwner->GetGOC<app::player::GOCPlayerBlackboard>();

	if (!pGOCPlayerBlackboard)
		return;

	auto pBlackboard = pGOCPlayerBlackboard->pBlackboard;

	if (!pBlackboard)
		return;

	auto pBlackboardItem = pBlackboard->GetBlackboardContent<app::player::BlackboardItem>();

	if (!pBlackboardItem)
		return;

	if (pBlackboardItem->RingCount <= 0)
	{
		if (m_isCommittedLazyUpdate)
			return;

		if (BattleRushListener::IsBattleRush)
			return;

		Discord::CommitState(LanguageHelper::Localise("StateExploring"));

		BossListener::IsBoss = false;
		StageListener::IsLazyUpdate = true;

		m_isSupremeBeast = false;
		m_isCommittedLazyUpdate = true;
	}
	else
	{
		m_isCommittedLazyUpdate = false;
	}
}

void BossListener::Glitch(float in_deltaTime)
{
	if (!BossListener::IsBoss)
		return;

	if (!m_isSupremeBeast)
		return;

	if (m_glitchTimer >= m_glitchTimerThreshold)
	{
		switch (m_glitchPhase)
		{
			case 0:
				Discord::CommitState(LanguageHelper::Localise("StateBossSupremeBeast"));
				m_glitchPhase = 1;
				break;

			case 1:
				Discord::CommitState(LanguageHelper::Localise("StateBossTheEnd"));
				m_glitchPhase = 0;
				break;
		}

		m_glitchTimer = 0.0f;
	}

	m_glitchTimer += in_deltaTime;
}

void BossListener::Init()
{
	INSTALL_HOOK(StatePluginBossBattleCtor);
	INSTALL_HOOK(BossListener_GOCPlayerHsmUpdate);
}