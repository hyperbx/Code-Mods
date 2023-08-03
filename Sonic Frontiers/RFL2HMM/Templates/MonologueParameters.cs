using System.Numerics;
using System.Runtime.InteropServices;

public class MonologueParametersClass
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

    [StructLayout(LayoutKind.Explicit, Size = 392)]
    public struct MonologueIslandParameters
    {
        [FieldOffset(0)] public float playSpanTime;
        [FieldOffset(8)] public CString labelNames__arr0;
        [FieldOffset(263)] public CString labelNames__arr1;
        [FieldOffset(518)] public CString labelNames__arr2;
        [FieldOffset(773)] public CString labelNames__arr3;
        [FieldOffset(1028)] public CString labelNames__arr4;
        [FieldOffset(1283)] public CString labelNames__arr5;
        [FieldOffset(1538)] public CString labelNames__arr6;
        [FieldOffset(1793)] public CString labelNames__arr7;
        [FieldOffset(2048)] public CString labelNames__arr8;
        [FieldOffset(2303)] public CString labelNames__arr9;
        [FieldOffset(2558)] public CString labelNames__arr10;
        [FieldOffset(2813)] public CString labelNames__arr11;
        [FieldOffset(3068)] public CString labelNames__arr12;
        [FieldOffset(3323)] public CString labelNames__arr13;
        [FieldOffset(3578)] public CString labelNames__arr14;
        [FieldOffset(3833)] public CString labelNames__arr15;
        [FieldOffset(4088)] public CString labelNames__arr16;
        [FieldOffset(4343)] public CString labelNames__arr17;
        [FieldOffset(4598)] public CString labelNames__arr18;
        [FieldOffset(4853)] public CString labelNames__arr19;
        [FieldOffset(5108)] public CString labelNames__arr20;
        [FieldOffset(5363)] public CString labelNames__arr21;
        [FieldOffset(5618)] public CString labelNames__arr22;
        [FieldOffset(5873)] public CString labelNames__arr23;
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct MonologueMultiTextParameters
    {
        [FieldOffset(0)] public CString labelNames__arr0;
        [FieldOffset(255)] public CString labelNames__arr1;
        [FieldOffset(510)] public CString labelNames__arr2;
        [FieldOffset(765)] public CString labelNames__arr3;
    }

    public enum Value : sbyte
    {
        SteppeIsland1 = 0,
        DesertIsland = 1,
        VolcanicIsland = 2,
        TowerIsland = 3,
        SteppeIsland2 = 4,
        Num = 5,
        ExtraIsland = 5,
        NumInExtra = 6
    }

    [StructLayout(LayoutKind.Explicit, Size = 2032)]
    public struct MonologueParameters
    {
        [FieldOffset(0)]    public MonologueIslandParameters islands__arr0;
        [FieldOffset(392)] public MonologueIslandParameters islands__arr1;
        [FieldOffset(784)] public MonologueIslandParameters islands__arr2;
        [FieldOffset(1176)] public MonologueIslandParameters islands__arr3;
        [FieldOffset(1568)] public MonologueIslandParameters islands__arr4;
        [FieldOffset(1960)] public MonologueMultiTextParameters multiText;
        [FieldOffset(2024)] public sbyte firstTheEndNotifyCount;
        [FieldOffset(2025)] public sbyte theEndNotifyCount;
        [FieldOffset(2026)] public Value dummy;
    }

}