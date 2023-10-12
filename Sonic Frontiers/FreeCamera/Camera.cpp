bool m_IsPhotoMode = false;
bool m_PhotoModeButtonInterrupt = false;

const char* m_pCurrentAnimation = "";

static std::unique_ptr<InputHelper> m_upInput;

Vector3* m_pCameraPosition;
Vector3* m_pPlayerPosition;

FUNCTION_PTR(void**, __fastcall, m_fpSendMsgPhotoMode, 0x1401CD150, app::game::PhotoModeService* in_pPhotoModeService, bool in_isDisabled);
FUNCTION_PTR(int64_t, __fastcall, m_fpSendMessageToGameDocumentAgain, 0x140BCB1B0, app::GameDocument* a1, hh::fnd::Message& a2);
FUNCTION_PTR(int64_t, __fastcall, m_fpSendMessageToGameDocument, 0x152E01DA0, app::GameDocument* a1, hh::fnd::Message& a2);
FUNCTION_PTR(int64_t, __fastcall, m_fpSendMessageToService, 0x1401375A0, hh::game::GameService* a1, app::GameDocument* a2, hh::fnd::Message& a3);

HOOK(int64_t, __fastcall, CreateServices, 0x1471DCC90, int64_t* in_this, hh::game::GameServiceClass** in_ppClasses)
{
	std::vector<hh::game::GameServiceClass*> classes;

	while (*in_ppClasses)
	{
		classes.push_back(*in_ppClasses);
		in_ppClasses++;
	}

	// v1.20: 0x143B790D0
	auto classPtr = (uint64_t)m_SigPhotoModeServiceClass() + (((*(uint32_t*)(((uint64_t)m_SigPhotoModeServiceClass() + 17) + 3)) + 7) + 17);

	// Always load PhotoModeService.
	classes.push_back((hh::game::GameServiceClass*)classPtr);
	classes.push_back(nullptr);

	return originalCreateServices(in_this, classes.data());
}

HOOK(void**, __fastcall, SendMsgPhotoMode, 0x1401CD150, app::game::PhotoModeService* in_pPhotoModeService, bool in_isDisabled)
{
	// This function uses an inverted if statement, so 0 is true and 1 is false.
	auto result = originalSendMsgPhotoMode(in_pPhotoModeService, !(m_IsPhotoMode = in_isDisabled));

	m_PhotoModeButtonInterrupt = true;

	FUNCTION_PTR(char, __fastcall, m_fpInvokePhotoMode, 0x1401CD230, app::game::PhotoModeService* in_pPhotoModeService, bool in_isEnabled);
	{
		m_fpInvokePhotoMode(in_pPhotoModeService, m_IsPhotoMode);
	}

	return result;
}

HOOK(void, __fastcall, CameraShakeUpdate, 0x1400B51C0, Quaternion* a1, float* a2, int64_t a3)
{
	if (m_IsPhotoMode)
		return;

	return originalCameraShakeUpdate(a1, a2, a3);
}

HOOK(int64_t, __fastcall, PhotoModeCameraUpdate, 0x1400A59C0, app::game::PhotoModeService* in_pPhotoModeService, float* in_deltaTime)
{
	m_pCameraPosition = (Vector3*)((int64_t)in_pPhotoModeService + 32);
	
	in_pPhotoModeService->StartPosition = *m_pCameraPosition;

	return originalPhotoModeCameraUpdate(in_pPhotoModeService, in_deltaTime);
}

HOOK(char, __fastcall, PlayerPositionUpdate, 0x1407BED60, int64_t a1, float in_deltaTime)
{
	m_pPlayerPosition = (Vector3*)(a1 + 128);

	return originalPlayerPositionUpdate(a1, in_deltaTime);
}

HOOK(int64_t, __fastcall, ChangeAnimation, 0x1407C9280, int64_t a1, const char* in_pAnimationName, char a3)
{
	m_pCurrentAnimation = in_pAnimationName;

	return originalChangeAnimation(a1, in_pAnimationName, a3);
}

void TeleportCameraToPlayer()
{
	if (m_pCameraPosition && m_pPlayerPosition)
		*m_pCameraPosition = *m_pPlayerPosition;
}

void TeleportPlayerToCamera()
{
	if (m_pPlayerPosition && m_pCameraPosition)
		*m_pPlayerPosition = *m_pCameraPosition;
}

void Camera::UpdateImGui()
{
	if (!m_IsPhotoMode)
		return;

	ImGui::Begin("Properties", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (m_pCameraPosition && m_pPlayerPosition)
		{
			ImGui::Text("Camera Position: %f, %f, %f", m_pCameraPosition->X, m_pCameraPosition->Y, m_pCameraPosition->Z);
			ImGui::Text("Player Position: %f, %f, %f", m_pPlayerPosition->X, m_pPlayerPosition->Y, m_pPlayerPosition->Z);
			ImGui::NewLine();

			if (ImGui::Button("Teleport camera to player"))
				TeleportCameraToPlayer();

			if (ImGui::Button("Teleport player to camera"))
				TeleportPlayerToCamera();

			ImGui::NewLine();
			ImGui::Text("Press Back to teleport player to camera");
		}

		if (m_pCurrentAnimation)
		{
			ImGui::NewLine();
			ImGui::Text("Current Animation: %s", m_pCurrentAnimation);
		}

		ImGui::NewLine();
		if (ImGui::Checkbox("Automatically unhook mouse cursor", &Configuration::IsAutomaticMouseUnhook))
		{
			Configuration::Save();
		}

		ImGui::NewLine();
		ImGui::Text("Press Tab to unhook mouse cursor");

		ImGui::NewLine();
		ImGui::Text("Press Escape to hide");
	}
	ImGui::End();
}

void SendMsgPlayAnimation(const char* in_pAnimationName, float in_duration)
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return;

	auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

	if (!pSonic)
		return;

	app::player::MsgPlayAnimation msgPlayAnimation{ in_pAnimationName, in_duration };
	{
		pSonic->SendMessageImmToPlayer(pGameDocument, 0, msgPlayAnimation);
	}
}

void Camera::Update()
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return;

	if ((m_upInput->GetInputDown(XINPUT_GAMEPAD_LEFT_THUMB) && m_upInput->GetInputDown(XINPUT_GAMEPAD_RIGHT_THUMB)) || GetAsyncKeyState(VK_F1) & 1)
	{
		auto* pPhotoModeService = pGameDocument->GetService<app::game::PhotoModeService>();

		if (!pPhotoModeService)
			return;

		if (!m_PhotoModeButtonInterrupt)
			m_fpSendMsgPhotoMode(pPhotoModeService, !m_IsPhotoMode);
	}
	else
	{
		m_PhotoModeButtonInterrupt = false;
	}

	if (m_IsPhotoMode)
	{
		if (m_upInput->GetInputDown(XINPUT_GAMEPAD_BACK) || GetAsyncKeyState(VK_BACK) & 1)
		{
			TeleportPlayerToCamera();
		}

#if _DEBUG
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			SendMsgPlayAnimation("ev_idle02_end", 0.0f);
		}
#endif
	}
	else
	{
		DearImGuiContext::IsMouseCursorVisible = false;
	}
}

void Camera::Install()
{
	m_upInput.reset(new InputHelper());

	INSTALL_HOOK(CreateServices);
	INSTALL_HOOK(SendMsgPhotoMode);
	INSTALL_HOOK(CameraShakeUpdate);
	INSTALL_HOOK(PhotoModeCameraUpdate);
	INSTALL_HOOK(PlayerPositionUpdate);
	INSTALL_HOOK(ChangeAnimation);
}