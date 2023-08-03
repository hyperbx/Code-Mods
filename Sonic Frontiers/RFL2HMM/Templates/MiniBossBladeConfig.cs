using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossBladeConfigClass
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

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct MiniBossBladeCommonAIParam
    {
        [FieldOffset(0)]  public float backRange;
        [FieldOffset(4)]  public float standRange;
        [FieldOffset(8)]  public float shortRange;
        [FieldOffset(12)] public float middleRange;
        [FieldOffset(16)] public float runEndDistance;
        [FieldOffset(20)] public float dashEndDistance;
        [FieldOffset(24)] public float parryRange;
        [FieldOffset(28)] public float specialBeginDisappearTime;
        [FieldOffset(32)] public float specialEndDisappearTime;
        [FieldOffset(36)] public float endWarpWaitTime;
        [FieldOffset(40)] public float shiftTimeMin;
        [FieldOffset(44)] public float shiftTimeMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct MiniBossBladeCommonParam
    {
        [FieldOffset(0)]  public MiniBossCommonConfig commonConfig;
        [FieldOffset(64)] public MiniBossBladeCommonAIParam ai;
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

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct MiniBossBladeLevelCommonParam
    {
        [FieldOffset(0)]  public float angryHpRatio;
        [FieldOffset(4)]  public float stunTime;
        [FieldOffset(8)]  public float downTime;
        [FieldOffset(12)] public float strikeComboTimer;
        [FieldOffset(16)] public float cyloopComboTimer;
        [FieldOffset(20)] public float blowupComboTimer;
        [FieldOffset(24)] public float attackMotionSpeed;
        [FieldOffset(28)] public float preliminaryMotionSpeed;
        [FieldOffset(32)] public float ghostPreliminaryMotionSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct MiniBossBladeLevelAIParam
    {
        [FieldOffset(0)]  public float firstContactWait;
        [FieldOffset(4)]  public float specialAttackInterval;
        [FieldOffset(8)]  public float shortRangeIntervalMin;
        [FieldOffset(12)] public float shortRangeIntervalMax;
        [FieldOffset(16)] public float middleRangeIntervalMin;
        [FieldOffset(20)] public float middleRangeIntervalMax;
        [FieldOffset(24)] public float counterIntervalMin;
        [FieldOffset(28)] public float counterIntervalMax;
        [FieldOffset(32)] public float afterDashIntervalMin;
        [FieldOffset(36)] public float afterDashIntervalMax;
        [FieldOffset(40)] public float parryIntervalMin;
        [FieldOffset(44)] public float parryIntervalMax;
        [FieldOffset(48)] public float parryDuration;
        [FieldOffset(52)] public float slashComboCoolTime;
        [FieldOffset(56)] public float ghostDashSlashCoolTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1)]
    public struct MiniBossBladeSpecialAttackParam
    {
        [FieldOffset(0)] public byte spawnNum;
    }

    [StructLayout(LayoutKind.Explicit, Size = 156)]
    public struct MiniBossBladeLevelParam
    {
        [FieldOffset(0)]   public int level;
        [FieldOffset(4)]   public MiniBossLevelCommonConfig common;
        [FieldOffset(56)]  public MiniBossBladeLevelCommonParam general;
        [FieldOffset(92)]  public MiniBossBladeLevelAIParam ai;
        [FieldOffset(152)] public MiniBossBladeSpecialAttackParam special;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct MiniBossBladeLevelPhaseAction
    {
        [FieldOffset(0)]  public float verticalSlashRate;
        [FieldOffset(4)]  public float horizontalSlashRate;
        [FieldOffset(8)]  public float slashComboRate;
        [FieldOffset(12)] public float backSlashRate;
        [FieldOffset(16)] public float dashRate;
        [FieldOffset(20)] public float dashSlashRate;
        [FieldOffset(24)] public float ghostDashSlashRate;
        [FieldOffset(28)] public float specialAttackRate;
        [FieldOffset(32)] public bool useTimeStopAttack;
        [FieldOffset(36)] public float guardBeginTime;
        [FieldOffset(40)] public float guardJumpLaserRate;
        [FieldOffset(44)] public float parryJumpLaserRate;
        [FieldOffset(48)] public float cyloopJumpLaserRate;
        [FieldOffset(52)] public float doubleJumpLaserRate;
        [FieldOffset(56)] public bool useParry;
    }

    [StructLayout(LayoutKind.Explicit, Size = 124)]
    public struct MiniBossBladeLevelBand
    {
        [FieldOffset(0)] public uint level;
        [FieldOffset(4)] public MiniBossBladeLevelPhaseAction phases__arr0;
        [FieldOffset(64)] public MiniBossBladeLevelPhaseAction phases__arr1;
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

    [StructLayout(LayoutKind.Explicit, Size = 1552)]
    public struct MiniBossBladeConfig
    {
        [FieldOffset(0)]    public MiniBossBladeCommonParam commonParam;
        [FieldOffset(112)]  public MiniBossBladeLevelParam levelParams__arr0;
        [FieldOffset(268)] public MiniBossBladeLevelParam levelParams__arr1;
        [FieldOffset(424)] public MiniBossBladeLevelParam levelParams__arr2;
        [FieldOffset(580)] public MiniBossBladeLevelParam levelParams__arr3;
        [FieldOffset(736)] public MiniBossBladeLevelParam levelParams__arr4;
        [FieldOffset(892)]  public MiniBossBladeLevelBand levelBands__arr0;
        [FieldOffset(1016)] public MiniBossBladeLevelBand levelBands__arr1;
        [FieldOffset(1140)] public MiniBossBladeLevelBand levelBands__arr2;
        [FieldOffset(1264)] public MiniBossBladeLevelBand levelBands__arr3;
        [FieldOffset(1388)] public MiniBossBladeLevelBand levelBands__arr4;
        [FieldOffset(1512)] public RingParameter ringParam;
    }

}