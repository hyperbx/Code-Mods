using System.Numerics;
using System.Runtime.InteropServices;

public class ObjNormalFloorConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct NormalFloorSize
    {
        [FieldOffset(0)] public float length;
        [FieldOffset(4)] public float width;
        [FieldOffset(8)] public float height;
    }

    [StructLayout(LayoutKind.Explicit, Size = 120)]
    public struct ObjNormalFloorConfig
    {
        [FieldOffset(0)] public NormalFloorSize sizeInfo__arr0;
        [FieldOffset(12)] public NormalFloorSize sizeInfo__arr1;
        [FieldOffset(24)] public NormalFloorSize sizeInfo__arr2;
        [FieldOffset(36)] public NormalFloorSize sizeInfo__arr3;
        [FieldOffset(48)] public NormalFloorSize sizeInfo__arr4;
        [FieldOffset(60)] public NormalFloorSize sizeInfo__arr5;
        [FieldOffset(72)] public NormalFloorSize sizeInfo__arr6;
        [FieldOffset(84)] public NormalFloorSize sizeInfo__arr7;
        [FieldOffset(96)] public NormalFloorSize sizeInfo__arr8;
        [FieldOffset(108)] public NormalFloorSize sizeInfo__arr9;
    }

}