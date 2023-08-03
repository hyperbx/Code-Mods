using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossFlyerConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct MiniBossCommonConfig
    {
        [FieldOffset(0)]  public float scoutDistance;
        [FieldOffset(4)]  public float scoutDistanceOutside;
        [FieldOffset(8)]  public float zoomDistance;
        [FieldOffset(16)] public Vector3 zoomOffset;
        [FieldOffset(32)] public Vector3 zoomAngle;
        [FieldOffset(48)] public float zoomFov;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct FlyerTrailParam
    {
        [FieldOffset(0)]  public float interval;
        [FieldOffset(4)]  public int recordNumWander;
        [FieldOffset(8)]  public int recordNumWatch;
        [FieldOffset(12)] public int recordNumBattle;
        [FieldOffset(16)] public float width;
        [FieldOffset(20)] public float wallHeight;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct FlyerWanderParam
    {
        [FieldOffset(0)] public float speed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct FlyerWatchShotParam
    {
        [FieldOffset(0)]  public float interval;
        [FieldOffset(4)]  public float readyDuration;
        [FieldOffset(8)]  public float shotAnimSpeed;
        [FieldOffset(12)] public uint shotAnimNum;
        [FieldOffset(16)] public float speed;
        [FieldOffset(20)] public float lifeTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct FlyerWatchParam
    {
        [FieldOffset(0)] public float speed;
        [FieldOffset(4)] public float changeWanderTime;
        [FieldOffset(8)] public FlyerWatchShotParam shot;
    }

    public enum HorizontalType : sbyte
    {
        HorzCenter = 0,
        HorzLeft = 1,
        HorzRight = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 6)]
    public struct FlyerEscapeShotTableData
    {
        [FieldOffset(0)] public HorizontalType horz__arr0;
        [FieldOffset(1)] public HorizontalType horz__arr1;
        [FieldOffset(2)] public HorizontalType horz__arr2;
        [FieldOffset(3)] public HorizontalType horz__arr3;
        [FieldOffset(4)] public HorizontalType horz__arr4;
        [FieldOffset(5)] public HorizontalType horz__arr5;
    }

    [StructLayout(LayoutKind.Explicit, Size = 136)]
    public struct FlyerEscapeShotParam
    {
        [FieldOffset(0)]   public FlyerEscapeShotTableData posTable__arr0;
        [FieldOffset(6)] public FlyerEscapeShotTableData posTable__arr1;
        [FieldOffset(12)] public FlyerEscapeShotTableData posTable__arr2;
        [FieldOffset(18)] public FlyerEscapeShotTableData posTable__arr3;
        [FieldOffset(24)] public FlyerEscapeShotTableData posTable__arr4;
        [FieldOffset(30)] public FlyerEscapeShotTableData posTable__arr5;
        [FieldOffset(36)] public FlyerEscapeShotTableData posTable__arr6;
        [FieldOffset(42)] public FlyerEscapeShotTableData posTable__arr7;
        [FieldOffset(48)] public FlyerEscapeShotTableData posTable__arr8;
        [FieldOffset(54)] public FlyerEscapeShotTableData posTable__arr9;
        [FieldOffset(60)] public FlyerEscapeShotTableData posTable__arr10;
        [FieldOffset(66)] public FlyerEscapeShotTableData posTable__arr11;
        [FieldOffset(72)] public FlyerEscapeShotTableData posTable__arr12;
        [FieldOffset(78)] public FlyerEscapeShotTableData posTable__arr13;
        [FieldOffset(84)] public FlyerEscapeShotTableData posTable__arr14;
        [FieldOffset(90)] public FlyerEscapeShotTableData posTable__arr15;
        [FieldOffset(96)]  public float interval;
        [FieldOffset(100)] public float waitAfterLoop;
        [FieldOffset(104)] public float readyDuration;
        [FieldOffset(108)] public float shotAnimSpeed;
        [FieldOffset(112)] public uint shotAnimNum;
        [FieldOffset(116)] public float initSpeed;
        [FieldOffset(120)] public float maxSpeed;
        [FieldOffset(124)] public float acc;
        [FieldOffset(128)] public float lifeTime;
        [FieldOffset(132)] public float nearest;
    }

    public enum PlayerOffsetType : sbyte
    {
        PLAYER_OFFSET_NORMAL = 0,
        PLAYER_OFFSET_ABSOLUTE = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct FlyerEscapeCameraParam
    {
        [FieldOffset(0)]  public float fovy;
        [FieldOffset(4)]  public float zRot;
        [FieldOffset(8)]  public float distance;
        [FieldOffset(12)] public float pathOffset;
        [FieldOffset(16)] public bool usePathVerticalComponent;
        [FieldOffset(17)] public bool usePathNormal;
        [FieldOffset(20)] public float angleSensitivity;
        [FieldOffset(24)] public float angleSensitivityBoost;
        [FieldOffset(28)] public float azimuthOffsetDeg;
        [FieldOffset(32)] public float elevationOffsetDeg;
        [FieldOffset(36)] public float gravityOffset;
        [FieldOffset(48)] public Vector3 playerOffset;
        [FieldOffset(64)] public PlayerOffsetType playerOffsetType;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct FlyerEscapeQuickStepParam
    {
        [FieldOffset(0)]  public bool enable;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float boostSpeed;
        [FieldOffset(12)] public float boostSpeedMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 256)]
    public struct FlyerEscapeParam
    {
        [FieldOffset(0)]   public float startSpeed;
        [FieldOffset(4)]   public float decrease;
        [FieldOffset(8)]   public float minSpeed;
        [FieldOffset(12)]  public float targetDisableTime;
        [FieldOffset(16)]  public float resetByFallTime;
        [FieldOffset(20)]  public float resetByDistance;
        [FieldOffset(24)]  public FlyerEscapeShotParam shot;
        [FieldOffset(160)] public FlyerEscapeCameraParam camera;
        [FieldOffset(240)] public FlyerEscapeQuickStepParam quickStep;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct FlyerNearStartCamParam
    {
        [FieldOffset(0)]  public float duration;
        [FieldOffset(16)] public Vector3 posOffset;
        [FieldOffset(32)] public float fovy;
        [FieldOffset(36)] public float interpolateTimePush;
        [FieldOffset(40)] public float interpolateTimePop;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct FlyerIdlingNearParam
    {
        [FieldOffset(0)] public float durationMin;
        [FieldOffset(4)] public float durationMax;
        [FieldOffset(8)] public uint selectRatio__arr0;
        [FieldOffset(12)] public uint selectRatio__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct FlyerGuardParam
    {
        [FieldOffset(0)] public float duration;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct FlyerAutoLockonParam
    {
        [FieldOffset(0)]  public float lockonDistance;
        [FieldOffset(4)]  public float unlockDistance;
        [FieldOffset(8)]  public float distance;
        [FieldOffset(12)] public float minElevation;
        [FieldOffset(16)] public float maxElevation;
        [FieldOffset(20)] public float panningSuspensionK;
        [FieldOffset(24)] public float interiorPanningSuspensionK;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct FlyerNearEndLaunchParam
    {
        [FieldOffset(0)]  public float outStrength;
        [FieldOffset(4)]  public float inStrength;
        [FieldOffset(8)]  public float outElev;
        [FieldOffset(12)] public float inElev;
        [FieldOffset(16)] public float speedMin;
        [FieldOffset(20)] public float speedMax;
        [FieldOffset(24)] public float speedMinLength;
        [FieldOffset(28)] public float speedMaxLength;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct FlyerNearParam
    {
        [FieldOffset(0)]   public float duration;
        [FieldOffset(4)]   public float startHABounceUp;
        [FieldOffset(8)]   public float startHABounceBack;
        [FieldOffset(12)]  public float preliminaryMotionSpeed;
        [FieldOffset(16)]  public float resetByDistance;
        [FieldOffset(32)]  public FlyerNearStartCamParam startCam;
        [FieldOffset(80)]  public FlyerIdlingNearParam idling;
        [FieldOffset(96)]  public FlyerGuardParam guard;
        [FieldOffset(100)] public FlyerAutoLockonParam lockon;
        [FieldOffset(128)] public FlyerNearEndLaunchParam launch;
    }

    [StructLayout(LayoutKind.Explicit, Size = 560)]
    public struct MiniBossFlyerCommonParam
    {
        [FieldOffset(0)]   public MiniBossCommonConfig commonConfig;
        [FieldOffset(64)]  public FlyerTrailParam trail;
        [FieldOffset(88)]  public FlyerWanderParam wander;
        [FieldOffset(92)]  public FlyerWatchParam watch;
        [FieldOffset(128)] public FlyerEscapeParam escape;
        [FieldOffset(384)] public FlyerNearParam nearRange;
        [FieldOffset(544)] public float stunTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 52)]
    public struct MiniBossLevelCommonConfig
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
        [FieldOffset(44)] public float attackRate;
        [FieldOffset(48)] public ushort expItemNum;
        [FieldOffset(50)] public ushort exp;
    }

    [StructLayout(LayoutKind.Explicit, Size = 56)]
    public struct MiniBossFlyerLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public MiniBossLevelCommonConfig commonConfig;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct FlayerEscapeShotSequenceTable
    {
        [FieldOffset(0)] public int id;
        [FieldOffset(4)] public float interval;
    }

    [StructLayout(LayoutKind.Explicit, Size = 68)]
    public struct FlayerEscapeShotSequenceTableData
    {
        [FieldOffset(0)] public bool isUse;
        [FieldOffset(4)] public FlayerEscapeShotSequenceTable table__arr0;
        [FieldOffset(12)] public FlayerEscapeShotSequenceTable table__arr1;
        [FieldOffset(20)] public FlayerEscapeShotSequenceTable table__arr2;
        [FieldOffset(28)] public FlayerEscapeShotSequenceTable table__arr3;
        [FieldOffset(36)] public FlayerEscapeShotSequenceTable table__arr4;
        [FieldOffset(44)] public FlayerEscapeShotSequenceTable table__arr5;
        [FieldOffset(52)] public FlayerEscapeShotSequenceTable table__arr6;
        [FieldOffset(60)] public FlayerEscapeShotSequenceTable table__arr7;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1092)]
    public struct MiniBossFlyerLevelBand
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public FlayerEscapeShotSequenceTableData sequence__arr0;
        [FieldOffset(72)] public FlayerEscapeShotSequenceTableData sequence__arr1;
        [FieldOffset(140)] public FlayerEscapeShotSequenceTableData sequence__arr2;
        [FieldOffset(208)] public FlayerEscapeShotSequenceTableData sequence__arr3;
        [FieldOffset(276)] public FlayerEscapeShotSequenceTableData sequence__arr4;
        [FieldOffset(344)] public FlayerEscapeShotSequenceTableData sequence__arr5;
        [FieldOffset(412)] public FlayerEscapeShotSequenceTableData sequence__arr6;
        [FieldOffset(480)] public FlayerEscapeShotSequenceTableData sequence__arr7;
        [FieldOffset(548)] public FlayerEscapeShotSequenceTableData sequence__arr8;
        [FieldOffset(616)] public FlayerEscapeShotSequenceTableData sequence__arr9;
        [FieldOffset(684)] public FlayerEscapeShotSequenceTableData sequence__arr10;
        [FieldOffset(752)] public FlayerEscapeShotSequenceTableData sequence__arr11;
        [FieldOffset(820)] public FlayerEscapeShotSequenceTableData sequence__arr12;
        [FieldOffset(888)] public FlayerEscapeShotSequenceTableData sequence__arr13;
        [FieldOffset(956)] public FlayerEscapeShotSequenceTableData sequence__arr14;
        [FieldOffset(1024)] public FlayerEscapeShotSequenceTableData sequence__arr15;
    }

    [StructLayout(LayoutKind.Explicit, Size = 6304)]
    public struct MiniBossFlyerConfig
    {
        [FieldOffset(0)]   public MiniBossFlyerCommonParam commonParam;
        [FieldOffset(560)] public MiniBossFlyerLevelParam levelParams__arr0;
        [FieldOffset(616)] public MiniBossFlyerLevelParam levelParams__arr1;
        [FieldOffset(672)] public MiniBossFlyerLevelParam levelParams__arr2;
        [FieldOffset(728)] public MiniBossFlyerLevelParam levelParams__arr3;
        [FieldOffset(784)] public MiniBossFlyerLevelParam levelParams__arr4;
        [FieldOffset(840)] public MiniBossFlyerLevelBand levelBand__arr0;
        [FieldOffset(1932)] public MiniBossFlyerLevelBand levelBand__arr1;
        [FieldOffset(3024)] public MiniBossFlyerLevelBand levelBand__arr2;
        [FieldOffset(4116)] public MiniBossFlyerLevelBand levelBand__arr3;
        [FieldOffset(5208)] public MiniBossFlyerLevelBand levelBand__arr4;
    }

}