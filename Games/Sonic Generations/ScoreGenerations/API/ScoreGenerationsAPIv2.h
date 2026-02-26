#pragma once

#include "ScoreGenerationsAPI.h"

#define SCORE_GENS_API_EXPORT_NAME ScoreGenerations_GetAPI

#define DECLARE_API_FUNC(RETURN_TYPE, NAME, ...) \
	RETURN_TYPE (SCORE_GENS_API *NAME)(__VA_ARGS__) = nullptr;

namespace ScoreGenerations
{
	struct API
	{
		DECLARE_API_FUNC(void, ReadConfiguration, const char* in_pPath);
		DECLARE_API_FUNC(int&, AddScore, int in_score);
		DECLARE_API_FUNC(int&, RemoveScore, int in_score);
		DECLARE_API_FUNC(int&, GetCurrentScore);
		DECLARE_API_FUNC(int&, GetFinalScore);
		DECLARE_API_FUNC(int&, SetScore, int in_score);
		DECLARE_API_FUNC(RankType, GetRank);
		DECLARE_API_FUNC(int, ComputeTimeBonus);
		DECLARE_API_FUNC(int, ComputeRingBonus);
		DECLARE_API_FUNC(int, ComputeSpeedBonus);
		DECLARE_API_FUNC(int, ComputeUserBonus);
		DECLARE_API_FUNC(Statistics&, GetStatistics);
		DECLARE_API_FUNC(ScoreTable&, GetScoreTable);
		DECLARE_API_FUNC(RankTable&, GetRankTable);
		DECLARE_API_FUNC(void, GetRankTables, RankTableNode** out_ppBuffer, int* out_pLength);
		DECLARE_API_FUNC(RankTable&, FindRankTable, const char* in_pStageID);
		DECLARE_API_FUNC(BonusTable&, GetBonusTable);
		DECLARE_API_FUNC(MultiplierTable&, GetMultiplierTable);
		DECLARE_API_FUNC(TimerTable&, GetTimerTable);
		DECLARE_API_FUNC(bool, IsScoreHudVisible);
		DECLARE_API_FUNC(void, SetScoreHudVisible, bool in_isVisible);
		DECLARE_API_FUNC(bool, IsProhibitedStage);
		DECLARE_API_FUNC(const char*, GetStageID);
	};

	inline HMODULE GetModule()
	{
		return GetModuleHandleA(SCORE_GENS_MODULE);
	}

#ifndef SCORE_GENS_IMPL
	inline const ScoreGenerations::API* GetAPI()
	{
		static const ScoreGenerations::API* s_pApi{};

		if (!s_pApi)
		{
			auto hModule = GetModule();

			if (hModule)
			{
				const ScoreGenerations::API* (*fpGetAPI)() = (const ScoreGenerations::API * (*)())GetProcAddress(hModule, SCORE_GENS_XSTRINGIFY(SCORE_GENS_API_EXPORT_NAME));

				if (fpGetAPI)
					s_pApi = fpGetAPI();
			}
		}

		return s_pApi;
	}
#endif
};

extern ScoreGenerations::API g_ScoreGenerationsAPI;

#ifdef SCORE_GENS_IMPL
SCORE_GENS_EXPORT const ScoreGenerations::API* SCORE_GENS_API SCORE_GENS_API_EXPORT_NAME();
#endif

#undef DECLARE_API_FUNC
