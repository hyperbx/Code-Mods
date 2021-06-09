int ScoreListener::score = 0;

void ScoreListener::Reset()
{
	StatisticsListener::stats.totalRingCount = 0;
	StatisticsListener::stats.totalVelocity = 0;
	StatisticsListener::stats.ringCount = 0;
	StatisticsListener::stats.minutes = 0;
	StatisticsListener::stats.seconds = 0;
	score = 0;
}

void ScoreListener::AddClamp(unsigned int scoreToReward)
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
		{
			scoreToReward = Tables::scoreTable.Physics;

			// Increase total physics count.
			StatisticsListener::stats.totalPhysics++;

			break;
		}

		case PointMarker:
		{
			scoreToReward = Tables::scoreTable.PointMarker;

			// Increase total velocity for the speed bonus.
			StatisticsListener::stats.totalVelocity += PlayerListener::GetVelocity() * 10;

#if _DEBUG
			printf("[Score Generations] Total Velocity = %d\n", StatisticsListener::stats.totalVelocity);
#endif

			// Increase total checkpoint count.
			StatisticsListener::stats.totalPointMarkers++;

			break;
		}

		case RedRing:
		{
			scoreToReward = Tables::scoreTable.RedRing;

			// Increase total red ring count.
			StatisticsListener::stats.totalRedRings++;

			break;
		}

		case RainbowRing:
		{
			scoreToReward = Tables::scoreTable.RainbowRing;

			// Increase total rainbow ring count.
			StatisticsListener::stats.totalRainbowRings++;

			break;
		}

		case ItemBox:
		{
			scoreToReward = Tables::scoreTable.ItemBox;

			// Increase total item box count.
			StatisticsListener::stats.totalItemBoxes++;

			break;
		}

		case SuperRing:
		{
			scoreToReward = Tables::scoreTable.SuperRing;

			// Increase total super ring count.
			StatisticsListener::stats.totalSuperRings++;

			break;
		}

		case TrickFinish:
			scoreToReward = Tables::scoreTable.TrickFinish;
			break;

		case Trick:
		{
			scoreToReward = Tables::scoreTable.Trick;

			// Increase total trick count.
			StatisticsListener::stats.totalTricks++;

			break;
		}

		case Life:
			scoreToReward = Tables::scoreTable.Life;
			break;

		case DashRing:
		{
			scoreToReward = Tables::scoreTable.DashRing;

			// Increase total dash ring count.
			StatisticsListener::stats.totalDashRings++;

			break;
		}

		case QuickStep:
		{
			scoreToReward = Tables::scoreTable.QuickStep;

			// Increase total quick step count.
			StatisticsListener::stats.totalQuickSteps++;

			break;
		}

		case Drift:
		{
			scoreToReward = Tables::scoreTable.Drift;

			// Increase total drift count.
			StatisticsListener::stats.totalDrifts++;

			break;
		}

		case Balloon:
		{
			scoreToReward = Tables::scoreTable.Balloon;

			// Increase total balloon count.
			StatisticsListener::stats.totalBalloons++;

			break;
		}

		case Super:
			scoreToReward = Tables::scoreTable.Super;
			break;

		case BoardTrick:
		{
			scoreToReward = Tables::scoreTable.BoardTrick;

			// Increase total trick count.
			StatisticsListener::stats.totalTricks++;

			break;
		}
	}

	// Rewards the score and clamps it.
	AddClamp(scoreToReward);

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}