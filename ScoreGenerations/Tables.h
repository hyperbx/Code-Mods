#pragma once

class Tables
{
public:
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

        static ScoreTable GetScore()
        {
            ScoreTable scoreTable;

            // Use the current configuration to get the score for objects.
            scoreTable.Ring = Configuration::config.GetInteger("Score", "Ring", Tables::scoreTable.Ring);
            scoreTable.Enemy = Configuration::config.GetInteger("Score", "Enemy", Tables::scoreTable.Enemy);
            scoreTable.Physics = Configuration::config.GetInteger("Score", "Physics", Tables::scoreTable.Physics);
            scoreTable.PointMarker = Configuration::config.GetInteger("Score", "PointMarker", Tables::scoreTable.PointMarker);
            scoreTable.RedRing = Configuration::config.GetInteger("Score", "RedRing", Tables::scoreTable.RedRing);
            scoreTable.RainbowRing = Configuration::config.GetInteger("Score", "RainbowRing", Tables::scoreTable.RainbowRing);
            scoreTable.ItemBox = Configuration::config.GetInteger("Score", "ItemBox", Tables::scoreTable.ItemBox);
            scoreTable.SuperRing = Configuration::config.GetInteger("Score", "SuperRing", Tables::scoreTable.SuperRing);
            scoreTable.TrickFinish = Configuration::config.GetInteger("Score", "TrickFinish", Tables::scoreTable.TrickFinish);
            scoreTable.Trick = Configuration::config.GetInteger("Score", "Trick", Tables::scoreTable.Trick);
            scoreTable.Life = Configuration::config.GetInteger("Score", "Life", Tables::scoreTable.Life);
            scoreTable.DashRing = Configuration::config.GetInteger("Score", "DashRing", Tables::scoreTable.DashRing);
            scoreTable.QuickStep = Configuration::config.GetInteger("Score", "QuickStep", Tables::scoreTable.QuickStep);
            scoreTable.Drift = Configuration::config.GetInteger("Score", "Drift", Tables::scoreTable.Drift);
            scoreTable.Balloon = Configuration::config.GetInteger("Score", "Balloon", Tables::scoreTable.Balloon);
            scoreTable.Super = Configuration::config.GetInteger("Score", "Super", Tables::scoreTable.Super);
            scoreTable.BoardTrick = Configuration::config.GetInteger("Score", "BoardTrick", Tables::scoreTable.BoardTrick);

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
    };

    static ScoreTable scoreTable;

    /// <summary>
    /// Table of ranks defined in the mod configuration.
    /// </summary>
    struct RankTable
    {
        // Time in seconds required for bonuses.
        int minSeconds = 0;
        int maxSeconds = 0;

        // Score required for ranks.
        int A = 0;
        int B = 0;
        int C = 0;

        /// <summary>
        /// Gets the ranks from the current configurations.
        /// </summary>
        static void GetRanks()
        {
            for (auto& section : Configuration::config.Sections())
            {
                RankTable rankTable;

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
    };

    static unordered_map<string, RankTable> rankTables;

    struct BonusTable
    {
        // Algorithms for calculating bonuses.
        int homingChainBonus;
        string timeBonusAlgorithm;
        string ringBonusAlgorithm;
        string speedBonusAlgorithm;

        static BonusTable GetBonuses()
        {
            BonusTable bonusTable;

            // Use the current configuration to get the bonuses.
            bonusTable.homingChainBonus = Configuration::config.GetInteger("Bonus", "homingChainBonus", Tables::bonusTable.homingChainBonus);
            bonusTable.timeBonusAlgorithm = Configuration::config.Get("Bonus", "timeBonusAlgorithm", Tables::bonusTable.timeBonusAlgorithm);
            bonusTable.ringBonusAlgorithm = Configuration::config.Get("Bonus", "ringBonusAlgorithm", Tables::bonusTable.ringBonusAlgorithm);
            bonusTable.speedBonusAlgorithm = Configuration::config.Get("Bonus", "speedBonusAlgorithm", Tables::bonusTable.speedBonusAlgorithm);

#if _DEBUG
            printf("[Score Generations] homingChainBonus = %d\n", bonusTable.homingChainBonus);
            printf("[Score Generations] timeBonusAlgorithm = %s\n", bonusTable.timeBonusAlgorithm.c_str());
            printf("[Score Generations] ringBonusAlgorithm = %s\n", bonusTable.ringBonusAlgorithm.c_str());
            printf("[Score Generations] speedBonusAlgorithm = %s\n", bonusTable.speedBonusAlgorithm.c_str());
#endif

            return bonusTable;
        }
    };

    static BonusTable bonusTable;

    struct MultiplierTable
    {
        // Multipliers for certain conditions.
        int homingChainMultiplier = 0;

        static MultiplierTable GetMultipliers()
        {
            MultiplierTable multiplierTable;

            multiplierTable.homingChainMultiplier = Configuration::config.GetInteger("Multiplier", "homingChainMultiplier", Tables::multiplierTable.homingChainMultiplier);

#if _DEBUG
            printf("[Score Generations] homingChainMultiplier = %d\n", multiplierTable.homingChainMultiplier);
#endif

            return multiplierTable;
        }
    };

    static MultiplierTable multiplierTable;
};