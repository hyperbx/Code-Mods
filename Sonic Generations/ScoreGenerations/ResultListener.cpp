ResultListener::ResultDescription ResultListener::resultDescription;

void ResultListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.timeBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.ringBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.speedBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.userAlgorithm), false);
}

ResultListener::RankType ResultListener::Rank(bool perfect)
{
	RankType rank;
	int total = ScoreListener::totalScore;
	int S = TableListener::rankTables[BlueBlurCommon::GetStageID()].S;
	int A = TableListener::rankTables[BlueBlurCommon::GetStageID()].A;
	int B = TableListener::rankTables[BlueBlurCommon::GetStageID()].B;
	int C = TableListener::rankTables[BlueBlurCommon::GetStageID()].C;

	if (Configuration::perfectBonus == Configuration::PerfectBonusType::Disabled && S != -1 && total > S)
	{
		/* Only use S rank if perfect bonus is disabled
		   and S rank isn't the default value. */
		return RankType::S;
	}

	if (total < A)
	{
		if (total < B)
		{
			if (total < C)
			{
				rank = RankType::D;
			}
			else
			{
				rank = RankType::C;
			}
		}
		else
		{
			rank = RankType::B;
		}
	}
	else
	{
		rank = RankType::A;
	}

	return (RankType)(perfect && Configuration::perfectBonus != Configuration::PerfectBonusType::Disabled ? rank + 1 : rank);
}

/// <summary>
/// Computes the progress bar percentage based on the input rank and divider.
/// </summary>
/// <param name="rank">Rank to line up with.</param>
/// <param name="divider">Divider to set up rank results.</param>
float ComputeProgressBar(ResultListener::RankType rank, int divider)
{
	switch (rank)
	{
		case ResultListener::RankType::D:
			return ((float)divider / (float)TableListener::rankTables[BlueBlurCommon::GetStageID()].C) / 3.0f;

		case ResultListener::RankType::C:
		{
			const float baseScore = (float)TableListener::rankTables[BlueBlurCommon::GetStageID()].C;
			return (1.0f / 3.0f) + (((float)divider - baseScore) / ((float)TableListener::rankTables[BlueBlurCommon::GetStageID()].B - baseScore)) / 3.0f;
		}

		case ResultListener::RankType::B:
		{
			const float baseScore = (float)TableListener::rankTables[BlueBlurCommon::GetStageID()].B;
			return (2.0f / 3.0f) + (((float)divider - baseScore) / ((float)TableListener::rankTables[BlueBlurCommon::GetStageID()].A - baseScore)) / 3.0f;
		}

		default:
			return 1.0f;
	}
}

std::tuple<float, float> ResultListener::ComputeProgressBars(RankType rank)
{
	float scoreProgress;
	float ringProgress;

	int ringBonus = LuaCallback::RunAlgorithm(TableListener::bonusTable.ringBonusAlgorithm);

	// Compute score progress.
	scoreProgress = ComputeProgressBar(rank, ScoreListener::totalScore - ringBonus);

	// Compute ring progress.
	ringProgress = (scoreProgress == 1.0f || StatisticsListener::totals.ringCount == 0)
				   ? scoreProgress + 0.0001f
				   : ComputeProgressBar(rank, ScoreListener::totalScore + static_cast<float>(ringBonus) / StatisticsListener::totals.ringCount) + 0.0001f;

	return { scoreProgress, ringProgress };
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
	resultDescription.perfectRank = Rank(true);

	// Compute results progress bar.
	auto [score, ring] = ComputeProgressBars(Rank());

	// Set up progress bars.
	resultDescription.scoreProgress = score;
	resultDescription.ringProgress = ring;
}