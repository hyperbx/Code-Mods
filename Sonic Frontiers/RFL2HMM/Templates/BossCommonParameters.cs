using System.Numerics;
using System.Runtime.InteropServices;

public class BossCommonParametersClass
{
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

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct BossResourceInfo
    {
        [FieldOffset(0)]  public CString modelName;
        [FieldOffset(16)] public CString animName;
        [FieldOffset(32)] public Vector3 scale;
        [FieldOffset(48)] public CString stageName;
        [FieldOffset(64)] public Vector3 stagePos;
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct HoldPoint
    {
        [FieldOffset(0)]  public CString nodeName;
        [FieldOffset(16)] public Vector3 offset;
        [FieldOffset(32)] public Vector3 rot;
        [FieldOffset(48)] public CString tagName;
        [FieldOffset(64)] public int nextPointId;
    }

    [StructLayout(LayoutKind.Explicit, Size = 10240)]
    public struct HoldPointParameter
    {
        [FieldOffset(0)] public HoldPoint holdPoints__arr0;
        [FieldOffset(80)] public HoldPoint holdPoints__arr1;
        [FieldOffset(160)] public HoldPoint holdPoints__arr2;
        [FieldOffset(240)] public HoldPoint holdPoints__arr3;
        [FieldOffset(320)] public HoldPoint holdPoints__arr4;
        [FieldOffset(400)] public HoldPoint holdPoints__arr5;
        [FieldOffset(480)] public HoldPoint holdPoints__arr6;
        [FieldOffset(560)] public HoldPoint holdPoints__arr7;
        [FieldOffset(640)] public HoldPoint holdPoints__arr8;
        [FieldOffset(720)] public HoldPoint holdPoints__arr9;
        [FieldOffset(800)] public HoldPoint holdPoints__arr10;
        [FieldOffset(880)] public HoldPoint holdPoints__arr11;
        [FieldOffset(960)] public HoldPoint holdPoints__arr12;
        [FieldOffset(1040)] public HoldPoint holdPoints__arr13;
        [FieldOffset(1120)] public HoldPoint holdPoints__arr14;
        [FieldOffset(1200)] public HoldPoint holdPoints__arr15;
        [FieldOffset(1280)] public HoldPoint holdPoints__arr16;
        [FieldOffset(1360)] public HoldPoint holdPoints__arr17;
        [FieldOffset(1440)] public HoldPoint holdPoints__arr18;
        [FieldOffset(1520)] public HoldPoint holdPoints__arr19;
        [FieldOffset(1600)] public HoldPoint holdPoints__arr20;
        [FieldOffset(1680)] public HoldPoint holdPoints__arr21;
        [FieldOffset(1760)] public HoldPoint holdPoints__arr22;
        [FieldOffset(1840)] public HoldPoint holdPoints__arr23;
        [FieldOffset(1920)] public HoldPoint holdPoints__arr24;
        [FieldOffset(2000)] public HoldPoint holdPoints__arr25;
        [FieldOffset(2080)] public HoldPoint holdPoints__arr26;
        [FieldOffset(2160)] public HoldPoint holdPoints__arr27;
        [FieldOffset(2240)] public HoldPoint holdPoints__arr28;
        [FieldOffset(2320)] public HoldPoint holdPoints__arr29;
        [FieldOffset(2400)] public HoldPoint holdPoints__arr30;
        [FieldOffset(2480)] public HoldPoint holdPoints__arr31;
        [FieldOffset(2560)] public HoldPoint holdPoints__arr32;
        [FieldOffset(2640)] public HoldPoint holdPoints__arr33;
        [FieldOffset(2720)] public HoldPoint holdPoints__arr34;
        [FieldOffset(2800)] public HoldPoint holdPoints__arr35;
        [FieldOffset(2880)] public HoldPoint holdPoints__arr36;
        [FieldOffset(2960)] public HoldPoint holdPoints__arr37;
        [FieldOffset(3040)] public HoldPoint holdPoints__arr38;
        [FieldOffset(3120)] public HoldPoint holdPoints__arr39;
        [FieldOffset(3200)] public HoldPoint holdPoints__arr40;
        [FieldOffset(3280)] public HoldPoint holdPoints__arr41;
        [FieldOffset(3360)] public HoldPoint holdPoints__arr42;
        [FieldOffset(3440)] public HoldPoint holdPoints__arr43;
        [FieldOffset(3520)] public HoldPoint holdPoints__arr44;
        [FieldOffset(3600)] public HoldPoint holdPoints__arr45;
        [FieldOffset(3680)] public HoldPoint holdPoints__arr46;
        [FieldOffset(3760)] public HoldPoint holdPoints__arr47;
        [FieldOffset(3840)] public HoldPoint holdPoints__arr48;
        [FieldOffset(3920)] public HoldPoint holdPoints__arr49;
        [FieldOffset(4000)] public HoldPoint holdPoints__arr50;
        [FieldOffset(4080)] public HoldPoint holdPoints__arr51;
        [FieldOffset(4160)] public HoldPoint holdPoints__arr52;
        [FieldOffset(4240)] public HoldPoint holdPoints__arr53;
        [FieldOffset(4320)] public HoldPoint holdPoints__arr54;
        [FieldOffset(4400)] public HoldPoint holdPoints__arr55;
        [FieldOffset(4480)] public HoldPoint holdPoints__arr56;
        [FieldOffset(4560)] public HoldPoint holdPoints__arr57;
        [FieldOffset(4640)] public HoldPoint holdPoints__arr58;
        [FieldOffset(4720)] public HoldPoint holdPoints__arr59;
        [FieldOffset(4800)] public HoldPoint holdPoints__arr60;
        [FieldOffset(4880)] public HoldPoint holdPoints__arr61;
        [FieldOffset(4960)] public HoldPoint holdPoints__arr62;
        [FieldOffset(5040)] public HoldPoint holdPoints__arr63;
        [FieldOffset(5120)] public HoldPoint holdPoints__arr64;
        [FieldOffset(5200)] public HoldPoint holdPoints__arr65;
        [FieldOffset(5280)] public HoldPoint holdPoints__arr66;
        [FieldOffset(5360)] public HoldPoint holdPoints__arr67;
        [FieldOffset(5440)] public HoldPoint holdPoints__arr68;
        [FieldOffset(5520)] public HoldPoint holdPoints__arr69;
        [FieldOffset(5600)] public HoldPoint holdPoints__arr70;
        [FieldOffset(5680)] public HoldPoint holdPoints__arr71;
        [FieldOffset(5760)] public HoldPoint holdPoints__arr72;
        [FieldOffset(5840)] public HoldPoint holdPoints__arr73;
        [FieldOffset(5920)] public HoldPoint holdPoints__arr74;
        [FieldOffset(6000)] public HoldPoint holdPoints__arr75;
        [FieldOffset(6080)] public HoldPoint holdPoints__arr76;
        [FieldOffset(6160)] public HoldPoint holdPoints__arr77;
        [FieldOffset(6240)] public HoldPoint holdPoints__arr78;
        [FieldOffset(6320)] public HoldPoint holdPoints__arr79;
        [FieldOffset(6400)] public HoldPoint holdPoints__arr80;
        [FieldOffset(6480)] public HoldPoint holdPoints__arr81;
        [FieldOffset(6560)] public HoldPoint holdPoints__arr82;
        [FieldOffset(6640)] public HoldPoint holdPoints__arr83;
        [FieldOffset(6720)] public HoldPoint holdPoints__arr84;
        [FieldOffset(6800)] public HoldPoint holdPoints__arr85;
        [FieldOffset(6880)] public HoldPoint holdPoints__arr86;
        [FieldOffset(6960)] public HoldPoint holdPoints__arr87;
        [FieldOffset(7040)] public HoldPoint holdPoints__arr88;
        [FieldOffset(7120)] public HoldPoint holdPoints__arr89;
        [FieldOffset(7200)] public HoldPoint holdPoints__arr90;
        [FieldOffset(7280)] public HoldPoint holdPoints__arr91;
        [FieldOffset(7360)] public HoldPoint holdPoints__arr92;
        [FieldOffset(7440)] public HoldPoint holdPoints__arr93;
        [FieldOffset(7520)] public HoldPoint holdPoints__arr94;
        [FieldOffset(7600)] public HoldPoint holdPoints__arr95;
        [FieldOffset(7680)] public HoldPoint holdPoints__arr96;
        [FieldOffset(7760)] public HoldPoint holdPoints__arr97;
        [FieldOffset(7840)] public HoldPoint holdPoints__arr98;
        [FieldOffset(7920)] public HoldPoint holdPoints__arr99;
        [FieldOffset(8000)] public HoldPoint holdPoints__arr100;
        [FieldOffset(8080)] public HoldPoint holdPoints__arr101;
        [FieldOffset(8160)] public HoldPoint holdPoints__arr102;
        [FieldOffset(8240)] public HoldPoint holdPoints__arr103;
        [FieldOffset(8320)] public HoldPoint holdPoints__arr104;
        [FieldOffset(8400)] public HoldPoint holdPoints__arr105;
        [FieldOffset(8480)] public HoldPoint holdPoints__arr106;
        [FieldOffset(8560)] public HoldPoint holdPoints__arr107;
        [FieldOffset(8640)] public HoldPoint holdPoints__arr108;
        [FieldOffset(8720)] public HoldPoint holdPoints__arr109;
        [FieldOffset(8800)] public HoldPoint holdPoints__arr110;
        [FieldOffset(8880)] public HoldPoint holdPoints__arr111;
        [FieldOffset(8960)] public HoldPoint holdPoints__arr112;
        [FieldOffset(9040)] public HoldPoint holdPoints__arr113;
        [FieldOffset(9120)] public HoldPoint holdPoints__arr114;
        [FieldOffset(9200)] public HoldPoint holdPoints__arr115;
        [FieldOffset(9280)] public HoldPoint holdPoints__arr116;
        [FieldOffset(9360)] public HoldPoint holdPoints__arr117;
        [FieldOffset(9440)] public HoldPoint holdPoints__arr118;
        [FieldOffset(9520)] public HoldPoint holdPoints__arr119;
        [FieldOffset(9600)] public HoldPoint holdPoints__arr120;
        [FieldOffset(9680)] public HoldPoint holdPoints__arr121;
        [FieldOffset(9760)] public HoldPoint holdPoints__arr122;
        [FieldOffset(9840)] public HoldPoint holdPoints__arr123;
        [FieldOffset(9920)] public HoldPoint holdPoints__arr124;
        [FieldOffset(10000)] public HoldPoint holdPoints__arr125;
        [FieldOffset(10080)] public HoldPoint holdPoints__arr126;
        [FieldOffset(10160)] public HoldPoint holdPoints__arr127;
    }

    public enum Shape : sbyte
    {
        SHAPE_SPHERER = 0,
        SHAPE_BOX = 1,
        SHAPE_CYLINDER = 2,
        SHAPE_CAPCULE = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 96)]
    public struct CollisionPart
    {
        [FieldOffset(0)]  public CString nodeName;
        [FieldOffset(16)] public Shape shape;
        [FieldOffset(17)] public bool isPhysics;
        [FieldOffset(32)] public Vector3 size;
        [FieldOffset(48)] public Vector3 offset;
        [FieldOffset(64)] public Vector3 rot;
        [FieldOffset(80)] public CString tagName;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3072)]
    public struct CollisionPartParameter
    {
        [FieldOffset(0)] public CollisionPart colParts__arr0;
        [FieldOffset(96)] public CollisionPart colParts__arr1;
        [FieldOffset(192)] public CollisionPart colParts__arr2;
        [FieldOffset(288)] public CollisionPart colParts__arr3;
        [FieldOffset(384)] public CollisionPart colParts__arr4;
        [FieldOffset(480)] public CollisionPart colParts__arr5;
        [FieldOffset(576)] public CollisionPart colParts__arr6;
        [FieldOffset(672)] public CollisionPart colParts__arr7;
        [FieldOffset(768)] public CollisionPart colParts__arr8;
        [FieldOffset(864)] public CollisionPart colParts__arr9;
        [FieldOffset(960)] public CollisionPart colParts__arr10;
        [FieldOffset(1056)] public CollisionPart colParts__arr11;
        [FieldOffset(1152)] public CollisionPart colParts__arr12;
        [FieldOffset(1248)] public CollisionPart colParts__arr13;
        [FieldOffset(1344)] public CollisionPart colParts__arr14;
        [FieldOffset(1440)] public CollisionPart colParts__arr15;
        [FieldOffset(1536)] public CollisionPart colParts__arr16;
        [FieldOffset(1632)] public CollisionPart colParts__arr17;
        [FieldOffset(1728)] public CollisionPart colParts__arr18;
        [FieldOffset(1824)] public CollisionPart colParts__arr19;
        [FieldOffset(1920)] public CollisionPart colParts__arr20;
        [FieldOffset(2016)] public CollisionPart colParts__arr21;
        [FieldOffset(2112)] public CollisionPart colParts__arr22;
        [FieldOffset(2208)] public CollisionPart colParts__arr23;
        [FieldOffset(2304)] public CollisionPart colParts__arr24;
        [FieldOffset(2400)] public CollisionPart colParts__arr25;
        [FieldOffset(2496)] public CollisionPart colParts__arr26;
        [FieldOffset(2592)] public CollisionPart colParts__arr27;
        [FieldOffset(2688)] public CollisionPart colParts__arr28;
        [FieldOffset(2784)] public CollisionPart colParts__arr29;
        [FieldOffset(2880)] public CollisionPart colParts__arr30;
        [FieldOffset(2976)] public CollisionPart colParts__arr31;
    }

    [StructLayout(LayoutKind.Explicit, Size = 13392)]
    public struct BossCommonParameters
    {
        [FieldOffset(0)]     public BossResourceInfo resource;
        [FieldOffset(80)]    public HoldPointParameter holdParam;
        [FieldOffset(10320)] public CollisionPartParameter colParam;
    }

}