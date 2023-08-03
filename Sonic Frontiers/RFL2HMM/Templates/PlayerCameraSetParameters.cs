using System.Numerics;
using System.Runtime.InteropServices;

public class PlayerCameraSetParametersClass
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

    public enum Priority : byte
    {
        Default = 0,
        High = 1
    }

    public enum CameraType : byte
    {
        None = 0,
        Fixed = 1,
        Offset = 2,
        Follow = 3,
        Pan = 4,
        StaticPan = 5,
        PanUpByFront = 6
    }

    public enum CameraCoordType : byte
    {
        Orthgonal = 0,
        Spherical = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 112)]
    public struct PlayerCameraParameter
    {
        [FieldOffset(0)]  public CameraType type;
        [FieldOffset(4)]  public float time;
        [FieldOffset(8)]  public float easeinTime;
        [FieldOffset(12)] public CameraCoordType lookAtCoord;
        [FieldOffset(16)] public Vector3 localLookAtOffset;
        [FieldOffset(32)] public Vector3 worldLookAtOffset;
        [FieldOffset(48)] public CameraCoordType eyeCoord;
        [FieldOffset(64)] public Vector3 localEyeOffset;
        [FieldOffset(80)] public Vector3 worldEyeOffset;
        [FieldOffset(96)] public float roll;
    }

    [StructLayout(LayoutKind.Explicit, Size = 928)]
    public struct PlayerCameraSetParameter
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public float easeoutTime;
        [FieldOffset(20)] public Priority priority;
        [FieldOffset(32)] public PlayerCameraParameter param__arr0;
        [FieldOffset(144)] public PlayerCameraParameter param__arr1;
        [FieldOffset(256)] public PlayerCameraParameter param__arr2;
        [FieldOffset(368)] public PlayerCameraParameter param__arr3;
        [FieldOffset(480)] public PlayerCameraParameter param__arr4;
        [FieldOffset(592)] public PlayerCameraParameter param__arr5;
        [FieldOffset(704)] public PlayerCameraParameter param__arr6;
        [FieldOffset(816)] public PlayerCameraParameter param__arr7;
    }

    [StructLayout(LayoutKind.Explicit, Size = 41760)]
    public struct PlayerCameraSetParameters
    {
        [FieldOffset(0)] public PlayerCameraSetParameter data__arr0;
        [FieldOffset(928)] public PlayerCameraSetParameter data__arr1;
        [FieldOffset(1856)] public PlayerCameraSetParameter data__arr2;
        [FieldOffset(2784)] public PlayerCameraSetParameter data__arr3;
        [FieldOffset(3712)] public PlayerCameraSetParameter data__arr4;
        [FieldOffset(4640)] public PlayerCameraSetParameter data__arr5;
        [FieldOffset(5568)] public PlayerCameraSetParameter data__arr6;
        [FieldOffset(6496)] public PlayerCameraSetParameter data__arr7;
        [FieldOffset(7424)] public PlayerCameraSetParameter data__arr8;
        [FieldOffset(8352)] public PlayerCameraSetParameter data__arr9;
        [FieldOffset(9280)] public PlayerCameraSetParameter data__arr10;
        [FieldOffset(10208)] public PlayerCameraSetParameter data__arr11;
        [FieldOffset(11136)] public PlayerCameraSetParameter data__arr12;
        [FieldOffset(12064)] public PlayerCameraSetParameter data__arr13;
        [FieldOffset(12992)] public PlayerCameraSetParameter data__arr14;
        [FieldOffset(13920)] public PlayerCameraSetParameter data__arr15;
        [FieldOffset(14848)] public PlayerCameraSetParameter data__arr16;
        [FieldOffset(15776)] public PlayerCameraSetParameter data__arr17;
        [FieldOffset(16704)] public PlayerCameraSetParameter data__arr18;
        [FieldOffset(17632)] public PlayerCameraSetParameter data__arr19;
        [FieldOffset(18560)] public PlayerCameraSetParameter data__arr20;
        [FieldOffset(19488)] public PlayerCameraSetParameter data__arr21;
        [FieldOffset(20416)] public PlayerCameraSetParameter data__arr22;
        [FieldOffset(21344)] public PlayerCameraSetParameter data__arr23;
        [FieldOffset(22272)] public PlayerCameraSetParameter data__arr24;
        [FieldOffset(23200)] public PlayerCameraSetParameter data__arr25;
        [FieldOffset(24128)] public PlayerCameraSetParameter data__arr26;
        [FieldOffset(25056)] public PlayerCameraSetParameter data__arr27;
        [FieldOffset(25984)] public PlayerCameraSetParameter data__arr28;
        [FieldOffset(26912)] public PlayerCameraSetParameter data__arr29;
        [FieldOffset(27840)] public PlayerCameraSetParameter data__arr30;
        [FieldOffset(28768)] public PlayerCameraSetParameter data__arr31;
        [FieldOffset(29696)] public PlayerCameraSetParameter data__arr32;
        [FieldOffset(30624)] public PlayerCameraSetParameter data__arr33;
        [FieldOffset(31552)] public PlayerCameraSetParameter data__arr34;
        [FieldOffset(32480)] public PlayerCameraSetParameter data__arr35;
        [FieldOffset(33408)] public PlayerCameraSetParameter data__arr36;
        [FieldOffset(34336)] public PlayerCameraSetParameter data__arr37;
        [FieldOffset(35264)] public PlayerCameraSetParameter data__arr38;
        [FieldOffset(36192)] public PlayerCameraSetParameter data__arr39;
        [FieldOffset(37120)] public PlayerCameraSetParameter data__arr40;
        [FieldOffset(38048)] public PlayerCameraSetParameter data__arr41;
        [FieldOffset(38976)] public PlayerCameraSetParameter data__arr42;
        [FieldOffset(39904)] public PlayerCameraSetParameter data__arr43;
        [FieldOffset(40832)] public PlayerCameraSetParameter data__arr44;
    }

}