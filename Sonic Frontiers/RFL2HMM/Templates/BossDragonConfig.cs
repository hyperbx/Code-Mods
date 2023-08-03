using System.Numerics;
using System.Runtime.InteropServices;

public class BossDragonConfigClass
{
    public struct CSetObjectID
    {
        public unsafe fixed byte GUID[16];
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct CSetObjectIDArray
    {
        [FieldOffset(0)] public ulong pData;
        [FieldOffset(8)] public ulong Size;
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
    public struct PlayerMoveableRangeParam
    {
        [FieldOffset(0)]  public CSetObjectIDArray initPositions;
        [FieldOffset(32)] public CString heightTargetNodeName;
        [FieldOffset(48)] public float heightMoveSpeed;
        [FieldOffset(52)] public float bossToPlayerDistanceMin;
        [FieldOffset(56)] public float bossToPlayerDistanceMax;
        [FieldOffset(60)] public float offsetHeightMin;
        [FieldOffset(64)] public float offsetHeightMax;
        [FieldOffset(68)] public float areaDistanceMin;
        [FieldOffset(72)] public float areaDistanceMax;
        [FieldOffset(76)] public float playerSpawnDistance;
        [FieldOffset(80)] public float playerRespawnDistance;
        [FieldOffset(84)] public float playerRespawnDistance2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct BossPhaseParam
    {
        [FieldOffset(0)] public bool isUse;
        [FieldOffset(1)] public bool isUsePillar;
        [FieldOffset(4)] public float phaseChangeHpRatio;
    }

    public enum EaseType : sbyte
    {
        ET_Sin = 0,
        ET_Cubic = 1,
        ET_Quadratic = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct BossLockOnCameraParam
    {
        [FieldOffset(0)]  public float easeTime;
        [FieldOffset(4)]  public EaseType easeType;
        [FieldOffset(8)]  public CString mainLookAtNodeName;
        [FieldOffset(32)] public Vector3 mainLookOffsetPos;
        [FieldOffset(48)] public CString subLookAtNodeName;
        [FieldOffset(64)] public Vector3 subLookOffsetPos;
        [FieldOffset(80)] public float distance;
        [FieldOffset(96)] public Vector3 playerOffsetPos;
    }

    [StructLayout(LayoutKind.Explicit, Size = 416)]
    public struct BossStatusConfig
    {
        [FieldOffset(0)]   public uint healthPoint;
        [FieldOffset(4)]   public float stunTime;
        [FieldOffset(8)]   public float maxStunPoint__arr0;
        [FieldOffset(12)] public float maxStunPoint__arr1;
        [FieldOffset(16)] public float maxStunPoint__arr2;
        [FieldOffset(20)]  public float maxStaggerPoint__arr0;
        [FieldOffset(24)] public float maxStaggerPoint__arr1;
        [FieldOffset(28)] public float maxStaggerPoint__arr2;
        [FieldOffset(32)] public float maxStaggerPoint__arr3;
        [FieldOffset(36)] public float maxStaggerPoint__arr4;
        [FieldOffset(40)]  public ushort exp;
        [FieldOffset(48)]  public PlayerMoveableRangeParam moveRangeParam;
        [FieldOffset(136)] public PlayerMoveableRangeParam cyloopDamageMoveRangeParam;
        [FieldOffset(224)] public BossPhaseParam phaseParams__arr0;
        [FieldOffset(232)] public BossPhaseParam phaseParams__arr1;
        [FieldOffset(240)] public BossPhaseParam phaseParams__arr2;
        [FieldOffset(248)] public BossPhaseParam phaseParams__arr3;
        [FieldOffset(256)] public BossPhaseParam phaseParams__arr4;
        [FieldOffset(264)] public BossPhaseParam phaseParams__arr5;
        [FieldOffset(272)] public BossPhaseParam phaseParams__arr6;
        [FieldOffset(280)] public BossPhaseParam phaseParams__arr7;
        [FieldOffset(288)] public BossLockOnCameraParam cameraParam;
        [FieldOffset(400)] public bool isDebugDraw;
        [FieldOffset(404)] public uint debugDrawPhaseIndex;
    }

    public enum GimmickType : sbyte
    {
        GT_A = 0,
        GT_B = 1,
        GT_C = 2,
        GT_D = 3,
        GT_E = 4,
        NUM_GIMMICK_TYPE = 5
    }

    public enum AttackType : sbyte
    {
        AT_A = 0,
        AT_B = 1,
        AT_C = 2,
        AT_D = 3,
        AT_E = 4,
        NUM_ATTACK_TYPE = 5
    }

    public enum BossPillarParam_GimmickType : sbyte
    {
        BossPillarParam_GimmickType_GT_A = 0,
        BossPillarParam_GimmickType_GT_B = 1,
        BossPillarParam_GimmickType_GT_C = 2,
        BossPillarParam_GimmickType_GT_D = 3,
        BossPillarParam_GimmickType_GT_E = 4,
        BossPillarParam_GimmickType_NUM_GIMMICK_TYPE = 5
    }

    public enum BossPillarParam_AttackType : sbyte
    {
        BossPillarParam_AttackType_AT_A = 0,
        BossPillarParam_AttackType_AT_B = 1,
        BossPillarParam_AttackType_AT_C = 2,
        BossPillarParam_AttackType_AT_D = 3,
        BossPillarParam_AttackType_AT_E = 4,
        BossPillarParam_AttackType_NUM_ATTACK_TYPE = 5
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct BossPillarParam
    {
        [FieldOffset(0)]  public bool isUse;
        [FieldOffset(4)]  public float gimmickPhaseTime;
        [FieldOffset(8)]  public float attackPhaseTime;
        [FieldOffset(12)] public bool isUnique;
        [FieldOffset(13)] public BossPillarParam_GimmickType gimmickType;
        [FieldOffset(16)] public float gimmickIntervalTime;
        [FieldOffset(20)] public BossPillarParam_AttackType attackType;
        [FieldOffset(24)] public float attackIntervalTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 952)]
    public struct BossPillarConfig
    {
        [FieldOffset(0)]   public GimmickType gimmickTypeAll;
        [FieldOffset(4)]   public float gimmickIntervalTimeAll;
        [FieldOffset(8)]   public AttackType attackTypeAll;
        [FieldOffset(12)]  public float attackIntervalTimeAll;
        [FieldOffset(16)]  public BossPillarParam pillars__arr0;
        [FieldOffset(44)] public BossPillarParam pillars__arr1;
        [FieldOffset(72)] public BossPillarParam pillars__arr2;
        [FieldOffset(100)] public BossPillarParam pillars__arr3;
        [FieldOffset(128)] public BossPillarParam pillars__arr4;
        [FieldOffset(156)] public BossPillarParam pillars__arr5;
        [FieldOffset(184)] public BossPillarParam pillars__arr6;
        [FieldOffset(212)] public BossPillarParam pillars__arr7;
        [FieldOffset(240)] public BossPillarParam pillars__arr8;
        [FieldOffset(268)] public BossPillarParam pillars__arr9;
        [FieldOffset(296)] public BossPillarParam pillars__arr10;
        [FieldOffset(324)] public BossPillarParam pillars__arr11;
        [FieldOffset(352)] public BossPillarParam pillars__arr12;
        [FieldOffset(380)] public BossPillarParam pillars__arr13;
        [FieldOffset(408)] public BossPillarParam pillars__arr14;
        [FieldOffset(436)] public BossPillarParam pillars__arr15;
        [FieldOffset(464)] public BossPillarParam pillars__arr16;
        [FieldOffset(492)] public BossPillarParam pillars__arr17;
        [FieldOffset(520)] public BossPillarParam pillars__arr18;
        [FieldOffset(548)] public BossPillarParam pillars__arr19;
        [FieldOffset(576)] public BossPillarParam pillars__arr20;
        [FieldOffset(604)] public BossPillarParam pillars__arr21;
        [FieldOffset(632)] public BossPillarParam pillars__arr22;
        [FieldOffset(660)] public BossPillarParam pillars__arr23;
        [FieldOffset(688)] public BossPillarParam pillars__arr24;
        [FieldOffset(716)] public BossPillarParam pillars__arr25;
        [FieldOffset(744)] public BossPillarParam pillars__arr26;
        [FieldOffset(772)] public BossPillarParam pillars__arr27;
        [FieldOffset(800)] public BossPillarParam pillars__arr28;
        [FieldOffset(828)] public BossPillarParam pillars__arr29;
        [FieldOffset(856)] public BossPillarParam pillars__arr30;
        [FieldOffset(884)] public BossPillarParam pillars__arr31;
        [FieldOffset(912)] public CString spawnPositionName;
        [FieldOffset(928)] public uint pillarHealthPoint;
        [FieldOffset(932)] public uint pillarBreakDamage;
        [FieldOffset(936)] public float pillarBreakStun;
        [FieldOffset(940)] public bool isDebugDraw;
        [FieldOffset(944)] public uint DebugDrawType;
    }

    public enum CollisionType : sbyte
    {
        CT_SPHERE = 0,
        CT_CAPSULE = 1,
        CT_CYLINDER = 2,
        CT_BOX = 3,
        NUM_COLLISION_TYPE = 4
    }

    public enum ColliderActiveType : sbyte
    {
        Always = 0,
        OnContactActive = 1,
        OnContactInactive = 2,
        OnMotionActive = 3,
        OnMotionInactive = 4,
        Manual = 5,
        NUM_COLLIDER_ACTIVE_TYPE = 6
    }

    public enum ColliderProperty : short
    {
        CpNone = 0,
        CpBattleUse = 1,
        CpBattleUnuse = 2,
        CpRestPoint = 3,
        CpHomingTarget = 4,
        CpPerceive = 5,
        CpDamage = 6,
        CpAttack = 7,
        CpContactActive = 8,
        CpContactInactive = 9,
        CpMotionActive = 10,
        CpMotionInactive = 11,
        CpManual = 12,
        CpUpperSide = 13,
        CpLowerSide = 14,
        CpFrontSide = 15,
        CpBackSide = 16,
        CpLeftSide = 17,
        CpRightSide = 18,
        CpPointA = 19,
        CpPointB = 20,
        CpPointC = 21,
        CpPointD = 22,
        CpCyloopDownUnuse = 23,
        CpDummyDamage = 24,
        NUM_COLLIDER_PROPERTY = 25
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct BossColliderStatus
    {
        [FieldOffset(0)]  public ColliderActiveType type;
        [FieldOffset(2)]  public ColliderProperty propertys__arr0;
        [FieldOffset(4)] public ColliderProperty propertys__arr1;
        [FieldOffset(6)] public ColliderProperty propertys__arr2;
        [FieldOffset(8)] public ColliderProperty propertys__arr3;
        [FieldOffset(16)] public CString text;
    }

    [StructLayout(LayoutKind.Explicit, Size = 128)]
    public struct BossPerceiveCollisionParam
    {
        [FieldOffset(0)]   public bool isUse;
        [FieldOffset(2)]   public short priority;
        [FieldOffset(4)]   public CollisionType type;
        [FieldOffset(8)]   public CString attachNodeName;
        [FieldOffset(24)]  public CString name;
        [FieldOffset(40)]  public BossColliderStatus status;
        [FieldOffset(80)]  public Vector3 size;
        [FieldOffset(96)]  public Vector3 offset;
        [FieldOffset(112)] public Vector3 rotation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8208)]
    public struct BossPerceivePartsWithCollisionConfig
    {
        [FieldOffset(0)]    public BossPerceiveCollisionParam perceiveCollisions__arr0;
        [FieldOffset(128)] public BossPerceiveCollisionParam perceiveCollisions__arr1;
        [FieldOffset(256)] public BossPerceiveCollisionParam perceiveCollisions__arr2;
        [FieldOffset(384)] public BossPerceiveCollisionParam perceiveCollisions__arr3;
        [FieldOffset(512)] public BossPerceiveCollisionParam perceiveCollisions__arr4;
        [FieldOffset(640)] public BossPerceiveCollisionParam perceiveCollisions__arr5;
        [FieldOffset(768)] public BossPerceiveCollisionParam perceiveCollisions__arr6;
        [FieldOffset(896)] public BossPerceiveCollisionParam perceiveCollisions__arr7;
        [FieldOffset(1024)] public BossPerceiveCollisionParam perceiveCollisions__arr8;
        [FieldOffset(1152)] public BossPerceiveCollisionParam perceiveCollisions__arr9;
        [FieldOffset(1280)] public BossPerceiveCollisionParam perceiveCollisions__arr10;
        [FieldOffset(1408)] public BossPerceiveCollisionParam perceiveCollisions__arr11;
        [FieldOffset(1536)] public BossPerceiveCollisionParam perceiveCollisions__arr12;
        [FieldOffset(1664)] public BossPerceiveCollisionParam perceiveCollisions__arr13;
        [FieldOffset(1792)] public BossPerceiveCollisionParam perceiveCollisions__arr14;
        [FieldOffset(1920)] public BossPerceiveCollisionParam perceiveCollisions__arr15;
        [FieldOffset(2048)] public BossPerceiveCollisionParam perceiveCollisions__arr16;
        [FieldOffset(2176)] public BossPerceiveCollisionParam perceiveCollisions__arr17;
        [FieldOffset(2304)] public BossPerceiveCollisionParam perceiveCollisions__arr18;
        [FieldOffset(2432)] public BossPerceiveCollisionParam perceiveCollisions__arr19;
        [FieldOffset(2560)] public BossPerceiveCollisionParam perceiveCollisions__arr20;
        [FieldOffset(2688)] public BossPerceiveCollisionParam perceiveCollisions__arr21;
        [FieldOffset(2816)] public BossPerceiveCollisionParam perceiveCollisions__arr22;
        [FieldOffset(2944)] public BossPerceiveCollisionParam perceiveCollisions__arr23;
        [FieldOffset(3072)] public BossPerceiveCollisionParam perceiveCollisions__arr24;
        [FieldOffset(3200)] public BossPerceiveCollisionParam perceiveCollisions__arr25;
        [FieldOffset(3328)] public BossPerceiveCollisionParam perceiveCollisions__arr26;
        [FieldOffset(3456)] public BossPerceiveCollisionParam perceiveCollisions__arr27;
        [FieldOffset(3584)] public BossPerceiveCollisionParam perceiveCollisions__arr28;
        [FieldOffset(3712)] public BossPerceiveCollisionParam perceiveCollisions__arr29;
        [FieldOffset(3840)] public BossPerceiveCollisionParam perceiveCollisions__arr30;
        [FieldOffset(3968)] public BossPerceiveCollisionParam perceiveCollisions__arr31;
        [FieldOffset(4096)] public BossPerceiveCollisionParam perceiveCollisions__arr32;
        [FieldOffset(4224)] public BossPerceiveCollisionParam perceiveCollisions__arr33;
        [FieldOffset(4352)] public BossPerceiveCollisionParam perceiveCollisions__arr34;
        [FieldOffset(4480)] public BossPerceiveCollisionParam perceiveCollisions__arr35;
        [FieldOffset(4608)] public BossPerceiveCollisionParam perceiveCollisions__arr36;
        [FieldOffset(4736)] public BossPerceiveCollisionParam perceiveCollisions__arr37;
        [FieldOffset(4864)] public BossPerceiveCollisionParam perceiveCollisions__arr38;
        [FieldOffset(4992)] public BossPerceiveCollisionParam perceiveCollisions__arr39;
        [FieldOffset(5120)] public BossPerceiveCollisionParam perceiveCollisions__arr40;
        [FieldOffset(5248)] public BossPerceiveCollisionParam perceiveCollisions__arr41;
        [FieldOffset(5376)] public BossPerceiveCollisionParam perceiveCollisions__arr42;
        [FieldOffset(5504)] public BossPerceiveCollisionParam perceiveCollisions__arr43;
        [FieldOffset(5632)] public BossPerceiveCollisionParam perceiveCollisions__arr44;
        [FieldOffset(5760)] public BossPerceiveCollisionParam perceiveCollisions__arr45;
        [FieldOffset(5888)] public BossPerceiveCollisionParam perceiveCollisions__arr46;
        [FieldOffset(6016)] public BossPerceiveCollisionParam perceiveCollisions__arr47;
        [FieldOffset(6144)] public BossPerceiveCollisionParam perceiveCollisions__arr48;
        [FieldOffset(6272)] public BossPerceiveCollisionParam perceiveCollisions__arr49;
        [FieldOffset(6400)] public BossPerceiveCollisionParam perceiveCollisions__arr50;
        [FieldOffset(6528)] public BossPerceiveCollisionParam perceiveCollisions__arr51;
        [FieldOffset(6656)] public BossPerceiveCollisionParam perceiveCollisions__arr52;
        [FieldOffset(6784)] public BossPerceiveCollisionParam perceiveCollisions__arr53;
        [FieldOffset(6912)] public BossPerceiveCollisionParam perceiveCollisions__arr54;
        [FieldOffset(7040)] public BossPerceiveCollisionParam perceiveCollisions__arr55;
        [FieldOffset(7168)] public BossPerceiveCollisionParam perceiveCollisions__arr56;
        [FieldOffset(7296)] public BossPerceiveCollisionParam perceiveCollisions__arr57;
        [FieldOffset(7424)] public BossPerceiveCollisionParam perceiveCollisions__arr58;
        [FieldOffset(7552)] public BossPerceiveCollisionParam perceiveCollisions__arr59;
        [FieldOffset(7680)] public BossPerceiveCollisionParam perceiveCollisions__arr60;
        [FieldOffset(7808)] public BossPerceiveCollisionParam perceiveCollisions__arr61;
        [FieldOffset(7936)] public BossPerceiveCollisionParam perceiveCollisions__arr62;
        [FieldOffset(8064)] public BossPerceiveCollisionParam perceiveCollisions__arr63;
        [FieldOffset(8192)] public bool isDebugDraw;
    }

    public enum PointType : sbyte
    {
        PT_HOMINGPOINT = 0,
        PT_HEROSAGE = 1,
        PT_MINIONGENERATOR = 2,
        PT_TRIGGER = 3,
        PT_ANCHOR = 4,
        PT_DAMAGEPOINT = 5,
        PT_STICK = 6,
        PT_DAMAGEEFFECT = 7,
        PT_DASHCIRCLE = 8,
        NUM_POINT_TYPE = 9
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossHomingPointParam
    {
        [FieldOffset(0)]  public BossColliderStatus status;
        [FieldOffset(32)] public float distance;
        [FieldOffset(36)] public float nextSearchDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct BossMinionParam
    {
        [FieldOffset(0)]  public uint num;
        [FieldOffset(4)]  public float interval;
        [FieldOffset(8)]  public float liveTime;
        [FieldOffset(12)] public float waitTime;
    }

    public enum Shape : sbyte
    {
        SHAPE_BOX = 0,
        SHAPE_SPHERE = 1,
        SHAPE_CYLINDER = 2,
        SHAPE_CAPSULE = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct BossTrigerParam
    {
        [FieldOffset(0)]  public Shape ShapeType;
        [FieldOffset(4)]  public float CollisionWidth;
        [FieldOffset(8)]  public float CollisionHeight;
        [FieldOffset(12)] public float CollisionDepth;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct BossStickParam
    {
        [FieldOffset(0)] public float phaseTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct BossDamagePointParam
    {
        [FieldOffset(0)] public bool isCyloopDownUnuse;
        [FieldOffset(8)] public CString text;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossDashCirclPointParam
    {
        [FieldOffset(0)]  public int focusGeometryIndex;
        [FieldOffset(4)]  public int focusTriangleIndex;
        [FieldOffset(8)]  public float sizeScale;
        [FieldOffset(12)] public float impulseSpeed;
        [FieldOffset(16)] public float ocTime;
        [FieldOffset(20)] public float slowRateBoss;
        [FieldOffset(24)] public float slowRatePlayer;
        [FieldOffset(28)] public float slowTime;
        [FieldOffset(32)] public float slowEaseInTime;
        [FieldOffset(36)] public float slowEaseOutTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 224)]
    public struct BossMeshFrameParam
    {
        [FieldOffset(0)]   public bool isUse;
        [FieldOffset(4)]   public uint geometryIndex;
        [FieldOffset(8)]   public uint triangleIndex;
        [FieldOffset(12)]  public PointType type;
        [FieldOffset(16)]  public BossHomingPointParam homingPoint;
        [FieldOffset(56)]  public BossMinionParam minionParam;
        [FieldOffset(72)]  public BossTrigerParam trigger;
        [FieldOffset(88)]  public BossStickParam stickParam;
        [FieldOffset(96)]  public BossDamagePointParam damagePoint;
        [FieldOffset(120)] public BossDashCirclPointParam dashCirclPoint;
        [FieldOffset(160)] public int linkNums__arr0;
        [FieldOffset(164)] public int linkNums__arr1;
        [FieldOffset(168)] public int linkNums__arr2;
        [FieldOffset(172)] public int linkNums__arr3;
        [FieldOffset(176)] public int linkNums__arr4;
        [FieldOffset(192)] public Vector3 offsetPos;
        [FieldOffset(208)] public Vector3 offsetRot;
    }

    [StructLayout(LayoutKind.Explicit, Size = 57360)]
    public struct BossMeshFrameConfig
    {
        [FieldOffset(0)]     public BossMeshFrameParam meshShapeKeyFrames__arr0;
        [FieldOffset(224)] public BossMeshFrameParam meshShapeKeyFrames__arr1;
        [FieldOffset(448)] public BossMeshFrameParam meshShapeKeyFrames__arr2;
        [FieldOffset(672)] public BossMeshFrameParam meshShapeKeyFrames__arr3;
        [FieldOffset(896)] public BossMeshFrameParam meshShapeKeyFrames__arr4;
        [FieldOffset(1120)] public BossMeshFrameParam meshShapeKeyFrames__arr5;
        [FieldOffset(1344)] public BossMeshFrameParam meshShapeKeyFrames__arr6;
        [FieldOffset(1568)] public BossMeshFrameParam meshShapeKeyFrames__arr7;
        [FieldOffset(1792)] public BossMeshFrameParam meshShapeKeyFrames__arr8;
        [FieldOffset(2016)] public BossMeshFrameParam meshShapeKeyFrames__arr9;
        [FieldOffset(2240)] public BossMeshFrameParam meshShapeKeyFrames__arr10;
        [FieldOffset(2464)] public BossMeshFrameParam meshShapeKeyFrames__arr11;
        [FieldOffset(2688)] public BossMeshFrameParam meshShapeKeyFrames__arr12;
        [FieldOffset(2912)] public BossMeshFrameParam meshShapeKeyFrames__arr13;
        [FieldOffset(3136)] public BossMeshFrameParam meshShapeKeyFrames__arr14;
        [FieldOffset(3360)] public BossMeshFrameParam meshShapeKeyFrames__arr15;
        [FieldOffset(3584)] public BossMeshFrameParam meshShapeKeyFrames__arr16;
        [FieldOffset(3808)] public BossMeshFrameParam meshShapeKeyFrames__arr17;
        [FieldOffset(4032)] public BossMeshFrameParam meshShapeKeyFrames__arr18;
        [FieldOffset(4256)] public BossMeshFrameParam meshShapeKeyFrames__arr19;
        [FieldOffset(4480)] public BossMeshFrameParam meshShapeKeyFrames__arr20;
        [FieldOffset(4704)] public BossMeshFrameParam meshShapeKeyFrames__arr21;
        [FieldOffset(4928)] public BossMeshFrameParam meshShapeKeyFrames__arr22;
        [FieldOffset(5152)] public BossMeshFrameParam meshShapeKeyFrames__arr23;
        [FieldOffset(5376)] public BossMeshFrameParam meshShapeKeyFrames__arr24;
        [FieldOffset(5600)] public BossMeshFrameParam meshShapeKeyFrames__arr25;
        [FieldOffset(5824)] public BossMeshFrameParam meshShapeKeyFrames__arr26;
        [FieldOffset(6048)] public BossMeshFrameParam meshShapeKeyFrames__arr27;
        [FieldOffset(6272)] public BossMeshFrameParam meshShapeKeyFrames__arr28;
        [FieldOffset(6496)] public BossMeshFrameParam meshShapeKeyFrames__arr29;
        [FieldOffset(6720)] public BossMeshFrameParam meshShapeKeyFrames__arr30;
        [FieldOffset(6944)] public BossMeshFrameParam meshShapeKeyFrames__arr31;
        [FieldOffset(7168)] public BossMeshFrameParam meshShapeKeyFrames__arr32;
        [FieldOffset(7392)] public BossMeshFrameParam meshShapeKeyFrames__arr33;
        [FieldOffset(7616)] public BossMeshFrameParam meshShapeKeyFrames__arr34;
        [FieldOffset(7840)] public BossMeshFrameParam meshShapeKeyFrames__arr35;
        [FieldOffset(8064)] public BossMeshFrameParam meshShapeKeyFrames__arr36;
        [FieldOffset(8288)] public BossMeshFrameParam meshShapeKeyFrames__arr37;
        [FieldOffset(8512)] public BossMeshFrameParam meshShapeKeyFrames__arr38;
        [FieldOffset(8736)] public BossMeshFrameParam meshShapeKeyFrames__arr39;
        [FieldOffset(8960)] public BossMeshFrameParam meshShapeKeyFrames__arr40;
        [FieldOffset(9184)] public BossMeshFrameParam meshShapeKeyFrames__arr41;
        [FieldOffset(9408)] public BossMeshFrameParam meshShapeKeyFrames__arr42;
        [FieldOffset(9632)] public BossMeshFrameParam meshShapeKeyFrames__arr43;
        [FieldOffset(9856)] public BossMeshFrameParam meshShapeKeyFrames__arr44;
        [FieldOffset(10080)] public BossMeshFrameParam meshShapeKeyFrames__arr45;
        [FieldOffset(10304)] public BossMeshFrameParam meshShapeKeyFrames__arr46;
        [FieldOffset(10528)] public BossMeshFrameParam meshShapeKeyFrames__arr47;
        [FieldOffset(10752)] public BossMeshFrameParam meshShapeKeyFrames__arr48;
        [FieldOffset(10976)] public BossMeshFrameParam meshShapeKeyFrames__arr49;
        [FieldOffset(11200)] public BossMeshFrameParam meshShapeKeyFrames__arr50;
        [FieldOffset(11424)] public BossMeshFrameParam meshShapeKeyFrames__arr51;
        [FieldOffset(11648)] public BossMeshFrameParam meshShapeKeyFrames__arr52;
        [FieldOffset(11872)] public BossMeshFrameParam meshShapeKeyFrames__arr53;
        [FieldOffset(12096)] public BossMeshFrameParam meshShapeKeyFrames__arr54;
        [FieldOffset(12320)] public BossMeshFrameParam meshShapeKeyFrames__arr55;
        [FieldOffset(12544)] public BossMeshFrameParam meshShapeKeyFrames__arr56;
        [FieldOffset(12768)] public BossMeshFrameParam meshShapeKeyFrames__arr57;
        [FieldOffset(12992)] public BossMeshFrameParam meshShapeKeyFrames__arr58;
        [FieldOffset(13216)] public BossMeshFrameParam meshShapeKeyFrames__arr59;
        [FieldOffset(13440)] public BossMeshFrameParam meshShapeKeyFrames__arr60;
        [FieldOffset(13664)] public BossMeshFrameParam meshShapeKeyFrames__arr61;
        [FieldOffset(13888)] public BossMeshFrameParam meshShapeKeyFrames__arr62;
        [FieldOffset(14112)] public BossMeshFrameParam meshShapeKeyFrames__arr63;
        [FieldOffset(14336)] public BossMeshFrameParam meshShapeKeyFrames__arr64;
        [FieldOffset(14560)] public BossMeshFrameParam meshShapeKeyFrames__arr65;
        [FieldOffset(14784)] public BossMeshFrameParam meshShapeKeyFrames__arr66;
        [FieldOffset(15008)] public BossMeshFrameParam meshShapeKeyFrames__arr67;
        [FieldOffset(15232)] public BossMeshFrameParam meshShapeKeyFrames__arr68;
        [FieldOffset(15456)] public BossMeshFrameParam meshShapeKeyFrames__arr69;
        [FieldOffset(15680)] public BossMeshFrameParam meshShapeKeyFrames__arr70;
        [FieldOffset(15904)] public BossMeshFrameParam meshShapeKeyFrames__arr71;
        [FieldOffset(16128)] public BossMeshFrameParam meshShapeKeyFrames__arr72;
        [FieldOffset(16352)] public BossMeshFrameParam meshShapeKeyFrames__arr73;
        [FieldOffset(16576)] public BossMeshFrameParam meshShapeKeyFrames__arr74;
        [FieldOffset(16800)] public BossMeshFrameParam meshShapeKeyFrames__arr75;
        [FieldOffset(17024)] public BossMeshFrameParam meshShapeKeyFrames__arr76;
        [FieldOffset(17248)] public BossMeshFrameParam meshShapeKeyFrames__arr77;
        [FieldOffset(17472)] public BossMeshFrameParam meshShapeKeyFrames__arr78;
        [FieldOffset(17696)] public BossMeshFrameParam meshShapeKeyFrames__arr79;
        [FieldOffset(17920)] public BossMeshFrameParam meshShapeKeyFrames__arr80;
        [FieldOffset(18144)] public BossMeshFrameParam meshShapeKeyFrames__arr81;
        [FieldOffset(18368)] public BossMeshFrameParam meshShapeKeyFrames__arr82;
        [FieldOffset(18592)] public BossMeshFrameParam meshShapeKeyFrames__arr83;
        [FieldOffset(18816)] public BossMeshFrameParam meshShapeKeyFrames__arr84;
        [FieldOffset(19040)] public BossMeshFrameParam meshShapeKeyFrames__arr85;
        [FieldOffset(19264)] public BossMeshFrameParam meshShapeKeyFrames__arr86;
        [FieldOffset(19488)] public BossMeshFrameParam meshShapeKeyFrames__arr87;
        [FieldOffset(19712)] public BossMeshFrameParam meshShapeKeyFrames__arr88;
        [FieldOffset(19936)] public BossMeshFrameParam meshShapeKeyFrames__arr89;
        [FieldOffset(20160)] public BossMeshFrameParam meshShapeKeyFrames__arr90;
        [FieldOffset(20384)] public BossMeshFrameParam meshShapeKeyFrames__arr91;
        [FieldOffset(20608)] public BossMeshFrameParam meshShapeKeyFrames__arr92;
        [FieldOffset(20832)] public BossMeshFrameParam meshShapeKeyFrames__arr93;
        [FieldOffset(21056)] public BossMeshFrameParam meshShapeKeyFrames__arr94;
        [FieldOffset(21280)] public BossMeshFrameParam meshShapeKeyFrames__arr95;
        [FieldOffset(21504)] public BossMeshFrameParam meshShapeKeyFrames__arr96;
        [FieldOffset(21728)] public BossMeshFrameParam meshShapeKeyFrames__arr97;
        [FieldOffset(21952)] public BossMeshFrameParam meshShapeKeyFrames__arr98;
        [FieldOffset(22176)] public BossMeshFrameParam meshShapeKeyFrames__arr99;
        [FieldOffset(22400)] public BossMeshFrameParam meshShapeKeyFrames__arr100;
        [FieldOffset(22624)] public BossMeshFrameParam meshShapeKeyFrames__arr101;
        [FieldOffset(22848)] public BossMeshFrameParam meshShapeKeyFrames__arr102;
        [FieldOffset(23072)] public BossMeshFrameParam meshShapeKeyFrames__arr103;
        [FieldOffset(23296)] public BossMeshFrameParam meshShapeKeyFrames__arr104;
        [FieldOffset(23520)] public BossMeshFrameParam meshShapeKeyFrames__arr105;
        [FieldOffset(23744)] public BossMeshFrameParam meshShapeKeyFrames__arr106;
        [FieldOffset(23968)] public BossMeshFrameParam meshShapeKeyFrames__arr107;
        [FieldOffset(24192)] public BossMeshFrameParam meshShapeKeyFrames__arr108;
        [FieldOffset(24416)] public BossMeshFrameParam meshShapeKeyFrames__arr109;
        [FieldOffset(24640)] public BossMeshFrameParam meshShapeKeyFrames__arr110;
        [FieldOffset(24864)] public BossMeshFrameParam meshShapeKeyFrames__arr111;
        [FieldOffset(25088)] public BossMeshFrameParam meshShapeKeyFrames__arr112;
        [FieldOffset(25312)] public BossMeshFrameParam meshShapeKeyFrames__arr113;
        [FieldOffset(25536)] public BossMeshFrameParam meshShapeKeyFrames__arr114;
        [FieldOffset(25760)] public BossMeshFrameParam meshShapeKeyFrames__arr115;
        [FieldOffset(25984)] public BossMeshFrameParam meshShapeKeyFrames__arr116;
        [FieldOffset(26208)] public BossMeshFrameParam meshShapeKeyFrames__arr117;
        [FieldOffset(26432)] public BossMeshFrameParam meshShapeKeyFrames__arr118;
        [FieldOffset(26656)] public BossMeshFrameParam meshShapeKeyFrames__arr119;
        [FieldOffset(26880)] public BossMeshFrameParam meshShapeKeyFrames__arr120;
        [FieldOffset(27104)] public BossMeshFrameParam meshShapeKeyFrames__arr121;
        [FieldOffset(27328)] public BossMeshFrameParam meshShapeKeyFrames__arr122;
        [FieldOffset(27552)] public BossMeshFrameParam meshShapeKeyFrames__arr123;
        [FieldOffset(27776)] public BossMeshFrameParam meshShapeKeyFrames__arr124;
        [FieldOffset(28000)] public BossMeshFrameParam meshShapeKeyFrames__arr125;
        [FieldOffset(28224)] public BossMeshFrameParam meshShapeKeyFrames__arr126;
        [FieldOffset(28448)] public BossMeshFrameParam meshShapeKeyFrames__arr127;
        [FieldOffset(28672)] public BossMeshFrameParam meshShapeKeyFrames__arr128;
        [FieldOffset(28896)] public BossMeshFrameParam meshShapeKeyFrames__arr129;
        [FieldOffset(29120)] public BossMeshFrameParam meshShapeKeyFrames__arr130;
        [FieldOffset(29344)] public BossMeshFrameParam meshShapeKeyFrames__arr131;
        [FieldOffset(29568)] public BossMeshFrameParam meshShapeKeyFrames__arr132;
        [FieldOffset(29792)] public BossMeshFrameParam meshShapeKeyFrames__arr133;
        [FieldOffset(30016)] public BossMeshFrameParam meshShapeKeyFrames__arr134;
        [FieldOffset(30240)] public BossMeshFrameParam meshShapeKeyFrames__arr135;
        [FieldOffset(30464)] public BossMeshFrameParam meshShapeKeyFrames__arr136;
        [FieldOffset(30688)] public BossMeshFrameParam meshShapeKeyFrames__arr137;
        [FieldOffset(30912)] public BossMeshFrameParam meshShapeKeyFrames__arr138;
        [FieldOffset(31136)] public BossMeshFrameParam meshShapeKeyFrames__arr139;
        [FieldOffset(31360)] public BossMeshFrameParam meshShapeKeyFrames__arr140;
        [FieldOffset(31584)] public BossMeshFrameParam meshShapeKeyFrames__arr141;
        [FieldOffset(31808)] public BossMeshFrameParam meshShapeKeyFrames__arr142;
        [FieldOffset(32032)] public BossMeshFrameParam meshShapeKeyFrames__arr143;
        [FieldOffset(32256)] public BossMeshFrameParam meshShapeKeyFrames__arr144;
        [FieldOffset(32480)] public BossMeshFrameParam meshShapeKeyFrames__arr145;
        [FieldOffset(32704)] public BossMeshFrameParam meshShapeKeyFrames__arr146;
        [FieldOffset(32928)] public BossMeshFrameParam meshShapeKeyFrames__arr147;
        [FieldOffset(33152)] public BossMeshFrameParam meshShapeKeyFrames__arr148;
        [FieldOffset(33376)] public BossMeshFrameParam meshShapeKeyFrames__arr149;
        [FieldOffset(33600)] public BossMeshFrameParam meshShapeKeyFrames__arr150;
        [FieldOffset(33824)] public BossMeshFrameParam meshShapeKeyFrames__arr151;
        [FieldOffset(34048)] public BossMeshFrameParam meshShapeKeyFrames__arr152;
        [FieldOffset(34272)] public BossMeshFrameParam meshShapeKeyFrames__arr153;
        [FieldOffset(34496)] public BossMeshFrameParam meshShapeKeyFrames__arr154;
        [FieldOffset(34720)] public BossMeshFrameParam meshShapeKeyFrames__arr155;
        [FieldOffset(34944)] public BossMeshFrameParam meshShapeKeyFrames__arr156;
        [FieldOffset(35168)] public BossMeshFrameParam meshShapeKeyFrames__arr157;
        [FieldOffset(35392)] public BossMeshFrameParam meshShapeKeyFrames__arr158;
        [FieldOffset(35616)] public BossMeshFrameParam meshShapeKeyFrames__arr159;
        [FieldOffset(35840)] public BossMeshFrameParam meshShapeKeyFrames__arr160;
        [FieldOffset(36064)] public BossMeshFrameParam meshShapeKeyFrames__arr161;
        [FieldOffset(36288)] public BossMeshFrameParam meshShapeKeyFrames__arr162;
        [FieldOffset(36512)] public BossMeshFrameParam meshShapeKeyFrames__arr163;
        [FieldOffset(36736)] public BossMeshFrameParam meshShapeKeyFrames__arr164;
        [FieldOffset(36960)] public BossMeshFrameParam meshShapeKeyFrames__arr165;
        [FieldOffset(37184)] public BossMeshFrameParam meshShapeKeyFrames__arr166;
        [FieldOffset(37408)] public BossMeshFrameParam meshShapeKeyFrames__arr167;
        [FieldOffset(37632)] public BossMeshFrameParam meshShapeKeyFrames__arr168;
        [FieldOffset(37856)] public BossMeshFrameParam meshShapeKeyFrames__arr169;
        [FieldOffset(38080)] public BossMeshFrameParam meshShapeKeyFrames__arr170;
        [FieldOffset(38304)] public BossMeshFrameParam meshShapeKeyFrames__arr171;
        [FieldOffset(38528)] public BossMeshFrameParam meshShapeKeyFrames__arr172;
        [FieldOffset(38752)] public BossMeshFrameParam meshShapeKeyFrames__arr173;
        [FieldOffset(38976)] public BossMeshFrameParam meshShapeKeyFrames__arr174;
        [FieldOffset(39200)] public BossMeshFrameParam meshShapeKeyFrames__arr175;
        [FieldOffset(39424)] public BossMeshFrameParam meshShapeKeyFrames__arr176;
        [FieldOffset(39648)] public BossMeshFrameParam meshShapeKeyFrames__arr177;
        [FieldOffset(39872)] public BossMeshFrameParam meshShapeKeyFrames__arr178;
        [FieldOffset(40096)] public BossMeshFrameParam meshShapeKeyFrames__arr179;
        [FieldOffset(40320)] public BossMeshFrameParam meshShapeKeyFrames__arr180;
        [FieldOffset(40544)] public BossMeshFrameParam meshShapeKeyFrames__arr181;
        [FieldOffset(40768)] public BossMeshFrameParam meshShapeKeyFrames__arr182;
        [FieldOffset(40992)] public BossMeshFrameParam meshShapeKeyFrames__arr183;
        [FieldOffset(41216)] public BossMeshFrameParam meshShapeKeyFrames__arr184;
        [FieldOffset(41440)] public BossMeshFrameParam meshShapeKeyFrames__arr185;
        [FieldOffset(41664)] public BossMeshFrameParam meshShapeKeyFrames__arr186;
        [FieldOffset(41888)] public BossMeshFrameParam meshShapeKeyFrames__arr187;
        [FieldOffset(42112)] public BossMeshFrameParam meshShapeKeyFrames__arr188;
        [FieldOffset(42336)] public BossMeshFrameParam meshShapeKeyFrames__arr189;
        [FieldOffset(42560)] public BossMeshFrameParam meshShapeKeyFrames__arr190;
        [FieldOffset(42784)] public BossMeshFrameParam meshShapeKeyFrames__arr191;
        [FieldOffset(43008)] public BossMeshFrameParam meshShapeKeyFrames__arr192;
        [FieldOffset(43232)] public BossMeshFrameParam meshShapeKeyFrames__arr193;
        [FieldOffset(43456)] public BossMeshFrameParam meshShapeKeyFrames__arr194;
        [FieldOffset(43680)] public BossMeshFrameParam meshShapeKeyFrames__arr195;
        [FieldOffset(43904)] public BossMeshFrameParam meshShapeKeyFrames__arr196;
        [FieldOffset(44128)] public BossMeshFrameParam meshShapeKeyFrames__arr197;
        [FieldOffset(44352)] public BossMeshFrameParam meshShapeKeyFrames__arr198;
        [FieldOffset(44576)] public BossMeshFrameParam meshShapeKeyFrames__arr199;
        [FieldOffset(44800)] public BossMeshFrameParam meshShapeKeyFrames__arr200;
        [FieldOffset(45024)] public BossMeshFrameParam meshShapeKeyFrames__arr201;
        [FieldOffset(45248)] public BossMeshFrameParam meshShapeKeyFrames__arr202;
        [FieldOffset(45472)] public BossMeshFrameParam meshShapeKeyFrames__arr203;
        [FieldOffset(45696)] public BossMeshFrameParam meshShapeKeyFrames__arr204;
        [FieldOffset(45920)] public BossMeshFrameParam meshShapeKeyFrames__arr205;
        [FieldOffset(46144)] public BossMeshFrameParam meshShapeKeyFrames__arr206;
        [FieldOffset(46368)] public BossMeshFrameParam meshShapeKeyFrames__arr207;
        [FieldOffset(46592)] public BossMeshFrameParam meshShapeKeyFrames__arr208;
        [FieldOffset(46816)] public BossMeshFrameParam meshShapeKeyFrames__arr209;
        [FieldOffset(47040)] public BossMeshFrameParam meshShapeKeyFrames__arr210;
        [FieldOffset(47264)] public BossMeshFrameParam meshShapeKeyFrames__arr211;
        [FieldOffset(47488)] public BossMeshFrameParam meshShapeKeyFrames__arr212;
        [FieldOffset(47712)] public BossMeshFrameParam meshShapeKeyFrames__arr213;
        [FieldOffset(47936)] public BossMeshFrameParam meshShapeKeyFrames__arr214;
        [FieldOffset(48160)] public BossMeshFrameParam meshShapeKeyFrames__arr215;
        [FieldOffset(48384)] public BossMeshFrameParam meshShapeKeyFrames__arr216;
        [FieldOffset(48608)] public BossMeshFrameParam meshShapeKeyFrames__arr217;
        [FieldOffset(48832)] public BossMeshFrameParam meshShapeKeyFrames__arr218;
        [FieldOffset(49056)] public BossMeshFrameParam meshShapeKeyFrames__arr219;
        [FieldOffset(49280)] public BossMeshFrameParam meshShapeKeyFrames__arr220;
        [FieldOffset(49504)] public BossMeshFrameParam meshShapeKeyFrames__arr221;
        [FieldOffset(49728)] public BossMeshFrameParam meshShapeKeyFrames__arr222;
        [FieldOffset(49952)] public BossMeshFrameParam meshShapeKeyFrames__arr223;
        [FieldOffset(50176)] public BossMeshFrameParam meshShapeKeyFrames__arr224;
        [FieldOffset(50400)] public BossMeshFrameParam meshShapeKeyFrames__arr225;
        [FieldOffset(50624)] public BossMeshFrameParam meshShapeKeyFrames__arr226;
        [FieldOffset(50848)] public BossMeshFrameParam meshShapeKeyFrames__arr227;
        [FieldOffset(51072)] public BossMeshFrameParam meshShapeKeyFrames__arr228;
        [FieldOffset(51296)] public BossMeshFrameParam meshShapeKeyFrames__arr229;
        [FieldOffset(51520)] public BossMeshFrameParam meshShapeKeyFrames__arr230;
        [FieldOffset(51744)] public BossMeshFrameParam meshShapeKeyFrames__arr231;
        [FieldOffset(51968)] public BossMeshFrameParam meshShapeKeyFrames__arr232;
        [FieldOffset(52192)] public BossMeshFrameParam meshShapeKeyFrames__arr233;
        [FieldOffset(52416)] public BossMeshFrameParam meshShapeKeyFrames__arr234;
        [FieldOffset(52640)] public BossMeshFrameParam meshShapeKeyFrames__arr235;
        [FieldOffset(52864)] public BossMeshFrameParam meshShapeKeyFrames__arr236;
        [FieldOffset(53088)] public BossMeshFrameParam meshShapeKeyFrames__arr237;
        [FieldOffset(53312)] public BossMeshFrameParam meshShapeKeyFrames__arr238;
        [FieldOffset(53536)] public BossMeshFrameParam meshShapeKeyFrames__arr239;
        [FieldOffset(53760)] public BossMeshFrameParam meshShapeKeyFrames__arr240;
        [FieldOffset(53984)] public BossMeshFrameParam meshShapeKeyFrames__arr241;
        [FieldOffset(54208)] public BossMeshFrameParam meshShapeKeyFrames__arr242;
        [FieldOffset(54432)] public BossMeshFrameParam meshShapeKeyFrames__arr243;
        [FieldOffset(54656)] public BossMeshFrameParam meshShapeKeyFrames__arr244;
        [FieldOffset(54880)] public BossMeshFrameParam meshShapeKeyFrames__arr245;
        [FieldOffset(55104)] public BossMeshFrameParam meshShapeKeyFrames__arr246;
        [FieldOffset(55328)] public BossMeshFrameParam meshShapeKeyFrames__arr247;
        [FieldOffset(55552)] public BossMeshFrameParam meshShapeKeyFrames__arr248;
        [FieldOffset(55776)] public BossMeshFrameParam meshShapeKeyFrames__arr249;
        [FieldOffset(56000)] public BossMeshFrameParam meshShapeKeyFrames__arr250;
        [FieldOffset(56224)] public BossMeshFrameParam meshShapeKeyFrames__arr251;
        [FieldOffset(56448)] public BossMeshFrameParam meshShapeKeyFrames__arr252;
        [FieldOffset(56672)] public BossMeshFrameParam meshShapeKeyFrames__arr253;
        [FieldOffset(56896)] public BossMeshFrameParam meshShapeKeyFrames__arr254;
        [FieldOffset(57120)] public BossMeshFrameParam meshShapeKeyFrames__arr255;
        [FieldOffset(57344)] public bool isDebugDraw;
        [FieldOffset(57345)] public bool isDebugDrawPoint;
        [FieldOffset(57346)] public bool isDebugDrawMesh;
        [FieldOffset(57347)] public bool isDebugDrawMeshIndivid;
        [FieldOffset(57348)] public float debugDrawMeshTriangleDistance;
        [FieldOffset(57352)] public uint debugDrawMeshTriangleNum;
    }

    public enum BossAttackCollisionParam_AttackType : sbyte
    {
        AT_NONE = 0,
        AT_BLOWOFF = 1,
        AT_SLAMDOWNWARD = 2,
        AT_KILLING = 3,
        AT_NOTPARRY = 4,
        AT_NOTDAMAGE = 5,
        BossAttackCollisionParam_AttackType_NUM_ATTACK_TYPE = 6
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct BossAttackCollisionParam
    {
        [FieldOffset(0)]  public bool isUse;
        [FieldOffset(8)]  public CString attachNodeName;
        [FieldOffset(24)] public float damageVelocityRaito;
        [FieldOffset(28)] public BossAttackCollisionParam_AttackType types__arr0;
        [FieldOffset(29)] public BossAttackCollisionParam_AttackType types__arr1;
        [FieldOffset(30)] public BossAttackCollisionParam_AttackType types__arr2;
        [FieldOffset(31)] public BossAttackCollisionParam_AttackType types__arr3;
        [FieldOffset(32)] public BossColliderStatus status;
        [FieldOffset(64)] public float size;
        [FieldOffset(80)] public Vector3 offset;
        [FieldOffset(96)] public CString parryCounterTargetCollisionName;
    }

    [StructLayout(LayoutKind.Explicit, Size = 7184)]
    public struct BossAttackCollisionConfig
    {
        [FieldOffset(0)]    public BossAttackCollisionParam attackCollisions__arr0;
        [FieldOffset(112)] public BossAttackCollisionParam attackCollisions__arr1;
        [FieldOffset(224)] public BossAttackCollisionParam attackCollisions__arr2;
        [FieldOffset(336)] public BossAttackCollisionParam attackCollisions__arr3;
        [FieldOffset(448)] public BossAttackCollisionParam attackCollisions__arr4;
        [FieldOffset(560)] public BossAttackCollisionParam attackCollisions__arr5;
        [FieldOffset(672)] public BossAttackCollisionParam attackCollisions__arr6;
        [FieldOffset(784)] public BossAttackCollisionParam attackCollisions__arr7;
        [FieldOffset(896)] public BossAttackCollisionParam attackCollisions__arr8;
        [FieldOffset(1008)] public BossAttackCollisionParam attackCollisions__arr9;
        [FieldOffset(1120)] public BossAttackCollisionParam attackCollisions__arr10;
        [FieldOffset(1232)] public BossAttackCollisionParam attackCollisions__arr11;
        [FieldOffset(1344)] public BossAttackCollisionParam attackCollisions__arr12;
        [FieldOffset(1456)] public BossAttackCollisionParam attackCollisions__arr13;
        [FieldOffset(1568)] public BossAttackCollisionParam attackCollisions__arr14;
        [FieldOffset(1680)] public BossAttackCollisionParam attackCollisions__arr15;
        [FieldOffset(1792)] public BossAttackCollisionParam attackCollisions__arr16;
        [FieldOffset(1904)] public BossAttackCollisionParam attackCollisions__arr17;
        [FieldOffset(2016)] public BossAttackCollisionParam attackCollisions__arr18;
        [FieldOffset(2128)] public BossAttackCollisionParam attackCollisions__arr19;
        [FieldOffset(2240)] public BossAttackCollisionParam attackCollisions__arr20;
        [FieldOffset(2352)] public BossAttackCollisionParam attackCollisions__arr21;
        [FieldOffset(2464)] public BossAttackCollisionParam attackCollisions__arr22;
        [FieldOffset(2576)] public BossAttackCollisionParam attackCollisions__arr23;
        [FieldOffset(2688)] public BossAttackCollisionParam attackCollisions__arr24;
        [FieldOffset(2800)] public BossAttackCollisionParam attackCollisions__arr25;
        [FieldOffset(2912)] public BossAttackCollisionParam attackCollisions__arr26;
        [FieldOffset(3024)] public BossAttackCollisionParam attackCollisions__arr27;
        [FieldOffset(3136)] public BossAttackCollisionParam attackCollisions__arr28;
        [FieldOffset(3248)] public BossAttackCollisionParam attackCollisions__arr29;
        [FieldOffset(3360)] public BossAttackCollisionParam attackCollisions__arr30;
        [FieldOffset(3472)] public BossAttackCollisionParam attackCollisions__arr31;
        [FieldOffset(3584)] public BossAttackCollisionParam attackCollisions__arr32;
        [FieldOffset(3696)] public BossAttackCollisionParam attackCollisions__arr33;
        [FieldOffset(3808)] public BossAttackCollisionParam attackCollisions__arr34;
        [FieldOffset(3920)] public BossAttackCollisionParam attackCollisions__arr35;
        [FieldOffset(4032)] public BossAttackCollisionParam attackCollisions__arr36;
        [FieldOffset(4144)] public BossAttackCollisionParam attackCollisions__arr37;
        [FieldOffset(4256)] public BossAttackCollisionParam attackCollisions__arr38;
        [FieldOffset(4368)] public BossAttackCollisionParam attackCollisions__arr39;
        [FieldOffset(4480)] public BossAttackCollisionParam attackCollisions__arr40;
        [FieldOffset(4592)] public BossAttackCollisionParam attackCollisions__arr41;
        [FieldOffset(4704)] public BossAttackCollisionParam attackCollisions__arr42;
        [FieldOffset(4816)] public BossAttackCollisionParam attackCollisions__arr43;
        [FieldOffset(4928)] public BossAttackCollisionParam attackCollisions__arr44;
        [FieldOffset(5040)] public BossAttackCollisionParam attackCollisions__arr45;
        [FieldOffset(5152)] public BossAttackCollisionParam attackCollisions__arr46;
        [FieldOffset(5264)] public BossAttackCollisionParam attackCollisions__arr47;
        [FieldOffset(5376)] public BossAttackCollisionParam attackCollisions__arr48;
        [FieldOffset(5488)] public BossAttackCollisionParam attackCollisions__arr49;
        [FieldOffset(5600)] public BossAttackCollisionParam attackCollisions__arr50;
        [FieldOffset(5712)] public BossAttackCollisionParam attackCollisions__arr51;
        [FieldOffset(5824)] public BossAttackCollisionParam attackCollisions__arr52;
        [FieldOffset(5936)] public BossAttackCollisionParam attackCollisions__arr53;
        [FieldOffset(6048)] public BossAttackCollisionParam attackCollisions__arr54;
        [FieldOffset(6160)] public BossAttackCollisionParam attackCollisions__arr55;
        [FieldOffset(6272)] public BossAttackCollisionParam attackCollisions__arr56;
        [FieldOffset(6384)] public BossAttackCollisionParam attackCollisions__arr57;
        [FieldOffset(6496)] public BossAttackCollisionParam attackCollisions__arr58;
        [FieldOffset(6608)] public BossAttackCollisionParam attackCollisions__arr59;
        [FieldOffset(6720)] public BossAttackCollisionParam attackCollisions__arr60;
        [FieldOffset(6832)] public BossAttackCollisionParam attackCollisions__arr61;
        [FieldOffset(6944)] public BossAttackCollisionParam attackCollisions__arr62;
        [FieldOffset(7056)] public BossAttackCollisionParam attackCollisions__arr63;
        [FieldOffset(7168)] public bool isDebugDraw;
    }

    [StructLayout(LayoutKind.Explicit, Size = 96)]
    public struct BossBattlePhaseCollisionParam
    {
        [FieldOffset(0)]  public bool isUse;
        [FieldOffset(8)]  public CString attachNodeName;
        [FieldOffset(24)] public CString name;
        [FieldOffset(40)] public float size;
        [FieldOffset(48)] public Vector3 offset;
        [FieldOffset(64)] public Vector3 rotation;
        [FieldOffset(80)] public bool isParryActive;
        [FieldOffset(84)] public float cyloopRadius;
        [FieldOffset(88)] public bool onlyRigidBody;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1552)]
    public struct BossBattlePhaseCollisionConfig
    {
        [FieldOffset(0)]    public BossBattlePhaseCollisionParam battleCollisions__arr0;
        [FieldOffset(96)] public BossBattlePhaseCollisionParam battleCollisions__arr1;
        [FieldOffset(192)] public BossBattlePhaseCollisionParam battleCollisions__arr2;
        [FieldOffset(288)] public BossBattlePhaseCollisionParam battleCollisions__arr3;
        [FieldOffset(384)] public BossBattlePhaseCollisionParam battleCollisions__arr4;
        [FieldOffset(480)] public BossBattlePhaseCollisionParam battleCollisions__arr5;
        [FieldOffset(576)] public BossBattlePhaseCollisionParam battleCollisions__arr6;
        [FieldOffset(672)] public BossBattlePhaseCollisionParam battleCollisions__arr7;
        [FieldOffset(768)] public BossBattlePhaseCollisionParam battleCollisions__arr8;
        [FieldOffset(864)] public BossBattlePhaseCollisionParam battleCollisions__arr9;
        [FieldOffset(960)] public BossBattlePhaseCollisionParam battleCollisions__arr10;
        [FieldOffset(1056)] public BossBattlePhaseCollisionParam battleCollisions__arr11;
        [FieldOffset(1152)] public BossBattlePhaseCollisionParam battleCollisions__arr12;
        [FieldOffset(1248)] public BossBattlePhaseCollisionParam battleCollisions__arr13;
        [FieldOffset(1344)] public BossBattlePhaseCollisionParam battleCollisions__arr14;
        [FieldOffset(1440)] public BossBattlePhaseCollisionParam battleCollisions__arr15;
        [FieldOffset(1536)] public bool isDebugDraw;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct BossDropRingConfig
    {
        [FieldOffset(0)]  public uint ringNumQuickCyloopUp;
        [FieldOffset(4)]  public uint ringNumQuickCyloopDown;
        [FieldOffset(8)]  public uint ringNumSonicSpecial;
        [FieldOffset(12)] public float ringSpawnDistance;
        [FieldOffset(16)] public float ringSuckedVelocity;
    }

    [StructLayout(LayoutKind.Explicit, Size = 75712)]
    public struct BossBaseConfig
    {
        [FieldOffset(0)]     public BossStatusConfig status;
        [FieldOffset(416)]   public BossPillarConfig pillar;
        [FieldOffset(1376)]  public BossPerceivePartsWithCollisionConfig perceivPartsWithCollision;
        [FieldOffset(9584)]  public BossMeshFrameConfig meshShapeKeyFrame;
        [FieldOffset(66944)] public BossAttackCollisionConfig attackCollision;
        [FieldOffset(74128)] public BossBattlePhaseCollisionConfig battleCollision;
        [FieldOffset(75680)] public BossDropRingConfig dropRing;
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct BossDragonCollisionParamBase
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public CString parentFrame;
        [FieldOffset(32)] public Vector3 size;
        [FieldOffset(48)] public Vector3 localPosition;
        [FieldOffset(64)] public Vector3 localRotation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 96)]
    public struct BossDragonHitBoxParam
    {
        [FieldOffset(0)]  public BossDragonCollisionParamBase bossDragonCollisionParamBase;
        [FieldOffset(80)] public Vector3 damageVelocity;
    }

    [StructLayout(LayoutKind.Explicit, Size = 144)]
    public struct BossDragonHurtBoxParam
    {
        [FieldOffset(0)]   public BossDragonCollisionParamBase bossDragonCollisionParamBase;
        [FieldOffset(80)]  public bool isEnableHoming;
        [FieldOffset(88)]  public CString homingNode;
        [FieldOffset(104)] public CString homingNodeMirror;
        [FieldOffset(128)] public Vector3 homingPosition;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct BossDragonScratchParam
    {
        [FieldOffset(0)] public float aimTime;
        [FieldOffset(4)] public float stunTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossDragonReflectShotParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float maxSpeed;
        [FieldOffset(12)] public float accel;
        [FieldOffset(16)] public float reflectSpeedScale;
        [FieldOffset(20)] public float intervalTime;
        [FieldOffset(24)] public float lifeTime;
        [FieldOffset(28)] public float pitchOffsetRange;
        [FieldOffset(32)] public float yawOffsetRange;
        [FieldOffset(36)] public bool isBound;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct BossDragonShotParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float intervalTime;
        [FieldOffset(12)] public float lifeTime;
        [FieldOffset(16)] public float pitchOffsetRange;
        [FieldOffset(20)] public float yawOffsetRange;
        [FieldOffset(24)] public int count;
        [FieldOffset(28)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossDragonSpiralShotParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float intervalTime;
        [FieldOffset(12)] public float lifeTime;
        [FieldOffset(16)] public float pitchSpeed;
        [FieldOffset(20)] public float yawSpeed;
        [FieldOffset(24)] public float circleIntervalTime;
        [FieldOffset(28)] public int count;
        [FieldOffset(32)] public int parriableCount;
        [FieldOffset(36)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 44)]
    public struct BossDragonSplashShotParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float gravity;
        [FieldOffset(12)] public float intervalTime;
        [FieldOffset(16)] public float lifeTime;
        [FieldOffset(20)] public float pitch;
        [FieldOffset(24)] public float pitchInterval;
        [FieldOffset(28)] public float yawInterval;
        [FieldOffset(32)] public int count;
        [FieldOffset(36)] public int parriableCount;
        [FieldOffset(40)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 44)]
    public struct BossDragonHomingLaserParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float speed;
        [FieldOffset(8)]  public float maxAccel;
        [FieldOffset(12)] public float intervalTime;
        [FieldOffset(16)] public float arrivalTime;
        [FieldOffset(20)] public float lifeTime;
        [FieldOffset(24)] public float minPitchOffset;
        [FieldOffset(28)] public float maxPitchOffset;
        [FieldOffset(32)] public float yawOffsetRange;
        [FieldOffset(36)] public int count;
        [FieldOffset(40)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossDragonHomingMissileParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float length;
        [FieldOffset(8)]  public float speed;
        [FieldOffset(12)] public float intervalTime;
        [FieldOffset(16)] public float lifeTime;
        [FieldOffset(20)] public float minPitchOffset;
        [FieldOffset(24)] public float maxPitchOffset;
        [FieldOffset(28)] public float yawOffsetRange;
        [FieldOffset(32)] public int count;
        [FieldOffset(36)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct BossDragonRippleLaserParam
    {
        [FieldOffset(0)]  public float innerRadius;
        [FieldOffset(4)]  public float outerRadius;
        [FieldOffset(8)]  public float speed;
        [FieldOffset(12)] public float intervalTime;
        [FieldOffset(16)] public float lifeTime;
        [FieldOffset(20)] public float pitchOffsetRange;
        [FieldOffset(24)] public float yawOffsetRange;
        [FieldOffset(28)] public int count;
        [FieldOffset(32)] public int parriableCount;
        [FieldOffset(36)] public float intervalTimeInGroup;
        [FieldOffset(40)] public int countInGroup;
        [FieldOffset(44)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 56)]
    public struct BossDragonRippleLaserRageParam
    {
        [FieldOffset(0)]  public float innerRadius;
        [FieldOffset(4)]  public float outerRadius;
        [FieldOffset(8)]  public float speed;
        [FieldOffset(12)] public float intervalTime;
        [FieldOffset(16)] public float lifeTime;
        [FieldOffset(20)] public float maxPitch;
        [FieldOffset(24)] public float maxYaw;
        [FieldOffset(28)] public int verticalCount;
        [FieldOffset(32)] public int horizontalCount;
        [FieldOffset(36)] public int extraFrontCount;
        [FieldOffset(40)] public int parriableCount;
        [FieldOffset(44)] public float intervalTimeInGroup;
        [FieldOffset(48)] public int countInGroup;
        [FieldOffset(52)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossDragonRippleLaserDummyParam
    {
        [FieldOffset(0)]  public float innerRadius;
        [FieldOffset(4)]  public float outerRadius;
        [FieldOffset(8)]  public float speed;
        [FieldOffset(12)] public float intervalTime;
        [FieldOffset(16)] public float lifeTime;
        [FieldOffset(20)] public float pitchOffsetRange;
        [FieldOffset(24)] public float yawOffsetRange;
        [FieldOffset(28)] public int count;
        [FieldOffset(32)] public float intervalTimeInGroup;
        [FieldOffset(36)] public int countInGroup;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct BossDragonWaveParam
    {
        [FieldOffset(0)]  public float speed;
        [FieldOffset(4)]  public float rotSpeed;
        [FieldOffset(8)]  public float accel;
        [FieldOffset(12)] public float rotAccel;
        [FieldOffset(16)] public float intervalTime;
        [FieldOffset(20)] public float lifeTime;
        [FieldOffset(24)] public int segmentCount;
        [FieldOffset(28)] public float waveRate;
        [FieldOffset(32)] public int count;
        [FieldOffset(36)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct BossDragonLaserParam
    {
        [FieldOffset(0)]  public float radius;
        [FieldOffset(4)]  public float length;
        [FieldOffset(8)]  public float rotSpeed;
        [FieldOffset(12)] public float rotAccel;
        [FieldOffset(16)] public float roll;
        [FieldOffset(20)] public float intervalTime;
        [FieldOffset(24)] public float standbyTime;
        [FieldOffset(28)] public int count;
        [FieldOffset(32)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct BossDragonCounterLaserParam
    {
        [FieldOffset(0)] public float radius;
        [FieldOffset(4)] public float speed;
        [FieldOffset(8)] public float lifeTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct BossDragonRingSupplyMissileParam
    {
        [FieldOffset(0)] public int missileNum;
        [FieldOffset(4)] public float missileWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct BossDragonRingSupplyParam
    {
        [FieldOffset(0)]  public Vector3 playerPosition;
        [FieldOffset(16)] public float moveTime;
        [FieldOffset(20)] public float moveRange;
        [FieldOffset(24)] public float rotSpeed;
        [FieldOffset(28)] public BossDragonRingSupplyMissileParam missile__arr0;
        [FieldOffset(36)] public BossDragonRingSupplyMissileParam missile__arr1;
        [FieldOffset(44)] public BossDragonRingSupplyMissileParam missile__arr2;
    }

    public enum BossDragonLayoutParam_EaseType : sbyte
    {
        SMOOTH = 0,
        EASE_IN = 1,
        EASE_OUT = 2,
        EASE_IN_OUT = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct BossDragonLayoutParam
    {
        [FieldOffset(0)]  public Vector3 bossPosition;
        [FieldOffset(16)] public float bossYaw;
        [FieldOffset(20)] public BossDragonLayoutParam_EaseType bossEaseType;
        [FieldOffset(24)] public float bossEaseTime;
        [FieldOffset(32)] public Vector3 playerPosition;
        [FieldOffset(48)] public float playerFieldRange;
        [FieldOffset(52)] public float playerFieldHeight;
        [FieldOffset(56)] public float playerFieldYaw;
        [FieldOffset(60)] public BossDragonLayoutParam_EaseType playerEaseType;
        [FieldOffset(64)] public float playerEaseTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct BossDragonCameraParam
    {
        [FieldOffset(0)]  public CString gazeFrame;
        [FieldOffset(16)] public CString gazeFrameMirror;
        [FieldOffset(32)] public Vector3 gazeOffset;
        [FieldOffset(48)] public float distance;
        [FieldOffset(64)] public Vector3 playerOffset;
        [FieldOffset(80)] public float elevationOffset;
        [FieldOffset(96)] public Vector3 followRate;
    }

    [StructLayout(LayoutKind.Explicit, Size = 272)]
    public struct BossDragonMoveParam
    {
        [FieldOffset(0)]   public Vector3 playerNodes__arr0;
        [FieldOffset(16)] public Vector3 playerNodes__arr1;
        [FieldOffset(32)] public Vector3 playerNodes__arr2;
        [FieldOffset(48)] public Vector3 playerNodes__arr3;
        [FieldOffset(64)] public Vector3 playerNodes__arr4;
        [FieldOffset(80)] public Vector3 playerNodes__arr5;
        [FieldOffset(96)] public Vector3 playerNodes__arr6;
        [FieldOffset(112)] public Vector3 playerNodes__arr7;
        [FieldOffset(128)] public Vector3 bossNodes__arr0;
        [FieldOffset(144)] public Vector3 bossNodes__arr1;
        [FieldOffset(160)] public Vector3 bossNodes__arr2;
        [FieldOffset(176)] public Vector3 bossNodes__arr3;
        [FieldOffset(192)] public Vector3 bossNodes__arr4;
        [FieldOffset(208)] public Vector3 bossNodes__arr5;
        [FieldOffset(224)] public Vector3 bossNodes__arr6;
        [FieldOffset(240)] public Vector3 bossNodes__arr7;
        [FieldOffset(256)] public int playerNodeCount;
        [FieldOffset(260)] public int bossNodeCount;
        [FieldOffset(264)] public float time;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct BossDragonFireBarParam
    {
        [FieldOffset(0)] public float radius;
        [FieldOffset(4)] public float length;
        [FieldOffset(8)] public float rotSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct BossDragonEscapeShotParam
    {
        [FieldOffset(0)]  public uint vertRatio__arr0;
        [FieldOffset(4)] public uint vertRatio__arr1;
        [FieldOffset(8)] public uint vertRatio__arr2;
        [FieldOffset(12)] public float initSpeed;
        [FieldOffset(16)] public float maxSpeed;
        [FieldOffset(20)] public float acc;
        [FieldOffset(24)] public float lifeTime;
    }

    public enum Type : sbyte
    {
        None = 0,
        FireBar = 1,
        FireBar4 = 2,
        Spark = 3
    }

    public enum Location : sbyte
    {
        Left = 0,
        Center = 1,
        Right = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct BossDragonObstacleParam
    {
        [FieldOffset(0)] public float distance;
        [FieldOffset(4)] public Type type;
        [FieldOffset(5)] public Location location;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct BossDragonHoleParam
    {
        [FieldOffset(0)] public float start;
        [FieldOffset(4)] public float end;
    }

    [StructLayout(LayoutKind.Explicit, Size = 692)]
    public struct BossDragonRoadParam
    {
        [FieldOffset(0)]   public float interval;
        [FieldOffset(4)]   public int recordNum;
        [FieldOffset(8)]   public float width;
        [FieldOffset(12)]  public BossDragonFireBarParam fireBar;
        [FieldOffset(24)]  public BossDragonEscapeShotParam shot;
        [FieldOffset(52)]  public BossDragonObstacleParam obstacles__arr0;
        [FieldOffset(60)] public BossDragonObstacleParam obstacles__arr1;
        [FieldOffset(68)] public BossDragonObstacleParam obstacles__arr2;
        [FieldOffset(76)] public BossDragonObstacleParam obstacles__arr3;
        [FieldOffset(84)] public BossDragonObstacleParam obstacles__arr4;
        [FieldOffset(92)] public BossDragonObstacleParam obstacles__arr5;
        [FieldOffset(100)] public BossDragonObstacleParam obstacles__arr6;
        [FieldOffset(108)] public BossDragonObstacleParam obstacles__arr7;
        [FieldOffset(116)] public BossDragonObstacleParam obstacles__arr8;
        [FieldOffset(124)] public BossDragonObstacleParam obstacles__arr9;
        [FieldOffset(132)] public BossDragonObstacleParam obstacles__arr10;
        [FieldOffset(140)] public BossDragonObstacleParam obstacles__arr11;
        [FieldOffset(148)] public BossDragonObstacleParam obstacles__arr12;
        [FieldOffset(156)] public BossDragonObstacleParam obstacles__arr13;
        [FieldOffset(164)] public BossDragonObstacleParam obstacles__arr14;
        [FieldOffset(172)] public BossDragonObstacleParam obstacles__arr15;
        [FieldOffset(180)] public BossDragonObstacleParam obstacles__arr16;
        [FieldOffset(188)] public BossDragonObstacleParam obstacles__arr17;
        [FieldOffset(196)] public BossDragonObstacleParam obstacles__arr18;
        [FieldOffset(204)] public BossDragonObstacleParam obstacles__arr19;
        [FieldOffset(212)] public BossDragonObstacleParam obstacles__arr20;
        [FieldOffset(220)] public BossDragonObstacleParam obstacles__arr21;
        [FieldOffset(228)] public BossDragonObstacleParam obstacles__arr22;
        [FieldOffset(236)] public BossDragonObstacleParam obstacles__arr23;
        [FieldOffset(244)] public BossDragonObstacleParam obstacles__arr24;
        [FieldOffset(252)] public BossDragonObstacleParam obstacles__arr25;
        [FieldOffset(260)] public BossDragonObstacleParam obstacles__arr26;
        [FieldOffset(268)] public BossDragonObstacleParam obstacles__arr27;
        [FieldOffset(276)] public BossDragonObstacleParam obstacles__arr28;
        [FieldOffset(284)] public BossDragonObstacleParam obstacles__arr29;
        [FieldOffset(292)] public BossDragonObstacleParam obstacles__arr30;
        [FieldOffset(300)] public BossDragonObstacleParam obstacles__arr31;
        [FieldOffset(308)] public BossDragonObstacleParam obstacles__arr32;
        [FieldOffset(316)] public BossDragonObstacleParam obstacles__arr33;
        [FieldOffset(324)] public BossDragonObstacleParam obstacles__arr34;
        [FieldOffset(332)] public BossDragonObstacleParam obstacles__arr35;
        [FieldOffset(340)] public BossDragonObstacleParam obstacles__arr36;
        [FieldOffset(348)] public BossDragonObstacleParam obstacles__arr37;
        [FieldOffset(356)] public BossDragonObstacleParam obstacles__arr38;
        [FieldOffset(364)] public BossDragonObstacleParam obstacles__arr39;
        [FieldOffset(372)] public BossDragonObstacleParam obstacles__arr40;
        [FieldOffset(380)] public BossDragonObstacleParam obstacles__arr41;
        [FieldOffset(388)] public BossDragonObstacleParam obstacles__arr42;
        [FieldOffset(396)] public BossDragonObstacleParam obstacles__arr43;
        [FieldOffset(404)] public BossDragonObstacleParam obstacles__arr44;
        [FieldOffset(412)] public BossDragonObstacleParam obstacles__arr45;
        [FieldOffset(420)] public BossDragonObstacleParam obstacles__arr46;
        [FieldOffset(428)] public BossDragonObstacleParam obstacles__arr47;
        [FieldOffset(436)] public BossDragonObstacleParam obstacles__arr48;
        [FieldOffset(444)] public BossDragonObstacleParam obstacles__arr49;
        [FieldOffset(452)] public BossDragonObstacleParam obstacles__arr50;
        [FieldOffset(460)] public BossDragonObstacleParam obstacles__arr51;
        [FieldOffset(468)] public BossDragonObstacleParam obstacles__arr52;
        [FieldOffset(476)] public BossDragonObstacleParam obstacles__arr53;
        [FieldOffset(484)] public BossDragonObstacleParam obstacles__arr54;
        [FieldOffset(492)] public BossDragonObstacleParam obstacles__arr55;
        [FieldOffset(500)] public BossDragonObstacleParam obstacles__arr56;
        [FieldOffset(508)] public BossDragonObstacleParam obstacles__arr57;
        [FieldOffset(516)] public BossDragonObstacleParam obstacles__arr58;
        [FieldOffset(524)] public BossDragonObstacleParam obstacles__arr59;
        [FieldOffset(532)] public BossDragonObstacleParam obstacles__arr60;
        [FieldOffset(540)] public BossDragonObstacleParam obstacles__arr61;
        [FieldOffset(548)] public BossDragonObstacleParam obstacles__arr62;
        [FieldOffset(556)] public BossDragonObstacleParam obstacles__arr63;
        [FieldOffset(564)] public BossDragonHoleParam holes__arr0;
        [FieldOffset(572)] public BossDragonHoleParam holes__arr1;
        [FieldOffset(580)] public BossDragonHoleParam holes__arr2;
        [FieldOffset(588)] public BossDragonHoleParam holes__arr3;
        [FieldOffset(596)] public BossDragonHoleParam holes__arr4;
        [FieldOffset(604)] public BossDragonHoleParam holes__arr5;
        [FieldOffset(612)] public BossDragonHoleParam holes__arr6;
        [FieldOffset(620)] public BossDragonHoleParam holes__arr7;
        [FieldOffset(628)] public BossDragonHoleParam holes__arr8;
        [FieldOffset(636)] public BossDragonHoleParam holes__arr9;
        [FieldOffset(644)] public BossDragonHoleParam holes__arr10;
        [FieldOffset(652)] public BossDragonHoleParam holes__arr11;
        [FieldOffset(660)] public BossDragonHoleParam holes__arr12;
        [FieldOffset(668)] public BossDragonHoleParam holes__arr13;
        [FieldOffset(676)] public BossDragonHoleParam holes__arr14;
        [FieldOffset(684)] public BossDragonHoleParam holes__arr15;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct BossDragonLaunchParam
    {
        [FieldOffset(0)]   public float outStrength;
        [FieldOffset(4)]   public float inStrength;
        [FieldOffset(8)]   public float outElev;
        [FieldOffset(12)]  public float inElev;
        [FieldOffset(16)]  public float speed;
        [FieldOffset(32)]  public Vector3 targetOffset;
        [FieldOffset(48)]  public float launchCameraInterpolateTime;
        [FieldOffset(64)]  public Vector3 launchCameraPos;
        [FieldOffset(80)]  public Vector3 launchCameraTarget;
        [FieldOffset(96)]  public float launchCameraRoll;
        [FieldOffset(100)] public float launchCameraTime;
        [FieldOffset(104)] public float fallCameraInterpolateTime;
        [FieldOffset(108)] public float fallCameraDistance;
        [FieldOffset(112)] public float fallCameraElavation;
        [FieldOffset(116)] public float landingCameraInterpolateTime;
        [FieldOffset(120)] public float landingCameraDistance;
        [FieldOffset(124)] public float landingCameraElavation;
        [FieldOffset(128)] public float landingCameraAzimuth;
        [FieldOffset(132)] public float landingCameraChangeDistance;
        [FieldOffset(136)] public float landingCameraNearInterpolateTime;
        [FieldOffset(140)] public float landingCameraNearDistance;
        [FieldOffset(144)] public float landingCameraNearElavation;
        [FieldOffset(148)] public float landingCameraNearAzimuth;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct BossDragonQuickStepParam
    {
        [FieldOffset(0)] public float speed;
        [FieldOffset(4)] public float boostSpeed;
        [FieldOffset(8)] public float boostSpeedMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 56)]
    public struct BossDragonChaseParam
    {
        [FieldOffset(0)]  public float distance;
        [FieldOffset(4)]  public float goalOffset;
        [FieldOffset(8)]  public float speed;
        [FieldOffset(12)] public float boostSpeed;
        [FieldOffset(16)] public float width;
        [FieldOffset(20)] public float height;
        [FieldOffset(24)] public float closeDistance;
        [FieldOffset(28)] public float closeSpeedScale;
        [FieldOffset(32)] public float fastMoveDistance;
        [FieldOffset(36)] public float stunTime;
        [FieldOffset(40)] public float stunSpeedScale;
        [FieldOffset(44)] public float superBoostDelayTime;
        [FieldOffset(48)] public float superBoostTime;
        [FieldOffset(52)] public float superBoostSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct BossDragonMissileIndividualParam
    {
        [FieldOffset(0)]  public bool isValid;
        [FieldOffset(4)]  public float rotForce;
        [FieldOffset(8)]  public float maxRotForce;
        [FieldOffset(12)] public float rotForceSpeed;
        [FieldOffset(16)] public float rotDamper;
        [FieldOffset(20)] public float straightTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct BossDragonMissileFirePattern
    {
        [FieldOffset(0)]  public float hpRatioThreshold;
        [FieldOffset(4)]  public int count;
        [FieldOffset(8)]  public float intervalTime;
        [FieldOffset(12)] public float waitTime;
        [FieldOffset(16)] public float badRatio;
    }

    [StructLayout(LayoutKind.Explicit, Size = 760)]
    public struct BossDragonMissileParam
    {
        [FieldOffset(0)]   public float radius;
        [FieldOffset(4)]   public float length;
        [FieldOffset(8)]   public float speed;
        [FieldOffset(12)]  public float maxSpeed;
        [FieldOffset(16)]  public float accel;
        [FieldOffset(20)]  public float lifeTime;
        [FieldOffset(24)]  public BossDragonMissileIndividualParam individuals__arr0;
        [FieldOffset(48)] public BossDragonMissileIndividualParam individuals__arr1;
        [FieldOffset(72)] public BossDragonMissileIndividualParam individuals__arr2;
        [FieldOffset(96)] public BossDragonMissileIndividualParam individuals__arr3;
        [FieldOffset(120)] public BossDragonMissileIndividualParam individuals__arr4;
        [FieldOffset(144)] public BossDragonMissileIndividualParam individuals__arr5;
        [FieldOffset(168)] public BossDragonMissileIndividualParam individuals__arr6;
        [FieldOffset(192)] public BossDragonMissileIndividualParam individuals__arr7;
        [FieldOffset(216)] public BossDragonMissileIndividualParam individuals__arr8;
        [FieldOffset(240)] public BossDragonMissileIndividualParam individuals__arr9;
        [FieldOffset(264)] public BossDragonMissileIndividualParam individuals__arr10;
        [FieldOffset(288)] public BossDragonMissileIndividualParam individuals__arr11;
        [FieldOffset(312)] public BossDragonMissileIndividualParam individuals__arr12;
        [FieldOffset(336)] public BossDragonMissileIndividualParam individuals__arr13;
        [FieldOffset(360)] public BossDragonMissileIndividualParam individuals__arr14;
        [FieldOffset(384)] public BossDragonMissileIndividualParam individuals__arr15;
        [FieldOffset(408)] public BossDragonMissileIndividualParam badIndividuals__arr0;
        [FieldOffset(432)] public BossDragonMissileIndividualParam badIndividuals__arr1;
        [FieldOffset(456)] public BossDragonMissileIndividualParam badIndividuals__arr2;
        [FieldOffset(480)] public BossDragonMissileIndividualParam badIndividuals__arr3;
        [FieldOffset(504)] public BossDragonMissileIndividualParam badIndividuals__arr4;
        [FieldOffset(528)] public BossDragonMissileIndividualParam badIndividuals__arr5;
        [FieldOffset(552)] public BossDragonMissileIndividualParam badIndividuals__arr6;
        [FieldOffset(576)] public BossDragonMissileIndividualParam badIndividuals__arr7;
        [FieldOffset(600)] public BossDragonMissileFirePattern firePatterns__arr0;
        [FieldOffset(620)] public BossDragonMissileFirePattern firePatterns__arr1;
        [FieldOffset(640)] public BossDragonMissileFirePattern firePatterns__arr2;
        [FieldOffset(660)] public BossDragonMissileFirePattern firePatterns__arr3;
        [FieldOffset(680)] public BossDragonMissileFirePattern firePatterns__arr4;
        [FieldOffset(700)] public BossDragonMissileFirePattern firePatterns__arr5;
        [FieldOffset(720)] public BossDragonMissileFirePattern firePatterns__arr6;
        [FieldOffset(740)] public BossDragonMissileFirePattern firePatterns__arr7;
    }

    public enum BossDragonSequence : sbyte
    {
        NOP = 0,
        BITE = 1,
        LIGHT_SCRATCH = 2,
        SCRATCH = 3,
        SHOOT = 4,
        SHOOT_NORMAL = 5,
        SHOOT_SPIRAL = 6,
        SHOOT_SPIRAL_ALTERNATE = 7,
        SHOOT_SPIRAL_VERTICAL = 8,
        SHOOT_SPLASH = 9,
        SHOOT_HOMING_LASER = 10,
        SHOOT_HOMING_MISSILE = 11,
        SHOOT_RIPPLE_LASER = 12,
        SHOOT_RIPPLE_LASER_RAGE = 13,
        SHOOT_WAVE = 14,
        SHOOT_LASER_WINDER = 15,
        SHOOT_RANDOM_LASER = 16,
        SHOOT_END = 17,
        SWAP_SIDE = 18,
        CHASE = 19
    }

    public enum BossDragonInterrupt : sbyte
    {
        BossDragonInterrupt_NOP = 0,
        RAGE = 1,
        SPECIAL_ATTACK = 2,
        SPECIAL_ATTACK2 = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct BossDragonInterruptParam
    {
        [FieldOffset(0)] public float hpRatio;
        [FieldOffset(4)] public BossDragonInterrupt interrupt;
        [FieldOffset(5)] public bool forceInterrupt;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct BossDragonCyloopBindParam
    {
        [FieldOffset(0)] public float postCameraTime__arr0;
        [FieldOffset(4)] public float postCameraTime__arr1;
        [FieldOffset(8)] public float postCameraTime__arr2;
        [FieldOffset(12)] public float postCameraTime__arr3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct BossDragonParrySlowParam
    {
        [FieldOffset(0)]  public float scale;
        [FieldOffset(4)]  public float time;
        [FieldOffset(8)]  public float easeOutTime;
        [FieldOffset(12)] public bool cameraSlow;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct BossDragonParryParam
    {
        [FieldOffset(0)] public BossDragonParrySlowParam slowParams__arr0;
        [FieldOffset(16)] public BossDragonParrySlowParam slowParams__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct BossDragonAttackSignParam
    {
        [FieldOffset(0)] public float delayTime__arr0;
        [FieldOffset(4)] public float delayTime__arr1;
        [FieldOffset(8)] public float delayTime__arr2;
        [FieldOffset(12)] public float delayTime__arr3;
        [FieldOffset(16)] public float delayTime__arr4;
        [FieldOffset(20)] public float delayTime__arr5;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3)]
    public struct EnemyPracticeNotifierConfig
    {
        [FieldOffset(0)] public bool usePracticeNotifier;
        [FieldOffset(1)] public sbyte practiceNo;
        [FieldOffset(2)] public sbyte tipsNo;
    }

    [StructLayout(LayoutKind.Explicit, Size = 6)]
    public struct BossDragonNotifierParam
    {
        [FieldOffset(0)] public EnemyPracticeNotifierConfig notifierConfigClimb;
        [FieldOffset(3)] public EnemyPracticeNotifierConfig notifierConfigBattle;
    }

    [StructLayout(LayoutKind.Explicit, Size = 95632)]
    public struct BossDragonConfig
    {
        [FieldOffset(0)]     public BossBaseConfig bossBaseConfig;
        [FieldOffset(75712)] public float cruisePathSpeed;
        [FieldOffset(75716)] public float patrolPathSpeed;
        [FieldOffset(75720)] public float approachPathSpeedMin;
        [FieldOffset(75724)] public float approachPathSpeedMax;
        [FieldOffset(75728)] public float climbPathSpeed;
        [FieldOffset(75732)] public float pathSpeed;
        [FieldOffset(75736)] public float ringSupplyPathSpeed;
        [FieldOffset(75740)] public float sideDistance;
        [FieldOffset(75744)] public float shootEndTime;
        [FieldOffset(75748)] public int staggerPoint;
        [FieldOffset(75752)] public int staggerPointRage;
        [FieldOffset(75756)] public float staggerTime;
        [FieldOffset(75760)] public float biteParriedTime;
        [FieldOffset(75764)] public float scratchParriedTime;
        [FieldOffset(75768)] public int knockBackStaggerCount;
        [FieldOffset(75772)] public int knockBackPoint;
        [FieldOffset(75776)] public float knockBackTime;
        [FieldOffset(75780)] public float hardStunTime;
        [FieldOffset(75784)] public float cyloopBindTime;
        [FieldOffset(75788)] public float cyloopBind2Time;
        [FieldOffset(75792)] public float cyloopEscapeHpRatio;
        [FieldOffset(75796)] public float cyloopEscapeTime;
        [FieldOffset(75800)] public float fallDeadHeight;
        [FieldOffset(75804)] public int specialAttackDamage;
        [FieldOffset(75808)] public int qte1Damage;
        [FieldOffset(75816)] public CString accessNodeNames__arr0;
        [FieldOffset(76071)] public CString accessNodeNames__arr1;
        [FieldOffset(76326)] public CString accessNodeNames__arr2;
        [FieldOffset(76581)] public CString accessNodeNames__arr3;
        [FieldOffset(76836)] public CString accessNodeNames__arr4;
        [FieldOffset(77091)] public CString accessNodeNames__arr5;
        [FieldOffset(77346)] public CString accessNodeNames__arr6;
        [FieldOffset(77601)] public CString accessNodeNames__arr7;
        [FieldOffset(77856)] public CString accessNodeNames__arr8;
        [FieldOffset(78111)] public CString accessNodeNames__arr9;
        [FieldOffset(78366)] public CString accessNodeNames__arr10;
        [FieldOffset(78621)] public CString accessNodeNames__arr11;
        [FieldOffset(78876)] public CString accessNodeNames__arr12;
        [FieldOffset(79131)] public CString accessNodeNames__arr13;
        [FieldOffset(79386)] public CString accessNodeNames__arr14;
        [FieldOffset(79641)] public CString accessNodeNames__arr15;
        [FieldOffset(76080)] public BossDragonHitBoxParam hitBoxes__arr0;
        [FieldOffset(76176)] public BossDragonHitBoxParam hitBoxes__arr1;
        [FieldOffset(76272)] public BossDragonHitBoxParam hitBoxes__arr2;
        [FieldOffset(76368)] public BossDragonHitBoxParam hitBoxes__arr3;
        [FieldOffset(76464)] public BossDragonHitBoxParam hitBoxes__arr4;
        [FieldOffset(76560)] public BossDragonHitBoxParam hitBoxes__arr5;
        [FieldOffset(76656)] public BossDragonHitBoxParam hitBoxes__arr6;
        [FieldOffset(76752)] public BossDragonHitBoxParam hitBoxes__arr7;
        [FieldOffset(76848)] public BossDragonHitBoxParam hitBoxes__arr8;
        [FieldOffset(76944)] public BossDragonHitBoxParam hitBoxes__arr9;
        [FieldOffset(77040)] public BossDragonHitBoxParam hitBoxes__arr10;
        [FieldOffset(77136)] public BossDragonHitBoxParam hitBoxes__arr11;
        [FieldOffset(77232)] public BossDragonHitBoxParam hitBoxes__arr12;
        [FieldOffset(77328)] public BossDragonHitBoxParam hitBoxes__arr13;
        [FieldOffset(77424)] public BossDragonHitBoxParam hitBoxes__arr14;
        [FieldOffset(77520)] public BossDragonHitBoxParam hitBoxes__arr15;
        [FieldOffset(77616)] public BossDragonHitBoxParam hitBoxes__arr16;
        [FieldOffset(77712)] public BossDragonHitBoxParam hitBoxes__arr17;
        [FieldOffset(77808)] public BossDragonHitBoxParam hitBoxes__arr18;
        [FieldOffset(77904)] public BossDragonHitBoxParam hitBoxes__arr19;
        [FieldOffset(78000)] public BossDragonHitBoxParam hitBoxes__arr20;
        [FieldOffset(78096)] public BossDragonHitBoxParam hitBoxes__arr21;
        [FieldOffset(78192)] public BossDragonHitBoxParam hitBoxes__arr22;
        [FieldOffset(78288)] public BossDragonHitBoxParam hitBoxes__arr23;
        [FieldOffset(78384)] public BossDragonHitBoxParam hitBoxes__arr24;
        [FieldOffset(78480)] public BossDragonHitBoxParam hitBoxes__arr25;
        [FieldOffset(78576)] public BossDragonHitBoxParam hitBoxes__arr26;
        [FieldOffset(78672)] public BossDragonHitBoxParam hitBoxes__arr27;
        [FieldOffset(78768)] public BossDragonHitBoxParam hitBoxes__arr28;
        [FieldOffset(78864)] public BossDragonHitBoxParam hitBoxes__arr29;
        [FieldOffset(78960)] public BossDragonHitBoxParam hitBoxes__arr30;
        [FieldOffset(79056)] public BossDragonHitBoxParam hitBoxes__arr31;
        [FieldOffset(79152)] public BossDragonHurtBoxParam hurtBoxes__arr0;
        [FieldOffset(79296)] public BossDragonHurtBoxParam hurtBoxes__arr1;
        [FieldOffset(79440)] public BossDragonHurtBoxParam hurtBoxes__arr2;
        [FieldOffset(79584)] public BossDragonHurtBoxParam hurtBoxes__arr3;
        [FieldOffset(79728)] public BossDragonHurtBoxParam hurtBoxes__arr4;
        [FieldOffset(79872)] public BossDragonHurtBoxParam hurtBoxes__arr5;
        [FieldOffset(80016)] public BossDragonHurtBoxParam hurtBoxes__arr6;
        [FieldOffset(80160)] public BossDragonHurtBoxParam hurtBoxes__arr7;
        [FieldOffset(80304)] public BossDragonHurtBoxParam hurtBoxes__arr8;
        [FieldOffset(80448)] public BossDragonHurtBoxParam hurtBoxes__arr9;
        [FieldOffset(80592)] public BossDragonHurtBoxParam hurtBoxes__arr10;
        [FieldOffset(80736)] public BossDragonHurtBoxParam hurtBoxes__arr11;
        [FieldOffset(80880)] public BossDragonHurtBoxParam hurtBoxes__arr12;
        [FieldOffset(81024)] public BossDragonHurtBoxParam hurtBoxes__arr13;
        [FieldOffset(81168)] public BossDragonHurtBoxParam hurtBoxes__arr14;
        [FieldOffset(81312)] public BossDragonHurtBoxParam hurtBoxes__arr15;
        [FieldOffset(81456)] public BossDragonHurtBoxParam hurtBoxes__arr16;
        [FieldOffset(81600)] public BossDragonHurtBoxParam hurtBoxes__arr17;
        [FieldOffset(81744)] public BossDragonHurtBoxParam hurtBoxes__arr18;
        [FieldOffset(81888)] public BossDragonHurtBoxParam hurtBoxes__arr19;
        [FieldOffset(82032)] public BossDragonHurtBoxParam hurtBoxes__arr20;
        [FieldOffset(82176)] public BossDragonHurtBoxParam hurtBoxes__arr21;
        [FieldOffset(82320)] public BossDragonHurtBoxParam hurtBoxes__arr22;
        [FieldOffset(82464)] public BossDragonHurtBoxParam hurtBoxes__arr23;
        [FieldOffset(82608)] public BossDragonHurtBoxParam hurtBoxes__arr24;
        [FieldOffset(82752)] public BossDragonHurtBoxParam hurtBoxes__arr25;
        [FieldOffset(82896)] public BossDragonHurtBoxParam hurtBoxes__arr26;
        [FieldOffset(83040)] public BossDragonHurtBoxParam hurtBoxes__arr27;
        [FieldOffset(83184)] public BossDragonHurtBoxParam hurtBoxes__arr28;
        [FieldOffset(83328)] public BossDragonHurtBoxParam hurtBoxes__arr29;
        [FieldOffset(83472)] public BossDragonHurtBoxParam hurtBoxes__arr30;
        [FieldOffset(83616)] public BossDragonHurtBoxParam hurtBoxes__arr31;
        [FieldOffset(83760)] public BossDragonScratchParam scratch;
        [FieldOffset(83768)] public BossDragonReflectShotParam reflect;
        [FieldOffset(83808)] public BossDragonShotParam shot;
        [FieldOffset(83840)] public BossDragonSpiralShotParam spiral;
        [FieldOffset(83880)] public BossDragonSpiralShotParam spiralAlternate;
        [FieldOffset(83920)] public BossDragonSpiralShotParam spiralVertical;
        [FieldOffset(83960)] public BossDragonSplashShotParam splash;
        [FieldOffset(84004)] public BossDragonHomingLaserParam homingLaser;
        [FieldOffset(84048)] public BossDragonHomingMissileParam homingMissile;
        [FieldOffset(84088)] public BossDragonRippleLaserParam rippleLaser;
        [FieldOffset(84136)] public BossDragonRippleLaserRageParam rippleLaserRage;
        [FieldOffset(84192)] public BossDragonRippleLaserDummyParam rippleLaserDummy;
        [FieldOffset(84232)] public BossDragonWaveParam wave;
        [FieldOffset(84272)] public BossDragonLaserParam laserWinder;
        [FieldOffset(84308)] public BossDragonLaserParam randomLaser;
        [FieldOffset(84344)] public BossDragonCounterLaserParam counterLaser;
        [FieldOffset(84368)] public BossDragonRingSupplyParam ringSupply;
        [FieldOffset(84432)] public float damageRates__arr0;
        [FieldOffset(84436)] public float damageRates__arr1;
        [FieldOffset(84440)] public float damageRates__arr2;
        [FieldOffset(84444)] public float damageRates__arr3;
        [FieldOffset(84448)] public BossDragonLayoutParam layouts__arr0;
        [FieldOffset(84528)] public BossDragonLayoutParam layouts__arr1;
        [FieldOffset(84608)] public BossDragonLayoutParam layouts__arr2;
        [FieldOffset(84688)] public BossDragonLayoutParam layouts__arr3;
        [FieldOffset(84768)] public BossDragonLayoutParam layouts__arr4;
        [FieldOffset(84848)] public BossDragonLayoutParam layouts__arr5;
        [FieldOffset(84928)] public BossDragonLayoutParam layouts__arr6;
        [FieldOffset(85008)] public BossDragonLayoutParam layouts__arr7;
        [FieldOffset(85088)] public BossDragonLayoutParam layouts__arr8;
        [FieldOffset(85168)] public BossDragonLayoutParam layouts__arr9;
        [FieldOffset(85248)] public BossDragonLayoutParam layouts__arr10;
        [FieldOffset(85328)] public BossDragonLayoutParam layouts__arr11;
        [FieldOffset(85408)] public BossDragonLayoutParam layouts__arr12;
        [FieldOffset(85488)] public BossDragonLayoutParam layouts__arr13;
        [FieldOffset(85568)] public BossDragonLayoutParam layouts__arr14;
        [FieldOffset(85648)] public BossDragonLayoutParam layouts__arr15;
        [FieldOffset(85728)] public BossDragonLayoutParam layouts__arr16;
        [FieldOffset(85808)] public BossDragonLayoutParam layouts__arr17;
        [FieldOffset(85888)] public BossDragonLayoutParam layouts__arr18;
        [FieldOffset(85968)] public BossDragonLayoutParam layouts__arr19;
        [FieldOffset(86048)] public BossDragonLayoutParam layouts__arr20;
        [FieldOffset(86128)] public BossDragonLayoutParam layouts__arr21;
        [FieldOffset(86208)] public BossDragonLayoutParam layouts__arr22;
        [FieldOffset(86288)] public BossDragonLayoutParam layouts__arr23;
        [FieldOffset(86368)] public BossDragonLayoutParam layouts__arr24;
        [FieldOffset(86448)] public BossDragonLayoutParam layouts__arr25;
        [FieldOffset(86528)] public BossDragonLayoutParam layouts__arr26;
        [FieldOffset(86608)] public BossDragonLayoutParam layouts__arr27;
        [FieldOffset(86688)] public BossDragonLayoutParam layouts__arr28;
        [FieldOffset(86768)] public BossDragonLayoutParam layouts__arr29;
        [FieldOffset(86848)] public BossDragonLayoutParam layouts__arr30;
        [FieldOffset(86928)] public BossDragonLayoutParam layouts__arr31;
        [FieldOffset(87008)] public BossDragonLayoutParam layouts__arr32;
        [FieldOffset(87088)] public BossDragonLayoutParam layouts__arr33;
        [FieldOffset(87168)] public BossDragonLayoutParam layouts__arr34;
        [FieldOffset(87248)] public BossDragonLayoutParam layouts__arr35;
        [FieldOffset(87328)] public BossDragonLayoutParam layouts__arr36;
        [FieldOffset(87408)] public BossDragonLayoutParam layouts__arr37;
        [FieldOffset(87488)] public BossDragonLayoutParam layouts__arr38;
        [FieldOffset(87568)] public BossDragonLayoutParam layouts__arr39;
        [FieldOffset(87648)] public BossDragonLayoutParam layouts__arr40;
        [FieldOffset(87728)] public BossDragonLayoutParam layouts__arr41;
        [FieldOffset(87808)] public BossDragonLayoutParam layouts__arr42;
        [FieldOffset(87888)] public BossDragonLayoutParam layouts__arr43;
        [FieldOffset(87968)] public BossDragonLayoutParam layouts__arr44;
        [FieldOffset(88048)] public BossDragonLayoutParam layouts__arr45;
        [FieldOffset(88128)] public BossDragonCameraParam cameras__arr0;
        [FieldOffset(88240)] public BossDragonCameraParam cameras__arr1;
        [FieldOffset(88352)] public BossDragonCameraParam cameras__arr2;
        [FieldOffset(88464)] public BossDragonCameraParam cameras__arr3;
        [FieldOffset(88576)] public BossDragonCameraParam cameras__arr4;
        [FieldOffset(88688)] public BossDragonCameraParam cameras__arr5;
        [FieldOffset(88800)] public BossDragonCameraParam cameras__arr6;
        [FieldOffset(88912)] public BossDragonCameraParam cameras__arr7;
        [FieldOffset(89024)] public BossDragonCameraParam cameras__arr8;
        [FieldOffset(89136)] public BossDragonCameraParam cameras__arr9;
        [FieldOffset(89248)] public BossDragonCameraParam cameras__arr10;
        [FieldOffset(89360)] public BossDragonCameraParam cameras__arr11;
        [FieldOffset(89472)] public BossDragonCameraParam cameras__arr12;
        [FieldOffset(89584)] public BossDragonCameraParam cameras__arr13;
        [FieldOffset(89696)] public BossDragonCameraParam cameras__arr14;
        [FieldOffset(89808)] public BossDragonCameraParam cameras__arr15;
        [FieldOffset(89920)] public BossDragonCameraParam cameras__arr16;
        [FieldOffset(90032)] public BossDragonCameraParam cameras__arr17;
        [FieldOffset(90144)] public BossDragonCameraParam cameras__arr18;
        [FieldOffset(90256)] public BossDragonCameraParam cameras__arr19;
        [FieldOffset(90368)] public BossDragonCameraParam cameras__arr20;
        [FieldOffset(90480)] public BossDragonCameraParam cameras__arr21;
        [FieldOffset(90592)] public BossDragonCameraParam cameras__arr22;
        [FieldOffset(90704)] public BossDragonCameraParam cameras__arr23;
        [FieldOffset(90816)] public BossDragonCameraParam cameras__arr24;
        [FieldOffset(90928)] public BossDragonCameraParam cameras__arr25;
        [FieldOffset(91040)] public BossDragonCameraParam cameras__arr26;
        [FieldOffset(91152)] public BossDragonCameraParam cameras__arr27;
        [FieldOffset(91264)] public BossDragonCameraParam cameras__arr28;
        [FieldOffset(91376)] public BossDragonCameraParam cameras__arr29;
        [FieldOffset(91488)] public BossDragonCameraParam cameras__arr30;
        [FieldOffset(91600)] public BossDragonCameraParam cameras__arr31;
        [FieldOffset(91712)] public BossDragonCameraParam cameras__arr32;
        [FieldOffset(91824)] public BossDragonCameraParam cameras__arr33;
        [FieldOffset(91936)] public BossDragonCameraParam cameras__arr34;
        [FieldOffset(92048)] public BossDragonCameraParam cameras__arr35;
        [FieldOffset(92160)] public BossDragonCameraParam cameras__arr36;
        [FieldOffset(92272)] public BossDragonCameraParam cameras__arr37;
        [FieldOffset(92384)] public BossDragonCameraParam cameras__arr38;
        [FieldOffset(92496)] public BossDragonCameraParam cameras__arr39;
        [FieldOffset(92608)] public BossDragonCameraParam cameras__arr40;
        [FieldOffset(92720)] public BossDragonCameraParam cameras__arr41;
        [FieldOffset(92832)] public BossDragonCameraParam cameras__arr42;
        [FieldOffset(92944)] public BossDragonCameraParam cameras__arr43;
        [FieldOffset(93056)] public BossDragonCameraParam cameras__arr44;
        [FieldOffset(93168)] public BossDragonCameraParam cameras__arr45;
        [FieldOffset(93280)] public BossDragonCameraParam cameras__arr46;
        [FieldOffset(93392)] public BossDragonMoveParam swapMove;
        [FieldOffset(93664)] public BossDragonRoadParam road;
        [FieldOffset(94368)] public BossDragonLaunchParam launch;
        [FieldOffset(94528)] public BossDragonQuickStepParam quickStep;
        [FieldOffset(94540)] public BossDragonChaseParam chase;
        [FieldOffset(94596)] public BossDragonMissileParam missile;
        [FieldOffset(95356)] public BossDragonSequence seq__arr0;
        [FieldOffset(95357)] public BossDragonSequence seq__arr1;
        [FieldOffset(95358)] public BossDragonSequence seq__arr2;
        [FieldOffset(95359)] public BossDragonSequence seq__arr3;
        [FieldOffset(95360)] public BossDragonSequence seq__arr4;
        [FieldOffset(95361)] public BossDragonSequence seq__arr5;
        [FieldOffset(95362)] public BossDragonSequence seq__arr6;
        [FieldOffset(95363)] public BossDragonSequence seq__arr7;
        [FieldOffset(95364)] public BossDragonSequence seq__arr8;
        [FieldOffset(95365)] public BossDragonSequence seq__arr9;
        [FieldOffset(95366)] public BossDragonSequence seq__arr10;
        [FieldOffset(95367)] public BossDragonSequence seq__arr11;
        [FieldOffset(95368)] public BossDragonSequence seq__arr12;
        [FieldOffset(95369)] public BossDragonSequence seq__arr13;
        [FieldOffset(95370)] public BossDragonSequence seq__arr14;
        [FieldOffset(95371)] public BossDragonSequence seq__arr15;
        [FieldOffset(95372)] public BossDragonSequence seq2__arr0;
        [FieldOffset(95373)] public BossDragonSequence seq2__arr1;
        [FieldOffset(95374)] public BossDragonSequence seq2__arr2;
        [FieldOffset(95375)] public BossDragonSequence seq2__arr3;
        [FieldOffset(95376)] public BossDragonSequence seq2__arr4;
        [FieldOffset(95377)] public BossDragonSequence seq2__arr5;
        [FieldOffset(95378)] public BossDragonSequence seq2__arr6;
        [FieldOffset(95379)] public BossDragonSequence seq2__arr7;
        [FieldOffset(95380)] public BossDragonSequence seq2__arr8;
        [FieldOffset(95381)] public BossDragonSequence seq2__arr9;
        [FieldOffset(95382)] public BossDragonSequence seq2__arr10;
        [FieldOffset(95383)] public BossDragonSequence seq2__arr11;
        [FieldOffset(95384)] public BossDragonSequence seq2__arr12;
        [FieldOffset(95385)] public BossDragonSequence seq2__arr13;
        [FieldOffset(95386)] public BossDragonSequence seq2__arr14;
        [FieldOffset(95387)] public BossDragonSequence seq2__arr15;
        [FieldOffset(95388)] public BossDragonInterruptParam interrupts__arr0;
        [FieldOffset(95396)] public BossDragonInterruptParam interrupts__arr1;
        [FieldOffset(95404)] public BossDragonInterruptParam interrupts__arr2;
        [FieldOffset(95412)] public BossDragonInterruptParam interrupts__arr3;
        [FieldOffset(95420)] public BossDragonInterruptParam interrupts__arr4;
        [FieldOffset(95428)] public BossDragonInterruptParam interrupts__arr5;
        [FieldOffset(95436)] public BossDragonInterruptParam interrupts__arr6;
        [FieldOffset(95444)] public BossDragonInterruptParam interrupts__arr7;
        [FieldOffset(95452)] public BossDragonCyloopBindParam cyloopBind;
        [FieldOffset(95468)] public BossDragonParryParam parry__arr0;
        [FieldOffset(95500)] public BossDragonParryParam parry__arr1;
        [FieldOffset(95532)] public BossDragonParryParam parry__arr2;
        [FieldOffset(95564)] public BossDragonParryParam parry__arr3;
        [FieldOffset(95596)] public BossDragonAttackSignParam attackSign;
        [FieldOffset(95620)] public BossDragonNotifierParam notifier;
    }

}