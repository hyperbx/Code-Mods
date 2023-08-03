using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossStriderConfigClass
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
    public struct MiniBossStriderCommonParam
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
    public struct MiniBossStriderLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public MiniBossLevelCommonConfig commonConfig;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct MiniBossStriderLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    public enum MeansOfAttack : byte
    {
        Bullet = 0,
        Laser = 1,
        NumAttackTypes = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct AttackInfo
    {
        [FieldOffset(0)] public MeansOfAttack meansOfAttack;
        [FieldOffset(1)] public bool enabled;
        [FieldOffset(4)] public float attackInterval;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct AttackPhase
    {
        [FieldOffset(0)]  public AttackInfo attackInfos__arr0;
        [FieldOffset(8)] public AttackInfo attackInfos__arr1;
        [FieldOffset(16)] public float triggeredHPRatio;
    }

    [StructLayout(LayoutKind.Explicit, Size = 140)]
    public struct MiniBossStriderParam
    {
        [FieldOffset(0)]   public AttackPhase attackPhases__arr0;
        [FieldOffset(20)] public AttackPhase attackPhases__arr1;
        [FieldOffset(40)] public AttackPhase attackPhases__arr2;
        [FieldOffset(60)]  public float initialAttackWaitBullet;
        [FieldOffset(64)]  public float initialAttackWaitLaser;
        [FieldOffset(68)]  public float attackableTime;
        [FieldOffset(72)]  public float railBulletAttackInterval;
        [FieldOffset(76)]  public float tentativePlatformTopYOffset;
        [FieldOffset(80)]  public float tentativePlatformBottomYOffset;
        [FieldOffset(84)]  public float tentativePlatformRadius;
        [FieldOffset(88)]  public float cameraElevation;
        [FieldOffset(92)]  public float cameraFovy;
        [FieldOffset(96)]  public float cameraDistance;
        [FieldOffset(100)] public float cameraDegreeForClockwiseMovement;
        [FieldOffset(104)] public float cameraDegreeForCounterClockwiseMovement;
        [FieldOffset(108)] public float cameraLookAtPointOffsetY;
        [FieldOffset(112)] public float cameraMaxChangeableDegreeByStickInput;
        [FieldOffset(116)] public float cameraMaxDegreeChangedByStickInputPerSec;
        [FieldOffset(120)] public float attackableCameraElevation;
        [FieldOffset(124)] public float attackableCameraDistance;
        [FieldOffset(128)] public float attackableCameraInterpolationTime;
        [FieldOffset(132)] public float attackableCameraDuration;
        [FieldOffset(136)] public bool enableAttackableCamera;
        [FieldOffset(137)] public bool enableStun;
        [FieldOffset(138)] public bool enableStagger;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct ObjStriderGrindRailParam
    {
        [FieldOffset(0)]  public float radius1;
        [FieldOffset(4)]  public float radius2;
        [FieldOffset(8)]  public float radius3;
        [FieldOffset(12)] public float yOffset1;
        [FieldOffset(16)] public float yOffset2;
        [FieldOffset(20)] public float yOffset3;
        [FieldOffset(24)] public byte numRailBulletsFiredAtOnce;
        [FieldOffset(28)] public float railBulletPreAttackEffectTime;
        [FieldOffset(32)] public float railBulletRadius;
        [FieldOffset(36)] public float railBulletSearchDistance;
        [FieldOffset(40)] public float maxJumpDistanceFromRailBullet;
        [FieldOffset(44)] public float distToDestWithinWhichJumpIsDone;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct ObjStriderPlatformParam
    {
        [FieldOffset(0)] public float colliderRadius;
        [FieldOffset(4)] public float colliderHeight;
    }

    [StructLayout(LayoutKind.Explicit, Size = 560)]
    public struct MiniBossStriderConfig
    {
        [FieldOffset(0)]   public MiniBossStriderCommonParam commonParam;
        [FieldOffset(64)]  public MiniBossStriderLevelParam levelParams__arr0;
        [FieldOffset(120)] public MiniBossStriderLevelParam levelParams__arr1;
        [FieldOffset(176)] public MiniBossStriderLevelParam levelParams__arr2;
        [FieldOffset(232)] public MiniBossStriderLevelParam levelParams__arr3;
        [FieldOffset(288)] public MiniBossStriderLevelParam levelParams__arr4;
        [FieldOffset(344)] public MiniBossStriderLevelBand levelBand__arr0;
        [FieldOffset(348)] public MiniBossStriderLevelBand levelBand__arr1;
        [FieldOffset(352)] public MiniBossStriderLevelBand levelBand__arr2;
        [FieldOffset(356)] public MiniBossStriderLevelBand levelBand__arr3;
        [FieldOffset(360)] public MiniBossStriderLevelBand levelBand__arr4;
        [FieldOffset(364)] public MiniBossStriderParam striderParam;
        [FieldOffset(504)] public ObjStriderGrindRailParam grindRailParam;
        [FieldOffset(552)] public ObjStriderPlatformParam platformParam;
    }

}