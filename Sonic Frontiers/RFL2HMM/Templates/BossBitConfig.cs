using System.Numerics;
using System.Runtime.InteropServices;

public class BossBitConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct LargeBitLaserParameter
    {
        [FieldOffset(0)] public float rangeMin;
        [FieldOffset(4)] public float rangeMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 44)]
    public struct SmallBitLaserBulletParameter
    {
        [FieldOffset(0)]  public float bulletRadius;
        [FieldOffset(4)]  public float bulletMoveLimitDistance;
        [FieldOffset(8)]  public float bitHp;
        [FieldOffset(12)] public float rotDamageAngleSpeed;
        [FieldOffset(16)] public float rotDamageSize;
        [FieldOffset(20)] public float hitDamageNotAttackTime;
        [FieldOffset(24)] public float blowoffSpeed;
        [FieldOffset(28)] public float outOfControlTime;
        [FieldOffset(32)] public float keepVelocity;
        [FieldOffset(36)] public float muzzleEffectMinTime;
        [FieldOffset(40)] public byte dropRingNum;
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

    public enum BulletType : byte
    {
        Normal = 0,
        Normal2 = 1,
        Laser = 2,
        Homing = 3
    }

    public enum RotType : byte
    {
        Rotation = 0,
        RoundTrip = 1,
        Aim = 2,
        Fix = 3
    }

    public enum CameraId : byte
    {
        Invalid = 0,
        Rotate = 1,
        Trace = 2,
        Sub = 3,
        Num = 4
    }

    public enum FormationId : byte
    {
        Default = 0,
        FanShaped = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 100)]
    public struct SmallBitAttackPatternParameter
    {
        [FieldOffset(0)]  public bool isParry;
        [FieldOffset(4)]  public float time;
        [FieldOffset(8)]  public float angleSpeed;
        [FieldOffset(12)] public BulletType bulletType;
        [FieldOffset(13)] public RotType rotType;
        [FieldOffset(16)] public float rotAngle;
        [FieldOffset(20)] public float phaseRotTime;
        [FieldOffset(24)] public uint shootNum;
        [FieldOffset(28)] public float shootSpeed;
        [FieldOffset(32)] public float addShootSpeed;
        [FieldOffset(36)] public float shootAccel;
        [FieldOffset(40)] public float shootAccelMax;
        [FieldOffset(44)] public float shootAccelDelay;
        [FieldOffset(48)] public byte wayNum;
        [FieldOffset(52)] public float wayAngle;
        [FieldOffset(56)] public float shootTime;
        [FieldOffset(60)] public float phaseShootTime;
        [FieldOffset(64)] public uint periodShootCool;
        [FieldOffset(68)] public float periodShootCoolTime;
        [FieldOffset(72)] public float homingAccuracy;
        [FieldOffset(76)] public float homingDelay;
        [FieldOffset(80)] public float homingLimitAngle;
        [FieldOffset(84)] public bool isHomingLowFly;
        [FieldOffset(85)] public CameraId overlookingId;
        [FieldOffset(88)] public float waveRotationSpeed;
        [FieldOffset(92)] public float flyMoveSpeed;
        [FieldOffset(96)] public FormationId formationId;
    }

    [StructLayout(LayoutKind.Explicit, Size = 120)]
    public struct SmallBitSetPatternParameter
    {
        [FieldOffset(0)]  public CString text;
        [FieldOffset(16)] public SmallBitAttackPatternParameter param;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct SmallBitFormationFanShaped
    {
        [FieldOffset(0)]  public float distance;
        [FieldOffset(4)]  public float height;
        [FieldOffset(8)]  public float radius;
        [FieldOffset(12)] public float angleMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct SmallBitFormationParameter
    {
        [FieldOffset(0)]  public float changeTime;
        [FieldOffset(4)]  public float changeDelay;
        [FieldOffset(8)]  public float changeOffsetHeight;
        [FieldOffset(12)] public SmallBitFormationFanShaped fanShaped;
    }

    [StructLayout(LayoutKind.Explicit, Size = 7768)]
    public struct BossBitConfig
    {
        [FieldOffset(0)]    public LargeBitLaserParameter largeBitLaserParam;
        [FieldOffset(8)]    public SmallBitLaserBulletParameter smallBitLaserParam;
        [FieldOffset(56)]   public SmallBitSetPatternParameter smallBitPatternDatas__arr0;
        [FieldOffset(176)] public SmallBitSetPatternParameter smallBitPatternDatas__arr1;
        [FieldOffset(296)] public SmallBitSetPatternParameter smallBitPatternDatas__arr2;
        [FieldOffset(416)] public SmallBitSetPatternParameter smallBitPatternDatas__arr3;
        [FieldOffset(536)] public SmallBitSetPatternParameter smallBitPatternDatas__arr4;
        [FieldOffset(656)] public SmallBitSetPatternParameter smallBitPatternDatas__arr5;
        [FieldOffset(776)] public SmallBitSetPatternParameter smallBitPatternDatas__arr6;
        [FieldOffset(896)] public SmallBitSetPatternParameter smallBitPatternDatas__arr7;
        [FieldOffset(1016)] public SmallBitSetPatternParameter smallBitPatternDatas__arr8;
        [FieldOffset(1136)] public SmallBitSetPatternParameter smallBitPatternDatas__arr9;
        [FieldOffset(1256)] public SmallBitSetPatternParameter smallBitPatternDatas__arr10;
        [FieldOffset(1376)] public SmallBitSetPatternParameter smallBitPatternDatas__arr11;
        [FieldOffset(1496)] public SmallBitSetPatternParameter smallBitPatternDatas__arr12;
        [FieldOffset(1616)] public SmallBitSetPatternParameter smallBitPatternDatas__arr13;
        [FieldOffset(1736)] public SmallBitSetPatternParameter smallBitPatternDatas__arr14;
        [FieldOffset(1856)] public SmallBitSetPatternParameter smallBitPatternDatas__arr15;
        [FieldOffset(1976)] public SmallBitSetPatternParameter smallBitPatternDatas__arr16;
        [FieldOffset(2096)] public SmallBitSetPatternParameter smallBitPatternDatas__arr17;
        [FieldOffset(2216)] public SmallBitSetPatternParameter smallBitPatternDatas__arr18;
        [FieldOffset(2336)] public SmallBitSetPatternParameter smallBitPatternDatas__arr19;
        [FieldOffset(2456)] public SmallBitSetPatternParameter smallBitPatternDatas__arr20;
        [FieldOffset(2576)] public SmallBitSetPatternParameter smallBitPatternDatas__arr21;
        [FieldOffset(2696)] public SmallBitSetPatternParameter smallBitPatternDatas__arr22;
        [FieldOffset(2816)] public SmallBitSetPatternParameter smallBitPatternDatas__arr23;
        [FieldOffset(2936)] public SmallBitSetPatternParameter smallBitPatternDatas__arr24;
        [FieldOffset(3056)] public SmallBitSetPatternParameter smallBitPatternDatas__arr25;
        [FieldOffset(3176)] public SmallBitSetPatternParameter smallBitPatternDatas__arr26;
        [FieldOffset(3296)] public SmallBitSetPatternParameter smallBitPatternDatas__arr27;
        [FieldOffset(3416)] public SmallBitSetPatternParameter smallBitPatternDatas__arr28;
        [FieldOffset(3536)] public SmallBitSetPatternParameter smallBitPatternDatas__arr29;
        [FieldOffset(3656)] public SmallBitSetPatternParameter smallBitPatternDatas__arr30;
        [FieldOffset(3776)] public SmallBitSetPatternParameter smallBitPatternDatas__arr31;
        [FieldOffset(3896)] public SmallBitSetPatternParameter smallBitPatternDatas__arr32;
        [FieldOffset(4016)] public SmallBitSetPatternParameter smallBitPatternDatas__arr33;
        [FieldOffset(4136)] public SmallBitSetPatternParameter smallBitPatternDatas__arr34;
        [FieldOffset(4256)] public SmallBitSetPatternParameter smallBitPatternDatas__arr35;
        [FieldOffset(4376)] public SmallBitSetPatternParameter smallBitPatternDatas__arr36;
        [FieldOffset(4496)] public SmallBitSetPatternParameter smallBitPatternDatas__arr37;
        [FieldOffset(4616)] public SmallBitSetPatternParameter smallBitPatternDatas__arr38;
        [FieldOffset(4736)] public SmallBitSetPatternParameter smallBitPatternDatas__arr39;
        [FieldOffset(4856)] public SmallBitSetPatternParameter smallBitPatternDatas__arr40;
        [FieldOffset(4976)] public SmallBitSetPatternParameter smallBitPatternDatas__arr41;
        [FieldOffset(5096)] public SmallBitSetPatternParameter smallBitPatternDatas__arr42;
        [FieldOffset(5216)] public SmallBitSetPatternParameter smallBitPatternDatas__arr43;
        [FieldOffset(5336)] public SmallBitSetPatternParameter smallBitPatternDatas__arr44;
        [FieldOffset(5456)] public SmallBitSetPatternParameter smallBitPatternDatas__arr45;
        [FieldOffset(5576)] public SmallBitSetPatternParameter smallBitPatternDatas__arr46;
        [FieldOffset(5696)] public SmallBitSetPatternParameter smallBitPatternDatas__arr47;
        [FieldOffset(5816)] public SmallBitSetPatternParameter smallBitPatternDatas__arr48;
        [FieldOffset(5936)] public SmallBitSetPatternParameter smallBitPatternDatas__arr49;
        [FieldOffset(6056)] public SmallBitSetPatternParameter smallBitPatternDatas__arr50;
        [FieldOffset(6176)] public SmallBitSetPatternParameter smallBitPatternDatas__arr51;
        [FieldOffset(6296)] public SmallBitSetPatternParameter smallBitPatternDatas__arr52;
        [FieldOffset(6416)] public SmallBitSetPatternParameter smallBitPatternDatas__arr53;
        [FieldOffset(6536)] public SmallBitSetPatternParameter smallBitPatternDatas__arr54;
        [FieldOffset(6656)] public SmallBitSetPatternParameter smallBitPatternDatas__arr55;
        [FieldOffset(6776)] public SmallBitSetPatternParameter smallBitPatternDatas__arr56;
        [FieldOffset(6896)] public SmallBitSetPatternParameter smallBitPatternDatas__arr57;
        [FieldOffset(7016)] public SmallBitSetPatternParameter smallBitPatternDatas__arr58;
        [FieldOffset(7136)] public SmallBitSetPatternParameter smallBitPatternDatas__arr59;
        [FieldOffset(7256)] public SmallBitSetPatternParameter smallBitPatternDatas__arr60;
        [FieldOffset(7376)] public SmallBitSetPatternParameter smallBitPatternDatas__arr61;
        [FieldOffset(7496)] public SmallBitSetPatternParameter smallBitPatternDatas__arr62;
        [FieldOffset(7616)] public SmallBitSetPatternParameter smallBitPatternDatas__arr63;
        [FieldOffset(7736)] public SmallBitFormationParameter smallBitFormation;
    }

}