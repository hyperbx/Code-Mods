using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossWarshipConfigClass
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

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct MiniBossWarshipSpeedParam
    {
        [FieldOffset(0)]  public float highSpeed;
        [FieldOffset(4)]  public float lowSpeed;
        [FieldOffset(8)]  public float changeLowSpeedDistance;
        [FieldOffset(12)] public float disableDistanceMaxSpeed;
        [FieldOffset(16)] public float relativeSpeedDisableDistance;
        [FieldOffset(20)] public float speedOnJump;
        [FieldOffset(24)] public float speedDownOnJumpDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct MiniBossWarshipAccelSpeed
    {
        [FieldOffset(0)] public float min;
        [FieldOffset(4)] public float max;
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct MiniBossWarshipWarpCameraParam
    {
        [FieldOffset(0)]  public float zoomDistance;
        [FieldOffset(16)] public Vector3 zoomOffset;
        [FieldOffset(32)] public Vector3 zoomAngle;
        [FieldOffset(48)] public float zoomFov;
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct MiniBossWarshipEscapeCameraParam
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
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct MiniBossWarshipObjectParam
    {
        [FieldOffset(0)]  public float dashRingAppearDistance;
        [FieldOffset(4)]  public float dashRingDisappearDistance;
        [FieldOffset(8)]  public float birdAppearDistance;
        [FieldOffset(12)] public float birdDisappearDistance;
        [FieldOffset(16)] public float bulletAppearDistance;
        [FieldOffset(20)] public float bulletDisappearDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct WarshipNearLaunchParam
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

    [StructLayout(LayoutKind.Explicit, Size = 304)]
    public struct MiniBossWarshipCommonParam
    {
        [FieldOffset(0)]   public MiniBossCommonConfig commonConfig;
        [FieldOffset(64)]  public MiniBossWarshipSpeedParam speedParam;
        [FieldOffset(92)]  public MiniBossWarshipAccelSpeed normalSpeedParam;
        [FieldOffset(100)] public MiniBossWarshipAccelSpeed boostSpeedParam;
        [FieldOffset(112)] public MiniBossWarshipWarpCameraParam warpCameraParam;
        [FieldOffset(176)] public MiniBossWarshipEscapeCameraParam escapeCameraParam;
        [FieldOffset(240)] public MiniBossWarshipObjectParam objectParam;
        [FieldOffset(264)] public WarshipNearLaunchParam launchParam;
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
    public struct MiniBossWarshipLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public MiniBossLevelCommonConfig commonConfig;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct MiniBossWarshipLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct MiniBossWarshipRecoverBoostGaugeParam
    {
        [FieldOffset(0)] public float normal;
        [FieldOffset(4)] public float boost;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct MiniBossWarshipAttackStateParam
    {
        [FieldOffset(0)]  public float moveSpeed;
        [FieldOffset(4)]  public float bombDropSpeed;
        [FieldOffset(8)]  public float bombInterval;
        [FieldOffset(12)] public float explosionRadius;
        [FieldOffset(16)] public float bombPreDistEffectRange;
        [FieldOffset(20)] public float lifeTime;
        [FieldOffset(24)] public float preBombTime;
        [FieldOffset(28)] public float preBombStateSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct MiniBossWarshipBattleFlagParam
    {
        [FieldOffset(0)] public float firstFinishTimer;
        [FieldOffset(4)] public float finishTimer;
        [FieldOffset(8)] public float disableHomingTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct MiniBossWarshipNearBattleCameraParam
    {
        [FieldOffset(0)]  public float distance;
        [FieldOffset(4)]  public float minElevation;
        [FieldOffset(8)]  public float maxElevation;
        [FieldOffset(12)] public float targetUpOffset;
        [FieldOffset(16)] public float targetMinUpOffsetLimit;
        [FieldOffset(20)] public float targetMaxUpOffsetLimit;
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

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct WarshipPathSectionInfo
    {
        [FieldOffset(0)] public bool enable;
        [FieldOffset(4)] public float start;
        [FieldOffset(8)] public float end;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1216)]
    public struct WarshipEscapePathInfo
    {
        [FieldOffset(0)]   public CString followPaths;
        [FieldOffset(16)]  public WarshipPathSectionInfo usePathInfo__arr0;
        [FieldOffset(28)] public WarshipPathSectionInfo usePathInfo__arr1;
        [FieldOffset(40)] public WarshipPathSectionInfo usePathInfo__arr2;
        [FieldOffset(52)] public WarshipPathSectionInfo usePathInfo__arr3;
        [FieldOffset(64)] public WarshipPathSectionInfo usePathInfo__arr4;
        [FieldOffset(76)] public WarshipPathSectionInfo usePathInfo__arr5;
        [FieldOffset(88)] public WarshipPathSectionInfo usePathInfo__arr6;
        [FieldOffset(100)] public WarshipPathSectionInfo usePathInfo__arr7;
        [FieldOffset(112)] public WarshipPathSectionInfo usePathInfo__arr8;
        [FieldOffset(124)] public WarshipPathSectionInfo usePathInfo__arr9;
        [FieldOffset(136)] public WarshipPathSectionInfo usePathInfo__arr10;
        [FieldOffset(148)] public WarshipPathSectionInfo usePathInfo__arr11;
        [FieldOffset(160)] public WarshipPathSectionInfo usePathInfo__arr12;
        [FieldOffset(172)] public WarshipPathSectionInfo usePathInfo__arr13;
        [FieldOffset(184)] public WarshipPathSectionInfo usePathInfo__arr14;
        [FieldOffset(196)] public WarshipPathSectionInfo usePathInfo__arr15;
        [FieldOffset(208)] public WarshipPathSectionInfo usePathInfo__arr16;
        [FieldOffset(220)] public WarshipPathSectionInfo usePathInfo__arr17;
        [FieldOffset(232)] public WarshipPathSectionInfo usePathInfo__arr18;
        [FieldOffset(244)] public WarshipPathSectionInfo usePathInfo__arr19;
        [FieldOffset(256)] public WarshipPathSectionInfo usePathInfo__arr20;
        [FieldOffset(268)] public WarshipPathSectionInfo usePathInfo__arr21;
        [FieldOffset(280)] public WarshipPathSectionInfo usePathInfo__arr22;
        [FieldOffset(292)] public WarshipPathSectionInfo usePathInfo__arr23;
        [FieldOffset(304)] public WarshipPathSectionInfo usePathInfo__arr24;
        [FieldOffset(316)] public WarshipPathSectionInfo usePathInfo__arr25;
        [FieldOffset(328)] public WarshipPathSectionInfo usePathInfo__arr26;
        [FieldOffset(340)] public WarshipPathSectionInfo usePathInfo__arr27;
        [FieldOffset(352)] public WarshipPathSectionInfo usePathInfo__arr28;
        [FieldOffset(364)] public WarshipPathSectionInfo usePathInfo__arr29;
        [FieldOffset(376)] public WarshipPathSectionInfo usePathInfo__arr30;
        [FieldOffset(388)] public WarshipPathSectionInfo usePathInfo__arr31;
        [FieldOffset(400)] public WarshipPathSectionInfo usePathInfo__arr32;
        [FieldOffset(412)] public WarshipPathSectionInfo usePathInfo__arr33;
        [FieldOffset(424)] public WarshipPathSectionInfo usePathInfo__arr34;
        [FieldOffset(436)] public WarshipPathSectionInfo usePathInfo__arr35;
        [FieldOffset(448)] public WarshipPathSectionInfo usePathInfo__arr36;
        [FieldOffset(460)] public WarshipPathSectionInfo usePathInfo__arr37;
        [FieldOffset(472)] public WarshipPathSectionInfo usePathInfo__arr38;
        [FieldOffset(484)] public WarshipPathSectionInfo usePathInfo__arr39;
        [FieldOffset(496)] public WarshipPathSectionInfo usePathInfo__arr40;
        [FieldOffset(508)] public WarshipPathSectionInfo usePathInfo__arr41;
        [FieldOffset(520)] public WarshipPathSectionInfo usePathInfo__arr42;
        [FieldOffset(532)] public WarshipPathSectionInfo usePathInfo__arr43;
        [FieldOffset(544)] public WarshipPathSectionInfo usePathInfo__arr44;
        [FieldOffset(556)] public WarshipPathSectionInfo usePathInfo__arr45;
        [FieldOffset(568)] public WarshipPathSectionInfo usePathInfo__arr46;
        [FieldOffset(580)] public WarshipPathSectionInfo usePathInfo__arr47;
        [FieldOffset(592)] public WarshipPathSectionInfo usePathInfo__arr48;
        [FieldOffset(604)] public WarshipPathSectionInfo usePathInfo__arr49;
        [FieldOffset(616)] public WarshipPathSectionInfo accelInfo__arr0;
        [FieldOffset(628)] public WarshipPathSectionInfo accelInfo__arr1;
        [FieldOffset(640)] public WarshipPathSectionInfo accelInfo__arr2;
        [FieldOffset(652)] public WarshipPathSectionInfo accelInfo__arr3;
        [FieldOffset(664)] public WarshipPathSectionInfo accelInfo__arr4;
        [FieldOffset(676)] public WarshipPathSectionInfo accelInfo__arr5;
        [FieldOffset(688)] public WarshipPathSectionInfo accelInfo__arr6;
        [FieldOffset(700)] public WarshipPathSectionInfo accelInfo__arr7;
        [FieldOffset(712)] public WarshipPathSectionInfo accelInfo__arr8;
        [FieldOffset(724)] public WarshipPathSectionInfo accelInfo__arr9;
        [FieldOffset(736)] public WarshipPathSectionInfo accelInfo__arr10;
        [FieldOffset(748)] public WarshipPathSectionInfo accelInfo__arr11;
        [FieldOffset(760)] public WarshipPathSectionInfo accelInfo__arr12;
        [FieldOffset(772)] public WarshipPathSectionInfo accelInfo__arr13;
        [FieldOffset(784)] public WarshipPathSectionInfo accelInfo__arr14;
        [FieldOffset(796)] public WarshipPathSectionInfo accelInfo__arr15;
        [FieldOffset(808)] public WarshipPathSectionInfo accelInfo__arr16;
        [FieldOffset(820)] public WarshipPathSectionInfo accelInfo__arr17;
        [FieldOffset(832)] public WarshipPathSectionInfo accelInfo__arr18;
        [FieldOffset(844)] public WarshipPathSectionInfo accelInfo__arr19;
        [FieldOffset(856)] public WarshipPathSectionInfo accelInfo__arr20;
        [FieldOffset(868)] public WarshipPathSectionInfo accelInfo__arr21;
        [FieldOffset(880)] public WarshipPathSectionInfo accelInfo__arr22;
        [FieldOffset(892)] public WarshipPathSectionInfo accelInfo__arr23;
        [FieldOffset(904)] public WarshipPathSectionInfo accelInfo__arr24;
        [FieldOffset(916)] public WarshipPathSectionInfo accelInfo__arr25;
        [FieldOffset(928)] public WarshipPathSectionInfo accelInfo__arr26;
        [FieldOffset(940)] public WarshipPathSectionInfo accelInfo__arr27;
        [FieldOffset(952)] public WarshipPathSectionInfo accelInfo__arr28;
        [FieldOffset(964)] public WarshipPathSectionInfo accelInfo__arr29;
        [FieldOffset(976)] public WarshipPathSectionInfo accelInfo__arr30;
        [FieldOffset(988)] public WarshipPathSectionInfo accelInfo__arr31;
        [FieldOffset(1000)] public WarshipPathSectionInfo accelInfo__arr32;
        [FieldOffset(1012)] public WarshipPathSectionInfo accelInfo__arr33;
        [FieldOffset(1024)] public WarshipPathSectionInfo accelInfo__arr34;
        [FieldOffset(1036)] public WarshipPathSectionInfo accelInfo__arr35;
        [FieldOffset(1048)] public WarshipPathSectionInfo accelInfo__arr36;
        [FieldOffset(1060)] public WarshipPathSectionInfo accelInfo__arr37;
        [FieldOffset(1072)] public WarshipPathSectionInfo accelInfo__arr38;
        [FieldOffset(1084)] public WarshipPathSectionInfo accelInfo__arr39;
        [FieldOffset(1096)] public WarshipPathSectionInfo accelInfo__arr40;
        [FieldOffset(1108)] public WarshipPathSectionInfo accelInfo__arr41;
        [FieldOffset(1120)] public WarshipPathSectionInfo accelInfo__arr42;
        [FieldOffset(1132)] public WarshipPathSectionInfo accelInfo__arr43;
        [FieldOffset(1144)] public WarshipPathSectionInfo accelInfo__arr44;
        [FieldOffset(1156)] public WarshipPathSectionInfo accelInfo__arr45;
        [FieldOffset(1168)] public WarshipPathSectionInfo accelInfo__arr46;
        [FieldOffset(1180)] public WarshipPathSectionInfo accelInfo__arr47;
        [FieldOffset(1192)] public WarshipPathSectionInfo accelInfo__arr48;
        [FieldOffset(1204)] public WarshipPathSectionInfo accelInfo__arr49;
    }

    [StructLayout(LayoutKind.Explicit, Size = 6080)]
    public struct MiniBossWarshipEscapePathParam
    {
        [FieldOffset(0)] public WarshipEscapePathInfo escapePathInfo__arr0;
        [FieldOffset(1216)] public WarshipEscapePathInfo escapePathInfo__arr1;
        [FieldOffset(2432)] public WarshipEscapePathInfo escapePathInfo__arr2;
        [FieldOffset(3648)] public WarshipEscapePathInfo escapePathInfo__arr3;
        [FieldOffset(4864)] public WarshipEscapePathInfo escapePathInfo__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct MiniBossWarshipBombAttackCameraParam
    {
        [FieldOffset(0)]  public float lockonDistance;
        [FieldOffset(4)]  public float unlockDistance;
        [FieldOffset(8)]  public float duration;
        [FieldOffset(12)] public float distance;
        [FieldOffset(16)] public float minElevation;
        [FieldOffset(20)] public float maxElevation;
        [FieldOffset(24)] public float lockonFrameYOffset;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct MiniBossWarshipAttackStateCameraParam
    {
        [FieldOffset(0)]  public float midCameraPosOffset;
        [FieldOffset(4)]  public MiniBossWarshipBombAttackCameraParam firstCamera;
        [FieldOffset(32)] public MiniBossWarshipBombAttackCameraParam secondCamera;
    }

    [StructLayout(LayoutKind.Explicit, Size = 31456)]
    public struct MiniBossWarshipConfig
    {
        [FieldOffset(0)]     public MiniBossWarshipCommonParam commonParam;
        [FieldOffset(304)]   public MiniBossWarshipLevelParam levelParams__arr0;
        [FieldOffset(360)] public MiniBossWarshipLevelParam levelParams__arr1;
        [FieldOffset(416)] public MiniBossWarshipLevelParam levelParams__arr2;
        [FieldOffset(472)] public MiniBossWarshipLevelParam levelParams__arr3;
        [FieldOffset(528)] public MiniBossWarshipLevelParam levelParams__arr4;
        [FieldOffset(584)]   public MiniBossWarshipLevelBand levelBand__arr0;
        [FieldOffset(588)] public MiniBossWarshipLevelBand levelBand__arr1;
        [FieldOffset(592)] public MiniBossWarshipLevelBand levelBand__arr2;
        [FieldOffset(596)] public MiniBossWarshipLevelBand levelBand__arr3;
        [FieldOffset(600)] public MiniBossWarshipLevelBand levelBand__arr4;
        [FieldOffset(604)]   public float wanderMoveSpeed;
        [FieldOffset(608)]   public float railMaxLength;
        [FieldOffset(612)]   public MiniBossWarshipSpeedParam shiftStateMoveSpeedParam;
        [FieldOffset(640)]   public float locatorDistance;
        [FieldOffset(644)]   public float distanceEscapePathToStart;
        [FieldOffset(648)]   public MiniBossWarshipRecoverBoostGaugeParam boostGaugeParam;
        [FieldOffset(656)]   public MiniBossWarshipAttackStateParam attackStateParam;
        [FieldOffset(688)]   public MiniBossWarshipBattleFlagParam battleFlagParam;
        [FieldOffset(700)]   public MiniBossWarshipNearBattleCameraParam nearBattleCameraParam;
        [FieldOffset(724)]   public float disableGimmickDistance;
        [FieldOffset(728)]   public float warpTime;
        [FieldOffset(732)]   public float cameraChangeTime;
        [FieldOffset(736)]   public float cameraAppearTime;
        [FieldOffset(740)]   public float spreadHomingDistance;
        [FieldOffset(744)]   public MiniBossWarshipEscapePathParam escapePathID__arr0;
        [FieldOffset(6824)] public MiniBossWarshipEscapePathParam escapePathID__arr1;
        [FieldOffset(12904)] public MiniBossWarshipEscapePathParam escapePathID__arr2;
        [FieldOffset(18984)] public MiniBossWarshipEscapePathParam escapePathID__arr3;
        [FieldOffset(25064)] public MiniBossWarshipEscapePathParam escapePathID__arr4;
        [FieldOffset(31144)] public MiniBossWarshipAttackStateCameraParam bombAttackCameraParam__arr0;
        [FieldOffset(31204)] public MiniBossWarshipAttackStateCameraParam bombAttackCameraParam__arr1;
        [FieldOffset(31264)] public MiniBossWarshipAttackStateCameraParam bombAttackCameraParam__arr2;
        [FieldOffset(31324)] public MiniBossWarshipAttackStateCameraParam bombAttackCameraParam__arr3;
        [FieldOffset(31384)] public MiniBossWarshipAttackStateCameraParam bombAttackCameraParam__arr4;
    }

}