// Declare class variables.
unsigned int ScoreListener::score = 0;
ScoreListener::ScoreTable ScoreListener::scoreTable;
ScoreListener::RankTable ScoreListener::rankTable;
ScoreListener::BonusTable ScoreListener::bonusTable;

/// <summary>
/// Resets all statistics used for score calculation.
/// </summary>
void ScoreListener::Reset()
{
	StatisticsListener::totalRingCount = 0;
	StatisticsListener::totalVelocity = 0;
	StatisticsListener::elapsedTime = 0;
	StatisticsListener::ringCount = 0;
	score = 0;

#if _DEBUG
	printf("[Score Generations] StatisticsListener::totalRingCount = %d\n", StatisticsListener::totalRingCount);
	printf("[Score Generations] StatisticsListener::totalVelocity = %d\n", StatisticsListener::totalVelocity);
	printf("[Score Generations] StatisticsListener::elapsedTime = %d\n", StatisticsListener::elapsedTime);
	printf("[Score Generations] StatisticsListener::ringCount = %d\n", StatisticsListener::ringCount);
	printf("[Score Generations] ScoreListener::score = %d\n", score);
#endif
}

/// <summary>
/// Calculates the bonuses and adds them to the total score.
/// </summary>
void ScoreListener::Bonus()
{
	if (bonusTable.timeBonus != -1)
	{
		// Calculate time bonus.
		score += StatisticsListener::elapsedTime * bonusTable.timeBonus;
	}

	if (bonusTable.ringBonus != -1)
	{
		// Calculate ring bonus.
		score += StatisticsListener::ringCount * bonusTable.ringBonus;
	}

	if (bonusTable.speedBonus != -1)
	{
		// Calculate speed bonus.
		score += StatisticsListener::totalVelocity * bonusTable.speedBonus;
	}

#if _DEBUG
	printf("[Score Generations] Time Bonus = %d\n", StatisticsListener::elapsedTime * bonusTable.timeBonus);
	printf("[Score Generations] Ring Bonus = %d\n", StatisticsListener::ringCount * bonusTable.ringBonus);
	printf("[Score Generations] Speed Bonus = %d\n", StatisticsListener::totalVelocity * bonusTable.speedBonus);
#endif
}

/// <summary>
/// Rewards the player with score based on the input type.
/// </summary>
void __fastcall ScoreListener::Reward(Object type)
{
	int scoreToReward = 0;

	switch (type)
	{
		case Ring:
			scoreToReward = scoreTable.Ring;
			break;

		case Enemy:
			scoreToReward = scoreTable.Enemy;
			break;

		case Physics:
			scoreToReward = scoreTable.Physics;
			break;

		case PointMarker:
		{
			scoreToReward = scoreTable.PointMarker;

			// Increase total velocity for the speed bonus.
			StatisticsListener::totalVelocity += (unsigned int)(PlayerListener::GetVelocity() * 10);

#if _DEBUG
			printf("[Score Generations] Total Velocity = %d\n", StatisticsListener::totalVelocity);
#endif

			break;
		}

		case RedRing:
			scoreToReward = scoreTable.RedRing;
			break;

		case RainbowRing:
			scoreToReward = scoreTable.RainbowRing;
			break;

		case ItemBox:
			scoreToReward = scoreTable.ItemBox;
			break;

		case SuperRing:
			scoreToReward = scoreTable.SuperRing;
			break;

		case TrickRamp:
			scoreToReward = scoreTable.TrickRamp;
			break;

		case Tricks:
			scoreToReward = scoreTable.TrickRamp;
			break;

		case Life:
			scoreToReward = scoreTable.Life;
			break;
	}

	// Clamp the maximum score.
	if ((score + scoreToReward) <= 999999)
		score += scoreToReward;
	else
		score = 999999;

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}