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
	StatisticsListener::ringCount = 0;
	StatisticsListener::minutes = 0;
	StatisticsListener::seconds = 0;
	score = 0;

#if _DEBUG
	printf("[Score Generations] Your score has been reset...\n");
	printf("[Score Generations] totalRingCount = %d\n", StatisticsListener::totalRingCount);
	printf("[Score Generations] totalVelocity = %d\n", StatisticsListener::totalVelocity);
	printf("[Score Generations] ringCount = %d\n", StatisticsListener::ringCount);
	printf("[Score Generations] minutes = %d\n", StatisticsListener::minutes);
	printf("[Score Generations] seconds = %d\n", StatisticsListener::seconds);
	printf("[Score Generations] elapsedTime = %d\n", StatisticsListener::GetElapsedTime());
	printf("[Score Generations] score = %d\n", score);
#endif
}

void ScoreListener::Clamp(unsigned int scoreToReward)
{
	// Clamp the maximum score.
	if ((score + scoreToReward) <= Configuration::scoreLimit)
		score += scoreToReward;
	else
		score = Configuration::scoreLimit;
}

/// <summary>
/// Calculates the bonuses and adds them to the total score.
/// </summary>
void ScoreListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	Clamp(LuaCallback::GetBonus(bonusTable.timeBonusAlgorithm));
	Clamp(LuaCallback::GetBonus(bonusTable.ringBonusAlgorithm));
	Clamp(LuaCallback::GetBonus(bonusTable.speedBonusAlgorithm));
}

/// <summary>
/// Rewards the player with score based on the input type.
/// </summary>
void __fastcall ScoreListener::Reward(ScoreType type)
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

		case TrickFinish:
			scoreToReward = scoreTable.TrickFinish;
			break;

		case Trick:
			scoreToReward = scoreTable.Trick;
			break;

		case Life:
			scoreToReward = scoreTable.Life;
			break;

		case DashRing:
			scoreToReward = scoreTable.DashRing;
			break;

		case QuickStep:
			scoreToReward = scoreTable.QuickStep;
			break;

		case Drift:
			scoreToReward = scoreTable.Drift;
			break;

		case Balloon:
			scoreToReward = scoreTable.Balloon;
			break;
	}

	// Rewards the score and clamps it.
	Clamp(scoreToReward);

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}