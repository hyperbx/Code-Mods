HOOK(bool, __fastcall, _StateSlideDash_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	if (in_stateId == ESonicState_StateSliding && Configuration::IsSlideDash)
	{
		in_stateId = ESonicState_StateDropDash;

		StateSlideDash::Flags.set(EStateSlideDashFlags_IsActive);
	}

	return original_StateSlideDash_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

HOOK(int64_t, __fastcall, _StateSlideDash_StateDropDashEnd, m_SigStateDropDashEnd(), int64_t in_pThis, int64_t in_pSonicContext)
{
	StateSlideDash::Flags.reset(EStateSlideDashFlags_IsActive);

	return original_StateSlideDash_StateDropDashEnd(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, _StateSlideDash_StateSquatUpdate, m_SigStateSquatUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	if (Configuration::IsSlideDash)
	{
		PRESERVE_MEMORY((int64_t)m_SigPreventSquatToSlide(), 1);
		WRITE_MEMORY(m_SigPreventSquatToSlide(), uint8_t, 0xEB);
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigPreventSquatToSlide());
	}

	return original_StateSlideDash_StateSquatUpdate(in_pThis, in_pSonicContext);
}

void StateSlideDash::Install()
{
	INSTALL_HOOK(_StateSlideDash_GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(_StateSlideDash_StateDropDashEnd);
	INSTALL_HOOK(_StateSlideDash_StateSquatUpdate);
}