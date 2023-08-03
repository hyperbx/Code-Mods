using System.Numerics;
using System.Runtime.InteropServices;

public class DLCMhrBarbecueParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct DLCMhrBarbecueTokenParam
    {
        [FieldOffset(0)]  public uint rawToken;
        [FieldOffset(4)]  public uint rawBurnToken;
        [FieldOffset(8)]  public uint brownedToken;
        [FieldOffset(12)] public uint charredToken;
    }

    [StructLayout(LayoutKind.Explicit, Size = 100)]
    public struct DLCMhrBarbecueParameter
    {
        [FieldOffset(0)]  public float rawTime;
        [FieldOffset(4)]  public float rawBurnTime;
        [FieldOffset(8)]  public float brownedTime;
        [FieldOffset(12)] public float charredTime;
        [FieldOffset(16)] public float startwaitTime;
        [FieldOffset(20)] public float successTime;
        [FieldOffset(24)] public float missTime;
        [FieldOffset(28)] public float resultUIDelaySuccess;
        [FieldOffset(32)] public float resultUIDelayFaild;
        [FieldOffset(36)] public DLCMhrBarbecueTokenParam tokenParam__arr0;
        [FieldOffset(52)] public DLCMhrBarbecueTokenParam tokenParam__arr1;
        [FieldOffset(68)] public DLCMhrBarbecueTokenParam tokenParam__arr2;
        [FieldOffset(84)] public DLCMhrBarbecueTokenParam tokenParam__arr3;
    }

}