HOOK(bool, __fastcall, StateFallSlopeUpdate, m_SigStateFallSlopeUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	// Exit into StateSpinBoostCharge if the boost gauge isn't in the red zone.
	if (IsButtonPressed(EPlayerActionType_PlayerSonicboom) && StatePluginBoost::Flags.test(EStatePluginBoostFlags_IsBoostAvailable))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateSpinBoostCharge);
		return true;
	}

	return originalStateFallSlopeUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

void StateFallSlope::Install()
{
	INSTALL_HOOK(StateFallSlopeUpdate);
}