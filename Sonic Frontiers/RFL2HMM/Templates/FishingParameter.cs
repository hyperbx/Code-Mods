using System.Numerics;
using System.Runtime.InteropServices;

public class FishingParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct FishingCommonParam
    {
        [FieldOffset(0)]  public float baseWaveThickness;
        [FieldOffset(4)]  public float baseWaveSuccessRatioNormal;
        [FieldOffset(8)]  public float baseWaveSuccessRatioHold;
        [FieldOffset(12)] public float singleWaveThickness;
        [FieldOffset(16)] public float baseWaveEdgeThickness;
        [FieldOffset(20)] public float timingEdgeThickness;
        [FieldOffset(24)] public uint fishShadowNum;
        [FieldOffset(28)] public float fishApproachIntervalMin;
        [FieldOffset(32)] public float fishApproachIntervalMax;
        [FieldOffset(36)] public float fishEscapeDistance;
        [FieldOffset(40)] public uint buoyTwitchNumMin;
        [FieldOffset(44)] public uint buoyTwitchNumMax;
        [FieldOffset(48)] public float buoyTwitchIntervalMin;
        [FieldOffset(52)] public float buoyTwitchIntervalMax;
        [FieldOffset(56)] public float inputValidTime;
        [FieldOffset(60)] public float fishingCameraTransitDelay;
        [FieldOffset(64)] public float cutinDelay;
        [FieldOffset(68)] public float cutinDuration;
        [FieldOffset(72)] public float successPullUpDelay;
        [FieldOffset(76)] public uint goldenChestLimitNum;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct FishingSuccessPatternParam
    {
        [FieldOffset(0)] public uint successNum;
        [FieldOffset(4)] public uint failureNum;
    }

    public enum Type : sbyte
    {
        TYPE_INVALID = 0,
        TYPE_NORMAL = 1,
        TYPE_HOLD = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct FishingWaveParam
    {
        [FieldOffset(0)] public Type type;
        [FieldOffset(4)] public float radius;
        [FieldOffset(8)] public float thickness;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct FishingWaveGroupParam
    {
        [FieldOffset(0)] public FishingWaveParam waves__arr0;
        [FieldOffset(12)] public FishingWaveParam waves__arr1;
        [FieldOffset(24)] public FishingWaveParam waves__arr2;
        [FieldOffset(36)] public FishingWaveParam waves__arr3;
        [FieldOffset(48)] public FishingWaveParam waves__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 632)]
    public struct FishingWavePatternParam
    {
        [FieldOffset(0)]  public float speed;
        [FieldOffset(4)]  public float intervalMinFirst;
        [FieldOffset(8)]  public float intervalMaxFirst;
        [FieldOffset(12)] public float intervalMin;
        [FieldOffset(16)] public float intervalMax;
        [FieldOffset(20)] public float addRadiusMin;
        [FieldOffset(24)] public float addRadiusMax;
        [FieldOffset(28)] public uint waveGroupNum;
        [FieldOffset(32)] public FishingWaveGroupParam waveGroups__arr0;
        [FieldOffset(92)] public FishingWaveGroupParam waveGroups__arr1;
        [FieldOffset(152)] public FishingWaveGroupParam waveGroups__arr2;
        [FieldOffset(212)] public FishingWaveGroupParam waveGroups__arr3;
        [FieldOffset(272)] public FishingWaveGroupParam waveGroups__arr4;
        [FieldOffset(332)] public FishingWaveGroupParam waveGroups__arr5;
        [FieldOffset(392)] public FishingWaveGroupParam waveGroups__arr6;
        [FieldOffset(452)] public FishingWaveGroupParam waveGroups__arr7;
        [FieldOffset(512)] public FishingWaveGroupParam waveGroups__arr8;
        [FieldOffset(572)] public FishingWaveGroupParam waveGroups__arr9;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct FishingFishGroupParam
    {
        [FieldOffset(0)] public float rate;
    }

    public enum FishShadowType : sbyte
    {
        SMALL = 0,
        MEDIUM = 1,
        LARGE = 2
    }

    public enum CatchUpMotionType : sbyte
    {
        SHADOW_SIZE = 0,
        LARGE_GOOD_FISH = 1,
        LARGE_GOOD_ITEM = 2,
        LARGE_BAD = 3,
        CatchUpMotionType_LARGE = 4,
        CatchUpMotionType_MEDIUM = 5,
        CatchUpMotionType_SMALL = 6,
        CHEST_GOOD = 7,
        CHEST_VERYGOOD = 8,
        SCROLL = 9
    }

    public enum ToastType : sbyte
    {
        MOTION = 0,
        PATTERN_1 = 1,
        PATTERN_2 = 2,
        PATTERN_3 = 3,
        PATTERN_4 = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct FishingFishParam
    {
        [FieldOffset(0)]  public int fishGroupId;
        [FieldOffset(4)]  public FishShadowType shadowType;
        [FieldOffset(8)]  public uint successPatternId;
        [FieldOffset(12)] public uint wavePatternId;
        [FieldOffset(16)] public uint expPoint;
        [FieldOffset(20)] public uint tokenNum;
        [FieldOffset(24)] public bool isRare;
        [FieldOffset(25)] public CatchUpMotionType catchUpMotionType;
        [FieldOffset(26)] public ToastType toastType;
        [FieldOffset(32)] public Vector3 catchUpOffsetPos;
        [FieldOffset(48)] public Vector3 catchUpOffsetRot;
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct FishingSpotSpawnFishParam
    {
        [FieldOffset(0)] public int spawnFishId__arr0;
        [FieldOffset(4)] public int spawnFishId__arr1;
        [FieldOffset(8)] public int spawnFishId__arr2;
        [FieldOffset(12)] public int spawnFishId__arr3;
        [FieldOffset(16)] public int spawnFishId__arr4;
        [FieldOffset(20)] public int spawnFishId__arr5;
        [FieldOffset(24)] public int spawnFishId__arr6;
        [FieldOffset(28)] public int spawnFishId__arr7;
        [FieldOffset(32)] public int spawnFishId__arr8;
        [FieldOffset(36)] public int spawnFishId__arr9;
        [FieldOffset(40)] public int spawnFishId__arr10;
        [FieldOffset(44)] public int spawnFishId__arr11;
        [FieldOffset(48)] public int spawnFishId__arr12;
        [FieldOffset(52)] public int spawnFishId__arr13;
        [FieldOffset(56)] public int spawnFishId__arr14;
        [FieldOffset(60)] public int spawnFishId__arr15;
        [FieldOffset(64)] public int spawnFishId__arr16;
        [FieldOffset(68)] public int spawnFishId__arr17;
        [FieldOffset(72)] public int spawnFishId__arr18;
        [FieldOffset(76)] public int spawnFishId__arr19;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct FishingFixedResultParam
    {
        [FieldOffset(0)] public int count;
        [FieldOffset(4)] public int fishId;
    }

    [StructLayout(LayoutKind.Explicit, Size = 408)]
    public struct FishingSpotFixedResultParam
    {
        [FieldOffset(0)] public uint tableSize;
        [FieldOffset(4)] public uint achievementUnlockCount;
        [FieldOffset(8)] public FishingFixedResultParam fixedResultList__arr0;
        [FieldOffset(16)] public FishingFixedResultParam fixedResultList__arr1;
        [FieldOffset(24)] public FishingFixedResultParam fixedResultList__arr2;
        [FieldOffset(32)] public FishingFixedResultParam fixedResultList__arr3;
        [FieldOffset(40)] public FishingFixedResultParam fixedResultList__arr4;
        [FieldOffset(48)] public FishingFixedResultParam fixedResultList__arr5;
        [FieldOffset(56)] public FishingFixedResultParam fixedResultList__arr6;
        [FieldOffset(64)] public FishingFixedResultParam fixedResultList__arr7;
        [FieldOffset(72)] public FishingFixedResultParam fixedResultList__arr8;
        [FieldOffset(80)] public FishingFixedResultParam fixedResultList__arr9;
        [FieldOffset(88)] public FishingFixedResultParam fixedResultList__arr10;
        [FieldOffset(96)] public FishingFixedResultParam fixedResultList__arr11;
        [FieldOffset(104)] public FishingFixedResultParam fixedResultList__arr12;
        [FieldOffset(112)] public FishingFixedResultParam fixedResultList__arr13;
        [FieldOffset(120)] public FishingFixedResultParam fixedResultList__arr14;
        [FieldOffset(128)] public FishingFixedResultParam fixedResultList__arr15;
        [FieldOffset(136)] public FishingFixedResultParam fixedResultList__arr16;
        [FieldOffset(144)] public FishingFixedResultParam fixedResultList__arr17;
        [FieldOffset(152)] public FishingFixedResultParam fixedResultList__arr18;
        [FieldOffset(160)] public FishingFixedResultParam fixedResultList__arr19;
        [FieldOffset(168)] public FishingFixedResultParam fixedResultList__arr20;
        [FieldOffset(176)] public FishingFixedResultParam fixedResultList__arr21;
        [FieldOffset(184)] public FishingFixedResultParam fixedResultList__arr22;
        [FieldOffset(192)] public FishingFixedResultParam fixedResultList__arr23;
        [FieldOffset(200)] public FishingFixedResultParam fixedResultList__arr24;
        [FieldOffset(208)] public FishingFixedResultParam fixedResultList__arr25;
        [FieldOffset(216)] public FishingFixedResultParam fixedResultList__arr26;
        [FieldOffset(224)] public FishingFixedResultParam fixedResultList__arr27;
        [FieldOffset(232)] public FishingFixedResultParam fixedResultList__arr28;
        [FieldOffset(240)] public FishingFixedResultParam fixedResultList__arr29;
        [FieldOffset(248)] public FishingFixedResultParam fixedResultList__arr30;
        [FieldOffset(256)] public FishingFixedResultParam fixedResultList__arr31;
        [FieldOffset(264)] public FishingFixedResultParam fixedResultList__arr32;
        [FieldOffset(272)] public FishingFixedResultParam fixedResultList__arr33;
        [FieldOffset(280)] public FishingFixedResultParam fixedResultList__arr34;
        [FieldOffset(288)] public FishingFixedResultParam fixedResultList__arr35;
        [FieldOffset(296)] public FishingFixedResultParam fixedResultList__arr36;
        [FieldOffset(304)] public FishingFixedResultParam fixedResultList__arr37;
        [FieldOffset(312)] public FishingFixedResultParam fixedResultList__arr38;
        [FieldOffset(320)] public FishingFixedResultParam fixedResultList__arr39;
        [FieldOffset(328)] public FishingFixedResultParam fixedResultList__arr40;
        [FieldOffset(336)] public FishingFixedResultParam fixedResultList__arr41;
        [FieldOffset(344)] public FishingFixedResultParam fixedResultList__arr42;
        [FieldOffset(352)] public FishingFixedResultParam fixedResultList__arr43;
        [FieldOffset(360)] public FishingFixedResultParam fixedResultList__arr44;
        [FieldOffset(368)] public FishingFixedResultParam fixedResultList__arr45;
        [FieldOffset(376)] public FishingFixedResultParam fixedResultList__arr46;
        [FieldOffset(384)] public FishingFixedResultParam fixedResultList__arr47;
        [FieldOffset(392)] public FishingFixedResultParam fixedResultList__arr48;
        [FieldOffset(400)] public FishingFixedResultParam fixedResultList__arr49;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1984)]
    public struct FishingSpotParam
    {
        [FieldOffset(0)]    public FishingSpotSpawnFishParam spawnFish__arr0;
        [FieldOffset(80)] public FishingSpotSpawnFishParam spawnFish__arr1;
        [FieldOffset(160)] public FishingSpotSpawnFishParam spawnFish__arr2;
        [FieldOffset(240)] public FishingSpotSpawnFishParam spawnFish__arr3;
        [FieldOffset(320)]  public FishingSpotFixedResultParam fixedResults__arr0;
        [FieldOffset(728)] public FishingSpotFixedResultParam fixedResults__arr1;
        [FieldOffset(1136)] public FishingSpotFixedResultParam fixedResults__arr2;
        [FieldOffset(1544)] public FishingSpotFixedResultParam fixedResults__arr3;
        [FieldOffset(1952)] public uint useFishCoinNum__arr0;
        [FieldOffset(1956)] public uint useFishCoinNum__arr1;
        [FieldOffset(1960)] public uint useFishCoinNum__arr2;
        [FieldOffset(1964)] public uint useFishCoinNum__arr3;
        [FieldOffset(1968)] public uint tokenRate__arr0;
        [FieldOffset(1972)] public uint tokenRate__arr1;
        [FieldOffset(1976)] public uint tokenRate__arr2;
        [FieldOffset(1980)] public uint tokenRate__arr3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1272)]
    public struct FishingTutorialParam
    {
        [FieldOffset(0)]   public uint singleWaveSuccessCount;
        [FieldOffset(4)]   public uint holdWaveSuccessCount;
        [FieldOffset(8)]   public FishingWavePatternParam singleWave;
        [FieldOffset(640)] public FishingWavePatternParam holdWave;
    }

    [StructLayout(LayoutKind.Explicit, Size = 9)]
    public struct FishingTradeTableParma
    {
        [FieldOffset(0)] public byte sales__arr0;
        [FieldOffset(1)] public byte sales__arr1;
        [FieldOffset(2)] public byte sales__arr2;
        [FieldOffset(3)] public byte sales__arr3;
        [FieldOffset(4)] public byte sales__arr4;
        [FieldOffset(5)] public byte sales__arr5;
        [FieldOffset(6)] public byte sales__arr6;
        [FieldOffset(7)] public byte sales__arr7;
        [FieldOffset(8)] public byte sales__arr8;
    }

    [StructLayout(LayoutKind.Explicit, Size = 63)]
    public struct FishingTradeParam
    {
        [FieldOffset(0)]  public FishingTradeTableParma spot__arr0;
        [FieldOffset(9)] public FishingTradeTableParma spot__arr1;
        [FieldOffset(18)] public FishingTradeTableParma spot__arr2;
        [FieldOffset(27)] public FishingTradeTableParma spot__arr3;
        [FieldOffset(36)] public byte prices__arr0;
        [FieldOffset(37)] public byte prices__arr1;
        [FieldOffset(38)] public byte prices__arr2;
        [FieldOffset(39)] public byte prices__arr3;
        [FieldOffset(40)] public byte prices__arr4;
        [FieldOffset(41)] public byte prices__arr5;
        [FieldOffset(42)] public byte prices__arr6;
        [FieldOffset(43)] public byte prices__arr7;
        [FieldOffset(44)] public byte prices__arr8;
        [FieldOffset(45)] public byte pricesVeryHard__arr0;
        [FieldOffset(46)] public byte pricesVeryHard__arr1;
        [FieldOffset(47)] public byte pricesVeryHard__arr2;
        [FieldOffset(48)] public byte pricesVeryHard__arr3;
        [FieldOffset(49)] public byte pricesVeryHard__arr4;
        [FieldOffset(50)] public byte pricesVeryHard__arr5;
        [FieldOffset(51)] public byte pricesVeryHard__arr6;
        [FieldOffset(52)] public byte pricesVeryHard__arr7;
        [FieldOffset(53)] public byte pricesVeryHard__arr8;
        [FieldOffset(54)] public byte counts__arr0;
        [FieldOffset(55)] public byte counts__arr1;
        [FieldOffset(56)] public byte counts__arr2;
        [FieldOffset(57)] public byte counts__arr3;
        [FieldOffset(58)] public byte counts__arr4;
        [FieldOffset(59)] public byte counts__arr5;
        [FieldOffset(60)] public byte counts__arr6;
        [FieldOffset(61)] public byte counts__arr7;
        [FieldOffset(62)] public byte counts__arr8;
    }

    [StructLayout(LayoutKind.Explicit, Size = 18176)]
    public struct FishingParameter
    {
        [FieldOffset(0)]     public FishingCommonParam common;
        [FieldOffset(80)]    public FishingSuccessPatternParam successPattern__arr0;
        [FieldOffset(88)] public FishingSuccessPatternParam successPattern__arr1;
        [FieldOffset(96)] public FishingSuccessPatternParam successPattern__arr2;
        [FieldOffset(104)] public FishingSuccessPatternParam successPattern__arr3;
        [FieldOffset(112)] public FishingSuccessPatternParam successPattern__arr4;
        [FieldOffset(120)] public FishingSuccessPatternParam successPattern__arr5;
        [FieldOffset(128)] public FishingSuccessPatternParam successPattern__arr6;
        [FieldOffset(136)] public FishingSuccessPatternParam successPattern__arr7;
        [FieldOffset(144)] public FishingSuccessPatternParam successPattern__arr8;
        [FieldOffset(152)] public FishingSuccessPatternParam successPattern__arr9;
        [FieldOffset(160)]   public FishingWavePatternParam wavePattern__arr0;
        [FieldOffset(792)] public FishingWavePatternParam wavePattern__arr1;
        [FieldOffset(1424)] public FishingWavePatternParam wavePattern__arr2;
        [FieldOffset(2056)] public FishingWavePatternParam wavePattern__arr3;
        [FieldOffset(2688)] public FishingWavePatternParam wavePattern__arr4;
        [FieldOffset(3320)] public FishingWavePatternParam wavePattern__arr5;
        [FieldOffset(3952)] public FishingWavePatternParam wavePattern__arr6;
        [FieldOffset(4584)] public FishingWavePatternParam wavePattern__arr7;
        [FieldOffset(5216)] public FishingWavePatternParam wavePattern__arr8;
        [FieldOffset(5848)] public FishingWavePatternParam wavePattern__arr9;
        [FieldOffset(6480)]  public FishingFishGroupParam fishGroup__arr0;
        [FieldOffset(6484)] public FishingFishGroupParam fishGroup__arr1;
        [FieldOffset(6488)] public FishingFishGroupParam fishGroup__arr2;
        [FieldOffset(6492)] public FishingFishGroupParam fishGroup__arr3;
        [FieldOffset(6496)] public FishingFishGroupParam fishGroup__arr4;
        [FieldOffset(6500)] public FishingFishGroupParam fishGroup__arr5;
        [FieldOffset(6504)] public FishingFishGroupParam fishGroup__arr6;
        [FieldOffset(6508)] public FishingFishGroupParam fishGroup__arr7;
        [FieldOffset(6512)] public FishingFishGroupParam fishGroup__arr8;
        [FieldOffset(6516)] public FishingFishGroupParam fishGroup__arr9;
        [FieldOffset(6528)]  public FishingFishParam fish__arr0;
        [FieldOffset(6592)] public FishingFishParam fish__arr1;
        [FieldOffset(6656)] public FishingFishParam fish__arr2;
        [FieldOffset(6720)] public FishingFishParam fish__arr3;
        [FieldOffset(6784)] public FishingFishParam fish__arr4;
        [FieldOffset(6848)] public FishingFishParam fish__arr5;
        [FieldOffset(6912)] public FishingFishParam fish__arr6;
        [FieldOffset(6976)] public FishingFishParam fish__arr7;
        [FieldOffset(7040)] public FishingFishParam fish__arr8;
        [FieldOffset(7104)] public FishingFishParam fish__arr9;
        [FieldOffset(7168)] public FishingFishParam fish__arr10;
        [FieldOffset(7232)] public FishingFishParam fish__arr11;
        [FieldOffset(7296)] public FishingFishParam fish__arr12;
        [FieldOffset(7360)] public FishingFishParam fish__arr13;
        [FieldOffset(7424)] public FishingFishParam fish__arr14;
        [FieldOffset(7488)] public FishingFishParam fish__arr15;
        [FieldOffset(7552)] public FishingFishParam fish__arr16;
        [FieldOffset(7616)] public FishingFishParam fish__arr17;
        [FieldOffset(7680)] public FishingFishParam fish__arr18;
        [FieldOffset(7744)] public FishingFishParam fish__arr19;
        [FieldOffset(7808)] public FishingFishParam fish__arr20;
        [FieldOffset(7872)] public FishingFishParam fish__arr21;
        [FieldOffset(7936)] public FishingFishParam fish__arr22;
        [FieldOffset(8000)] public FishingFishParam fish__arr23;
        [FieldOffset(8064)] public FishingFishParam fish__arr24;
        [FieldOffset(8128)] public FishingFishParam fish__arr25;
        [FieldOffset(8192)] public FishingFishParam fish__arr26;
        [FieldOffset(8256)] public FishingFishParam fish__arr27;
        [FieldOffset(8320)] public FishingFishParam fish__arr28;
        [FieldOffset(8384)] public FishingFishParam fish__arr29;
        [FieldOffset(8448)] public FishingFishParam fish__arr30;
        [FieldOffset(8512)] public FishingFishParam fish__arr31;
        [FieldOffset(8576)] public FishingFishParam fish__arr32;
        [FieldOffset(8640)] public FishingFishParam fish__arr33;
        [FieldOffset(8704)] public FishingFishParam fish__arr34;
        [FieldOffset(8768)] public FishingFishParam fish__arr35;
        [FieldOffset(8832)] public FishingFishParam fish__arr36;
        [FieldOffset(8896)] public FishingFishParam fish__arr37;
        [FieldOffset(8960)] public FishingFishParam fish__arr38;
        [FieldOffset(9024)] public FishingFishParam fish__arr39;
        [FieldOffset(9088)] public FishingFishParam fish__arr40;
        [FieldOffset(9152)] public FishingFishParam fish__arr41;
        [FieldOffset(9216)] public FishingFishParam fish__arr42;
        [FieldOffset(9280)] public FishingFishParam fish__arr43;
        [FieldOffset(9344)] public FishingFishParam fish__arr44;
        [FieldOffset(9408)] public FishingFishParam fish__arr45;
        [FieldOffset(9472)] public FishingFishParam fish__arr46;
        [FieldOffset(9536)] public FishingFishParam fish__arr47;
        [FieldOffset(9600)] public FishingFishParam fish__arr48;
        [FieldOffset(9664)] public FishingFishParam fish__arr49;
        [FieldOffset(9728)] public FishingFishParam fish__arr50;
        [FieldOffset(9792)] public FishingFishParam fish__arr51;
        [FieldOffset(9856)] public FishingFishParam fish__arr52;
        [FieldOffset(9920)] public FishingFishParam fish__arr53;
        [FieldOffset(9984)] public FishingFishParam fish__arr54;
        [FieldOffset(10048)] public FishingFishParam fish__arr55;
        [FieldOffset(10112)] public FishingFishParam fish__arr56;
        [FieldOffset(10176)] public FishingFishParam fish__arr57;
        [FieldOffset(10240)] public FishingFishParam fish__arr58;
        [FieldOffset(10304)] public FishingFishParam fish__arr59;
        [FieldOffset(10368)] public FishingFishParam fish__arr60;
        [FieldOffset(10432)] public FishingFishParam fish__arr61;
        [FieldOffset(10496)] public FishingFishParam fish__arr62;
        [FieldOffset(10560)] public FishingFishParam fish__arr63;
        [FieldOffset(10624)] public FishingFishParam fish__arr64;
        [FieldOffset(10688)] public FishingFishParam fish__arr65;
        [FieldOffset(10752)] public FishingFishParam fish__arr66;
        [FieldOffset(10816)] public FishingFishParam fish__arr67;
        [FieldOffset(10880)] public FishingFishParam fish__arr68;
        [FieldOffset(10944)] public FishingFishParam fish__arr69;
        [FieldOffset(11008)] public FishingFishParam fish__arr70;
        [FieldOffset(11072)] public FishingFishParam fish__arr71;
        [FieldOffset(11136)] public FishingFishParam fish__arr72;
        [FieldOffset(11200)] public FishingFishParam fish__arr73;
        [FieldOffset(11264)] public FishingFishParam fish__arr74;
        [FieldOffset(11328)] public FishingFishParam fish__arr75;
        [FieldOffset(11392)] public FishingFishParam fish__arr76;
        [FieldOffset(11456)] public FishingFishParam fish__arr77;
        [FieldOffset(11520)] public FishingFishParam fish__arr78;
        [FieldOffset(11584)] public FishingFishParam fish__arr79;
        [FieldOffset(11648)] public FishingFishParam fish__arr80;
        [FieldOffset(11712)] public FishingFishParam fish__arr81;
        [FieldOffset(11776)] public FishingFishParam fish__arr82;
        [FieldOffset(11840)] public FishingFishParam fish__arr83;
        [FieldOffset(11904)] public FishingFishParam fish__arr84;
        [FieldOffset(11968)] public FishingFishParam fish__arr85;
        [FieldOffset(12032)] public FishingFishParam fish__arr86;
        [FieldOffset(12096)] public FishingFishParam fish__arr87;
        [FieldOffset(12160)] public FishingFishParam fish__arr88;
        [FieldOffset(12224)] public FishingFishParam fish__arr89;
        [FieldOffset(12288)] public FishingFishParam fish__arr90;
        [FieldOffset(12352)] public FishingFishParam fish__arr91;
        [FieldOffset(12416)] public FishingFishParam fish__arr92;
        [FieldOffset(12480)] public FishingFishParam fish__arr93;
        [FieldOffset(12544)] public FishingFishParam fish__arr94;
        [FieldOffset(12608)] public FishingFishParam fish__arr95;
        [FieldOffset(12672)] public FishingFishParam fish__arr96;
        [FieldOffset(12736)] public FishingFishParam fish__arr97;
        [FieldOffset(12800)] public FishingFishParam fish__arr98;
        [FieldOffset(12864)] public FishingFishParam fish__arr99;
        [FieldOffset(12928)] public FishingFishParam fish__arr100;
        [FieldOffset(12992)] public FishingFishParam fish__arr101;
        [FieldOffset(13056)] public FishingFishParam fish__arr102;
        [FieldOffset(13120)] public FishingFishParam fish__arr103;
        [FieldOffset(13184)] public FishingFishParam fish__arr104;
        [FieldOffset(13248)] public FishingFishParam fish__arr105;
        [FieldOffset(13312)] public FishingFishParam fish__arr106;
        [FieldOffset(13376)] public FishingFishParam fish__arr107;
        [FieldOffset(13440)] public FishingFishParam fish__arr108;
        [FieldOffset(13504)] public FishingFishParam fish__arr109;
        [FieldOffset(13568)] public FishingFishParam fish__arr110;
        [FieldOffset(13632)] public FishingFishParam fish__arr111;
        [FieldOffset(13696)] public FishingFishParam fish__arr112;
        [FieldOffset(13760)] public FishingFishParam fish__arr113;
        [FieldOffset(13824)] public FishingFishParam fish__arr114;
        [FieldOffset(13888)] public FishingFishParam fish__arr115;
        [FieldOffset(13952)] public FishingFishParam fish__arr116;
        [FieldOffset(14016)] public FishingFishParam fish__arr117;
        [FieldOffset(14080)] public FishingFishParam fish__arr118;
        [FieldOffset(14144)] public FishingFishParam fish__arr119;
        [FieldOffset(14208)] public FishingFishParam fish__arr120;
        [FieldOffset(14272)] public FishingFishParam fish__arr121;
        [FieldOffset(14336)] public FishingFishParam fish__arr122;
        [FieldOffset(14400)] public FishingFishParam fish__arr123;
        [FieldOffset(14464)] public FishingFishParam fish__arr124;
        [FieldOffset(14528)] public FishingFishParam fish__arr125;
        [FieldOffset(14592)] public FishingFishParam fish__arr126;
        [FieldOffset(14656)] public FishingFishParam fish__arr127;
        [FieldOffset(14720)] public FishingFishParam fish__arr128;
        [FieldOffset(14784)] public FishingFishParam fish__arr129;
        [FieldOffset(14848)] public FishingSpotParam spot;
        [FieldOffset(16832)] public FishingTutorialParam tutorial;
        [FieldOffset(18104)] public FishingTradeParam trade;
    }

}