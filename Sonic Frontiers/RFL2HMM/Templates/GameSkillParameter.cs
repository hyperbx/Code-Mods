using System.Numerics;
using System.Runtime.InteropServices;

public class GameSkillParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 3)]
    public struct SkillParam
    {
        [FieldOffset(0)] public byte unlockPoint;
        [FieldOffset(1)] public byte addUnlockPoint;
        [FieldOffset(2)] public bool present;
    }

    public enum Value : sbyte
    {
        Cyloop = 0,
        Smash = 1,
        QuickCyloop = 2,
        AcceleLevel = 3,
        ChargeAttack = 4,
        RecoverySmash = 5,
        AirTrick = 6,
        SonicBoom = 7,
        Crasher = 8,
        LoopKick = 9,
        SpinSlash = 10,
        StompingAttack = 11,
        HomingShot = 12,
        CrossSlash = 13,
        AutoCombo = 14,
        Dummy0 = 15,
        Dummy1 = 16,
        Dummy2 = 17,
        Dummy3 = 18,
        Dummy4 = 19,
        Num = 20,
        NumUsed = 15,
        Invalid = -1
    }

    [StructLayout(LayoutKind.Explicit, Size = 3)]
    public struct SkillLinkSetting
    {
        [FieldOffset(0)] public bool down;
        [FieldOffset(1)] public bool left;
        [FieldOffset(2)] public bool right;
    }

    [StructLayout(LayoutKind.Explicit, Size = 5)]
    public struct SkillNodeParam
    {
        [FieldOffset(0)] public bool enable;
        [FieldOffset(1)] public Value skill;
        [FieldOffset(2)] public SkillLinkSetting link;
    }

    [StructLayout(LayoutKind.Explicit, Size = 151)]
    public struct SkillTreeParam
    {
        [FieldOffset(0)]   public SkillNodeParam nodeParams__arr0;
        [FieldOffset(5)] public SkillNodeParam nodeParams__arr1;
        [FieldOffset(10)] public SkillNodeParam nodeParams__arr2;
        [FieldOffset(15)] public SkillNodeParam nodeParams__arr3;
        [FieldOffset(20)] public SkillNodeParam nodeParams__arr4;
        [FieldOffset(25)] public SkillNodeParam nodeParams__arr5;
        [FieldOffset(30)] public SkillNodeParam nodeParams__arr6;
        [FieldOffset(35)] public SkillNodeParam nodeParams__arr7;
        [FieldOffset(40)] public SkillNodeParam nodeParams__arr8;
        [FieldOffset(45)] public SkillNodeParam nodeParams__arr9;
        [FieldOffset(50)] public SkillNodeParam nodeParams__arr10;
        [FieldOffset(55)] public SkillNodeParam nodeParams__arr11;
        [FieldOffset(60)] public SkillNodeParam nodeParams__arr12;
        [FieldOffset(65)] public SkillNodeParam nodeParams__arr13;
        [FieldOffset(70)] public SkillNodeParam nodeParams__arr14;
        [FieldOffset(75)] public SkillNodeParam nodeParams__arr15;
        [FieldOffset(80)] public SkillNodeParam nodeParams__arr16;
        [FieldOffset(85)] public SkillNodeParam nodeParams__arr17;
        [FieldOffset(90)] public SkillNodeParam nodeParams__arr18;
        [FieldOffset(95)] public SkillNodeParam nodeParams__arr19;
        [FieldOffset(100)] public SkillNodeParam nodeParams__arr20;
        [FieldOffset(105)] public SkillNodeParam nodeParams__arr21;
        [FieldOffset(110)] public SkillNodeParam nodeParams__arr22;
        [FieldOffset(115)] public SkillNodeParam nodeParams__arr23;
        [FieldOffset(120)] public SkillNodeParam nodeParams__arr24;
        [FieldOffset(125)] public SkillNodeParam nodeParams__arr25;
        [FieldOffset(130)] public SkillNodeParam nodeParams__arr26;
        [FieldOffset(135)] public SkillNodeParam nodeParams__arr27;
        [FieldOffset(140)] public SkillNodeParam nodeParams__arr28;
        [FieldOffset(145)] public SkillNodeParam nodeParams__arr29;
        [FieldOffset(150)] public sbyte startIndex;
    }

    [StructLayout(LayoutKind.Explicit, Size = 211)]
    public struct GameSkillParameter
    {
        [FieldOffset(0)]  public SkillParam skillParams__arr0;
        [FieldOffset(3)] public SkillParam skillParams__arr1;
        [FieldOffset(6)] public SkillParam skillParams__arr2;
        [FieldOffset(9)] public SkillParam skillParams__arr3;
        [FieldOffset(12)] public SkillParam skillParams__arr4;
        [FieldOffset(15)] public SkillParam skillParams__arr5;
        [FieldOffset(18)] public SkillParam skillParams__arr6;
        [FieldOffset(21)] public SkillParam skillParams__arr7;
        [FieldOffset(24)] public SkillParam skillParams__arr8;
        [FieldOffset(27)] public SkillParam skillParams__arr9;
        [FieldOffset(30)] public SkillParam skillParams__arr10;
        [FieldOffset(33)] public SkillParam skillParams__arr11;
        [FieldOffset(36)] public SkillParam skillParams__arr12;
        [FieldOffset(39)] public SkillParam skillParams__arr13;
        [FieldOffset(42)] public SkillParam skillParams__arr14;
        [FieldOffset(45)] public SkillParam skillParams__arr15;
        [FieldOffset(48)] public SkillParam skillParams__arr16;
        [FieldOffset(51)] public SkillParam skillParams__arr17;
        [FieldOffset(54)] public SkillParam skillParams__arr18;
        [FieldOffset(57)] public SkillParam skillParams__arr19;
        [FieldOffset(60)] public SkillTreeParam treeParams;
    }

}