int ScoreListener::score = 0;

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
			scoreToReward = Tables::scoreTable.Ring;
			break;

		case Enemy:
			scoreToReward = MultiplierListener::AddHomingChainBonus(Tables::scoreTable.Enemy);
			break;

		case Physics:
			scoreToReward = Tables::scoreTable.Physics;
			break;

		case PointMarker:
		{
			scoreToReward = Tables::scoreTable.PointMarker;

			// Increase total velocity for the speed bonus.
			StatisticsListener::totalVelocity += (unsigned int)(PlayerListener::GetVelocity() * 10);

#if _DEBUG
			printf("[Score Generations] Total Velocity = %d\n", StatisticsListener::totalVelocity);
#endif

			break;
		}

		case RedRing:
			scoreToReward = Tables::scoreTable.RedRing;
			break;

		case RainbowRing:
			scoreToReward = Tables::scoreTable.RainbowRing;
			break;

		case ItemBox:
			scoreToReward = Tables::scoreTable.ItemBox;
			break;

		case SuperRing:
			scoreToReward = Tables::scoreTable.SuperRing;
			break;

		case TrickFinish:
			scoreToReward = Tables::scoreTable.TrickFinish;
			break;

		case Trick:
			scoreToReward = Tables::scoreTable.Trick;
			break;

		case Life:
			scoreToReward = Tables::scoreTable.Life;
			break;

		case DashRing:
			scoreToReward = Tables::scoreTable.DashRing;
			break;

		case QuickStep:
			scoreToReward = Tables::scoreTable.QuickStep;
			break;

		case Drift:
			scoreToReward = Tables::scoreTable.Drift;
			break;

		case Balloon:
			scoreToReward = Tables::scoreTable.Balloon;
			break;

		case Super:
			scoreToReward = Tables::scoreTable.Super;
			break;

		case BoardTrick:
			scoreToReward = Tables::scoreTable.BoardTrick;
			break;
	}

	// Rewards the score and clamps it.
	AddClamp(scoreToReward);

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}