#include "ScoreGenerationsAPIv2.h"

#include <filesystem>
#include <memory>

#include "../Configuration.h"
#include "../LuaSystem.h"
#include "../ScoreHud.h"
#include "../ScoreProvider.h"
#include "../StatisticsProvider.h"
#include "../TableProvider.h"

using namespace ScoreGenerations;

static void SCORE_GENS_API ReadConfiguration(const char* in_pPath)
{
    Configuration::Read(std::filesystem::path(in_pPath));
}

static int& SCORE_GENS_API AddScore(int in_score)
{
    return ScoreProvider::AddScore(in_score);
}

static int& SCORE_GENS_API RemoveScore(int in_score)
{
    return ScoreProvider::RemoveScore(in_score);
}

static int& SCORE_GENS_API GetCurrentScore()
{
    return ScoreProvider::GetCurrentScore();
}

static int& SCORE_GENS_API GetFinalScore()
{
    return ScoreProvider::GetFinalScore();
}

static int& SCORE_GENS_API SetScore(int in_score)
{
    return ScoreProvider::SetScore(in_score);
}

static RankType SCORE_GENS_API GetRank()
{
    return ScoreProvider::GetRank();
}

static int SCORE_GENS_API ComputeTimeBonus()
{
    return LuaSystem::RunExpression<int>(TableProvider::GetBonusTable().pTimeBonusExpression);
}

static int SCORE_GENS_API ComputeRingBonus()
{
    return LuaSystem::RunExpression<int>(TableProvider::GetBonusTable().pRingBonusExpression);
}

static int SCORE_GENS_API ComputeSpeedBonus()
{
    return LuaSystem::RunExpression<int>(TableProvider::GetBonusTable().pSpeedBonusExpression);
}

static int SCORE_GENS_API ComputeUserBonus()
{
    return LuaSystem::RunExpression<int>(TableProvider::GetBonusTable().pUserExpression);
}

static Statistics& SCORE_GENS_API GetStatistics()
{
    return StatisticsProvider::GetStatistics();
}

static ScoreTable& SCORE_GENS_API GetScoreTable()
{
    return TableProvider::GetScoreTable();
}

static RankTable& SCORE_GENS_API GetCurrentRankTable()
{
    return TableProvider::GetRankTables()[g_pStageID];
}

static RankTable& SCORE_GENS_API GetRankTable(const char* in_pStageID)
{
    return TableProvider::GetRankTables()[in_pStageID];
}

static void SCORE_GENS_API GetRankTables(RankTableNode** out_ppBuffer, int* out_pLength)
{
    auto& rRankTables = TableProvider::GetRankTables();

    auto length = rRankTables.size();
    auto pBuffer = new RankTableNode[length];
    auto i = 0;

    for (const auto& [key, value] : rRankTables)
    {
        pBuffer[i] = RankTableNode(key.c_str(), &value);
        i++;
    }

    *out_ppBuffer = pBuffer;
    *out_pLength = length;
}

static BonusTable& SCORE_GENS_API GetBonusTable()
{
    return TableProvider::GetBonusTable();
}

static MultiplierTable& SCORE_GENS_API GetMultiplierTable()
{
    return TableProvider::GetMultiplierTable();
}

static TimerTable& SCORE_GENS_API GetTimerTable()
{
    return TableProvider::GetTimerTable();
}

static bool SCORE_GENS_API IsScoreHudVisible()
{
    return ScoreHud::IsVisible;
}

static void SCORE_GENS_API SetScoreHudVisible(bool in_isVisible)
{
    ScoreHud::IsVisible = in_isVisible;
}

static bool SCORE_GENS_API IsProhibitedStage()
{
    return ScoreHud::IsProhibitedStage();
}

static const char* SCORE_GENS_API GetStageID()
{
    return g_pStageID;
}

static const API* SCORE_GENS_API SCORE_GENS_API_EXPORT_NAME()
{
    return &g_ScoreGenerationsAPI;
}

API g_ScoreGenerationsAPI
{
    ReadConfiguration,
    AddScore,
    RemoveScore,
    GetCurrentScore,
    GetFinalScore,
    SetScore,
    GetRank,
    ComputeTimeBonus,
    ComputeRingBonus,
    ComputeSpeedBonus,
    ComputeUserBonus,
    GetStatistics,
    GetScoreTable,
    GetCurrentRankTable,
    GetRankTable,
    GetRankTables,
    GetBonusTable,
    GetMultiplierTable,
    GetTimerTable,
    IsScoreHudVisible,
    SetScoreHudVisible,
    IsProhibitedStage,
    GetStageID
};