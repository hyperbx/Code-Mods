using System.Numerics;
using System.Runtime.InteropServices;

public class BattleRushParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct BattleRushPhaseRankParameter
    {
        [FieldOffset(0)]  public uint rankTime__arr0;
        [FieldOffset(4)] public uint rankTime__arr1;
        [FieldOffset(8)] public uint rankTime__arr2;
        [FieldOffset(12)] public uint rankTime__arr3;
        [FieldOffset(16)] public uint rankTimeAll__arr0;
        [FieldOffset(20)] public uint rankTimeAll__arr1;
        [FieldOffset(24)] public uint rankTimeAll__arr2;
        [FieldOffset(28)] public uint rankTimeAll__arr3;
    }

    public enum BgmType : sbyte
    {
        INVALID = -1,
        ENEMY_BATTLE = 0,
        FORCE_BATTLE_FIELD = 1,
        MINIBOSS_CHARGER_BATTLE = 2,
        MINIBOSS_DARUMA_BATTLE = 3,
        MINIBOSS_SPIDER_BATTLE = 4,
        MINIBOSS_BLADE_BATTLE = 5,
        MINIBOSS_FLYER_BATTLE = 6,
        MINIBOSS_TRACKER_BATTLE = 7,
        MINIBOSS_ASHURA_BATTLE = 8,
        MINIBOSS_SKIER_BATTLE = 9,
        MINIBOSS_SUMO_BATTLE = 10,
        MINIBOSS_TYRANT_BATTLE = 11,
        MINIBOSS_STRIDER_BATTLE = 12,
        MINIBOSS_WARSHIP_BATTLE = 13,
        ENEMY_AQUABALL = 14,
        TUTORIAL_BLADE_BATTLE = 15
    }

    [StructLayout(LayoutKind.Explicit, Size = 508)]
    public struct BattleRushStageParameter
    {
        [FieldOffset(0)]   public uint numPhases;
        [FieldOffset(4)]   public float phaseLimitTime__arr0;
        [FieldOffset(8)] public float phaseLimitTime__arr1;
        [FieldOffset(12)] public float phaseLimitTime__arr2;
        [FieldOffset(16)] public float phaseLimitTime__arr3;
        [FieldOffset(20)] public float phaseLimitTime__arr4;
        [FieldOffset(24)] public float phaseLimitTime__arr5;
        [FieldOffset(28)] public float phaseLimitTime__arr6;
        [FieldOffset(32)] public float phaseLimitTime__arr7;
        [FieldOffset(36)] public float phaseLimitTime__arr8;
        [FieldOffset(40)] public float phaseLimitTime__arr9;
        [FieldOffset(44)] public float phaseLimitTime__arr10;
        [FieldOffset(48)]  public float phaseClearedTime__arr0;
        [FieldOffset(52)] public float phaseClearedTime__arr1;
        [FieldOffset(56)] public float phaseClearedTime__arr2;
        [FieldOffset(60)] public float phaseClearedTime__arr3;
        [FieldOffset(64)] public float phaseClearedTime__arr4;
        [FieldOffset(68)] public float phaseClearedTime__arr5;
        [FieldOffset(72)] public float phaseClearedTime__arr6;
        [FieldOffset(76)] public float phaseClearedTime__arr7;
        [FieldOffset(80)] public float phaseClearedTime__arr8;
        [FieldOffset(84)] public float phaseClearedTime__arr9;
        [FieldOffset(88)] public float phaseClearedTime__arr10;
        [FieldOffset(92)]  public float phaseResultTime__arr0;
        [FieldOffset(96)] public float phaseResultTime__arr1;
        [FieldOffset(100)] public float phaseResultTime__arr2;
        [FieldOffset(104)] public float phaseResultTime__arr3;
        [FieldOffset(108)] public float phaseResultTime__arr4;
        [FieldOffset(112)] public float phaseResultTime__arr5;
        [FieldOffset(116)] public float phaseResultTime__arr6;
        [FieldOffset(120)] public float phaseResultTime__arr7;
        [FieldOffset(124)] public float phaseResultTime__arr8;
        [FieldOffset(128)] public float phaseResultTime__arr9;
        [FieldOffset(132)] public float phaseResultTime__arr10;
        [FieldOffset(136)] public BattleRushPhaseRankParameter phaseRank__arr0;
        [FieldOffset(168)] public BattleRushPhaseRankParameter phaseRank__arr1;
        [FieldOffset(200)] public BattleRushPhaseRankParameter phaseRank__arr2;
        [FieldOffset(232)] public BattleRushPhaseRankParameter phaseRank__arr3;
        [FieldOffset(264)] public BattleRushPhaseRankParameter phaseRank__arr4;
        [FieldOffset(296)] public BattleRushPhaseRankParameter phaseRank__arr5;
        [FieldOffset(328)] public BattleRushPhaseRankParameter phaseRank__arr6;
        [FieldOffset(360)] public BattleRushPhaseRankParameter phaseRank__arr7;
        [FieldOffset(392)] public BattleRushPhaseRankParameter phaseRank__arr8;
        [FieldOffset(424)] public BattleRushPhaseRankParameter phaseRank__arr9;
        [FieldOffset(456)] public BattleRushPhaseRankParameter phaseRank__arr10;
        [FieldOffset(488)] public BgmType phaseBgmType__arr0;
        [FieldOffset(489)] public BgmType phaseBgmType__arr1;
        [FieldOffset(490)] public BgmType phaseBgmType__arr2;
        [FieldOffset(491)] public BgmType phaseBgmType__arr3;
        [FieldOffset(492)] public BgmType phaseBgmType__arr4;
        [FieldOffset(493)] public BgmType phaseBgmType__arr5;
        [FieldOffset(494)] public BgmType phaseBgmType__arr6;
        [FieldOffset(495)] public BgmType phaseBgmType__arr7;
        [FieldOffset(496)] public BgmType phaseBgmType__arr8;
        [FieldOffset(497)] public BgmType phaseBgmType__arr9;
        [FieldOffset(498)] public BgmType phaseBgmType__arr10;
        [FieldOffset(500)] public uint hour;
        [FieldOffset(504)] public uint minute;
    }

    [StructLayout(LayoutKind.Explicit, Size = 2036)]
    public struct BattleRushParameter
    {
        [FieldOffset(0)]    public BattleRushStageParameter stages__arr0;
        [FieldOffset(508)] public BattleRushStageParameter stages__arr1;
        [FieldOffset(1016)] public BattleRushStageParameter stages__arr2;
        [FieldOffset(1524)] public BattleRushStageParameter stages__arr3;
        [FieldOffset(2032)] public float viewPaseResultTime;
    }

}