#define FLURRY_DASH_TIME_SCALE 0.03f

void SetFlurryRushBulletTime(bool in_isEnabled)
{
	// TODO: add a sound.
	if (in_isEnabled)
	{
		Player::SetBulletTime(true, FLURRY_DASH_TIME_SCALE, 0.25f, "Battle", 0x180);
	}
	else
	{
		Player::SetBulletTime(false, 1.0f, 0.25f, "Battle", 0x180);
	}
}

void StartFlurryRush()
{
	SetFlurryRushBulletTime(true);

	Player::IsDamage = false;

	RFL_SET_PARAM(common.acceleComboSet.sonic.motionSpeedRatio, 1.25f);
	RFL_SET_PARAM(common.acceleComboSet.sonic.motionSpeedRatioAccele, 1.25f);

	StateFlurryRush::Flags.set(EStateFlurryRushFlags_IsActive);

	StateFlurryRush::FlurryRushTimer = 0.0f;
}

void EndFlurryRush()
{
	SetFlurryRushBulletTime(false);

	Player::IsDamage = true;

	RFL_RESET_PARAM(common.acceleComboSet.sonic.motionSpeedRatio);
	RFL_RESET_PARAM(common.acceleComboSet.sonic.motionSpeedRatioAccele);

	StateFlurryRush::Flags.reset(EStateFlurryRushFlags_IsActive);

	BlackboardHelper::SetPhantomRushGauge(0.0f);

	StateFlurryRush::FlurryRushTimer = 0.0f;
}

HOOK(void, __fastcall, _StateFlurryRush_GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	if (StateFlurryRush::Flags.test(EStateFlurryRushFlags_IsActive))
	{
		if (StateFlurryRush::FlurryRushTimer >= Configuration::FlurryRushDuration ||
			!BlackboardHelper::IsBattle() || BlackboardHelper::IsDamaged() || BlackboardHelper::IsDead())
		{
			EndFlurryRush();
			goto Exit;
		}

		BlackboardHelper::SetPhantomRushGauge(120.0f);

		StateFlurryRush::FlurryRushTimer += (FLURRY_DASH_TIME_SCALE * *in_pDeltaTime) * 10.0f;
	}

Exit:
	original_StateFlurryRush_GOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

HOOK(bool, __fastcall, _StateFlurryRush_StateAvoidProcessMessage, m_SigStateAvoidProcessMessage(), int64_t in_pThis, int64_t in_pSonicContext, hh::fnd::Message& in_rMessage)
{
	// MsgChangeCounterState
	if (in_rMessage.ID == 0x20A7)
	{
		if (*(float*)(in_pThis + 0xB8) >= *(float*)(in_pThis + 0xA0) && (*(uint8_t*)(in_pThis + 0xC0) & 4) == 0)
		{
			if (!Configuration::IsFlurryRush)
				goto Exit;

			StartFlurryRush();
		}
	}

Exit:
	return original_StateFlurryRush_StateAvoidProcessMessage(in_pThis, in_pSonicContext, in_rMessage);
}

HOOK(int64_t, __fastcall, _StateFlurryRush_ActionProcessor, m_SigActionProcessor(), int64_t a1, int8_t in_action, int8_t a3, int64_t a4, char a5)
{
	if (!Configuration::IsFlurryRushNoWildRush)
		goto Exit;

	// Disable Wild Rush when in Flurry Rush.
	if (in_action == 6 && StateFlurryRush::Flags.test(EStateFlurryRushFlags_IsActive))
		return 0;

Exit:
	return original_StateFlurryRush_ActionProcessor(a1, in_action, a3, a4, a5);
}

void StateFlurryRush::Install()
{
	INSTALL_HOOK(_StateFlurryRush_GOCPlayerHsmUpdate);
	INSTALL_HOOK(_StateFlurryRush_StateAvoidProcessMessage);
	INSTALL_HOOK(_StateFlurryRush_ActionProcessor);
}