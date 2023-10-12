HOOK(bool, __fastcall, _StateAirDash_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	if (!Configuration::IsAirDash || !Player::IsStateAvailableInWorld(Configuration::AirDashWorldType))
		return original_StateAirDash_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);

	if (in_stateId == ESonicState_StateAirBoost && StateDropDash::Flags.test(EStateDropDashFlags_IsCharging))
	{
		StateAirDash::Flags.set(EStateAirDashFlags_IsActive);
		StateAirDash::Flags.set(EStateAirDashFlags_IsReleased);

		in_stateId = ESonicState_StateDropDash;
	}

	return original_StateAirDash_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

HOOK(int64_t, __fastcall, _StateAirDash_PlayerKinematicsAirUpdate, READ_CALL(m_SigPlayerKinematicsAirUpdateCaller()), int64_t in_pThis, app::player::GOCPlayerKinematicParams* in_pGOCPlayerKinematicParams)
{
	auto forward = in_pGOCPlayerKinematicParams->Rotation.GetForward();

	if (Player::IsGroundedSpecial())
		StateAirDash::Flags.reset(EStateAirDashFlags_IsReleasedFromRecoveryJump);

	if (StateAirDash::Flags.test(EStateAirDashFlags_IsReleased))
	{
		StateAirDash::Flags.reset(EStateAirDashFlags_IsReleased);

		in_pGOCPlayerKinematicParams->Velocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::AirDashInitialVelocitySV
			: Configuration::AirDashInitialVelocity);
	}

	return original_StateAirDash_PlayerKinematicsAirUpdate(in_pThis, in_pGOCPlayerKinematicParams);
}

HOOK(bool, __fastcall, _StateAirDash_StateDropDashUpdate, m_SigStateDropDashUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	if (!StateAirDash::Flags.test(EStateAirDashFlags_IsActive))
		return original_StateAirDash_StateDropDashUpdate(in_pThis, in_pSonicContext);

	switch (GET_UNCURL_TYPE_BY_VIEW(Configuration::AirDashUncurlType))
	{
		// Exit into StateRecovery immediately.
		case EUncurlType_Immediate:
		{
			Player::SetState(in_pSonicContext, ESonicState_StateBumpJump);
			return true;
		}

		// Exit into StateRun when grounded.
		case EUncurlType_Grounded:
		{
			if (!Player::IsGrounded())
				break;

			Player::SetState(in_pSonicContext, ESonicState_StateRun);

			return true;
		}
	}

	return original_StateAirDash_StateDropDashUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, _StateAirDash_StateDropDashEnd, m_SigStateDropDashEnd(), int64_t in_pThis, int64_t in_pSonicContext)
{
	StateAirDash::Flags.reset(EStateAirDashFlags_IsActive);

	return original_StateAirDash_StateDropDashEnd(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, _StateAirDash_StateRecoveryJumpUpdate, m_SigStateRecoveryJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	if (IsButtonPressed(EPlayerActionType_PlayerBoost))
	{
		// Always allow StateRecoveryJump to exit to StateAirBoost.
		if (!StateAirDash::Flags.test(EStateAirDashFlags_IsReleasedFromRecoveryJump) &&
			StateDropDash::Flags.test(EStateDropDashFlags_IsCharging))
		{
			StateAirDash::Flags.set(EStateAirDashFlags_IsReleasedFromRecoveryJump);

			Player::SetState(in_pSonicContext, ESonicState_StateAirBoost);
		}
	}

	return original_StateAirDash_StateRecoveryJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

void StateAirDash::Install()
{
	INSTALL_HOOK(_StateAirDash_GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(_StateAirDash_PlayerKinematicsAirUpdate);
	INSTALL_HOOK(_StateAirDash_StateDropDashUpdate);
	INSTALL_HOOK(_StateAirDash_StateDropDashEnd);
	INSTALL_HOOK(_StateAirDash_StateRecoveryJumpUpdate);
}