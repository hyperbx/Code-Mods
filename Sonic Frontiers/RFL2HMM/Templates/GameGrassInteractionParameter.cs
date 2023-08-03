using System.Numerics;
using System.Runtime.InteropServices;

public class GameGrassInteractionParameterClass
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

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct GameGrassInteractionParameterData
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public float radius;
        [FieldOffset(20)] public float height;
        [FieldOffset(24)] public float power;
        [FieldOffset(28)] public bool moveHitEnabled;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1024)]
    public struct GameGrassInteractionParameter
    {
        [FieldOffset(0)] public GameGrassInteractionParameterData data__arr0;
        [FieldOffset(32)] public GameGrassInteractionParameterData data__arr1;
        [FieldOffset(64)] public GameGrassInteractionParameterData data__arr2;
        [FieldOffset(96)] public GameGrassInteractionParameterData data__arr3;
        [FieldOffset(128)] public GameGrassInteractionParameterData data__arr4;
        [FieldOffset(160)] public GameGrassInteractionParameterData data__arr5;
        [FieldOffset(192)] public GameGrassInteractionParameterData data__arr6;
        [FieldOffset(224)] public GameGrassInteractionParameterData data__arr7;
        [FieldOffset(256)] public GameGrassInteractionParameterData data__arr8;
        [FieldOffset(288)] public GameGrassInteractionParameterData data__arr9;
        [FieldOffset(320)] public GameGrassInteractionParameterData data__arr10;
        [FieldOffset(352)] public GameGrassInteractionParameterData data__arr11;
        [FieldOffset(384)] public GameGrassInteractionParameterData data__arr12;
        [FieldOffset(416)] public GameGrassInteractionParameterData data__arr13;
        [FieldOffset(448)] public GameGrassInteractionParameterData data__arr14;
        [FieldOffset(480)] public GameGrassInteractionParameterData data__arr15;
        [FieldOffset(512)] public GameGrassInteractionParameterData data__arr16;
        [FieldOffset(544)] public GameGrassInteractionParameterData data__arr17;
        [FieldOffset(576)] public GameGrassInteractionParameterData data__arr18;
        [FieldOffset(608)] public GameGrassInteractionParameterData data__arr19;
        [FieldOffset(640)] public GameGrassInteractionParameterData data__arr20;
        [FieldOffset(672)] public GameGrassInteractionParameterData data__arr21;
        [FieldOffset(704)] public GameGrassInteractionParameterData data__arr22;
        [FieldOffset(736)] public GameGrassInteractionParameterData data__arr23;
        [FieldOffset(768)] public GameGrassInteractionParameterData data__arr24;
        [FieldOffset(800)] public GameGrassInteractionParameterData data__arr25;
        [FieldOffset(832)] public GameGrassInteractionParameterData data__arr26;
        [FieldOffset(864)] public GameGrassInteractionParameterData data__arr27;
        [FieldOffset(896)] public GameGrassInteractionParameterData data__arr28;
        [FieldOffset(928)] public GameGrassInteractionParameterData data__arr29;
        [FieldOffset(960)] public GameGrassInteractionParameterData data__arr30;
        [FieldOffset(992)] public GameGrassInteractionParameterData data__arr31;
    }

}