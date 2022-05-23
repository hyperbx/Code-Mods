#pragma once

class TableListener
{
public:
    static Tables::ScoreTable scoreTable;
    static std::unordered_map<std::string, Tables::RankTable> rankTables;
    static Tables::BonusTable bonusTable;
    static Tables::MultiplierTable multiplierTable;
    static Tables::TimerTable timerTable;

    /// <summary>
    /// Gets the score values from the current configuration.
    /// </summary>
    static Tables::ScoreTable GetScore()
    {
        Tables::ScoreTable newScoreTable;

        // Use the current configuration to get the score for objects.
        newScoreTable.Ring        = Configuration::config.GetInteger("Score", "Ring", scoreTable.Ring);
        newScoreTable.Enemy       = Configuration::config.GetInteger("Score", "Enemy", scoreTable.Enemy);
        newScoreTable.Physics     = Configuration::config.GetInteger("Score", "Physics", scoreTable.Physics);
        newScoreTable.PointMarker = Configuration::config.GetInteger("Score", "PointMarker", scoreTable.PointMarker);
        newScoreTable.RedRing     = Configuration::config.GetInteger("Score", "RedRing", scoreTable.RedRing);
        newScoreTable.RainbowRing = Configuration::config.GetInteger("Score", "RainbowRing", scoreTable.RainbowRing);
        newScoreTable.ItemBox     = Configuration::config.GetInteger("Score", "ItemBox", scoreTable.ItemBox);
        newScoreTable.SuperRing   = Configuration::config.GetInteger("Score", "SuperRing", scoreTable.SuperRing);
        newScoreTable.TrickFinish = Configuration::config.GetInteger("Score", "TrickFinish", scoreTable.TrickFinish);
        newScoreTable.Trick       = Configuration::config.GetInteger("Score", "Trick", scoreTable.Trick);
        newScoreTable.Life        = Configuration::config.GetInteger("Score", "Life", scoreTable.Life);
        newScoreTable.DashRing    = Configuration::config.GetInteger("Score", "DashRing", scoreTable.DashRing);
        newScoreTable.QuickStep   = Configuration::config.GetInteger("Score", "QuickStep", scoreTable.QuickStep);
        newScoreTable.Drift       = Configuration::config.GetInteger("Score", "Drift", scoreTable.Drift);
        newScoreTable.Balloon     = Configuration::config.GetInteger("Score", "Balloon", scoreTable.Balloon);
        newScoreTable.Super       = Configuration::config.GetInteger("Score", "Super", scoreTable.Super);
        newScoreTable.BoardTrick  = Configuration::config.GetInteger("Score", "BoardTrick", scoreTable.BoardTrick);

#if _DEBUG
        printf("[Score Generations] Ring = %d\n", newScoreTable.Ring);
        printf("[Score Generations] Enemy = %d\n", newScoreTable.Enemy);
        printf("[Score Generations] Physics = %d\n", newScoreTable.Physics);
        printf("[Score Generations] PointMarker = %d\n", newScoreTable.PointMarker);
        printf("[Score Generations] RedRing = %d\n", newScoreTable.RedRing);
        printf("[Score Generations] RainbowRing = %d\n", newScoreTable.RainbowRing);
        printf("[Score Generations] ItemBox = %d\n", newScoreTable.ItemBox);
        printf("[Score Generations] SuperRing = %d\n", newScoreTable.SuperRing);
        printf("[Score Generations] TrickFinish = %d\n", newScoreTable.TrickFinish);
        printf("[Score Generations] Trick = %d\n", newScoreTable.Trick);
        printf("[Score Generations] Life = %d\n", newScoreTable.Life);
        printf("[Score Generations] DashRing = %d\n", newScoreTable.DashRing);
        printf("[Score Generations] QuickStep = %d\n", newScoreTable.QuickStep);
        printf("[Score Generations] Drift = %d\n", newScoreTable.Drift);
        printf("[Score Generations] Balloon = %d\n", newScoreTable.Balloon);
        printf("[Score Generations] Super = %d\n", newScoreTable.Balloon);
        printf("[Score Generations] BoardTrick = %d\n", newScoreTable.BoardTrick);
#endif

        return newScoreTable;
    }

    /// <summary>
    /// Gets the ranks from the current configurations.
    /// </summary>
    static void GetRanks()
    {
        for (auto& section : Configuration::config.Sections())
        {
            Tables::RankTable rankTable;

            if (section[0] == '#')
            {
                // Use the current stage ID to get the time requirements.
                rankTable.minSeconds = Configuration::config.GetInteger(section, "minSeconds", 0);
                rankTable.maxSeconds = Configuration::config.GetInteger(section, "maxSeconds", 0);

                // Use the current stage ID to get the ranks.
                rankTable.S = Configuration::config.GetInteger(section, "S", -1);
                rankTable.A = Configuration::config.GetInteger(section, "A", -1);
                rankTable.B = Configuration::config.GetInteger(section, "B", -1);
                rankTable.C = Configuration::config.GetInteger(section, "C", -1);
                rankTable.D = Configuration::config.GetInteger(section, "D", -1);

#if _DEBUG
                printf("[Score Generations] minSeconds = %d\n", rankTable.minSeconds);
                printf("[Score Generations] maxSeconds = %d\n", rankTable.maxSeconds);
                printf("[Score Generations] S = %d\n", rankTable.S);
                printf("[Score Generations] A = %d\n", rankTable.A);
                printf("[Score Generations] B = %d\n", rankTable.B);
                printf("[Score Generations] C = %d\n", rankTable.C);
                printf("[Score Generations] D = %d\n", rankTable.D);
#endif

                // Section without the hash is the stage ID.
                std::string sectionStageID = section.substr(1);

                // Remove the current stage ID if it already exists in the rank database.
                if (rankTables.find(sectionStageID) != rankTables.end())
                    rankTables.erase(sectionStageID);

                rankTables.emplace(sectionStageID, rankTable);
            }
        }
    }

    /// <summary>
    /// Gets the bonuses from the current configuration.
    /// </summary>
    static Tables::BonusTable GetBonuses()
    {
        Tables::BonusTable newBonusTable;

        // Use the current configuration to get the bonuses.
        newBonusTable.homingChainBonus      = Configuration::config.GetInteger("GameplayBonus", "homingChainBonus", bonusTable.homingChainBonus);
        newBonusTable.homingChainBonusLimit = Configuration::config.GetInteger("GameplayBonus", "homingChainBonusLimit", bonusTable.homingChainBonusLimit);
        newBonusTable.slamBonus             = Configuration::config.GetInteger("GameplayBonus", "slamBonus", bonusTable.slamBonus);
        newBonusTable.slamBonusLimit        = Configuration::config.GetInteger("GameplayBonus", "slamBonusLimit", bonusTable.slamBonusLimit);
        newBonusTable.trickBonusLimit       = Configuration::config.GetInteger("GameplayBonus", "trickBonusLimit", bonusTable.trickBonusLimit);
        newBonusTable.timeBonusAlgorithm    = Configuration::config.Get("ResultBonus", "timeBonusAlgorithm", bonusTable.timeBonusAlgorithm);
        newBonusTable.ringBonusAlgorithm    = Configuration::config.Get("ResultBonus", "ringBonusAlgorithm", bonusTable.ringBonusAlgorithm);
        newBonusTable.speedBonusAlgorithm   = Configuration::config.Get("ResultBonus", "speedBonusAlgorithm", bonusTable.speedBonusAlgorithm);
        newBonusTable.userAlgorithm         = Configuration::config.Get("ResultBonus", "userAlgorithm", bonusTable.userAlgorithm);

#if _DEBUG
        printf("[Score Generations] homingChainBonus = %d\n", newBonusTable.homingChainBonus);
        printf("[Score Generations] homingChainBonusLimit = %d\n", newBonusTable.homingChainBonusLimit);
        printf("[Score Generations] slamBonus = %d\n", newBonusTable.slamBonus);
        printf("[Score Generations] slamBonusLimit = %d\n", newBonusTable.slamBonusLimit);
        printf("[Score Generations] timeBonusAlgorithm = %s\n", newBonusTable.timeBonusAlgorithm.c_str());
        printf("[Score Generations] ringBonusAlgorithm = %s\n", newBonusTable.ringBonusAlgorithm.c_str());
        printf("[Score Generations] speedBonusAlgorithm = %s\n", newBonusTable.speedBonusAlgorithm.c_str());
        printf("[Score Generations] userAlgorithm = %s\n", newBonusTable.userAlgorithm.c_str());
#endif

        return newBonusTable;
    }

    /// <summary>
    /// Gets the multipliers from the current configuration.
    /// </summary>
    static Tables::MultiplierTable GetMultipliers()
    {
        Tables::MultiplierTable newMultiplierTable;

        // Use the current configuration to get the multipliers.
        newMultiplierTable.homingChainMultiplier = Configuration::config.GetReal("Multiplier", "homingChainMultiplier", multiplierTable.homingChainMultiplier);
        newMultiplierTable.slamMultiplier        = Configuration::config.GetReal("Multiplier", "slamMultiplier", multiplierTable.slamMultiplier);
        newMultiplierTable.trickMultiplier       = Configuration::config.GetReal("Multiplier", "trickMultiplier", multiplierTable.trickMultiplier);
        newMultiplierTable.speedBonusMultiplier  = Configuration::config.GetReal("Multiplier", "speedBonusMultiplier", multiplierTable.speedBonusMultiplier);

#if _DEBUG
        printf("[Score Generations] homingChainMultiplier = %d\n", newMultiplierTable.homingChainMultiplier);
        printf("[Score Generations] slamMultiplier = %d\n", newMultiplierTable.slamMultiplier);
        printf("[Score Generations] trickMultiplier = %d\n", newMultiplierTable.trickMultiplier);
        printf("[Score Generations] speedBonusMultiplier = %d\n", newMultiplierTable.speedBonusMultiplier);
#endif

        return newMultiplierTable;
    }

    /// <summary>
    /// Gets the timers from the current configuration.
    /// </summary>
    static Tables::TimerTable GetTimers()
    {
        Tables::TimerTable newTimerTable;

        // Use the current configuration to get the timers.
        newTimerTable.superSonicTimer = Configuration::config.GetReal("Timer", "superSonicTimer", timerTable.superSonicTimer);
        newTimerTable.slamTimer       = Configuration::config.GetReal("Timer", "slamTimer", timerTable.slamTimer);

#if _DEBUG
        printf("[Score Generations] superSonicTimer = %d\n", newTimerTable.superSonicTimer);
        printf("[Score Generations] slamTimer = %d\n", newTimerTable.slamTimer);
#endif

        return newTimerTable;
    }
};

inline Tables::ScoreTable TableListener::scoreTable;
inline std::unordered_map<std::string, Tables::RankTable> TableListener::rankTables;
inline Tables::BonusTable TableListener::bonusTable;
inline Tables::MultiplierTable TableListener::multiplierTable;
inline Tables::TimerTable TableListener::timerTable;