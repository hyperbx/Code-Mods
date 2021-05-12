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
        Object,
        PointMarker,
        RedRing,
        RainbowRing,
        ItemBox,
        SuperRing
    };

    static void Reset();
    static void Bonus();
    static void __fastcall Reward(ScoreType id);

    /// <summary>
    /// Score calculated locally.
    /// </summary>
    static unsigned int score;
};