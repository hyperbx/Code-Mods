using System.Numerics;
using System.Runtime.InteropServices;

public class BossKnightConfigClass
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

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct KnightIdleConfig
    {
        [FieldOffset(0)] public float runSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct KnightClimbIdleConfig
    {
        [FieldOffset(0)] public float moveIntervalAfterSlam;
        [FieldOffset(4)] public float moveIntervalAfterMove;
        [FieldOffset(8)] public float moveIntervalAfterFall;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct KnightClimbMoveConfig
    {
        [FieldOffset(0)]  public float speedAvg;
        [FieldOffset(4)]  public float angle1Min;
        [FieldOffset(8)]  public float angle1Max;
        [FieldOffset(12)] public float angle2Min;
        [FieldOffset(16)] public float angle2Max;
        [FieldOffset(20)] public float move2WaitDuration;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct KnightClimbSlamLookupCameraConfig
    {
        [FieldOffset(0)]  public float duration;
        [FieldOffset(4)]  public float lockonDistance;
        [FieldOffset(8)]  public float unlockDistance;
        [FieldOffset(12)] public float distance;
        [FieldOffset(16)] public float minElevation;
        [FieldOffset(20)] public float maxElevation;
        [FieldOffset(24)] public float panningSuspensionK;
        [FieldOffset(28)] public float interiorPanningSuspensionK;
    }

    [StructLayout(LayoutKind.Explicit, Size = 52)]
    public struct KnightClimbSlamWaveConfig
    {
        [FieldOffset(0)]  public float interval;
        [FieldOffset(4)]  public uint generateNum;
        [FieldOffset(8)]  public float coolTime;
        [FieldOffset(12)] public float radius;
        [FieldOffset(16)] public float appearRadius;
        [FieldOffset(20)] public float keepRadius;
        [FieldOffset(24)] public float disappearRadius;
        [FieldOffset(28)] public float heightMin;
        [FieldOffset(32)] public float heightMax;
        [FieldOffset(36)] public float lifeTime;
        [FieldOffset(40)] public float modelScale;
        [FieldOffset(44)] public float modelDiameter;
        [FieldOffset(48)] public float effectDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct KnightClimbSlamConfig
    {
        [FieldOffset(0)]  public float rotateSpeedBeforeSlam;
        [FieldOffset(4)]  public float slamAnimSpeed;
        [FieldOffset(8)]  public float waitTimeAfterSlam;
        [FieldOffset(12)] public float liftUpStartAnimSpeed;
        [FieldOffset(16)] public float liftUpEndAnimSpeed;
        [FieldOffset(20)] public float liftUpStartAnimSpeedMiss;
        [FieldOffset(24)] public float liftUpEndAnimSpeedMiss;
        [FieldOffset(28)] public KnightClimbSlamLookupCameraConfig lookupCam;
        [FieldOffset(60)] public KnightClimbSlamWaveConfig wave;
    }

    public enum PlayerOffsetType : sbyte
    {
        PLAYER_OFFSET_NORMAL = 0,
        PLAYER_OFFSET_ABSOLUTE = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct KnightGrindCameraConfig
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

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct KnightGrindTrapConfig
    {
        [FieldOffset(0)] public int damage;
        [FieldOffset(4)] public bool blowOff;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct KnightGrindLaunchCameraConfig
    {
        [FieldOffset(0)]  public Vector3 lookAtOffset;
        [FieldOffset(16)] public Vector3 eyeOffset;
        [FieldOffset(32)] public float duration;
        [FieldOffset(36)] public float easeTimeBegin;
        [FieldOffset(40)] public float easeTimeEnd;
    }

    [StructLayout(LayoutKind.Explicit, Size = 144)]
    public struct KnightGrindLaunchConfig
    {
        [FieldOffset(0)]  public float outStrength;
        [FieldOffset(4)]  public float inStrength;
        [FieldOffset(8)]  public float outElev;
        [FieldOffset(12)] public float inElev;
        [FieldOffset(16)] public float speed;
        [FieldOffset(24)] public CString landFrameName;
        [FieldOffset(48)] public Vector3 landOffset;
        [FieldOffset(64)] public Vector3 landRayOffset;
        [FieldOffset(80)] public Vector3 landOffsetAfterRaycast;
        [FieldOffset(96)] public KnightGrindLaunchCameraConfig camera;
    }

    [StructLayout(LayoutKind.Explicit, Size = 240)]
    public struct KnightClimbGrindConfig
    {
        [FieldOffset(0)]  public KnightGrindCameraConfig camera;
        [FieldOffset(80)] public float playerSpeed;
        [FieldOffset(84)] public KnightGrindTrapConfig trap;
        [FieldOffset(96)] public KnightGrindLaunchConfig launch;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct KnightClimbTraceWaveConfig
    {
        [FieldOffset(0)]  public float traceSpeed;
        [FieldOffset(4)]  public float traceRotSpeed;
        [FieldOffset(8)]  public float traceLifeTime;
        [FieldOffset(12)] public float traceWidth;
        [FieldOffset(16)] public float traceHeight;
        [FieldOffset(20)] public float traceAppearDistance;
        [FieldOffset(24)] public float traceKeepDistance;
        [FieldOffset(28)] public float traceDisappearDistance;
        [FieldOffset(32)] public float traceModelScale;
        [FieldOffset(36)] public float traceModelDiameter;
        [FieldOffset(40)] public float traceModelInterval;
        [FieldOffset(44)] public float traceCollisionDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 464)]
    public struct KnightClimbConfig
    {
        [FieldOffset(0)]   public KnightClimbIdleConfig idle;
        [FieldOffset(12)]  public KnightClimbMoveConfig move;
        [FieldOffset(36)]  public KnightClimbSlamConfig slam;
        [FieldOffset(160)] public KnightClimbGrindConfig grind;
        [FieldOffset(400)] public float climbTimeLimit;
        [FieldOffset(404)] public KnightClimbTraceWaveConfig trace;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct KnightBattle1IdleConfig
    {
        [FieldOffset(0)] public float moveInterval;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct KnightBattle1MoveConfig
    {
        [FieldOffset(0)]  public float speedAvg;
        [FieldOffset(4)]  public float angle1Min;
        [FieldOffset(8)]  public float angle1Max;
        [FieldOffset(12)] public float angle2Min;
        [FieldOffset(16)] public float angle2Max;
        [FieldOffset(20)] public float move2WaitDuration;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct KnightBattle1GuardConfig
    {
        [FieldOffset(0)] public float guardStaggerMax;
        [FieldOffset(4)] public float damageStaggerMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 288)]
    public struct KnightShieldRideConfig
    {
        [FieldOffset(0)]   public float startDistance;
        [FieldOffset(4)]   public float startXOffset;
        [FieldOffset(8)]   public float startYOffset;
        [FieldOffset(12)]  public float startAngle;
        [FieldOffset(16)]  public float speed;
        [FieldOffset(20)]  public float turnAcc;
        [FieldOffset(24)]  public float turnSpeedMax;
        [FieldOffset(28)]  public float areaRadius;
        [FieldOffset(32)]  public float windPowerMin;
        [FieldOffset(36)]  public float windPowerMax;
        [FieldOffset(40)]  public float windTimeMin;
        [FieldOffset(44)]  public float windTimeMax;
        [FieldOffset(48)]  public float windInterval;
        [FieldOffset(52)]  public float camRideElevation;
        [FieldOffset(56)]  public float camRideDistance;
        [FieldOffset(64)]  public Vector3 camRideOffset;
        [FieldOffset(80)]  public float camCompeteElevation;
        [FieldOffset(84)]  public float camCompeteAzimuth;
        [FieldOffset(88)]  public float camCompeteDistance;
        [FieldOffset(92)]  public float camHitElevation;
        [FieldOffset(96)]  public float camHitAzimuth;
        [FieldOffset(100)] public float camHitDistance;
        [FieldOffset(104)] public float camShakeHitLoopMagnitude;
        [FieldOffset(108)] public int camShakeHitLoopFreq;
        [FieldOffset(112)] public float camShakeRejectLoopMagnitude;
        [FieldOffset(116)] public int camShakeRejectLoopFreq;
        [FieldOffset(120)] public byte missileNum;
        [FieldOffset(124)] public float missileInterval;
        [FieldOffset(128)] public float missileStartTime;
        [FieldOffset(132)] public float missileSpeed;
        [FieldOffset(136)] public float missileRotateSpeed;
        [FieldOffset(140)] public float missileMidPosDistance;
        [FieldOffset(144)] public float missileMidPosHeightOffset;
        [FieldOffset(148)] public float missileShotAngle;
        [FieldOffset(152)] public float missileShotStartWait;
        [FieldOffset(156)] public float missileRiseSpeed;
        [FieldOffset(160)] public float missileRiseTime;
        [FieldOffset(164)] public float missileHideTime;
        [FieldOffset(168)] public float missileAppearDistance;
        [FieldOffset(172)] public float missileAppearHeight;
        [FieldOffset(176)] public float missileAppearWidth;
        [FieldOffset(180)] public float missileLifeTime;
        [FieldOffset(184)] public float missileLifeTimeNoHit;
        [FieldOffset(188)] public float missileHitPower;
        [FieldOffset(192)] public float missileHitPowerRateDown;
        [FieldOffset(196)] public float missileHitPowerKeepTime;
        [FieldOffset(200)] public float missileHeightShakeMax;
        [FieldOffset(204)] public float missileHeightShakeMin;
        [FieldOffset(208)] public float missileWidthShake;
        [FieldOffset(212)] public float rejectCompeteDuration;
        [FieldOffset(216)] public float hitShaveDamageSum;
        [FieldOffset(220)] public uint hitShaveHitNum;
        [FieldOffset(224)] public float hitShaveHitInterval;
        [FieldOffset(228)] public float damageRatio;
        [FieldOffset(232)] public float staggerValue;
        [FieldOffset(236)] public float knockbackDistance;
        [FieldOffset(240)] public float durationAfterHit;
        [FieldOffset(244)] public uint missileHitPattern__arr0;
        [FieldOffset(248)] public uint missileHitPattern__arr1;
        [FieldOffset(252)] public uint missileHitPattern__arr2;
        [FieldOffset(256)] public uint missileHitPattern__arr3;
        [FieldOffset(260)] public uint missileHitPattern__arr4;
        [FieldOffset(264)] public uint missileHitPattern__arr5;
        [FieldOffset(268)] public uint missileHitPattern__arr6;
        [FieldOffset(272)] public uint missileHitPattern__arr7;
        [FieldOffset(276)] public uint missileHitPattern__arr8;
        [FieldOffset(280)] public uint missileHitPattern__arr9;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct KnightBattle1InterruptConfig
    {
        [FieldOffset(0)]  public float parriedDuration;
        [FieldOffset(4)]  public float slowRate;
        [FieldOffset(8)]  public float slowTime;
        [FieldOffset(12)] public float cameraOffset;
        [FieldOffset(16)] public float cameraFade;
    }

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct KnightBattle1CyFloat
    {
        [FieldOffset(0)]  public float height;
        [FieldOffset(4)]  public float riseDuration;
        [FieldOffset(8)]  public float floatDuration;
        [FieldOffset(12)] public float fallDuration;
        [FieldOffset(16)] public float cyFallDuration;
        [FieldOffset(20)] public float cyFallDelay;
        [FieldOffset(24)] public float downDuration;
        [FieldOffset(28)] public float enableDownCounterHPRatio;
        [FieldOffset(32)] public float enableGuardHPRatio;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct KnightThresholdRingSupplyParam
    {
        [FieldOffset(0)] public float hpRatio;
        [FieldOffset(4)] public int missileNum;
        [FieldOffset(8)] public float missileWaitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct KnightRageShieldAttackCameraConfig
    {
        [FieldOffset(0)] public float interpolateTimeBegin;
        [FieldOffset(4)] public float interpolateTimeEnd;
    }

    [StructLayout(LayoutKind.Explicit, Size = 144)]
    public struct KnightRageShieldConfig
    {
        [FieldOffset(0)]   public float modelScale;
        [FieldOffset(4)]   public float hitEffectScale;
        [FieldOffset(8)]   public float actionGuideOffsetX;
        [FieldOffset(12)]  public float actionGuideOffsetY;
        [FieldOffset(16)]  public float heightOffset;
        [FieldOffset(20)]  public float flySpeed;
        [FieldOffset(24)]  public float flyLineWidth;
        [FieldOffset(28)]  public float flyLineAfterHitWallLength;
        [FieldOffset(32)]  public float flyLineDuration;
        [FieldOffset(36)]  public float hitWallTargetingStart;
        [FieldOffset(40)]  public float hitWallTargetingAdd;
        [FieldOffset(44)]  public float hitWallTargetingSub;
        [FieldOffset(48)]  public float hitWallTargeting;
        [FieldOffset(52)]  public byte hitWallTargetingCycle;
        [FieldOffset(56)]  public float hitWallTargetAreaRadius;
        [FieldOffset(60)]  public float hitWallStopDuration;
        [FieldOffset(64)]  public float hitWallFlySpeed;
        [FieldOffset(68)]  public float hitWallAccStartTime;
        [FieldOffset(72)]  public float hitWallAccDuration;
        [FieldOffset(76)]  public float parryTargetRange;
        [FieldOffset(80)]  public float parryTargetAngVel;
        [FieldOffset(84)]  public float parryTargetTimeLimit;
        [FieldOffset(88)]  public float parryTargetLineWidth;
        [FieldOffset(92)]  public float parryTargetLineLength;
        [FieldOffset(96)]  public float parryFlySpeedStart;
        [FieldOffset(100)] public float parryFlySpeed;
        [FieldOffset(104)] public float parryAccStartTime;
        [FieldOffset(108)] public float parryAccDuration;
        [FieldOffset(112)] public float parryFlyLineWidth;
        [FieldOffset(116)] public float parryFlyLineDuration;
        [FieldOffset(120)] public float parryFlySuspendDuration;
        [FieldOffset(124)] public float parryFlySuspendEndDistance;
        [FieldOffset(128)] public KnightRageShieldAttackCameraConfig attackCamera;
        [FieldOffset(136)] public float damageRatio;
        [FieldOffset(140)] public float damageVelocity;
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct KnightRageOverlookCameraConfig
    {
        [FieldOffset(0)]  public float azimuth;
        [FieldOffset(4)]  public float elevation;
        [FieldOffset(8)]  public float distance;
        [FieldOffset(12)] public float zRoll;
        [FieldOffset(16)] public float fovy;
        [FieldOffset(32)] public Vector3 offset;
        [FieldOffset(48)] public float followPlayerRatio;
        [FieldOffset(52)] public float lookCenterRatio;
        [FieldOffset(56)] public float interpolateTimeBegin;
        [FieldOffset(60)] public float interpolateTimeEnd;
        [FieldOffset(64)] public float controlAngAcc;
        [FieldOffset(68)] public float controlAngVel;
    }

    [StructLayout(LayoutKind.Explicit, Size = 320)]
    public struct KnightBattle1Rage
    {
        [FieldOffset(0)]   public KnightRageShieldConfig shield;
        [FieldOffset(144)] public KnightRageOverlookCameraConfig normalCamera;
        [FieldOffset(224)] public KnightRageOverlookCameraConfig targetingCamera;
        [FieldOffset(304)] public float moveRestartAnimSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct KnightAerialCamera
    {
        [FieldOffset(0)]  public float downTime;
        [FieldOffset(4)]  public float downCutChangeTime__arr0;
        [FieldOffset(8)] public float downCutChangeTime__arr1;
        [FieldOffset(16)] public Vector3 downCamOffset;
        [FieldOffset(32)] public float riseTime;
        [FieldOffset(48)] public Vector3 riseCamOffset;
    }

    [StructLayout(LayoutKind.Explicit, Size = 848)]
    public struct KnightBattle1Config
    {
        [FieldOffset(0)]   public float closedAreaRadius;
        [FieldOffset(4)]   public KnightBattle1IdleConfig idle;
        [FieldOffset(8)]   public KnightBattle1MoveConfig move;
        [FieldOffset(32)]  public KnightBattle1GuardConfig guard;
        [FieldOffset(48)]  public KnightShieldRideConfig shieldRide;
        [FieldOffset(336)] public KnightBattle1InterruptConfig interrupt;
        [FieldOffset(356)] public float normalKnockbackDistance;
        [FieldOffset(360)] public KnightBattle1CyFloat cyFloat;
        [FieldOffset(396)] public KnightThresholdRingSupplyParam ringSupply__arr0;
        [FieldOffset(408)] public KnightThresholdRingSupplyParam ringSupply__arr1;
        [FieldOffset(420)] public KnightThresholdRingSupplyParam ringSupply__arr2;
        [FieldOffset(432)] public KnightBattle1Rage rage;
        [FieldOffset(752)] public float rageHPRatio;
        [FieldOffset(756)] public float atkSpecialHPRatio;
        [FieldOffset(768)] public KnightAerialCamera aerialCamera;
        [FieldOffset(832)] public float damageEventTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct KnightBattle2RunCamera
    {
        [FieldOffset(0)]  public float azimuth;
        [FieldOffset(4)]  public float elevation;
        [FieldOffset(8)]  public float distance;
        [FieldOffset(12)] public float zRoll;
        [FieldOffset(16)] public float fovy;
        [FieldOffset(32)] public Vector3 frameOffset;
    }

    [StructLayout(LayoutKind.Explicit, Size = 144)]
    public struct KnightBattle2RunConfig
    {
        [FieldOffset(0)]  public float speed;
        [FieldOffset(4)]  public float moveWidth;
        [FieldOffset(8)]  public float moveHeight;
        [FieldOffset(16)] public Vector3 playerOffset;
        [FieldOffset(32)] public Vector3 playerOffsetFar;
        [FieldOffset(48)] public Vector3 playerOffsetNear;
        [FieldOffset(64)] public Vector3 playerOffsetTackle;
        [FieldOffset(80)] public float attackInterval;
        [FieldOffset(84)] public float attackIntervalDelayOnHit;
        [FieldOffset(96)] public KnightBattle2RunCamera camera;
    }

    public enum XType : byte
    {
        Zero = 0,
        HitPosX = 1,
        Indivisual = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct KnightBattle2ShieldSplineNode
    {
        [FieldOffset(0)]  public bool enable;
        [FieldOffset(1)]  public XType xType;
        [FieldOffset(4)]  public float xIndivisual;
        [FieldOffset(8)]  public float y;
        [FieldOffset(12)] public float z;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct KnightBattle2ShieldUTurnCameraConfig
    {
        [FieldOffset(0)] public float duration;
        [FieldOffset(4)] public float interpolateTimeBegin;
        [FieldOffset(8)] public float interpolateTimeEnd;
    }

    [StructLayout(LayoutKind.Explicit, Size = 368)]
    public struct KnightBattle2ShieldConfig
    {
        [FieldOffset(0)]   public KnightBattle2ShieldSplineNode nodesStraight__arr0;
        [FieldOffset(16)] public KnightBattle2ShieldSplineNode nodesStraight__arr1;
        [FieldOffset(32)] public KnightBattle2ShieldSplineNode nodesStraight__arr2;
        [FieldOffset(48)] public KnightBattle2ShieldSplineNode nodesStraight__arr3;
        [FieldOffset(64)] public KnightBattle2ShieldSplineNode nodesStraight__arr4;
        [FieldOffset(80)] public KnightBattle2ShieldSplineNode nodesStraight__arr5;
        [FieldOffset(96)] public KnightBattle2ShieldSplineNode nodesStraight__arr6;
        [FieldOffset(112)] public KnightBattle2ShieldSplineNode nodesStraight__arr7;
        [FieldOffset(128)] public float stopPosRatioStraight;
        [FieldOffset(132)] public float stopDecStartPosRatioStraight;
        [FieldOffset(136)] public float stopAccEndPosRatioStraight;
        [FieldOffset(140)] public float stopDurationStraight;
        [FieldOffset(144)] public float speedStraight1;
        [FieldOffset(148)] public float speedStraight2;
        [FieldOffset(152)] public float hitPosXStraight;
        [FieldOffset(156)] public float uTurnEndPosStraight;
        [FieldOffset(160)] public float swordDelayStraight;
        [FieldOffset(164)] public KnightBattle2ShieldSplineNode nodesSlalom__arr0;
        [FieldOffset(180)] public KnightBattle2ShieldSplineNode nodesSlalom__arr1;
        [FieldOffset(196)] public KnightBattle2ShieldSplineNode nodesSlalom__arr2;
        [FieldOffset(212)] public KnightBattle2ShieldSplineNode nodesSlalom__arr3;
        [FieldOffset(228)] public KnightBattle2ShieldSplineNode nodesSlalom__arr4;
        [FieldOffset(244)] public KnightBattle2ShieldSplineNode nodesSlalom__arr5;
        [FieldOffset(260)] public KnightBattle2ShieldSplineNode nodesSlalom__arr6;
        [FieldOffset(276)] public KnightBattle2ShieldSplineNode nodesSlalom__arr7;
        [FieldOffset(292)] public float stopPosRatioSlalom;
        [FieldOffset(296)] public float stopDecStartPosRatioSlalom;
        [FieldOffset(300)] public float stopAccEndPosRatioSlalom;
        [FieldOffset(304)] public float stopDurationSlalom;
        [FieldOffset(308)] public float speedSlalom1;
        [FieldOffset(312)] public float speedSlalom2;
        [FieldOffset(316)] public float hitPosXSlalom;
        [FieldOffset(320)] public float uTurnEndPosSlalom;
        [FieldOffset(324)] public float magnitudeSlalomFar;
        [FieldOffset(328)] public float magnitudeSlalomNear;
        [FieldOffset(332)] public byte slalomNumMin;
        [FieldOffset(333)] public byte slalomNumMax;
        [FieldOffset(336)] public float slalomEndPosRatio;
        [FieldOffset(340)] public float swordDelaySlalom;
        [FieldOffset(344)] public float uTurnSpeedRatioDuringCam;
        [FieldOffset(348)] public float uTurnSpeedRatioAfterCam;
        [FieldOffset(352)] public KnightBattle2ShieldUTurnCameraConfig uTurnCamera;
        [FieldOffset(364)] public float attackLineWidth;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct KnightBattle2SwordConfig
    {
        [FieldOffset(0)] public float parriedDuration;
        [FieldOffset(4)] public float animSpeedOnDoubleAtkParried;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct KnightBattle2InterruptConfig
    {
        [FieldOffset(0)] public float parriedDuration;
    }

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct KnightBattle2CyFloat
    {
        [FieldOffset(0)]  public float height;
        [FieldOffset(4)]  public float riseDuration;
        [FieldOffset(8)]  public float floatDuration;
        [FieldOffset(12)] public float fallDuration;
        [FieldOffset(16)] public float cyFallDuration;
        [FieldOffset(20)] public float cyFallDelay;
        [FieldOffset(24)] public float downDuration;
        [FieldOffset(28)] public float enableDownCounterHPRatio;
        [FieldOffset(32)] public float enableGuardHPRatio;
    }

    [StructLayout(LayoutKind.Explicit, Size = 640)]
    public struct KnightBattle2Config
    {
        [FieldOffset(0)]   public KnightBattle2RunConfig run;
        [FieldOffset(144)] public KnightBattle2ShieldConfig shield;
        [FieldOffset(512)] public KnightBattle2SwordConfig sword;
        [FieldOffset(520)] public KnightBattle2InterruptConfig interrupt;
        [FieldOffset(524)] public float knockbackDistance;
        [FieldOffset(528)] public KnightBattle2CyFloat cyFloat;
        [FieldOffset(576)] public KnightAerialCamera aerialCamera;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct KnightSonicSpecialConfig
    {
        [FieldOffset(0)] public float damageRatio;
    }

    [StructLayout(LayoutKind.Explicit, Size = 320)]
    public struct KnightCyFloatSpearConfig
    {
        [FieldOffset(0)]   public Vector3 upOffset__arr0;
        [FieldOffset(16)] public Vector3 upOffset__arr1;
        [FieldOffset(32)] public Vector3 upOffset__arr2;
        [FieldOffset(48)] public Vector3 upOffset__arr3;
        [FieldOffset(64)] public Vector3 upOffset__arr4;
        [FieldOffset(80)] public Vector3 upOffset__arr5;
        [FieldOffset(96)] public Vector3 upOffset__arr6;
        [FieldOffset(112)] public Vector3 upOffset__arr7;
        [FieldOffset(128)] public Vector3 upRotationAngle__arr0;
        [FieldOffset(144)] public Vector3 upRotationAngle__arr1;
        [FieldOffset(160)] public Vector3 upRotationAngle__arr2;
        [FieldOffset(176)] public Vector3 upRotationAngle__arr3;
        [FieldOffset(192)] public Vector3 upRotationAngle__arr4;
        [FieldOffset(208)] public Vector3 upRotationAngle__arr5;
        [FieldOffset(224)] public Vector3 upRotationAngle__arr6;
        [FieldOffset(240)] public Vector3 upRotationAngle__arr7;
        [FieldOffset(256)] public float upMoveDistanceOffset;
        [FieldOffset(272)] public Vector3 downOffset;
        [FieldOffset(288)] public float downMoveDelay;
        [FieldOffset(292)] public float downMoveDistance__arr0;
        [FieldOffset(296)] public float downMoveDistance__arr1;
        [FieldOffset(300)] public float downMoveDistance__arr2;
        [FieldOffset(304)] public float downMoveDuration__arr0;
        [FieldOffset(308)] public float downMoveDuration__arr1;
        [FieldOffset(312)] public float downMoveDuration__arr2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct KnightAttackSignParam
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

    [StructLayout(LayoutKind.Explicit, Size = 9)]
    public struct BossKnightNotifierParam
    {
        [FieldOffset(0)] public EnemyPracticeNotifierConfig notifierConfigClimb;
        [FieldOffset(3)] public EnemyPracticeNotifierConfig notifierConfigBattle1;
        [FieldOffset(6)] public EnemyPracticeNotifierConfig notifierConfigBattle2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 78080)]
    public struct BossKnightConfig
    {
        [FieldOffset(0)]     public BossBaseConfig bossBaseConfig;
        [FieldOffset(75712)] public KnightIdleConfig idle;
        [FieldOffset(75728)] public KnightClimbConfig climb;
        [FieldOffset(76192)] public KnightBattle1Config battle1;
        [FieldOffset(77040)] public KnightBattle2Config battle2;
        [FieldOffset(77680)] public KnightSonicSpecialConfig sonicSpecial;
        [FieldOffset(77696)] public KnightCyFloatSpearConfig cyFloatSpear;
        [FieldOffset(78016)] public byte knockbackStaggerCount;
        [FieldOffset(78020)] public float thresholdDamageEffectHPRatio__arr0;
        [FieldOffset(78024)] public float thresholdDamageEffectHPRatio__arr1;
        [FieldOffset(78028)] public float thresholdDamageEffectHPRatio__arr2;
        [FieldOffset(78032)] public KnightAttackSignParam attackSign;
        [FieldOffset(78056)] public BossKnightNotifierParam notifier;
    }

}