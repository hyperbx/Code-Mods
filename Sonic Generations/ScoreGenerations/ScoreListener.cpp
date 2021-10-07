int ScoreListener::score = 0;
int ScoreListener::lastCheckpointScore = 0;

void ScoreListener::Reset()
{
	score = Configuration::restoreLastCheckpointScore && PlayerListener::isDead ? lastCheckpointScore : 0;
	StatisticsListener::stats.Reset();
}

void ScoreListener::AddClamp(int scoreToReward)
{
	// Stop rewarding score if the player is over the maximum time.
	if (Configuration::scoreTimeout && StatisticsListener::GetElapsedTime() > Tables::rankTables[StateHooks::stageID].maxSeconds)
	{
#if _DEBUG
		printf("[Score Generations] Time bonus expired! No longer rewarding score...\n");
#endif

		return;
	}

	// Clamp the maximum score.
	if ((score + scoreToReward) <= Configuration::scoreLimit)
		score += scoreToReward;
	else
		score = Configuration::scoreLimit;
}

void __fastcall ScoreListener::Reward(ScoreType type)
{
	int scoreToReward = 0;

	switch (type)
	{
		case Ring:
			scoreToReward = Tables::scoreTable.Ring;
			break;

		case Enemy:
		{
			scoreToReward = Tables::scoreTable.Enemy;

			// Calculate homing chain bonus.
			scoreToReward += MultiplierListener::AddHomingChainBonus();

			// Calculate slam bonus.
			scoreToReward += MultiplierListener::AddSlamBonus();

			// Increase total enemy count.
			StatisticsListener::stats.totalEnemies++;

			break;
		}

		case Physics:
			scoreToReward = Tables::scoreTable.Physics;
			StatisticsListener::stats.totalPhysics++;
			break;

		case PointMarker:
		{
			scoreToReward = Tables::scoreTable.PointMarker;

			// Increase total velocity for the speed bonus.
			if (Configuration::rewardSpeedBonus)
			{
				StatisticsListener::stats.totalVelocity += PlayerListener::GetVelocity() * Tables::multiplierTable.speedBonusMultiplier;

#if _DEBUG
				printf("[Score Generations] Total Velocity = %d\n", StatisticsListener::stats.totalVelocity);
#endif
			}

			// Store the current score so we can restore it later upon death if requested.
			if (Configuration::restoreLastCheckpointScore)
				lastCheckpointScore = score;

			// Increase total checkpoint count.
			StatisticsListener::stats.totalPointMarkers++;

			break;
		}

		case RedRing:
			scoreToReward = Tables::scoreTable.RedRing;
			StatisticsListener::stats.totalRedRings++;
			break;

		case RainbowRing:
			scoreToReward = Tables::scoreTable.RainbowRing;
			StatisticsListener::stats.totalRainbowRings++;
			break;

		case ItemBox:
			scoreToReward = Tables::scoreTable.ItemBox;
			StatisticsListener::stats.totalItemBoxes++;
			break;

		case SuperRing:
			scoreToReward = Tables::scoreTable.SuperRing;
			StatisticsListener::stats.totalSuperRings++;
			break;

		case Trick:
		case TrickFinish:
		case BoardTrick:
			scoreToReward = type == Trick ? Tables::scoreTable.Trick : type == BoardTrick ? Tables::scoreTable.BoardTrick : Tables::scoreTable.TrickFinish;
			StatisticsListener::stats.totalTricks++;
			break;

		case Life:
			scoreToReward = Tables::scoreTable.Life;
			break;

		case DashRing:
			scoreToReward = Tables::scoreTable.DashRing;
			StatisticsListener::stats.totalDashRings++;
			break;

		case QuickStep:
			scoreToReward = Tables::scoreTable.QuickStep;
			StatisticsListener::stats.totalQuickSteps++;
			break;

		case Drift:
			scoreToReward = Tables::scoreTable.Drift;
			StatisticsListener::stats.totalDrifts++;
			break;

		case Balloon:
			scoreToReward = Tables::scoreTable.Balloon;
			StatisticsListener::stats.totalBalloons++;
			break;

		case Super:
			scoreToReward = Tables::scoreTable.Super;
			break;
	}

	// Rewards the score and clamps it.
	AddClamp(scoreToReward);

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}