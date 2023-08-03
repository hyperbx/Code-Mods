using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyDefenceRecordTableClass
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

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct EnemyDefenceRecord
    {
        [FieldOffset(0)]  public Record record;
        [FieldOffset(8)]  public CString name;
        [FieldOffset(24)] public float baseRate;
        [FieldOffset(28)] public float slashRate;
        [FieldOffset(32)] public float quickRate;
        [FieldOffset(36)] public float stunRate;
        [FieldOffset(40)] public float staggerRate;
    }

    [StructLayout(LayoutKind.Explicit, Size = 6144)]
    public struct EnemyDefenceRecordTable
    {
        [FieldOffset(0)] public EnemyDefenceRecord data__arr0;
        [FieldOffset(48)] public EnemyDefenceRecord data__arr1;
        [FieldOffset(96)] public EnemyDefenceRecord data__arr2;
        [FieldOffset(144)] public EnemyDefenceRecord data__arr3;
        [FieldOffset(192)] public EnemyDefenceRecord data__arr4;
        [FieldOffset(240)] public EnemyDefenceRecord data__arr5;
        [FieldOffset(288)] public EnemyDefenceRecord data__arr6;
        [FieldOffset(336)] public EnemyDefenceRecord data__arr7;
        [FieldOffset(384)] public EnemyDefenceRecord data__arr8;
        [FieldOffset(432)] public EnemyDefenceRecord data__arr9;
        [FieldOffset(480)] public EnemyDefenceRecord data__arr10;
        [FieldOffset(528)] public EnemyDefenceRecord data__arr11;
        [FieldOffset(576)] public EnemyDefenceRecord data__arr12;
        [FieldOffset(624)] public EnemyDefenceRecord data__arr13;
        [FieldOffset(672)] public EnemyDefenceRecord data__arr14;
        [FieldOffset(720)] public EnemyDefenceRecord data__arr15;
        [FieldOffset(768)] public EnemyDefenceRecord data__arr16;
        [FieldOffset(816)] public EnemyDefenceRecord data__arr17;
        [FieldOffset(864)] public EnemyDefenceRecord data__arr18;
        [FieldOffset(912)] public EnemyDefenceRecord data__arr19;
        [FieldOffset(960)] public EnemyDefenceRecord data__arr20;
        [FieldOffset(1008)] public EnemyDefenceRecord data__arr21;
        [FieldOffset(1056)] public EnemyDefenceRecord data__arr22;
        [FieldOffset(1104)] public EnemyDefenceRecord data__arr23;
        [FieldOffset(1152)] public EnemyDefenceRecord data__arr24;
        [FieldOffset(1200)] public EnemyDefenceRecord data__arr25;
        [FieldOffset(1248)] public EnemyDefenceRecord data__arr26;
        [FieldOffset(1296)] public EnemyDefenceRecord data__arr27;
        [FieldOffset(1344)] public EnemyDefenceRecord data__arr28;
        [FieldOffset(1392)] public EnemyDefenceRecord data__arr29;
        [FieldOffset(1440)] public EnemyDefenceRecord data__arr30;
        [FieldOffset(1488)] public EnemyDefenceRecord data__arr31;
        [FieldOffset(1536)] public EnemyDefenceRecord data__arr32;
        [FieldOffset(1584)] public EnemyDefenceRecord data__arr33;
        [FieldOffset(1632)] public EnemyDefenceRecord data__arr34;
        [FieldOffset(1680)] public EnemyDefenceRecord data__arr35;
        [FieldOffset(1728)] public EnemyDefenceRecord data__arr36;
        [FieldOffset(1776)] public EnemyDefenceRecord data__arr37;
        [FieldOffset(1824)] public EnemyDefenceRecord data__arr38;
        [FieldOffset(1872)] public EnemyDefenceRecord data__arr39;
        [FieldOffset(1920)] public EnemyDefenceRecord data__arr40;
        [FieldOffset(1968)] public EnemyDefenceRecord data__arr41;
        [FieldOffset(2016)] public EnemyDefenceRecord data__arr42;
        [FieldOffset(2064)] public EnemyDefenceRecord data__arr43;
        [FieldOffset(2112)] public EnemyDefenceRecord data__arr44;
        [FieldOffset(2160)] public EnemyDefenceRecord data__arr45;
        [FieldOffset(2208)] public EnemyDefenceRecord data__arr46;
        [FieldOffset(2256)] public EnemyDefenceRecord data__arr47;
        [FieldOffset(2304)] public EnemyDefenceRecord data__arr48;
        [FieldOffset(2352)] public EnemyDefenceRecord data__arr49;
        [FieldOffset(2400)] public EnemyDefenceRecord data__arr50;
        [FieldOffset(2448)] public EnemyDefenceRecord data__arr51;
        [FieldOffset(2496)] public EnemyDefenceRecord data__arr52;
        [FieldOffset(2544)] public EnemyDefenceRecord data__arr53;
        [FieldOffset(2592)] public EnemyDefenceRecord data__arr54;
        [FieldOffset(2640)] public EnemyDefenceRecord data__arr55;
        [FieldOffset(2688)] public EnemyDefenceRecord data__arr56;
        [FieldOffset(2736)] public EnemyDefenceRecord data__arr57;
        [FieldOffset(2784)] public EnemyDefenceRecord data__arr58;
        [FieldOffset(2832)] public EnemyDefenceRecord data__arr59;
        [FieldOffset(2880)] public EnemyDefenceRecord data__arr60;
        [FieldOffset(2928)] public EnemyDefenceRecord data__arr61;
        [FieldOffset(2976)] public EnemyDefenceRecord data__arr62;
        [FieldOffset(3024)] public EnemyDefenceRecord data__arr63;
        [FieldOffset(3072)] public EnemyDefenceRecord data__arr64;
        [FieldOffset(3120)] public EnemyDefenceRecord data__arr65;
        [FieldOffset(3168)] public EnemyDefenceRecord data__arr66;
        [FieldOffset(3216)] public EnemyDefenceRecord data__arr67;
        [FieldOffset(3264)] public EnemyDefenceRecord data__arr68;
        [FieldOffset(3312)] public EnemyDefenceRecord data__arr69;
        [FieldOffset(3360)] public EnemyDefenceRecord data__arr70;
        [FieldOffset(3408)] public EnemyDefenceRecord data__arr71;
        [FieldOffset(3456)] public EnemyDefenceRecord data__arr72;
        [FieldOffset(3504)] public EnemyDefenceRecord data__arr73;
        [FieldOffset(3552)] public EnemyDefenceRecord data__arr74;
        [FieldOffset(3600)] public EnemyDefenceRecord data__arr75;
        [FieldOffset(3648)] public EnemyDefenceRecord data__arr76;
        [FieldOffset(3696)] public EnemyDefenceRecord data__arr77;
        [FieldOffset(3744)] public EnemyDefenceRecord data__arr78;
        [FieldOffset(3792)] public EnemyDefenceRecord data__arr79;
        [FieldOffset(3840)] public EnemyDefenceRecord data__arr80;
        [FieldOffset(3888)] public EnemyDefenceRecord data__arr81;
        [FieldOffset(3936)] public EnemyDefenceRecord data__arr82;
        [FieldOffset(3984)] public EnemyDefenceRecord data__arr83;
        [FieldOffset(4032)] public EnemyDefenceRecord data__arr84;
        [FieldOffset(4080)] public EnemyDefenceRecord data__arr85;
        [FieldOffset(4128)] public EnemyDefenceRecord data__arr86;
        [FieldOffset(4176)] public EnemyDefenceRecord data__arr87;
        [FieldOffset(4224)] public EnemyDefenceRecord data__arr88;
        [FieldOffset(4272)] public EnemyDefenceRecord data__arr89;
        [FieldOffset(4320)] public EnemyDefenceRecord data__arr90;
        [FieldOffset(4368)] public EnemyDefenceRecord data__arr91;
        [FieldOffset(4416)] public EnemyDefenceRecord data__arr92;
        [FieldOffset(4464)] public EnemyDefenceRecord data__arr93;
        [FieldOffset(4512)] public EnemyDefenceRecord data__arr94;
        [FieldOffset(4560)] public EnemyDefenceRecord data__arr95;
        [FieldOffset(4608)] public EnemyDefenceRecord data__arr96;
        [FieldOffset(4656)] public EnemyDefenceRecord data__arr97;
        [FieldOffset(4704)] public EnemyDefenceRecord data__arr98;
        [FieldOffset(4752)] public EnemyDefenceRecord data__arr99;
        [FieldOffset(4800)] public EnemyDefenceRecord data__arr100;
        [FieldOffset(4848)] public EnemyDefenceRecord data__arr101;
        [FieldOffset(4896)] public EnemyDefenceRecord data__arr102;
        [FieldOffset(4944)] public EnemyDefenceRecord data__arr103;
        [FieldOffset(4992)] public EnemyDefenceRecord data__arr104;
        [FieldOffset(5040)] public EnemyDefenceRecord data__arr105;
        [FieldOffset(5088)] public EnemyDefenceRecord data__arr106;
        [FieldOffset(5136)] public EnemyDefenceRecord data__arr107;
        [FieldOffset(5184)] public EnemyDefenceRecord data__arr108;
        [FieldOffset(5232)] public EnemyDefenceRecord data__arr109;
        [FieldOffset(5280)] public EnemyDefenceRecord data__arr110;
        [FieldOffset(5328)] public EnemyDefenceRecord data__arr111;
        [FieldOffset(5376)] public EnemyDefenceRecord data__arr112;
        [FieldOffset(5424)] public EnemyDefenceRecord data__arr113;
        [FieldOffset(5472)] public EnemyDefenceRecord data__arr114;
        [FieldOffset(5520)] public EnemyDefenceRecord data__arr115;
        [FieldOffset(5568)] public EnemyDefenceRecord data__arr116;
        [FieldOffset(5616)] public EnemyDefenceRecord data__arr117;
        [FieldOffset(5664)] public EnemyDefenceRecord data__arr118;
        [FieldOffset(5712)] public EnemyDefenceRecord data__arr119;
        [FieldOffset(5760)] public EnemyDefenceRecord data__arr120;
        [FieldOffset(5808)] public EnemyDefenceRecord data__arr121;
        [FieldOffset(5856)] public EnemyDefenceRecord data__arr122;
        [FieldOffset(5904)] public EnemyDefenceRecord data__arr123;
        [FieldOffset(5952)] public EnemyDefenceRecord data__arr124;
        [FieldOffset(6000)] public EnemyDefenceRecord data__arr125;
        [FieldOffset(6048)] public EnemyDefenceRecord data__arr126;
        [FieldOffset(6096)] public EnemyDefenceRecord data__arr127;
    }

}