HOOK(bool, __fastcall, _StateQuickStompDash_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	if (in_stateId == ESonicState_StateStompingDown)
	{
		if (!Configuration::IsQuickStompDash)
			goto Exit;

		if (!Player::IsStateAvailableInWorld(Configuration::QuickStompDashWorldType))
			goto Exit;

		if (Configuration::IsQuickStompDashRequireAirBoost && !BlackboardHelper::IsAirBoosting())
			goto Exit;

		if (Player::LastState == ESonicState_StateAirBoost && StateQuickStompDash::Flags.test(EStateQuickStompDashFlags_IsActive))
			goto Exit;

		if (Player::LastState == ESonicState_StateBumpJump || Player::LastState == ESonicState_StateRecoveryJump)
			goto Exit;

		auto* pGOCPlayerKinematicParams = Player::GetKinematics();

		if (pGOCPlayerKinematicParams == nullptr)
			goto Exit;

		float horzVelocityMag = pGOCPlayerKinematicParams->Velocity.head<2>().norm();

		bool isVelocityAboveThreshold = BlackboardHelper::IsSideView()
			? horzVelocityMag >= Configuration::QuickStompDashVelocityThresholdSV
			: horzVelocityMag >= Configuration::QuickStompDashVelocityThreshold;

		if (Configuration::IsQuickStompDashRequireAirBoost || isVelocityAboveThreshold)
		{
			StateQuickStompDash::Flags.set(EStateQuickStompDashFlags_IsActive);

			in_stateId = ESonicState_StateDropDash;
		}
	}

Exit:
	return original_StateQuickStompDash_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

HOOK(bool, __fastcall, _StateQuickStompDash_StateDropDashUpdate, m_SigStateDropDashUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	if (!StateQuickStompDash::Flags.test(EStateQuickStompDashFlags_IsActive))
		return original_StateQuickStompDash_StateDropDashUpdate(in_pThis, in_pSonicContext);

	switch (GET_UNCURL_TYPE_BY_VIEW(Configuration::QuickStompDashUncurlType))
	{
		// Exit into StateRecovery immediately.
		case EUncurlType_Immediate:
		{
			StateQuickStompDash::Flags.reset(EStateQuickStompDashFlags_IsActive);

			Player::SetState(in_pSonicContext, ESonicState_StateBumpJump);

			return true;
		}

		// Exit into StateRun when grounded.
		case EUncurlType_Grounded:
		{
			if (!Player::IsGrounded())
				break;

			StateQuickStompDash::Flags.reset(EStateQuickStompDashFlags_IsActive);

			Player::SetState(in_pSonicContext, ESonicState_StateRun);

			return true;
		}
	}

	return original_StateQuickStompDash_StateDropDashUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, _StateQuickStompDash_StateDropDashEnd, m_SigStateDropDashEnd(), int64_t in_pThis, int64_t in_pSonicContext)
{
	StateQuickStompDash::Flags.set(EStateQuickStompDashFlags_IsDropDashEnd);

	return original_StateQuickStompDash_StateDropDashEnd(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, _StateQuickStompDash_PlayerKinematicsAirUpdate, READ_CALL(m_SigPlayerKinematicsAirUpdateCaller()), int64_t in_pThis, app::player::GOCPlayerKinematicParams* in_pGOCPlayerKinematicParams)
{
	if (Player::IsGroundedSpecial() && StateQuickStompDash::Flags.test(EStateQuickStompDashFlags_IsDropDashEnd))
	{
		StateQuickStompDash::Flags.reset(EStateQuickStompDashFlags_IsActive);
		StateQuickStompDash::Flags.reset(EStateQuickStompDashFlags_IsDropDashEnd);
	}

	return original_StateQuickStompDash_PlayerKinematicsAirUpdate(in_pThis, in_pGOCPlayerKinematicParams);
}

void StateQuickStompDash::Install()
{
	INSTALL_HOOK(_StateQuickStompDash_GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(_StateQuickStompDash_StateDropDashUpdate);
	INSTALL_HOOK(_StateQuickStompDash_StateDropDashEnd);
	INSTALL_HOOK(_StateQuickStompDash_PlayerKinematicsAirUpdate);
}