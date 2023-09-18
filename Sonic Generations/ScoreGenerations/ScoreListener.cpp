int ScoreListener::score = 0;
int ScoreListener::totalScore = 0;
int ScoreListener::lastCheckpointScore = 0;
float ScoreListener::lastCheckpointVelocity = 0;

void ScoreListener::Reset(bool useLastCheckpointScore)
{
	// Reset last checkpoint score if not used.
	if (!useLastCheckpointScore)
		lastCheckpointScore = 0;

	totalScore = score = useLastCheckpointScore ? lastCheckpointScore : 0;
	StatisticsListener::totals.Reset();
}

void ScoreListener::AddClamp(int& score, int scoreToReward, bool timeout)
{
	if (timeout)
	{
		// Stop rewarding score if the player is over the maximum time.
		if (Configuration::scoreTimeout && StatisticsListener::totals.elapsedTime > TableListener::rankTables[BlueBlurCommon::GetStageCharID()].maxSeconds)
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
			scoreToReward = TableListener::scoreTable.Enemy;
			scoreToReward += MultiplierListener::GetHomingChainBonus();
			scoreToReward += MultiplierListener::GetSlamBonus();
			StatisticsListener::totals.totalEnemies++;
			break;

		case Physics:
			scoreToReward = TableListener::scoreTable.Physics;
			StatisticsListener::totals.totalPhysics++;
			break;

		case PointMarker:
		{
			scoreToReward = TableListener::scoreTable.PointMarker;

			// Update current velocity.
			lastCheckpointVelocity = BlueBlurCommon::GetVelocity();
			{
				// Update max velocity if current velocity is higher.
				if (lastCheckpointVelocity > StatisticsListener::totals.maxVelocity)
					StatisticsListener::totals.maxVelocity = lastCheckpointVelocity;

#if _DEBUG
				printf("[Score Generations] Max Velocity = %f\n", StatisticsListener::totals.maxVelocity);
#endif
			}

			// Increase total velocity for the speed bonus.
			if (Configuration::rewardSpeedBonus)
			{
				StatisticsListener::totals.totalVelocity += lastCheckpointVelocity * TableListener::multiplierTable.speedBonusMultiplier;

#if _DEBUG
				printf("[Score Generations] Total Velocity = %f\n", StatisticsListener::totals.totalVelocity);
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
		case BoardTrick:
			scoreToReward = MultiplierListener::GetTrickBonus(type == Trick ? TableListener::scoreTable.Trick : TableListener::scoreTable.BoardTrick);
			StatisticsListener::totals.totalTricks++;
			break;

		case TrickFinish:
			scoreToReward = TableListener::scoreTable.TrickFinish;
			MultiplierListener::ResetTrickBonus();
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