using System.Numerics;
using System.Runtime.InteropServices;

public class GraphicsParametersClass
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

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct AuraEffectLerpNode
    {
        [FieldOffset(0)]  public float distance;
        [FieldOffset(4)]  public float noiseTextureScrollSpeed;
        [FieldOffset(8)]  public float blurScale;
        [FieldOffset(12)] public float colorGain;
        [FieldOffset(16)] public float noiseGain;
    }

    [StructLayout(LayoutKind.Explicit, Size = 56)]
    public struct AuraEffectLerpParameter
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public AuraEffectLerpNode node__arr0;
        [FieldOffset(36)] public AuraEffectLerpNode node__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 224)]
    public struct AuraEffectParameters
    {
        [FieldOffset(0)] public AuraEffectLerpParameter _params__arr0;
        [FieldOffset(56)] public AuraEffectLerpParameter _params__arr1;
        [FieldOffset(112)] public AuraEffectLerpParameter _params__arr2;
        [FieldOffset(168)] public AuraEffectLerpParameter _params__arr3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct EffectParameters
    {
        [FieldOffset(0)] public float localLightIntensityScale;
        [FieldOffset(4)] public bool dropPriorityEnabled;
        [FieldOffset(5)] public sbyte dropPriority;
    }

    [StructLayout(LayoutKind.Explicit, Size = 5)]
    public struct WeatherBlockParameter
    {
        [FieldOffset(0)] public byte blockWeights__arr0;
        [FieldOffset(1)] public byte blockWeights__arr1;
        [FieldOffset(2)] public byte blockWeights__arr2;
        [FieldOffset(3)] public byte blockWeights__arr3;
        [FieldOffset(4)] public byte blockWeights__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 30)]
    public struct WeatherTypeParameter
    {
        [FieldOffset(0)] public byte transitWeights__arr0;
        [FieldOffset(1)] public byte transitWeights__arr1;
        [FieldOffset(2)] public byte transitWeights__arr2;
        [FieldOffset(3)] public byte transitWeights__arr3;
        [FieldOffset(4)] public byte transitWeights__arr4;
        [FieldOffset(5)] public WeatherBlockParameter blockParams__arr0;
        [FieldOffset(10)] public WeatherBlockParameter blockParams__arr1;
        [FieldOffset(15)] public WeatherBlockParameter blockParams__arr2;
        [FieldOffset(20)] public WeatherBlockParameter blockParams__arr3;
        [FieldOffset(25)] public WeatherBlockParameter blockParams__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 2)]
    public struct WeatherTimeParameter
    {
        [FieldOffset(0)] public byte hour;
        [FieldOffset(1)] public byte minute;
    }

    [StructLayout(LayoutKind.Explicit, Size = 10)]
    public struct WeatherTimeControlParameter
    {
        [FieldOffset(0)] public WeatherTimeParameter sunriseBeginTime;
        [FieldOffset(2)] public WeatherTimeParameter dayBeginTime;
        [FieldOffset(4)] public WeatherTimeParameter sunsetBeginTime;
        [FieldOffset(6)] public WeatherTimeParameter nightBeginTime;
        [FieldOffset(8)] public WeatherTimeParameter blockTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct WeatherParameters
    {
        [FieldOffset(0)]   public WeatherTypeParameter type__arr0;
        [FieldOffset(30)] public WeatherTypeParameter type__arr1;
        [FieldOffset(60)] public WeatherTypeParameter type__arr2;
        [FieldOffset(90)] public WeatherTypeParameter type__arr3;
        [FieldOffset(120)] public WeatherTypeParameter type__arr4;
        [FieldOffset(150)] public WeatherTimeControlParameter timeControl;
    }

    [StructLayout(LayoutKind.Explicit, Size = 392)]
    public struct GraphicsParameters
    {
        [FieldOffset(0)]   public AuraEffectParameters aura;
        [FieldOffset(224)] public EffectParameters effect;
        [FieldOffset(232)] public WeatherParameters weather;
    }

}