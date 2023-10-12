bool m_IsAquaballCaptureStart = false;

float m_HomingSleepTimer = 0.0f;

int m_PersistentHomingPositionCount = 0;

csl::math::Vector3 m_LastHomingPosition = *csl::math::Vector3::Zero;

/* I really don't need this vector, but if I ever need to
   block any states in future, it'll be here for convenience. */
std::vector<ESonicState> m_DeniedStates =
{
	ESonicState_StateSpringJump
};

bool IsAllowedState()
{
	for (ESonicState state : m_DeniedStates)
	{
		if (Player::CurrentState == state)
			return false;
	}

	return true;
}

void EndLightSpeedAttack(int64_t in_pSonicContext)
{
	StateLightSpeedAttack::Flags.reset(EStateLightSpeedAttackFlags_IsActive);
	StateLightSpeedAttack::Flags.reset(EStateLightSpeedAttackFlags_IsHoming);
	StateLightSpeedAttack::ChainTime = 0.0f;

	m_IsAquaballCaptureStart = false;
	m_PersistentHomingPositionCount = 0;

	RFL_RESET_PARAM(common.commonPackage.attack.loopKick.damageRate);
	RFL_RESET_PARAM(common.loopKickSet.sonic.loopTime);
	RFL_RESET_PARAM(common.loopKickSet.sonic.failSafeTime);
	RFL_RESET_PARAM(common.loopKickSet.sonic.cameraName.value);

	Player::StopEffect(in_pSonicContext, "LightSpeedAttack");
	Player::StopEffect(in_pSonicContext, "LightSpeedAttackSlash");

	StatePluginCyloop::IsForceCyloopAura = false;
}

HOOK(int64_t, __fastcall, _StateLightSpeedAttack_StateSpinBoostChargeStart, m_SigStateSpinBoostChargeStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	// Show charge particle only when grounded.
	if (Configuration::IsLightSpeedAttack && Configuration::IsLightSpeedAttackChargeVFX && Player::IsGrounded())
		Player::PlayEffect(in_pSonicContext, "LightSpeedAttackCharge", "ef_so_skill_accelerator_aura01");

	return original_StateLightSpeedAttack_StateSpinBoostChargeStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, _StateLightSpeedAttack_StateSpinBoostChargeUpdate, m_SigStateSpinBoostChargeUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	StateLightSpeedAttack::ChargeTime += Player::DeltaTime;

	if (Configuration::IsLightSpeedAttack &&
		StateLightSpeedAttack::ChargeTime > Configuration::LightSpeedAttackChargeDuration &&
		Player::IsGrounded())
	{
		StateLightSpeedAttack::Flags.set(EStateLightSpeedAttackFlags_IsActive);
		StateLightSpeedAttack::ChainTime = 0.0f;

		Player::PlayEffect(in_pSonicContext, "LightSpeedAttack", "ef_so_skill_accelerator_aura01");
		Player::PlaySound("sn_ringmax_impact01");
		Player::PlayVoice(in_pSonicContext, 2);

		Player::SetState(in_pSonicContext, ESonicState_StateRun);

		return true;
	}

	return original_StateLightSpeedAttack_StateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, _StateLightSpeedAttack_StateSpinBoostChargeEnd, m_SigStateSpinBoostChargeEnd(), int64_t in_pThis, int64_t in_pSonicContext, int64_t a3)
{
	StateLightSpeedAttack::ChargeTime = 0.0f;

	Player::StopEffect(in_pSonicContext, "LightSpeedAttackCharge");

	return original_StateLightSpeedAttack_StateSpinBoostChargeEnd(in_pThis, in_pSonicContext, a3);
}

// This hook is a hack to obtain app::player::SonicContext, since the singleton from app::player::Sonic doesn't seem to work properly.
HOOK(int64_t, __fastcall, _StateLightSpeedAttack_StatePluginBoostUpdate, m_SigStatePluginBoostUpdate(), int64_t in_pThis, int64_t a2, float in_deltaTime)
{
	// Ignore bad naming convention, used for macro.
	int64_t in_pSonicContext = *(int64_t*)(in_pThis + 0x20);

	auto kinematics = Player::GetKinematics();

	if (!kinematics)
		goto Exit;

	if (StateLightSpeedAttack::Flags.test(EStateLightSpeedAttackFlags_IsActive))
	{
		StatePluginCyloop::IsForceCyloopAura = true;

		// Cancel using LB/RB.
		if (IsButtonPressed(EPlayerActionType_PlayerLeftStep) || IsButtonPressed(EPlayerActionType_PlayerRightStep))
		{
			EndLightSpeedAttack(in_pSonicContext);
			goto Exit;
		}

		if (IsButtonReleased(EPlayerActionType_PlayerSonicboom) || StateLightSpeedAttack::Flags.test(EStateLightSpeedAttackFlags_IsHoming))
		{
			bool isTimeUp = (Configuration::LightSpeedAttackDuration == 0.0f
				? false
				: StateLightSpeedAttack::ChainTime > Configuration::LightSpeedAttackDuration);

			if (isTimeUp || m_IsAquaballCaptureStart || !IsAllowedState() || BlackboardHelper::IsDamaged() || BlackboardHelper::IsDead())
			{
				EndLightSpeedAttack(in_pSonicContext);
				goto Exit;
			}

			if (Player::IsHomingTarget)
			{
				StateLightSpeedAttack::Flags.set(EStateLightSpeedAttackFlags_IsHoming);

				Player::IsHitStop = false;

				// Don't grant player free Phantom Rush, we won't be using it anyway.
				BlackboardHelper::SetPhantomRushGauge(0.0f);

				if (m_HomingSleepTimer > 0.1f)
				{
					float distance = (m_LastHomingPosition - kinematics->Position).norm();

					/* Check distance between current and last position to
					   prevent repeat homing attacks against the same enemy. */
					if (distance >= 0.0f && distance <= 1.25f)
						m_PersistentHomingPositionCount++;

					// Increase distance threshold to account for Loop Kick.
					if (m_PersistentHomingPositionCount >= 2 && distance <= 5.0f && !BlackboardHelper::IsCyberSpace())
					{
						RFL_SET_PARAM(common.commonPackage.attack.loopKick.damageRate, 0.5f);
						RFL_SET_PARAM(common.loopKickSet.sonic.loopTime, 0.5f);
						RFL_SET_PARAM(common.loopKickSet.sonic.failSafeTime, 0.5f);
						RFL_SET_PARAM(common.loopKickSet.sonic.cameraName.value, "");

						Player::PlayEffect(in_pSonicContext, "LightSpeedAttackSlash", "ef_so_skill_crossslash_hit01");
						Player::SetState(in_pSonicContext, ESonicState_StateLoopKick);
					}
					else
					{
						Player::SetState(in_pSonicContext, ESonicState_StateHomingAttack);
					}

					m_HomingSleepTimer = 0.0f;
					m_LastHomingPosition = kinematics->Position;
				}

				m_HomingSleepTimer += in_deltaTime;
			}
			else
			{
				Player::IsHitStop = true;

				EndLightSpeedAttack(in_pSonicContext);

				if (Configuration::IsLightSpeedAttackLightDashExit)
				{
					// Brake amount for standard homing.
					float homingBrake = (BlackboardHelper::IsCyberSpace() ? 0.0f : 400.0f);

					RFL_SET_CONTEXTUAL_PARAM(lightDash.brake, (m_PersistentHomingPositionCount >= 2 ? 250.0f : homingBrake));

					Player::SetState(in_pSonicContext, ESonicState_StateLightDash);
				}
				else
				{
					if (!Player::IsGrounded())
						Player::SetState(in_pSonicContext, ESonicState_StateHomingFinished);
				}
			}

			StateLightSpeedAttack::ChainTime += in_deltaTime;
		}
	}

Exit:
	return original_StateLightSpeedAttack_StatePluginBoostUpdate(in_pThis, a2, in_deltaTime);
}

HOOK(bool, __fastcall, _StateLightSpeedAttack_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	// Disallow LT actions until Light Speed Attack is no longer active.
	if (StateLightSpeedAttack::Flags.test(EStateLightSpeedAttackFlags_IsActive))
	{
		if (in_stateId == ESonicState_StateSpinBoostCharge ||
			in_stateId == ESonicState_StateSpinBoost ||
			in_stateId == ESonicState_StateSpinMove)
		{
			// Always land from a stomp in this state.
			if (Player::CurrentState == ESonicState_StateStompingDown)
			{
				in_stateId = ESonicState_StateStompingLand;
			}
			else
			{
				return true;
			}
		}
	}

	if (Player::LastState == ESonicState_StateLightDash)
		RFL_RESET_CONTEXTUAL_PARAM(lightDash.brake);

	return original_StateLightSpeedAttack_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

HOOK(bool, __fastcall, _StateLightSpeedAttack_EnemyAquaballStateCaptureStart, m_SigEnemyAquaballStateCaptureStart(), int64_t in_pThis)
{
	m_IsAquaballCaptureStart = true;

	return original_StateLightSpeedAttack_EnemyAquaballStateCaptureStart(in_pThis);
}

void StateLightSpeedAttack::Install()
{
	INSTALL_HOOK(_StateLightSpeedAttack_StateSpinBoostChargeStart);
	INSTALL_HOOK(_StateLightSpeedAttack_StateSpinBoostChargeUpdate);
	INSTALL_HOOK(_StateLightSpeedAttack_StateSpinBoostChargeEnd);
	INSTALL_HOOK(_StateLightSpeedAttack_StatePluginBoostUpdate);
	INSTALL_HOOK(_StateLightSpeedAttack_GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(_StateLightSpeedAttack_EnemyAquaballStateCaptureStart);
}