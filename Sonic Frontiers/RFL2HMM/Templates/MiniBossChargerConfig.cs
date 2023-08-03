using System.Numerics;
using System.Runtime.InteropServices;

public class MiniBossChargerConfigClass
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

    public enum BarrageType : sbyte
    {
        TYPE_LASER = 0,
        TYPE_BALL = 1,
        TYPE_BALL_L = 2,
        TYPE_BALL_LL = 3,
        TYPE_AIR_DROP = 4
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

    [StructLayout(LayoutKind.Explicit, Size = 88)]
    public struct MiniBossChagerBarrageParam
    {
        [FieldOffset(0)]  public BarrageType type;
        [FieldOffset(8)]  public CString damageTag;
        [FieldOffset(24)] public float startSpeed;
        [FieldOffset(28)] public float decelePower;
        [FieldOffset(32)] public float minSpeed;
        [FieldOffset(36)] public float lifeTime;
        [FieldOffset(40)] public float waitTime;
        [FieldOffset(44)] public float lineTime;
        [FieldOffset(48)] public float scale;
        [FieldOffset(52)] public float hitVelocity;
        [FieldOffset(56)] public float parriedSpeed;
        [FieldOffset(60)] public int parriedDamage;
        [FieldOffset(64)] public float parriedStaggerValue;
        [FieldOffset(68)] public float parriedStunValue;
        [FieldOffset(72)] public CString hitEffName;
    }

    [StructLayout(LayoutKind.Explicit, Size = 44)]
    public struct MiniBossChagerSimpleRotateBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public int muzzleNum;
        [FieldOffset(12)] public float yOffset;
        [FieldOffset(16)] public float zOffset;
        [FieldOffset(20)] public float heightLength;
        [FieldOffset(24)] public float rotSpeed;
        [FieldOffset(28)] public float shakeSpeed;
        [FieldOffset(32)] public float intervalTime;
        [FieldOffset(36)] public float activeTime;
        [FieldOffset(40)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct MiniBossChagerFollowLaser
    {
        [FieldOffset(0)]  public float startWaitTime;
        [FieldOffset(4)]  public float yOffset;
        [FieldOffset(8)]  public float zOffset;
        [FieldOffset(12)] public float moveSpeed;
        [FieldOffset(16)] public float followDeg;
        [FieldOffset(20)] public int shotNum;
        [FieldOffset(24)] public float intervalTime;
        [FieldOffset(28)] public float lifeTime;
        [FieldOffset(32)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct MiniBossChagerVortexLaser
    {
        [FieldOffset(0)]  public float startWaitTime;
        [FieldOffset(4)]  public int muzzleNum;
        [FieldOffset(8)]  public float yOffset;
        [FieldOffset(12)] public float zOffset;
        [FieldOffset(16)] public float rotSpeed;
        [FieldOffset(20)] public float moveSpeed;
        [FieldOffset(24)] public float activeTime;
        [FieldOffset(28)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct MiniBossChagerCrossLaser
    {
        [FieldOffset(0)]  public float startWaitTime;
        [FieldOffset(4)]  public float moveSpeed;
        [FieldOffset(8)]  public float setDeg;
        [FieldOffset(12)] public float lifeTime;
        [FieldOffset(16)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct MiniBossChagerCrossBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float yOffset;
        [FieldOffset(8)]  public float zOffset;
        [FieldOffset(12)] public bool isFollowPlayer;
        [FieldOffset(16)] public float startWaitTime;
        [FieldOffset(20)] public float shotIntarval;
        [FieldOffset(24)] public float maxAngle;
        [FieldOffset(28)] public float rotateSpeed;
        [FieldOffset(32)] public float rotateAngle;
        [FieldOffset(36)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct MiniBossChagerMassLaser
    {
        [FieldOffset(0)]  public float startWaitTime;
        [FieldOffset(4)]  public float yOffset;
        [FieldOffset(8)]  public float scale;
        [FieldOffset(12)] public float lifeTime;
        [FieldOffset(16)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct MiniBossChagerVerticalRoundBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public int muzzleNum;
        [FieldOffset(12)] public int verticalNum;
        [FieldOffset(16)] public float radius;
        [FieldOffset(20)] public float spaceRate;
        [FieldOffset(24)] public float verticalWaitTime;
        [FieldOffset(28)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct MiniBossPyramidRoundBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public int muzzleNum;
        [FieldOffset(12)] public float radius;
        [FieldOffset(16)] public float height;
        [FieldOffset(20)] public float scale;
        [FieldOffset(24)] public int sideNum;
        [FieldOffset(28)] public int attackNum;
        [FieldOffset(32)] public float intervalTime;
        [FieldOffset(36)] public float nextDeg;
        [FieldOffset(40)] public float shotWaitTime;
        [FieldOffset(44)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct MiniBossPlaneUpDownBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public float yOffset;
        [FieldOffset(12)] public float scale;
        [FieldOffset(16)] public float step;
        [FieldOffset(20)] public int allNum;
        [FieldOffset(24)] public float upRate;
        [FieldOffset(28)] public float downRate;
        [FieldOffset(32)] public float frontRate;
        [FieldOffset(36)] public float shotWaitTimeMin;
        [FieldOffset(40)] public float shotWaitTimeMax;
        [FieldOffset(44)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct MiniBossTriangleBatteryBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public float yOffset;
        [FieldOffset(12)] public float edgeLength;
        [FieldOffset(16)] public float activeTime;
        [FieldOffset(20)] public float intervalTime;
        [FieldOffset(24)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct MiniBossPlayerFallBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public float yOffset;
        [FieldOffset(12)] public float scale;
        [FieldOffset(16)] public float lengthMin;
        [FieldOffset(20)] public float lengthMax;
        [FieldOffset(24)] public float intervalTime;
        [FieldOffset(28)] public float shotWaitTime;
        [FieldOffset(32)] public float activeTime;
        [FieldOffset(36)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct MiniBossGatlingRevolverBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float startWaitTime;
        [FieldOffset(8)]  public float yOffset;
        [FieldOffset(12)] public float zOffset;
        [FieldOffset(16)] public float scale;
        [FieldOffset(20)] public int muzzleNum;
        [FieldOffset(24)] public float bulletRad;
        [FieldOffset(28)] public float intervalTime;
        [FieldOffset(32)] public float activeTime;
        [FieldOffset(36)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 44)]
    public struct MiniBossWinderBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float yOffset;
        [FieldOffset(8)]  public float zOffset;
        [FieldOffset(12)] public bool isFollowPlayer;
        [FieldOffset(16)] public float shotIntarval;
        [FieldOffset(20)] public float maxAngle;
        [FieldOffset(24)] public float rotateSpeed;
        [FieldOffset(28)] public float rotateAngle;
        [FieldOffset(32)] public float barrageAngleDiff;
        [FieldOffset(36)] public float startWaitTime;
        [FieldOffset(40)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 44)]
    public struct MiniBossShotgunBullet
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float yOffset;
        [FieldOffset(8)]  public float zOffset;
        [FieldOffset(12)] public bool isFollowPlayer;
        [FieldOffset(16)] public float shotIntarval;
        [FieldOffset(20)] public float maxAngle;
        [FieldOffset(24)] public float yAngleOffset;
        [FieldOffset(28)] public float shotTime;
        [FieldOffset(32)] public float addSpeedMax;
        [FieldOffset(36)] public float startWaitTime;
        [FieldOffset(40)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct MiniBossChagerAirDrop
    {
        [FieldOffset(0)]  public int barrageIndex;
        [FieldOffset(4)]  public float yOffset;
        [FieldOffset(8)]  public float zOffset;
        [FieldOffset(12)] public float upRotOffset;
        [FieldOffset(16)] public float yAngleOffset;
        [FieldOffset(20)] public float maxAngle;
        [FieldOffset(24)] public float shotTime;
        [FieldOffset(28)] public float addSpeedMax;
        [FieldOffset(32)] public float lineTime;
        [FieldOffset(36)] public float fallPower;
        [FieldOffset(40)] public float startWaitTime;
        [FieldOffset(44)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct MiniBossChagerGroundObj
    {
        [FieldOffset(0)]  public int bulletDamage;
        [FieldOffset(4)]  public float bulletStaggerPoint;
        [FieldOffset(8)]  public float bulletSpeed;
        [FieldOffset(12)] public float bulletFallSpeed;
        [FieldOffset(16)] public float bulletCyloopSpeed;
        [FieldOffset(20)] public float bulletGroundTime;
        [FieldOffset(24)] public float bulletFallTime;
        [FieldOffset(28)] public float yOffset;
        [FieldOffset(32)] public float zOffset;
        [FieldOffset(36)] public float upRotOffset;
        [FieldOffset(40)] public float yAngleOffset;
        [FieldOffset(44)] public float maxAngle;
        [FieldOffset(48)] public float shotTime;
        [FieldOffset(52)] public float startWaitTime;
        [FieldOffset(56)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 336)]
    public struct MiniBossChagerDiffuseLaser
    {
        [FieldOffset(0)]   public float startWaitTime;
        [FieldOffset(4)]   public float yOffset;
        [FieldOffset(8)]   public float scale;
        [FieldOffset(12)]  public int muzzleNum;
        [FieldOffset(16)]  public Vector3 muzzlePosOffset__arr0;
        [FieldOffset(32)] public Vector3 muzzlePosOffset__arr1;
        [FieldOffset(48)] public Vector3 muzzlePosOffset__arr2;
        [FieldOffset(64)] public Vector3 muzzlePosOffset__arr3;
        [FieldOffset(80)] public Vector3 muzzlePosOffset__arr4;
        [FieldOffset(96)] public Vector3 muzzlePosOffset__arr5;
        [FieldOffset(112)] public Vector3 muzzlePosOffset__arr6;
        [FieldOffset(128)] public Vector3 muzzlePosOffset__arr7;
        [FieldOffset(144)] public Vector3 muzzlePosOffset__arr8;
        [FieldOffset(160)] public Vector3 muzzlePosOffset__arr9;
        [FieldOffset(176)] public float muzzleRotOffset__arr0;
        [FieldOffset(180)] public float muzzleRotOffset__arr1;
        [FieldOffset(184)] public float muzzleRotOffset__arr2;
        [FieldOffset(188)] public float muzzleRotOffset__arr3;
        [FieldOffset(192)] public float muzzleRotOffset__arr4;
        [FieldOffset(196)] public float muzzleRotOffset__arr5;
        [FieldOffset(200)] public float muzzleRotOffset__arr6;
        [FieldOffset(204)] public float muzzleRotOffset__arr7;
        [FieldOffset(208)] public float muzzleRotOffset__arr8;
        [FieldOffset(212)] public float muzzleRotOffset__arr9;
        [FieldOffset(216)] public float muzzleTimeOffset__arr0;
        [FieldOffset(220)] public float muzzleTimeOffset__arr1;
        [FieldOffset(224)] public float muzzleTimeOffset__arr2;
        [FieldOffset(228)] public float muzzleTimeOffset__arr3;
        [FieldOffset(232)] public float muzzleTimeOffset__arr4;
        [FieldOffset(236)] public float muzzleTimeOffset__arr5;
        [FieldOffset(240)] public float muzzleTimeOffset__arr6;
        [FieldOffset(244)] public float muzzleTimeOffset__arr7;
        [FieldOffset(248)] public float muzzleTimeOffset__arr8;
        [FieldOffset(252)] public float muzzleTimeOffset__arr9;
        [FieldOffset(256)] public float muzzleLaserStartOffset__arr0;
        [FieldOffset(260)] public float muzzleLaserStartOffset__arr1;
        [FieldOffset(264)] public float muzzleLaserStartOffset__arr2;
        [FieldOffset(268)] public float muzzleLaserStartOffset__arr3;
        [FieldOffset(272)] public float muzzleLaserStartOffset__arr4;
        [FieldOffset(276)] public float muzzleLaserStartOffset__arr5;
        [FieldOffset(280)] public float muzzleLaserStartOffset__arr6;
        [FieldOffset(284)] public float muzzleLaserStartOffset__arr7;
        [FieldOffset(288)] public float muzzleLaserStartOffset__arr8;
        [FieldOffset(292)] public float muzzleLaserStartOffset__arr9;
        [FieldOffset(296)] public int laserNum;
        [FieldOffset(300)] public int attackNum;
        [FieldOffset(304)] public float laserRandomRange;
        [FieldOffset(308)] public float laserTime;
        [FieldOffset(312)] public float laserEndTime;
        [FieldOffset(316)] public float laserNextTime;
        [FieldOffset(320)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 384)]
    public struct MiniBossChagerChaseShot
    {
        [FieldOffset(0)]   public float startWaitTime;
        [FieldOffset(4)]   public int muzzleNum;
        [FieldOffset(16)]  public Vector3 muzzlePosOffset__arr0;
        [FieldOffset(32)] public Vector3 muzzlePosOffset__arr1;
        [FieldOffset(48)] public Vector3 muzzlePosOffset__arr2;
        [FieldOffset(64)] public Vector3 muzzlePosOffset__arr3;
        [FieldOffset(80)] public Vector3 muzzlePosOffset__arr4;
        [FieldOffset(96)] public Vector3 muzzlePosOffset__arr5;
        [FieldOffset(112)] public Vector3 muzzlePosOffset__arr6;
        [FieldOffset(128)] public Vector3 muzzlePosOffset__arr7;
        [FieldOffset(144)] public Vector3 muzzlePosOffset__arr8;
        [FieldOffset(160)] public Vector3 muzzlePosOffset__arr9;
        [FieldOffset(176)] public float muzzleRotOffsetX__arr0;
        [FieldOffset(180)] public float muzzleRotOffsetX__arr1;
        [FieldOffset(184)] public float muzzleRotOffsetX__arr2;
        [FieldOffset(188)] public float muzzleRotOffsetX__arr3;
        [FieldOffset(192)] public float muzzleRotOffsetX__arr4;
        [FieldOffset(196)] public float muzzleRotOffsetX__arr5;
        [FieldOffset(200)] public float muzzleRotOffsetX__arr6;
        [FieldOffset(204)] public float muzzleRotOffsetX__arr7;
        [FieldOffset(208)] public float muzzleRotOffsetX__arr8;
        [FieldOffset(212)] public float muzzleRotOffsetX__arr9;
        [FieldOffset(216)] public float muzzleRotOffsetY__arr0;
        [FieldOffset(220)] public float muzzleRotOffsetY__arr1;
        [FieldOffset(224)] public float muzzleRotOffsetY__arr2;
        [FieldOffset(228)] public float muzzleRotOffsetY__arr3;
        [FieldOffset(232)] public float muzzleRotOffsetY__arr4;
        [FieldOffset(236)] public float muzzleRotOffsetY__arr5;
        [FieldOffset(240)] public float muzzleRotOffsetY__arr6;
        [FieldOffset(244)] public float muzzleRotOffsetY__arr7;
        [FieldOffset(248)] public float muzzleRotOffsetY__arr8;
        [FieldOffset(252)] public float muzzleRotOffsetY__arr9;
        [FieldOffset(256)] public float muzzleTimeOffset__arr0;
        [FieldOffset(260)] public float muzzleTimeOffset__arr1;
        [FieldOffset(264)] public float muzzleTimeOffset__arr2;
        [FieldOffset(268)] public float muzzleTimeOffset__arr3;
        [FieldOffset(272)] public float muzzleTimeOffset__arr4;
        [FieldOffset(276)] public float muzzleTimeOffset__arr5;
        [FieldOffset(280)] public float muzzleTimeOffset__arr6;
        [FieldOffset(284)] public float muzzleTimeOffset__arr7;
        [FieldOffset(288)] public float muzzleTimeOffset__arr8;
        [FieldOffset(292)] public float muzzleTimeOffset__arr9;
        [FieldOffset(296)] public float muzzleLaserStartOffset__arr0;
        [FieldOffset(300)] public float muzzleLaserStartOffset__arr1;
        [FieldOffset(304)] public float muzzleLaserStartOffset__arr2;
        [FieldOffset(308)] public float muzzleLaserStartOffset__arr3;
        [FieldOffset(312)] public float muzzleLaserStartOffset__arr4;
        [FieldOffset(316)] public float muzzleLaserStartOffset__arr5;
        [FieldOffset(320)] public float muzzleLaserStartOffset__arr6;
        [FieldOffset(324)] public float muzzleLaserStartOffset__arr7;
        [FieldOffset(328)] public float muzzleLaserStartOffset__arr8;
        [FieldOffset(332)] public float muzzleLaserStartOffset__arr9;
        [FieldOffset(336)] public float laserShotTimeMin;
        [FieldOffset(340)] public float laserShotTimeMax;
        [FieldOffset(344)] public int laserNum;
        [FieldOffset(348)] public float laserRange;
        [FieldOffset(352)] public float laserEndTime;
        [FieldOffset(356)] public float laserSpeed;
        [FieldOffset(360)] public float laserRandomRangeMin;
        [FieldOffset(364)] public float laserRandomRangeMax;
        [FieldOffset(368)] public float laserHomingTime;
        [FieldOffset(372)] public float endWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct MiniBossChargerCatchParam
    {
        [FieldOffset(0)]  public float hitDistance;
        [FieldOffset(4)]  public float durationBind;
        [FieldOffset(8)]  public float distanceStartBlackOut;
        [FieldOffset(12)] public float timeEaseBlackOut;
        [FieldOffset(16)] public float timeDelayEndtBlackOut;
        [FieldOffset(32)] public Vector3 tangentFrom;
        [FieldOffset(48)] public Vector3 tangentTo;
    }

    [StructLayout(LayoutKind.Explicit, Size = 5568)]
    public struct MiniBossChargerCommonParam
    {
        [FieldOffset(0)]    public MiniBossCommonConfig commonConfig;
        [FieldOffset(64)]   public MiniBossChagerBarrageParam barrage__arr0;
        [FieldOffset(152)] public MiniBossChagerBarrageParam barrage__arr1;
        [FieldOffset(240)] public MiniBossChagerBarrageParam barrage__arr2;
        [FieldOffset(328)] public MiniBossChagerBarrageParam barrage__arr3;
        [FieldOffset(416)] public MiniBossChagerBarrageParam barrage__arr4;
        [FieldOffset(504)] public MiniBossChagerBarrageParam barrage__arr5;
        [FieldOffset(592)] public MiniBossChagerBarrageParam barrage__arr6;
        [FieldOffset(680)] public MiniBossChagerBarrageParam barrage__arr7;
        [FieldOffset(768)] public MiniBossChagerBarrageParam barrage__arr8;
        [FieldOffset(856)] public MiniBossChagerBarrageParam barrage__arr9;
        [FieldOffset(944)] public MiniBossChagerBarrageParam barrage__arr10;
        [FieldOffset(1032)] public MiniBossChagerBarrageParam barrage__arr11;
        [FieldOffset(1120)] public MiniBossChagerBarrageParam barrage__arr12;
        [FieldOffset(1208)] public MiniBossChagerBarrageParam barrage__arr13;
        [FieldOffset(1296)] public MiniBossChagerBarrageParam barrage__arr14;
        [FieldOffset(1384)] public MiniBossChagerBarrageParam barrage__arr15;
        [FieldOffset(1472)] public MiniBossChagerSimpleRotateBullet simpleRotateBullet__arr0;
        [FieldOffset(1516)] public MiniBossChagerSimpleRotateBullet simpleRotateBullet__arr1;
        [FieldOffset(1560)] public MiniBossChagerSimpleRotateBullet simpleRotateBullet__arr2;
        [FieldOffset(1604)] public MiniBossChagerFollowLaser followLaser__arr0;
        [FieldOffset(1640)] public MiniBossChagerFollowLaser followLaser__arr1;
        [FieldOffset(1676)] public MiniBossChagerFollowLaser followLaser__arr2;
        [FieldOffset(1712)] public MiniBossChagerVortexLaser vortexLaser__arr0;
        [FieldOffset(1744)] public MiniBossChagerVortexLaser vortexLaser__arr1;
        [FieldOffset(1776)] public MiniBossChagerVortexLaser vortexLaser__arr2;
        [FieldOffset(1808)] public MiniBossChagerCrossLaser crossLaser__arr0;
        [FieldOffset(1828)] public MiniBossChagerCrossLaser crossLaser__arr1;
        [FieldOffset(1848)] public MiniBossChagerCrossLaser crossLaser__arr2;
        [FieldOffset(1868)] public MiniBossChagerCrossBullet crossBullet__arr0;
        [FieldOffset(1908)] public MiniBossChagerCrossBullet crossBullet__arr1;
        [FieldOffset(1948)] public MiniBossChagerCrossBullet crossBullet__arr2;
        [FieldOffset(1988)] public MiniBossChagerMassLaser massLaser__arr0;
        [FieldOffset(2008)] public MiniBossChagerMassLaser massLaser__arr1;
        [FieldOffset(2028)] public MiniBossChagerMassLaser massLaser__arr2;
        [FieldOffset(2048)] public MiniBossChagerVerticalRoundBullet verticalRoundBullet__arr0;
        [FieldOffset(2080)] public MiniBossChagerVerticalRoundBullet verticalRoundBullet__arr1;
        [FieldOffset(2112)] public MiniBossChagerVerticalRoundBullet verticalRoundBullet__arr2;
        [FieldOffset(2144)] public MiniBossPyramidRoundBullet pyramidRoundBullet__arr0;
        [FieldOffset(2192)] public MiniBossPyramidRoundBullet pyramidRoundBullet__arr1;
        [FieldOffset(2240)] public MiniBossPyramidRoundBullet pyramidRoundBullet__arr2;
        [FieldOffset(2288)] public MiniBossPlaneUpDownBullet planeUpDownBullet__arr0;
        [FieldOffset(2336)] public MiniBossPlaneUpDownBullet planeUpDownBullet__arr1;
        [FieldOffset(2384)] public MiniBossPlaneUpDownBullet planeUpDownBullet__arr2;
        [FieldOffset(2432)] public MiniBossTriangleBatteryBullet triangleBatteryBullet__arr0;
        [FieldOffset(2460)] public MiniBossTriangleBatteryBullet triangleBatteryBullet__arr1;
        [FieldOffset(2488)] public MiniBossTriangleBatteryBullet triangleBatteryBullet__arr2;
        [FieldOffset(2516)] public MiniBossPlayerFallBullet playerFallBullet__arr0;
        [FieldOffset(2556)] public MiniBossPlayerFallBullet playerFallBullet__arr1;
        [FieldOffset(2596)] public MiniBossPlayerFallBullet playerFallBullet__arr2;
        [FieldOffset(2636)] public MiniBossGatlingRevolverBullet gatlingRevolverBullet__arr0;
        [FieldOffset(2676)] public MiniBossGatlingRevolverBullet gatlingRevolverBullet__arr1;
        [FieldOffset(2716)] public MiniBossGatlingRevolverBullet gatlingRevolverBullet__arr2;
        [FieldOffset(2756)] public MiniBossWinderBullet winderBullet__arr0;
        [FieldOffset(2800)] public MiniBossWinderBullet winderBullet__arr1;
        [FieldOffset(2844)] public MiniBossWinderBullet winderBullet__arr2;
        [FieldOffset(2888)] public MiniBossShotgunBullet shotgunBullet__arr0;
        [FieldOffset(2932)] public MiniBossShotgunBullet shotgunBullet__arr1;
        [FieldOffset(2976)] public MiniBossShotgunBullet shotgunBullet__arr2;
        [FieldOffset(3020)] public MiniBossChagerAirDrop airDrop__arr0;
        [FieldOffset(3068)] public MiniBossChagerAirDrop airDrop__arr1;
        [FieldOffset(3116)] public MiniBossChagerAirDrop airDrop__arr2;
        [FieldOffset(3164)] public MiniBossChagerGroundObj groundObj__arr0;
        [FieldOffset(3224)] public MiniBossChagerGroundObj groundObj__arr1;
        [FieldOffset(3284)] public MiniBossChagerGroundObj groundObj__arr2;
        [FieldOffset(3344)] public MiniBossChagerDiffuseLaser diffuseLaser__arr0;
        [FieldOffset(3680)] public MiniBossChagerDiffuseLaser diffuseLaser__arr1;
        [FieldOffset(4016)] public MiniBossChagerDiffuseLaser diffuseLaser__arr2;
        [FieldOffset(4352)] public MiniBossChagerChaseShot chaseShot__arr0;
        [FieldOffset(4736)] public MiniBossChagerChaseShot chaseShot__arr1;
        [FieldOffset(5120)] public MiniBossChagerChaseShot chaseShot__arr2;
        [FieldOffset(5504)] public MiniBossChargerCatchParam atkCatch;
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

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct MiniBossChargerLevelParam
    {
        [FieldOffset(0)]  public int level;
        [FieldOffset(4)]  public MiniBossLevelCommonConfig commonConfig;
        [FieldOffset(56)] public float stunTime;
    }

    public enum AttackType : int
    {
        AttackTypeInvalid = 0,
        AttackSimpleRotateBullet = 1,
        AttackFollowLaser = 2,
        AttackVortexLaser = 3,
        AttackCrossLaser = 4,
        AttackCrossBullet = 5,
        AttackMassLaser = 6,
        AttackVerticalRoundBullet = 7,
        AttackPyramidRoundBullet = 8,
        AttackPlaneUpDownBullet = 9,
        AttackTriangleBatteryBullet = 10,
        AttackPlayerFallBullet = 11,
        AttackGatlingRevolverBullet = 12,
        AttackWinderBullet = 13,
        AttackShotgunBullet = 14,
        AttackAirDropBullet = 15,
        AttackChaseShotObject = 16,
        AttackDiffuseLaser = 17,
        AttackChaseShot = 18,
        AttackTypeNum = 19
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct MiniBossChargerHPRateParam
    {
        [FieldOffset(0)] public int rateHp;
        [FieldOffset(8)] public CString grindSetName;
    }

    [StructLayout(LayoutKind.Explicit, Size = 184)]
    public struct MiniBossChargerLevelBand
    {
        [FieldOffset(0)]   public int level;
        [FieldOffset(4)]   public float rate;
        [FieldOffset(8)]   public float chanceTime;
        [FieldOffset(12)]  public float chanceTimeMoveSpeed;
        [FieldOffset(16)]  public float chanceTimeDecSpeed;
        [FieldOffset(20)]  public float chanceTimeSpeedMin;
        [FieldOffset(24)]  public float damageTime;
        [FieldOffset(28)]  public float chanceTimeAddSpeed;
        [FieldOffset(32)]  public AttackType attackTable__arr0;
        [FieldOffset(36)] public AttackType attackTable__arr1;
        [FieldOffset(40)] public AttackType attackTable__arr2;
        [FieldOffset(44)] public AttackType attackTable__arr3;
        [FieldOffset(48)] public AttackType attackTable__arr4;
        [FieldOffset(52)] public AttackType attackTable__arr5;
        [FieldOffset(56)] public AttackType attackTable__arr6;
        [FieldOffset(60)] public AttackType attackTable__arr7;
        [FieldOffset(64)] public AttackType attackTable__arr8;
        [FieldOffset(68)] public AttackType attackTable__arr9;
        [FieldOffset(72)]  public int attackIndexTable__arr0;
        [FieldOffset(76)] public int attackIndexTable__arr1;
        [FieldOffset(80)] public int attackIndexTable__arr2;
        [FieldOffset(84)] public int attackIndexTable__arr3;
        [FieldOffset(88)] public int attackIndexTable__arr4;
        [FieldOffset(92)] public int attackIndexTable__arr5;
        [FieldOffset(96)] public int attackIndexTable__arr6;
        [FieldOffset(100)] public int attackIndexTable__arr7;
        [FieldOffset(104)] public int attackIndexTable__arr8;
        [FieldOffset(108)] public int attackIndexTable__arr9;
        [FieldOffset(112)] public MiniBossChargerHPRateParam hpRateParams__arr0;
        [FieldOffset(136)] public MiniBossChargerHPRateParam hpRateParams__arr1;
        [FieldOffset(160)] public MiniBossChargerHPRateParam hpRateParams__arr2;
    }

    public enum MiniBossChargerLevel1_AttackType : int
    {
        MiniBossChargerLevel1_AttackType_AttackTypeInvalid = 0,
        MiniBossChargerLevel1_AttackType_AttackSimpleRotateBullet = 1,
        MiniBossChargerLevel1_AttackType_AttackFollowLaser = 2,
        MiniBossChargerLevel1_AttackType_AttackVortexLaser = 3,
        MiniBossChargerLevel1_AttackType_AttackCrossLaser = 4,
        MiniBossChargerLevel1_AttackType_AttackCrossBullet = 5,
        MiniBossChargerLevel1_AttackType_AttackMassLaser = 6,
        MiniBossChargerLevel1_AttackType_AttackVerticalRoundBullet = 7,
        MiniBossChargerLevel1_AttackType_AttackPyramidRoundBullet = 8,
        MiniBossChargerLevel1_AttackType_AttackPlaneUpDownBullet = 9,
        MiniBossChargerLevel1_AttackType_AttackTriangleBatteryBullet = 10,
        MiniBossChargerLevel1_AttackType_AttackPlayerFallBullet = 11,
        MiniBossChargerLevel1_AttackType_AttackGatlingRevolverBullet = 12,
        MiniBossChargerLevel1_AttackType_AttackWinderBullet = 13,
        MiniBossChargerLevel1_AttackType_AttackShotgunBullet = 14,
        MiniBossChargerLevel1_AttackType_AttackAirDropBullet = 15,
        MiniBossChargerLevel1_AttackType_AttackChaseShotObject = 16,
        MiniBossChargerLevel1_AttackType_AttackDiffuseLaser = 17,
        MiniBossChargerLevel1_AttackType_AttackChaseShot = 18,
        MiniBossChargerLevel1_AttackType_AttackTypeNum = 19
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct MiniBossChargerLevel1
    {
        [FieldOffset(0)]  public float range;
        [FieldOffset(4)]  public MiniBossChargerLevel1_AttackType attackTable__arr0;
        [FieldOffset(8)] public MiniBossChargerLevel1_AttackType attackTable__arr1;
        [FieldOffset(12)] public int attackIndexTable__arr0;
        [FieldOffset(16)] public int attackIndexTable__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 6832)]
    public struct MiniBossChargerConfig
    {
        [FieldOffset(0)]    public MiniBossChargerCommonParam commonParam;
        [FieldOffset(5568)] public MiniBossChargerLevelParam levelParams__arr0;
        [FieldOffset(5628)] public MiniBossChargerLevelParam levelParams__arr1;
        [FieldOffset(5688)] public MiniBossChargerLevelParam levelParams__arr2;
        [FieldOffset(5748)] public MiniBossChargerLevelParam levelParams__arr3;
        [FieldOffset(5808)] public MiniBossChargerLevelParam levelParams__arr4;
        [FieldOffset(5872)] public MiniBossChargerLevelBand levelBands__arr0;
        [FieldOffset(6056)] public MiniBossChargerLevelBand levelBands__arr1;
        [FieldOffset(6240)] public MiniBossChargerLevelBand levelBands__arr2;
        [FieldOffset(6424)] public MiniBossChargerLevelBand levelBands__arr3;
        [FieldOffset(6608)] public MiniBossChargerLevelBand levelBands__arr4;
        [FieldOffset(6792)] public MiniBossChargerLevel1 level1Params__arr0;
        [FieldOffset(6812)] public MiniBossChargerLevel1 level1Params__arr1;
    }

}