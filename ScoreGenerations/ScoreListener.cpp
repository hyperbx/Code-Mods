int ScoreListener::score = 0;
ScoreListener::ScoreTable ScoreListener::scoreTable;

void ScoreListener::Reset()
{
	StatisticsListener::totalRingCount = 0;
	StatisticsListener::totalVelocity = 0;
	StatisticsListener::ringCount = 0;
	StatisticsListener::minutes = 0;
	StatisticsListener::seconds = 0;
	score = 0;
}

void ScoreListener::AddClamp(unsigned int scoreToReward)
{
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

		case Super:
			scoreToReward = scoreTable.Super;
			break;

		case BoardTrick:
			scoreToReward = scoreTable.BoardTrick;
			break;
	}

	// Rewards the score and clamps it.
	AddClamp(scoreToReward);

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}