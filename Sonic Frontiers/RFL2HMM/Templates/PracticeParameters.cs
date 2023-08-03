using System.Numerics;
using System.Runtime.InteropServices;

public class PracticeParametersClass
{
    public enum Checker : sbyte
    {
        InvalidChecker = -1,
        CountActions = 0,
        CountAirTrick = 1,
        CountControlCamera = 2,
        CountInfinityCombo = 3,
        CountFiveCombo = 4,
        NumCheckers = 5
    }

    public enum Type : byte
    {
        None = 0,
        ControlCamera = 1,
        Cyloop = 2,
        QuickCyloop = 3,
        FocusCamera = 4,
        Parry = 5,
        Avoid = 6,
        AcceleCombo = 7,
        Crasher = 8,
        HomingShot = 9,
        StompingAttack = 10,
        SonicBoom = 11,
        SpinSlash = 12,
        LoopKick = 13,
        CrossSlash = 14,
        ChargeAttack = 15,
        Smash = 16,
        RecoverySmash = 17,
        Jump = 18,
        DoubleJump = 19,
        HomingAttack = 20,
        Boost = 21,
        Stomping = 22,
        BoundStomping = 23,
        AirBoost = 24,
        QuickStep = 25,
        LightDash = 26,
        DropDash = 27,
        Sliding = 28,
        WallRun = 29,
        Discontinued = 30,
        AirTrick = 31,
        AirTrickEnd = 32,
        CancelHomingAttackBounceStomping = 33,
        CancelAirBoostStomping = 34,
        Squat = 35,
        SpinBoostCharge = 36,
        SpinBoost = 37,
        RunToSpinBoost = 38,
        Num = 39
    }

    public enum Judge : sbyte
    {
        Succeed = 0,
        Failed = 1,
        Skiped = 2,
        Waiting = 3,
        Unknown = 4,
        NumJudges = 5
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
    public struct PracticeAction
    {
        [FieldOffset(0)]  public Type action;
        [FieldOffset(1)]  public Judge dummy;
        [FieldOffset(8)]  public ulong skipableActions;
        [FieldOffset(16)] public CString label;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct PracticePrerequisite
    {
        [FieldOffset(0)]  public uint skill;
        [FieldOffset(8)]  public ulong clearedSubject;
        [FieldOffset(16)] public ulong clearedSubject2;
        [FieldOffset(24)] public ulong clearedSubject3;
        [FieldOffset(32)] public ulong clearedSubject4;
        [FieldOffset(40)] public bool unlockSpinBoost;
    }

    [StructLayout(LayoutKind.Explicit, Size = 264)]
    public struct PracticeSubject
    {
        [FieldOffset(0)]   public Checker checker;
        [FieldOffset(8)]   public PracticeAction actions__arr0;
        [FieldOffset(40)] public PracticeAction actions__arr1;
        [FieldOffset(72)] public PracticeAction actions__arr2;
        [FieldOffset(104)] public PracticeAction actions__arr3;
        [FieldOffset(136)] public PracticeAction actions__arr4;
        [FieldOffset(168)] public PracticeAction actions__arr5;
        [FieldOffset(200)] public int count;
        [FieldOffset(208)] public PracticePrerequisite prerequisite;
        [FieldOffset(256)] public byte options;
    }

    [StructLayout(LayoutKind.Explicit, Size = 160)]
    public struct PracticeText
    {
        [FieldOffset(0)] public CString labels__arr0;
        [FieldOffset(255)] public CString labels__arr1;
        [FieldOffset(510)] public CString labels__arr2;
        [FieldOffset(765)] public CString labels__arr3;
        [FieldOffset(1020)] public CString labels__arr4;
        [FieldOffset(1275)] public CString labels__arr5;
        [FieldOffset(1530)] public CString labels__arr6;
        [FieldOffset(1785)] public CString labels__arr7;
        [FieldOffset(2040)] public CString labels__arr8;
        [FieldOffset(2295)] public CString labels__arr9;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct PracticeTime
    {
        [FieldOffset(0)]  public float readyTime;
        [FieldOffset(4)]  public float countTime;
        [FieldOffset(8)]  public float subjectViewTime;
        [FieldOffset(12)] public float clearedPostTime;
        [FieldOffset(16)] public float fadeoutWaitTime;
        [FieldOffset(20)] public float rebuildWaitTime1;
        [FieldOffset(24)] public float rebuildWaitTime2;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct PracticeTipsPrerequisite
    {
        [FieldOffset(0)] public uint skill;
        [FieldOffset(4)] public bool tutorialCleared;
        [FieldOffset(5)] public bool unlockArcadeMode;
        [FieldOffset(6)] public bool unlockCyberPowerBoost;
        [FieldOffset(7)] public bool unlockVeryHardMode;
        [FieldOffset(8)] public bool unlockStrongNewGame;
        [FieldOffset(9)] public bool unlockSpinBoost;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct PracticeTips
    {
        [FieldOffset(0)] public PracticeTipsPrerequisite prerequisite;
    }

    [StructLayout(LayoutKind.Explicit, Size = 220)]
    public struct PracticeSet
    {
        [FieldOffset(0)]  public sbyte subjects__arr0;
        [FieldOffset(1)] public sbyte subjects__arr1;
        [FieldOffset(2)] public sbyte subjects__arr2;
        [FieldOffset(3)] public sbyte subjects__arr3;
        [FieldOffset(4)] public sbyte subjects__arr4;
        [FieldOffset(5)] public sbyte subjects__arr5;
        [FieldOffset(6)] public sbyte subjects__arr6;
        [FieldOffset(7)] public sbyte subjects__arr7;
        [FieldOffset(8)] public sbyte subjects__arr8;
        [FieldOffset(9)] public sbyte subjects__arr9;
        [FieldOffset(10)] public sbyte subjects__arr10;
        [FieldOffset(11)] public sbyte subjects__arr11;
        [FieldOffset(12)] public sbyte subjects__arr12;
        [FieldOffset(13)] public sbyte subjects__arr13;
        [FieldOffset(14)] public sbyte subjects__arr14;
        [FieldOffset(15)] public sbyte subjects__arr15;
        [FieldOffset(16)] public sbyte subjects__arr16;
        [FieldOffset(17)] public sbyte subjects__arr17;
        [FieldOffset(18)] public sbyte subjects__arr18;
        [FieldOffset(19)] public sbyte subjects__arr19;
        [FieldOffset(20)] public short tips__arr0;
        [FieldOffset(22)] public short tips__arr1;
        [FieldOffset(24)] public short tips__arr2;
        [FieldOffset(26)] public short tips__arr3;
        [FieldOffset(28)] public short tips__arr4;
        [FieldOffset(30)] public short tips__arr5;
        [FieldOffset(32)] public short tips__arr6;
        [FieldOffset(34)] public short tips__arr7;
        [FieldOffset(36)] public short tips__arr8;
        [FieldOffset(38)] public short tips__arr9;
        [FieldOffset(40)] public short tips__arr10;
        [FieldOffset(42)] public short tips__arr11;
        [FieldOffset(44)] public short tips__arr12;
        [FieldOffset(46)] public short tips__arr13;
        [FieldOffset(48)] public short tips__arr14;
        [FieldOffset(50)] public short tips__arr15;
        [FieldOffset(52)] public short tips__arr16;
        [FieldOffset(54)] public short tips__arr17;
        [FieldOffset(56)] public short tips__arr18;
        [FieldOffset(58)] public short tips__arr19;
        [FieldOffset(60)] public short tips__arr20;
        [FieldOffset(62)] public short tips__arr21;
        [FieldOffset(64)] public short tips__arr22;
        [FieldOffset(66)] public short tips__arr23;
        [FieldOffset(68)] public short tips__arr24;
        [FieldOffset(70)] public short tips__arr25;
        [FieldOffset(72)] public short tips__arr26;
        [FieldOffset(74)] public short tips__arr27;
        [FieldOffset(76)] public short tips__arr28;
        [FieldOffset(78)] public short tips__arr29;
        [FieldOffset(80)] public short tips__arr30;
        [FieldOffset(82)] public short tips__arr31;
        [FieldOffset(84)] public short tips__arr32;
        [FieldOffset(86)] public short tips__arr33;
        [FieldOffset(88)] public short tips__arr34;
        [FieldOffset(90)] public short tips__arr35;
        [FieldOffset(92)] public short tips__arr36;
        [FieldOffset(94)] public short tips__arr37;
        [FieldOffset(96)] public short tips__arr38;
        [FieldOffset(98)] public short tips__arr39;
        [FieldOffset(100)] public short tips__arr40;
        [FieldOffset(102)] public short tips__arr41;
        [FieldOffset(104)] public short tips__arr42;
        [FieldOffset(106)] public short tips__arr43;
        [FieldOffset(108)] public short tips__arr44;
        [FieldOffset(110)] public short tips__arr45;
        [FieldOffset(112)] public short tips__arr46;
        [FieldOffset(114)] public short tips__arr47;
        [FieldOffset(116)] public short tips__arr48;
        [FieldOffset(118)] public short tips__arr49;
        [FieldOffset(120)] public short tips__arr50;
        [FieldOffset(122)] public short tips__arr51;
        [FieldOffset(124)] public short tips__arr52;
        [FieldOffset(126)] public short tips__arr53;
        [FieldOffset(128)] public short tips__arr54;
        [FieldOffset(130)] public short tips__arr55;
        [FieldOffset(132)] public short tips__arr56;
        [FieldOffset(134)] public short tips__arr57;
        [FieldOffset(136)] public short tips__arr58;
        [FieldOffset(138)] public short tips__arr59;
        [FieldOffset(140)] public short tips__arr60;
        [FieldOffset(142)] public short tips__arr61;
        [FieldOffset(144)] public short tips__arr62;
        [FieldOffset(146)] public short tips__arr63;
        [FieldOffset(148)] public short tips__arr64;
        [FieldOffset(150)] public short tips__arr65;
        [FieldOffset(152)] public short tips__arr66;
        [FieldOffset(154)] public short tips__arr67;
        [FieldOffset(156)] public short tips__arr68;
        [FieldOffset(158)] public short tips__arr69;
        [FieldOffset(160)] public short tips__arr70;
        [FieldOffset(162)] public short tips__arr71;
        [FieldOffset(164)] public short tips__arr72;
        [FieldOffset(166)] public short tips__arr73;
        [FieldOffset(168)] public short tips__arr74;
        [FieldOffset(170)] public short tips__arr75;
        [FieldOffset(172)] public short tips__arr76;
        [FieldOffset(174)] public short tips__arr77;
        [FieldOffset(176)] public short tips__arr78;
        [FieldOffset(178)] public short tips__arr79;
        [FieldOffset(180)] public short tips__arr80;
        [FieldOffset(182)] public short tips__arr81;
        [FieldOffset(184)] public short tips__arr82;
        [FieldOffset(186)] public short tips__arr83;
        [FieldOffset(188)] public short tips__arr84;
        [FieldOffset(190)] public short tips__arr85;
        [FieldOffset(192)] public short tips__arr86;
        [FieldOffset(194)] public short tips__arr87;
        [FieldOffset(196)] public short tips__arr88;
        [FieldOffset(198)] public short tips__arr89;
        [FieldOffset(200)] public short tips__arr90;
        [FieldOffset(202)] public short tips__arr91;
        [FieldOffset(204)] public short tips__arr92;
        [FieldOffset(206)] public short tips__arr93;
        [FieldOffset(208)] public short tips__arr94;
        [FieldOffset(210)] public short tips__arr95;
        [FieldOffset(212)] public short tips__arr96;
        [FieldOffset(214)] public short tips__arr97;
        [FieldOffset(216)] public short tips__arr98;
        [FieldOffset(218)] public short tips__arr99;
    }

    [StructLayout(LayoutKind.Explicit, Size = 73888)]
    public struct PracticeParameters
    {
        [FieldOffset(0)]     public PracticeSubject subjects__arr0;
        [FieldOffset(264)] public PracticeSubject subjects__arr1;
        [FieldOffset(528)] public PracticeSubject subjects__arr2;
        [FieldOffset(792)] public PracticeSubject subjects__arr3;
        [FieldOffset(1056)] public PracticeSubject subjects__arr4;
        [FieldOffset(1320)] public PracticeSubject subjects__arr5;
        [FieldOffset(1584)] public PracticeSubject subjects__arr6;
        [FieldOffset(1848)] public PracticeSubject subjects__arr7;
        [FieldOffset(2112)] public PracticeSubject subjects__arr8;
        [FieldOffset(2376)] public PracticeSubject subjects__arr9;
        [FieldOffset(2640)] public PracticeSubject subjects__arr10;
        [FieldOffset(2904)] public PracticeSubject subjects__arr11;
        [FieldOffset(3168)] public PracticeSubject subjects__arr12;
        [FieldOffset(3432)] public PracticeSubject subjects__arr13;
        [FieldOffset(3696)] public PracticeSubject subjects__arr14;
        [FieldOffset(3960)] public PracticeSubject subjects__arr15;
        [FieldOffset(4224)] public PracticeSubject subjects__arr16;
        [FieldOffset(4488)] public PracticeSubject subjects__arr17;
        [FieldOffset(4752)] public PracticeSubject subjects__arr18;
        [FieldOffset(5016)] public PracticeSubject subjects__arr19;
        [FieldOffset(5280)] public PracticeSubject subjects__arr20;
        [FieldOffset(5544)] public PracticeSubject subjects__arr21;
        [FieldOffset(5808)] public PracticeSubject subjects__arr22;
        [FieldOffset(6072)] public PracticeSubject subjects__arr23;
        [FieldOffset(6336)] public PracticeSubject subjects__arr24;
        [FieldOffset(6600)] public PracticeSubject subjects__arr25;
        [FieldOffset(6864)] public PracticeSubject subjects__arr26;
        [FieldOffset(7128)] public PracticeSubject subjects__arr27;
        [FieldOffset(7392)] public PracticeSubject subjects__arr28;
        [FieldOffset(7656)] public PracticeSubject subjects__arr29;
        [FieldOffset(7920)] public PracticeSubject subjects__arr30;
        [FieldOffset(8184)] public PracticeSubject subjects__arr31;
        [FieldOffset(8448)] public PracticeSubject subjects__arr32;
        [FieldOffset(8712)] public PracticeSubject subjects__arr33;
        [FieldOffset(8976)] public PracticeSubject subjects__arr34;
        [FieldOffset(9240)] public PracticeSubject subjects__arr35;
        [FieldOffset(9504)] public PracticeSubject subjects__arr36;
        [FieldOffset(9768)] public PracticeSubject subjects__arr37;
        [FieldOffset(10032)] public PracticeSubject subjects__arr38;
        [FieldOffset(10296)] public PracticeSubject subjects__arr39;
        [FieldOffset(10560)] public PracticeSubject subjects__arr40;
        [FieldOffset(10824)] public PracticeSubject subjects__arr41;
        [FieldOffset(11088)] public PracticeSubject subjects__arr42;
        [FieldOffset(11352)] public PracticeSubject subjects__arr43;
        [FieldOffset(11616)] public PracticeSubject subjects__arr44;
        [FieldOffset(11880)] public PracticeSubject subjects__arr45;
        [FieldOffset(12144)] public PracticeSubject subjects__arr46;
        [FieldOffset(12408)] public PracticeSubject subjects__arr47;
        [FieldOffset(12672)] public PracticeSubject subjects__arr48;
        [FieldOffset(12936)] public PracticeSubject subjects__arr49;
        [FieldOffset(13200)] public PracticeSubject subjects__arr50;
        [FieldOffset(13464)] public PracticeSubject subjects__arr51;
        [FieldOffset(13728)] public PracticeSubject subjects__arr52;
        [FieldOffset(13992)] public PracticeSubject subjects__arr53;
        [FieldOffset(14256)] public PracticeSubject subjects__arr54;
        [FieldOffset(14520)] public PracticeSubject subjects__arr55;
        [FieldOffset(14784)] public PracticeSubject subjects__arr56;
        [FieldOffset(15048)] public PracticeSubject subjects__arr57;
        [FieldOffset(15312)] public PracticeSubject subjects__arr58;
        [FieldOffset(15576)] public PracticeSubject subjects__arr59;
        [FieldOffset(15840)] public PracticeSubject subjects__arr60;
        [FieldOffset(16104)] public PracticeSubject subjects__arr61;
        [FieldOffset(16368)] public PracticeSubject subjects__arr62;
        [FieldOffset(16632)] public PracticeSubject subjects__arr63;
        [FieldOffset(16896)] public PracticeSubject subjects__arr64;
        [FieldOffset(17160)] public PracticeSubject subjects__arr65;
        [FieldOffset(17424)] public PracticeSubject subjects__arr66;
        [FieldOffset(17688)] public PracticeSubject subjects__arr67;
        [FieldOffset(17952)] public PracticeSubject subjects__arr68;
        [FieldOffset(18216)] public PracticeSubject subjects__arr69;
        [FieldOffset(18480)] public PracticeSubject subjects__arr70;
        [FieldOffset(18744)] public PracticeSubject subjects__arr71;
        [FieldOffset(19008)] public PracticeSubject subjects__arr72;
        [FieldOffset(19272)] public PracticeSubject subjects__arr73;
        [FieldOffset(19536)] public PracticeSubject subjects__arr74;
        [FieldOffset(19800)] public PracticeSubject subjects__arr75;
        [FieldOffset(20064)] public PracticeSubject subjects__arr76;
        [FieldOffset(20328)] public PracticeSubject subjects__arr77;
        [FieldOffset(20592)] public PracticeSubject subjects__arr78;
        [FieldOffset(20856)] public PracticeSubject subjects__arr79;
        [FieldOffset(21120)] public PracticeSubject subjects__arr80;
        [FieldOffset(21384)] public PracticeSubject subjects__arr81;
        [FieldOffset(21648)] public PracticeSubject subjects__arr82;
        [FieldOffset(21912)] public PracticeSubject subjects__arr83;
        [FieldOffset(22176)] public PracticeSubject subjects__arr84;
        [FieldOffset(22440)] public PracticeSubject subjects__arr85;
        [FieldOffset(22704)] public PracticeSubject subjects__arr86;
        [FieldOffset(22968)] public PracticeSubject subjects__arr87;
        [FieldOffset(23232)] public PracticeSubject subjects__arr88;
        [FieldOffset(23496)] public PracticeSubject subjects__arr89;
        [FieldOffset(23760)] public PracticeSubject subjects__arr90;
        [FieldOffset(24024)] public PracticeSubject subjects__arr91;
        [FieldOffset(24288)] public PracticeSubject subjects__arr92;
        [FieldOffset(24552)] public PracticeSubject subjects__arr93;
        [FieldOffset(24816)] public PracticeSubject subjects__arr94;
        [FieldOffset(25080)] public PracticeSubject subjects__arr95;
        [FieldOffset(25344)] public PracticeSubject subjects__arr96;
        [FieldOffset(25608)] public PracticeSubject subjects__arr97;
        [FieldOffset(25872)] public PracticeSubject subjects__arr98;
        [FieldOffset(26136)] public PracticeSubject subjects__arr99;
        [FieldOffset(26400)] public PracticeSubject subjects__arr100;
        [FieldOffset(26664)] public PracticeSubject subjects__arr101;
        [FieldOffset(26928)] public PracticeSubject subjects__arr102;
        [FieldOffset(27192)] public PracticeSubject subjects__arr103;
        [FieldOffset(27456)] public PracticeSubject subjects__arr104;
        [FieldOffset(27720)] public PracticeSubject subjects__arr105;
        [FieldOffset(27984)] public PracticeSubject subjects__arr106;
        [FieldOffset(28248)] public PracticeSubject subjects__arr107;
        [FieldOffset(28512)] public PracticeSubject subjects__arr108;
        [FieldOffset(28776)] public PracticeSubject subjects__arr109;
        [FieldOffset(29040)] public PracticeSubject subjects__arr110;
        [FieldOffset(29304)] public PracticeSubject subjects__arr111;
        [FieldOffset(29568)] public PracticeSubject subjects__arr112;
        [FieldOffset(29832)] public PracticeSubject subjects__arr113;
        [FieldOffset(30096)] public PracticeSubject subjects__arr114;
        [FieldOffset(30360)] public PracticeSubject subjects__arr115;
        [FieldOffset(30624)] public PracticeSubject subjects__arr116;
        [FieldOffset(30888)] public PracticeSubject subjects__arr117;
        [FieldOffset(31152)] public PracticeSubject subjects__arr118;
        [FieldOffset(31416)] public PracticeSubject subjects__arr119;
        [FieldOffset(31680)] public PracticeSubject subjects__arr120;
        [FieldOffset(31944)] public PracticeSubject subjects__arr121;
        [FieldOffset(32208)] public PracticeSubject subjects__arr122;
        [FieldOffset(32472)] public PracticeSubject subjects__arr123;
        [FieldOffset(32736)] public PracticeSubject subjects__arr124;
        [FieldOffset(33000)] public PracticeSubject subjects__arr125;
        [FieldOffset(33264)] public PracticeSubject subjects__arr126;
        [FieldOffset(33528)] public PracticeSubject subjects__arr127;
        [FieldOffset(33792)] public PracticeSubject subjects__arr128;
        [FieldOffset(34056)] public PracticeSubject subjects__arr129;
        [FieldOffset(34320)] public PracticeSubject subjects__arr130;
        [FieldOffset(34584)] public PracticeSubject subjects__arr131;
        [FieldOffset(34848)] public PracticeSubject subjects__arr132;
        [FieldOffset(35112)] public PracticeSubject subjects__arr133;
        [FieldOffset(35376)] public PracticeSubject subjects__arr134;
        [FieldOffset(35640)] public PracticeSubject subjects__arr135;
        [FieldOffset(35904)] public PracticeSubject subjects__arr136;
        [FieldOffset(36168)] public PracticeSubject subjects__arr137;
        [FieldOffset(36432)] public PracticeSubject subjects__arr138;
        [FieldOffset(36696)] public PracticeSubject subjects__arr139;
        [FieldOffset(36960)] public PracticeSubject subjects__arr140;
        [FieldOffset(37224)] public PracticeSubject subjects__arr141;
        [FieldOffset(37488)] public PracticeSubject subjects__arr142;
        [FieldOffset(37752)] public PracticeSubject subjects__arr143;
        [FieldOffset(38016)] public PracticeSubject subjects__arr144;
        [FieldOffset(38280)] public PracticeSubject subjects__arr145;
        [FieldOffset(38544)] public PracticeSubject subjects__arr146;
        [FieldOffset(38808)] public PracticeSubject subjects__arr147;
        [FieldOffset(39072)] public PracticeSubject subjects__arr148;
        [FieldOffset(39336)] public PracticeSubject subjects__arr149;
        [FieldOffset(39600)] public PracticeSubject subjects__arr150;
        [FieldOffset(39864)] public PracticeSubject subjects__arr151;
        [FieldOffset(40128)] public PracticeSubject subjects__arr152;
        [FieldOffset(40392)] public PracticeSubject subjects__arr153;
        [FieldOffset(40656)] public PracticeSubject subjects__arr154;
        [FieldOffset(40920)] public PracticeSubject subjects__arr155;
        [FieldOffset(41184)] public PracticeSubject subjects__arr156;
        [FieldOffset(41448)] public PracticeSubject subjects__arr157;
        [FieldOffset(41712)] public PracticeSubject subjects__arr158;
        [FieldOffset(41976)] public PracticeSubject subjects__arr159;
        [FieldOffset(42240)] public PracticeSubject subjects__arr160;
        [FieldOffset(42504)] public PracticeSubject subjects__arr161;
        [FieldOffset(42768)] public PracticeSubject subjects__arr162;
        [FieldOffset(43032)] public PracticeSubject subjects__arr163;
        [FieldOffset(43296)] public PracticeSubject subjects__arr164;
        [FieldOffset(43560)] public PracticeSubject subjects__arr165;
        [FieldOffset(43824)] public PracticeSubject subjects__arr166;
        [FieldOffset(44088)] public PracticeSubject subjects__arr167;
        [FieldOffset(44352)] public PracticeSubject subjects__arr168;
        [FieldOffset(44616)] public PracticeSubject subjects__arr169;
        [FieldOffset(44880)] public PracticeSubject subjects__arr170;
        [FieldOffset(45144)] public PracticeSubject subjects__arr171;
        [FieldOffset(45408)] public PracticeSubject subjects__arr172;
        [FieldOffset(45672)] public PracticeSubject subjects__arr173;
        [FieldOffset(45936)] public PracticeSubject subjects__arr174;
        [FieldOffset(46200)] public PracticeSubject subjects__arr175;
        [FieldOffset(46464)] public PracticeSubject subjects__arr176;
        [FieldOffset(46728)] public PracticeSubject subjects__arr177;
        [FieldOffset(46992)] public PracticeSubject subjects__arr178;
        [FieldOffset(47256)] public PracticeSubject subjects__arr179;
        [FieldOffset(47520)] public PracticeSubject subjects__arr180;
        [FieldOffset(47784)] public PracticeSubject subjects__arr181;
        [FieldOffset(48048)] public PracticeSubject subjects__arr182;
        [FieldOffset(48312)] public PracticeSubject subjects__arr183;
        [FieldOffset(48576)] public PracticeSubject subjects__arr184;
        [FieldOffset(48840)] public PracticeSubject subjects__arr185;
        [FieldOffset(49104)] public PracticeSubject subjects__arr186;
        [FieldOffset(49368)] public PracticeSubject subjects__arr187;
        [FieldOffset(49632)] public PracticeSubject subjects__arr188;
        [FieldOffset(49896)] public PracticeSubject subjects__arr189;
        [FieldOffset(50160)] public PracticeSubject subjects__arr190;
        [FieldOffset(50424)] public PracticeSubject subjects__arr191;
        [FieldOffset(50688)] public PracticeSubject subjects__arr192;
        [FieldOffset(50952)] public PracticeSubject subjects__arr193;
        [FieldOffset(51216)] public PracticeSubject subjects__arr194;
        [FieldOffset(51480)] public PracticeSubject subjects__arr195;
        [FieldOffset(51744)] public PracticeSubject subjects__arr196;
        [FieldOffset(52008)] public PracticeSubject subjects__arr197;
        [FieldOffset(52272)] public PracticeSubject subjects__arr198;
        [FieldOffset(52536)] public PracticeSubject subjects__arr199;
        [FieldOffset(52800)] public PracticeText text;
        [FieldOffset(52960)] public PracticeTime time;
        [FieldOffset(52988)] public float notifyTime;
        [FieldOffset(52992)] public PracticeTips tips__arr0;
        [FieldOffset(53004)] public PracticeTips tips__arr1;
        [FieldOffset(53016)] public PracticeTips tips__arr2;
        [FieldOffset(53028)] public PracticeTips tips__arr3;
        [FieldOffset(53040)] public PracticeTips tips__arr4;
        [FieldOffset(53052)] public PracticeTips tips__arr5;
        [FieldOffset(53064)] public PracticeTips tips__arr6;
        [FieldOffset(53076)] public PracticeTips tips__arr7;
        [FieldOffset(53088)] public PracticeTips tips__arr8;
        [FieldOffset(53100)] public PracticeTips tips__arr9;
        [FieldOffset(53112)] public PracticeTips tips__arr10;
        [FieldOffset(53124)] public PracticeTips tips__arr11;
        [FieldOffset(53136)] public PracticeTips tips__arr12;
        [FieldOffset(53148)] public PracticeTips tips__arr13;
        [FieldOffset(53160)] public PracticeTips tips__arr14;
        [FieldOffset(53172)] public PracticeTips tips__arr15;
        [FieldOffset(53184)] public PracticeTips tips__arr16;
        [FieldOffset(53196)] public PracticeTips tips__arr17;
        [FieldOffset(53208)] public PracticeTips tips__arr18;
        [FieldOffset(53220)] public PracticeTips tips__arr19;
        [FieldOffset(53232)] public PracticeTips tips__arr20;
        [FieldOffset(53244)] public PracticeTips tips__arr21;
        [FieldOffset(53256)] public PracticeTips tips__arr22;
        [FieldOffset(53268)] public PracticeTips tips__arr23;
        [FieldOffset(53280)] public PracticeTips tips__arr24;
        [FieldOffset(53292)] public PracticeTips tips__arr25;
        [FieldOffset(53304)] public PracticeTips tips__arr26;
        [FieldOffset(53316)] public PracticeTips tips__arr27;
        [FieldOffset(53328)] public PracticeTips tips__arr28;
        [FieldOffset(53340)] public PracticeTips tips__arr29;
        [FieldOffset(53352)] public PracticeTips tips__arr30;
        [FieldOffset(53364)] public PracticeTips tips__arr31;
        [FieldOffset(53376)] public PracticeTips tips__arr32;
        [FieldOffset(53388)] public PracticeTips tips__arr33;
        [FieldOffset(53400)] public PracticeTips tips__arr34;
        [FieldOffset(53412)] public PracticeTips tips__arr35;
        [FieldOffset(53424)] public PracticeTips tips__arr36;
        [FieldOffset(53436)] public PracticeTips tips__arr37;
        [FieldOffset(53448)] public PracticeTips tips__arr38;
        [FieldOffset(53460)] public PracticeTips tips__arr39;
        [FieldOffset(53472)] public PracticeTips tips__arr40;
        [FieldOffset(53484)] public PracticeTips tips__arr41;
        [FieldOffset(53496)] public PracticeTips tips__arr42;
        [FieldOffset(53508)] public PracticeTips tips__arr43;
        [FieldOffset(53520)] public PracticeTips tips__arr44;
        [FieldOffset(53532)] public PracticeTips tips__arr45;
        [FieldOffset(53544)] public PracticeTips tips__arr46;
        [FieldOffset(53556)] public PracticeTips tips__arr47;
        [FieldOffset(53568)] public PracticeTips tips__arr48;
        [FieldOffset(53580)] public PracticeTips tips__arr49;
        [FieldOffset(53592)] public PracticeTips tips__arr50;
        [FieldOffset(53604)] public PracticeTips tips__arr51;
        [FieldOffset(53616)] public PracticeTips tips__arr52;
        [FieldOffset(53628)] public PracticeTips tips__arr53;
        [FieldOffset(53640)] public PracticeTips tips__arr54;
        [FieldOffset(53652)] public PracticeTips tips__arr55;
        [FieldOffset(53664)] public PracticeTips tips__arr56;
        [FieldOffset(53676)] public PracticeTips tips__arr57;
        [FieldOffset(53688)] public PracticeTips tips__arr58;
        [FieldOffset(53700)] public PracticeTips tips__arr59;
        [FieldOffset(53712)] public PracticeTips tips__arr60;
        [FieldOffset(53724)] public PracticeTips tips__arr61;
        [FieldOffset(53736)] public PracticeTips tips__arr62;
        [FieldOffset(53748)] public PracticeTips tips__arr63;
        [FieldOffset(53760)] public PracticeTips tips__arr64;
        [FieldOffset(53772)] public PracticeTips tips__arr65;
        [FieldOffset(53784)] public PracticeTips tips__arr66;
        [FieldOffset(53796)] public PracticeTips tips__arr67;
        [FieldOffset(53808)] public PracticeTips tips__arr68;
        [FieldOffset(53820)] public PracticeTips tips__arr69;
        [FieldOffset(53832)] public PracticeTips tips__arr70;
        [FieldOffset(53844)] public PracticeTips tips__arr71;
        [FieldOffset(53856)] public PracticeTips tips__arr72;
        [FieldOffset(53868)] public PracticeTips tips__arr73;
        [FieldOffset(53880)] public PracticeTips tips__arr74;
        [FieldOffset(53892)] public PracticeTips tips__arr75;
        [FieldOffset(53904)] public PracticeTips tips__arr76;
        [FieldOffset(53916)] public PracticeTips tips__arr77;
        [FieldOffset(53928)] public PracticeTips tips__arr78;
        [FieldOffset(53940)] public PracticeTips tips__arr79;
        [FieldOffset(53952)] public PracticeTips tips__arr80;
        [FieldOffset(53964)] public PracticeTips tips__arr81;
        [FieldOffset(53976)] public PracticeTips tips__arr82;
        [FieldOffset(53988)] public PracticeTips tips__arr83;
        [FieldOffset(54000)] public PracticeTips tips__arr84;
        [FieldOffset(54012)] public PracticeTips tips__arr85;
        [FieldOffset(54024)] public PracticeTips tips__arr86;
        [FieldOffset(54036)] public PracticeTips tips__arr87;
        [FieldOffset(54048)] public PracticeTips tips__arr88;
        [FieldOffset(54060)] public PracticeTips tips__arr89;
        [FieldOffset(54072)] public PracticeTips tips__arr90;
        [FieldOffset(54084)] public PracticeTips tips__arr91;
        [FieldOffset(54096)] public PracticeTips tips__arr92;
        [FieldOffset(54108)] public PracticeTips tips__arr93;
        [FieldOffset(54120)] public PracticeTips tips__arr94;
        [FieldOffset(54132)] public PracticeTips tips__arr95;
        [FieldOffset(54144)] public PracticeTips tips__arr96;
        [FieldOffset(54156)] public PracticeTips tips__arr97;
        [FieldOffset(54168)] public PracticeTips tips__arr98;
        [FieldOffset(54180)] public PracticeTips tips__arr99;
        [FieldOffset(54192)] public PracticeTips tips__arr100;
        [FieldOffset(54204)] public PracticeTips tips__arr101;
        [FieldOffset(54216)] public PracticeTips tips__arr102;
        [FieldOffset(54228)] public PracticeTips tips__arr103;
        [FieldOffset(54240)] public PracticeTips tips__arr104;
        [FieldOffset(54252)] public PracticeTips tips__arr105;
        [FieldOffset(54264)] public PracticeTips tips__arr106;
        [FieldOffset(54276)] public PracticeTips tips__arr107;
        [FieldOffset(54288)] public PracticeTips tips__arr108;
        [FieldOffset(54300)] public PracticeTips tips__arr109;
        [FieldOffset(54312)] public PracticeTips tips__arr110;
        [FieldOffset(54324)] public PracticeTips tips__arr111;
        [FieldOffset(54336)] public PracticeTips tips__arr112;
        [FieldOffset(54348)] public PracticeTips tips__arr113;
        [FieldOffset(54360)] public PracticeTips tips__arr114;
        [FieldOffset(54372)] public PracticeTips tips__arr115;
        [FieldOffset(54384)] public PracticeTips tips__arr116;
        [FieldOffset(54396)] public PracticeTips tips__arr117;
        [FieldOffset(54408)] public PracticeTips tips__arr118;
        [FieldOffset(54420)] public PracticeTips tips__arr119;
        [FieldOffset(54432)] public PracticeTips tips__arr120;
        [FieldOffset(54444)] public PracticeTips tips__arr121;
        [FieldOffset(54456)] public PracticeTips tips__arr122;
        [FieldOffset(54468)] public PracticeTips tips__arr123;
        [FieldOffset(54480)] public PracticeTips tips__arr124;
        [FieldOffset(54492)] public PracticeTips tips__arr125;
        [FieldOffset(54504)] public PracticeTips tips__arr126;
        [FieldOffset(54516)] public PracticeTips tips__arr127;
        [FieldOffset(54528)] public PracticeTips tips__arr128;
        [FieldOffset(54540)] public PracticeTips tips__arr129;
        [FieldOffset(54552)] public PracticeTips tips__arr130;
        [FieldOffset(54564)] public PracticeTips tips__arr131;
        [FieldOffset(54576)] public PracticeTips tips__arr132;
        [FieldOffset(54588)] public PracticeTips tips__arr133;
        [FieldOffset(54600)] public PracticeTips tips__arr134;
        [FieldOffset(54612)] public PracticeTips tips__arr135;
        [FieldOffset(54624)] public PracticeTips tips__arr136;
        [FieldOffset(54636)] public PracticeTips tips__arr137;
        [FieldOffset(54648)] public PracticeTips tips__arr138;
        [FieldOffset(54660)] public PracticeTips tips__arr139;
        [FieldOffset(54672)] public PracticeTips tips__arr140;
        [FieldOffset(54684)] public PracticeTips tips__arr141;
        [FieldOffset(54696)] public PracticeTips tips__arr142;
        [FieldOffset(54708)] public PracticeTips tips__arr143;
        [FieldOffset(54720)] public PracticeTips tips__arr144;
        [FieldOffset(54732)] public PracticeTips tips__arr145;
        [FieldOffset(54744)] public PracticeTips tips__arr146;
        [FieldOffset(54756)] public PracticeTips tips__arr147;
        [FieldOffset(54768)] public PracticeTips tips__arr148;
        [FieldOffset(54780)] public PracticeTips tips__arr149;
        [FieldOffset(54792)] public PracticeTips tips__arr150;
        [FieldOffset(54804)] public PracticeTips tips__arr151;
        [FieldOffset(54816)] public PracticeTips tips__arr152;
        [FieldOffset(54828)] public PracticeTips tips__arr153;
        [FieldOffset(54840)] public PracticeTips tips__arr154;
        [FieldOffset(54852)] public PracticeTips tips__arr155;
        [FieldOffset(54864)] public PracticeTips tips__arr156;
        [FieldOffset(54876)] public PracticeTips tips__arr157;
        [FieldOffset(54888)] public PracticeTips tips__arr158;
        [FieldOffset(54900)] public PracticeTips tips__arr159;
        [FieldOffset(54912)] public PracticeTips tips__arr160;
        [FieldOffset(54924)] public PracticeTips tips__arr161;
        [FieldOffset(54936)] public PracticeTips tips__arr162;
        [FieldOffset(54948)] public PracticeTips tips__arr163;
        [FieldOffset(54960)] public PracticeTips tips__arr164;
        [FieldOffset(54972)] public PracticeTips tips__arr165;
        [FieldOffset(54984)] public PracticeTips tips__arr166;
        [FieldOffset(54996)] public PracticeTips tips__arr167;
        [FieldOffset(55008)] public PracticeTips tips__arr168;
        [FieldOffset(55020)] public PracticeTips tips__arr169;
        [FieldOffset(55032)] public PracticeTips tips__arr170;
        [FieldOffset(55044)] public PracticeTips tips__arr171;
        [FieldOffset(55056)] public PracticeTips tips__arr172;
        [FieldOffset(55068)] public PracticeTips tips__arr173;
        [FieldOffset(55080)] public PracticeTips tips__arr174;
        [FieldOffset(55092)] public PracticeTips tips__arr175;
        [FieldOffset(55104)] public PracticeTips tips__arr176;
        [FieldOffset(55116)] public PracticeTips tips__arr177;
        [FieldOffset(55128)] public PracticeTips tips__arr178;
        [FieldOffset(55140)] public PracticeTips tips__arr179;
        [FieldOffset(55152)] public PracticeTips tips__arr180;
        [FieldOffset(55164)] public PracticeTips tips__arr181;
        [FieldOffset(55176)] public PracticeTips tips__arr182;
        [FieldOffset(55188)] public PracticeTips tips__arr183;
        [FieldOffset(55200)] public PracticeTips tips__arr184;
        [FieldOffset(55212)] public PracticeTips tips__arr185;
        [FieldOffset(55224)] public PracticeTips tips__arr186;
        [FieldOffset(55236)] public PracticeTips tips__arr187;
        [FieldOffset(55248)] public PracticeTips tips__arr188;
        [FieldOffset(55260)] public PracticeTips tips__arr189;
        [FieldOffset(55272)] public PracticeTips tips__arr190;
        [FieldOffset(55284)] public PracticeTips tips__arr191;
        [FieldOffset(55296)] public PracticeTips tips__arr192;
        [FieldOffset(55308)] public PracticeTips tips__arr193;
        [FieldOffset(55320)] public PracticeTips tips__arr194;
        [FieldOffset(55332)] public PracticeTips tips__arr195;
        [FieldOffset(55344)] public PracticeTips tips__arr196;
        [FieldOffset(55356)] public PracticeTips tips__arr197;
        [FieldOffset(55368)] public PracticeTips tips__arr198;
        [FieldOffset(55380)] public PracticeTips tips__arr199;
        [FieldOffset(55392)] public PracticeTips tips__arr200;
        [FieldOffset(55404)] public PracticeTips tips__arr201;
        [FieldOffset(55416)] public PracticeTips tips__arr202;
        [FieldOffset(55428)] public PracticeTips tips__arr203;
        [FieldOffset(55440)] public PracticeTips tips__arr204;
        [FieldOffset(55452)] public PracticeTips tips__arr205;
        [FieldOffset(55464)] public PracticeTips tips__arr206;
        [FieldOffset(55476)] public PracticeTips tips__arr207;
        [FieldOffset(55488)] public PracticeTips tips__arr208;
        [FieldOffset(55500)] public PracticeTips tips__arr209;
        [FieldOffset(55512)] public PracticeTips tips__arr210;
        [FieldOffset(55524)] public PracticeTips tips__arr211;
        [FieldOffset(55536)] public PracticeTips tips__arr212;
        [FieldOffset(55548)] public PracticeTips tips__arr213;
        [FieldOffset(55560)] public PracticeTips tips__arr214;
        [FieldOffset(55572)] public PracticeTips tips__arr215;
        [FieldOffset(55584)] public PracticeTips tips__arr216;
        [FieldOffset(55596)] public PracticeTips tips__arr217;
        [FieldOffset(55608)] public PracticeTips tips__arr218;
        [FieldOffset(55620)] public PracticeTips tips__arr219;
        [FieldOffset(55632)] public PracticeTips tips__arr220;
        [FieldOffset(55644)] public PracticeTips tips__arr221;
        [FieldOffset(55656)] public PracticeTips tips__arr222;
        [FieldOffset(55668)] public PracticeTips tips__arr223;
        [FieldOffset(55680)] public PracticeTips tips__arr224;
        [FieldOffset(55692)] public PracticeTips tips__arr225;
        [FieldOffset(55704)] public PracticeTips tips__arr226;
        [FieldOffset(55716)] public PracticeTips tips__arr227;
        [FieldOffset(55728)] public PracticeTips tips__arr228;
        [FieldOffset(55740)] public PracticeTips tips__arr229;
        [FieldOffset(55752)] public PracticeTips tips__arr230;
        [FieldOffset(55764)] public PracticeTips tips__arr231;
        [FieldOffset(55776)] public PracticeTips tips__arr232;
        [FieldOffset(55788)] public PracticeTips tips__arr233;
        [FieldOffset(55800)] public PracticeTips tips__arr234;
        [FieldOffset(55812)] public PracticeTips tips__arr235;
        [FieldOffset(55824)] public PracticeTips tips__arr236;
        [FieldOffset(55836)] public PracticeTips tips__arr237;
        [FieldOffset(55848)] public PracticeTips tips__arr238;
        [FieldOffset(55860)] public PracticeTips tips__arr239;
        [FieldOffset(55872)] public PracticeTips tips__arr240;
        [FieldOffset(55884)] public PracticeTips tips__arr241;
        [FieldOffset(55896)] public PracticeTips tips__arr242;
        [FieldOffset(55908)] public PracticeTips tips__arr243;
        [FieldOffset(55920)] public PracticeTips tips__arr244;
        [FieldOffset(55932)] public PracticeTips tips__arr245;
        [FieldOffset(55944)] public PracticeTips tips__arr246;
        [FieldOffset(55956)] public PracticeTips tips__arr247;
        [FieldOffset(55968)] public PracticeTips tips__arr248;
        [FieldOffset(55980)] public PracticeTips tips__arr249;
        [FieldOffset(55992)] public PracticeTips tips__arr250;
        [FieldOffset(56004)] public PracticeTips tips__arr251;
        [FieldOffset(56016)] public PracticeTips tips__arr252;
        [FieldOffset(56028)] public PracticeTips tips__arr253;
        [FieldOffset(56040)] public PracticeTips tips__arr254;
        [FieldOffset(56052)] public PracticeTips tips__arr255;
        [FieldOffset(56064)] public float tipsMinViewTime;
        [FieldOffset(56068)] public PracticeSet sets__arr0;
        [FieldOffset(56288)] public PracticeSet sets__arr1;
        [FieldOffset(56508)] public PracticeSet sets__arr2;
        [FieldOffset(56728)] public PracticeSet sets__arr3;
        [FieldOffset(56948)] public PracticeSet sets__arr4;
        [FieldOffset(57168)] public PracticeSet sets__arr5;
        [FieldOffset(57388)] public PracticeSet sets__arr6;
        [FieldOffset(57608)] public PracticeSet sets__arr7;
        [FieldOffset(57828)] public PracticeSet sets__arr8;
        [FieldOffset(58048)] public PracticeSet sets__arr9;
        [FieldOffset(58268)] public PracticeSet sets__arr10;
        [FieldOffset(58488)] public PracticeSet sets__arr11;
        [FieldOffset(58708)] public PracticeSet sets__arr12;
        [FieldOffset(58928)] public PracticeSet sets__arr13;
        [FieldOffset(59148)] public PracticeSet sets__arr14;
        [FieldOffset(59368)] public PracticeSet sets__arr15;
        [FieldOffset(59588)] public PracticeSet sets__arr16;
        [FieldOffset(59808)] public PracticeSet sets__arr17;
        [FieldOffset(60028)] public PracticeSet sets__arr18;
        [FieldOffset(60248)] public PracticeSet sets__arr19;
        [FieldOffset(60468)] public PracticeSet sets__arr20;
        [FieldOffset(60688)] public PracticeSet sets__arr21;
        [FieldOffset(60908)] public PracticeSet sets__arr22;
        [FieldOffset(61128)] public PracticeSet sets__arr23;
        [FieldOffset(61348)] public PracticeSet sets__arr24;
        [FieldOffset(61568)] public PracticeSet sets__arr25;
        [FieldOffset(61788)] public PracticeSet sets__arr26;
        [FieldOffset(62008)] public PracticeSet sets__arr27;
        [FieldOffset(62228)] public PracticeSet sets__arr28;
        [FieldOffset(62448)] public PracticeSet sets__arr29;
        [FieldOffset(62668)] public PracticeSet sets__arr30;
        [FieldOffset(62888)] public PracticeSet sets__arr31;
        [FieldOffset(63108)] public PracticeSet sets__arr32;
        [FieldOffset(63328)] public PracticeSet sets__arr33;
        [FieldOffset(63548)] public PracticeSet sets__arr34;
        [FieldOffset(63768)] public PracticeSet sets__arr35;
        [FieldOffset(63988)] public PracticeSet sets__arr36;
        [FieldOffset(64208)] public PracticeSet sets__arr37;
        [FieldOffset(64428)] public PracticeSet sets__arr38;
        [FieldOffset(64648)] public PracticeSet sets__arr39;
        [FieldOffset(64868)] public PracticeSet sets__arr40;
        [FieldOffset(65088)] public PracticeSet sets__arr41;
        [FieldOffset(65308)] public PracticeSet sets__arr42;
        [FieldOffset(65528)] public PracticeSet sets__arr43;
        [FieldOffset(65748)] public PracticeSet sets__arr44;
        [FieldOffset(65968)] public PracticeSet sets__arr45;
        [FieldOffset(66188)] public PracticeSet sets__arr46;
        [FieldOffset(66408)] public PracticeSet sets__arr47;
        [FieldOffset(66628)] public PracticeSet sets__arr48;
        [FieldOffset(66848)] public PracticeSet sets__arr49;
        [FieldOffset(67068)] public PracticeSet sets__arr50;
        [FieldOffset(67288)] public PracticeSet sets__arr51;
        [FieldOffset(67508)] public PracticeSet sets__arr52;
        [FieldOffset(67728)] public PracticeSet sets__arr53;
        [FieldOffset(67948)] public PracticeSet sets__arr54;
        [FieldOffset(68168)] public PracticeSet sets__arr55;
        [FieldOffset(68388)] public PracticeSet sets__arr56;
        [FieldOffset(68608)] public PracticeSet sets__arr57;
        [FieldOffset(68828)] public PracticeSet sets__arr58;
        [FieldOffset(69048)] public PracticeSet sets__arr59;
        [FieldOffset(69268)] public PracticeSet sets__arr60;
        [FieldOffset(69488)] public PracticeSet sets__arr61;
        [FieldOffset(69708)] public PracticeSet sets__arr62;
        [FieldOffset(69928)] public PracticeSet sets__arr63;
        [FieldOffset(70148)] public PracticeSet sets__arr64;
        [FieldOffset(70368)] public PracticeSet sets__arr65;
        [FieldOffset(70588)] public PracticeSet sets__arr66;
        [FieldOffset(70808)] public PracticeSet sets__arr67;
        [FieldOffset(71028)] public PracticeSet sets__arr68;
        [FieldOffset(71248)] public PracticeSet sets__arr69;
        [FieldOffset(71468)] public PracticeSet sets__arr70;
        [FieldOffset(71688)] public PracticeSet sets__arr71;
        [FieldOffset(71908)] public PracticeSet sets__arr72;
        [FieldOffset(72128)] public PracticeSet sets__arr73;
        [FieldOffset(72348)] public PracticeSet sets__arr74;
        [FieldOffset(72568)] public PracticeSet sets__arr75;
        [FieldOffset(72788)] public PracticeSet sets__arr76;
        [FieldOffset(73008)] public PracticeSet sets__arr77;
        [FieldOffset(73228)] public PracticeSet sets__arr78;
        [FieldOffset(73448)] public PracticeSet sets__arr79;
        [FieldOffset(73668)] public PracticeSet sets__arr80;
    }

}