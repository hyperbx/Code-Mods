std::bitset<8> m_StateFlags;
std::bitset<3> m_InputFlags;

enum EStateFlags
{
	EStateFlags_IsDropDash,
	EStateFlags_IsDropDashCharge,
	EStateFlags_IsAirDashRelease,
	EStateFlags_IsAirDash,
	EStateFlags_IsSlideDash,
	EStateFlags_IsStompDashRelease,
	EStateFlags_IsStompDash,
	EStateFlags_IsQuickStompDash
};

enum EStateID
{
	EStateID_StateRun = 4,
	EStateID_StateDoubleJump = 9,
	EStateID_StateStompingBounce = 10,
	EStateID_StateFall = 14,
	EStateID_StateAirBoost = 22,
	EStateID_StateGrindDoubleJump = 46,
	EStateID_StateStomping = 52,
	EStateID_StateStompingLand = 55,
	EStateID_StateSliding = 57,
	EStateID_StateDropDash = 110
};

enum EInputFlags
{
	EInputFlags_IsJumpInputBuffered,
	EInputFlags_IsUncurlInputBuffered,
	EInputFlags_IsUncurlTriggerBuffered
};

bool m_IsAirDashJumpOut = false;

float m_DeltaTime = 0.0f;
float m_DropDashDelayTime = 0.0f;
float m_StompDashPressDelayTime = 0.0f;
float m_HorizontalVelocity = 0.0f;

FUNCTION_PTR(bool, __fastcall, fpSetCurrentState, m_SigSetCurrentState(), int64_t a1, int a2, int a3);

bool IsNormalDropDash()
{
	return m_StateFlags.test(EStateFlags_IsDropDash) &&
		!m_StateFlags.test(EStateFlags_IsAirDash) &&
		!m_StateFlags.test(EStateFlags_IsSlideDash) &&
		!m_StateFlags.test(EStateFlags_IsStompDash) &&
		!m_StateFlags.test(EStateFlags_IsQuickStompDash);
}

bool IsGroundDropDash()
{
	return m_StateFlags.test(EStateFlags_IsDropDash) &&
		!m_StateFlags.test(EStateFlags_IsAirDash) &&
		!m_StateFlags.test(EStateFlags_IsQuickStompDash);
}

bool IsNoCameraDelay()
{
	return Configuration::IsNoCameraDelay && IsNormalDropDash() ||
		Configuration::IsNoAirDashCameraDelay && m_StateFlags.test(EStateFlags_IsAirDash) ||
		Configuration::IsNoSlideDashCameraDelay && m_StateFlags.test(EStateFlags_IsSlideDash) ||
		Configuration::IsNoStompDashCameraDelay && m_StateFlags.test(EStateFlags_IsStompDash) ||
		Configuration::IsNoQuickStompDashCameraDelay && m_StateFlags.test(EStateFlags_IsQuickStompDash);
}

bool IsMoveAvailable(Configuration::EWorldType in_worldType)
{
	return (BlackboardHelper::IsCyberSpace()
		? (in_worldType == Configuration::EWorldType_Both || in_worldType == Configuration::EWorldType_CyberOnly)
		: (in_worldType == Configuration::EWorldType_Both || in_worldType == Configuration::EWorldType_IslandOnly));
}

bool IsCyberSpaceOrSideView()
{
	return BlackboardHelper::IsCyberSpace() || BlackboardHelper::IsSideView();
}

bool IsImmediateExit()
{
	if (IsCyberSpaceOrSideView())
		return false;

	return (Configuration::AirDashUncurlType == Configuration::EUncurlType_Immediate && m_StateFlags.test(EStateFlags_IsAirDash)) ||
		(Configuration::QuickStompDashUncurlType == Configuration::EUncurlType_Immediate && m_StateFlags.test(EStateFlags_IsQuickStompDash));
}

bool IsUngroundedExit()
{
	if (IsCyberSpaceOrSideView())
		return false;

	return Configuration::IsUncurlWhenUngrounded;
}

bool IsGroundedExit(bool in_isGrounded)
{
	return in_isGrounded &&
		(Configuration::AirDashUncurlType == Configuration::EUncurlType_Grounded && m_StateFlags.test(EStateFlags_IsAirDash) ||
		Configuration::QuickStompDashUncurlType == Configuration::EUncurlType_Grounded && m_StateFlags.test(EStateFlags_IsQuickStompDash));
}

HOOK(int64_t, __fastcall, StateDropDashStart, m_SigStateDropDashStart(), int64_t a1, int64_t a2)
{
	m_StateFlags.set(EStateFlags_IsDropDash);
	m_InputFlags.set(EInputFlags_IsJumpInputBuffered, InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A));
	m_InputFlags.set(EInputFlags_IsUncurlInputBuffered, InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B));
	m_InputFlags.set(EInputFlags_IsUncurlTriggerBuffered, InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD);

	if (IsNoCameraDelay())
	{
		if (m_SigDropDashCameraDelay() != nullptr)
			WRITE_MEMORY(m_SigDropDashCameraDelay(), uint8_t, 0xEB);
	}

	if (IsImmediateExit())
	{
		if (m_SigDropDashUngroundedExitFunc() != nullptr && m_SigExitStateWithTricks() != nullptr)
			WRITE_CALL((uint64_t)m_SigDropDashUngroundedExitFunc(), (uint64_t)m_SigExitStateWithTricks());
	}

	return originalStateDropDashStart(a1, a2);
}

HOOK(bool, __fastcall, StateDropDashUpdate, m_SigStateDropDashUpdate(), int64_t a1, int64_t a2)
{
	bool isGrounded = *(bool*)((*(int64_t*)(a2 + 72) + 400) + 53) & 2;

	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
		m_InputFlags.reset(EInputFlags_IsJumpInputBuffered);

	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
		m_InputFlags.reset(EInputFlags_IsUncurlInputBuffered);

	if (InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) < TRIGGER_THRESHOLD)
		m_InputFlags.reset(EInputFlags_IsUncurlTriggerBuffered);

	if (IsUngroundedExit() && isGrounded)
	{
		if (m_SigDropDashUngroundedExitFunc() != nullptr && m_SigExitStateWithTricks() != nullptr)
			WRITE_CALL((uint64_t)m_SigDropDashUngroundedExitFunc(), (uint64_t)m_SigExitStateWithTricks());
	}

	if (IsGroundedExit(isGrounded) || !m_InputFlags.test(EInputFlags_IsUncurlTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		BlackboardHelper::GetStatus()->StateParameter |= STATUS_PARAM_BOOST;

		goto Uncurl;
	}

	if (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B) ||
		!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
	{
		if (m_StateFlags.test(EStateFlags_IsAirDash) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
			m_IsAirDashJumpOut = true;

	Uncurl:
		fpSetCurrentState(*(int64_t*)(a2 + 56), isGrounded ? EStateID_StateRun : EStateID_StateFall, 0);

		return true;
	}

	return originalStateDropDashUpdate(a1, a2);
}

HOOK(int64_t, __fastcall, StateDropDashEnd, m_SigStateDropDashEnd(), int64_t a1, int64_t a2)
{
	m_StateFlags.reset();

	if (m_SigDropDashCameraDelay() != nullptr)
		RESTORE_MEMORY((uint64_t)m_SigDropDashCameraDelay());

	if (m_SigDropDashUngroundedExitFunc() != nullptr)
		RESTORE_MEMORY((uint64_t)m_SigDropDashUngroundedExitFunc());

	return originalStateDropDashEnd(a1, a2);
}

HOOK(bool, __fastcall, PostureDropDashUpdate, m_SigPostureDropDashUpdate(), int64_t a1, double a2)
{
	if (m_SigFixDropDashSideView() != nullptr)
	{
		if (BlackboardHelper::IsSideView())
		{
			WRITE_MEMORY(m_SigFixDropDashSideView(), uint8_t, 0xEB);
		}
		else
		{
			RESTORE_MEMORY((uint64_t)m_SigFixDropDashSideView());
		}
	}

	return originalPostureDropDashUpdate(a1, a2);
}

HOOK(bool, __fastcall, StateDoubleJumpUpdate, m_SigStateDoubleJumpUpdate(), int64_t a1, int64_t in_pSonicContext, float in_deltaTime)
{
	m_StateFlags.set(EStateFlags_IsDropDashCharge, *(float*)(a1 + 180) > 0.0f);

	return originalStateDoubleJumpUpdate(a1, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateRecoveryJumpUpdate, m_SigStateRecoveryJumpUpdate(), int64_t a1, int64_t in_pSonicContext, float in_deltaTime)
{
	m_StateFlags.set(EStateFlags_IsDropDashCharge, *(bool*)(a1 + 196));

	// Always allow air boost exit.
	if (m_StateFlags.test(EStateFlags_IsDropDashCharge) &&
		InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		fpSetCurrentState(*(int64_t*)(in_pSonicContext + 56), EStateID_StateAirBoost, 0);
	}

	return originalStateRecoveryJumpUpdate(a1, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateStompingLandUpdate, m_SigStateStompingLandUpdate(), int64_t a1, int64_t a2, float in_deltaTime)
{
	if (!Configuration::IsStompDash || !IsMoveAvailable(Configuration::StompDashWorldType))
		return originalStateStompingLandUpdate(a1, a2, in_deltaTime);

	switch (BlackboardHelper::IsCyberSpace()
			? Configuration::StompDashInputTypeCyber
			: Configuration::StompDashInputType)
	{
		case Configuration::EStompDashInputType_Hold:
		{
			if (*(float*)(a1 + 180) > 0.0f)
			{
				m_StateFlags.set(EStateFlags_IsStompDash);

				fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateDropDash, 0);
			}

			break;
		}

		case Configuration::EStompDashInputType_Press:
		{
			if (InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
				break;

			// Prevent stomp bounce timer from running so we can do our own timing.
			*(float*)(a1 + 180) = 1.0f;

			m_StompDashPressDelayTime += in_deltaTime;

			if (m_StompDashPressDelayTime > 0.075f)
			{
				m_StateFlags.set(EStateFlags_IsStompDash);

				fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateDropDash, 0);
			}

			break;
		}
	}

	return originalStateStompingLandUpdate(a1, a2, in_deltaTime);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	Player::CreateInput();

	m_DeltaTime = *in_pDeltaTime;

	if (!m_StateFlags.test(EStateFlags_IsDropDash))
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
		case EStateID_StateFall:
		{
			if (m_IsAirDashJumpOut)
			{
				m_IsAirDashJumpOut = false;
				in_stateIndex = EStateID_StateDoubleJump;
			}

			break;
		}

		case EStateID_StateAirBoost:
		{
			if (Configuration::IsAirDash && IsMoveAvailable(Configuration::AirDashWorldType) && m_StateFlags.test(EStateFlags_IsDropDashCharge))
			{
				m_StateFlags.set(EStateFlags_IsAirDash);

				in_stateIndex = EStateID_StateDropDash;
			}

			break;
		}

		case EStateID_StateGrindDoubleJump:
		{
			if (Configuration::IsGrindDoubleJumpFix)
			{
				if (m_SigForceGrindJumpPosture() != nullptr)
					WRITE_NOP(m_SigForceGrindJumpPosture(), 2);

				in_stateIndex = EStateID_StateDoubleJump;
			}

			break;
		}

		case EStateID_StateStomping:
		{
			if (!Configuration::IsQuickStompDash ||
				!IsMoveAvailable(Configuration::QuickStompDashWorldType) ||
				(Configuration::IsQuickStompDashRequireAirBoost && !BlackboardHelper::IsAirBoosting()))
			{
				break;
			}

			bool isVelocityAboveThreshold = BlackboardHelper::IsSideView()
				? m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThresholdSV
				: m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThreshold;

			if (Configuration::IsQuickStompDashRequireAirBoost || isVelocityAboveThreshold)
			{
				m_StateFlags.set(EStateFlags_IsQuickStompDash);
				in_stateIndex = EStateID_StateDropDash;
			}

			break;
		}

		case EStateID_StateStompingLand:
			m_StompDashPressDelayTime = 0.0f;
			break;

		case EStateID_StateSliding:
		{
			if (Configuration::IsSlideDash)
			{
				if (m_DropDashDelayTime < 0.1f)
					return 0;

				m_DropDashDelayTime = 0.0f;

				m_StateFlags.set(EStateFlags_IsSlideDash);

				in_stateIndex = EStateID_StateDropDash;
			}

			break;
		}

		/* I have no idea what this state is, but it kept
		   killing Air Dash when jumping off rails. */
		case 165:
			return 0;

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

	m_IsAirDashJumpOut = false;
	m_StateFlags.reset(EStateFlags_IsDropDashCharge);

	return originalGOCPlayerHsmGroundStateUpdate(in_pThis, in_stateIndex);
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

HOOK(int64_t, __fastcall, PlayerSpeedUpdate, READ_CALL(m_SigPlayerSpeedUpdateCaller()), int64_t a1, int64_t a2)
{
	auto pVelocity = (Vector3*)(a2 + 0xD0);
	auto rotation = *(Quaternion*)(a2 + 0x90);
	auto forward = Quaternion::Forward(rotation);

	if (!m_StateFlags.test(EStateFlags_IsAirDashRelease) && m_StateFlags.test(EStateFlags_IsAirDash))
	{
		m_StateFlags.set(EStateFlags_IsAirDashRelease);

		*pVelocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::AirDashInitialVelocitySV
			: Configuration::AirDashInitialVelocity);
	}
	else if (!m_StateFlags.test(EStateFlags_IsStompDashRelease) && m_StateFlags.test(EStateFlags_IsStompDash))
	{
		m_StateFlags.set(EStateFlags_IsStompDashRelease);

		*pVelocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::StompDashInitialVelocitySV
			: Configuration::StompDashInitialVelocity);
	}

	m_HorizontalVelocity = Vector3::Magnitude(Vector3::ProjectOnPlane(*pVelocity, rotation * Vector3(0, 1, 0)));

#if _DEBUG
	// printf("[EnhancedDropDash] m_HorizontalVelocity: %f\n", m_HorizontalVelocity);
#endif

	return originalPlayerSpeedUpdate(a1, a2);
}

void Player::Install()
{
	FrontiersInput::Install();

	if (m_SigDropDashCameraDelay() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigDropDashCameraDelay(), 1);

	if (m_SigDropDashUngroundedExitFunc() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigDropDashUngroundedExitFunc(), 5);

	if (m_SigForceGrindJumpPosture() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigForceGrindJumpPosture(), 2);

	if (m_SigFixDropDashSideView() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigFixDropDashSideView(), 1);

	INSTALL_HOOK(StateDropDashStart);
	INSTALL_HOOK(StateDropDashUpdate);
	INSTALL_HOOK(StateDropDashEnd);
	INSTALL_HOOK(PostureDropDashUpdate);
	INSTALL_HOOK(StateDoubleJumpUpdate);
	INSTALL_HOOK(StateRecoveryJumpUpdate);
	INSTALL_HOOK(StateStompingLandUpdate);
	INSTALL_HOOK(GOCPlayerHsmUpdate);
	INSTALL_HOOK(GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(PlayerSpeedUpdate);

	if (Configuration::IsSlideDash)
	{
		// Prevent squat to slide.
		if (m_SigSquatToSlideWorkaround() != nullptr)
			WRITE_MEMORY(m_SigSquatToSlideWorkaround(), uint8_t, 0xEB);
	}
}