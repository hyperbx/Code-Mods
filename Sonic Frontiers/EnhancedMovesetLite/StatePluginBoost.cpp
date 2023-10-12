HOOK(int64_t, __fastcall, StatePluginBoostUpdate, m_SigStatePluginBoostUpdate(), int64_t in_pThis, int64_t a2, float in_deltaTime)
{
	StatePluginBoost::pCapacity = (float*)(in_pThis + 0x3C);
	StatePluginBoost::pCapacityMax = (float*)(in_pThis + 0x38);
	StatePluginBoost::pInfiniteGaugeTimer = (float*)(in_pThis + 0x54);

	StatePluginBoost::Flags.set(EStatePluginBoostFlags_IsBoostAvailable, (*(int32_t*)(in_pThis + 0x80) & 8) != 8);
	StatePluginBoost::Flags.set(EStatePluginBoostFlags_IsInfiniteBoostCode, IS_NOP(m_SigInfiniteBoostGaugeCode()));

	return originalStatePluginBoostUpdate(in_pThis, a2, in_deltaTime);
}

HOOK(bool, __fastcall, StatePluginBoostRechargeMode, m_SigStatePluginBoostRechargeMode(), int64_t in_pThis)
{
	if (!StatePluginBoost::IsRecharge)
		return false;

	return originalStatePluginBoostRechargeMode(in_pThis);
}

void StatePluginBoost::Install()
{
	INSTALL_HOOK(StatePluginBoostUpdate);
	INSTALL_HOOK(StatePluginBoostRechargeMode);
}