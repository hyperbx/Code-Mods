using System.Numerics;
using System.Runtime.InteropServices;

public class ObjEffectDebrisParametersClass
{
    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct ExplosionParameter
    {
        [FieldOffset(0)]  public Vector3 centerPosOffsetMin;
        [FieldOffset(16)] public Vector3 centerPosOffsetMax;
        [FieldOffset(32)] public float range;
        [FieldOffset(36)] public float powerMin;
        [FieldOffset(40)] public float powerMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct ImpulseParameter
    {
        [FieldOffset(0)]  public Vector3 impulseDir;
        [FieldOffset(16)] public float powerMin;
        [FieldOffset(20)] public float powerMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct DebrisPhaseParameter
    {
        [FieldOffset(0)]  public float marginTime;
        [FieldOffset(4)]  public float nextTime;
        [FieldOffset(8)]  public float gravity;
        [FieldOffset(12)] public float moveStopTime;
        [FieldOffset(16)] public bool damping;
        [FieldOffset(32)] public ExplosionParameter explosionParam;
        [FieldOffset(80)] public ImpulseParameter impulseParam;
    }

    [StructLayout(LayoutKind.Explicit, Size = 336)]
    public struct EffectDebrisParameter
    {
        [FieldOffset(0)] public DebrisPhaseParameter debrisPhaseParameters__arr0;
        [FieldOffset(112)] public DebrisPhaseParameter debrisPhaseParameters__arr1;
        [FieldOffset(224)] public DebrisPhaseParameter debrisPhaseParameters__arr2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3360)]
    public struct ObjEffectDebrisParameters
    {
        [FieldOffset(0)] public EffectDebrisParameter effectDebrisParameters__arr0;
        [FieldOffset(336)] public EffectDebrisParameter effectDebrisParameters__arr1;
        [FieldOffset(672)] public EffectDebrisParameter effectDebrisParameters__arr2;
        [FieldOffset(1008)] public EffectDebrisParameter effectDebrisParameters__arr3;
        [FieldOffset(1344)] public EffectDebrisParameter effectDebrisParameters__arr4;
        [FieldOffset(1680)] public EffectDebrisParameter effectDebrisParameters__arr5;
        [FieldOffset(2016)] public EffectDebrisParameter effectDebrisParameters__arr6;
        [FieldOffset(2352)] public EffectDebrisParameter effectDebrisParameters__arr7;
        [FieldOffset(2688)] public EffectDebrisParameter effectDebrisParameters__arr8;
        [FieldOffset(3024)] public EffectDebrisParameter effectDebrisParameters__arr9;
    }

}