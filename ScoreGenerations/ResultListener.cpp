ResultListener::ResultDescription ResultListener::resultDescription;

void ResultListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	ScoreListener::AddClamp(LuaCallback::GetBonus(Tables::bonusTable.timeBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::GetBonus(Tables::bonusTable.ringBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::GetBonus(Tables::bonusTable.speedBonusAlgorithm));
}

ResultListener::RankType ResultListener::Rank()
{
	if (ScoreListener::score < Tables::rankTables[StateHooks::stageID].A)
	{
		if (ScoreListener::score < Tables::rankTables[StateHooks::stageID].B)
		{
			if (ScoreListener::score < Tables::rankTables[StateHooks::stageID].C)
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
	// Print exposed Lua data before results manipulation.
	LuaCallback::PrintExposedData();

	// Calculate the bonuses.
	ResultListener::Bonus();

	// Set the final score.
	resultDescription.score = ScoreListener::score;

	// Set up ranks.
	resultDescription.rank = Rank();
	resultDescription.perfectRank = Rank() + 1;

	// Set up progress bar.
	resultDescription.scoreProgress = min((float)ScoreListener::score / (float)Tables::rankTables[StateHooks::stageID].A, 1);
	resultDescription.ringProgress = resultDescription.scoreProgress + 0.0001; // Increment the tiniest amount so the ring count appears.
}