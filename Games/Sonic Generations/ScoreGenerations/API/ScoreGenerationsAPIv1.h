#pragma once

#include "ScoreGenerationsAPI.h"

#define DECLARE_API_FUNC(RETURN_TYPE, NAME, ...) \
    typedef RETURN_TYPE NAME##_t(__VA_ARGS__);   \
    NAME##_t* fp##NAME = (NAME##_t*)GetProcAddress(GetModuleHandleA(SCORE_GENS_MODULE), SCORE_GENS_XSTRINGIFY(API_##NAME));

#define GET_API_FUNC(NAME) GetInstance()->fp##NAME

class ScoreGenerationsAPI
{
private:
	DECLARE_API_FUNC(void, AddScore, int in_score);
	DECLARE_API_FUNC(void, SetScore, int in_score);
	DECLARE_API_FUNC(void, ForceConfiguration, const char* in_pPath);
	DECLARE_API_FUNC(int, GetScore);
	DECLARE_API_FUNC(int, GetTotalScore);
	DECLARE_API_FUNC(ScoreGenerations::RankType, GetRank);
	DECLARE_API_FUNC(bool, IsStageForbidden);
	DECLARE_API_FUNC(int, ComputeTimeBonus);
	DECLARE_API_FUNC(int, ComputeRingBonus);
	DECLARE_API_FUNC(int, ComputeSpeedBonus);
	DECLARE_API_FUNC(int, ComputeUserBonus);
	DECLARE_API_FUNC(ScoreGenerations::Statistics, GetStatistics);
	DECLARE_API_FUNC(ScoreGenerations::ScoreTable, GetScoreTable);
	DECLARE_API_FUNC(void, GetRankTables);
	DECLARE_API_FUNC(void, GetBonusTable);
	DECLARE_API_FUNC(ScoreGenerations::MultiplierTable, GetMultiplierTable);
	DECLARE_API_FUNC(ScoreGenerations::TimerTable, GetTimerTable);
	DECLARE_API_FUNC(void, SetVisibility, bool in_isVisible);
	DECLARE_API_FUNC(bool, GetVisibility);

public:
	static void AddScore(int in_score)
	{
		return GET_API_FUNC(AddScore)(in_score);
	}

	static void SetScore(int in_score)
	{
		return GET_API_FUNC(SetScore)(in_score);
	}

	static void ForceConfiguration(const char* in_pPath)
	{
		return GET_API_FUNC(ForceConfiguration)(in_pPath);
	}

	static int GetScore()
	{
		return GET_API_FUNC(GetScore)();
	}

	static int GetTotalScore()
	{
		return GET_API_FUNC(GetTotalScore)();
	}

	static int GetRank()
	{
		return int(GET_API_FUNC(GetRank)());
	}

	static bool IsStageForbidden()
	{
		return GET_API_FUNC(IsStageForbidden)();
	}

	static int ComputeTimeBonus()
	{
		return GET_API_FUNC(ComputeTimeBonus)();
	}

	static int ComputeRingBonus()
	{
		return GET_API_FUNC(ComputeRingBonus)();
	}

	static int ComputeSpeedBonus()
	{
		return GET_API_FUNC(ComputeSpeedBonus)();
	}

	static int ComputeUserBonus()
	{
		return GET_API_FUNC(ComputeUserBonus)();
	}

	static ScoreGenerations::Statistics GetStatistics()
	{
		return GET_API_FUNC(GetStatistics)();
	}

	static ScoreGenerations::ScoreTable GetScoreTable()
	{
		return GET_API_FUNC(GetScoreTable)();
	}

	static void GetRankTables()
	{
		return GET_API_FUNC(GetRankTables)();
	}

	static void GetBonusTable()
	{
		return GET_API_FUNC(GetBonusTable)();
	}

	static ScoreGenerations::MultiplierTable GetMultiplierTable()
	{
		return GET_API_FUNC(GetMultiplierTable)();
	}

	static ScoreGenerations::TimerTable GetTimerTable()
	{
		return GET_API_FUNC(GetTimerTable)();
	}

	static void SetVisibility(bool in_isVisible)
	{
		return GET_API_FUNC(SetVisibility)(in_isVisible);
	}

	static bool GetVisibility()
	{
		return GET_API_FUNC(GetVisibility)();
	}

	static bool IsAttached()
	{
		return GetModuleHandleA(SCORE_GENS_MODULE) != nullptr;
	}

	static ScoreGenerationsAPI* GetInstance()
	{
		static ScoreGenerationsAPI* s_pApi{};

		return s_pApi ? s_pApi : s_pApi = new ScoreGenerationsAPI();
	}
};

#undef GET_API_FUNC
#undef DECLARE_API_FUNC
