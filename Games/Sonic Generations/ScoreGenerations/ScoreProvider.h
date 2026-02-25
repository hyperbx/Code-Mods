#pragma once

#include "API/ScoreGenerationsTypes.h"

namespace ScoreGenerations
{
    enum class ScoreType
    {
        Ring,
        Enemy,
        Physics,
        PointMarker,
        RedRing,
        RainbowRing,
        ItemBox,
        SuperRing,
        TrickFinish,
        Trick,
        Life,
        DashRing,
        QuickStep,
        Drift,
        Balloon,
        Super,
        BoardTrick
    };

    struct ResultsDescription
    {
        int m_Score{};
        int m_Rank{};
        int m_PerfectRank{};
        int m_NextRankTime{};
        float m_RingProgress{};
        float m_TimeProgress{};
    };

    class ScoreProvider
    {
        inline static int m_CurrentScore{};
        inline static int m_FinalScore{};
        inline static int m_LastCheckpointScore{};
        inline static float m_LastCheckpointSpeed{};
        inline static ResultsDescription m_Results{};

    public:
        static int& __fastcall AddScore(int in_score, bool in_isResult = false);
        static int& __fastcall AddScoreByType(ScoreType in_type);
        static int& __fastcall RemoveScore(int in_score, bool in_isResult = false);
        static int& SetScore(int in_score);

        static int& GetCurrentScore();
        static int& GetFinalScore();
        static int& GetLastCheckpointScore();
        static float& GetLastCheckpointSpeed();
        static RankType GetRank(bool in_isPerfectBonus = false);
        static ResultsDescription& GetResults();

        static void ComputeResults();

        static void Reset(bool in_isUseLastCheckpointScore = false);
    };
}
