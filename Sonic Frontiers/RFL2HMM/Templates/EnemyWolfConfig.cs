using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyWolfConfigClass
{
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
    public struct WolfMovementParam
    {
        [FieldOffset(0)]  public float rotateSpeedMin;
        [FieldOffset(4)]  public float rotateSpeedMax;
        [FieldOffset(8)]  public float rotateSpeedMaxSpeedMin;
        [FieldOffset(12)] public float rotateSpeedMinSpeedMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct WolfEyesightParam
    {
        [FieldOffset(0)] public float distance;
        [FieldOffset(4)] public float angle;
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

    public enum WolfVolumeShape : sbyte
    {
        SPHERE = 0,
        BOX = 1,
        CYLINDER = 2,
        CAPSULE = 3,
        NUM = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct WolfVolumeInfo
    {
        [FieldOffset(0)]  public Vector3 volumeSize;
        [FieldOffset(16)] public Vector3 volumeOffset;
        [FieldOffset(32)] public Vector3 volumeRotation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct WolfMappingPairInfo
    {
        [FieldOffset(0)]  public CString tagName;
        [FieldOffset(16)] public sbyte pieceNum;
        [FieldOffset(20)] public float pieceFuncFactor;
        [FieldOffset(24)] public WolfVolumeShape volumeShape;
        [FieldOffset(32)] public CString wolfNodeName;
        [FieldOffset(48)] public WolfVolumeInfo wolfVolume;
        [FieldOffset(96)] public bool effectActive;
        [FieldOffset(97)] public bool debugDraw;
        [FieldOffset(98)] public bool debugDrawVolumeAxis;
        [FieldOffset(99)] public bool debugDrawAxis;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3680)]
    public struct EnemyWolfCommonParam
    {
        [FieldOffset(0)]  public RingParameter ringParam;
        [FieldOffset(28)] public WolfMovementParam movement;
        [FieldOffset(44)] public WolfEyesightParam eyesight;
        [FieldOffset(52)] public float killWaitTime;
        [FieldOffset(56)] public float blockColliderRadius;
        [FieldOffset(60)] public float blockColliderHeight;
        [FieldOffset(64)] public float damageColliderRadius;
        [FieldOffset(68)] public float damageColliderHeight;
        [FieldOffset(72)] public float eyesightDistance;
        [FieldOffset(80)] public Vector3 cursorOffset;
        [FieldOffset(96)] public WolfMappingPairInfo mappingPairInfo__arr0;
        [FieldOffset(208)] public WolfMappingPairInfo mappingPairInfo__arr1;
        [FieldOffset(320)] public WolfMappingPairInfo mappingPairInfo__arr2;
        [FieldOffset(432)] public WolfMappingPairInfo mappingPairInfo__arr3;
        [FieldOffset(544)] public WolfMappingPairInfo mappingPairInfo__arr4;
        [FieldOffset(656)] public WolfMappingPairInfo mappingPairInfo__arr5;
        [FieldOffset(768)] public WolfMappingPairInfo mappingPairInfo__arr6;
        [FieldOffset(880)] public WolfMappingPairInfo mappingPairInfo__arr7;
        [FieldOffset(992)] public WolfMappingPairInfo mappingPairInfo__arr8;
        [FieldOffset(1104)] public WolfMappingPairInfo mappingPairInfo__arr9;
        [FieldOffset(1216)] public WolfMappingPairInfo mappingPairInfo__arr10;
        [FieldOffset(1328)] public WolfMappingPairInfo mappingPairInfo__arr11;
        [FieldOffset(1440)] public WolfMappingPairInfo mappingPairInfo__arr12;
        [FieldOffset(1552)] public WolfMappingPairInfo mappingPairInfo__arr13;
        [FieldOffset(1664)] public WolfMappingPairInfo mappingPairInfo__arr14;
        [FieldOffset(1776)] public WolfMappingPairInfo mappingPairInfo__arr15;
        [FieldOffset(1888)] public WolfMappingPairInfo mappingPairInfo__arr16;
        [FieldOffset(2000)] public WolfMappingPairInfo mappingPairInfo__arr17;
        [FieldOffset(2112)] public WolfMappingPairInfo mappingPairInfo__arr18;
        [FieldOffset(2224)] public WolfMappingPairInfo mappingPairInfo__arr19;
        [FieldOffset(2336)] public WolfMappingPairInfo mappingPairInfo__arr20;
        [FieldOffset(2448)] public WolfMappingPairInfo mappingPairInfo__arr21;
        [FieldOffset(2560)] public WolfMappingPairInfo mappingPairInfo__arr22;
        [FieldOffset(2672)] public WolfMappingPairInfo mappingPairInfo__arr23;
        [FieldOffset(2784)] public WolfMappingPairInfo mappingPairInfo__arr24;
        [FieldOffset(2896)] public WolfMappingPairInfo mappingPairInfo__arr25;
        [FieldOffset(3008)] public WolfMappingPairInfo mappingPairInfo__arr26;
        [FieldOffset(3120)] public WolfMappingPairInfo mappingPairInfo__arr27;
        [FieldOffset(3232)] public WolfMappingPairInfo mappingPairInfo__arr28;
        [FieldOffset(3344)] public WolfMappingPairInfo mappingPairInfo__arr29;
        [FieldOffset(3456)] public WolfMappingPairInfo mappingPairInfo__arr30;
        [FieldOffset(3568)] public WolfMappingPairInfo mappingPairInfo__arr31;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct EnemyWolfCommonLevelParam
    {
        [FieldOffset(0)]  public int maxHealthPoint;
        [FieldOffset(4)]  public float attackRate;
        [FieldOffset(8)]  public ushort expItemNum;
        [FieldOffset(10)] public ushort exp;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct EnemyWolfLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public EnemyWolfCommonLevelParam common;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct EnemyWolfLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3792)]
    public struct EnemyWolfConfig
    {
        [FieldOffset(0)]    public EnemyWolfCommonParam commonParam;
        [FieldOffset(3680)] public EnemyWolfLevelParam levelParams__arr0;
        [FieldOffset(3696)] public EnemyWolfLevelParam levelParams__arr1;
        [FieldOffset(3712)] public EnemyWolfLevelParam levelParams__arr2;
        [FieldOffset(3728)] public EnemyWolfLevelParam levelParams__arr3;
        [FieldOffset(3744)] public EnemyWolfLevelParam levelParams__arr4;
        [FieldOffset(3760)] public EnemyWolfLevelBand levelBand__arr0;
        [FieldOffset(3764)] public EnemyWolfLevelBand levelBand__arr1;
        [FieldOffset(3768)] public EnemyWolfLevelBand levelBand__arr2;
        [FieldOffset(3772)] public EnemyWolfLevelBand levelBand__arr3;
        [FieldOffset(3776)] public EnemyWolfLevelBand levelBand__arr4;
    }

}