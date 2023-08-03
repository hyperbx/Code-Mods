using System.Numerics;
using System.Runtime.InteropServices;

public class ContentParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 2)]
    public struct AddDatabaseInfo
    {
        [FieldOffset(0)] public byte recordNo;
        [FieldOffset(1)] public byte numRecords;
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

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct ContentParameter
    {
        [FieldOffset(0)] public AddDatabaseInfo databases__arr0;
        [FieldOffset(2)] public AddDatabaseInfo databases__arr1;
        [FieldOffset(8)] public CString stagedata;
    }

}