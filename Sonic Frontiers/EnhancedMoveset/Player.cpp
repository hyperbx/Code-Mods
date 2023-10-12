extern "C"
{
	DECLARE_ASM_HOOK(CheckHomingTarget);

	// CheckHomingTarget members
	int64_t m_pSigCheckHomingTarget = 0;
	int64_t m_HomingTargetActiveFrames = 0;
	int64_t m_HomingTargetLastActiveFrame = 0;
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	int64_t vftable = in_pThis + 0x88;
	int size = *(int*)(vftable + 0x0C);
	ESonicState currentState = *(ESonicState*)(*(int64_t*)(*(int64_t*)(vftable + 0x20) + 0x08 * size - 0x08) + 0x18);

	Player::CurrentState = currentState;
	Player::DeltaTime = *in_pDeltaTime;

	if (m_HomingTargetLastActiveFrame < m_HomingTargetActiveFrames)
	{
		Player::IsHomingTarget = true;

		m_HomingTargetLastActiveFrame = m_HomingTargetActiveFrames;
	}
	else
	{
		Player::IsHomingTarget = false;

		m_HomingTargetActiveFrames = 0;
		m_HomingTargetLastActiveFrame = 0;
	}

	originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

HOOK(bool, __fastcall, GOCPlayerHsmAirStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	auto result = originalGOCPlayerHsmAirStateUpdate(in_pThis, in_stateId);

	Player::LastState = in_stateId;

	return result;
}

HOOK(bool, __fastcall, GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	// Redirect side step states to StateAvoid during battle if the homing reticle is present.
	// TODO: revisit this for final release.
	// if ((in_stateId == ESonicState_StateLeftStep || in_stateId == ESonicState_StateRightStep) &&
	// 	(BlackboardHelper::IsBattle() && Player::IsHomingTarget))
	// {
	// 	in_stateId = ESonicState_StateAvoid;
	// }

	auto result = originalGOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);

	Player::LastState = in_stateId;

	return result;
}

HOOK(int64_t, __fastcall, EffectForetasteUpdate, m_SigEffectForetasteUpdate(), int64_t in_pThis)
{
	Player::pIsForetasteActive = (bool*)(in_pThis + 0x50);

	if (*Player::pIsForetasteActive)
	{
		Player::ForetasteActiveTime += Player::DeltaTime;
	}
	else
	{
		Player::ForetasteActiveTime = 0.0f;
	}

	Player::Flags.set(EPlayerFlags_IsForetasteActive, *Player::pIsForetasteActive);

	return originalEffectForetasteUpdate(in_pThis);
}

HOOK(int64_t, __fastcall, HitStopUpdate, m_SigHitStopUpdate(), int64_t a1, int a2, float a3, int a4, int a5, float a6, int a7)
{
	if (!Player::IsHitStop)
		a7 = 0;

	return originalHitStopUpdate(a1, a2, a3, a4, a5, a6, a7);
}

HOOK(bool, __fastcall, SonicProcessMessage, m_SigSonicProcessMessage(), int64_t in_pThis, hh::fnd::Message& in_rMessage, int64_t a3)
{
	// MsgDamage
	if (in_rMessage.ID == 0x20CD && !Player::IsDamage)
		return true;

	return originalSonicProcessMessage(in_pThis, in_rMessage, a3);
}

void Player::Install()
{
	// Force allow recovery jump.
	if (m_SigIsRecoveryJumpAvailable() != nullptr)
	{
		READ_THUNK(CanRecoveryJump, (int64_t)m_SigIsRecoveryJumpAvailable());
		WRITE_NOP(CanRecoveryJump + 0x8E, 2);
	}

	m_pSigCheckHomingTarget = (int64_t)m_SigCheckHomingTarget();
	INSTALL_HOOK_ADDRESSED(CheckHomingTarget, m_pSigCheckHomingTarget);

	INSTALL_HOOK(GOCPlayerHsmUpdate);
	INSTALL_HOOK(GOCPlayerHsmAirStateUpdate);
	INSTALL_HOOK(GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(EffectForetasteUpdate);
	INSTALL_HOOK(HitStopUpdate);
	INSTALL_HOOK(SonicProcessMessage);

	StateAirDash::Install();
	StateDropDash::Install();
	StateFallSlope::Install();
	StateFlurryRush::Install();
	StateBulletDash::Install();
	StateGrindDoubleJump::Install();
	StateLightSpeedAttack::Install();
	StatePluginAirTrick::Install();
	StatePluginBoost::Install();
	StatePluginCyloop::Install();
	StateQuickStompDash::Install();
	StateSlideDash::Install();
	StateSpinBoost::Install();
	StateSpinBoostCharge::Install();
	StateSpinMove::Install();
	StateSpringJumpHeadLand::Install();
}