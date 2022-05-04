#pragma once

// Standard library
#include <string>
#include <unordered_map>

class Tables
{
public:
    /// <summary>
    /// Table of score values defined in the mod configuration.
    /// </summary>
    struct ScoreTable
    {
        // Score rewarded for objects.
        int Ring = 0;
        int Enemy = 0;
        int Physics = 0;
        int PointMarker = 0;
        int RedRing = 0;
        int RainbowRing = 0;
        int ItemBox = 0;
        int SuperRing = 0;
        int TrickFinish = 0;
        int Trick = 0;
        int Life = 0;
        int DashRing = 0;
        int QuickStep = 0;
        int Drift = 0;
        int Balloon = 0;
        int Super = 0;
        int BoardTrick = 0;
    };

    /// <summary>
    /// Table of ranks defined in the mod configuration.
    /// </summary>
    struct RankTable
    {
        // Time in seconds required for bonuses.
        int minSeconds = 0;
        int maxSeconds = 0;

        // Score required for ranks.
        int S = 0;
        int A = 0;
        int B = 0;
        int C = 0;
    };

    /// <summary>
    /// Table of bonuses defined in the mod configuration.
    /// </summary>
    struct BonusTable
    {
        int homingChainBonus = 0;
        int homingChainBonusLimit = 0;
        int slamBonus = 0;
        int slamBonusLimit = 0;
        int trickBonusLimit = 0;
        std::string timeBonusAlgorithm;
        std::string ringBonusAlgorithm;
        std::string speedBonusAlgorithm;
        std::string userAlgorithm;
    };

    /// <summary>
    /// Table of multipliers defined in the mod configuration.
    /// </summary>
    struct MultiplierTable
    {
        float homingChainMultiplier = 0;
        float slamMultiplier = 0;
        float trickMultiplier = 0;
        float speedBonusMultiplier = 0;
    };

    /// <summary>
    /// Table of timers defined in the mod configuration.
    /// </summary>
    struct TimerTable
    {
        float superSonicTimer = 0;
        float slamTimer = 0;
    };
};
