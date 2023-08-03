using System.Numerics;
using System.Runtime.InteropServices;

public class GameHitStopParameterClass
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

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct GameHitStopParameterData
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public float scale;
        [FieldOffset(20)] public float time;
        [FieldOffset(24)] public float easeOutTime;
        [FieldOffset(28)] public float delayTime;
        [FieldOffset(32)] public bool layerPlayer;
        [FieldOffset(33)] public bool layerEnemy;
        [FieldOffset(34)] public bool layerDamagedEnemy;
        [FieldOffset(35)] public bool layerCamera;
        [FieldOffset(36)] public bool layerOthers;
    }

    [StructLayout(LayoutKind.Explicit, Size = 2560)]
    public struct GameHitStopParameter
    {
        [FieldOffset(0)] public GameHitStopParameterData data__arr0;
        [FieldOffset(40)] public GameHitStopParameterData data__arr1;
        [FieldOffset(80)] public GameHitStopParameterData data__arr2;
        [FieldOffset(120)] public GameHitStopParameterData data__arr3;
        [FieldOffset(160)] public GameHitStopParameterData data__arr4;
        [FieldOffset(200)] public GameHitStopParameterData data__arr5;
        [FieldOffset(240)] public GameHitStopParameterData data__arr6;
        [FieldOffset(280)] public GameHitStopParameterData data__arr7;
        [FieldOffset(320)] public GameHitStopParameterData data__arr8;
        [FieldOffset(360)] public GameHitStopParameterData data__arr9;
        [FieldOffset(400)] public GameHitStopParameterData data__arr10;
        [FieldOffset(440)] public GameHitStopParameterData data__arr11;
        [FieldOffset(480)] public GameHitStopParameterData data__arr12;
        [FieldOffset(520)] public GameHitStopParameterData data__arr13;
        [FieldOffset(560)] public GameHitStopParameterData data__arr14;
        [FieldOffset(600)] public GameHitStopParameterData data__arr15;
        [FieldOffset(640)] public GameHitStopParameterData data__arr16;
        [FieldOffset(680)] public GameHitStopParameterData data__arr17;
        [FieldOffset(720)] public GameHitStopParameterData data__arr18;
        [FieldOffset(760)] public GameHitStopParameterData data__arr19;
        [FieldOffset(800)] public GameHitStopParameterData data__arr20;
        [FieldOffset(840)] public GameHitStopParameterData data__arr21;
        [FieldOffset(880)] public GameHitStopParameterData data__arr22;
        [FieldOffset(920)] public GameHitStopParameterData data__arr23;
        [FieldOffset(960)] public GameHitStopParameterData data__arr24;
        [FieldOffset(1000)] public GameHitStopParameterData data__arr25;
        [FieldOffset(1040)] public GameHitStopParameterData data__arr26;
        [FieldOffset(1080)] public GameHitStopParameterData data__arr27;
        [FieldOffset(1120)] public GameHitStopParameterData data__arr28;
        [FieldOffset(1160)] public GameHitStopParameterData data__arr29;
        [FieldOffset(1200)] public GameHitStopParameterData data__arr30;
        [FieldOffset(1240)] public GameHitStopParameterData data__arr31;
        [FieldOffset(1280)] public GameHitStopParameterData data__arr32;
        [FieldOffset(1320)] public GameHitStopParameterData data__arr33;
        [FieldOffset(1360)] public GameHitStopParameterData data__arr34;
        [FieldOffset(1400)] public GameHitStopParameterData data__arr35;
        [FieldOffset(1440)] public GameHitStopParameterData data__arr36;
        [FieldOffset(1480)] public GameHitStopParameterData data__arr37;
        [FieldOffset(1520)] public GameHitStopParameterData data__arr38;
        [FieldOffset(1560)] public GameHitStopParameterData data__arr39;
        [FieldOffset(1600)] public GameHitStopParameterData data__arr40;
        [FieldOffset(1640)] public GameHitStopParameterData data__arr41;
        [FieldOffset(1680)] public GameHitStopParameterData data__arr42;
        [FieldOffset(1720)] public GameHitStopParameterData data__arr43;
        [FieldOffset(1760)] public GameHitStopParameterData data__arr44;
        [FieldOffset(1800)] public GameHitStopParameterData data__arr45;
        [FieldOffset(1840)] public GameHitStopParameterData data__arr46;
        [FieldOffset(1880)] public GameHitStopParameterData data__arr47;
        [FieldOffset(1920)] public GameHitStopParameterData data__arr48;
        [FieldOffset(1960)] public GameHitStopParameterData data__arr49;
        [FieldOffset(2000)] public GameHitStopParameterData data__arr50;
        [FieldOffset(2040)] public GameHitStopParameterData data__arr51;
        [FieldOffset(2080)] public GameHitStopParameterData data__arr52;
        [FieldOffset(2120)] public GameHitStopParameterData data__arr53;
        [FieldOffset(2160)] public GameHitStopParameterData data__arr54;
        [FieldOffset(2200)] public GameHitStopParameterData data__arr55;
        [FieldOffset(2240)] public GameHitStopParameterData data__arr56;
        [FieldOffset(2280)] public GameHitStopParameterData data__arr57;
        [FieldOffset(2320)] public GameHitStopParameterData data__arr58;
        [FieldOffset(2360)] public GameHitStopParameterData data__arr59;
        [FieldOffset(2400)] public GameHitStopParameterData data__arr60;
        [FieldOffset(2440)] public GameHitStopParameterData data__arr61;
        [FieldOffset(2480)] public GameHitStopParameterData data__arr62;
        [FieldOffset(2520)] public GameHitStopParameterData data__arr63;
    }

}