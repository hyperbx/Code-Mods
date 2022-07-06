#pragma once

class ScoreListener
{
public:
    /// <summary>
    /// Index-based score type - makes things easier when rewarding score in other classes.
    /// </summary>
    enum ScoreType
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

    /// <summary>
    /// Resets all statistics used for score calculation.
    /// </summary>
    static void Reset(bool useLastCheckpointScore = false);

    /// <summary>
    /// Adds the input score to reward and clamps it to the maximum allowed.
    /// </summary>
    static void AddClamp(int& score, int scoreToReward, bool timeout = true);

    /// <summary>
    /// Rewards the player with score based on the input type.
    /// </summary>
    static void __fastcall Reward(ScoreType type);

    /// <summary>
    /// Score calculated locally.
    /// </summary>
    static int score;

    /// <summary>
    /// Score calculated at the results screen.
    /// </summary>
    static int totalScore;

    /// <summary>
    /// The last score calculated before a checkpoint was hit.
    /// </summary>
    static int lastCheckpointScore;

    /// <summary>
    /// The last velocity logged when a checkpoint was hit.
    /// </summary>
    static float lastCheckpointVelocity;
};