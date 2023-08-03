using System.Numerics;
using System.Runtime.InteropServices;

public class CustomMusicParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct CustomMusicTransitInfo
    {
        [FieldOffset(0)] public float fadeOutTime;
        [FieldOffset(4)] public float delayTime;
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

    public enum MusicType : sbyte
    {
        THEME_SONG = 0,
        OTHER = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct CustomMusicInfo
    {
        [FieldOffset(0)]  public CString cueName;
        [FieldOffset(16)] public float fadeOutTiming;
        [FieldOffset(20)] public bool _lock;
        [FieldOffset(21)] public MusicType musicType;
    }

    [StructLayout(LayoutKind.Explicit, Size = 3088)]
    public struct CustomMusicParameter
    {
        [FieldOffset(0)]    public CustomMusicTransitInfo transitInfo;
        [FieldOffset(8)]    public CustomMusicInfo musicInfos__arr0;
        [FieldOffset(32)] public CustomMusicInfo musicInfos__arr1;
        [FieldOffset(56)] public CustomMusicInfo musicInfos__arr2;
        [FieldOffset(80)] public CustomMusicInfo musicInfos__arr3;
        [FieldOffset(104)] public CustomMusicInfo musicInfos__arr4;
        [FieldOffset(128)] public CustomMusicInfo musicInfos__arr5;
        [FieldOffset(152)] public CustomMusicInfo musicInfos__arr6;
        [FieldOffset(176)] public CustomMusicInfo musicInfos__arr7;
        [FieldOffset(200)] public CustomMusicInfo musicInfos__arr8;
        [FieldOffset(224)] public CustomMusicInfo musicInfos__arr9;
        [FieldOffset(248)] public CustomMusicInfo musicInfos__arr10;
        [FieldOffset(272)] public CustomMusicInfo musicInfos__arr11;
        [FieldOffset(296)] public CustomMusicInfo musicInfos__arr12;
        [FieldOffset(320)] public CustomMusicInfo musicInfos__arr13;
        [FieldOffset(344)] public CustomMusicInfo musicInfos__arr14;
        [FieldOffset(368)] public CustomMusicInfo musicInfos__arr15;
        [FieldOffset(392)] public CustomMusicInfo musicInfos__arr16;
        [FieldOffset(416)] public CustomMusicInfo musicInfos__arr17;
        [FieldOffset(440)] public CustomMusicInfo musicInfos__arr18;
        [FieldOffset(464)] public CustomMusicInfo musicInfos__arr19;
        [FieldOffset(488)] public CustomMusicInfo musicInfos__arr20;
        [FieldOffset(512)] public CustomMusicInfo musicInfos__arr21;
        [FieldOffset(536)] public CustomMusicInfo musicInfos__arr22;
        [FieldOffset(560)] public CustomMusicInfo musicInfos__arr23;
        [FieldOffset(584)] public CustomMusicInfo musicInfos__arr24;
        [FieldOffset(608)] public CustomMusicInfo musicInfos__arr25;
        [FieldOffset(632)] public CustomMusicInfo musicInfos__arr26;
        [FieldOffset(656)] public CustomMusicInfo musicInfos__arr27;
        [FieldOffset(680)] public CustomMusicInfo musicInfos__arr28;
        [FieldOffset(704)] public CustomMusicInfo musicInfos__arr29;
        [FieldOffset(728)] public CustomMusicInfo musicInfos__arr30;
        [FieldOffset(752)] public CustomMusicInfo musicInfos__arr31;
        [FieldOffset(776)] public CustomMusicInfo musicInfos__arr32;
        [FieldOffset(800)] public CustomMusicInfo musicInfos__arr33;
        [FieldOffset(824)] public CustomMusicInfo musicInfos__arr34;
        [FieldOffset(848)] public CustomMusicInfo musicInfos__arr35;
        [FieldOffset(872)] public CustomMusicInfo musicInfos__arr36;
        [FieldOffset(896)] public CustomMusicInfo musicInfos__arr37;
        [FieldOffset(920)] public CustomMusicInfo musicInfos__arr38;
        [FieldOffset(944)] public CustomMusicInfo musicInfos__arr39;
        [FieldOffset(968)] public CustomMusicInfo musicInfos__arr40;
        [FieldOffset(992)] public CustomMusicInfo musicInfos__arr41;
        [FieldOffset(1016)] public CustomMusicInfo musicInfos__arr42;
        [FieldOffset(1040)] public CustomMusicInfo musicInfos__arr43;
        [FieldOffset(1064)] public CustomMusicInfo musicInfos__arr44;
        [FieldOffset(1088)] public CustomMusicInfo musicInfos__arr45;
        [FieldOffset(1112)] public CustomMusicInfo musicInfos__arr46;
        [FieldOffset(1136)] public CustomMusicInfo musicInfos__arr47;
        [FieldOffset(1160)] public CustomMusicInfo musicInfos__arr48;
        [FieldOffset(1184)] public CustomMusicInfo musicInfos__arr49;
        [FieldOffset(1208)] public CustomMusicInfo musicInfos__arr50;
        [FieldOffset(1232)] public CustomMusicInfo musicInfos__arr51;
        [FieldOffset(1256)] public CustomMusicInfo musicInfos__arr52;
        [FieldOffset(1280)] public CustomMusicInfo musicInfos__arr53;
        [FieldOffset(1304)] public CustomMusicInfo musicInfos__arr54;
        [FieldOffset(1328)] public CustomMusicInfo musicInfos__arr55;
        [FieldOffset(1352)] public CustomMusicInfo musicInfos__arr56;
        [FieldOffset(1376)] public CustomMusicInfo musicInfos__arr57;
        [FieldOffset(1400)] public CustomMusicInfo musicInfos__arr58;
        [FieldOffset(1424)] public CustomMusicInfo musicInfos__arr59;
        [FieldOffset(1448)] public CustomMusicInfo musicInfos__arr60;
        [FieldOffset(1472)] public CustomMusicInfo musicInfos__arr61;
        [FieldOffset(1496)] public CustomMusicInfo musicInfos__arr62;
        [FieldOffset(1520)] public CustomMusicInfo musicInfos__arr63;
        [FieldOffset(1544)] public CustomMusicInfo musicInfos__arr64;
        [FieldOffset(1568)] public CustomMusicInfo musicInfos__arr65;
        [FieldOffset(1592)] public CustomMusicInfo musicInfos__arr66;
        [FieldOffset(1616)] public CustomMusicInfo musicInfos__arr67;
        [FieldOffset(1640)] public CustomMusicInfo musicInfos__arr68;
        [FieldOffset(1664)] public CustomMusicInfo musicInfos__arr69;
        [FieldOffset(1688)] public CustomMusicInfo musicInfos__arr70;
        [FieldOffset(1712)] public CustomMusicInfo musicInfos__arr71;
        [FieldOffset(1736)] public CustomMusicInfo musicInfos__arr72;
        [FieldOffset(1760)] public CustomMusicInfo musicInfos__arr73;
        [FieldOffset(1784)] public CustomMusicInfo musicInfos__arr74;
        [FieldOffset(1808)] public CustomMusicInfo musicInfos__arr75;
        [FieldOffset(1832)] public CustomMusicInfo musicInfos__arr76;
        [FieldOffset(1856)] public CustomMusicInfo musicInfos__arr77;
        [FieldOffset(1880)] public CustomMusicInfo musicInfos__arr78;
        [FieldOffset(1904)] public CustomMusicInfo musicInfos__arr79;
        [FieldOffset(1928)] public CustomMusicInfo musicInfos__arr80;
        [FieldOffset(1952)] public CustomMusicInfo musicInfos__arr81;
        [FieldOffset(1976)] public CustomMusicInfo musicInfos__arr82;
        [FieldOffset(2000)] public CustomMusicInfo musicInfos__arr83;
        [FieldOffset(2024)] public CustomMusicInfo musicInfos__arr84;
        [FieldOffset(2048)] public CustomMusicInfo musicInfos__arr85;
        [FieldOffset(2072)] public CustomMusicInfo musicInfos__arr86;
        [FieldOffset(2096)] public CustomMusicInfo musicInfos__arr87;
        [FieldOffset(2120)] public CustomMusicInfo musicInfos__arr88;
        [FieldOffset(2144)] public CustomMusicInfo musicInfos__arr89;
        [FieldOffset(2168)] public CustomMusicInfo musicInfos__arr90;
        [FieldOffset(2192)] public CustomMusicInfo musicInfos__arr91;
        [FieldOffset(2216)] public CustomMusicInfo musicInfos__arr92;
        [FieldOffset(2240)] public CustomMusicInfo musicInfos__arr93;
        [FieldOffset(2264)] public CustomMusicInfo musicInfos__arr94;
        [FieldOffset(2288)] public CustomMusicInfo musicInfos__arr95;
        [FieldOffset(2312)] public CustomMusicInfo musicInfos__arr96;
        [FieldOffset(2336)] public CustomMusicInfo musicInfos__arr97;
        [FieldOffset(2360)] public CustomMusicInfo musicInfos__arr98;
        [FieldOffset(2384)] public CustomMusicInfo musicInfos__arr99;
        [FieldOffset(2408)] public CustomMusicInfo musicInfos__arr100;
        [FieldOffset(2432)] public CustomMusicInfo musicInfos__arr101;
        [FieldOffset(2456)] public CustomMusicInfo musicInfos__arr102;
        [FieldOffset(2480)] public CustomMusicInfo musicInfos__arr103;
        [FieldOffset(2504)] public CustomMusicInfo musicInfos__arr104;
        [FieldOffset(2528)] public CustomMusicInfo musicInfos__arr105;
        [FieldOffset(2552)] public CustomMusicInfo musicInfos__arr106;
        [FieldOffset(2576)] public CustomMusicInfo musicInfos__arr107;
        [FieldOffset(2600)] public CustomMusicInfo musicInfos__arr108;
        [FieldOffset(2624)] public CustomMusicInfo musicInfos__arr109;
        [FieldOffset(2648)] public CustomMusicInfo musicInfos__arr110;
        [FieldOffset(2672)] public CustomMusicInfo musicInfos__arr111;
        [FieldOffset(2696)] public CustomMusicInfo musicInfos__arr112;
        [FieldOffset(2720)] public CustomMusicInfo musicInfos__arr113;
        [FieldOffset(2744)] public CustomMusicInfo musicInfos__arr114;
        [FieldOffset(2768)] public CustomMusicInfo musicInfos__arr115;
        [FieldOffset(2792)] public CustomMusicInfo musicInfos__arr116;
        [FieldOffset(2816)] public CustomMusicInfo musicInfos__arr117;
        [FieldOffset(2840)] public CustomMusicInfo musicInfos__arr118;
        [FieldOffset(2864)] public CustomMusicInfo musicInfos__arr119;
        [FieldOffset(2888)] public CustomMusicInfo musicInfos__arr120;
        [FieldOffset(2912)] public CustomMusicInfo musicInfos__arr121;
        [FieldOffset(2936)] public CustomMusicInfo musicInfos__arr122;
        [FieldOffset(2960)] public CustomMusicInfo musicInfos__arr123;
        [FieldOffset(2984)] public CustomMusicInfo musicInfos__arr124;
        [FieldOffset(3008)] public CustomMusicInfo musicInfos__arr125;
        [FieldOffset(3032)] public CustomMusicInfo musicInfos__arr126;
        [FieldOffset(3056)] public CustomMusicInfo musicInfos__arr127;
        [FieldOffset(3080)] public float idlingViewTime;
    }

}