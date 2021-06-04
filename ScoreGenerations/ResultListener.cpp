unordered_map<string, ResultListener::RankTable> ResultListener::rankTables;
ResultListener::BonusTable ResultListener::bonusTable;
ResultListener::ResultDescription ResultListener::resultDescription;

void ResultListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	ScoreListener::AddClamp(LuaCallback::GetBonus(bonusTable.timeBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::GetBonus(bonusTable.ringBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::GetBonus(bonusTable.speedBonusAlgorithm));
}

ResultListener::RankType ResultListener::Rank()
{
	if (ScoreListener::score < rankTables[StateHooks::stageID].A)
	{
		if (ScoreListener::score < rankTables[StateHooks::stageID].B)
		{
			if (ScoreListener::score < rankTables[StateHooks::stageID].C)
			{
				return RankType::D; // D rank
			}
			else
			{
				return RankType::C; // C rank
			}
		}
		else
		{
			return RankType::B; // B rank
		}
	}
	else
	{
		return RankType::A; // A rank
	}
}

void ResultListener::Result()
{
	// Calculate the bonuses.
	ResultListener::Bonus();

	// Set the final score.
	resultDescription.score = ScoreListener::score;

	// Set up ranks.
	resultDescription.rank = Rank();
	resultDescription.perfectRank = Rank() + 1;

	// Set up progress bars.
	resultDescription.scoreProgress = min((float)ScoreListener::score / (float)rankTables[StateHooks::stageID].A, 1);
	resultDescription.ringProgress = resultDescription.scoreProgress + min((float)StatisticsListener::ringCount / 999, 1);
}