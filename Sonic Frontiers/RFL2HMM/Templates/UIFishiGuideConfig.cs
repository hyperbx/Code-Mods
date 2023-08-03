using System.Numerics;
using System.Runtime.InteropServices;

public class UIFishiGuideConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct FishCameraParam
    {
        [FieldOffset(0)]  public Vector3 position;
        [FieldOffset(16)] public Vector3 target;
        [FieldOffset(32)] public float fovy;
    }

    [StructLayout(LayoutKind.Explicit, Size = 5040)]
    public struct UIFishiGuideConfig
    {
        [FieldOffset(0)] public FishCameraParam fishList__arr0;
        [FieldOffset(48)] public FishCameraParam fishList__arr1;
        [FieldOffset(96)] public FishCameraParam fishList__arr2;
        [FieldOffset(144)] public FishCameraParam fishList__arr3;
        [FieldOffset(192)] public FishCameraParam fishList__arr4;
        [FieldOffset(240)] public FishCameraParam fishList__arr5;
        [FieldOffset(288)] public FishCameraParam fishList__arr6;
        [FieldOffset(336)] public FishCameraParam fishList__arr7;
        [FieldOffset(384)] public FishCameraParam fishList__arr8;
        [FieldOffset(432)] public FishCameraParam fishList__arr9;
        [FieldOffset(480)] public FishCameraParam fishList__arr10;
        [FieldOffset(528)] public FishCameraParam fishList__arr11;
        [FieldOffset(576)] public FishCameraParam fishList__arr12;
        [FieldOffset(624)] public FishCameraParam fishList__arr13;
        [FieldOffset(672)] public FishCameraParam fishList__arr14;
        [FieldOffset(720)] public FishCameraParam fishList__arr15;
        [FieldOffset(768)] public FishCameraParam fishList__arr16;
        [FieldOffset(816)] public FishCameraParam fishList__arr17;
        [FieldOffset(864)] public FishCameraParam fishList__arr18;
        [FieldOffset(912)] public FishCameraParam fishList__arr19;
        [FieldOffset(960)] public FishCameraParam fishList__arr20;
        [FieldOffset(1008)] public FishCameraParam fishList__arr21;
        [FieldOffset(1056)] public FishCameraParam fishList__arr22;
        [FieldOffset(1104)] public FishCameraParam fishList__arr23;
        [FieldOffset(1152)] public FishCameraParam fishList__arr24;
        [FieldOffset(1200)] public FishCameraParam fishList__arr25;
        [FieldOffset(1248)] public FishCameraParam fishList__arr26;
        [FieldOffset(1296)] public FishCameraParam fishList__arr27;
        [FieldOffset(1344)] public FishCameraParam fishList__arr28;
        [FieldOffset(1392)] public FishCameraParam fishList__arr29;
        [FieldOffset(1440)] public FishCameraParam fishList__arr30;
        [FieldOffset(1488)] public FishCameraParam fishList__arr31;
        [FieldOffset(1536)] public FishCameraParam fishList__arr32;
        [FieldOffset(1584)] public FishCameraParam fishList__arr33;
        [FieldOffset(1632)] public FishCameraParam fishList__arr34;
        [FieldOffset(1680)] public FishCameraParam fishList__arr35;
        [FieldOffset(1728)] public FishCameraParam fishList__arr36;
        [FieldOffset(1776)] public FishCameraParam fishList__arr37;
        [FieldOffset(1824)] public FishCameraParam fishList__arr38;
        [FieldOffset(1872)] public FishCameraParam fishList__arr39;
        [FieldOffset(1920)] public FishCameraParam fishList__arr40;
        [FieldOffset(1968)] public FishCameraParam fishList__arr41;
        [FieldOffset(2016)] public FishCameraParam fishList__arr42;
        [FieldOffset(2064)] public FishCameraParam fishList__arr43;
        [FieldOffset(2112)] public FishCameraParam fishList__arr44;
        [FieldOffset(2160)] public FishCameraParam fishList__arr45;
        [FieldOffset(2208)] public FishCameraParam fishList__arr46;
        [FieldOffset(2256)] public FishCameraParam fishList__arr47;
        [FieldOffset(2304)] public FishCameraParam fishList__arr48;
        [FieldOffset(2352)] public FishCameraParam fishList__arr49;
        [FieldOffset(2400)] public FishCameraParam fishList__arr50;
        [FieldOffset(2448)] public FishCameraParam fishList__arr51;
        [FieldOffset(2496)] public FishCameraParam fishList__arr52;
        [FieldOffset(2544)] public FishCameraParam fishList__arr53;
        [FieldOffset(2592)] public FishCameraParam fishList__arr54;
        [FieldOffset(2640)] public FishCameraParam fishList__arr55;
        [FieldOffset(2688)] public FishCameraParam fishList__arr56;
        [FieldOffset(2736)] public FishCameraParam fishList__arr57;
        [FieldOffset(2784)] public FishCameraParam fishList__arr58;
        [FieldOffset(2832)] public FishCameraParam fishList__arr59;
        [FieldOffset(2880)] public FishCameraParam fishList__arr60;
        [FieldOffset(2928)] public FishCameraParam fishList__arr61;
        [FieldOffset(2976)] public FishCameraParam fishList__arr62;
        [FieldOffset(3024)] public FishCameraParam fishList__arr63;
        [FieldOffset(3072)] public FishCameraParam fishList__arr64;
        [FieldOffset(3120)] public FishCameraParam fishList__arr65;
        [FieldOffset(3168)] public FishCameraParam fishList__arr66;
        [FieldOffset(3216)] public FishCameraParam fishList__arr67;
        [FieldOffset(3264)] public FishCameraParam fishList__arr68;
        [FieldOffset(3312)] public FishCameraParam fishList__arr69;
        [FieldOffset(3360)] public FishCameraParam fishList__arr70;
        [FieldOffset(3408)] public FishCameraParam fishList__arr71;
        [FieldOffset(3456)] public FishCameraParam fishList__arr72;
        [FieldOffset(3504)] public FishCameraParam fishList__arr73;
        [FieldOffset(3552)] public FishCameraParam fishList__arr74;
        [FieldOffset(3600)] public FishCameraParam fishList__arr75;
        [FieldOffset(3648)] public FishCameraParam fishList__arr76;
        [FieldOffset(3696)] public FishCameraParam fishList__arr77;
        [FieldOffset(3744)] public FishCameraParam fishList__arr78;
        [FieldOffset(3792)] public FishCameraParam fishList__arr79;
        [FieldOffset(3840)] public FishCameraParam fishList__arr80;
        [FieldOffset(3888)] public FishCameraParam fishList__arr81;
        [FieldOffset(3936)] public FishCameraParam fishList__arr82;
        [FieldOffset(3984)] public FishCameraParam fishList__arr83;
        [FieldOffset(4032)] public FishCameraParam fishList__arr84;
        [FieldOffset(4080)] public FishCameraParam fishList__arr85;
        [FieldOffset(4128)] public FishCameraParam fishList__arr86;
        [FieldOffset(4176)] public FishCameraParam fishList__arr87;
        [FieldOffset(4224)] public FishCameraParam fishList__arr88;
        [FieldOffset(4272)] public FishCameraParam fishList__arr89;
        [FieldOffset(4320)] public FishCameraParam fishList__arr90;
        [FieldOffset(4368)] public FishCameraParam fishList__arr91;
        [FieldOffset(4416)] public FishCameraParam fishList__arr92;
        [FieldOffset(4464)] public FishCameraParam fishList__arr93;
        [FieldOffset(4512)] public FishCameraParam fishList__arr94;
        [FieldOffset(4560)] public FishCameraParam fishList__arr95;
        [FieldOffset(4608)] public FishCameraParam fishList__arr96;
        [FieldOffset(4656)] public FishCameraParam fishList__arr97;
        [FieldOffset(4704)] public FishCameraParam fishList__arr98;
        [FieldOffset(4752)] public FishCameraParam fishList__arr99;
        [FieldOffset(4800)] public FishCameraParam fishList__arr100;
        [FieldOffset(4848)] public FishCameraParam fishList__arr101;
        [FieldOffset(4896)] public FishCameraParam fishList__arr102;
        [FieldOffset(4944)] public FishCameraParam fishList__arr103;
        [FieldOffset(4992)] public FishCameraParam fishList__arr104;
    }

}