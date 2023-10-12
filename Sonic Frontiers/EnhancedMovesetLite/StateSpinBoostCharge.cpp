extern "C"
{
	DECLARE_ASM_HOOK(SpinChargeInputHandler);

	// SpinChargeInputHandler members
	int64_t m_pSigDisableSpinChargeOriginalChargeInput = 0;
	bool m_IsSpinCharge = false;
}

float m_SpinChargeVibration = 0.0f;
float m_SpinChargeTriggerVibration = 0.0f;

void StartSpinChargeCamera(int64_t in_pSonicContext, bool in_configValue)
{
	if (in_configValue)
	{
		// Use faster turning parameters.
		RFL_SET_CONTEXTUAL_PARAM(spinBoost.chargeRotateForce, 500.0f);
		RFL_SET_CONTEXTUAL_PARAM(spinBoost.cameraShakeName.value, "");
	}
	else
	{
		RFL_RESET_CONTEXTUAL_PARAM(spinBoost.chargeRotateForce);

		if (!IS_NOP(m_SigDisableSpinChargeCameraCode()))
			StateSpinBoostCharge::StartSpinChargeCamera(in_pSonicContext);
	}
}

void IncreaseCharge()
{
	m_SpinChargeVibration = 100.0f;
	m_SpinChargeTriggerVibration = 75.0f;
}

void UpdateController()
{
	m_SpinChargeVibration = max(std::lerp(m_SpinChargeVibration - 1.0f, 0.0f, Player::DeltaTime), 25.0f);
	m_SpinChargeTriggerVibration = max(std::lerp(m_SpinChargeTriggerVibration - 2.5f, 0.0f, Player::DeltaTime), 0.0f);

	if (Configuration::IsSpinChargeVibration)
	{
		Input::SetRumbleMotors(m_SpinChargeVibration);
		Input::SetTriggerMotor(Input::EInputIndex_Left, m_SpinChargeTriggerVibration);
	}
}

HOOK(int64_t, __fastcall, StateSpinBoostChargeStart, m_SigStateSpinBoostChargeStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = Player::IsGrounded();

	StateSpinBoostCharge::Flags.set(EStateSpinBoostChargeFlags_IsStartGrounded, isGrounded);

	IncreaseCharge();

	if (Configuration::IsSpinChargeNoAirDeceleration)
	{
		PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeDeceleration(), 5);
		WRITE_NOP(m_SigDisableSpinChargeDeceleration(), 5);
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeDeceleration());
	}

	if (isGrounded)
	{
		if (Configuration::IsSpinBoostEnhancedIslandPhysics)
		{
			RFL_SET_PARAM(forwardView.spinBoost.chargeRotateForce, 100.0f);
		}
		else
		{
			RFL_RESET_PARAM(forwardView.spinBoost.chargeRotateForce);
		}

		if (Configuration::SpinChargeCameraShakeType <= 3)
		{
			const char* cameraShakeName = Configuration::CameraShakeNames[Configuration::SpinChargeCameraShakeType].c_str();

			if (Configuration::SpinChargeCameraShakeType == -1)
				cameraShakeName = "";

			RFL_SET_CONTEXTUAL_PARAM(spinBoost.cameraShakeName.value, cameraShakeName);
		}

		StartSpinChargeCamera(in_pSonicContext, Configuration::IsSpinChargeNoGroundCamera);
	}
	else
	{
		StartSpinChargeCamera(in_pSonicContext, Configuration::IsSpinChargeNoAirCamera);
	}

	return originalStateSpinBoostChargeStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateSpinBoostChargeUpdate, m_SigStateSpinBoostChargeUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isSpinBoostRelease = false;

	switch (Configuration::SpinChargeControlType)
	{
		case ESpinChargeControlType_Frontiers:
		{
			// Increase Spin Charge multiplier on LT press.
			if (IsButtonPressed(EPlayerActionType_PlayerSonicboom))
				IncreaseCharge();

			if (IsButtonReleased(EPlayerActionType_PlayerStomping))
				isSpinBoostRelease = true;

			break;
		}

		case ESpinChargeControlType_LostWorld:
		{
			// Increase Spin Charge multiplier and execute original code via mid-asm hook on A/B press.
			if (IsButtonPressed(EPlayerActionType_PlayerJump) || IsButtonPressed(EPlayerActionType_PlayerStomping))
			{
				IncreaseCharge();

				m_IsSpinCharge = true;
			}
			else
			{
				m_IsSpinCharge = false;
			}

			// Exit into StateSpringJumpHeadLand on X/Y press.
			if (IsButtonPressed(EPlayerActionType_PlayerAttack) || IsButtonPressed(EPlayerActionType_PlayerCyloop))
			{
				Player::SetState(in_pSonicContext, ESonicState_StateSpringJumpHeadLand);
				return true;
			}

			// Exit into StateSpinBoost on LT release or when the player is grounded.
			if (IsButtonReleased(EPlayerActionType_PlayerSonicboom) ||
				(!StateSpinBoostCharge::Flags.test(EStateSpinBoostChargeFlags_IsStartGrounded) && Player::IsGrounded()))
			{
				isSpinBoostRelease = true;
			}

			break;
		}
	}

	UpdateController();

	if (Configuration::IsSpinChargeBoostRelease)
	{
		// Exit into StateSpinBoost on RT press.
		if (IsButtonPressed(EPlayerActionType_PlayerBoost))
			isSpinBoostRelease = true;
	}

	if (isSpinBoostRelease)
	{
		Player::SetState(in_pSonicContext, ESonicState_StateSpinBoost);
		return true;
	}

	return originalStateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, StateSpinBoostChargeEnd, m_SigStateSpinBoostChargeEnd(), int64_t in_pThis, int64_t in_pSonicContext, int64_t a3)
{
	Input::ResetMotors();

	return originalStateSpinBoostChargeEnd(in_pThis, in_pSonicContext, a3);
}

HOOK(bool, __fastcall, _StateSpinBoostCharge_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	if (in_stateId == ESonicState_StateSpinBoost)
		StateSpinBoostCharge::Flags.set(EStateSpinBoostChargeFlags_IsReleased);

	if (Configuration::SpinChargeControlType == ESpinChargeControlType_LostWorld)
	{
		// Exit into StateSpinBoostCharge if LT was buffered, since Sonic Lost World immediately charges on LT.
		if (in_stateId == ESonicState_StateSpinMove && Player::LastState != ESonicState_StateSpinBoost)
			in_stateId = ESonicState_StateSpinBoostCharge;
	}

	return original_StateSpinBoostCharge_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

HOOK(bool, __fastcall, _StateSpinBoostCharge_StateGrindJumpUpdate, m_SigStateGrindJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	// Exit into StateSpinBoostCharge.
	if (IsButtonPressed(EPlayerActionType_PlayerSonicboom))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateSpinBoostCharge);
		return true;
	}

	return original_StateSpinBoostCharge_StateGrindJumpUpdate(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, _StateSpinBoostCharge_StateStompingDownUpdate, m_SigStateStompingDownUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	// Play rolling animation to flow better into Spin Boost.
	if (IsButtonDown(EPlayerActionType_PlayerSonicboom))
		Player::SetAnimation("JUMP_BALL");

	return original_StateSpinBoostCharge_StateStompingDownUpdate(in_pThis, in_pSonicContext);
}

// This hook is a hack to obtain app::player::SonicContext, since the singleton from app::player::Sonic doesn't seem to work properly.
HOOK(int64_t, __fastcall, _StateSpinBoostCharge_StatePluginBoostUpdate, m_SigStatePluginBoostUpdate(), int64_t in_pThis, int64_t a2, float in_deltaTime)
{
	// Ignore bad naming convention, used for macro.
	int64_t in_pSonicContext = *(int64_t*)(in_pThis + 0x20);

	auto* pGOCPlayerKinematicParams = Player::GetKinematics();

	if (!pGOCPlayerKinematicParams)
		return original_StateSpinBoostCharge_StatePluginBoostUpdate(in_pThis, a2, in_deltaTime);

	float dot = (pGOCPlayerKinematicParams->Rotation * csl::math::Vector3::UnitY()).dot(csl::math::Vector3::UnitY());

	// Check dot product of current rotation to make sure we're not trying to enter StateSpinBoostCharge on a right angle.
	if (dot > 0.01f)
	{
		if (Player::CurrentState == ESonicState_StateWallMove || Player::CurrentState == ESonicState_StateClimbing)
		{
			// Allow StateSpinBoostCharge to work when resting on climbable walls.
			if (IsButtonDown(EPlayerActionType_PlayerStomping) && IsButtonPressed(EPlayerActionType_PlayerSonicboom))
				Player::SetState(in_pSonicContext, ESonicState_StateSpinBoostCharge);
		}
	}

	return original_StateSpinBoostCharge_StatePluginBoostUpdate(in_pThis, a2, in_deltaTime);
}

void StateSpinBoostCharge::ConfigLazyUpdate()
{
	if (Configuration::SpinChargeControlType == ESpinChargeControlType_LostWorld)
	{
		// Disable original charge implementation to use our own.
		if (m_SigDisableSpinChargeOriginalChargeInput() != nullptr)
		{
			m_pSigDisableSpinChargeOriginalChargeInput = (uint64_t)m_SigDisableSpinChargeOriginalChargeInput();

			PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeOriginalChargeInput(), 7);
			INSTALL_HOOK_ADDRESSED(SpinChargeInputHandler, m_pSigDisableSpinChargeOriginalChargeInput);
			WRITE_NOP((uint64_t)m_SigDisableSpinChargeOriginalChargeInput() + 5, 2);
		}

		// Disable original release implementation to use our own.
		if (m_SigDisableSpinChargeOriginalReleaseInput() != nullptr)
		{
			PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeOriginalReleaseInput(), 2);
			WRITE_NOP(m_SigDisableSpinChargeOriginalReleaseInput(), 2);

			PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeOriginalReleaseInput() + 9, 2);
			WRITE_MEMORY((int64_t)(m_SigDisableSpinChargeOriginalReleaseInput()) + 9, uint8_t, 0xEB);
		}

		if (m_SigDisableSpinChargeRelease() != nullptr)
		{
			PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeRelease(), 1);
			WRITE_MEMORY(m_SigDisableSpinChargeRelease(), uint8_t, 0xEB);
		}

		// Replace StateSpinBoost with StateSpinBoostCharge whilst running.
		if (m_SigRunToSpinBoostCaller() != nullptr)
		{
			PRESERVE_MEMORY(READ_CALL(m_SigRunToSpinBoostCaller()) + 0xD8, 1);
			WRITE_MEMORY(READ_CALL(m_SigRunToSpinBoostCaller()) + 0xD8, uint8_t, ESonicState_StateSpinBoostCharge);
		}
	}
	else
	{
		if (m_SigDisableSpinChargeOriginalChargeInput() != nullptr)
		{
			RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeOriginalChargeInput());
		}

		if (m_SigDisableSpinChargeOriginalReleaseInput() != nullptr)
		{
			RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeOriginalReleaseInput());
			RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeOriginalReleaseInput() + 9);
		}

		if (m_SigDisableSpinChargeRelease() != nullptr)
		{
			RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeRelease());
		}

		if (m_SigRunToSpinBoostCaller() != nullptr)
		{
			RESTORE_MEMORY(READ_CALL(m_SigRunToSpinBoostCaller()) + 0xD8);
		}
	}
}

void StateSpinBoostCharge::Install()
{
	// Disable original Spin Charge camera implementation.
	WRITE_MEMORY(m_SigDisableSpinChargeCamera(), uint8_t, 0xEB);

	INSTALL_HOOK(StateSpinBoostChargeStart);
	INSTALL_HOOK(StateSpinBoostChargeUpdate);
	INSTALL_HOOK(StateSpinBoostChargeEnd);
	INSTALL_HOOK(_StateSpinBoostCharge_GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(_StateSpinBoostCharge_StateGrindJumpUpdate);
	INSTALL_HOOK(_StateSpinBoostCharge_StateStompingDownUpdate);
	INSTALL_HOOK(_StateSpinBoostCharge_StatePluginBoostUpdate);
}