#pragma once

class ScoreListener
{
public:
    /// <summary>
    /// Index-based score type - makes things easier when rewarding score in other classes.
    /// </summary>
    enum Object
    {
        Ring,
        Enemy,
        Physics,
        PointMarker,
        RedRing,
        RainbowRing,
        ItemBox,
        SuperRing,
        TrickRamp, // TODO: implement.
        Tricks,    // TODO: implement.
        Life       // TODO: implement.
    };

    static void Reset();
    static void Bonus();
    static void __fastcall Reward(Object type);

    /// <summary>
    /// Score calculated locally.
    /// </summary>
    static unsigned int score;

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
        int TrickRamp = 0;
        int Tricks = 0;
        int Life = 0;

        static ScoreTable GetScore()
        {
            ScoreTable scoreTable;

            // Use the current configuration to get the score for objects.
            scoreTable.Ring        = Configuration::config.GetInteger("Object", "Ring", 0);
            scoreTable.Enemy       = Configuration::config.GetInteger("Object", "Enemy", 0);
            scoreTable.Physics     = Configuration::config.GetInteger("Object", "Physics", 0);
            scoreTable.PointMarker = Configuration::config.GetInteger("Object", "PointMarker", 0);
            scoreTable.RedRing     = Configuration::config.GetInteger("Object", "RedRing", 0);
            scoreTable.RainbowRing = Configuration::config.GetInteger("Object", "RainbowRing", 0);
            scoreTable.ItemBox     = Configuration::config.GetInteger("Object", "ItemBox", 0);
            scoreTable.SuperRing   = Configuration::config.GetInteger("Object", "SuperRing", 0);
            scoreTable.TrickRamp   = Configuration::config.GetInteger("Object", "TrickRamp", 0);
            scoreTable.Life        = Configuration::config.GetInteger("Object", "Life", 0);

#if _DEBUG
            printf("[Score Generations] Ring = %d\n", scoreTable.Ring);
            printf("[Score Generations] Enemy = %d\n", scoreTable.Enemy);
            printf("[Score Generations] Physics = %d\n", scoreTable.Physics);
            printf("[Score Generations] PointMarker = %d\n", scoreTable.PointMarker);
            printf("[Score Generations] RedRing = %d\n", scoreTable.RedRing);
            printf("[Score Generations] RainbowRing = %d\n", scoreTable.RainbowRing);
            printf("[Score Generations] ItemBox = %d\n", scoreTable.ItemBox);
            printf("[Score Generations] SuperRing = %d\n", scoreTable.SuperRing);
            printf("[Score Generations] TrickRamp = %d\n", scoreTable.TrickRamp);
            printf("[Score Generations] Life = %d\n", scoreTable.Life);
#endif

            return scoreTable;
        }
    };

    static ScoreTable scoreTable;

    struct BonusTable
    {
        // Multipliers for bonus algorithms.
        int timeBonus = 0;
        int ringBonus = 0;
        int speedBonus = 0;

        static BonusTable GetBonuses()
        {
            BonusTable bonusTable;

            // Use the current configuration to get the bonuses.
            bonusTable.timeBonus  = Configuration::config.GetInteger("Bonus", "timeBonus", -1);
            bonusTable.ringBonus  = Configuration::config.GetInteger("Bonus", "ringBonus", -1);
            bonusTable.speedBonus = Configuration::config.GetInteger("Bonus", "speedBonus", -1);

#if _DEBUG
            printf("[Score Generations] timeBonus = %d\n", bonusTable.timeBonus);
            printf("[Score Generations] ringBonus = %d\n", bonusTable.ringBonus);
            printf("[Score Generations] speedBonus = %d\n", bonusTable.speedBonus);
#endif

            return bonusTable;
        }
    };

    static BonusTable bonusTable;

    /// <summary>
    /// Table of ranks defined in the mod configuration.
    /// </summary>
    struct RankTable
    {
        // Score required for ranks.
        int S = 0;
        int A = 0;
        int B = 0;
        int C = 0;
        int D = 0;

        /// <summary>
        /// Gets the ranks from the current configuration.
        /// </summary>
        static RankTable GetRanks()
        {
            RankTable rankTable;

            // Use the current stage ID to get the ranks as strings.
            rankTable.S = Configuration::config.GetInteger(StateHooks::stageID, "S", 0);
            rankTable.A = Configuration::config.GetInteger(StateHooks::stageID, "A", 0);
            rankTable.B = Configuration::config.GetInteger(StateHooks::stageID, "B", 0);
            rankTable.C = Configuration::config.GetInteger(StateHooks::stageID, "C", 0);
            rankTable.D = Configuration::config.GetInteger(StateHooks::stageID, "D", 0);

#if _DEBUG
            printf("[Score Generations] S = %d\n", rankTable.S);
            printf("[Score Generations] A = %d\n", rankTable.A);
            printf("[Score Generations] B = %d\n", rankTable.B);
            printf("[Score Generations] C = %d\n", rankTable.C);
            printf("[Score Generations] D = %d\n", rankTable.D);
#endif

            return rankTable;
        }
    };

    static RankTable rankTable;
};