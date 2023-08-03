using System.Numerics;
using System.Runtime.InteropServices;

public class CameraShakeTableClass
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

    public enum ShakeType : byte
    {
        Directional = 0,
        WorldY = 1,
        Random = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct CameraShakeRecord
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public ShakeType type;
        [FieldOffset(20)] public float zRot;
        [FieldOffset(24)] public float duration;
        [FieldOffset(28)] public float frequency;
        [FieldOffset(32)] public float amplitude;
        [FieldOffset(36)] public float timeAttenuationRate;
        [FieldOffset(40)] public bool enableDistanceAttenuation;
        [FieldOffset(44)] public float attenuationDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3072)]
    public struct CameraShakeTable
    {
        [FieldOffset(0)] public CameraShakeRecord records__arr0;
        [FieldOffset(48)] public CameraShakeRecord records__arr1;
        [FieldOffset(96)] public CameraShakeRecord records__arr2;
        [FieldOffset(144)] public CameraShakeRecord records__arr3;
        [FieldOffset(192)] public CameraShakeRecord records__arr4;
        [FieldOffset(240)] public CameraShakeRecord records__arr5;
        [FieldOffset(288)] public CameraShakeRecord records__arr6;
        [FieldOffset(336)] public CameraShakeRecord records__arr7;
        [FieldOffset(384)] public CameraShakeRecord records__arr8;
        [FieldOffset(432)] public CameraShakeRecord records__arr9;
        [FieldOffset(480)] public CameraShakeRecord records__arr10;
        [FieldOffset(528)] public CameraShakeRecord records__arr11;
        [FieldOffset(576)] public CameraShakeRecord records__arr12;
        [FieldOffset(624)] public CameraShakeRecord records__arr13;
        [FieldOffset(672)] public CameraShakeRecord records__arr14;
        [FieldOffset(720)] public CameraShakeRecord records__arr15;
        [FieldOffset(768)] public CameraShakeRecord records__arr16;
        [FieldOffset(816)] public CameraShakeRecord records__arr17;
        [FieldOffset(864)] public CameraShakeRecord records__arr18;
        [FieldOffset(912)] public CameraShakeRecord records__arr19;
        [FieldOffset(960)] public CameraShakeRecord records__arr20;
        [FieldOffset(1008)] public CameraShakeRecord records__arr21;
        [FieldOffset(1056)] public CameraShakeRecord records__arr22;
        [FieldOffset(1104)] public CameraShakeRecord records__arr23;
        [FieldOffset(1152)] public CameraShakeRecord records__arr24;
        [FieldOffset(1200)] public CameraShakeRecord records__arr25;
        [FieldOffset(1248)] public CameraShakeRecord records__arr26;
        [FieldOffset(1296)] public CameraShakeRecord records__arr27;
        [FieldOffset(1344)] public CameraShakeRecord records__arr28;
        [FieldOffset(1392)] public CameraShakeRecord records__arr29;
        [FieldOffset(1440)] public CameraShakeRecord records__arr30;
        [FieldOffset(1488)] public CameraShakeRecord records__arr31;
        [FieldOffset(1536)] public CameraShakeRecord records__arr32;
        [FieldOffset(1584)] public CameraShakeRecord records__arr33;
        [FieldOffset(1632)] public CameraShakeRecord records__arr34;
        [FieldOffset(1680)] public CameraShakeRecord records__arr35;
        [FieldOffset(1728)] public CameraShakeRecord records__arr36;
        [FieldOffset(1776)] public CameraShakeRecord records__arr37;
        [FieldOffset(1824)] public CameraShakeRecord records__arr38;
        [FieldOffset(1872)] public CameraShakeRecord records__arr39;
        [FieldOffset(1920)] public CameraShakeRecord records__arr40;
        [FieldOffset(1968)] public CameraShakeRecord records__arr41;
        [FieldOffset(2016)] public CameraShakeRecord records__arr42;
        [FieldOffset(2064)] public CameraShakeRecord records__arr43;
        [FieldOffset(2112)] public CameraShakeRecord records__arr44;
        [FieldOffset(2160)] public CameraShakeRecord records__arr45;
        [FieldOffset(2208)] public CameraShakeRecord records__arr46;
        [FieldOffset(2256)] public CameraShakeRecord records__arr47;
        [FieldOffset(2304)] public CameraShakeRecord records__arr48;
        [FieldOffset(2352)] public CameraShakeRecord records__arr49;
        [FieldOffset(2400)] public CameraShakeRecord records__arr50;
        [FieldOffset(2448)] public CameraShakeRecord records__arr51;
        [FieldOffset(2496)] public CameraShakeRecord records__arr52;
        [FieldOffset(2544)] public CameraShakeRecord records__arr53;
        [FieldOffset(2592)] public CameraShakeRecord records__arr54;
        [FieldOffset(2640)] public CameraShakeRecord records__arr55;
        [FieldOffset(2688)] public CameraShakeRecord records__arr56;
        [FieldOffset(2736)] public CameraShakeRecord records__arr57;
        [FieldOffset(2784)] public CameraShakeRecord records__arr58;
        [FieldOffset(2832)] public CameraShakeRecord records__arr59;
        [FieldOffset(2880)] public CameraShakeRecord records__arr60;
        [FieldOffset(2928)] public CameraShakeRecord records__arr61;
        [FieldOffset(2976)] public CameraShakeRecord records__arr62;
        [FieldOffset(3024)] public CameraShakeRecord records__arr63;
    }

}