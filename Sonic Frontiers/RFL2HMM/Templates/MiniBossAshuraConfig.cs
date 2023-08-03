using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossAshuraConfigClass
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

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct MiniBossAshuraCommonParam
    {
        [FieldOffset(0)] public MiniBossCommonConfig commonConfig;
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
    public struct MiniBossAshuraLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public MiniBossLevelCommonConfig commonConfig;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct MiniBossAshuraLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct MiniBossAshuraObjectCircleLaser
    {
        [FieldOffset(0)]  public float rotationSpeed;
        [FieldOffset(4)]  public float moveRadiusMin;
        [FieldOffset(8)]  public float moveRadiusMax;
        [FieldOffset(12)] public float initKeepTime;
        [FieldOffset(16)] public float scaleUpTime;
        [FieldOffset(20)] public float scaleUpKeepTime;
        [FieldOffset(24)] public float scaleDownTime;
        [FieldOffset(28)] public float scaleDownKeepTime;
        [FieldOffset(32)] public int num;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct MiniBossAshuraObjectCrawlSpark
    {
        [FieldOffset(0)]  public int createNum;
        [FieldOffset(4)]  public int createParkourNum;
        [FieldOffset(8)]  public float createCycleTime;
        [FieldOffset(12)] public float moveSpeed;
        [FieldOffset(16)] public float lifeTime;
        [FieldOffset(20)] public float homingMaxAngle;
        [FieldOffset(24)] public float homingStartTime;
        [FieldOffset(28)] public float homingPowerMaxTime;
        [FieldOffset(32)] public float meanderingPower;
        [FieldOffset(36)] public float meanderingCycleTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct MiniBossAshuraObjectDashCircleBulletParamByType
    {
        [FieldOffset(0)]  public float ocTime;
        [FieldOffset(4)]  public float dashSpeed;
        [FieldOffset(8)]  public float ocTimeOnGround;
        [FieldOffset(12)] public float dashSpeedOnGround;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct MiniBossAshuraObjectDashCircleBullet
    {
        [FieldOffset(0)]  public float moveSpeed;
        [FieldOffset(4)]  public float lifeTime;
        [FieldOffset(8)]  public MiniBossAshuraObjectDashCircleBulletParamByType frontType;
        [FieldOffset(24)] public MiniBossAshuraObjectDashCircleBulletParamByType backType;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct MiniBossAshuraObjectSlamWave
    {
        [FieldOffset(0)] public float blowOffRadius;
        [FieldOffset(4)] public float blowOffHeight;
        [FieldOffset(8)] public float killRadius;
    }

    [StructLayout(LayoutKind.Explicit, Size = 128)]
    public struct MiniBossAshuraObjectParam
    {
        [FieldOffset(0)]   public MiniBossAshuraObjectCircleLaser circleLaser;
        [FieldOffset(36)]  public MiniBossAshuraObjectCrawlSpark crawlSpark;
        [FieldOffset(76)]  public MiniBossAshuraObjectDashCircleBullet dashCircleBullet;
        [FieldOffset(116)] public MiniBossAshuraObjectSlamWave slamWave;
    }

    public enum OnArmCircleBulletType : sbyte
    {
        CBT_NONE = 0,
        CBT_FRONT = 1,
        CBT_BACK = 2,
        NUM_CBT = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct MiniBossAshuraPhaseOnArmCircleBulletPos
    {
        [FieldOffset(0)]  public OnArmCircleBulletType left;
        [FieldOffset(1)]  public OnArmCircleBulletType center;
        [FieldOffset(2)]  public OnArmCircleBulletType right;
        [FieldOffset(4)]  public float leftOffsetAngle;
        [FieldOffset(8)]  public float centerOffsetAngle;
        [FieldOffset(12)] public float rightOffsetAngle;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct MiniBossAshuraPhaseParam
    {
        [FieldOffset(0)]   public bool isCircleLaser;
        [FieldOffset(1)]   public bool isCrawlSpark;
        [FieldOffset(2)]   public bool isAttackArmWave;
        [FieldOffset(3)]   public bool isAttackArmCircleBulletOnArm;
        [FieldOffset(4)]   public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr0;
        [FieldOffset(20)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr1;
        [FieldOffset(36)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr2;
        [FieldOffset(52)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr3;
        [FieldOffset(68)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr4;
        [FieldOffset(84)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr5;
        [FieldOffset(100)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr6;
        [FieldOffset(116)] public MiniBossAshuraPhaseOnArmCircleBulletPos onArmCircleBullets__arr7;
        [FieldOffset(132)] public bool isAttackArmCircleBullet;
        [FieldOffset(136)] public int circleBulletBackTypeFreq;
        [FieldOffset(140)] public int circleBulletCreateNum;
        [FieldOffset(144)] public float circleBulletCreateAngle;
        [FieldOffset(148)] public float circleJumpTargetDistace;
        [FieldOffset(152)] public float circleBulletCreateIntervalTime;
        [FieldOffset(156)] public int armAttackConsecutiveNum;
    }

    [StructLayout(LayoutKind.Explicit, Size = 976)]
    public struct MiniBossAshuraConfig
    {
        [FieldOffset(0)]   public MiniBossAshuraCommonParam commonParam;
        [FieldOffset(64)]  public MiniBossAshuraLevelParam levelParams__arr0;
        [FieldOffset(120)] public MiniBossAshuraLevelParam levelParams__arr1;
        [FieldOffset(176)] public MiniBossAshuraLevelParam levelParams__arr2;
        [FieldOffset(232)] public MiniBossAshuraLevelParam levelParams__arr3;
        [FieldOffset(288)] public MiniBossAshuraLevelParam levelParams__arr4;
        [FieldOffset(344)] public MiniBossAshuraLevelBand levelBand__arr0;
        [FieldOffset(348)] public MiniBossAshuraLevelBand levelBand__arr1;
        [FieldOffset(352)] public MiniBossAshuraLevelBand levelBand__arr2;
        [FieldOffset(356)] public MiniBossAshuraLevelBand levelBand__arr3;
        [FieldOffset(360)] public MiniBossAshuraLevelBand levelBand__arr4;
        [FieldOffset(364)] public MiniBossAshuraObjectParam objectParam;
        [FieldOffset(492)] public MiniBossAshuraPhaseParam phaseParam__arr0;
        [FieldOffset(652)] public MiniBossAshuraPhaseParam phaseParam__arr1;
        [FieldOffset(812)] public MiniBossAshuraPhaseParam phaseParam__arr2;
    }

}