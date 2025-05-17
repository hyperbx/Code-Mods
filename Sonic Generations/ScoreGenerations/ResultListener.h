#pragma once

class ResultListener
{
public:
    /// <summary>
    /// Index-based ranks.
    /// </summary>
    enum RankType
    {
        E = -1,
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
    static RankType Rank(bool perfect = false);

    /// <summary>
    /// Computes the progress the results bars should land on.
    /// </summary>
    static std::tuple<float, float> ComputeProgressBars(RankType rank);

    /// <summary>
    /// Gathers the final results.
    /// </summary>
    static void Result();

    /// <summary>
    /// Reverse-engineered struct for the result description - by Sajid and hyperbx.
    /// </summary>
    struct ResultDescription
    {
        /// <summary>
        /// The final score.
        /// </summary>
        int score;

        /// <summary>
        /// The final rank.
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
};

