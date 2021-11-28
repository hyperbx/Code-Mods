int ScoreListener::score = 0;
int ScoreListener::totalScore = 0;
int ScoreListener::lastCheckpointScore = 0;

void ScoreListener::Reset()
{
	totalScore = score = Configuration::restoreLastCheckpointScore && PlayerListener::isDead ? lastCheckpointScore : 0;
	StatisticsListener::totals.Reset();
}

void ScoreListener::AddClamp(int& score, int scoreToReward, bool timeout)
{
	if (timeout)
	{
		// Stop rewarding score if the player is over the maximum time.
		if (Configuration::scoreTimeout && StatisticsListener::GetElapsedTime() > TableListener::rankTables[StateHooks::stageID].maxSeconds)
		{
#if _DEBUG
			printf("[Score Generations] Time bonus expired! No longer rewarding score...\n");
#endif

			return;
		}
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
			scoreToReward = TableListener::scoreTable.Ring;
			break;

		case Enemy:
		{
			scoreToReward = TableListener::scoreTable.Enemy;

			// Calculate homing chain bonus.
			scoreToReward += MultiplierListener::AddHomingChainBonus();

			// Calculate slam bonus.
			scoreToReward += MultiplierListener::AddSlamBonus();

			// Increase total enemy count.
			StatisticsListener::totals.totalEnemies++;

			break;
		}

		case Physics:
			scoreToReward = TableListener::scoreTable.Physics;
			StatisticsListener::totals.totalPhysics++;
			break;

		case PointMarker:
		{
			scoreToReward = TableListener::scoreTable.PointMarker;

			// Increase total velocity for the speed bonus.
			if (Configuration::rewardSpeedBonus)
			{
				StatisticsListener::totals.totalVelocity += PlayerListener::GetVelocity() * TableListener::multiplierTable.speedBonusMultiplier;

#if _DEBUG
				printf("[Score Generations] Total Velocity = %d\n", StatisticsListener::totals.totalVelocity);
#endif
			}

			// Store the current score so we can restore it later upon death if requested.
			if (Configuration::restoreLastCheckpointScore)
				lastCheckpointScore = score;

			// Increase total checkpoint count.
			StatisticsListener::totals.totalPointMarkers++;

			break;
		}

		case RedRing:
			scoreToReward = TableListener::scoreTable.RedRing;
			StatisticsListener::totals.totalRedRings++;
			break;

		case RainbowRing:
			scoreToReward = TableListener::scoreTable.RainbowRing;
			StatisticsListener::totals.totalRainbowRings++;
			break;

		case ItemBox:
			scoreToReward = TableListener::scoreTable.ItemBox;
			StatisticsListener::totals.totalItemBoxes++;
			break;

		case SuperRing:
			scoreToReward = TableListener::scoreTable.SuperRing;
			StatisticsListener::totals.totalSuperRings++;
			break;

		case Trick:
		case TrickFinish:
		case BoardTrick:
			scoreToReward = type == Trick ? TableListener::scoreTable.Trick : type == BoardTrick ? TableListener::scoreTable.BoardTrick : TableListener::scoreTable.TrickFinish;
			StatisticsListener::totals.totalTricks++;
			break;

		case Life:
			scoreToReward = TableListener::scoreTable.Life;
			break;

		case DashRing:
			scoreToReward = TableListener::scoreTable.DashRing;
			StatisticsListener::totals.totalDashRings++;
			break;

		case QuickStep:
			scoreToReward = TableListener::scoreTable.QuickStep;
			StatisticsListener::totals.totalQuickSteps++;
			break;

		case Drift:
			scoreToReward = TableListener::scoreTable.Drift;
			StatisticsListener::totals.totalDrifts++;
			break;

		case Balloon:
			scoreToReward = TableListener::scoreTable.Balloon;
			StatisticsListener::totals.totalBalloons++;
			break;

		case Super:
			scoreToReward = TableListener::scoreTable.Super;
			break;
	}

	// Rewards the score and clamps it.
	AddClamp(ScoreListener::score, scoreToReward);

	// Update total score.
	totalScore = score;

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}