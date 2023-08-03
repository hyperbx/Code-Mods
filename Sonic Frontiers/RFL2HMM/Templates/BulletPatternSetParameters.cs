using System.Numerics;
using System.Runtime.InteropServices;

public class BulletPatternSetParametersClass
{
    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct HackingBulletParameter
    {
        [FieldOffset(0)]  public float bulletRadius;
        [FieldOffset(4)]  public float bulletModelScale;
        [FieldOffset(8)]  public float bulletRadiusLastBoss;
        [FieldOffset(12)] public float bulletModelScaleLastBoss;
        [FieldOffset(16)] public float bulletModelOffsetRateLastBoss;
        [FieldOffset(20)] public float laserNormalRadius;
        [FieldOffset(24)] public float laserThickRadius;
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

    public enum Type : byte
    {
        BulletFixed = 0,
        BulletAimPlayer = 1,
        LaserNormal = 2,
        LaserThick = 3,
        LaserAimPlayer = 4
    }

    public enum ElementType : byte
    {
        Hacking1 = 0,
        Hacking2 = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct AnimationParameter
    {
        [FieldOffset(0)] public float angle;
        [FieldOffset(4)] public float time;
    }

    [StructLayout(LayoutKind.Explicit, Size = 104)]
    public struct BulletPatternParameter
    {
        [FieldOffset(0)]  public Type type;
        [FieldOffset(1)]  public ElementType element;
        [FieldOffset(4)]  public float startAngle;
        [FieldOffset(8)]  public float endAngle;
        [FieldOffset(12)] public byte shootNum;
        [FieldOffset(16)] public float shootSpeed;
        [FieldOffset(20)] public byte wayNum;
        [FieldOffset(24)] public float wayAngle;
        [FieldOffset(28)] public float laserLength;
        [FieldOffset(32)] public float lifeTime;
        [FieldOffset(36)] public bool animation;
        [FieldOffset(40)] public AnimationParameter animParam__arr0;
        [FieldOffset(48)] public AnimationParameter animParam__arr1;
        [FieldOffset(56)] public AnimationParameter animParam__arr2;
        [FieldOffset(64)] public AnimationParameter animParam__arr3;
        [FieldOffset(72)] public AnimationParameter animParam__arr4;
        [FieldOffset(80)] public AnimationParameter animParam__arr5;
        [FieldOffset(88)] public AnimationParameter animParam__arr6;
        [FieldOffset(96)] public AnimationParameter animParam__arr7;
    }

    [StructLayout(LayoutKind.Explicit, Size = 120)]
    public struct BulletPatternSetParameter
    {
        [FieldOffset(0)]  public CString name;
        [FieldOffset(16)] public BulletPatternParameter param;
    }

    [StructLayout(LayoutKind.Explicit, Size = 30752)]
    public struct BulletPatternSetParameters
    {
        [FieldOffset(0)]  public HackingBulletParameter bulletParam;
        [FieldOffset(32)] public BulletPatternSetParameter data__arr0;
        [FieldOffset(152)] public BulletPatternSetParameter data__arr1;
        [FieldOffset(272)] public BulletPatternSetParameter data__arr2;
        [FieldOffset(392)] public BulletPatternSetParameter data__arr3;
        [FieldOffset(512)] public BulletPatternSetParameter data__arr4;
        [FieldOffset(632)] public BulletPatternSetParameter data__arr5;
        [FieldOffset(752)] public BulletPatternSetParameter data__arr6;
        [FieldOffset(872)] public BulletPatternSetParameter data__arr7;
        [FieldOffset(992)] public BulletPatternSetParameter data__arr8;
        [FieldOffset(1112)] public BulletPatternSetParameter data__arr9;
        [FieldOffset(1232)] public BulletPatternSetParameter data__arr10;
        [FieldOffset(1352)] public BulletPatternSetParameter data__arr11;
        [FieldOffset(1472)] public BulletPatternSetParameter data__arr12;
        [FieldOffset(1592)] public BulletPatternSetParameter data__arr13;
        [FieldOffset(1712)] public BulletPatternSetParameter data__arr14;
        [FieldOffset(1832)] public BulletPatternSetParameter data__arr15;
        [FieldOffset(1952)] public BulletPatternSetParameter data__arr16;
        [FieldOffset(2072)] public BulletPatternSetParameter data__arr17;
        [FieldOffset(2192)] public BulletPatternSetParameter data__arr18;
        [FieldOffset(2312)] public BulletPatternSetParameter data__arr19;
        [FieldOffset(2432)] public BulletPatternSetParameter data__arr20;
        [FieldOffset(2552)] public BulletPatternSetParameter data__arr21;
        [FieldOffset(2672)] public BulletPatternSetParameter data__arr22;
        [FieldOffset(2792)] public BulletPatternSetParameter data__arr23;
        [FieldOffset(2912)] public BulletPatternSetParameter data__arr24;
        [FieldOffset(3032)] public BulletPatternSetParameter data__arr25;
        [FieldOffset(3152)] public BulletPatternSetParameter data__arr26;
        [FieldOffset(3272)] public BulletPatternSetParameter data__arr27;
        [FieldOffset(3392)] public BulletPatternSetParameter data__arr28;
        [FieldOffset(3512)] public BulletPatternSetParameter data__arr29;
        [FieldOffset(3632)] public BulletPatternSetParameter data__arr30;
        [FieldOffset(3752)] public BulletPatternSetParameter data__arr31;
        [FieldOffset(3872)] public BulletPatternSetParameter data__arr32;
        [FieldOffset(3992)] public BulletPatternSetParameter data__arr33;
        [FieldOffset(4112)] public BulletPatternSetParameter data__arr34;
        [FieldOffset(4232)] public BulletPatternSetParameter data__arr35;
        [FieldOffset(4352)] public BulletPatternSetParameter data__arr36;
        [FieldOffset(4472)] public BulletPatternSetParameter data__arr37;
        [FieldOffset(4592)] public BulletPatternSetParameter data__arr38;
        [FieldOffset(4712)] public BulletPatternSetParameter data__arr39;
        [FieldOffset(4832)] public BulletPatternSetParameter data__arr40;
        [FieldOffset(4952)] public BulletPatternSetParameter data__arr41;
        [FieldOffset(5072)] public BulletPatternSetParameter data__arr42;
        [FieldOffset(5192)] public BulletPatternSetParameter data__arr43;
        [FieldOffset(5312)] public BulletPatternSetParameter data__arr44;
        [FieldOffset(5432)] public BulletPatternSetParameter data__arr45;
        [FieldOffset(5552)] public BulletPatternSetParameter data__arr46;
        [FieldOffset(5672)] public BulletPatternSetParameter data__arr47;
        [FieldOffset(5792)] public BulletPatternSetParameter data__arr48;
        [FieldOffset(5912)] public BulletPatternSetParameter data__arr49;
        [FieldOffset(6032)] public BulletPatternSetParameter data__arr50;
        [FieldOffset(6152)] public BulletPatternSetParameter data__arr51;
        [FieldOffset(6272)] public BulletPatternSetParameter data__arr52;
        [FieldOffset(6392)] public BulletPatternSetParameter data__arr53;
        [FieldOffset(6512)] public BulletPatternSetParameter data__arr54;
        [FieldOffset(6632)] public BulletPatternSetParameter data__arr55;
        [FieldOffset(6752)] public BulletPatternSetParameter data__arr56;
        [FieldOffset(6872)] public BulletPatternSetParameter data__arr57;
        [FieldOffset(6992)] public BulletPatternSetParameter data__arr58;
        [FieldOffset(7112)] public BulletPatternSetParameter data__arr59;
        [FieldOffset(7232)] public BulletPatternSetParameter data__arr60;
        [FieldOffset(7352)] public BulletPatternSetParameter data__arr61;
        [FieldOffset(7472)] public BulletPatternSetParameter data__arr62;
        [FieldOffset(7592)] public BulletPatternSetParameter data__arr63;
        [FieldOffset(7712)] public BulletPatternSetParameter data__arr64;
        [FieldOffset(7832)] public BulletPatternSetParameter data__arr65;
        [FieldOffset(7952)] public BulletPatternSetParameter data__arr66;
        [FieldOffset(8072)] public BulletPatternSetParameter data__arr67;
        [FieldOffset(8192)] public BulletPatternSetParameter data__arr68;
        [FieldOffset(8312)] public BulletPatternSetParameter data__arr69;
        [FieldOffset(8432)] public BulletPatternSetParameter data__arr70;
        [FieldOffset(8552)] public BulletPatternSetParameter data__arr71;
        [FieldOffset(8672)] public BulletPatternSetParameter data__arr72;
        [FieldOffset(8792)] public BulletPatternSetParameter data__arr73;
        [FieldOffset(8912)] public BulletPatternSetParameter data__arr74;
        [FieldOffset(9032)] public BulletPatternSetParameter data__arr75;
        [FieldOffset(9152)] public BulletPatternSetParameter data__arr76;
        [FieldOffset(9272)] public BulletPatternSetParameter data__arr77;
        [FieldOffset(9392)] public BulletPatternSetParameter data__arr78;
        [FieldOffset(9512)] public BulletPatternSetParameter data__arr79;
        [FieldOffset(9632)] public BulletPatternSetParameter data__arr80;
        [FieldOffset(9752)] public BulletPatternSetParameter data__arr81;
        [FieldOffset(9872)] public BulletPatternSetParameter data__arr82;
        [FieldOffset(9992)] public BulletPatternSetParameter data__arr83;
        [FieldOffset(10112)] public BulletPatternSetParameter data__arr84;
        [FieldOffset(10232)] public BulletPatternSetParameter data__arr85;
        [FieldOffset(10352)] public BulletPatternSetParameter data__arr86;
        [FieldOffset(10472)] public BulletPatternSetParameter data__arr87;
        [FieldOffset(10592)] public BulletPatternSetParameter data__arr88;
        [FieldOffset(10712)] public BulletPatternSetParameter data__arr89;
        [FieldOffset(10832)] public BulletPatternSetParameter data__arr90;
        [FieldOffset(10952)] public BulletPatternSetParameter data__arr91;
        [FieldOffset(11072)] public BulletPatternSetParameter data__arr92;
        [FieldOffset(11192)] public BulletPatternSetParameter data__arr93;
        [FieldOffset(11312)] public BulletPatternSetParameter data__arr94;
        [FieldOffset(11432)] public BulletPatternSetParameter data__arr95;
        [FieldOffset(11552)] public BulletPatternSetParameter data__arr96;
        [FieldOffset(11672)] public BulletPatternSetParameter data__arr97;
        [FieldOffset(11792)] public BulletPatternSetParameter data__arr98;
        [FieldOffset(11912)] public BulletPatternSetParameter data__arr99;
        [FieldOffset(12032)] public BulletPatternSetParameter data__arr100;
        [FieldOffset(12152)] public BulletPatternSetParameter data__arr101;
        [FieldOffset(12272)] public BulletPatternSetParameter data__arr102;
        [FieldOffset(12392)] public BulletPatternSetParameter data__arr103;
        [FieldOffset(12512)] public BulletPatternSetParameter data__arr104;
        [FieldOffset(12632)] public BulletPatternSetParameter data__arr105;
        [FieldOffset(12752)] public BulletPatternSetParameter data__arr106;
        [FieldOffset(12872)] public BulletPatternSetParameter data__arr107;
        [FieldOffset(12992)] public BulletPatternSetParameter data__arr108;
        [FieldOffset(13112)] public BulletPatternSetParameter data__arr109;
        [FieldOffset(13232)] public BulletPatternSetParameter data__arr110;
        [FieldOffset(13352)] public BulletPatternSetParameter data__arr111;
        [FieldOffset(13472)] public BulletPatternSetParameter data__arr112;
        [FieldOffset(13592)] public BulletPatternSetParameter data__arr113;
        [FieldOffset(13712)] public BulletPatternSetParameter data__arr114;
        [FieldOffset(13832)] public BulletPatternSetParameter data__arr115;
        [FieldOffset(13952)] public BulletPatternSetParameter data__arr116;
        [FieldOffset(14072)] public BulletPatternSetParameter data__arr117;
        [FieldOffset(14192)] public BulletPatternSetParameter data__arr118;
        [FieldOffset(14312)] public BulletPatternSetParameter data__arr119;
        [FieldOffset(14432)] public BulletPatternSetParameter data__arr120;
        [FieldOffset(14552)] public BulletPatternSetParameter data__arr121;
        [FieldOffset(14672)] public BulletPatternSetParameter data__arr122;
        [FieldOffset(14792)] public BulletPatternSetParameter data__arr123;
        [FieldOffset(14912)] public BulletPatternSetParameter data__arr124;
        [FieldOffset(15032)] public BulletPatternSetParameter data__arr125;
        [FieldOffset(15152)] public BulletPatternSetParameter data__arr126;
        [FieldOffset(15272)] public BulletPatternSetParameter data__arr127;
        [FieldOffset(15392)] public BulletPatternSetParameter data__arr128;
        [FieldOffset(15512)] public BulletPatternSetParameter data__arr129;
        [FieldOffset(15632)] public BulletPatternSetParameter data__arr130;
        [FieldOffset(15752)] public BulletPatternSetParameter data__arr131;
        [FieldOffset(15872)] public BulletPatternSetParameter data__arr132;
        [FieldOffset(15992)] public BulletPatternSetParameter data__arr133;
        [FieldOffset(16112)] public BulletPatternSetParameter data__arr134;
        [FieldOffset(16232)] public BulletPatternSetParameter data__arr135;
        [FieldOffset(16352)] public BulletPatternSetParameter data__arr136;
        [FieldOffset(16472)] public BulletPatternSetParameter data__arr137;
        [FieldOffset(16592)] public BulletPatternSetParameter data__arr138;
        [FieldOffset(16712)] public BulletPatternSetParameter data__arr139;
        [FieldOffset(16832)] public BulletPatternSetParameter data__arr140;
        [FieldOffset(16952)] public BulletPatternSetParameter data__arr141;
        [FieldOffset(17072)] public BulletPatternSetParameter data__arr142;
        [FieldOffset(17192)] public BulletPatternSetParameter data__arr143;
        [FieldOffset(17312)] public BulletPatternSetParameter data__arr144;
        [FieldOffset(17432)] public BulletPatternSetParameter data__arr145;
        [FieldOffset(17552)] public BulletPatternSetParameter data__arr146;
        [FieldOffset(17672)] public BulletPatternSetParameter data__arr147;
        [FieldOffset(17792)] public BulletPatternSetParameter data__arr148;
        [FieldOffset(17912)] public BulletPatternSetParameter data__arr149;
        [FieldOffset(18032)] public BulletPatternSetParameter data__arr150;
        [FieldOffset(18152)] public BulletPatternSetParameter data__arr151;
        [FieldOffset(18272)] public BulletPatternSetParameter data__arr152;
        [FieldOffset(18392)] public BulletPatternSetParameter data__arr153;
        [FieldOffset(18512)] public BulletPatternSetParameter data__arr154;
        [FieldOffset(18632)] public BulletPatternSetParameter data__arr155;
        [FieldOffset(18752)] public BulletPatternSetParameter data__arr156;
        [FieldOffset(18872)] public BulletPatternSetParameter data__arr157;
        [FieldOffset(18992)] public BulletPatternSetParameter data__arr158;
        [FieldOffset(19112)] public BulletPatternSetParameter data__arr159;
        [FieldOffset(19232)] public BulletPatternSetParameter data__arr160;
        [FieldOffset(19352)] public BulletPatternSetParameter data__arr161;
        [FieldOffset(19472)] public BulletPatternSetParameter data__arr162;
        [FieldOffset(19592)] public BulletPatternSetParameter data__arr163;
        [FieldOffset(19712)] public BulletPatternSetParameter data__arr164;
        [FieldOffset(19832)] public BulletPatternSetParameter data__arr165;
        [FieldOffset(19952)] public BulletPatternSetParameter data__arr166;
        [FieldOffset(20072)] public BulletPatternSetParameter data__arr167;
        [FieldOffset(20192)] public BulletPatternSetParameter data__arr168;
        [FieldOffset(20312)] public BulletPatternSetParameter data__arr169;
        [FieldOffset(20432)] public BulletPatternSetParameter data__arr170;
        [FieldOffset(20552)] public BulletPatternSetParameter data__arr171;
        [FieldOffset(20672)] public BulletPatternSetParameter data__arr172;
        [FieldOffset(20792)] public BulletPatternSetParameter data__arr173;
        [FieldOffset(20912)] public BulletPatternSetParameter data__arr174;
        [FieldOffset(21032)] public BulletPatternSetParameter data__arr175;
        [FieldOffset(21152)] public BulletPatternSetParameter data__arr176;
        [FieldOffset(21272)] public BulletPatternSetParameter data__arr177;
        [FieldOffset(21392)] public BulletPatternSetParameter data__arr178;
        [FieldOffset(21512)] public BulletPatternSetParameter data__arr179;
        [FieldOffset(21632)] public BulletPatternSetParameter data__arr180;
        [FieldOffset(21752)] public BulletPatternSetParameter data__arr181;
        [FieldOffset(21872)] public BulletPatternSetParameter data__arr182;
        [FieldOffset(21992)] public BulletPatternSetParameter data__arr183;
        [FieldOffset(22112)] public BulletPatternSetParameter data__arr184;
        [FieldOffset(22232)] public BulletPatternSetParameter data__arr185;
        [FieldOffset(22352)] public BulletPatternSetParameter data__arr186;
        [FieldOffset(22472)] public BulletPatternSetParameter data__arr187;
        [FieldOffset(22592)] public BulletPatternSetParameter data__arr188;
        [FieldOffset(22712)] public BulletPatternSetParameter data__arr189;
        [FieldOffset(22832)] public BulletPatternSetParameter data__arr190;
        [FieldOffset(22952)] public BulletPatternSetParameter data__arr191;
        [FieldOffset(23072)] public BulletPatternSetParameter data__arr192;
        [FieldOffset(23192)] public BulletPatternSetParameter data__arr193;
        [FieldOffset(23312)] public BulletPatternSetParameter data__arr194;
        [FieldOffset(23432)] public BulletPatternSetParameter data__arr195;
        [FieldOffset(23552)] public BulletPatternSetParameter data__arr196;
        [FieldOffset(23672)] public BulletPatternSetParameter data__arr197;
        [FieldOffset(23792)] public BulletPatternSetParameter data__arr198;
        [FieldOffset(23912)] public BulletPatternSetParameter data__arr199;
        [FieldOffset(24032)] public BulletPatternSetParameter data__arr200;
        [FieldOffset(24152)] public BulletPatternSetParameter data__arr201;
        [FieldOffset(24272)] public BulletPatternSetParameter data__arr202;
        [FieldOffset(24392)] public BulletPatternSetParameter data__arr203;
        [FieldOffset(24512)] public BulletPatternSetParameter data__arr204;
        [FieldOffset(24632)] public BulletPatternSetParameter data__arr205;
        [FieldOffset(24752)] public BulletPatternSetParameter data__arr206;
        [FieldOffset(24872)] public BulletPatternSetParameter data__arr207;
        [FieldOffset(24992)] public BulletPatternSetParameter data__arr208;
        [FieldOffset(25112)] public BulletPatternSetParameter data__arr209;
        [FieldOffset(25232)] public BulletPatternSetParameter data__arr210;
        [FieldOffset(25352)] public BulletPatternSetParameter data__arr211;
        [FieldOffset(25472)] public BulletPatternSetParameter data__arr212;
        [FieldOffset(25592)] public BulletPatternSetParameter data__arr213;
        [FieldOffset(25712)] public BulletPatternSetParameter data__arr214;
        [FieldOffset(25832)] public BulletPatternSetParameter data__arr215;
        [FieldOffset(25952)] public BulletPatternSetParameter data__arr216;
        [FieldOffset(26072)] public BulletPatternSetParameter data__arr217;
        [FieldOffset(26192)] public BulletPatternSetParameter data__arr218;
        [FieldOffset(26312)] public BulletPatternSetParameter data__arr219;
        [FieldOffset(26432)] public BulletPatternSetParameter data__arr220;
        [FieldOffset(26552)] public BulletPatternSetParameter data__arr221;
        [FieldOffset(26672)] public BulletPatternSetParameter data__arr222;
        [FieldOffset(26792)] public BulletPatternSetParameter data__arr223;
        [FieldOffset(26912)] public BulletPatternSetParameter data__arr224;
        [FieldOffset(27032)] public BulletPatternSetParameter data__arr225;
        [FieldOffset(27152)] public BulletPatternSetParameter data__arr226;
        [FieldOffset(27272)] public BulletPatternSetParameter data__arr227;
        [FieldOffset(27392)] public BulletPatternSetParameter data__arr228;
        [FieldOffset(27512)] public BulletPatternSetParameter data__arr229;
        [FieldOffset(27632)] public BulletPatternSetParameter data__arr230;
        [FieldOffset(27752)] public BulletPatternSetParameter data__arr231;
        [FieldOffset(27872)] public BulletPatternSetParameter data__arr232;
        [FieldOffset(27992)] public BulletPatternSetParameter data__arr233;
        [FieldOffset(28112)] public BulletPatternSetParameter data__arr234;
        [FieldOffset(28232)] public BulletPatternSetParameter data__arr235;
        [FieldOffset(28352)] public BulletPatternSetParameter data__arr236;
        [FieldOffset(28472)] public BulletPatternSetParameter data__arr237;
        [FieldOffset(28592)] public BulletPatternSetParameter data__arr238;
        [FieldOffset(28712)] public BulletPatternSetParameter data__arr239;
        [FieldOffset(28832)] public BulletPatternSetParameter data__arr240;
        [FieldOffset(28952)] public BulletPatternSetParameter data__arr241;
        [FieldOffset(29072)] public BulletPatternSetParameter data__arr242;
        [FieldOffset(29192)] public BulletPatternSetParameter data__arr243;
        [FieldOffset(29312)] public BulletPatternSetParameter data__arr244;
        [FieldOffset(29432)] public BulletPatternSetParameter data__arr245;
        [FieldOffset(29552)] public BulletPatternSetParameter data__arr246;
        [FieldOffset(29672)] public BulletPatternSetParameter data__arr247;
        [FieldOffset(29792)] public BulletPatternSetParameter data__arr248;
        [FieldOffset(29912)] public BulletPatternSetParameter data__arr249;
        [FieldOffset(30032)] public BulletPatternSetParameter data__arr250;
        [FieldOffset(30152)] public BulletPatternSetParameter data__arr251;
        [FieldOffset(30272)] public BulletPatternSetParameter data__arr252;
        [FieldOffset(30392)] public BulletPatternSetParameter data__arr253;
        [FieldOffset(30512)] public BulletPatternSetParameter data__arr254;
        [FieldOffset(30632)] public BulletPatternSetParameter data__arr255;
    }

}