using System.Numerics;
using System.Runtime.InteropServices;

public class Obj3DPuzzleBlockConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 5)]
    public struct FSRow
    {
        [FieldOffset(0)] public byte columns__arr0;
        [FieldOffset(1)] public byte columns__arr1;
        [FieldOffset(2)] public byte columns__arr2;
        [FieldOffset(3)] public byte columns__arr3;
        [FieldOffset(4)] public byte columns__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 25)]
    public struct FSLayer
    {
        [FieldOffset(0)] public FSRow rows__arr0;
        [FieldOffset(5)] public FSRow rows__arr1;
        [FieldOffset(10)] public FSRow rows__arr2;
        [FieldOffset(15)] public FSRow rows__arr3;
        [FieldOffset(20)] public FSRow rows__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct FreeShape
    {
        [FieldOffset(0)]  public byte numLayers;
        [FieldOffset(1)]  public byte numRows;
        [FieldOffset(2)]  public byte numColumns;
        [FieldOffset(16)] public Vector3 offsetToTopLeft;
        [FieldOffset(32)] public FSLayer layers__arr0;
        [FieldOffset(57)] public FSLayer layers__arr1;
        [FieldOffset(82)] public FSLayer layers__arr2;
        [FieldOffset(107)] public FSLayer layers__arr3;
        [FieldOffset(132)] public FSLayer layers__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4640)]
    public struct Obj3DPuzzleBlockConfig
    {
        [FieldOffset(0)] public FreeShape freeShapes__arr0;
        [FieldOffset(160)] public FreeShape freeShapes__arr1;
        [FieldOffset(320)] public FreeShape freeShapes__arr2;
        [FieldOffset(480)] public FreeShape freeShapes__arr3;
        [FieldOffset(640)] public FreeShape freeShapes__arr4;
        [FieldOffset(800)] public FreeShape freeShapes__arr5;
        [FieldOffset(960)] public FreeShape freeShapes__arr6;
        [FieldOffset(1120)] public FreeShape freeShapes__arr7;
        [FieldOffset(1280)] public FreeShape freeShapes__arr8;
        [FieldOffset(1440)] public FreeShape freeShapes__arr9;
        [FieldOffset(1600)] public FreeShape freeShapes__arr10;
        [FieldOffset(1760)] public FreeShape freeShapes__arr11;
        [FieldOffset(1920)] public FreeShape freeShapes__arr12;
        [FieldOffset(2080)] public FreeShape freeShapes__arr13;
        [FieldOffset(2240)] public FreeShape freeShapes__arr14;
        [FieldOffset(2400)] public FreeShape freeShapes__arr15;
        [FieldOffset(2560)] public FreeShape freeShapes__arr16;
        [FieldOffset(2720)] public FreeShape freeShapes__arr17;
        [FieldOffset(2880)] public FreeShape freeShapes__arr18;
        [FieldOffset(3040)] public FreeShape freeShapes__arr19;
        [FieldOffset(3200)] public FreeShape freeShapes__arr20;
        [FieldOffset(3360)] public FreeShape freeShapes__arr21;
        [FieldOffset(3520)] public FreeShape freeShapes__arr22;
        [FieldOffset(3680)] public FreeShape freeShapes__arr23;
        [FieldOffset(3840)] public FreeShape freeShapes__arr24;
        [FieldOffset(4000)] public FreeShape freeShapes__arr25;
        [FieldOffset(4160)] public FreeShape freeShapes__arr26;
        [FieldOffset(4320)] public FreeShape freeShapes__arr27;
        [FieldOffset(4480)] public FreeShape freeShapes__arr28;
    }

}