HOOK(int64_t, __fastcall, StatePluginAirTrickUpdate, m_SigStatePluginAirTrickUpdate(), int64_t in_pThis)
{
	int trickDirection = *(int*)(in_pThis + 0x34);

	float minReward = Configuration::AirTrickMinBoostReward;
	float maxReward = Configuration::AirTrickMaxBoostReward;
	float fatigueTime = Configuration::AirTrickFatigueTime;

	// Begins fatigue once at least one trick has been performed.
	StatePluginAirTrick::Flags.set(EStatePluginAirTrickFlags_IsFatigueStart);

	if (minReward < maxReward)
	{
		StatePluginAirTrick::TrickReward = std::clamp
		(
			// Check last trick direction and penalise the player for reusing the same trick.
			StatePluginAirTrick::TrickReward + (trickDirection == StatePluginAirTrick::LastTrickDirection
				? -Configuration::AirTrickSamePenalty
				: minReward),

			minReward,

			fatigueTime == 0.0f
				? maxReward // Always reward maximum amount if the fatigue time is zero in the configuration.
				: std::clamp(RANGE(StatePluginAirTrick::TrickFatigueTimer, 0.0f, fatigueTime, maxReward, minReward), minReward, maxReward)
		);
	}
	else
	{
		StatePluginAirTrick::TrickReward = 0.0f;
	}

	StatePluginAirTrick::LastTrickDirection = trickDirection;

	if (Configuration::IsAirTricksEnhanced)
	{
		*StatePluginBoost::pCapacity = std::clamp
		(
			*StatePluginBoost::pCapacity + StatePluginAirTrick::TrickReward,
			0.0f,
			*StatePluginBoost::pCapacityMax
		);
	}

	return originalStatePluginAirTrickUpdate(in_pThis);
}

HOOK(int64_t, __fastcall, _StatePluginAirTrick_PlayerKinematicsAirUpdate, READ_CALL(m_SigPlayerKinematicsAirUpdateCaller()), int64_t in_pThis, app::player::GOCPlayerKinematicParams* in_pGOCPlayerKinematicParams)
{
	auto forward = in_pGOCPlayerKinematicParams->Rotation.GetForward();

	if (Player::IsGroundedSpecial())
	{
		// Reset trick fatigue.
		StatePluginAirTrick::Flags.reset(EStatePluginAirTrickFlags_IsFatigueStart);
		StatePluginAirTrick::TrickFatigueTimer = 0.0f;
	}

	if (StatePluginAirTrick::Flags.test(EStatePluginAirTrickFlags_IsFatigueStart))
	{
		// Increase trick fatigue timer.
		StatePluginAirTrick::TrickFatigueTimer += Player::DeltaTime;
	}

	return original_StatePluginAirTrick_PlayerKinematicsAirUpdate(in_pThis, in_pGOCPlayerKinematicParams);
}

void StatePluginAirTrick::Install()
{
	INSTALL_HOOK(StatePluginAirTrickUpdate);
	INSTALL_HOOK(_StatePluginAirTrick_PlayerKinematicsAirUpdate);
}