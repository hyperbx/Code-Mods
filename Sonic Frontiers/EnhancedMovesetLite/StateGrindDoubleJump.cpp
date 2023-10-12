HOOK(bool, __fastcall, _StateGrindDoubleJump_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	// Redirect StateGrindDoubleJump to StateDoubleJump with its posture.
	if (in_stateId == ESonicState_StateGrindDoubleJump)
	{
		PRESERVE_MEMORY((int64_t)m_SigForceGrindJumpPosture(), 2);
		WRITE_NOP(m_SigForceGrindJumpPosture(), 2);

		in_stateId = ESonicState_StateDoubleJump;
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigForceGrindJumpPosture());
	}

	return original_StateGrindDoubleJump_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

void StateGrindDoubleJump::Install()
{
	INSTALL_HOOK(_StateGrindDoubleJump_GOCPlayerHsmGroundStateUpdate);
}