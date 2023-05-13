std::bitset<9> m_StateFlags;
std::bitset<3> m_AirDashFlags;
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
	EStateFlags_IsQuickStompDash,
	EStateFlags_IsGroundedOnce
};

enum EAirDashFlags
{
	EAirDashFlags_AwaitDoubleJump,
	EAirDashFlags_AwaitRecovery,
	EAirDashFlags_FromRecoveryJump
};

enum EInputFlags
{
	EInputFlags_IsJumpInputBuffered,
	EInputFlags_IsUncurlInputBuffered,
	EInputFlags_IsUncurlTriggerBuffered
};

enum EStateID
{
	EStateID_Default = -1,
	EStateID_StateRun = 4,
	EStateID_StateDoubleJump = 9,
	EStateID_StateStompingBounce = 10,
	EStateID_StateRecoveryJump = 11,
	EStateID_StateFall = 14,
	EStateID_StateRecovery = 15,
	EStateID_StateAirBoost = 22,
	EStateID_StateGrindDoubleJump = 46,
	EStateID_StateStomping = 52,
	EStateID_StateStompingLand = 55,
	EStateID_StateSliding = 57,
	EStateID_StateDropDash = 110,
	EStateID_StateFan = 165
};

float m_DeltaTime = 0.0f;
float m_DropDashDelayTime = 0.0f;
float m_StompDashHoldDelayTime = 0.0f;
float m_StompDashPressDelayTime = 0.0f;
float m_HorizontalVelocity = 0.0f;

EStateID m_LastStateID = EStateID_Default;

FUNCTION_PTR(bool, __fastcall, fpSetCurrentState, m_SigSetCurrentState(), int64_t a1, int a2, int a3);

bool IsGrounded()
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return false;

	auto* pLevelInfo = pGameDocument->GetService<app::level::LevelInfo>();

	if (!pLevelInfo)
		return false;

	return pLevelInfo->playerInfos[0]->IsGrounded;
}

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

bool IsGroundedExit()
{
	return (Configuration::AirDashUncurlType == Configuration::EUncurlType_Grounded && m_StateFlags.test(EStateFlags_IsAirDash) ||
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

	m_AirDashFlags.set(EAirDashFlags_AwaitRecovery, m_StateFlags.test(EStateFlags_IsAirDash));

	// Exit StateDropDash into StateRecovery immediately (if enabled).
	if (IsImmediateExit())
	{
		fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateRecovery, 0);
		return true;
	}

	/* Set flag if we've been grounded at least once. This'll be used
	   for other conditions later that we must check when grounded. */
	if (!m_StateFlags.test(EStateFlags_IsGroundedOnce))
		m_StateFlags.set(EStateFlags_IsGroundedOnce, isGrounded);

	if (isGrounded)
	{
		// Exit StateDropDash into StateRun when grounded (if enabled) or whilst RT is held.
		if (IsGroundedExit() || !m_InputFlags.test(EInputFlags_IsUncurlTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
		{
			BlackboardHelper::GetStatus()->StateParameter |= STATUS_PARAM_BOOST;

			fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateRun, 0);

			return true;
		}
	}
	else
	{
		// Set double jump flag for when we enter the fall state later after cancelling Air Dash.
		if (!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && m_StateFlags.test(EStateFlags_IsAirDash) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
			m_AirDashFlags.set(EAirDashFlags_AwaitDoubleJump, true);

		// Exit StateDropDash into StateRecovery when ungrounded (if enabled).
		if (IsUngroundedExit() && m_StateFlags.test(EStateFlags_IsGroundedOnce))
		{
			fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateRecovery, 0);
			return true;
		}

		// Exit StateDropDash into StateAirBoost whilst RT is held when airborne.
		if (Configuration::IsAirBoostUngroundedExit && (!m_InputFlags.test(EInputFlags_IsUncurlTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD))
		{
			fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateAirBoost, 0);
			return true;
		}

		// Exit StateDropDash into StateStomping.
		if (Configuration::IsStompUngroundedExit && (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B)))
		{
			fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateStomping, 0);
			return true;
		}
	}

	// Exit StateDropDash into either StateRun or StateFall whilst B or A are held.
	if (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B) ||
		!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
	{
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

	return originalStateDropDashEnd(a1, a2);
}

HOOK(bool, __fastcall, PostureDropDashUpdate, m_SigPostureDropDashUpdate(), int64_t a1, double a2)
{
	if (Configuration::IsSideViewRollFix && m_SigFixDropDashSideView() != nullptr)
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

	// Always allow air boost exit for Air Dash.
	if (!m_AirDashFlags.test(EAirDashFlags_FromRecoveryJump) &&
		m_StateFlags.test(EStateFlags_IsDropDashCharge) &&
		InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		m_AirDashFlags.set(EAirDashFlags_FromRecoveryJump);

		fpSetCurrentState(*(int64_t*)(in_pSonicContext + 56), EStateID_StateAirBoost, 0);
	}

	return originalStateRecoveryJumpUpdate(a1, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateStompingLandUpdate, m_SigStateStompingLandUpdate(), int64_t a1, int64_t a2, float in_deltaTime)
{
	if (!Configuration::IsStompDash || !IsMoveAvailable(Configuration::StompDashWorldType))
		return originalStateStompingLandUpdate(a1, a2, in_deltaTime);

	bool startDropDash = false;

	switch (BlackboardHelper::IsCyberSpace()
			? Configuration::StompDashInputTypeCyber
			: Configuration::StompDashInputType)
	{
		case Configuration::EStompDashInputType_Hold:
		{
			if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
				break;

			// Disable original timing.
			*(float*)(a1 + 180) = 1.0f;

			m_StompDashHoldDelayTime += in_deltaTime;

			startDropDash = m_StompDashHoldDelayTime > Configuration::StompDashHoldDelay;

			break;
		}

		case Configuration::EStompDashInputType_Press:
		{
			if (InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
				break;

			// Disable original timing.
			*(float*)(a1 + 180) = 1.0f;

			m_StompDashPressDelayTime += in_deltaTime;

			startDropDash = m_StompDashPressDelayTime > 0.075f;

			break;
		}
	}

	if (startDropDash)
	{
		m_StateFlags.set(EStateFlags_IsStompDash);

		fpSetCurrentState(*(int64_t*)(a2 + 56), EStateID_StateDropDash, 0);
	}

	return originalStateStompingLandUpdate(a1, a2, in_deltaTime);
}

HOOK(bool, __fastcall, ObjFanProcessMessage, m_SigObjFanProcessMessage(), int64_t a1, int64_t a2)
{
	// Disable fans if we're rolling.
	if (Configuration::IsNoFansWhenRolling && m_StateFlags.test(EStateFlags_IsDropDash))
		return 1;

	return originalObjFanProcessMessage(a1, a2);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	Player::CreateInput();

	m_DeltaTime = *in_pDeltaTime;

	if (!m_StateFlags.test(EStateFlags_IsDropDash))
		m_DropDashDelayTime += m_DeltaTime;

	originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

HOOK(char, __fastcall, GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, EStateID in_stateId)
{
#if _DEBUG
	printf("[EnhancedDropDash::GOCPlayerHsmGroundStateUpdate] m_LastStateID: %d\n", m_LastStateID);
	printf("[EnhancedDropDash::GOCPlayerHsmGroundStateUpdate] in_stateId:    %d\n", in_stateId);
#endif

	switch (in_stateId)
	{
		case EStateID_StateFall:
		{
			/* I was debating changing this implementation to just switch
			   the state from StateDropDash itself, but doing that cancels
			   all horizontal velocity, so we're gonna keep it the old way. */
			if (m_AirDashFlags.test(EAirDashFlags_AwaitDoubleJump))
			{
				m_AirDashFlags.reset(EAirDashFlags_AwaitDoubleJump);

				in_stateId = EStateID_StateDoubleJump;
			}

			break;
		}

		case EStateID_StateAirBoost:
		{
			if (!Configuration::IsAirDash)
				break;

			if (!IsMoveAvailable(Configuration::AirDashWorldType))
				break;

			if (m_StateFlags.test(EStateFlags_IsDropDashCharge) && !m_AirDashFlags.test(EAirDashFlags_AwaitRecovery))
			{
				m_StateFlags.set(EStateFlags_IsAirDash);

				in_stateId = EStateID_StateDropDash;
			}

			break;
		}

		case EStateID_StateGrindDoubleJump:
		{
			if (!Configuration::IsGrindDoubleJumpFix)
				break;

			if (m_SigForceGrindJumpPosture() != nullptr)
				WRITE_NOP(m_SigForceGrindJumpPosture(), 2);

			in_stateId = EStateID_StateDoubleJump;

			break;
		}

		case EStateID_StateStomping:
		{
			if (!Configuration::IsQuickStompDash)
				break;

			if (!IsMoveAvailable(Configuration::QuickStompDashWorldType))
				break;

			if (Configuration::IsQuickStompDashRequireAirBoost && !BlackboardHelper::IsAirBoosting())
				break;

			/* Do a regular stomp if we're in StateRecovery or StateRecoveryJump,
			   otherwise we can spam Quick Stomp Dash. */
			if (m_LastStateID == EStateID_StateRecovery || m_LastStateID == EStateID_StateRecoveryJump)
				break;

			bool isVelocityAboveThreshold = BlackboardHelper::IsSideView()
				? m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThresholdSV
				: m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThreshold;

			if (Configuration::IsQuickStompDashRequireAirBoost || isVelocityAboveThreshold)
			{
				m_StateFlags.set(EStateFlags_IsQuickStompDash);

				in_stateId = EStateID_StateDropDash;
			}

			break;
		}

		case EStateID_StateStompingLand:
			m_StompDashHoldDelayTime = 0.0f;
			m_StompDashPressDelayTime = 0.0f;
			break;

		case EStateID_StateSliding:
		{
			if (!Configuration::IsSlideDash)
				break;

			if (m_DropDashDelayTime < 0.1f)
				return 0;

			m_DropDashDelayTime = 0.0f;

			m_StateFlags.set(EStateFlags_IsSlideDash);

			in_stateId = EStateID_StateDropDash;

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

	if (in_stateId != EStateID_StateRecovery && in_stateId != EStateID_StateRecoveryJump)
		m_AirDashFlags.reset(EAirDashFlags_AwaitRecovery);

	m_StateFlags.reset(EStateFlags_IsDropDashCharge);

	m_LastStateID = in_stateId;

	return originalGOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

#if 0
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmAirStateUpdate, "\x41\x56\x48\x83\xEC\x30\x0F\xB6\x81\x1C", "xxxxxxxxxx");

HOOK(char, __fastcall, GOCPlayerHsmAirStateUpdate, m_SigGOCPlayerHsmAirStateUpdate(), int64_t* in_pThis, int in_stateId)
{
#if _DEBUG
	printf("[EnhancedDropDash::GOCPlayerHsmAirStateUpdate] in_stateId: %d\n", in_stateId);
#endif

	return originalGOCPlayerHsmAirStateUpdate(in_pThis, in_stateId);
}
#endif

HOOK(int64_t, __fastcall, PlayerSpeedUpdate, READ_CALL(m_SigPlayerSpeedUpdateCaller()), int64_t a1, int64_t a2)
{
	auto pVelocity = (Vector3*)(a2 + 0xD0);
	auto rotation = *(Quaternion*)(a2 + 0x90);
	auto forward = Quaternion::Forward(rotation);

	if (IsGrounded() || BlackboardHelper::IsGrinding())
		m_AirDashFlags.reset(EAirDashFlags_FromRecoveryJump);

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

	if (m_SigForceGrindJumpPosture() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigForceGrindJumpPosture(), 2);

	if (m_SigFixDropDashSideView() != nullptr)
		PRESERVE_MEMORY((uint64_t)m_SigFixDropDashSideView(), 1);

	if (m_SigCanRecoveryJump() != nullptr)
	{
		READ_THUNK(CanRecoveryJump, (uint64_t)m_SigCanRecoveryJump());

		// Force allow recovery jump.
		WRITE_NOP(CanRecoveryJump + 0xA9, 2);
	}

	INSTALL_HOOK(StateDropDashStart);
	INSTALL_HOOK(StateDropDashUpdate);
	INSTALL_HOOK(StateDropDashEnd);
	INSTALL_HOOK(PostureDropDashUpdate);
	INSTALL_HOOK(StateDoubleJumpUpdate);
	INSTALL_HOOK(StateRecoveryJumpUpdate);
	INSTALL_HOOK(StateStompingLandUpdate);
	INSTALL_HOOK(ObjFanProcessMessage);
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