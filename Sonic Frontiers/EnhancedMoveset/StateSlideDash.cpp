HOOK(bool, __fastcall, _StateSlideDash_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	if (in_stateId == ESonicState_StateSliding)
	{
		auto actionType = BlackboardHelper::IsSideView()
			? Configuration::SlideDashActionTypeSV
			: Configuration::SlideDashActionType;

		switch (actionType)
		{
			case ESlideDashActionType_DropDash:
				in_stateId = ESonicState_StateDropDash;
				break;

			case ESlideDashActionType_SpinMove:
				in_stateId = ESonicState_StateSpinMove;
				break;
		}

		if (actionType != ESlideDashActionType_Disabled)
		{
			StateSlideDash::Flags.set(EStateSlideDashFlags_IsActive);
		}
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
	bool isSideView = BlackboardHelper::IsSideView();

	if ((Configuration::SlideDashActionTypeSV == ESlideDashActionType_DropDash && isSideView) ||
		(Configuration::SlideDashActionType == ESlideDashActionType_DropDash) && !isSideView)
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