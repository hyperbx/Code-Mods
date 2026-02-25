#include "ScoreGenerationsAPI.h"
#include "ScoreGenerationsAPIv2.h"

#define IMPL_API_FUNC(NAME) API_##NAME

using namespace ScoreGenerations;

SCORE_GENS_EXPORT void IMPL_API_FUNC(AddScore)(int in_score)
{
    LOGFN_UTILITY("API v1: Redirected AddScore({})", in_score);

    SCORE_GENS_API_EXPORT_NAME()->AddScore(in_score);
}

SCORE_GENS_EXPORT void IMPL_API_FUNC(SetScore)(int in_score)
{
    LOGFN_UTILITY("API v1: Redirected SetScore({})", in_score);

    SCORE_GENS_API_EXPORT_NAME()->SetScore(in_score);
}

SCORE_GENS_EXPORT void IMPL_API_FUNC(ForceConfiguration)(const char* in_pPath)
{
    LOGFN_UTILITY("API v1: Redirected ForceConfiguration(\"{}\") -> ReadConfiguration(\"{}\")", in_pPath, in_pPath);

    SCORE_GENS_API_EXPORT_NAME()->ReadConfiguration(in_pPath);
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(GetScore)()
{
    LOGFN_UTILITY("API v1: Redirected GetScore() -> GetCurrentScore()");

    return SCORE_GENS_API_EXPORT_NAME()->GetCurrentScore();
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(GetTotalScore)()
{
    LOGFN_UTILITY("API v1: Redirected GetTotalScore() -> GetFinalScore()");

    return SCORE_GENS_API_EXPORT_NAME()->GetFinalScore();
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(GetRank)()
{
    LOGFN_UTILITY("API v1: Redirected GetRank()");

    return int(SCORE_GENS_API_EXPORT_NAME()->GetRank());
}

SCORE_GENS_EXPORT bool IMPL_API_FUNC(IsStageForbidden)()
{
    LOGFN_UTILITY("API v1: Redirected IsStageForbidden() -> IsProhibitedStage()");

    return SCORE_GENS_API_EXPORT_NAME()->IsProhibitedStage();
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(ComputeTimeBonus)()
{
    LOGFN_UTILITY("API v1: Redirected ComputeTimeBonus()");

    return SCORE_GENS_API_EXPORT_NAME()->ComputeTimeBonus();
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(ComputeRingBonus)()
{
    LOGFN_UTILITY("API v1: Redirected ComputeRingBonus()");

    return SCORE_GENS_API_EXPORT_NAME()->ComputeRingBonus();
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(ComputeSpeedBonus)()
{
    LOGFN_UTILITY("API v1: Redirected ComputeSpeedBonus()");

    return SCORE_GENS_API_EXPORT_NAME()->ComputeSpeedBonus();
}

SCORE_GENS_EXPORT int IMPL_API_FUNC(ComputeUserBonus)()
{
    LOGFN_UTILITY("API v1: Redirected ComputeUserBonus()");

    return SCORE_GENS_API_EXPORT_NAME()->ComputeUserBonus();
}

SCORE_GENS_EXPORT Statistics IMPL_API_FUNC(GetStatistics)()
{
    LOGFN_UTILITY("API v1: Redirected GetStatistics()");

    return SCORE_GENS_API_EXPORT_NAME()->GetStatistics();
}

SCORE_GENS_EXPORT ScoreTable IMPL_API_FUNC(GetScoreTable)()
{
    LOGFN_UTILITY("API v1: Redirected GetScoreTable()");

    return SCORE_GENS_API_EXPORT_NAME()->GetScoreTable();
}

SCORE_GENS_EXPORT void IMPL_API_FUNC(GetRankTables)()
{
    LOGFN_ERROR("API v1: GetRankTables() is deprecated and no longer functions.");
}

SCORE_GENS_EXPORT void IMPL_API_FUNC(GetBonusTable)()
{
    LOGFN_ERROR("API v1: GetBonusTable() is deprecated and no longer functions.");
}

SCORE_GENS_EXPORT MultiplierTable IMPL_API_FUNC(GetMultiplierTable)()
{
    LOGFN_UTILITY("API v1: Redirected GetMultiplierTable()");

    return SCORE_GENS_API_EXPORT_NAME()->GetMultiplierTable();
}

SCORE_GENS_EXPORT TimerTable IMPL_API_FUNC(GetTimerTable)()
{
    LOGFN_UTILITY("API v1: Redirected GetTimerTable()");

    return SCORE_GENS_API_EXPORT_NAME()->GetTimerTable();
}

SCORE_GENS_EXPORT void IMPL_API_FUNC(SetVisibility)(bool in_isVisible)
{
    LOGFN_UTILITY("API v1: Redirected SetVisibility({}) -> SetHudVisible({})", in_isVisible ? "true" : "false", in_isVisible ? "true" : "false");

    return SCORE_GENS_API_EXPORT_NAME()->SetScoreHudVisible(in_isVisible);
}

SCORE_GENS_EXPORT bool IMPL_API_FUNC(GetVisibility)()
{
    LOGFN_UTILITY("API v1: Redirected GetVisibility() -> GetHudVisible()");

    return SCORE_GENS_API_EXPORT_NAME()->IsScoreHudVisible();
}
