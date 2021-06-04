#pragma once

class ResultListener
{
public:
    /// <summary>
    /// Index-based ranks.
    /// </summary>
    enum RankType
    {
        D,
        C,
        B,
        A,
        S
    };

    /// <summary>
    /// Calculates the bonuses and adds them to the total score.
    /// </summary>
    static void Bonus();

    /// <summary>
    /// Calculates the rank using the total score.
    /// </summary>
    static ResultListener::RankType Rank();

    /// <summary>
    /// Gathers the final results.
    /// </summary>
    static void Result();

    /// <summary>
    /// Reverse-engineered struct for the result description - by Sajid and HyperBE32.
    /// </summary>
    struct ResultDescription
    {
        /// <summary>
        /// The final score.
        /// </summary>
        int score;

        /// <summary>
        /// 0 - D rank
        /// 1 - C rank
        /// 2 - B rank
        /// 3 - A rank
        /// 4 - S rank
        /// </summary>
        int rank;

        /// <summary>
        /// The rank rewarded for getting the perfect bonus.
        /// </summary>
        int perfectRank;

        /// <summary>
        /// The amount of time in milliseconds required to get the next rank.
        /// </summary>
        int nextRankTime;

        /// <summary>
        /// The amount of progress related to rings in the progress bar between 0.0 - 1.0.
        /// </summary>
        float ringProgress;

        /// <summary>
        /// The amount of progress related to score in the progress bar between 0.0 - 1.0.
        /// </summary>
        float scoreProgress;
    };

    /// <summary>
    /// Table used for showing the final results.
    /// </summary>
    static ResultDescription resultDescription;

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
        string timeBonusAlgorithm;
        string ringBonusAlgorithm;
        string speedBonusAlgorithm;

        static BonusTable GetBonuses()
        {
            BonusTable bonusTable;

            // Use the current configuration to get the bonuses.
            bonusTable.timeBonusAlgorithm = Configuration::config.Get("Bonus", "timeBonusAlgorithm", "");
            bonusTable.ringBonusAlgorithm = Configuration::config.Get("Bonus", "ringBonusAlgorithm", "");
            bonusTable.speedBonusAlgorithm = Configuration::config.Get("Bonus", "speedBonusAlgorithm", "");

#if _DEBUG
            printf("[Score Generations] timeBonusAlgorithm = %s\n", bonusTable.timeBonusAlgorithm.c_str());
            printf("[Score Generations] ringBonusAlgorithm = %s\n", bonusTable.ringBonusAlgorithm.c_str());
            printf("[Score Generations] speedBonusAlgorithm = %s\n", bonusTable.speedBonusAlgorithm.c_str());
#endif

            return bonusTable;
        }
    };

    static BonusTable bonusTable;
};

