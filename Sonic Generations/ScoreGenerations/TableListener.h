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
        Tables::ScoreTable scoreTable;

        // Use the current configuration to get the score for objects.
        scoreTable.Ring = Configuration::config.GetInteger("Score", "Ring", scoreTable.Ring);
        scoreTable.Enemy = Configuration::config.GetInteger("Score", "Enemy", scoreTable.Enemy);
        scoreTable.Physics = Configuration::config.GetInteger("Score", "Physics", scoreTable.Physics);
        scoreTable.PointMarker = Configuration::config.GetInteger("Score", "PointMarker", scoreTable.PointMarker);
        scoreTable.RedRing = Configuration::config.GetInteger("Score", "RedRing", scoreTable.RedRing);
        scoreTable.RainbowRing = Configuration::config.GetInteger("Score", "RainbowRing", scoreTable.RainbowRing);
        scoreTable.ItemBox = Configuration::config.GetInteger("Score", "ItemBox", scoreTable.ItemBox);
        scoreTable.SuperRing = Configuration::config.GetInteger("Score", "SuperRing", scoreTable.SuperRing);
        scoreTable.TrickFinish = Configuration::config.GetInteger("Score", "TrickFinish", scoreTable.TrickFinish);
        scoreTable.Trick = Configuration::config.GetInteger("Score", "Trick", scoreTable.Trick);
        scoreTable.Life = Configuration::config.GetInteger("Score", "Life", scoreTable.Life);
        scoreTable.DashRing = Configuration::config.GetInteger("Score", "DashRing", scoreTable.DashRing);
        scoreTable.QuickStep = Configuration::config.GetInteger("Score", "QuickStep", scoreTable.QuickStep);
        scoreTable.Drift = Configuration::config.GetInteger("Score", "Drift", scoreTable.Drift);
        scoreTable.Balloon = Configuration::config.GetInteger("Score", "Balloon", scoreTable.Balloon);
        scoreTable.Super = Configuration::config.GetInteger("Score", "Super", scoreTable.Super);
        scoreTable.BoardTrick = Configuration::config.GetInteger("Score", "BoardTrick", scoreTable.BoardTrick);

#if _DEBUG
        printf("[Score Generations] Ring = %d\n", scoreTable.Ring);
        printf("[Score Generations] Enemy = %d\n", scoreTable.Enemy);
        printf("[Score Generations] Physics = %d\n", scoreTable.Physics);
        printf("[Score Generations] PointMarker = %d\n", scoreTable.PointMarker);
        printf("[Score Generations] RedRing = %d\n", scoreTable.RedRing);
        printf("[Score Generations] RainbowRing = %d\n", scoreTable.RainbowRing);
        printf("[Score Generations] ItemBox = %d\n", scoreTable.ItemBox);
        printf("[Score Generations] SuperRing = %d\n", scoreTable.SuperRing);
        printf("[Score Generations] TrickFinish = %d\n", scoreTable.TrickFinish);
        printf("[Score Generations] Trick = %d\n", scoreTable.Trick);
        printf("[Score Generations] Life = %d\n", scoreTable.Life);
        printf("[Score Generations] DashRing = %d\n", scoreTable.DashRing);
        printf("[Score Generations] QuickStep = %d\n", scoreTable.QuickStep);
        printf("[Score Generations] Drift = %d\n", scoreTable.Drift);
        printf("[Score Generations] Balloon = %d\n", scoreTable.Balloon);
        printf("[Score Generations] Super = %d\n", scoreTable.Balloon);
        printf("[Score Generations] BoardTrick = %d\n", scoreTable.BoardTrick);
#endif

        return scoreTable;
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
                rankTable.A = Configuration::config.GetInteger(section, "A", 50000);
                rankTable.B = Configuration::config.GetInteger(section, "B", 25000);
                rankTable.C = Configuration::config.GetInteger(section, "C", 7500);

#if _DEBUG
                printf("[Score Generations] minSeconds = %d\n", rankTable.minSeconds);
                printf("[Score Generations] maxSeconds = %d\n", rankTable.maxSeconds);
                printf("[Score Generations] A = %d\n", rankTable.A);
                printf("[Score Generations] B = %d\n", rankTable.B);
                printf("[Score Generations] C = %d\n", rankTable.C);
#endif

                // Section without the hash is the stage ID.
                string sectionStageID = section.substr(1);

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
        Tables::BonusTable bonusTable;

        // Use the current configuration to get the bonuses.
        bonusTable.homingChainBonus = Configuration::config.GetInteger("GameplayBonus", "homingChainBonus", bonusTable.homingChainBonus);
        bonusTable.homingChainBonusLimit = Configuration::config.GetInteger("GameplayBonus", "homingChainBonusLimit", bonusTable.homingChainBonusLimit);
        bonusTable.slamBonus = Configuration::config.GetInteger("GameplayBonus", "slamBonus", bonusTable.slamBonus);
        bonusTable.slamBonusLimit = Configuration::config.GetInteger("GameplayBonus", "slamBonusLimit", bonusTable.slamBonusLimit);
        bonusTable.timeBonusAlgorithm = Configuration::config.Get("ResultBonus", "timeBonusAlgorithm", bonusTable.timeBonusAlgorithm);
        bonusTable.ringBonusAlgorithm = Configuration::config.Get("ResultBonus", "ringBonusAlgorithm", bonusTable.ringBonusAlgorithm);
        bonusTable.speedBonusAlgorithm = Configuration::config.Get("ResultBonus", "speedBonusAlgorithm", bonusTable.speedBonusAlgorithm);
        bonusTable.userAlgorithm = Configuration::config.Get("ResultBonus", "userAlgorithm", bonusTable.userAlgorithm);

#if _DEBUG
        printf("[Score Generations] homingChainBonus = %d\n", bonusTable.homingChainBonus);
        printf("[Score Generations] homingChainBonusLimit = %d\n", bonusTable.homingChainBonusLimit);
        printf("[Score Generations] slamBonus = %d\n", bonusTable.slamBonus);
        printf("[Score Generations] slamBonusLimit = %d\n", bonusTable.slamBonusLimit);
        printf("[Score Generations] timeBonusAlgorithm = %s\n", bonusTable.timeBonusAlgorithm.c_str());
        printf("[Score Generations] ringBonusAlgorithm = %s\n", bonusTable.ringBonusAlgorithm.c_str());
        printf("[Score Generations] speedBonusAlgorithm = %s\n", bonusTable.speedBonusAlgorithm.c_str());
        printf("[Score Generations] userAlgorithm = %s\n", bonusTable.userAlgorithm.c_str());
#endif

        return bonusTable;
    }

    /// <summary>
    /// Gets the multipliers from the current configuration.
    /// </summary>
    static Tables::MultiplierTable GetMultipliers()
    {
        Tables::MultiplierTable multiplierTable;

        // Use the current configuration to get the multipliers.
        multiplierTable.homingChainMultiplier = Configuration::config.GetInteger("Multiplier", "homingChainMultiplier", multiplierTable.homingChainMultiplier);
        multiplierTable.slamMultiplier = Configuration::config.GetInteger("Multiplier", "slamMultiplier", multiplierTable.slamMultiplier);
        multiplierTable.speedBonusMultiplier = Configuration::config.GetInteger("Multiplier", "speedBonusMultiplier", multiplierTable.speedBonusMultiplier);

#if _DEBUG
        printf("[Score Generations] homingChainMultiplier = %d\n", multiplierTable.homingChainMultiplier);
        printf("[Score Generations] slamMultiplier = %d\n", multiplierTable.slamMultiplier);
        printf("[Score Generations] speedBonusMultiplier = %d\n", multiplierTable.speedBonusMultiplier);
#endif

        return multiplierTable;
    }

    /// <summary>
    /// Gets the timers from the current configuration.
    /// </summary>
    static Tables::TimerTable GetTimers()
    {
        Tables::TimerTable timerTable;

        // Use the current configuration to get the timers.
        timerTable.superSonicTimer = Configuration::config.GetInteger("Timer", "superSonicTimer", timerTable.superSonicTimer);
        timerTable.slamTimer = Configuration::config.GetInteger("Timer", "slamTimer", timerTable.slamTimer);

#if _DEBUG
        printf("[Score Generations] superSonicTimer = %d\n", timerTable.superSonicTimer);
        printf("[Score Generations] slamTimer = %d\n", timerTable.slamTimer);
#endif

        return timerTable;
    }
};

inline Tables::ScoreTable TableListener::scoreTable;
inline std::unordered_map<std::string, Tables::RankTable> TableListener::rankTables;
inline Tables::BonusTable TableListener::bonusTable;
inline Tables::MultiplierTable TableListener::multiplierTable;
inline Tables::TimerTable TableListener::timerTable;