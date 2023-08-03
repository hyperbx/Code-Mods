using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossSpiderConfigClass
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

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct MiniBossSpiderCameraShake
    {
        [FieldOffset(0)]  public float time;
        [FieldOffset(4)]  public float magnitude;
        [FieldOffset(8)]  public int freq;
        [FieldOffset(12)] public float attnRatio;
        [FieldOffset(16)] public float shakeRange;
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

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct MiniBossSpiderWaveParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float appearRadius;
        [FieldOffset(8)]  public float keepRadius;
        [FieldOffset(12)] public float disappearRadius;
        [FieldOffset(16)] public float heightMin;
        [FieldOffset(20)] public float heightMax;
        [FieldOffset(24)] public float lifeTime;
        [FieldOffset(28)] public float pauseBeginTime;
        [FieldOffset(32)] public float pauseTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct MiniBossSpiderCameraLockOn
    {
        [FieldOffset(0)]  public float time;
        [FieldOffset(4)]  public float distance;
        [FieldOffset(8)]  public float minElevation;
        [FieldOffset(12)] public float maxElevation;
        [FieldOffset(16)] public float panningSuspensionK;
        [FieldOffset(20)] public float interiorPanningSuspensionK;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct DebrisParameter
    {
        [FieldOffset(0)]  public int m_maxNumPieces;
        [FieldOffset(4)]  public float gravity;
        [FieldOffset(8)]  public float lifeTime;
        [FieldOffset(12)] public float force;
    }

    public enum MiniBossSpiderBreakType : sbyte
    {
        BREAK_NONE = 0,
        BREAK_LEG = 1,
        BREAK_AIR_LEG = 2,
        BREAK_BOUNCE_LEG = 3,
        BREAK_GIMMICK = 4,
        BREAK_ALL = 5
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct MiniBossSpiderLevelBandRate
    {
        [FieldOffset(0)]  public float pressRate;
        [FieldOffset(4)]  public float stompRate;
        [FieldOffset(8)]  public float shotRate;
        [FieldOffset(12)] public float chainRate;
        [FieldOffset(16)] public float traceRate;
        [FieldOffset(20)] public float laserStraightRate;
        [FieldOffset(24)] public float laserTraceRate;
        [FieldOffset(28)] public float jumpRate;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct MiniBossSpiderLevelBandInterval
    {
        [FieldOffset(0)]  public float pressInterval;
        [FieldOffset(4)]  public float stompInterval;
        [FieldOffset(8)]  public float shotInterval;
        [FieldOffset(12)] public float chainInterval;
        [FieldOffset(16)] public float traceInterval;
        [FieldOffset(20)] public float laserStaightInterval;
        [FieldOffset(24)] public float laserTraceInterval;
        [FieldOffset(28)] public float jumpInterval;
    }

    [StructLayout(LayoutKind.Explicit, Size = 196)]
    public struct MiniBossSpiderActionParam
    {
        [FieldOffset(0)]   public float nearRange;
        [FieldOffset(4)]   public MiniBossSpiderLevelBandRate nearRates__arr0;
        [FieldOffset(36)] public MiniBossSpiderLevelBandRate nearRates__arr1;
        [FieldOffset(68)]  public MiniBossSpiderLevelBandRate farRates__arr0;
        [FieldOffset(100)] public MiniBossSpiderLevelBandRate farRates__arr1;
        [FieldOffset(132)] public MiniBossSpiderLevelBandInterval interval__arr0;
        [FieldOffset(164)] public MiniBossSpiderLevelBandInterval interval__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1520)]
    public struct MiniBossSpiderCommonParam
    {
        [FieldOffset(0)]   public MiniBossCommonConfig commonConfig;
        [FieldOffset(64)]  public float patrolWalkWaitTimeMin;
        [FieldOffset(68)]  public float patrolWalkWaitTimeMax;
        [FieldOffset(72)]  public float jumpSpeed;
        [FieldOffset(76)]  public float pressDistance;
        [FieldOffset(80)]  public float waveDistance;
        [FieldOffset(84)]  public float waveModelScale;
        [FieldOffset(88)]  public float waveModelDiameter;
        [FieldOffset(92)]  public float waveWaitTime;
        [FieldOffset(96)]  public float mineDistance;
        [FieldOffset(100)] public float shotWaitTime;
        [FieldOffset(104)] public float walkWaitTime;
        [FieldOffset(108)] public float laserStraightDistance;
        [FieldOffset(112)] public float laserStraightPrepairTime;
        [FieldOffset(116)] public float laserStraightTime;
        [FieldOffset(120)] public float laserStraightAngle;
        [FieldOffset(124)] public float laserStraightWaitTime;
        [FieldOffset(128)] public float laserTraceDistance;
        [FieldOffset(132)] public float laserTracePrepairTime;
        [FieldOffset(136)] public float laserTraceTime;
        [FieldOffset(140)] public float laserTraceSpeed;
        [FieldOffset(144)] public float laserTraceWaitTime;
        [FieldOffset(148)] public float chainDistance;
        [FieldOffset(152)] public float chainJumpDistance;
        [FieldOffset(156)] public float chainWaitTime;
        [FieldOffset(160)] public float traceDistance;
        [FieldOffset(164)] public float traceJumpDistance;
        [FieldOffset(168)] public float traceSpeed;
        [FieldOffset(172)] public float traceRotSpeed;
        [FieldOffset(176)] public float traceLifeTime;
        [FieldOffset(180)] public float traceWidth;
        [FieldOffset(184)] public float traceHeight;
        [FieldOffset(188)] public float traceAppearDistance;
        [FieldOffset(192)] public float traceKeepDistance;
        [FieldOffset(196)] public float traceDisappearDistance;
        [FieldOffset(200)] public float traceWaitTime;
        [FieldOffset(204)] public float thornSpawnSpeed;
        [FieldOffset(208)] public float thornSpawnRadiusMax;
        [FieldOffset(212)] public float thornLifeTime;
        [FieldOffset(216)] public float thornFlyingSpeed;
        [FieldOffset(220)] public int protecterHp;
        [FieldOffset(224)] public MiniBossSpiderCameraShake cameraShakeWalk;
        [FieldOffset(244)] public MiniBossSpiderCameraShake cameraShakeAttack;
        [FieldOffset(264)] public RingParameter ringParam;
        [FieldOffset(292)] public MiniBossSpiderWaveParam waveParams__arr0;
        [FieldOffset(328)] public MiniBossSpiderWaveParam waveParams__arr1;
        [FieldOffset(364)] public MiniBossSpiderWaveParam waveParams__arr2;
        [FieldOffset(400)] public MiniBossSpiderWaveParam waveParams__arr3;
        [FieldOffset(436)] public MiniBossSpiderWaveParam waveParams__arr4;
        [FieldOffset(472)] public MiniBossSpiderWaveParam waveParams__arr5;
        [FieldOffset(508)] public MiniBossSpiderWaveParam waveParams__arr6;
        [FieldOffset(544)] public MiniBossSpiderWaveParam waveParams__arr7;
        [FieldOffset(580)] public MiniBossSpiderCameraLockOn cameraLockBreakArmor;
        [FieldOffset(604)] public MiniBossSpiderCameraLockOn cameraLockBlownUp;
        [FieldOffset(628)] public MiniBossSpiderCameraLockOn cameraLockBlownDown;
        [FieldOffset(652)] public MiniBossSpiderCameraLockOn cameraLockFootUp;
        [FieldOffset(676)] public MiniBossSpiderCameraLockOn cameraLockFall;
        [FieldOffset(700)] public DebrisParameter debrisSet;
        [FieldOffset(716)] public MiniBossSpiderBreakType rotationTypeTable__arr0;
        [FieldOffset(717)] public MiniBossSpiderBreakType rotationTypeTable__arr1;
        [FieldOffset(718)] public MiniBossSpiderBreakType rotationTypeTable__arr2;
        [FieldOffset(719)] public MiniBossSpiderBreakType rotationTypeTable__arr3;
        [FieldOffset(720)] public MiniBossSpiderBreakType rotationTypeTable__arr4;
        [FieldOffset(721)] public MiniBossSpiderBreakType rotationTypeTable__arr5;
        [FieldOffset(722)] public MiniBossSpiderBreakType rotationTypeTable__arr6;
        [FieldOffset(723)] public MiniBossSpiderBreakType rotationTypeTable__arr7;
        [FieldOffset(724)] public MiniBossSpiderActionParam rotationActionTable__arr0;
        [FieldOffset(920)] public MiniBossSpiderActionParam rotationActionTable__arr1;
        [FieldOffset(1116)] public MiniBossSpiderActionParam rotationActionTable__arr2;
        [FieldOffset(1312)] public MiniBossSpiderActionParam rotationActionTable__arr3;
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

    [StructLayout(LayoutKind.Explicit, Size = 84)]
    public struct MiniBossSpiderLevelParam
    {
        [FieldOffset(0)]  public int level;
        [FieldOffset(4)]  public MiniBossLevelCommonConfig commonConfig;
        [FieldOffset(56)] public float attackRate;
        [FieldOffset(60)] public float stunTime;
        [FieldOffset(64)] public float downTime;
        [FieldOffset(68)] public float downTime2;
        [FieldOffset(72)] public float reProtectWaitTime;
        [FieldOffset(76)] public float patrolWalkWaitTimeMin;
        [FieldOffset(80)] public float patrolWalkWaitTimeMax;
    }

    public enum MiniBossSpiderLevelBand_MiniBossSpiderBreakType : sbyte
    {
        MiniBossSpiderLevelBand_MiniBossSpiderBreakType_BREAK_NONE = 0,
        MiniBossSpiderLevelBand_MiniBossSpiderBreakType_BREAK_LEG = 1,
        MiniBossSpiderLevelBand_MiniBossSpiderBreakType_BREAK_AIR_LEG = 2,
        MiniBossSpiderLevelBand_MiniBossSpiderBreakType_BREAK_BOUNCE_LEG = 3,
        MiniBossSpiderLevelBand_MiniBossSpiderBreakType_BREAK_GIMMICK = 4,
        MiniBossSpiderLevelBand_MiniBossSpiderBreakType_BREAK_ALL = 5
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct MiniBossSpiderLevelPhaseAction
    {
        [FieldOffset(0)] public sbyte pressType;
        [FieldOffset(1)] public byte pressNum;
        [FieldOffset(4)] public float pressWaitTime;
        [FieldOffset(8)] public sbyte stompType;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct MiniBossSpiderLevelPhaseDiving
    {
        [FieldOffset(0)] public float divingEndHeight;
    }

    [StructLayout(LayoutKind.Explicit, Size = 336)]
    public struct MiniBossSpiderLevelBand
    {
        [FieldOffset(0)]   public int level;
        [FieldOffset(4)]   public float phaseChangeHpRatio;
        [FieldOffset(8)]   public int walkWaveId;
        [FieldOffset(12)]  public int stompWaveId;
        [FieldOffset(16)]  public int pressWaveId;
        [FieldOffset(20)]  public bool enableCounterKick;
        [FieldOffset(21)]  public MiniBossSpiderLevelBand_MiniBossSpiderBreakType breakType;
        [FieldOffset(24)]  public float mineRadius;
        [FieldOffset(28)]  public float mineExplodeRadius;
        [FieldOffset(32)]  public int mineNum;
        [FieldOffset(36)]  public float mineStartSpeed;
        [FieldOffset(40)]  public float mineDecelePower;
        [FieldOffset(44)]  public float mineMinSpeed;
        [FieldOffset(48)]  public float mineParriedSpeed;
        [FieldOffset(52)]  public float mineLifeTime;
        [FieldOffset(56)]  public float mineEnableParryRate;
        [FieldOffset(60)]  public int mineHorizonMaxNum;
        [FieldOffset(64)]  public int mineVerticalNum;
        [FieldOffset(68)]  public int shotCount;
        [FieldOffset(72)]  public float chainLifeTime;
        [FieldOffset(76)]  public float chainTraceTime;
        [FieldOffset(80)]  public float chainSpeed;
        [FieldOffset(84)]  public float chainWaitTime;
        [FieldOffset(88)]  public float chainRotateSpeed;
        [FieldOffset(92)]  public int chainWaveNum;
        [FieldOffset(96)]  public bool enableReProtect;
        [FieldOffset(100)] public float nearRange;
        [FieldOffset(104)] public MiniBossSpiderLevelBandRate nearRates__arr0;
        [FieldOffset(136)] public MiniBossSpiderLevelBandRate nearRates__arr1;
        [FieldOffset(168)] public MiniBossSpiderLevelBandRate farRates__arr0;
        [FieldOffset(200)] public MiniBossSpiderLevelBandRate farRates__arr1;
        [FieldOffset(232)] public MiniBossSpiderLevelPhaseAction phases__arr0;
        [FieldOffset(244)] public MiniBossSpiderLevelPhaseAction phases__arr1;
        [FieldOffset(256)] public MiniBossSpiderLevelBandInterval interval__arr0;
        [FieldOffset(288)] public MiniBossSpiderLevelBandInterval interval__arr1;
        [FieldOffset(320)] public MiniBossSpiderLevelPhaseDiving diving__arr0;
        [FieldOffset(324)] public MiniBossSpiderLevelPhaseDiving diving__arr1;
        [FieldOffset(328)] public float slowRate__arr0;
        [FieldOffset(332)] public float slowRate__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3632)]
    public struct MiniBossSpiderConfig
    {
        [FieldOffset(0)]    public MiniBossSpiderCommonParam commonParam;
        [FieldOffset(1520)] public MiniBossSpiderLevelParam levelParams__arr0;
        [FieldOffset(1604)] public MiniBossSpiderLevelParam levelParams__arr1;
        [FieldOffset(1688)] public MiniBossSpiderLevelParam levelParams__arr2;
        [FieldOffset(1772)] public MiniBossSpiderLevelParam levelParams__arr3;
        [FieldOffset(1856)] public MiniBossSpiderLevelParam levelParams__arr4;
        [FieldOffset(1940)] public MiniBossSpiderLevelBand levelBands__arr0;
        [FieldOffset(2276)] public MiniBossSpiderLevelBand levelBands__arr1;
        [FieldOffset(2612)] public MiniBossSpiderLevelBand levelBands__arr2;
        [FieldOffset(2948)] public MiniBossSpiderLevelBand levelBands__arr3;
        [FieldOffset(3284)] public MiniBossSpiderLevelBand levelBands__arr4;
    }

}