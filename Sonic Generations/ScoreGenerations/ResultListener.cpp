ResultListener::ResultDescription ResultListener::resultDescription;

void ResultListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.timeBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.ringBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.speedBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.userAlgorithm), false);
}

ResultListener::RankType ResultListener::Rank()
{
	if (ScoreListener::score < TableListener::rankTables[StateHooks::stageID].A)
	{
		if (ScoreListener::score < TableListener::rankTables[StateHooks::stageID].B)
		{
			if (ScoreListener::score < TableListener::rankTables[StateHooks::stageID].C)
			{
				return RankType::D;
			}
			else
			{
				return RankType::C;
			}
		}
		else
		{
			return RankType::B;
		}
	}
	else
	{
		return RankType::A;
	}
}

float ResultListener::Progress(RankType rank)
{
	switch (rank)
	{
		case D:
			return ((float)ScoreListener::score / (float)TableListener::rankTables[StateHooks::stageID].C) / 3.0f;

		case C:
		{
			const float baseScore = (float)TableListener::rankTables[StateHooks::stageID].C;
			return (1.0f / 3.0f) + (((float)ScoreListener::score - baseScore) / ((float)TableListener::rankTables[StateHooks::stageID].B - baseScore)) / 3.0f;
		}

		case B:
		{
			const float baseScore = (float)TableListener::rankTables[StateHooks::stageID].B;
			return (2.0f / 3.0f) + (((float)ScoreListener::score - baseScore) / ((float)TableListener::rankTables[StateHooks::stageID].A - baseScore)) / 3.0f;
		}

		case A:
			return 1.0f;
	}
}

void ResultListener::Result()
{
	// Calculate the bonuses.
	ResultListener::Bonus();

	// Set the final score.
	resultDescription.score = ScoreListener::totalScore;

	// Print exposed Lua data before results manipulation.
	LuaCallback::PrintExposedData();

	// Set up ranks.
	resultDescription.rank = Rank();
	resultDescription.perfectRank = Rank() + 1;

	// Set up progress bar.
	resultDescription.scoreProgress = Progress(Rank());
	resultDescription.ringProgress = resultDescription.scoreProgress + 0.0001; // Increment the tiniest amount so the ring count appears.
}