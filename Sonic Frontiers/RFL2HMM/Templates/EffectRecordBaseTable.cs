using System.Numerics;
using System.Runtime.InteropServices;

public class EffectRecordBaseTableClass
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

    [StructLayout(LayoutKind.Explicit, Size = 88)]
    public struct EffectRecord
    {
        [FieldOffset(0)] public Record record;
        [FieldOffset(8)] public CString emitterSetName__arr0;
        [FieldOffset(263)] public CString emitterSetName__arr1;
        [FieldOffset(518)] public CString emitterSetName__arr2;
        [FieldOffset(773)] public CString emitterSetName__arr3;
        [FieldOffset(1028)] public CString emitterSetName__arr4;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8800)]
    public struct EffectRecordBaseTable
    {
        [FieldOffset(0)] public EffectRecord data__arr0;
        [FieldOffset(88)] public EffectRecord data__arr1;
        [FieldOffset(176)] public EffectRecord data__arr2;
        [FieldOffset(264)] public EffectRecord data__arr3;
        [FieldOffset(352)] public EffectRecord data__arr4;
        [FieldOffset(440)] public EffectRecord data__arr5;
        [FieldOffset(528)] public EffectRecord data__arr6;
        [FieldOffset(616)] public EffectRecord data__arr7;
        [FieldOffset(704)] public EffectRecord data__arr8;
        [FieldOffset(792)] public EffectRecord data__arr9;
        [FieldOffset(880)] public EffectRecord data__arr10;
        [FieldOffset(968)] public EffectRecord data__arr11;
        [FieldOffset(1056)] public EffectRecord data__arr12;
        [FieldOffset(1144)] public EffectRecord data__arr13;
        [FieldOffset(1232)] public EffectRecord data__arr14;
        [FieldOffset(1320)] public EffectRecord data__arr15;
        [FieldOffset(1408)] public EffectRecord data__arr16;
        [FieldOffset(1496)] public EffectRecord data__arr17;
        [FieldOffset(1584)] public EffectRecord data__arr18;
        [FieldOffset(1672)] public EffectRecord data__arr19;
        [FieldOffset(1760)] public EffectRecord data__arr20;
        [FieldOffset(1848)] public EffectRecord data__arr21;
        [FieldOffset(1936)] public EffectRecord data__arr22;
        [FieldOffset(2024)] public EffectRecord data__arr23;
        [FieldOffset(2112)] public EffectRecord data__arr24;
        [FieldOffset(2200)] public EffectRecord data__arr25;
        [FieldOffset(2288)] public EffectRecord data__arr26;
        [FieldOffset(2376)] public EffectRecord data__arr27;
        [FieldOffset(2464)] public EffectRecord data__arr28;
        [FieldOffset(2552)] public EffectRecord data__arr29;
        [FieldOffset(2640)] public EffectRecord data__arr30;
        [FieldOffset(2728)] public EffectRecord data__arr31;
        [FieldOffset(2816)] public EffectRecord data__arr32;
        [FieldOffset(2904)] public EffectRecord data__arr33;
        [FieldOffset(2992)] public EffectRecord data__arr34;
        [FieldOffset(3080)] public EffectRecord data__arr35;
        [FieldOffset(3168)] public EffectRecord data__arr36;
        [FieldOffset(3256)] public EffectRecord data__arr37;
        [FieldOffset(3344)] public EffectRecord data__arr38;
        [FieldOffset(3432)] public EffectRecord data__arr39;
        [FieldOffset(3520)] public EffectRecord data__arr40;
        [FieldOffset(3608)] public EffectRecord data__arr41;
        [FieldOffset(3696)] public EffectRecord data__arr42;
        [FieldOffset(3784)] public EffectRecord data__arr43;
        [FieldOffset(3872)] public EffectRecord data__arr44;
        [FieldOffset(3960)] public EffectRecord data__arr45;
        [FieldOffset(4048)] public EffectRecord data__arr46;
        [FieldOffset(4136)] public EffectRecord data__arr47;
        [FieldOffset(4224)] public EffectRecord data__arr48;
        [FieldOffset(4312)] public EffectRecord data__arr49;
        [FieldOffset(4400)] public EffectRecord data__arr50;
        [FieldOffset(4488)] public EffectRecord data__arr51;
        [FieldOffset(4576)] public EffectRecord data__arr52;
        [FieldOffset(4664)] public EffectRecord data__arr53;
        [FieldOffset(4752)] public EffectRecord data__arr54;
        [FieldOffset(4840)] public EffectRecord data__arr55;
        [FieldOffset(4928)] public EffectRecord data__arr56;
        [FieldOffset(5016)] public EffectRecord data__arr57;
        [FieldOffset(5104)] public EffectRecord data__arr58;
        [FieldOffset(5192)] public EffectRecord data__arr59;
        [FieldOffset(5280)] public EffectRecord data__arr60;
        [FieldOffset(5368)] public EffectRecord data__arr61;
        [FieldOffset(5456)] public EffectRecord data__arr62;
        [FieldOffset(5544)] public EffectRecord data__arr63;
        [FieldOffset(5632)] public EffectRecord data__arr64;
        [FieldOffset(5720)] public EffectRecord data__arr65;
        [FieldOffset(5808)] public EffectRecord data__arr66;
        [FieldOffset(5896)] public EffectRecord data__arr67;
        [FieldOffset(5984)] public EffectRecord data__arr68;
        [FieldOffset(6072)] public EffectRecord data__arr69;
        [FieldOffset(6160)] public EffectRecord data__arr70;
        [FieldOffset(6248)] public EffectRecord data__arr71;
        [FieldOffset(6336)] public EffectRecord data__arr72;
        [FieldOffset(6424)] public EffectRecord data__arr73;
        [FieldOffset(6512)] public EffectRecord data__arr74;
        [FieldOffset(6600)] public EffectRecord data__arr75;
        [FieldOffset(6688)] public EffectRecord data__arr76;
        [FieldOffset(6776)] public EffectRecord data__arr77;
        [FieldOffset(6864)] public EffectRecord data__arr78;
        [FieldOffset(6952)] public EffectRecord data__arr79;
        [FieldOffset(7040)] public EffectRecord data__arr80;
        [FieldOffset(7128)] public EffectRecord data__arr81;
        [FieldOffset(7216)] public EffectRecord data__arr82;
        [FieldOffset(7304)] public EffectRecord data__arr83;
        [FieldOffset(7392)] public EffectRecord data__arr84;
        [FieldOffset(7480)] public EffectRecord data__arr85;
        [FieldOffset(7568)] public EffectRecord data__arr86;
        [FieldOffset(7656)] public EffectRecord data__arr87;
        [FieldOffset(7744)] public EffectRecord data__arr88;
        [FieldOffset(7832)] public EffectRecord data__arr89;
        [FieldOffset(7920)] public EffectRecord data__arr90;
        [FieldOffset(8008)] public EffectRecord data__arr91;
        [FieldOffset(8096)] public EffectRecord data__arr92;
        [FieldOffset(8184)] public EffectRecord data__arr93;
        [FieldOffset(8272)] public EffectRecord data__arr94;
        [FieldOffset(8360)] public EffectRecord data__arr95;
        [FieldOffset(8448)] public EffectRecord data__arr96;
        [FieldOffset(8536)] public EffectRecord data__arr97;
        [FieldOffset(8624)] public EffectRecord data__arr98;
        [FieldOffset(8712)] public EffectRecord data__arr99;
    }

}