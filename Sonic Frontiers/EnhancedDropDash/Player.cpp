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

enum EInputFlags
{
	EInputFlags_IsJumpInputBuffered,
	EInputFlags_IsUncurlInputBuffered,
	EInputFlags_IsUncurlTriggerBuffered
};

bool m_IsAirDashJumpOut = false;

float m_DeltaTime = 0.0f;
float m_DropDashDelayTime = 0.0f;
float m_HorizontalVelocity = 0.0f;

FUNCTION_PTR(bool, __fastcall, fpSetStateFlags, m_SigSetStateFlags(), int64_t a1, int a2, int a3);

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
		fpSetStateFlags(*(int64_t*)(a2 + 56), isGrounded ? 4 : 14, 0);

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

HOOK(void, __fastcall, PostureDropDashUpdate, m_SigPostureDropDashUpdate(), int64_t* in_pThis, float in_deltaTime)
{
	// Fix for rolling getting stuck in 2D.
	if (BlackboardHelper::IsSideView())
		*(bool*)(in_pThis + 32) = true;

	originalPostureDropDashUpdate(in_pThis, in_deltaTime);
}

HOOK(bool, __fastcall, StateDoubleJumpUpdate, m_SigStateDoubleJumpUpdate(), int64_t a1, int64_t in_pSonicContext, float in_deltaTime)
{
	m_StateFlags.set(EStateFlags_IsDropDashCharge, *(float*)(a1 + 180) > 0.0f);

	return originalStateDoubleJumpUpdate(a1, in_pSonicContext, in_deltaTime);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	Player::CreateInput();

	m_DeltaTime = *in_pDeltaTime;

	if (!m_StateFlags.test(EStateFlags_IsDropDash))
		m_DropDashDelayTime += m_DeltaTime;

	originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

bool DoStompDash(Configuration::EStompDashInputType in_inputType)
{
	if (!Configuration::IsStompDash)
		return false;

	if (!IsMoveAvailable(Configuration::StompDashWorldType))
		return false;

	if (Configuration::StompDashInputType != in_inputType)
		return false;

	m_StateFlags.set(EStateFlags_IsStompDash);

	return true;
}

HOOK(char, __fastcall, GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, int in_stateIndex)
{
#if _DEBUG
	printf("[EnhancedDropDash::GOCPlayerHsmGroundStateUpdate] in_stateIndex: %d\n", in_stateIndex);
#endif

	switch (in_stateIndex)
	{
		// StateFall (?)
		case 14:
		{
			if (m_IsAirDashJumpOut)
			{
				m_IsAirDashJumpOut = false;

				// Swap to StateDoubleJump.
				in_stateIndex = 9;
			}

			break;
		}

		// StateAirBoost
		case 22:
		{
			if (Configuration::IsAirDash && IsMoveAvailable(Configuration::AirDashWorldType) && m_StateFlags.test(EStateFlags_IsDropDashCharge))
			{
				m_StateFlags.set(EStateFlags_IsAirDash);

				// Swap to StateDropDash.
				in_stateIndex = 110;
			}

			break;
		}

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
			
				// Swap to StateDropDash.
				in_stateIndex = 110;
			}

			break;
		}

		// StateStompingLand
		case 55:
		{
			if (DoStompDash(Configuration::EStompDashInputType_Press))
			{
				// Swap to StateDropDash.
				in_stateIndex = 110;
			}

			break;
		}

		// StateSliding
		case 57:
		{
			if (Configuration::IsSlideDash)
			{
				if (m_DropDashDelayTime < 0.1f)
					return 0;

				m_DropDashDelayTime = 0.0f;
				m_StateFlags.set(EStateFlags_IsSlideDash);

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

	m_IsAirDashJumpOut = false;
	m_StateFlags.reset(EStateFlags_IsDropDashCharge);

	return originalGOCPlayerHsmGroundStateUpdate(in_pThis, in_stateIndex);
}

HOOK(char, __fastcall, GOCPlayerHsmAirStateUpdate, m_SigGOCPlayerHsmAirStateUpdate(), int64_t* in_pThis, int in_stateIndex)
{
#if _DEBUG
	printf("[EnhancedDropDash::GOCPlayerHsmAirStateUpdate] in_stateIndex: %d\n", in_stateIndex);
#endif

	switch (in_stateIndex)
	{
		// StateStompingBounce
		case 10:
		{
			if (DoStompDash(Configuration::EStompDashInputType_Hold))
			{
				// Swap to StateDropDash.
				in_stateIndex = 110;
			}

			break;
		}
	}

	return originalGOCPlayerHsmAirStateUpdate(in_pThis, in_stateIndex);
}

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

	INSTALL_HOOK(StateDropDashStart);
	INSTALL_HOOK(StateDropDashUpdate);
	INSTALL_HOOK(StateDropDashEnd);
	INSTALL_HOOK(PostureDropDashUpdate);
	INSTALL_HOOK(StateDoubleJumpUpdate);
	INSTALL_HOOK(GOCPlayerHsmUpdate);
	INSTALL_HOOK(GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(GOCPlayerHsmAirStateUpdate);
	INSTALL_HOOK(PlayerSpeedUpdate);

	if (Configuration::IsSlideDash)
	{
		// Prevent squat to slide.
		if (m_SigSquatToSlideWorkaround() != nullptr)
			WRITE_MEMORY(m_SigSquatToSlideWorkaround(), uint8_t, 0xEB);
	}
}