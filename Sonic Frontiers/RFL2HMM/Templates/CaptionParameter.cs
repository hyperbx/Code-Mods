using System.Numerics;
using System.Runtime.InteropServices;

public class CaptionParameterClass
{
    public enum DisplayType : sbyte
    {
        Caption = 0,
        Tutorial = 1
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

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct LabelData
    {
        [FieldOffset(0)]  public DisplayType display;
        [FieldOffset(8)]  public CString label;
        [FieldOffset(24)] public float waitTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 648)]
    public struct Discussion
    {
        [FieldOffset(0)]   public LabelData labels__arr0;
        [FieldOffset(32)] public LabelData labels__arr1;
        [FieldOffset(64)] public LabelData labels__arr2;
        [FieldOffset(96)] public LabelData labels__arr3;
        [FieldOffset(128)] public LabelData labels__arr4;
        [FieldOffset(160)] public LabelData labels__arr5;
        [FieldOffset(192)] public LabelData labels__arr6;
        [FieldOffset(224)] public LabelData labels__arr7;
        [FieldOffset(256)] public LabelData labels__arr8;
        [FieldOffset(288)] public LabelData labels__arr9;
        [FieldOffset(320)] public LabelData labels__arr10;
        [FieldOffset(352)] public LabelData labels__arr11;
        [FieldOffset(384)] public LabelData labels__arr12;
        [FieldOffset(416)] public LabelData labels__arr13;
        [FieldOffset(448)] public LabelData labels__arr14;
        [FieldOffset(480)] public LabelData labels__arr15;
        [FieldOffset(512)] public LabelData labels__arr16;
        [FieldOffset(544)] public LabelData labels__arr17;
        [FieldOffset(576)] public LabelData labels__arr18;
        [FieldOffset(608)] public LabelData labels__arr19;
        [FieldOffset(640)] public bool isForcePlay;
    }

    [StructLayout(LayoutKind.Explicit, Size = 6480)]
    public struct CaptionParameter
    {
        [FieldOffset(0)] public Discussion discussions__arr0;
        [FieldOffset(648)] public Discussion discussions__arr1;
        [FieldOffset(1296)] public Discussion discussions__arr2;
        [FieldOffset(1944)] public Discussion discussions__arr3;
        [FieldOffset(2592)] public Discussion discussions__arr4;
        [FieldOffset(3240)] public Discussion discussions__arr5;
        [FieldOffset(3888)] public Discussion discussions__arr6;
        [FieldOffset(4536)] public Discussion discussions__arr7;
        [FieldOffset(5184)] public Discussion discussions__arr8;
        [FieldOffset(5832)] public Discussion discussions__arr9;
    }

}