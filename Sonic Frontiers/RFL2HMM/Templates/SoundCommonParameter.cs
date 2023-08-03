using System.Numerics;
using System.Runtime.InteropServices;

public class SoundCommonParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct BGMVolumeChangeInfo
    {
        [FieldOffset(0)] public float value;
        [FieldOffset(4)] public float delayTime;
        [FieldOffset(8)] public float fadeTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 84)]
    public struct BGMVolumeChangeInfoList
    {
        [FieldOffset(0)]  public BGMVolumeChangeInfo playerStop;
        [FieldOffset(12)] public BGMVolumeChangeInfo playerWalk;
        [FieldOffset(24)] public BGMVolumeChangeInfo playerRun;
        [FieldOffset(36)] public BGMVolumeChangeInfo fishingHitIn;
        [FieldOffset(48)] public BGMVolumeChangeInfo fishingHitOut;
        [FieldOffset(60)] public BGMVolumeChangeInfo musicBoxIn;
        [FieldOffset(72)] public BGMVolumeChangeInfo musicBoxOut;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct AisacChangeInfo
    {
        [FieldOffset(0)] public float value;
        [FieldOffset(4)] public float fadeTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct AisacChangeInfoList
    {
        [FieldOffset(0)]  public AisacChangeInfo sunny;
        [FieldOffset(8)]  public AisacChangeInfo cloudy;
        [FieldOffset(16)] public AisacChangeInfo rainy;
        [FieldOffset(24)] public AisacChangeInfo beginUnderWater;
        [FieldOffset(32)] public AisacChangeInfo finishUnderWater;
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

    public enum Priority : sbyte
    {
        PRIORITY_LOW = 0,
        PRIORITY_DEFAULT = 1,
        PRIORITY_HIGH = 2,
        PRIORITY_SUPER_HIGH = 3,
        NUM_PRIORITY = 4,
        PRIORITY_INVALID = -1
    }

    public enum InterruptType : sbyte
    {
        INTERRUPT_TYPE_STOP = 0,
        INTERRUPT_TYPE_PAUSE = 1,
        INTERRUPT_TYPE_OVERLAP = 2,
        NUM_INTERRUPT_TYPE = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public struct BGMInfo
    {
        [FieldOffset(0)]  public CString cueName;
        [FieldOffset(16)] public int blockId;
        [FieldOffset(20)] public float fadeInTime;
        [FieldOffset(24)] public float fadeOutTime;
        [FieldOffset(28)] public float delayTime;
        [FieldOffset(32)] public CString aisacName;
        [FieldOffset(48)] public float aisacValue;
        [FieldOffset(52)] public float aisacFadeTime;
        [FieldOffset(56)] public bool isVolumeControl;
        [FieldOffset(57)] public bool isOverlapPlay;
        [FieldOffset(58)] public Priority priority;
        [FieldOffset(59)] public InterruptType interruptType;
    }

    public enum BGMTransitInfo_InterruptType : sbyte
    {
        BGMTransitInfo_InterruptType_INTERRUPT_TYPE_STOP = 0,
        BGMTransitInfo_InterruptType_INTERRUPT_TYPE_PAUSE = 1,
        BGMTransitInfo_InterruptType_INTERRUPT_TYPE_OVERLAP = 2,
        BGMTransitInfo_InterruptType_NUM_INTERRUPT_TYPE = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct BGMTransitInfo
    {
        [FieldOffset(0)]  public CString tagName;
        [FieldOffset(16)] public int beforeId;
        [FieldOffset(20)] public int beforeIdMax;
        [FieldOffset(24)] public int afterId;
        [FieldOffset(28)] public BGMTransitInfo_InterruptType type;
        [FieldOffset(32)] public float fadeOutTime;
        [FieldOffset(36)] public float fadeInTime;
        [FieldOffset(40)] public float delayTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 14480)]
    public struct SoundCommonParameter
    {
        [FieldOffset(0)]    public float pauseFadeOutTime;
        [FieldOffset(4)]    public float pauseFadeInTime;
        [FieldOffset(8)]    public float enterCyberFadeOutTime;
        [FieldOffset(12)]   public float leaveCyberResultFadeOutTime;
        [FieldOffset(16)]   public BGMVolumeChangeInfoList bgmVolumeInfo;
        [FieldOffset(100)]  public AisacChangeInfoList aisacInfo;
        [FieldOffset(144)]  public BGMInfo changeBgmInfo__arr0;
        [FieldOffset(208)] public BGMInfo changeBgmInfo__arr1;
        [FieldOffset(272)] public BGMInfo changeBgmInfo__arr2;
        [FieldOffset(336)] public BGMInfo changeBgmInfo__arr3;
        [FieldOffset(400)] public BGMInfo changeBgmInfo__arr4;
        [FieldOffset(464)] public BGMInfo changeBgmInfo__arr5;
        [FieldOffset(528)] public BGMInfo changeBgmInfo__arr6;
        [FieldOffset(592)] public BGMInfo changeBgmInfo__arr7;
        [FieldOffset(656)] public BGMInfo changeBgmInfo__arr8;
        [FieldOffset(720)] public BGMInfo changeBgmInfo__arr9;
        [FieldOffset(784)] public BGMInfo changeBgmInfo__arr10;
        [FieldOffset(848)] public BGMInfo changeBgmInfo__arr11;
        [FieldOffset(912)] public BGMInfo changeBgmInfo__arr12;
        [FieldOffset(976)] public BGMInfo changeBgmInfo__arr13;
        [FieldOffset(1040)] public BGMInfo changeBgmInfo__arr14;
        [FieldOffset(1104)] public BGMInfo changeBgmInfo__arr15;
        [FieldOffset(1168)] public BGMInfo changeBgmInfo__arr16;
        [FieldOffset(1232)] public BGMInfo changeBgmInfo__arr17;
        [FieldOffset(1296)] public BGMInfo changeBgmInfo__arr18;
        [FieldOffset(1360)] public BGMInfo changeBgmInfo__arr19;
        [FieldOffset(1424)] public BGMInfo changeBgmInfo__arr20;
        [FieldOffset(1488)] public BGMInfo changeBgmInfo__arr21;
        [FieldOffset(1552)] public BGMInfo changeBgmInfo__arr22;
        [FieldOffset(1616)] public BGMInfo changeBgmInfo__arr23;
        [FieldOffset(1680)] public BGMInfo changeBgmInfo__arr24;
        [FieldOffset(1744)] public BGMInfo changeBgmInfo__arr25;
        [FieldOffset(1808)] public BGMInfo changeBgmInfo__arr26;
        [FieldOffset(1872)] public BGMInfo changeBgmInfo__arr27;
        [FieldOffset(1936)] public BGMInfo changeBgmInfo__arr28;
        [FieldOffset(2000)] public BGMInfo changeBgmInfo__arr29;
        [FieldOffset(2064)] public BGMInfo changeBgmInfo__arr30;
        [FieldOffset(2128)] public BGMInfo changeBgmInfo__arr31;
        [FieldOffset(2192)] public BGMInfo changeBgmInfo__arr32;
        [FieldOffset(2256)] public BGMInfo changeBgmInfo__arr33;
        [FieldOffset(2320)] public BGMInfo changeBgmInfo__arr34;
        [FieldOffset(2384)] public BGMInfo changeBgmInfo__arr35;
        [FieldOffset(2448)] public BGMInfo changeBgmInfo__arr36;
        [FieldOffset(2512)] public BGMInfo changeBgmInfo__arr37;
        [FieldOffset(2576)] public BGMInfo changeBgmInfo__arr38;
        [FieldOffset(2640)] public BGMInfo changeBgmInfo__arr39;
        [FieldOffset(2704)] public BGMInfo changeBgmInfo__arr40;
        [FieldOffset(2768)] public BGMInfo changeBgmInfo__arr41;
        [FieldOffset(2832)] public BGMInfo changeBgmInfo__arr42;
        [FieldOffset(2896)] public BGMInfo changeBgmInfo__arr43;
        [FieldOffset(2960)] public BGMInfo changeBgmInfo__arr44;
        [FieldOffset(3024)] public BGMInfo changeBgmInfo__arr45;
        [FieldOffset(3088)] public BGMInfo changeBgmInfo__arr46;
        [FieldOffset(3152)] public BGMInfo changeBgmInfo__arr47;
        [FieldOffset(3216)] public BGMInfo changeBgmInfo__arr48;
        [FieldOffset(3280)] public BGMInfo changeBgmInfo__arr49;
        [FieldOffset(3344)] public BGMInfo changeBgmInfo__arr50;
        [FieldOffset(3408)] public BGMInfo changeBgmInfo__arr51;
        [FieldOffset(3472)] public BGMInfo changeBgmInfo__arr52;
        [FieldOffset(3536)] public BGMInfo changeBgmInfo__arr53;
        [FieldOffset(3600)] public BGMInfo changeBgmInfo__arr54;
        [FieldOffset(3664)] public BGMInfo changeBgmInfo__arr55;
        [FieldOffset(3728)] public BGMInfo changeBgmInfo__arr56;
        [FieldOffset(3792)] public BGMInfo changeBgmInfo__arr57;
        [FieldOffset(3856)] public BGMInfo changeBgmInfo__arr58;
        [FieldOffset(3920)] public BGMInfo changeBgmInfo__arr59;
        [FieldOffset(3984)] public BGMInfo changeBgmInfo__arr60;
        [FieldOffset(4048)] public BGMInfo changeBgmInfo__arr61;
        [FieldOffset(4112)] public BGMInfo changeBgmInfo__arr62;
        [FieldOffset(4176)] public BGMInfo changeBgmInfo__arr63;
        [FieldOffset(4240)] public BGMInfo changeBgmInfo__arr64;
        [FieldOffset(4304)] public BGMInfo changeBgmInfo__arr65;
        [FieldOffset(4368)] public BGMInfo changeBgmInfo__arr66;
        [FieldOffset(4432)] public BGMInfo changeBgmInfo__arr67;
        [FieldOffset(4496)] public BGMInfo changeBgmInfo__arr68;
        [FieldOffset(4560)] public BGMInfo changeBgmInfo__arr69;
        [FieldOffset(4624)] public BGMInfo changeBgmInfo__arr70;
        [FieldOffset(4688)] public BGMInfo changeBgmInfo__arr71;
        [FieldOffset(4752)] public BGMInfo changeBgmInfo__arr72;
        [FieldOffset(4816)] public BGMInfo changeBgmInfo__arr73;
        [FieldOffset(4880)] public BGMInfo changeBgmInfo__arr74;
        [FieldOffset(4944)] public BGMInfo changeBgmInfo__arr75;
        [FieldOffset(5008)] public BGMInfo changeBgmInfo__arr76;
        [FieldOffset(5072)] public BGMInfo changeBgmInfo__arr77;
        [FieldOffset(5136)] public BGMInfo changeBgmInfo__arr78;
        [FieldOffset(5200)] public BGMInfo changeBgmInfo__arr79;
        [FieldOffset(5264)] public BGMInfo changeBgmInfo__arr80;
        [FieldOffset(5328)] public BGMInfo changeBgmInfo__arr81;
        [FieldOffset(5392)] public BGMInfo changeBgmInfo__arr82;
        [FieldOffset(5456)] public BGMInfo changeBgmInfo__arr83;
        [FieldOffset(5520)] public BGMInfo changeBgmInfo__arr84;
        [FieldOffset(5584)] public BGMInfo changeBgmInfo__arr85;
        [FieldOffset(5648)] public BGMInfo changeBgmInfo__arr86;
        [FieldOffset(5712)] public BGMInfo changeBgmInfo__arr87;
        [FieldOffset(5776)] public BGMInfo changeBgmInfo__arr88;
        [FieldOffset(5840)] public BGMInfo changeBgmInfo__arr89;
        [FieldOffset(5904)] public BGMInfo changeBgmInfo__arr90;
        [FieldOffset(5968)] public BGMInfo changeBgmInfo__arr91;
        [FieldOffset(6032)] public BGMInfo changeBgmInfo__arr92;
        [FieldOffset(6096)] public BGMInfo changeBgmInfo__arr93;
        [FieldOffset(6160)] public BGMInfo changeBgmInfo__arr94;
        [FieldOffset(6224)] public BGMInfo changeBgmInfo__arr95;
        [FieldOffset(6288)] public BGMInfo changeBgmInfo__arr96;
        [FieldOffset(6352)] public BGMInfo changeBgmInfo__arr97;
        [FieldOffset(6416)] public BGMInfo changeBgmInfo__arr98;
        [FieldOffset(6480)] public BGMInfo changeBgmInfo__arr99;
        [FieldOffset(6544)] public BGMInfo changeBgmInfo__arr100;
        [FieldOffset(6608)] public BGMInfo changeBgmInfo__arr101;
        [FieldOffset(6672)] public BGMInfo changeBgmInfo__arr102;
        [FieldOffset(6736)] public BGMInfo changeBgmInfo__arr103;
        [FieldOffset(6800)] public BGMInfo changeBgmInfo__arr104;
        [FieldOffset(6864)] public BGMInfo changeBgmInfo__arr105;
        [FieldOffset(6928)] public BGMInfo changeBgmInfo__arr106;
        [FieldOffset(6992)] public BGMInfo changeBgmInfo__arr107;
        [FieldOffset(7056)] public BGMInfo changeBgmInfo__arr108;
        [FieldOffset(7120)] public BGMInfo changeBgmInfo__arr109;
        [FieldOffset(7184)] public BGMInfo changeBgmInfo__arr110;
        [FieldOffset(7248)] public BGMInfo changeBgmInfo__arr111;
        [FieldOffset(7312)] public BGMInfo changeBgmInfo__arr112;
        [FieldOffset(7376)] public BGMInfo changeBgmInfo__arr113;
        [FieldOffset(7440)] public BGMInfo changeBgmInfo__arr114;
        [FieldOffset(7504)] public BGMInfo changeBgmInfo__arr115;
        [FieldOffset(7568)] public BGMInfo changeBgmInfo__arr116;
        [FieldOffset(7632)] public BGMInfo changeBgmInfo__arr117;
        [FieldOffset(7696)] public BGMInfo changeBgmInfo__arr118;
        [FieldOffset(7760)] public BGMInfo changeBgmInfo__arr119;
        [FieldOffset(7824)] public BGMInfo changeBgmInfo__arr120;
        [FieldOffset(7888)] public BGMInfo changeBgmInfo__arr121;
        [FieldOffset(7952)] public BGMInfo changeBgmInfo__arr122;
        [FieldOffset(8016)] public BGMInfo changeBgmInfo__arr123;
        [FieldOffset(8080)] public BGMInfo changeBgmInfo__arr124;
        [FieldOffset(8144)] public BGMInfo changeBgmInfo__arr125;
        [FieldOffset(8208)] public BGMInfo changeBgmInfo__arr126;
        [FieldOffset(8272)] public BGMInfo changeBgmInfo__arr127;
        [FieldOffset(8336)] public BGMTransitInfo transitBgmInfo__arr0;
        [FieldOffset(8384)] public BGMTransitInfo transitBgmInfo__arr1;
        [FieldOffset(8432)] public BGMTransitInfo transitBgmInfo__arr2;
        [FieldOffset(8480)] public BGMTransitInfo transitBgmInfo__arr3;
        [FieldOffset(8528)] public BGMTransitInfo transitBgmInfo__arr4;
        [FieldOffset(8576)] public BGMTransitInfo transitBgmInfo__arr5;
        [FieldOffset(8624)] public BGMTransitInfo transitBgmInfo__arr6;
        [FieldOffset(8672)] public BGMTransitInfo transitBgmInfo__arr7;
        [FieldOffset(8720)] public BGMTransitInfo transitBgmInfo__arr8;
        [FieldOffset(8768)] public BGMTransitInfo transitBgmInfo__arr9;
        [FieldOffset(8816)] public BGMTransitInfo transitBgmInfo__arr10;
        [FieldOffset(8864)] public BGMTransitInfo transitBgmInfo__arr11;
        [FieldOffset(8912)] public BGMTransitInfo transitBgmInfo__arr12;
        [FieldOffset(8960)] public BGMTransitInfo transitBgmInfo__arr13;
        [FieldOffset(9008)] public BGMTransitInfo transitBgmInfo__arr14;
        [FieldOffset(9056)] public BGMTransitInfo transitBgmInfo__arr15;
        [FieldOffset(9104)] public BGMTransitInfo transitBgmInfo__arr16;
        [FieldOffset(9152)] public BGMTransitInfo transitBgmInfo__arr17;
        [FieldOffset(9200)] public BGMTransitInfo transitBgmInfo__arr18;
        [FieldOffset(9248)] public BGMTransitInfo transitBgmInfo__arr19;
        [FieldOffset(9296)] public BGMTransitInfo transitBgmInfo__arr20;
        [FieldOffset(9344)] public BGMTransitInfo transitBgmInfo__arr21;
        [FieldOffset(9392)] public BGMTransitInfo transitBgmInfo__arr22;
        [FieldOffset(9440)] public BGMTransitInfo transitBgmInfo__arr23;
        [FieldOffset(9488)] public BGMTransitInfo transitBgmInfo__arr24;
        [FieldOffset(9536)] public BGMTransitInfo transitBgmInfo__arr25;
        [FieldOffset(9584)] public BGMTransitInfo transitBgmInfo__arr26;
        [FieldOffset(9632)] public BGMTransitInfo transitBgmInfo__arr27;
        [FieldOffset(9680)] public BGMTransitInfo transitBgmInfo__arr28;
        [FieldOffset(9728)] public BGMTransitInfo transitBgmInfo__arr29;
        [FieldOffset(9776)] public BGMTransitInfo transitBgmInfo__arr30;
        [FieldOffset(9824)] public BGMTransitInfo transitBgmInfo__arr31;
        [FieldOffset(9872)] public BGMTransitInfo transitBgmInfo__arr32;
        [FieldOffset(9920)] public BGMTransitInfo transitBgmInfo__arr33;
        [FieldOffset(9968)] public BGMTransitInfo transitBgmInfo__arr34;
        [FieldOffset(10016)] public BGMTransitInfo transitBgmInfo__arr35;
        [FieldOffset(10064)] public BGMTransitInfo transitBgmInfo__arr36;
        [FieldOffset(10112)] public BGMTransitInfo transitBgmInfo__arr37;
        [FieldOffset(10160)] public BGMTransitInfo transitBgmInfo__arr38;
        [FieldOffset(10208)] public BGMTransitInfo transitBgmInfo__arr39;
        [FieldOffset(10256)] public BGMTransitInfo transitBgmInfo__arr40;
        [FieldOffset(10304)] public BGMTransitInfo transitBgmInfo__arr41;
        [FieldOffset(10352)] public BGMTransitInfo transitBgmInfo__arr42;
        [FieldOffset(10400)] public BGMTransitInfo transitBgmInfo__arr43;
        [FieldOffset(10448)] public BGMTransitInfo transitBgmInfo__arr44;
        [FieldOffset(10496)] public BGMTransitInfo transitBgmInfo__arr45;
        [FieldOffset(10544)] public BGMTransitInfo transitBgmInfo__arr46;
        [FieldOffset(10592)] public BGMTransitInfo transitBgmInfo__arr47;
        [FieldOffset(10640)] public BGMTransitInfo transitBgmInfo__arr48;
        [FieldOffset(10688)] public BGMTransitInfo transitBgmInfo__arr49;
        [FieldOffset(10736)] public BGMTransitInfo transitBgmInfo__arr50;
        [FieldOffset(10784)] public BGMTransitInfo transitBgmInfo__arr51;
        [FieldOffset(10832)] public BGMTransitInfo transitBgmInfo__arr52;
        [FieldOffset(10880)] public BGMTransitInfo transitBgmInfo__arr53;
        [FieldOffset(10928)] public BGMTransitInfo transitBgmInfo__arr54;
        [FieldOffset(10976)] public BGMTransitInfo transitBgmInfo__arr55;
        [FieldOffset(11024)] public BGMTransitInfo transitBgmInfo__arr56;
        [FieldOffset(11072)] public BGMTransitInfo transitBgmInfo__arr57;
        [FieldOffset(11120)] public BGMTransitInfo transitBgmInfo__arr58;
        [FieldOffset(11168)] public BGMTransitInfo transitBgmInfo__arr59;
        [FieldOffset(11216)] public BGMTransitInfo transitBgmInfo__arr60;
        [FieldOffset(11264)] public BGMTransitInfo transitBgmInfo__arr61;
        [FieldOffset(11312)] public BGMTransitInfo transitBgmInfo__arr62;
        [FieldOffset(11360)] public BGMTransitInfo transitBgmInfo__arr63;
        [FieldOffset(11408)] public BGMTransitInfo transitBgmInfo__arr64;
        [FieldOffset(11456)] public BGMTransitInfo transitBgmInfo__arr65;
        [FieldOffset(11504)] public BGMTransitInfo transitBgmInfo__arr66;
        [FieldOffset(11552)] public BGMTransitInfo transitBgmInfo__arr67;
        [FieldOffset(11600)] public BGMTransitInfo transitBgmInfo__arr68;
        [FieldOffset(11648)] public BGMTransitInfo transitBgmInfo__arr69;
        [FieldOffset(11696)] public BGMTransitInfo transitBgmInfo__arr70;
        [FieldOffset(11744)] public BGMTransitInfo transitBgmInfo__arr71;
        [FieldOffset(11792)] public BGMTransitInfo transitBgmInfo__arr72;
        [FieldOffset(11840)] public BGMTransitInfo transitBgmInfo__arr73;
        [FieldOffset(11888)] public BGMTransitInfo transitBgmInfo__arr74;
        [FieldOffset(11936)] public BGMTransitInfo transitBgmInfo__arr75;
        [FieldOffset(11984)] public BGMTransitInfo transitBgmInfo__arr76;
        [FieldOffset(12032)] public BGMTransitInfo transitBgmInfo__arr77;
        [FieldOffset(12080)] public BGMTransitInfo transitBgmInfo__arr78;
        [FieldOffset(12128)] public BGMTransitInfo transitBgmInfo__arr79;
        [FieldOffset(12176)] public BGMTransitInfo transitBgmInfo__arr80;
        [FieldOffset(12224)] public BGMTransitInfo transitBgmInfo__arr81;
        [FieldOffset(12272)] public BGMTransitInfo transitBgmInfo__arr82;
        [FieldOffset(12320)] public BGMTransitInfo transitBgmInfo__arr83;
        [FieldOffset(12368)] public BGMTransitInfo transitBgmInfo__arr84;
        [FieldOffset(12416)] public BGMTransitInfo transitBgmInfo__arr85;
        [FieldOffset(12464)] public BGMTransitInfo transitBgmInfo__arr86;
        [FieldOffset(12512)] public BGMTransitInfo transitBgmInfo__arr87;
        [FieldOffset(12560)] public BGMTransitInfo transitBgmInfo__arr88;
        [FieldOffset(12608)] public BGMTransitInfo transitBgmInfo__arr89;
        [FieldOffset(12656)] public BGMTransitInfo transitBgmInfo__arr90;
        [FieldOffset(12704)] public BGMTransitInfo transitBgmInfo__arr91;
        [FieldOffset(12752)] public BGMTransitInfo transitBgmInfo__arr92;
        [FieldOffset(12800)] public BGMTransitInfo transitBgmInfo__arr93;
        [FieldOffset(12848)] public BGMTransitInfo transitBgmInfo__arr94;
        [FieldOffset(12896)] public BGMTransitInfo transitBgmInfo__arr95;
        [FieldOffset(12944)] public BGMTransitInfo transitBgmInfo__arr96;
        [FieldOffset(12992)] public BGMTransitInfo transitBgmInfo__arr97;
        [FieldOffset(13040)] public BGMTransitInfo transitBgmInfo__arr98;
        [FieldOffset(13088)] public BGMTransitInfo transitBgmInfo__arr99;
        [FieldOffset(13136)] public BGMTransitInfo transitBgmInfo__arr100;
        [FieldOffset(13184)] public BGMTransitInfo transitBgmInfo__arr101;
        [FieldOffset(13232)] public BGMTransitInfo transitBgmInfo__arr102;
        [FieldOffset(13280)] public BGMTransitInfo transitBgmInfo__arr103;
        [FieldOffset(13328)] public BGMTransitInfo transitBgmInfo__arr104;
        [FieldOffset(13376)] public BGMTransitInfo transitBgmInfo__arr105;
        [FieldOffset(13424)] public BGMTransitInfo transitBgmInfo__arr106;
        [FieldOffset(13472)] public BGMTransitInfo transitBgmInfo__arr107;
        [FieldOffset(13520)] public BGMTransitInfo transitBgmInfo__arr108;
        [FieldOffset(13568)] public BGMTransitInfo transitBgmInfo__arr109;
        [FieldOffset(13616)] public BGMTransitInfo transitBgmInfo__arr110;
        [FieldOffset(13664)] public BGMTransitInfo transitBgmInfo__arr111;
        [FieldOffset(13712)] public BGMTransitInfo transitBgmInfo__arr112;
        [FieldOffset(13760)] public BGMTransitInfo transitBgmInfo__arr113;
        [FieldOffset(13808)] public BGMTransitInfo transitBgmInfo__arr114;
        [FieldOffset(13856)] public BGMTransitInfo transitBgmInfo__arr115;
        [FieldOffset(13904)] public BGMTransitInfo transitBgmInfo__arr116;
        [FieldOffset(13952)] public BGMTransitInfo transitBgmInfo__arr117;
        [FieldOffset(14000)] public BGMTransitInfo transitBgmInfo__arr118;
        [FieldOffset(14048)] public BGMTransitInfo transitBgmInfo__arr119;
        [FieldOffset(14096)] public BGMTransitInfo transitBgmInfo__arr120;
        [FieldOffset(14144)] public BGMTransitInfo transitBgmInfo__arr121;
        [FieldOffset(14192)] public BGMTransitInfo transitBgmInfo__arr122;
        [FieldOffset(14240)] public BGMTransitInfo transitBgmInfo__arr123;
        [FieldOffset(14288)] public BGMTransitInfo transitBgmInfo__arr124;
        [FieldOffset(14336)] public BGMTransitInfo transitBgmInfo__arr125;
        [FieldOffset(14384)] public BGMTransitInfo transitBgmInfo__arr126;
        [FieldOffset(14432)] public BGMTransitInfo transitBgmInfo__arr127;
    }

}