#pragma once

#include <string>
#include <unordered_map>

namespace ScoreGenerations
{
    enum class RankType
    {
        E = -1,
        D,
        C,
        B,
        A,
        S
    };

    struct Statistics
    {
        /// <summary>
        /// The total number of rings obtained by the player.
        /// <para>For the current number of rings the player has, use <see cref="RingCount"/>.</para>
        /// </summary>
        int TotalRingCount{};

        /// <summary>
        /// The total number of enemies destroyed by the player.
        /// </summary>
        int TotalEnemies{};

        /// <summary>
        /// The total number of physics objects destroyed by the player.
        /// </summary>
        int TotalPhysics{};

        /// <summary>
        /// The total number of checkpoints passed by the player.
        /// </summary>
        int TotalPointMarkers{};

        /// <summary>
        /// The total number of red rings obtained by the player.
        /// </summary>
        int TotalRedRings{};

        /// <summary>
        /// The total number of rainbow rings passed by the player.
        /// </summary>
        int TotalRainbowRings{};

        /// <summary>
        /// The total number of item boxes obtained by the player.
        /// </summary>
        int TotalItemBoxes{};

        /// <summary>
        /// The total number of super rings obtained by the player.
        /// </summary>
        int TotalSuperRings{};

        /// <summary>
        /// The total number of tricks performed by the player.
        /// </summary>
        int TotalTricks{};

        /// <summary>
        /// The total number of dash rings passed by the player.
        /// </summary>
        int TotalDashRings{};

        /// <summary>
        /// The total number of quick steps performed by the player.
        /// </summary>
        int TotalQuickSteps{};

        /// <summary>
        /// The total number of drifts performed by the player.
        /// </summary>
        int TotalDrifts{};

        /// <summary>
        /// The total number of balloons destroyed by the player.
        /// </summary>
        int TotalBalloons{};

        /// <summary>
        /// The total speed from checkpoints.
        /// </summary>
        float TotalSpeed{};

        /// <summary>
        /// The highest recorded speed from checkpoints.
        /// </summary>
        float HighestSpeed{};

        /// <summary>
        /// The current number of rings obtained by the player.
        /// <para>For the total number of rings obtained in this stage, use <see cref="TotalRingCount"/>.</para>
        /// </summary>
        int RingCount{};

        /// <summary>
        /// The current time on the timer.
        /// </summary>
        float ElapsedTime{};

        /// <summary>
        /// The current minutes on the timer.
        /// </summary>
        int Minutes{};

        /// <summary>
        /// The current seconds on the timer.
        /// </summary>
        int Seconds{};

        /// <summary>
        /// The current milliseconds on the timer.
        /// </summary>
        int Milliseconds{};

        void Reset()
        {
            memset(this, 0, sizeof(this));
        }
    };

    struct ScoreTable
    {
        int Ring{};
        int Enemy{};
        int Physics{};
        int PointMarker{};
        int RedRing{};
        int RainbowRing{};
        int ItemBox{};
        int SuperRing{};
        int TrickFinish{};
        int Trick{};
        int Life{};
        int DashRing{};
        int QuickStep{};
        int Drift{};
        int Balloon{};
        int Super{};
        int BoardTrick{};
    };

    struct RankTable
    {
        int MinSeconds{};
        int MaxSeconds{};
        int S{};
        int A{};
        int B{};
        int C{};
        int D{};
    };

    struct RankTableNode
    {
        const char* pStageID{};
        const RankTable* pRankTable{};

        RankTableNode() {}

        RankTableNode(const char* in_pStageID, const RankTable* in_pRankTable)
            : pStageID(in_pStageID), pRankTable(in_pRankTable) {}
    };

    struct BonusTable
    {
        int HomingChainBonus{};
        int HomingChainBonusLimit{};
        int SlamBonus{};
        int SlamBonusLimit{};
        int TrickBonusLimit{};
        const char* pTimeBonusExpression{};
        const char* pRingBonusExpression{};
        const char* pSpeedBonusExpression{};
        const char* pUserExpression{};
    };

    struct MultiplierTable
    {
        float HomingChainMultiplier{};
        float SlamMultiplier{};
        float TrickMultiplier{};
        float SpeedBonusMultiplier{};
    };

    struct TimerTable
    {
        float SuperSonicTimer{};
        float SlamTimer{};
    };

    typedef std::unordered_map<std::string, RankTable> RankTableMap_t;
};