using System.Numerics;
using System.Runtime.InteropServices;

public class ChallengeDataClass
{
    public enum Status : sbyte
    {
        STATUS_ZERO_FILL = 0,
        STATUS_INITIALIZED = 1
    }

    public enum Sequence : sbyte
    {
        Island1 = 0,
        Island2 = 1,
        Island3 = 2,
        Island4 = 3,
        Island5 = 4,
        FinalBossBefore = 5,
        FinalBossAfter = 6
    }

    public enum SaveDataIcon : sbyte
    {
        IconNoData = 0,
        IconIsland1 = 1,
        IconIsland2 = 2,
        IconIsland3 = 3,
        IconIsland4 = 4,
        IconIsland5 = 5,
        IconLastBoss = 6
    }

    public enum AppVersion : byte
    {
        AppVersion_1_10 = 0,
        AppVersion_1_20 = 1,
        AppVersion_1_30 = 2,
        AppVersion_1_40 = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct HeaderData
    {
        [FieldOffset(0)]  public uint signature;
        [FieldOffset(4)]  public byte version;
        [FieldOffset(5)]  public Status status;
        [FieldOffset(6)]  public byte config;
        [FieldOffset(7)]  public Sequence sequence;
        [FieldOffset(8)]  public uint playTime;
        [FieldOffset(12)] public SaveDataIcon icon;
        [FieldOffset(13)] public AppVersion appVersion;
        [FieldOffset(14)] public byte config2;
        [FieldOffset(15)] public byte reserved1;
        [FieldOffset(16)] public uint saveDate;
        [FieldOffset(20)] public byte index;
        [FieldOffset(24)] public uint reserved__arr0;
        [FieldOffset(28)] public uint reserved__arr1;
        [FieldOffset(32)] public uint reserved__arr2;
        [FieldOffset(36)] public uint reserved__arr3;
    }

    public enum Value : sbyte
    {
        S = 0,
        A = 1,
        B = 2,
        C = 3,
        D = 4,
        Num = 5
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct CyberStageData
    {
        [FieldOffset(0)] public ushort flags;
        [FieldOffset(4)] public uint bestTime;
        [FieldOffset(8)] public uint reserved__arr0;
        [FieldOffset(12)] public uint reserved__arr1;
        [FieldOffset(16)] public uint reserved__arr2;
        [FieldOffset(20)] public uint reserved__arr3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 768)]
    public struct CyberStageContainerData
    {
        [FieldOffset(0)] public CyberStageData actStages__arr0;
        [FieldOffset(24)] public CyberStageData actStages__arr1;
        [FieldOffset(48)] public CyberStageData actStages__arr2;
        [FieldOffset(72)] public CyberStageData actStages__arr3;
        [FieldOffset(96)] public CyberStageData actStages__arr4;
        [FieldOffset(120)] public CyberStageData actStages__arr5;
        [FieldOffset(144)] public CyberStageData actStages__arr6;
        [FieldOffset(168)] public CyberStageData actStages__arr7;
        [FieldOffset(192)] public CyberStageData actStages__arr8;
        [FieldOffset(216)] public CyberStageData actStages__arr9;
        [FieldOffset(240)] public CyberStageData actStages__arr10;
        [FieldOffset(264)] public CyberStageData actStages__arr11;
        [FieldOffset(288)] public CyberStageData actStages__arr12;
        [FieldOffset(312)] public CyberStageData actStages__arr13;
        [FieldOffset(336)] public CyberStageData actStages__arr14;
        [FieldOffset(360)] public CyberStageData actStages__arr15;
        [FieldOffset(384)] public CyberStageData actStages__arr16;
        [FieldOffset(408)] public CyberStageData actStages__arr17;
        [FieldOffset(432)] public CyberStageData actStages__arr18;
        [FieldOffset(456)] public CyberStageData actStages__arr19;
        [FieldOffset(480)] public CyberStageData actStages__arr20;
        [FieldOffset(504)] public CyberStageData actStages__arr21;
        [FieldOffset(528)] public CyberStageData actStages__arr22;
        [FieldOffset(552)] public CyberStageData actStages__arr23;
        [FieldOffset(576)] public CyberStageData actStages__arr24;
        [FieldOffset(600)] public CyberStageData actStages__arr25;
        [FieldOffset(624)] public CyberStageData actStages__arr26;
        [FieldOffset(648)] public CyberStageData actStages__arr27;
        [FieldOffset(672)] public CyberStageData actStages__arr28;
        [FieldOffset(696)] public CyberStageData actStages__arr29;
        [FieldOffset(720)] public CyberStageData actStages__arr30;
        [FieldOffset(744)] public CyberStageData actStages__arr31;
    }

    [StructLayout(LayoutKind.Explicit, Size = 908)]
    public struct ChallengeCyberStageData
    {
        [FieldOffset(0)]   public uint status;
        [FieldOffset(4)]   public uint totalBestTime;
        [FieldOffset(8)]   public Value totalBestRank;
        [FieldOffset(12)]  public CyberStageContainerData stages;
        [FieldOffset(780)] public int stageNos__arr0;
        [FieldOffset(784)] public int stageNos__arr1;
        [FieldOffset(788)] public int stageNos__arr2;
        [FieldOffset(792)] public int stageNos__arr3;
        [FieldOffset(796)] public int stageNos__arr4;
        [FieldOffset(800)] public int stageNos__arr5;
        [FieldOffset(804)] public int stageNos__arr6;
        [FieldOffset(808)] public int stageNos__arr7;
        [FieldOffset(812)] public int stageNos__arr8;
        [FieldOffset(816)] public int stageNos__arr9;
        [FieldOffset(820)] public int stageNos__arr10;
        [FieldOffset(824)] public int stageNos__arr11;
        [FieldOffset(828)] public int stageNos__arr12;
        [FieldOffset(832)] public int stageNos__arr13;
        [FieldOffset(836)] public int stageNos__arr14;
        [FieldOffset(840)] public int stageNos__arr15;
        [FieldOffset(844)] public int stageNos__arr16;
        [FieldOffset(848)] public int stageNos__arr17;
        [FieldOffset(852)] public int stageNos__arr18;
        [FieldOffset(856)] public int stageNos__arr19;
        [FieldOffset(860)] public int stageNos__arr20;
        [FieldOffset(864)] public int stageNos__arr21;
        [FieldOffset(868)] public int stageNos__arr22;
        [FieldOffset(872)] public int stageNos__arr23;
        [FieldOffset(876)] public int stageNos__arr24;
        [FieldOffset(880)] public int stageNos__arr25;
        [FieldOffset(884)] public int stageNos__arr26;
        [FieldOffset(888)] public int stageNos__arr27;
        [FieldOffset(892)] public int stageNos__arr28;
        [FieldOffset(896)] public int stageNos__arr29;
        [FieldOffset(900)] public int stageNos__arr30;
        [FieldOffset(904)] public int stageNos__arr31;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4540)]
    public struct ChallengeCyberStageContainerData
    {
        [FieldOffset(0)] public ChallengeCyberStageData stages__arr0;
        [FieldOffset(908)] public ChallengeCyberStageData stages__arr1;
        [FieldOffset(1816)] public ChallengeCyberStageData stages__arr2;
        [FieldOffset(2724)] public ChallengeCyberStageData stages__arr3;
        [FieldOffset(3632)] public ChallengeCyberStageData stages__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct ChallengeBattleRushScoreData
    {
        [FieldOffset(0)]  public uint bestTime;
        [FieldOffset(4)]  public uint reserved0;
        [FieldOffset(8)]  public uint reserved1;
        [FieldOffset(12)] public uint reserved2;
        [FieldOffset(16)] public uint reserved3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 324)]
    public struct ChallengeBattleRushData
    {
        [FieldOffset(0)] public uint status;
        [FieldOffset(4)] public ChallengeBattleRushScoreData scores__arr0;
        [FieldOffset(24)] public ChallengeBattleRushScoreData scores__arr1;
        [FieldOffset(44)] public ChallengeBattleRushScoreData scores__arr2;
        [FieldOffset(64)] public ChallengeBattleRushScoreData scores__arr3;
        [FieldOffset(84)] public ChallengeBattleRushScoreData scores__arr4;
        [FieldOffset(104)] public ChallengeBattleRushScoreData scores__arr5;
        [FieldOffset(124)] public ChallengeBattleRushScoreData scores__arr6;
        [FieldOffset(144)] public ChallengeBattleRushScoreData scores__arr7;
        [FieldOffset(164)] public ChallengeBattleRushScoreData scores__arr8;
        [FieldOffset(184)] public ChallengeBattleRushScoreData scores__arr9;
        [FieldOffset(204)] public ChallengeBattleRushScoreData scores__arr10;
        [FieldOffset(224)] public ChallengeBattleRushScoreData scores__arr11;
        [FieldOffset(244)] public ChallengeBattleRushScoreData scores__arr12;
        [FieldOffset(264)] public ChallengeBattleRushScoreData scores__arr13;
        [FieldOffset(284)] public ChallengeBattleRushScoreData scores__arr14;
        [FieldOffset(304)] public ChallengeBattleRushScoreData scores__arr15;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1296)]
    public struct ChallengeBattleRushContainerData
    {
        [FieldOffset(0)] public ChallengeBattleRushData stages__arr0;
        [FieldOffset(324)] public ChallengeBattleRushData stages__arr1;
        [FieldOffset(648)] public ChallengeBattleRushData stages__arr2;
        [FieldOffset(972)] public ChallengeBattleRushData stages__arr3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 7192)]
    public struct ChallengeData
    {
        [FieldOffset(0)]    public HeaderData header;
        [FieldOffset(40)]   public uint status;
        [FieldOffset(44)]   public ChallengeCyberStageContainerData cyberStage;
        [FieldOffset(4584)] public ChallengeBattleRushContainerData battleRush;
        [FieldOffset(5880)] public ChallengeBattleRushContainerData battleRushAll;
        [FieldOffset(7176)] public uint reserved0;
        [FieldOffset(7180)] public uint reserved1;
        [FieldOffset(7184)] public uint reserved2;
        [FieldOffset(7188)] public uint reserved3;
    }

}