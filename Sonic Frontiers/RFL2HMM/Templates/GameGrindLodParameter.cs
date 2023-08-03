using System.Numerics;
using System.Runtime.InteropServices;

public class GameGrindLodParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct GameGrindLodParameter
    {
        [FieldOffset(0)]  public float distances__arr0;
        [FieldOffset(4)] public float distances__arr1;
        [FieldOffset(8)] public float distances__arr2;
        [FieldOffset(12)] public float distances__arr3;
        [FieldOffset(16)] public float cullingDistances__arr0;
        [FieldOffset(20)] public float cullingDistances__arr1;
        [FieldOffset(24)] public float cullingDistances__arr2;
        [FieldOffset(28)] public float cullingDistances__arr3;
    }

}