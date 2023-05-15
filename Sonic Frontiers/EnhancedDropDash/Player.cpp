std::bitset<8> m_DropDashStateFlags;
std::bitset<4> m_PersistentStateFlags;
std::bitset<3> m_InputFlags;

enum EDropDashStateFlags
{
	EDropDashStateFlags_IsAirDash,
	EDropDashStateFlags_IsAirDashRelease,
	EDropDashStateFlags_IsDropDash,
	EDropDashStateFlags_IsDropDashCharge,
	EDropDashStateFlags_IsGroundedOnce,
	EDropDashStateFlags_IsSlideDash,
	EDropDashStateFlags_IsStompDash,
	EDropDashStateFlags_IsStompDashRelease
};

enum EPersistentStateFlags
{
	EPersistentStateFlags_IsAirDashExitDoubleJump,
	EPersistentStateFlags_IsAirDashExitRecovery,
	EPersistentStateFlags_IsAirDashFromRecoveryJump,
	EPersistentStateFlags_IsQuickStompDash
};

enum EInputFlags
{
	EInputFlags_IsJumpInputBuffered,
	EInputFlags_IsUncurlTriggerBuffered,
	EInputFlags_IsUncurlInputBuffered
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
	EStateID_StateQuickStep = 65,
	EStateID_StateQuickStepLeft = 66,
	EStateID_StateQuickStepRight = 67,
	EStateID_StateDropDash = 110,
	EStateID_StateFan = 165
};

float m_DeltaTime = 0.0f;
float m_DropDashDelayTime = 0.0f;
float m_StompDashHoldDelayTime = 0.0f;
float m_StompDashPressDelayTime = 0.0f;
float m_HorizontalVelocity = 0.0f;

EStateID m_LastStateID = EStateID_Default;

bool SetCurrentState(int64_t in_pSonicContext, EStateID in_stateId)
{
	FUNCTION_PTR(bool, __fastcall, fpSetCurrentState, m_SigSetCurrentState(), int64_t a1, int a2, int a3);

	return fpSetCurrentState(*(int64_t*)(in_pSonicContext + 56), in_stateId, 0);
}

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
	return m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsSlideDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsStompDash) &&
		!m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash);
}

bool IsGroundDropDash()
{
	return m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) &&
		!m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash);
}

bool IsNoCameraDelay()
{
	return Configuration::IsNoCameraDelay && IsNormalDropDash() ||
		Configuration::IsNoAirDashCameraDelay && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) ||
		Configuration::IsNoSlideDashCameraDelay && m_DropDashStateFlags.test(EDropDashStateFlags_IsSlideDash) ||
		Configuration::IsNoStompDashCameraDelay && m_DropDashStateFlags.test(EDropDashStateFlags_IsStompDash) ||
		Configuration::IsNoQuickStompDashCameraDelay && m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash);
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

	return (Configuration::AirDashUncurlType == Configuration::EUncurlType_Immediate && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash)) ||
		(Configuration::QuickStompDashUncurlType == Configuration::EUncurlType_Immediate && m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash));
}

bool IsUngroundedExit()
{
	if (IsCyberSpaceOrSideView())
		return false;

	return Configuration::IsUncurlWhenUngrounded;
}

bool IsGroundedExit()
{
	return (Configuration::AirDashUncurlType == Configuration::EUncurlType_Grounded && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) ||
		Configuration::QuickStompDashUncurlType == Configuration::EUncurlType_Grounded && m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash));
}

HOOK(int64_t, __fastcall, StateDropDashStart, m_SigStateDropDashStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	m_DropDashStateFlags.set(EDropDashStateFlags_IsDropDash);
	m_InputFlags.set(EInputFlags_IsJumpInputBuffered, InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A));
	m_InputFlags.set(EInputFlags_IsUncurlInputBuffered, InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B));
	m_InputFlags.set(EInputFlags_IsUncurlTriggerBuffered, InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD);

	if (IsNoCameraDelay())
	{
		if (m_SigDropDashCameraDelay() != nullptr)
			WRITE_MEMORY(m_SigDropDashCameraDelay(), uint8_t, 0xEB);
	}

	return originalStateDropDashStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateDropDashUpdate, m_SigStateDropDashUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = *(bool*)((*(int64_t*)(in_pSonicContext + 72) + 400) + 53) & 2;

	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
		m_InputFlags.reset(EInputFlags_IsJumpInputBuffered);

	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
		m_InputFlags.reset(EInputFlags_IsUncurlInputBuffered);

	if (InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) < TRIGGER_THRESHOLD)
		m_InputFlags.reset(EInputFlags_IsUncurlTriggerBuffered);

	m_PersistentStateFlags.set(EPersistentStateFlags_IsAirDashExitRecovery, m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash));

	// Exit StateDropDash into StateRecovery immediately (if enabled).
	if (IsImmediateExit())
	{
		SetCurrentState(in_pSonicContext, EStateID_StateRecovery);
		return true;
	}

	/* Set flag if we've been grounded at least once. This'll be used
	   for other conditions later that we must check when grounded. */
	if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsGroundedOnce))
		m_DropDashStateFlags.set(EDropDashStateFlags_IsGroundedOnce, isGrounded);

	if (isGrounded)
	{
		// Exit StateDropDash into StateRun when grounded (if enabled) or whilst RT is held.
		if (IsGroundedExit() || !m_InputFlags.test(EInputFlags_IsUncurlTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
		{
			BlackboardHelper::GetStatus()->StateParameter |= STATUS_PARAM_BOOST;

			SetCurrentState(in_pSonicContext, EStateID_StateRun);

			return true;
		}
	}
	else
	{
		// Set double jump flag for when we enter the fall state later after cancelling Air Dash.
		if (!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) &&
			m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) &&
			InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
		{
			m_PersistentStateFlags.set(EPersistentStateFlags_IsAirDashExitDoubleJump);
		}

		// Exit StateDropDash into StateRecovery when ungrounded (if enabled).
		if (IsUngroundedExit() && m_DropDashStateFlags.test(EDropDashStateFlags_IsGroundedOnce))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateRecovery);
			return true;
		}

		// Exit StateDropDash into StateAirBoost whilst RT is held when airborne.
		if (Configuration::IsAirBoostRollCancel && (!m_InputFlags.test(EInputFlags_IsUncurlTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateAirBoost);
			return true;
		}

		// Exit StateDropDash into StateStomping.
		if (Configuration::IsStompRollCancel && (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B)))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateStomping);
			return true;
		}
	}

	// Exit StateDropDash into StateQuickStep.
	if (Configuration::IsQuickStepRollCancel && (InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_LEFT_SHOULDER) || InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)))
	{
		SetCurrentState(in_pSonicContext, EStateID_StateQuickStep);
		return true;
	}

	// Exit StateDropDash into either StateRun or StateFall whilst B or A are held.
	if (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B) ||
		!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
	{
		SetCurrentState(in_pSonicContext, isGrounded ? EStateID_StateRun : EStateID_StateFall);
		return true;
	}

	return originalStateDropDashUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, StateDropDashEnd, m_SigStateDropDashEnd(), int64_t in_pThis, int64_t in_pSonicContext)
{
	m_DropDashStateFlags.reset();

	if (m_SigDropDashCameraDelay() != nullptr)
		RESTORE_MEMORY((uint64_t)m_SigDropDashCameraDelay());

	return originalStateDropDashEnd(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, PostureDropDashUpdate, m_SigPostureDropDashUpdate(), int64_t in_pThis, double in_deltaTime)
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

	return originalPostureDropDashUpdate(in_pThis, in_deltaTime);
}

HOOK(bool, __fastcall, StateDoubleJumpUpdate, m_SigStateDoubleJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	m_DropDashStateFlags.set(EDropDashStateFlags_IsDropDashCharge, *(float*)(in_pThis + 180) > 0.0f);

	return originalStateDoubleJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateRecoveryJumpUpdate, m_SigStateRecoveryJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	m_DropDashStateFlags.set(EDropDashStateFlags_IsDropDashCharge, *(bool*)(in_pThis + 196));

	// Always allow air boost exit for Air Dash.
	if (!m_PersistentStateFlags.test(EPersistentStateFlags_IsAirDashFromRecoveryJump) &&
		m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDashCharge) &&
		InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		m_PersistentStateFlags.set(EPersistentStateFlags_IsAirDashFromRecoveryJump);

		SetCurrentState(in_pSonicContext, EStateID_StateAirBoost);
	}

	return originalStateRecoveryJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateStompingLandUpdate, m_SigStateStompingLandUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	if (!Configuration::IsStompDash || !IsMoveAvailable(Configuration::StompDashWorldType))
		return originalStateStompingLandUpdate(in_pThis, in_pSonicContext, in_deltaTime);

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
			*(float*)(in_pThis + 180) = 1.0f;

			m_StompDashHoldDelayTime += in_deltaTime;

			startDropDash = m_StompDashHoldDelayTime > Configuration::StompDashHoldDelay;

			break;
		}

		case Configuration::EStompDashInputType_Press:
		{
			if (InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
				break;

			// Disable original timing.
			*(float*)(in_pThis + 180) = 1.0f;

			m_StompDashPressDelayTime += in_deltaTime;

			startDropDash = m_StompDashPressDelayTime > 0.075f;

			break;
		}
	}

	if (startDropDash)
	{
		m_DropDashStateFlags.set(EDropDashStateFlags_IsStompDash);

		SetCurrentState(in_pSonicContext, EStateID_StateDropDash);
	}

	return originalStateStompingLandUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, ObjFanProcessMessage, m_SigObjFanProcessMessage(), int64_t in_pThis, int64_t a2)
{
	// Disable fans if we're rolling.
	if (Configuration::IsNoFansWhenRolling && m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash))
		return 1;

	return originalObjFanProcessMessage(in_pThis, a2);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	Player::CreateInput();

	m_DeltaTime = *in_pDeltaTime;

	if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash))
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
			if (m_PersistentStateFlags.test(EPersistentStateFlags_IsAirDashExitDoubleJump))
			{
				m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirDashExitDoubleJump);

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

			if (m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDashCharge) && !m_PersistentStateFlags.test(EPersistentStateFlags_IsAirDashExitRecovery))
			{
				m_DropDashStateFlags.set(EDropDashStateFlags_IsAirDash);

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

			if ((m_LastStateID == EStateID_StateAirBoost &&
				m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash)))
			{
				break;
			}

			if (m_LastStateID == EStateID_StateRecovery ||
				m_LastStateID == EStateID_StateRecoveryJump)
			{
				break;
			}

			bool isVelocityAboveThreshold = BlackboardHelper::IsSideView()
				? m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThresholdSV
				: m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThreshold;

			if (Configuration::IsQuickStompDashRequireAirBoost || isVelocityAboveThreshold)
			{
				m_PersistentStateFlags.set(EPersistentStateFlags_IsQuickStompDash);

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

			m_DropDashStateFlags.set(EDropDashStateFlags_IsSlideDash);

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
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirDashExitRecovery);
	
	// Reset Quick Stomp Dash flag for Immediate exit.
	if (in_stateId == EStateID_StateRecovery || in_stateId == EStateID_StateRecoveryJump)
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsQuickStompDash);

	m_DropDashStateFlags.reset(EDropDashStateFlags_IsDropDashCharge);

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

HOOK(int64_t, __fastcall, PlayerSpeedUpdate, READ_CALL(m_SigPlayerSpeedUpdateCaller()), int64_t in_pThis, int64_t in_pGOCPlayerKinematicParams)
{
	auto pVelocity = (Vector3*)(in_pGOCPlayerKinematicParams + 0xD0);
	auto rotation = *(Quaternion*)(in_pGOCPlayerKinematicParams + 0x90);
	auto forward = Quaternion::Forward(rotation);

	if (IsGrounded() || BlackboardHelper::IsGrinding())
	{
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirDashFromRecoveryJump);
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsQuickStompDash);
	}

	if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDashRelease) && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash))
	{
		m_DropDashStateFlags.set(EDropDashStateFlags_IsAirDashRelease);

		*pVelocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::AirDashInitialVelocitySV
			: Configuration::AirDashInitialVelocity);
	}
	else if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsStompDashRelease) && m_DropDashStateFlags.test(EDropDashStateFlags_IsStompDash))
	{
		m_DropDashStateFlags.set(EDropDashStateFlags_IsStompDashRelease);

		*pVelocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::StompDashInitialVelocitySV
			: Configuration::StompDashInitialVelocity);
	}

	m_HorizontalVelocity = Vector3::Magnitude(Vector3::ProjectOnPlane(*pVelocity, rotation * Vector3(0, 1, 0)));

#if _DEBUG
	// printf("[EnhancedDropDash] m_HorizontalVelocity: %f\n", m_HorizontalVelocity);
#endif

	return originalPlayerSpeedUpdate(in_pThis, in_pGOCPlayerKinematicParams);
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