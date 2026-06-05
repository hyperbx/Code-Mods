// Score Generations API Debug
//
// Controls:
// - 1: Add 10 score
// - 2: Remove 10 score
// - 3: Get current score
// - 4: Get final score
// - 5: Set score to 123456
// - 6: Get rank
// - 7: Compute time bonus
// - 8: Compute ring bonus
// - 9: Compute speed bonus
// - 0: Compute user bonus
// - SHIFT + 1: Get statistics
// - SHIFT + 2: Get score table
// - SHIFT + 3: Get rank tables
// - SHIFT + 4: Get bonus table
// - SHIFT + 5: Get multiplier table
// - SHIFT + 6: Get timer table
// - SHIFT + 7: Get score HUD visibility
// - SHIFT + 8: Set (invert) score HUD visibility
// - SHIFT + 9: Get prohibition status of current stage
//
// Change API version in Pch.h

#define VK_NUM(NUMBER) 0x30 + NUMBER

EXPORT void Init()
{
	cmf::sys::Logger::Init();
}

EXPORT void OnFrame()
{
#if SCORE_GENS_API_VERSION == 2
	auto pApi = ScoreGenerations::GetAPI();
#endif

	auto isShift = GetAsyncKeyState(VK_SHIFT);

	if (!isShift)
	{
		if (GetAsyncKeyState(VK_NUM(1)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("AddScore(10)");
			ScoreGenerationsAPI::AddScore(10);
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("AddScore(10) = {}", pApi->AddScore(10));
#endif
		}

		if (GetAsyncKeyState(VK_NUM(2)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_ERROR("RemoveScore(int) is not in Score Generations API v1.");
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("RemoveScore(10) = {}", pApi->RemoveScore(10));
#endif
		}

		if (GetAsyncKeyState(VK_NUM(3)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("GetScore() = {}", ScoreGenerationsAPI::GetScore());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetCurrentScore() = {}", pApi->GetCurrentScore());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(4)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("GetTotalScore() = {}", ScoreGenerationsAPI::GetTotalScore());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetFinalScore() = {}", pApi->GetFinalScore());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(5)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("SetScore(123456)");
			ScoreGenerationsAPI::SetScore(123456);
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("SetScore(123456) = {}", pApi->SetScore(123456));
#endif
		}

		if (GetAsyncKeyState(VK_NUM(6)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("GetRank() = {}", ScoreGenerationsAPI::GetRank());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetRank() = {}", int(pApi->GetRank()));
#endif
		}

		if (GetAsyncKeyState(VK_NUM(7)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("ComputeTimeBonus() = {}", ScoreGenerationsAPI::ComputeTimeBonus());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("ComputeTimeBonus() = {}", pApi->ComputeTimeBonus());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(8)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("ComputeRingBonus() = {}", ScoreGenerationsAPI::ComputeRingBonus());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("ComputeRingBonus() = {}", pApi->ComputeRingBonus());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(9)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("ComputeSpeedBonus() = {}", ScoreGenerationsAPI::ComputeSpeedBonus());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("ComputeSpeedBonus() = {}", pApi->ComputeSpeedBonus());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(0)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("ComputeUserBonus() = {}", ScoreGenerationsAPI::ComputeUserBonus());
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("ComputeUserBonus() = {}", pApi->ComputeUserBonus());
#endif
		}
	}
	else
	{
		if (GetAsyncKeyState(VK_NUM(1)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			static ScoreGenerations::Statistics s_statistics{};
			s_statistics = ScoreGenerationsAPI::GetStatistics();
			LOGFN_WARNING("GetStatistics() = 0x{:X}", (size_t)&s_statistics);
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetStatistics() = 0x{:X}", (size_t)&pApi->GetStatistics());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(2)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			static ScoreGenerations::ScoreTable s_scoreTable{};
			s_scoreTable = ScoreGenerationsAPI::GetScoreTable();
			LOGFN_WARNING("GetScoreTable() = 0x{:X}", (size_t)&s_scoreTable);
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetScoreTable() = 0x{:X}", (size_t)&pApi->GetScoreTable());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(3)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			ScoreGenerationsAPI::GetRankTables();
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetRankTable() = 0x{:X}", (size_t)&pApi->GetRankTable());

			ScoreGenerations::RankTableNode* pRankTables{};
			int rankTablesLength{};

			pApi->GetRankTables(&pRankTables, &rankTablesLength);

			LOGFN_WARNING("GetRankTables()");

			for (int i = 0; i < rankTablesLength; i++)
			{
				auto& rRankTable = pRankTables[i];

				LOGFN_WARNING("{:>2}: 0x{:X} | \"{}\" :: MinSeconds={:<4} MaxSeconds={:<4} S={:<6} A={:<6} B={:<6} C={:<6} D={:<6}",
					i,
					(size_t)rRankTable.pRankTable,
					rRankTable.pStageID,
					rRankTable.pRankTable->MinSeconds,
					rRankTable.pRankTable->MaxSeconds,
					rRankTable.pRankTable->S,
					rRankTable.pRankTable->A,
					rRankTable.pRankTable->B,
					rRankTable.pRankTable->C,
					rRankTable.pRankTable->D
				);
			}

			delete[] pRankTables;

			LOGFN_WARNING("FindRankTable(\"{}\") = 0x{:X}", pApi->GetStageID(), (size_t)&pApi->FindRankTable(pApi->GetStageID()));
#endif
		}

		if (GetAsyncKeyState(VK_NUM(4)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			ScoreGenerationsAPI::GetBonusTable();
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetBonusTable() = 0x{:X}", (size_t)&pApi->GetBonusTable());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(5)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			static ScoreGenerations::MultiplierTable s_multiplierTable{};
			s_multiplierTable = ScoreGenerationsAPI::GetMultiplierTable();
			LOGFN_WARNING("GetMultiplierTable() = 0x{:X}", (size_t)&s_multiplierTable);
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetMultiplierTable() = 0x{:X}", (size_t)&pApi->GetMultiplierTable());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(6)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			static ScoreGenerations::TimerTable s_timerTable{};
			s_timerTable = ScoreGenerationsAPI::GetTimerTable();
			LOGFN_WARNING("GetTimerTable() = 0x{:X}", (size_t)&s_timerTable);
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("GetTimerTable() = {}", (size_t)&pApi->GetTimerTable());
#endif
		}

		if (GetAsyncKeyState(VK_NUM(7)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("GetVisibility() = {}", ScoreGenerationsAPI::GetVisibility() ? "true" : "false");
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("IsScoreHudVisible() = {}", pApi->IsScoreHudVisible() ? "true" : "false");
#endif
		}

		if (GetAsyncKeyState(VK_NUM(8)) & 1)
		{
			static bool s_setScoreHudVisible = false;

#if SCORE_GENS_API_VERSION == 1
			ScoreGenerationsAPI::SetVisibility(s_setScoreHudVisible);
			LOGFN_WARNING("SetVisibility({})", s_setScoreHudVisible ? "true" : "false");
#elif SCORE_GENS_API_VERSION == 2
			pApi->SetScoreHudVisible(s_setScoreHudVisible);
			LOGFN_WARNING("SetScoreHudVisible({})", s_setScoreHudVisible ? "true" : "false");
#endif

			s_setScoreHudVisible = !s_setScoreHudVisible;
		}

		if (GetAsyncKeyState(VK_NUM(9)) & 1)
		{
#if SCORE_GENS_API_VERSION == 1
			LOGFN_WARNING("IsStageForbidden() = {}", ScoreGenerationsAPI::IsStageForbidden() ? "true" : "false");
#elif SCORE_GENS_API_VERSION == 2
			LOGFN_WARNING("IsProhibitedStage() = {}", pApi->IsProhibitedStage() ? "true" : "false");
#endif
		}
	}
}
