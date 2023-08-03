using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyJellymanConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct Movement
    {
        [FieldOffset(0)]  public float rotateSpeedMin;
        [FieldOffset(4)]  public float rotateSpeedMax;
        [FieldOffset(8)]  public float rotateSpeedMaxSpeedMin;
        [FieldOffset(12)] public float rotateSpeedMinSpeedMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct Eyesight
    {
        [FieldOffset(0)] public float distance;
        [FieldOffset(4)] public float angle;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct Fight
    {
        [FieldOffset(0)] public float attackRange;
        [FieldOffset(4)] public float attackAngle;
        [FieldOffset(8)] public float attackSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct EnemyJellymanModeConfig
    {
        [FieldOffset(0)]  public Movement movement;
        [FieldOffset(16)] public Eyesight eyesight;
        [FieldOffset(24)] public Fight fight;
        [FieldOffset(36)] public float transformRate;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct JellymanHumanCommonConfig
    {
        [FieldOffset(0)]  public EnemyJellymanModeConfig common;
        [FieldOffset(40)] public float actionDistance__arr0;
        [FieldOffset(44)] public float actionDistance__arr1;
        [FieldOffset(48)] public float actionDistance__arr2;
        [FieldOffset(52)] public float actionDistance__arr3;
        [FieldOffset(56)] public float actionDistance__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct RingParameter
    {
        [FieldOffset(0)]  public float suckedTime;
        [FieldOffset(4)]  public float launchAngle;
        [FieldOffset(8)]  public float launchMaxSpeed;
        [FieldOffset(12)] public float launchMinSpeed;
        [FieldOffset(16)] public float randomRangeMin;
        [FieldOffset(20)] public float randomRangeMax;
        [FieldOffset(24)] public float lifeTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct CString
    {
        [FieldOffset(0)] public long pValue;

        public string Value
        {
        	get => Marshal.PtrToStringAnsi((IntPtr)pValue);
        	set => pValue = (long)Marshal.StringToHGlobalAnsi(value);
        }
    }

    public enum VolumeShape : sbyte
    {
        SPHERE = 0,
        BOX = 1,
        CYLINDER = 2,
        CAPSULE = 3,
        NUM = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct VolumeInfo
    {
        [FieldOffset(0)]  public Vector3 volumeSize;
        [FieldOffset(16)] public Vector3 volumeOffset;
        [FieldOffset(32)] public Vector3 volumeRotation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 176)]
    public struct MappingPairInfo
    {
        [FieldOffset(0)]   public CString tagName;
        [FieldOffset(16)]  public sbyte pieceNum;
        [FieldOffset(20)]  public float pieceFuncFactor;
        [FieldOffset(24)]  public VolumeShape volumeShape;
        [FieldOffset(32)]  public CString humanNodeName;
        [FieldOffset(48)]  public VolumeInfo humanVolume;
        [FieldOffset(96)]  public CString eggNodeName;
        [FieldOffset(112)] public VolumeInfo eggVolume;
        [FieldOffset(160)] public bool effectActive;
        [FieldOffset(161)] public bool debugDraw;
        [FieldOffset(162)] public bool debugDrawVolumeAxis;
        [FieldOffset(163)] public bool debugDrawAxis;
    }

    [StructLayout(LayoutKind.Explicit, Size = 5744)]
    public struct EnemyCommonConfig
    {
        [FieldOffset(0)]   public JellymanHumanCommonConfig human;
        [FieldOffset(60)]  public RingParameter ringParam;
        [FieldOffset(88)]  public int codeDropNumMin;
        [FieldOffset(92)]  public int codeDropNumMax;
        [FieldOffset(96)]  public int codeXDropNumMin;
        [FieldOffset(100)] public int codeXDropNumMax;
        [FieldOffset(112)] public MappingPairInfo mappingPairInfo__arr0;
        [FieldOffset(288)] public MappingPairInfo mappingPairInfo__arr1;
        [FieldOffset(464)] public MappingPairInfo mappingPairInfo__arr2;
        [FieldOffset(640)] public MappingPairInfo mappingPairInfo__arr3;
        [FieldOffset(816)] public MappingPairInfo mappingPairInfo__arr4;
        [FieldOffset(992)] public MappingPairInfo mappingPairInfo__arr5;
        [FieldOffset(1168)] public MappingPairInfo mappingPairInfo__arr6;
        [FieldOffset(1344)] public MappingPairInfo mappingPairInfo__arr7;
        [FieldOffset(1520)] public MappingPairInfo mappingPairInfo__arr8;
        [FieldOffset(1696)] public MappingPairInfo mappingPairInfo__arr9;
        [FieldOffset(1872)] public MappingPairInfo mappingPairInfo__arr10;
        [FieldOffset(2048)] public MappingPairInfo mappingPairInfo__arr11;
        [FieldOffset(2224)] public MappingPairInfo mappingPairInfo__arr12;
        [FieldOffset(2400)] public MappingPairInfo mappingPairInfo__arr13;
        [FieldOffset(2576)] public MappingPairInfo mappingPairInfo__arr14;
        [FieldOffset(2752)] public MappingPairInfo mappingPairInfo__arr15;
        [FieldOffset(2928)] public MappingPairInfo mappingPairInfo__arr16;
        [FieldOffset(3104)] public MappingPairInfo mappingPairInfo__arr17;
        [FieldOffset(3280)] public MappingPairInfo mappingPairInfo__arr18;
        [FieldOffset(3456)] public MappingPairInfo mappingPairInfo__arr19;
        [FieldOffset(3632)] public MappingPairInfo mappingPairInfo__arr20;
        [FieldOffset(3808)] public MappingPairInfo mappingPairInfo__arr21;
        [FieldOffset(3984)] public MappingPairInfo mappingPairInfo__arr22;
        [FieldOffset(4160)] public MappingPairInfo mappingPairInfo__arr23;
        [FieldOffset(4336)] public MappingPairInfo mappingPairInfo__arr24;
        [FieldOffset(4512)] public MappingPairInfo mappingPairInfo__arr25;
        [FieldOffset(4688)] public MappingPairInfo mappingPairInfo__arr26;
        [FieldOffset(4864)] public MappingPairInfo mappingPairInfo__arr27;
        [FieldOffset(5040)] public MappingPairInfo mappingPairInfo__arr28;
        [FieldOffset(5216)] public MappingPairInfo mappingPairInfo__arr29;
        [FieldOffset(5392)] public MappingPairInfo mappingPairInfo__arr30;
        [FieldOffset(5568)] public MappingPairInfo mappingPairInfo__arr31;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct JellymanCommonLevelConfig
    {
        [FieldOffset(0)]  public int maxHealthPoint;
        [FieldOffset(4)]  public float maxStunPoint__arr0;
        [FieldOffset(8)] public float maxStunPoint__arr1;
        [FieldOffset(12)] public float maxStunPoint__arr2;
        [FieldOffset(16)] public float stunDecreaseStartTime;
        [FieldOffset(20)] public float stunDecreaseSpeed;
        [FieldOffset(24)] public float maxStaggerPoint__arr0;
        [FieldOffset(28)] public float maxStaggerPoint__arr1;
        [FieldOffset(32)] public float maxStaggerPoint__arr2;
        [FieldOffset(36)] public float staggerDecreaseStartTime;
        [FieldOffset(40)] public float staggerDecreaseSpeed;
        [FieldOffset(44)] public float stunTime;
        [FieldOffset(48)] public float attackRate;
        [FieldOffset(52)] public float attackMotionSpeed;
        [FieldOffset(56)] public ushort expItemNum;
        [FieldOffset(58)] public ushort exp;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct JellymanHumanLevelConfig
    {
        [FieldOffset(0)]  public float wallTime;
        [FieldOffset(4)]  public int wallLife;
        [FieldOffset(8)]  public float guardTime;
        [FieldOffset(12)] public float guardCoolTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct EnemyLevelConfig
    {
        [FieldOffset(0)]  public int level;
        [FieldOffset(4)]  public JellymanCommonLevelConfig common;
        [FieldOffset(64)] public JellymanHumanLevelConfig human;
    }

    public enum SuperArmorType : sbyte
    {
        None = 0,
        Attack = 1,
        Always = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct JellymanCommonActionConfig
    {
        [FieldOffset(0)] public SuperArmorType superArmor;
        [FieldOffset(1)] public bool isTransform;
        [FieldOffset(4)] public float downTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct JellymanHumanActionRate
    {
        [FieldOffset(0)] public float actionRate__arr0;
        [FieldOffset(4)] public float actionRate__arr1;
        [FieldOffset(8)] public float actionRate__arr2;
        [FieldOffset(12)] public float actionRate__arr3;
        [FieldOffset(16)] public float actionRate__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct JellymanHumanActionConfig
    {
        [FieldOffset(0)]   public JellymanHumanActionRate rateTable__arr0;
        [FieldOffset(20)] public JellymanHumanActionRate rateTable__arr1;
        [FieldOffset(40)] public JellymanHumanActionRate rateTable__arr2;
        [FieldOffset(60)] public JellymanHumanActionRate rateTable__arr3;
        [FieldOffset(80)]  public float coolTime__arr0;
        [FieldOffset(84)] public float coolTime__arr1;
        [FieldOffset(88)] public float coolTime__arr2;
        [FieldOffset(92)] public float coolTime__arr3;
        [FieldOffset(96)] public float coolTime__arr4;
        [FieldOffset(100)] public float attackCoolTime;
        [FieldOffset(104)] public float nearRange;
        [FieldOffset(108)] public int nearRateId;
        [FieldOffset(112)] public int farRateId;
        [FieldOffset(116)] public bool isCounterGuard;
        [FieldOffset(117)] public bool isCounterWall;
        [FieldOffset(118)] public bool isSpikeWall;
        [FieldOffset(120)] public int waveNum;
        [FieldOffset(124)] public float waveUpTime;
        [FieldOffset(128)] public float waveLifeTime;
        [FieldOffset(132)] public float waveDownTime;
        [FieldOffset(136)] public float waveRadius;
        [FieldOffset(140)] public float waveAddRadius;
        [FieldOffset(144)] public float waveSpawnTime;
        [FieldOffset(148)] public float waveKeepRadius;
        [FieldOffset(152)] public float waveHeight;
        [FieldOffset(156)] public int rushNum;
    }

    [StructLayout(LayoutKind.Explicit, Size = 172)]
    public struct EnemyLevelBandConfig
    {
        [FieldOffset(0)]  public int level;
        [FieldOffset(4)]  public JellymanCommonActionConfig common;
        [FieldOffset(12)] public JellymanHumanActionConfig human;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct EnemySquadAvarageLevelConfig
    {
        [FieldOffset(0)]  public int level;
        [FieldOffset(4)]  public int maxActionCount;
        [FieldOffset(8)]  public float spAttackWaitTime;
        [FieldOffset(12)] public int humanMaxActionCount__arr0;
        [FieldOffset(16)] public int humanMaxActionCount__arr1;
        [FieldOffset(20)] public int humanMaxActionCount__arr2;
        [FieldOffset(24)] public int humanMaxActionCount__arr3;
        [FieldOffset(28)] public int humanMaxActionCount__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct EnemySquadConfig
    {
        [FieldOffset(0)] public EnemySquadAvarageLevelConfig averageLevelConfig__arr0;
        [FieldOffset(32)] public EnemySquadAvarageLevelConfig averageLevelConfig__arr1;
        [FieldOffset(64)] public EnemySquadAvarageLevelConfig averageLevelConfig__arr2;
        [FieldOffset(96)] public EnemySquadAvarageLevelConfig averageLevelConfig__arr3;
        [FieldOffset(128)] public EnemySquadAvarageLevelConfig averageLevelConfig__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 7408)]
    public struct EnemyJellymanConfig
    {
        [FieldOffset(0)]    public EnemyCommonConfig commonParams;
        [FieldOffset(5744)] public EnemyLevelConfig levelParams__arr0;
        [FieldOffset(5824)] public EnemyLevelConfig levelParams__arr1;
        [FieldOffset(5904)] public EnemyLevelConfig levelParams__arr2;
        [FieldOffset(5984)] public EnemyLevelConfig levelParams__arr3;
        [FieldOffset(6064)] public EnemyLevelConfig levelParams__arr4;
        [FieldOffset(6144)] public EnemyLevelConfig levelParams__arr5;
        [FieldOffset(6224)] public EnemyLevelConfig levelParams__arr6;
        [FieldOffset(6304)] public EnemyLevelConfig levelParams__arr7;
        [FieldOffset(6384)] public EnemyLevelBandConfig levelBands__arr0;
        [FieldOffset(6556)] public EnemyLevelBandConfig levelBands__arr1;
        [FieldOffset(6728)] public EnemyLevelBandConfig levelBands__arr2;
        [FieldOffset(6900)] public EnemyLevelBandConfig levelBands__arr3;
        [FieldOffset(7072)] public EnemyLevelBandConfig levelBands__arr4;
        [FieldOffset(7244)] public EnemySquadConfig squadParams;
    }

}