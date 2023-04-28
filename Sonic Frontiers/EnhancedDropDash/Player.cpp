bool m_IsDropDash              = false;
bool m_IsDropDashFromSlide     = false;
bool m_IsDropDashFromStomp     = false;
bool m_IsJumpInputBuffered     = false;
bool m_IsUncurlInputBuffered   = false;
bool m_IsUncurlTriggerBuffered = false;

float m_DeltaTime         = 0.0f;
float m_DropDashDelayTime = 0.0f;
float m_Velocity		  = 0.0f;

uint64_t m_PlayerSpeedUpdateAddr = READ_CALL(m_SigPlayerSpeedUpdateCaller());

FUNCTION_PTR(bool, __fastcall, fpSetStateFlags, m_SigSetStateFlags(), int64_t a1, int a2, int a3);
FUNCTION_PTR(bool, __fastcall, fpExitStateWithTricks, m_SigExitStateWithTricks(), int64_t a1, char a2);

HOOK(int64_t, __fastcall, DropDashStart, m_SigDropDashStart(), int64_t a1, int64_t a2)
{
	m_IsDropDash              = true;
	m_IsJumpInputBuffered     = InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A);
	m_IsUncurlInputBuffered   = InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B);
	m_IsUncurlTriggerBuffered = InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD;

	if (Configuration::IsNoCameraDelay && !m_IsDropDashFromSlide ||
		Configuration::IsNoSlideCameraDelay && m_IsDropDashFromSlide ||
		Configuration::IsNoStompCameraDelay && m_IsDropDashFromStomp)
	{
		if (m_SigDropDashCameraDelay() != nullptr)
			WRITE_MEMORY(m_SigDropDashCameraDelay(), uint8_t, 0xEB);
	}

	// I love switches
	if (Configuration::IsUncurlWhenUngrounded && !m_IsDropDashFromStomp ||
		Configuration::IsStompDashUncurlImmediate && m_IsDropDashFromStomp)
	{
		if (m_SigDropDashUngroundedExitFunc() != nullptr && m_SigExitStateWithTricks() != nullptr)
			WRITE_CALL((uint64_t)m_SigDropDashUngroundedExitFunc(), (uint64_t)m_SigExitStateWithTricks());
	}

	return originalDropDashStart(a1, a2);
}

HOOK(bool, __fastcall, DropDashUpdate, m_SigDropDashUpdate(), int64_t a1, int64_t a2)
{
	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
		m_IsJumpInputBuffered = false;

	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
		m_IsUncurlInputBuffered = false;

	if (InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) < TRIGGER_THRESHOLD)
		m_IsUncurlTriggerBuffered = false;

	if (!m_IsUncurlTriggerBuffered && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		BlackboardHelper::GetStatus()->StateParameter |= STATUS_PARAM_BOOST;

		goto Uncurl;
	}

	if (!m_IsUncurlInputBuffered && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B) ||
		!m_IsJumpInputBuffered && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
	{
	Uncurl:
		bool isGrounded = *(bool*)((*(int64_t*)(a2 + 72) + 400) + 53) & 2;

		fpSetStateFlags(*(int64_t*)(a2 + 56), isGrounded ? 4 : 14, 0);

		return true;
	}

	return originalDropDashUpdate(a1, a2);
}

HOOK(int64_t, __fastcall, DropDashEnd, m_SigDropDashEnd(), int64_t a1, int64_t a2)
{
	m_IsDropDash          = false;
	m_IsDropDashFromSlide = false;
	m_IsDropDashFromStomp = false;

	if (m_SigDropDashCameraDelay() != nullptr)
		RESTORE_MEMORY((uint64_t)m_SigDropDashCameraDelay());

	if (m_SigDropDashUngroundedExitFunc() != nullptr)
		RESTORE_MEMORY((uint64_t)m_SigDropDashUngroundedExitFunc());

	return originalDropDashEnd(a1, a2);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	Player::CreateInput();

	m_DeltaTime = *in_pDeltaTime;

	if (!m_IsDropDash)
		m_DropDashDelayTime += m_DeltaTime;

	originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

HOOK(char, __fastcall, GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, int in_stateIndex)
{
#if _DEBUG
	printf("[EnhancedDropDash::GOCPlayerHsmGroundStateUpdate] in_stateIndex: %d\n", in_stateIndex);
#endif

	switch (in_stateIndex)
	{
		// StateGrindDoubleJump
		case 46:
		{
			if (Configuration::IsGrindDoubleJumpFix)
			{
				if (m_SigForceGrindJumpPosture() != nullptr)
					WRITE_NOP(m_SigForceGrindJumpPosture(), 2);

				// Swap to StateDoubleJump.
				in_stateIndex = 9;
			}

			break;
		}

		// StateStomping
		case 52:
		{
			if (Configuration::IsDropDashOnStomp && m_Velocity >= Configuration::StompVelocityThreshold)
			{
				m_IsDropDashFromStomp = true;

				// Swap to StateDropDash.
				in_stateIndex = 110;
			}

			break;
		}

		// StateSliding
		case 57:
		{
			if (Configuration::IsDropDashOnSlide)
			{
				if (m_DropDashDelayTime < 0.1f)
					return 0;

				m_DropDashDelayTime = 0.0f;
				m_IsDropDashFromSlide = true;

				// Swap to StateDropDash.
				in_stateIndex = 110;
			}

			break;
		}

		default:
		{
			if (Configuration::IsGrindDoubleJumpFix)
			{
				if (m_SigForceGrindJumpPosture() != nullptr)
					RESTORE_MEMORY((uint64_t)m_SigForceGrindJumpPosture());
			}

			break;
		}
	}

	return originalGOCPlayerHsmGroundStateUpdate(in_pThis, in_stateIndex);
}

HOOK(int64_t, __fastcall, PlayerSpeedUpdate, m_PlayerSpeedUpdateAddr, int64_t a1, int64_t a2)
{
	m_Velocity = Vector3::Magnitude(*(Vector3*)(a2 + 208));

	return originalPlayerSpeedUpdate(a1, a2);
}

#if 0
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmAirStateUpdate, "\x41\x56\x48\x83\xEC\x30\x0F\xB6\x81\x1C", "xxxxxxxxxx");

HOOK(char, __fastcall, GOCPlayerHsmAirStateUpdate, m_SigGOCPlayerHsmAirStateUpdate(), int64_t* in_pThis, int in_stateIndex)
{
#if _DEBUG
	printf("[EnhancedDropDash::GOCPlayerHsmAirStateUpdate] in_stateIndex: %d\n", in_stateIndex);
#endif

	return originalGOCPlayerHsmAirStateUpdate(in_pThis, in_stateIndex);
}
#endif

void Player::Install()
{
	FrontiersInput::Install();

	if (m_SigDropDashCameraDelay() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigDropDashCameraDelay(), 1);

	if (m_SigDropDashUngroundedExitFunc() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigDropDashUngroundedExitFunc(), 5);

	if (m_SigForceGrindJumpPosture() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigForceGrindJumpPosture(), 2);

	INSTALL_HOOK(DropDashStart);
	INSTALL_HOOK(DropDashUpdate);
	INSTALL_HOOK(DropDashEnd);
	INSTALL_HOOK(GOCPlayerHsmUpdate);
	INSTALL_HOOK(GOCPlayerHsmGroundStateUpdate);

	if (Configuration::IsDropDashOnStomp && Configuration::StompVelocityThreshold > 0.0f)
	{
		INSTALL_HOOK(PlayerSpeedUpdate);
	}

	if (Configuration::IsDropDashOnSlide)
	{
		// Prevent squat to slide.
		if (m_SigSquatToSlideWorkaround() != nullptr)
			WRITE_MEMORY(m_SigSquatToSlideWorkaround(), uint8_t, 0xEB);
	}
}