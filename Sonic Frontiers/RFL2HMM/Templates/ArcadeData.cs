using System.Numerics;
using System.Runtime.InteropServices;

public class ArcadeDataClass
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

    [StructLayout(LayoutKind.Explicit, Size = 828)]
    public struct ArcadeData
    {
        [FieldOffset(0)]   public HeaderData header;
        [FieldOffset(40)]  public bool unlocked;
        [FieldOffset(44)]  public CyberStageContainerData stages;
        [FieldOffset(812)] public uint reserved__arr0;
        [FieldOffset(816)] public uint reserved__arr1;
        [FieldOffset(820)] public uint reserved__arr2;
        [FieldOffset(824)] public uint reserved__arr3;
    }

}