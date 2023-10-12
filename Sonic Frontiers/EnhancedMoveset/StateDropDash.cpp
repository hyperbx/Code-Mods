HOOK(int64_t, __fastcall, StateDropDashStart, m_SigStateDropDashStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	StateDropDash::Flags.set(EStateDropDashFlags_IsActive);

	if (StateDropDash::IsNoCameraDelay())
	{
		if (m_SigDropDashCameraDelay() != nullptr)
		{
			// Preserve and disable Drop Dash camera delay.
			PRESERVE_MEMORY((int64_t)m_SigDropDashCameraDelay(), 1);
			WRITE_MEMORY(m_SigDropDashCameraDelay(), uint8_t, 0xEB);
		}
	}

	return originalStateDropDashStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateDropDashUpdate, m_SigStateDropDashUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = Player::IsGrounded();

	// Store if we've been grounded at least once for later conditions.
	if (!StateDropDash::Flags.test(EStateDropDashFlags_IsGroundedOnce))
	{
		StateDropDash::Flags.set(EStateDropDashFlags_IsGroundedOnce, isGrounded);
	}

	// Exit into StateSpinBoostCharge.
	if (IsButtonPressed(EPlayerActionType_PlayerSonicboom))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateSpinBoostCharge);
		return true;
	}

	// Exit into StateSpringJumpHeadLand or StateBumpJump.
	if (IsButtonPressed(EPlayerActionType_PlayerStomping))
	{
		if (isGrounded)
		{
			Player::SetState(in_pSonicContext, ESonicState_StateSpringJumpHeadLand);
			return true;
		}
		else if (Player::IsStateAvailableInView(Configuration::DropDashAirTrickCancel))
		{
			Player::SetState(in_pSonicContext, ESonicState_StateBumpJump);
			return true;
		}
	}

	if (isGrounded)
	{
		// Exit into StateRun with boost.
		if (IsButtonPressed(EPlayerActionType_PlayerBoost))
		{
			BlackboardHelper::GetBlackboardStatus()->StateFlags |= BlackboardHelper::EStateFlags::EStateFlags_IsBoost;
			Player::SetState(in_pSonicContext, ESonicState_StateRun);
			return true;
		}
	}
	else
	{
		// Exit into StateBumpJump if we become ungrounded after having been grounded at least once.
		if (StateDropDash::Flags.test(EStateDropDashFlags_IsGroundedOnce) && StateDropDash::IsUngroundedExit())
		{
			Player::SetState(in_pSonicContext, ESonicState_StateBumpJump);
			return true;
		}

		// Exit into StateDoubleJump.
		if (IsButtonPressed(EPlayerActionType_PlayerJump))
		{
			Player::SetState(in_pSonicContext, ESonicState_StateDoubleJump);
			return true;
		}

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

	// Exit into StateQuickStep.
	if (IsButtonPressed(EPlayerActionType_PlayerLeftStep) || IsButtonPressed(EPlayerActionType_PlayerRightStep))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateQuickStep);
		return true;
	}

	return originalStateDropDashUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, StateDropDashEnd, m_SigStateDropDashEnd(), int64_t in_pThis, int64_t in_pSonicContext)
{
	StateDropDash::Flags.reset();

	// Restore Drop Dash camera delay.
	RESTORE_MEMORY((int64_t)m_SigDropDashCameraDelay());

	return originalStateDropDashEnd(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, PostureDropDashUpdate, m_SigPostureDropDashUpdate(), int64_t in_pThis, double in_deltaTime)
{
	if (Configuration::IsDropDashSideViewRollFix)
	{
		PRESERVE_MEMORY((int64_t)m_SigFixDropDashSideView(), 1);

		if (BlackboardHelper::IsSideView())
		{
			WRITE_MEMORY(m_SigFixDropDashSideView(), uint8_t, 0xEB);
		}
		else
		{
			RESTORE_MEMORY((int64_t)m_SigFixDropDashSideView());
		}
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigFixDropDashSideView());
	}

	return originalPostureDropDashUpdate(in_pThis, in_deltaTime);
}

HOOK(bool, __fastcall, _StateDropDash_StateDoubleJumpUpdate, m_SigStateDoubleJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	StateDropDash::Flags.set(EStateDropDashFlags_IsCharging, *(float*)(in_pThis + 0xB4) > 0.0f);

	return original_StateDropDash_StateDoubleJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(int64_t, __fastcall, _StateDropDash_StateDoubleJumpEnd, m_SigStateDoubleJumpEnd(), int64_t in_pThis, int64_t in_pSonicContext, int a3)
{
	StateDropDash::Flags.reset(EStateDropDashFlags_IsCharging);

	return original_StateDropDash_StateDoubleJumpEnd(in_pThis, in_pSonicContext, a3);
}

HOOK(bool, __fastcall, _StateDropDash_StateRecoveryJumpUpdate, m_SigStateRecoveryJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	StateDropDash::Flags.set(EStateDropDashFlags_IsCharging, *(bool*)(in_pThis + 0xC4));

	return original_StateDropDash_StateRecoveryJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(int64_t, __fastcall, _StateDropDash_StateRecoveryJumpEnd, m_SigStateRecoveryJumpEnd(), int64_t in_pThis, int64_t in_pSonicContext, int a3)
{
	StateDropDash::Flags.reset(EStateDropDashFlags_IsCharging);

	return original_StateDropDash_StateRecoveryJumpEnd(in_pThis, in_pSonicContext, a3);
}

HOOK(bool, __fastcall, _StateDropDash_ObjFanProcessMessage, m_SigObjFanProcessMessage(), int64_t in_pThis, int64_t a2)
{
	// Disable fans if we're rolling.
	if (Configuration::IsDropDashNoFans && StateDropDash::Flags.test(EStateDropDashFlags_IsActive))
		return 1;

	return original_StateDropDash_ObjFanProcessMessage(in_pThis, a2);
}

void StateDropDash::Install()
{
	INSTALL_HOOK(StateDropDashStart);
	INSTALL_HOOK(StateDropDashUpdate);
	INSTALL_HOOK(StateDropDashEnd);
	INSTALL_HOOK(PostureDropDashUpdate);
	INSTALL_HOOK(_StateDropDash_StateDoubleJumpUpdate);
	INSTALL_HOOK(_StateDropDash_StateDoubleJumpEnd);
	INSTALL_HOOK(_StateDropDash_StateRecoveryJumpUpdate);
	INSTALL_HOOK(_StateDropDash_StateRecoveryJumpEnd);
	INSTALL_HOOK(_StateDropDash_ObjFanProcessMessage);
}