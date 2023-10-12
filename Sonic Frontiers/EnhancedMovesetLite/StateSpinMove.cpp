HOOK(bool, __fastcall, StateSpinMoveUpdate, m_SigStateSpinMoveUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = Player::IsGrounded();
	bool isSideView = BlackboardHelper::IsSideView();

	auto* kinematics = Player::GetKinematics();

	if (!kinematics)
		return originalStateSpinMoveUpdate(in_pThis, in_pSonicContext);

	float velocityMag = kinematics->Velocity.norm();
	float horzVelocityMag = kinematics->Velocity.head<2>().norm();

	ESonicState groundedState = (horzVelocityMag >= 15.0f
		? ESonicState_StateSpringJumpHeadLand
		: ESonicState_StateRun);

	// Exit into groundedState or StateBumpJump if LT was buffered and released.
	if (IsButtonReleased(EPlayerActionType_PlayerSonicboom))
	{
		Player::SetState(in_pSonicContext, isGrounded ? groundedState : ESonicState_StateBumpJump);
		return true;
	}

	// Exit into StateSpinBoostCharge.
	if (IsButtonPressed(EPlayerActionType_PlayerSonicboom))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateSpinBoostCharge);
		return true;
	}

	// Set speed of rolling animation to match Sonic's speed.
	Player::SetAnimationParameter("SPEED", min(max(velocityMag / 15.0f, 0.0f), 1.0f));

	if (isGrounded)
	{
		// Expire state when reaching minimum rotation and velocity.
		{
			float dot = (kinematics->Rotation * csl::math::Vector3::UnitY()).dot(csl::math::Vector3::UnitY());

			if (dot < 0.05f && velocityMag < std::lerp(9.0f, 15.0f, -std::clamp(dot, -1.0f, 0.0f)))
			{
				Player::SetState(in_pSonicContext, ESonicState_StateFall);
				return true;
			}
		}

		// Exit StateSpinMove into StateRun whilst RT is held.
		if (IsButtonPressed(EPlayerActionType_PlayerBoost))
		{
			BlackboardHelper::GetBlackboardStatus()->StateFlags |= BlackboardHelper::EStateFlags::EStateFlags_IsBoost;
			Player::SetState(in_pSonicContext, ESonicState_StateRun);
			return true;
		}
	}
	else
	{
		// Exit into StateStompingDown.
		if (IsButtonPressed(EPlayerActionType_PlayerStomping))
		{
			Player::SetState(in_pSonicContext, ESonicState_StateStompingDown);
			return true;
		}

		// Exit into StateAirBoost.
		if (IsButtonPressed(EPlayerActionType_PlayerBoost))
		{
			Player::SetState(in_pSonicContext, ESonicState_StateAirBoost);
			return true;
		}
	}

	// Exit into groundedState or StateBumpJump.
	if (IsButtonPressed(EPlayerActionType_PlayerStomping))
	{
		Player::SetState(in_pSonicContext, isGrounded ? groundedState : ESonicState_StateBumpJump);
		return true;
	}

	return originalStateSpinMoveUpdate(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, _StateSpinMove_SendMoveImpulse, m_SigSendMoveImpulse(), int64_t in_pSonicContext, int64_t in_pMessage)
{
	bool isDashPanel = *(char*)(in_pMessage + 0x98) & 1;

	// Exit into StateSpinBoost when hitting a dash panel.
	if (isDashPanel && Player::LastState == ESonicState_StateSpinMove)
		Player::SetState(in_pSonicContext, ESonicState_StateSpinBoost);

	return original_StateSpinMove_SendMoveImpulse(in_pSonicContext, in_pMessage);
}

HOOK(bool, __fastcall, _StateSpinMove_StateFallSlopeStart, m_SigStateFallSlopeStart(), int64_t in_pThis, char a2)
{
	// Allow StateSpinMove to climb slippery slopes.
	if (Player::LastState == ESonicState_StateSpinMove)
		return false;

	return original_StateSpinMove_StateFallSlopeStart(in_pThis, a2);
}

HOOK(bool, __fastcall, _StateSpinMove_StateWallActionCheck, m_SigWallActionCheck(), int64_t in_pThis, char a2)
{
	// Allow StateSpinMove to work on climbable surfaces.
	if (Player::CurrentState == ESonicState_StateSpinMove)
		return false;

	return original_StateSpinMove_StateWallActionCheck(in_pThis, a2);
}

void StateSpinMove::Install()
{
	// Stop StateSpinMove exiting into StateSpinBoostCharge.
	WRITE_NOP(m_SigDisableSpinChargeFromSpinMove(), 13);

	// Stop StateSpinMove exiting if not holding LT.
	WRITE_MEMORY(m_SigDisableSpinMoveExitInput(), uint8_t, 0xEB, 0x5C);

	// Stop StateSpinMove exiting to StateSpinBoost if holding RT.
	WRITE_MEMORY(m_SigDisableSpinMoveSpinBoostExit(), uint8_t, 0xEB);

	// Fix slope acceleration for StateSpinMove.
	WRITE_JUMP((int64_t)m_SigPostureSpinBoostSlopeAccelFix(), ReadJump((int64_t)m_SigPostureSpinBoostSlopeAccelFix()));

	INSTALL_HOOK(StateSpinMoveUpdate);
	INSTALL_HOOK(_StateSpinMove_SendMoveImpulse);
	INSTALL_HOOK(_StateSpinMove_StateFallSlopeStart);
	INSTALL_HOOK(_StateSpinMove_StateWallActionCheck);
}