bool m_IsAlwaysTrickablePreviouslyEnabled = false;

float m_SpinBoostJumpUngroundedTime = 0.0f;

HOOK(int64_t, __fastcall, StateSpinBoostStart, m_SigStateSpinBoostStart(), int64_t in_pThis, int64_t in_pSonicContext, int64_t a3)
{
	if (Configuration::IsSpinBoostAlwaysTrickableExit)
	{
		if (m_SigAlwaysTrickableSpinBoostExit() != nullptr)
		{
			PRESERVE_MEMORY((int64_t)m_SigAlwaysTrickableSpinBoostExit(), 4);
			WRITE_MEMORY(m_SigAlwaysTrickableSpinBoostExit(), uint8_t, 0x41, 0x8D, 0x50, 0x10);

			m_IsAlwaysTrickablePreviouslyEnabled = true;
		}
	}
	else if (m_IsAlwaysTrickablePreviouslyEnabled)
	{
		RESTORE_MEMORY((int64_t)m_SigAlwaysTrickableSpinBoostExit());

		m_IsAlwaysTrickablePreviouslyEnabled = false;
	}

	return originalStateSpinBoostStart(in_pThis, in_pSonicContext, a3);
}

void StartSpinMove(int64_t in_pSonicContext)
{
	StateSpinBoost::Flags.set(EStateSpinBoostFlags_IsSpinMove);

	Player::SetState(in_pSonicContext, ESonicState_StateSpinMove);
}

HOOK(bool, __fastcall, StateSpinBoostUpdate, m_SigStateSpinBoostUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = Player::IsGrounded();
	bool isSpinMove = false;

	// Exit into StateSpringJumpHeadLand or StateBumpJump if LT was buffered and released.
	if (IsButtonReleased(EPlayerActionType_PlayerSonicboom) && Configuration::IsSpinBoostInputReleaseCancel)
	{
		Player::SetState(in_pSonicContext, isGrounded ? ESonicState_StateSpringJumpHeadLand : ESonicState_StateBumpJump);
		return true;
	}

	if (!isGrounded)
	{
		// Allow exiting StateSpinBoost into StateDoubleJump when ungrounded, checking for repeat inputs.
		if (IsButtonPressed(EPlayerActionType_PlayerJump) && !StateSpinBoost::Flags.test(EStateSpinBoostFlags_IsDoubleJump))
		{
			StateSpinBoost::Flags.set(EStateSpinBoostFlags_IsDoubleJump);
			Player::SetState(in_pSonicContext, ESonicState_StateDoubleJump);
			return true;
		}
	}

	return originalStateSpinBoostUpdate(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, _StateSpinBoost_StateFallSlopeStart, m_SigStateFallSlopeStart(), int64_t a1, char a2)
{
	// Allow StateSpinBoost to climb slippery slopes.
	if (Player::LastState == ESonicState_StateSpinBoost)
		return false;

	return original_StateSpinBoost_StateFallSlopeStart(a1, a2);
}

HOOK(bool, __fastcall, _StateSpinBoost_StateWallActionCheck, m_SigWallActionCheck(), int64_t in_pThis, char a2)
{
	// Allow StateSpinBoost to work on climbable surfaces.
	if (Player::CurrentState == ESonicState_StateSpinBoost)
		return false;

	return original_StateSpinBoost_StateWallActionCheck(in_pThis, a2);
}

// This hook is a hack to obtain app::player::SonicContext, since the singleton from app::player::Sonic doesn't seem to work properly.
HOOK(int64_t, __fastcall, _StateSpinBoost_StatePluginBoostUpdate, m_SigStatePluginBoostUpdate(), int64_t in_pThis, int64_t a2, float in_deltaTime)
{
	// Ignore bad naming convention, used for macro.
	int64_t in_pSonicContext = *(int64_t*)(in_pThis + 0x20);

	auto* kinematics = Player::GetKinematics();

	if (!kinematics)
		return original_StateSpinBoost_StatePluginBoostUpdate(in_pThis, a2, in_deltaTime);

	float dot = (kinematics->Rotation * csl::math::Vector3::UnitY()).dot(csl::math::Vector3::UnitY());

	// Check dot product of current rotation to make sure we're not trying to StateSpinBoost on a right angle.
	if (dot > 0.01f)
	{
		if (Player::CurrentState == ESonicState_StateWallMove && Player::GetKinematics()->Velocity.norm() > 0.0f)
		{
			// Allow StateSpinBoostCharge to work when resting on climbable walls.
			if (IsButtonPressed(EPlayerActionType_PlayerSonicboom))
				Player::SetState(in_pSonicContext, ESonicState_StateSpinBoost);
		}
	}

	return original_StateSpinBoost_StatePluginBoostUpdate(in_pThis, a2, in_deltaTime);
}

HOOK(int64_t, __fastcall, _StateSpinBoost_PlayerKinematicsAirUpdate, READ_CALL(m_SigPlayerKinematicsAirUpdateCaller()), int64_t in_pThis, app::player::GOCPlayerKinematicParams* in_pGOCPlayerKinematicParams)
{
	if (Player::IsGroundedSpecial())
		StateSpinBoost::Flags.reset(EStateSpinBoostFlags_IsDoubleJump);

	return original_StateSpinBoost_PlayerKinematicsAirUpdate(in_pThis, in_pGOCPlayerKinematicParams);
}

void StateSpinBoost::Install()
{
	INSTALL_HOOK(StateSpinBoostStart);
	INSTALL_HOOK(StateSpinBoostUpdate);
	INSTALL_HOOK(_StateSpinBoost_StateFallSlopeStart);
	INSTALL_HOOK(_StateSpinBoost_StateWallActionCheck);
	INSTALL_HOOK(_StateSpinBoost_StatePluginBoostUpdate);
	INSTALL_HOOK(_StateSpinBoost_PlayerKinematicsAirUpdate);
}