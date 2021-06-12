ResultListener::ResultDescription ResultListener::resultDescription;

void ResultListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	ScoreListener::AddClamp(LuaCallback::RunAlgorithm(Tables::bonusTable.timeBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::RunAlgorithm(Tables::bonusTable.ringBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::RunAlgorithm(Tables::bonusTable.speedBonusAlgorithm));
	ScoreListener::AddClamp(LuaCallback::RunAlgorithm(Tables::bonusTable.userAlgorithm));
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

float ResultListener::Progress(RankType rank)
{
	switch (rank)
	{
		case D:
			return ((float)ScoreListener::score / (float)Tables::rankTables[StateHooks::stageID].C) / 3.0f;

		case C:
		{
			const float baseScore = (float)Tables::rankTables[StateHooks::stageID].C;
			return (1.0f / 3.0f) + (((float)ScoreListener::score - baseScore) / ((float)Tables::rankTables[StateHooks::stageID].B - baseScore)) / 3.0f;
		}

		case B:
		{
			const float baseScore = (float)Tables::rankTables[StateHooks::stageID].B;
			return (2.0f / 3.0f) + (((float)ScoreListener::score - baseScore) / ((float)Tables::rankTables[StateHooks::stageID].A - baseScore)) / 3.0f;
		}

		case A:
			return 1.0f;
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
	resultDescription.scoreProgress = Progress(Rank());
	resultDescription.ringProgress = resultDescription.scoreProgress + 0.0001; // Increment the tiniest amount so the ring count appears.
}