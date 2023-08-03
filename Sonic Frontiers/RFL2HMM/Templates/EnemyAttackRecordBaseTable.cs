using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyAttackRecordBaseTableClass
{
    [StructLayout(LayoutKind.Explicit, Size = 1)]
    public struct Record
    {
        [FieldOffset(0)] public byte no;
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

    public enum Kind : sbyte
    {
        InvalidKind = -1,
        Dead_BattleJellymanLv1 = 0,
        Dead_BattleJellymanLv2 = 1,
        Dead_BattleJellymanLv3 = 2,
        Dead_BattleJellymanLv4 = 3,
        Dead_BattleWolf = 4,
        Dead_BattleBird = 5,
        Dead_BattleSniper = 6,
        Dead_BattleTwister = 7,
        Dead_BattleBommer = 8,
        Dead_BattleBubble = 9,
        Dead_BattleDefender = 10,
        Dead_BattleUmbrella = 11,
        Dead_BattleAquaBall = 12,
        Dead_BattleJumper = 13,
        Dead_BattleBladeLv1 = 14,
        Dead_BattleBladeLv2 = 15,
        Dead_BattleBladeLv3 = 16,
        Dead_BattleBladeLv4 = 17,
        Dead_BattleDarumaLv1 = 18,
        Dead_BattleDarumaLv2 = 19,
        Dead_BattleDarumaLv3 = 20,
        Dead_BattleDarumaLv4 = 21,
        Dead_BattleSpider = 22,
        Dead_BattleCharger = 23,
        Dead_BattleFlyer = 24,
        Dead_BattleTracker = 25,
        Dead_BattleAsura = 26,
        Dead_BattleSkier = 27,
        Dead_BattleTyrant = 28,
        Dead_BattleSumo = 29,
        Dead_BattleStrider = 30,
        Dead_BattleWarship = 31,
        Dead_BattleGiantFC = 32,
        Dead_BattleGiantClimb = 33,
        Dead_BattleGiant = 34,
        Dead_BattleDragonFC = 35,
        Dead_BattleDragonClimb = 36,
        Dead_BattleDragon = 37,
        Dead_BattleKnightFC = 38,
        Dead_BattleKnightClimb = 39,
        Dead_BattleKnight = 40,
        Dead_BattleRifle = 41,
        Dead_BattleTheEnd = 42,
        Dead_Gimmick = 43,
        Dead_Fall = 44,
        Dead_Water = 45,
        Dead_Lava = 46,
        Failed_QuestKodamaCollect1 = 47,
        Failed_QuestMowingGrass = 48,
        Failed_QuestKodamaEscort = 49,
        Failed_QuestKodamaCollect2 = 50,
        Failed_QuestDarumaBattle = 51,
        Failed_QuestCollectItem = 52,
        Failed_QuestDrawBridge = 53,
        Failed_PinBall = 54,
        Failed_Hacking = 55,
        Transit_ToIsland = 56,
        Transit_ToCyber = 57,
        Transit_ToFishing = 58,
        Transit_ToHacking = 59,
        Transit_ToTheEnd = 60,
        Transit_ToSkill1 = 61,
        Transit_ToSkill2 = 62,
        Transit_ToSkill3 = 63,
        Transit_ToSkill4 = 64,
        Transit_ToSkill5 = 65,
        Transit_ToSkill6 = 66,
        Transit_ToSkill7 = 67,
        Transit_ToSkill8 = 68,
        Transit_ToSkill9 = 69,
        Transit_ToSkill10 = 70,
        Transit_ToSkill11 = 71,
        Transit_ToSkill12 = 72,
        Transit_ToSkill13 = 73,
        Transit_ToSkill14 = 74,
        Transit_ToSkill15 = 75,
        Transit_ToSkill16 = 76,
        Transit_ToSkill17 = 77,
        Transit_ToSkill18 = 78,
        Transit_ToSkill19 = 79,
        Transit_ToSkill20 = 80,
        NumKinds = 81
    }

    [StructLayout(LayoutKind.Explicit, Size = 80)]
    public struct EnemyAttackRecord
    {
        [FieldOffset(0)]  public Record record;
        [FieldOffset(8)]  public CString name;
        [FieldOffset(24)] public int damage;
        [FieldOffset(28)] public float velocityX;
        [FieldOffset(32)] public float velocityY;
        [FieldOffset(40)] public CString hitStopName;
        [FieldOffset(56)] public CString cameraShakeName;
        [FieldOffset(72)] public Kind practice;
    }

    [StructLayout(LayoutKind.Explicit, Size = 15360)]
    public struct EnemyAttackRecordBaseTable
    {
        [FieldOffset(0)] public EnemyAttackRecord data__arr0;
        [FieldOffset(80)] public EnemyAttackRecord data__arr1;
        [FieldOffset(160)] public EnemyAttackRecord data__arr2;
        [FieldOffset(240)] public EnemyAttackRecord data__arr3;
        [FieldOffset(320)] public EnemyAttackRecord data__arr4;
        [FieldOffset(400)] public EnemyAttackRecord data__arr5;
        [FieldOffset(480)] public EnemyAttackRecord data__arr6;
        [FieldOffset(560)] public EnemyAttackRecord data__arr7;
        [FieldOffset(640)] public EnemyAttackRecord data__arr8;
        [FieldOffset(720)] public EnemyAttackRecord data__arr9;
        [FieldOffset(800)] public EnemyAttackRecord data__arr10;
        [FieldOffset(880)] public EnemyAttackRecord data__arr11;
        [FieldOffset(960)] public EnemyAttackRecord data__arr12;
        [FieldOffset(1040)] public EnemyAttackRecord data__arr13;
        [FieldOffset(1120)] public EnemyAttackRecord data__arr14;
        [FieldOffset(1200)] public EnemyAttackRecord data__arr15;
        [FieldOffset(1280)] public EnemyAttackRecord data__arr16;
        [FieldOffset(1360)] public EnemyAttackRecord data__arr17;
        [FieldOffset(1440)] public EnemyAttackRecord data__arr18;
        [FieldOffset(1520)] public EnemyAttackRecord data__arr19;
        [FieldOffset(1600)] public EnemyAttackRecord data__arr20;
        [FieldOffset(1680)] public EnemyAttackRecord data__arr21;
        [FieldOffset(1760)] public EnemyAttackRecord data__arr22;
        [FieldOffset(1840)] public EnemyAttackRecord data__arr23;
        [FieldOffset(1920)] public EnemyAttackRecord data__arr24;
        [FieldOffset(2000)] public EnemyAttackRecord data__arr25;
        [FieldOffset(2080)] public EnemyAttackRecord data__arr26;
        [FieldOffset(2160)] public EnemyAttackRecord data__arr27;
        [FieldOffset(2240)] public EnemyAttackRecord data__arr28;
        [FieldOffset(2320)] public EnemyAttackRecord data__arr29;
        [FieldOffset(2400)] public EnemyAttackRecord data__arr30;
        [FieldOffset(2480)] public EnemyAttackRecord data__arr31;
        [FieldOffset(2560)] public EnemyAttackRecord data__arr32;
        [FieldOffset(2640)] public EnemyAttackRecord data__arr33;
        [FieldOffset(2720)] public EnemyAttackRecord data__arr34;
        [FieldOffset(2800)] public EnemyAttackRecord data__arr35;
        [FieldOffset(2880)] public EnemyAttackRecord data__arr36;
        [FieldOffset(2960)] public EnemyAttackRecord data__arr37;
        [FieldOffset(3040)] public EnemyAttackRecord data__arr38;
        [FieldOffset(3120)] public EnemyAttackRecord data__arr39;
        [FieldOffset(3200)] public EnemyAttackRecord data__arr40;
        [FieldOffset(3280)] public EnemyAttackRecord data__arr41;
        [FieldOffset(3360)] public EnemyAttackRecord data__arr42;
        [FieldOffset(3440)] public EnemyAttackRecord data__arr43;
        [FieldOffset(3520)] public EnemyAttackRecord data__arr44;
        [FieldOffset(3600)] public EnemyAttackRecord data__arr45;
        [FieldOffset(3680)] public EnemyAttackRecord data__arr46;
        [FieldOffset(3760)] public EnemyAttackRecord data__arr47;
        [FieldOffset(3840)] public EnemyAttackRecord data__arr48;
        [FieldOffset(3920)] public EnemyAttackRecord data__arr49;
        [FieldOffset(4000)] public EnemyAttackRecord data__arr50;
        [FieldOffset(4080)] public EnemyAttackRecord data__arr51;
        [FieldOffset(4160)] public EnemyAttackRecord data__arr52;
        [FieldOffset(4240)] public EnemyAttackRecord data__arr53;
        [FieldOffset(4320)] public EnemyAttackRecord data__arr54;
        [FieldOffset(4400)] public EnemyAttackRecord data__arr55;
        [FieldOffset(4480)] public EnemyAttackRecord data__arr56;
        [FieldOffset(4560)] public EnemyAttackRecord data__arr57;
        [FieldOffset(4640)] public EnemyAttackRecord data__arr58;
        [FieldOffset(4720)] public EnemyAttackRecord data__arr59;
        [FieldOffset(4800)] public EnemyAttackRecord data__arr60;
        [FieldOffset(4880)] public EnemyAttackRecord data__arr61;
        [FieldOffset(4960)] public EnemyAttackRecord data__arr62;
        [FieldOffset(5040)] public EnemyAttackRecord data__arr63;
        [FieldOffset(5120)] public EnemyAttackRecord data__arr64;
        [FieldOffset(5200)] public EnemyAttackRecord data__arr65;
        [FieldOffset(5280)] public EnemyAttackRecord data__arr66;
        [FieldOffset(5360)] public EnemyAttackRecord data__arr67;
        [FieldOffset(5440)] public EnemyAttackRecord data__arr68;
        [FieldOffset(5520)] public EnemyAttackRecord data__arr69;
        [FieldOffset(5600)] public EnemyAttackRecord data__arr70;
        [FieldOffset(5680)] public EnemyAttackRecord data__arr71;
        [FieldOffset(5760)] public EnemyAttackRecord data__arr72;
        [FieldOffset(5840)] public EnemyAttackRecord data__arr73;
        [FieldOffset(5920)] public EnemyAttackRecord data__arr74;
        [FieldOffset(6000)] public EnemyAttackRecord data__arr75;
        [FieldOffset(6080)] public EnemyAttackRecord data__arr76;
        [FieldOffset(6160)] public EnemyAttackRecord data__arr77;
        [FieldOffset(6240)] public EnemyAttackRecord data__arr78;
        [FieldOffset(6320)] public EnemyAttackRecord data__arr79;
        [FieldOffset(6400)] public EnemyAttackRecord data__arr80;
        [FieldOffset(6480)] public EnemyAttackRecord data__arr81;
        [FieldOffset(6560)] public EnemyAttackRecord data__arr82;
        [FieldOffset(6640)] public EnemyAttackRecord data__arr83;
        [FieldOffset(6720)] public EnemyAttackRecord data__arr84;
        [FieldOffset(6800)] public EnemyAttackRecord data__arr85;
        [FieldOffset(6880)] public EnemyAttackRecord data__arr86;
        [FieldOffset(6960)] public EnemyAttackRecord data__arr87;
        [FieldOffset(7040)] public EnemyAttackRecord data__arr88;
        [FieldOffset(7120)] public EnemyAttackRecord data__arr89;
        [FieldOffset(7200)] public EnemyAttackRecord data__arr90;
        [FieldOffset(7280)] public EnemyAttackRecord data__arr91;
        [FieldOffset(7360)] public EnemyAttackRecord data__arr92;
        [FieldOffset(7440)] public EnemyAttackRecord data__arr93;
        [FieldOffset(7520)] public EnemyAttackRecord data__arr94;
        [FieldOffset(7600)] public EnemyAttackRecord data__arr95;
        [FieldOffset(7680)] public EnemyAttackRecord data__arr96;
        [FieldOffset(7760)] public EnemyAttackRecord data__arr97;
        [FieldOffset(7840)] public EnemyAttackRecord data__arr98;
        [FieldOffset(7920)] public EnemyAttackRecord data__arr99;
        [FieldOffset(8000)] public EnemyAttackRecord data__arr100;
        [FieldOffset(8080)] public EnemyAttackRecord data__arr101;
        [FieldOffset(8160)] public EnemyAttackRecord data__arr102;
        [FieldOffset(8240)] public EnemyAttackRecord data__arr103;
        [FieldOffset(8320)] public EnemyAttackRecord data__arr104;
        [FieldOffset(8400)] public EnemyAttackRecord data__arr105;
        [FieldOffset(8480)] public EnemyAttackRecord data__arr106;
        [FieldOffset(8560)] public EnemyAttackRecord data__arr107;
        [FieldOffset(8640)] public EnemyAttackRecord data__arr108;
        [FieldOffset(8720)] public EnemyAttackRecord data__arr109;
        [FieldOffset(8800)] public EnemyAttackRecord data__arr110;
        [FieldOffset(8880)] public EnemyAttackRecord data__arr111;
        [FieldOffset(8960)] public EnemyAttackRecord data__arr112;
        [FieldOffset(9040)] public EnemyAttackRecord data__arr113;
        [FieldOffset(9120)] public EnemyAttackRecord data__arr114;
        [FieldOffset(9200)] public EnemyAttackRecord data__arr115;
        [FieldOffset(9280)] public EnemyAttackRecord data__arr116;
        [FieldOffset(9360)] public EnemyAttackRecord data__arr117;
        [FieldOffset(9440)] public EnemyAttackRecord data__arr118;
        [FieldOffset(9520)] public EnemyAttackRecord data__arr119;
        [FieldOffset(9600)] public EnemyAttackRecord data__arr120;
        [FieldOffset(9680)] public EnemyAttackRecord data__arr121;
        [FieldOffset(9760)] public EnemyAttackRecord data__arr122;
        [FieldOffset(9840)] public EnemyAttackRecord data__arr123;
        [FieldOffset(9920)] public EnemyAttackRecord data__arr124;
        [FieldOffset(10000)] public EnemyAttackRecord data__arr125;
        [FieldOffset(10080)] public EnemyAttackRecord data__arr126;
        [FieldOffset(10160)] public EnemyAttackRecord data__arr127;
        [FieldOffset(10240)] public EnemyAttackRecord data__arr128;
        [FieldOffset(10320)] public EnemyAttackRecord data__arr129;
        [FieldOffset(10400)] public EnemyAttackRecord data__arr130;
        [FieldOffset(10480)] public EnemyAttackRecord data__arr131;
        [FieldOffset(10560)] public EnemyAttackRecord data__arr132;
        [FieldOffset(10640)] public EnemyAttackRecord data__arr133;
        [FieldOffset(10720)] public EnemyAttackRecord data__arr134;
        [FieldOffset(10800)] public EnemyAttackRecord data__arr135;
        [FieldOffset(10880)] public EnemyAttackRecord data__arr136;
        [FieldOffset(10960)] public EnemyAttackRecord data__arr137;
        [FieldOffset(11040)] public EnemyAttackRecord data__arr138;
        [FieldOffset(11120)] public EnemyAttackRecord data__arr139;
        [FieldOffset(11200)] public EnemyAttackRecord data__arr140;
        [FieldOffset(11280)] public EnemyAttackRecord data__arr141;
        [FieldOffset(11360)] public EnemyAttackRecord data__arr142;
        [FieldOffset(11440)] public EnemyAttackRecord data__arr143;
        [FieldOffset(11520)] public EnemyAttackRecord data__arr144;
        [FieldOffset(11600)] public EnemyAttackRecord data__arr145;
        [FieldOffset(11680)] public EnemyAttackRecord data__arr146;
        [FieldOffset(11760)] public EnemyAttackRecord data__arr147;
        [FieldOffset(11840)] public EnemyAttackRecord data__arr148;
        [FieldOffset(11920)] public EnemyAttackRecord data__arr149;
        [FieldOffset(12000)] public EnemyAttackRecord data__arr150;
        [FieldOffset(12080)] public EnemyAttackRecord data__arr151;
        [FieldOffset(12160)] public EnemyAttackRecord data__arr152;
        [FieldOffset(12240)] public EnemyAttackRecord data__arr153;
        [FieldOffset(12320)] public EnemyAttackRecord data__arr154;
        [FieldOffset(12400)] public EnemyAttackRecord data__arr155;
        [FieldOffset(12480)] public EnemyAttackRecord data__arr156;
        [FieldOffset(12560)] public EnemyAttackRecord data__arr157;
        [FieldOffset(12640)] public EnemyAttackRecord data__arr158;
        [FieldOffset(12720)] public EnemyAttackRecord data__arr159;
        [FieldOffset(12800)] public EnemyAttackRecord data__arr160;
        [FieldOffset(12880)] public EnemyAttackRecord data__arr161;
        [FieldOffset(12960)] public EnemyAttackRecord data__arr162;
        [FieldOffset(13040)] public EnemyAttackRecord data__arr163;
        [FieldOffset(13120)] public EnemyAttackRecord data__arr164;
        [FieldOffset(13200)] public EnemyAttackRecord data__arr165;
        [FieldOffset(13280)] public EnemyAttackRecord data__arr166;
        [FieldOffset(13360)] public EnemyAttackRecord data__arr167;
        [FieldOffset(13440)] public EnemyAttackRecord data__arr168;
        [FieldOffset(13520)] public EnemyAttackRecord data__arr169;
        [FieldOffset(13600)] public EnemyAttackRecord data__arr170;
        [FieldOffset(13680)] public EnemyAttackRecord data__arr171;
        [FieldOffset(13760)] public EnemyAttackRecord data__arr172;
        [FieldOffset(13840)] public EnemyAttackRecord data__arr173;
        [FieldOffset(13920)] public EnemyAttackRecord data__arr174;
        [FieldOffset(14000)] public EnemyAttackRecord data__arr175;
        [FieldOffset(14080)] public EnemyAttackRecord data__arr176;
        [FieldOffset(14160)] public EnemyAttackRecord data__arr177;
        [FieldOffset(14240)] public EnemyAttackRecord data__arr178;
        [FieldOffset(14320)] public EnemyAttackRecord data__arr179;
        [FieldOffset(14400)] public EnemyAttackRecord data__arr180;
        [FieldOffset(14480)] public EnemyAttackRecord data__arr181;
        [FieldOffset(14560)] public EnemyAttackRecord data__arr182;
        [FieldOffset(14640)] public EnemyAttackRecord data__arr183;
        [FieldOffset(14720)] public EnemyAttackRecord data__arr184;
        [FieldOffset(14800)] public EnemyAttackRecord data__arr185;
        [FieldOffset(14880)] public EnemyAttackRecord data__arr186;
        [FieldOffset(14960)] public EnemyAttackRecord data__arr187;
        [FieldOffset(15040)] public EnemyAttackRecord data__arr188;
        [FieldOffset(15120)] public EnemyAttackRecord data__arr189;
        [FieldOffset(15200)] public EnemyAttackRecord data__arr190;
        [FieldOffset(15280)] public EnemyAttackRecord data__arr191;
    }

}