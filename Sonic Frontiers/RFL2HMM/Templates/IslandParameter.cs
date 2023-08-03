using System.Numerics;
using System.Runtime.InteropServices;

public class IslandParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 2)]
    public struct ChaosEmeraldStorageParam
    {
        [FieldOffset(0)] public bool isEnable;
        [FieldOffset(1)] public sbyte useKeyNum;
    }

    [StructLayout(LayoutKind.Explicit, Size = 14)]
    public struct IslandParam
    {
        [FieldOffset(0)] public ChaosEmeraldStorageParam storages__arr0;
        [FieldOffset(2)] public ChaosEmeraldStorageParam storages__arr1;
        [FieldOffset(4)] public ChaosEmeraldStorageParam storages__arr2;
        [FieldOffset(6)] public ChaosEmeraldStorageParam storages__arr3;
        [FieldOffset(8)] public ChaosEmeraldStorageParam storages__arr4;
        [FieldOffset(10)] public ChaosEmeraldStorageParam storages__arr5;
        [FieldOffset(12)] public ChaosEmeraldStorageParam storages__arr6;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct KodamaCommonParam
    {
        [FieldOffset(0)]  public float takableRange;
        [FieldOffset(4)]  public float fadeTime;
        [FieldOffset(8)]  public float chestJumpOutFadeTime;
        [FieldOffset(12)] public float tutorialDelayTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct KodamaFollowParam
    {
        [FieldOffset(0)]  public sbyte maxFollowNum;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float rotateSpeed;
        [FieldOffset(12)] public float stopDistance;
        [FieldOffset(16)] public float vanishDistance;
        [FieldOffset(20)] public float respawnStandTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct KodamaNormalParam
    {
        [FieldOffset(0)]  public KodamaCommonParam common;
        [FieldOffset(16)] public KodamaFollowParam follow;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct KodamaElderParam
    {
        [FieldOffset(0)] public int levelupKodamaNum__arr0;
        [FieldOffset(4)] public int levelupKodamaNum__arr1;
        [FieldOffset(8)] public int levelupKodamaNum__arr2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct KodamaHermitLvUpParam
    {
        [FieldOffset(0)] public int difficulty__arr0;
        [FieldOffset(4)] public int difficulty__arr1;
        [FieldOffset(8)] public int difficulty__arr2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1188)]
    public struct KodamaHermitParam
    {
        [FieldOffset(0)] public KodamaHermitLvUpParam levelupSeedNum__arr0;
        [FieldOffset(12)] public KodamaHermitLvUpParam levelupSeedNum__arr1;
        [FieldOffset(24)] public KodamaHermitLvUpParam levelupSeedNum__arr2;
        [FieldOffset(36)] public KodamaHermitLvUpParam levelupSeedNum__arr3;
        [FieldOffset(48)] public KodamaHermitLvUpParam levelupSeedNum__arr4;
        [FieldOffset(60)] public KodamaHermitLvUpParam levelupSeedNum__arr5;
        [FieldOffset(72)] public KodamaHermitLvUpParam levelupSeedNum__arr6;
        [FieldOffset(84)] public KodamaHermitLvUpParam levelupSeedNum__arr7;
        [FieldOffset(96)] public KodamaHermitLvUpParam levelupSeedNum__arr8;
        [FieldOffset(108)] public KodamaHermitLvUpParam levelupSeedNum__arr9;
        [FieldOffset(120)] public KodamaHermitLvUpParam levelupSeedNum__arr10;
        [FieldOffset(132)] public KodamaHermitLvUpParam levelupSeedNum__arr11;
        [FieldOffset(144)] public KodamaHermitLvUpParam levelupSeedNum__arr12;
        [FieldOffset(156)] public KodamaHermitLvUpParam levelupSeedNum__arr13;
        [FieldOffset(168)] public KodamaHermitLvUpParam levelupSeedNum__arr14;
        [FieldOffset(180)] public KodamaHermitLvUpParam levelupSeedNum__arr15;
        [FieldOffset(192)] public KodamaHermitLvUpParam levelupSeedNum__arr16;
        [FieldOffset(204)] public KodamaHermitLvUpParam levelupSeedNum__arr17;
        [FieldOffset(216)] public KodamaHermitLvUpParam levelupSeedNum__arr18;
        [FieldOffset(228)] public KodamaHermitLvUpParam levelupSeedNum__arr19;
        [FieldOffset(240)] public KodamaHermitLvUpParam levelupSeedNum__arr20;
        [FieldOffset(252)] public KodamaHermitLvUpParam levelupSeedNum__arr21;
        [FieldOffset(264)] public KodamaHermitLvUpParam levelupSeedNum__arr22;
        [FieldOffset(276)] public KodamaHermitLvUpParam levelupSeedNum__arr23;
        [FieldOffset(288)] public KodamaHermitLvUpParam levelupSeedNum__arr24;
        [FieldOffset(300)] public KodamaHermitLvUpParam levelupSeedNum__arr25;
        [FieldOffset(312)] public KodamaHermitLvUpParam levelupSeedNum__arr26;
        [FieldOffset(324)] public KodamaHermitLvUpParam levelupSeedNum__arr27;
        [FieldOffset(336)] public KodamaHermitLvUpParam levelupSeedNum__arr28;
        [FieldOffset(348)] public KodamaHermitLvUpParam levelupSeedNum__arr29;
        [FieldOffset(360)] public KodamaHermitLvUpParam levelupSeedNum__arr30;
        [FieldOffset(372)] public KodamaHermitLvUpParam levelupSeedNum__arr31;
        [FieldOffset(384)] public KodamaHermitLvUpParam levelupSeedNum__arr32;
        [FieldOffset(396)] public KodamaHermitLvUpParam levelupSeedNum__arr33;
        [FieldOffset(408)] public KodamaHermitLvUpParam levelupSeedNum__arr34;
        [FieldOffset(420)] public KodamaHermitLvUpParam levelupSeedNum__arr35;
        [FieldOffset(432)] public KodamaHermitLvUpParam levelupSeedNum__arr36;
        [FieldOffset(444)] public KodamaHermitLvUpParam levelupSeedNum__arr37;
        [FieldOffset(456)] public KodamaHermitLvUpParam levelupSeedNum__arr38;
        [FieldOffset(468)] public KodamaHermitLvUpParam levelupSeedNum__arr39;
        [FieldOffset(480)] public KodamaHermitLvUpParam levelupSeedNum__arr40;
        [FieldOffset(492)] public KodamaHermitLvUpParam levelupSeedNum__arr41;
        [FieldOffset(504)] public KodamaHermitLvUpParam levelupSeedNum__arr42;
        [FieldOffset(516)] public KodamaHermitLvUpParam levelupSeedNum__arr43;
        [FieldOffset(528)] public KodamaHermitLvUpParam levelupSeedNum__arr44;
        [FieldOffset(540)] public KodamaHermitLvUpParam levelupSeedNum__arr45;
        [FieldOffset(552)] public KodamaHermitLvUpParam levelupSeedNum__arr46;
        [FieldOffset(564)] public KodamaHermitLvUpParam levelupSeedNum__arr47;
        [FieldOffset(576)] public KodamaHermitLvUpParam levelupSeedNum__arr48;
        [FieldOffset(588)] public KodamaHermitLvUpParam levelupSeedNum__arr49;
        [FieldOffset(600)] public KodamaHermitLvUpParam levelupSeedNum__arr50;
        [FieldOffset(612)] public KodamaHermitLvUpParam levelupSeedNum__arr51;
        [FieldOffset(624)] public KodamaHermitLvUpParam levelupSeedNum__arr52;
        [FieldOffset(636)] public KodamaHermitLvUpParam levelupSeedNum__arr53;
        [FieldOffset(648)] public KodamaHermitLvUpParam levelupSeedNum__arr54;
        [FieldOffset(660)] public KodamaHermitLvUpParam levelupSeedNum__arr55;
        [FieldOffset(672)] public KodamaHermitLvUpParam levelupSeedNum__arr56;
        [FieldOffset(684)] public KodamaHermitLvUpParam levelupSeedNum__arr57;
        [FieldOffset(696)] public KodamaHermitLvUpParam levelupSeedNum__arr58;
        [FieldOffset(708)] public KodamaHermitLvUpParam levelupSeedNum__arr59;
        [FieldOffset(720)] public KodamaHermitLvUpParam levelupSeedNum__arr60;
        [FieldOffset(732)] public KodamaHermitLvUpParam levelupSeedNum__arr61;
        [FieldOffset(744)] public KodamaHermitLvUpParam levelupSeedNum__arr62;
        [FieldOffset(756)] public KodamaHermitLvUpParam levelupSeedNum__arr63;
        [FieldOffset(768)] public KodamaHermitLvUpParam levelupSeedNum__arr64;
        [FieldOffset(780)] public KodamaHermitLvUpParam levelupSeedNum__arr65;
        [FieldOffset(792)] public KodamaHermitLvUpParam levelupSeedNum__arr66;
        [FieldOffset(804)] public KodamaHermitLvUpParam levelupSeedNum__arr67;
        [FieldOffset(816)] public KodamaHermitLvUpParam levelupSeedNum__arr68;
        [FieldOffset(828)] public KodamaHermitLvUpParam levelupSeedNum__arr69;
        [FieldOffset(840)] public KodamaHermitLvUpParam levelupSeedNum__arr70;
        [FieldOffset(852)] public KodamaHermitLvUpParam levelupSeedNum__arr71;
        [FieldOffset(864)] public KodamaHermitLvUpParam levelupSeedNum__arr72;
        [FieldOffset(876)] public KodamaHermitLvUpParam levelupSeedNum__arr73;
        [FieldOffset(888)] public KodamaHermitLvUpParam levelupSeedNum__arr74;
        [FieldOffset(900)] public KodamaHermitLvUpParam levelupSeedNum__arr75;
        [FieldOffset(912)] public KodamaHermitLvUpParam levelupSeedNum__arr76;
        [FieldOffset(924)] public KodamaHermitLvUpParam levelupSeedNum__arr77;
        [FieldOffset(936)] public KodamaHermitLvUpParam levelupSeedNum__arr78;
        [FieldOffset(948)] public KodamaHermitLvUpParam levelupSeedNum__arr79;
        [FieldOffset(960)] public KodamaHermitLvUpParam levelupSeedNum__arr80;
        [FieldOffset(972)] public KodamaHermitLvUpParam levelupSeedNum__arr81;
        [FieldOffset(984)] public KodamaHermitLvUpParam levelupSeedNum__arr82;
        [FieldOffset(996)] public KodamaHermitLvUpParam levelupSeedNum__arr83;
        [FieldOffset(1008)] public KodamaHermitLvUpParam levelupSeedNum__arr84;
        [FieldOffset(1020)] public KodamaHermitLvUpParam levelupSeedNum__arr85;
        [FieldOffset(1032)] public KodamaHermitLvUpParam levelupSeedNum__arr86;
        [FieldOffset(1044)] public KodamaHermitLvUpParam levelupSeedNum__arr87;
        [FieldOffset(1056)] public KodamaHermitLvUpParam levelupSeedNum__arr88;
        [FieldOffset(1068)] public KodamaHermitLvUpParam levelupSeedNum__arr89;
        [FieldOffset(1080)] public KodamaHermitLvUpParam levelupSeedNum__arr90;
        [FieldOffset(1092)] public KodamaHermitLvUpParam levelupSeedNum__arr91;
        [FieldOffset(1104)] public KodamaHermitLvUpParam levelupSeedNum__arr92;
        [FieldOffset(1116)] public KodamaHermitLvUpParam levelupSeedNum__arr93;
        [FieldOffset(1128)] public KodamaHermitLvUpParam levelupSeedNum__arr94;
        [FieldOffset(1140)] public KodamaHermitLvUpParam levelupSeedNum__arr95;
        [FieldOffset(1152)] public KodamaHermitLvUpParam levelupSeedNum__arr96;
        [FieldOffset(1164)] public KodamaHermitLvUpParam levelupSeedNum__arr97;
        [FieldOffset(1176)] public KodamaHermitLvUpParam levelupSeedNum__arr98;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct KodamaNewFormParam
    {
        [FieldOffset(0)]  public float takableRange;
        [FieldOffset(4)]  public float colliderRange;
        [FieldOffset(8)]  public float fadeTime;
        [FieldOffset(12)] public float spaceVertical;
        [FieldOffset(16)] public float spaceHorizontal;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1400)]
    public struct KodamaParam
    {
        [FieldOffset(0)]    public KodamaNormalParam normal;
        [FieldOffset(40)]   public KodamaElderParam elder;
        [FieldOffset(52)]   public KodamaHermitParam hermit;
        [FieldOffset(1240)] public KodamaNewFormParam newform__arr0;
        [FieldOffset(1260)] public KodamaNewFormParam newform__arr1;
        [FieldOffset(1280)] public KodamaNewFormParam newform__arr2;
        [FieldOffset(1300)] public KodamaNewFormParam newform__arr3;
        [FieldOffset(1320)] public KodamaNewFormParam newform__arr4;
        [FieldOffset(1340)] public KodamaNewFormParam newform__arr5;
        [FieldOffset(1360)] public KodamaNewFormParam newform__arr6;
        [FieldOffset(1380)] public KodamaNewFormParam newform__arr7;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct NpcParam
    {
        [FieldOffset(0)] public int inputSequenceItemNumShort;
        [FieldOffset(4)] public int inputSequenceItemNumMiddle;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1484)]
    public struct IslandParameter
    {
        [FieldOffset(0)]    public IslandParam islands__arr0;
        [FieldOffset(14)] public IslandParam islands__arr1;
        [FieldOffset(28)] public IslandParam islands__arr2;
        [FieldOffset(42)] public IslandParam islands__arr3;
        [FieldOffset(56)] public IslandParam islands__arr4;
        [FieldOffset(72)]   public KodamaParam kodama;
        [FieldOffset(1472)] public NpcParam npc;
        [FieldOffset(1480)] public int portalExtraKeyNum;
    }

}