using System.Numerics;
using System.Runtime.InteropServices;

public class QuestDrawBridgeParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct QuestDrawBridgeTimerParameter
    {
        [FieldOffset(0)]  public float timeLimitSeconds;
        [FieldOffset(4)]  public float cautionTime;
        [FieldOffset(8)]  public float warningTime;
        [FieldOffset(12)] public bool useCautionAnimation;
        [FieldOffset(13)] public bool useWarningAnimation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct QuestDrawBridgeParameterElement
    {
        [FieldOffset(0)] public int applicableFailedCount;
        [FieldOffset(4)] public QuestDrawBridgeTimerParameter timerParam;
    }

    [StructLayout(LayoutKind.Explicit, Size = 60)]
    public struct QuestDrawBridgeParameter
    {
        [FieldOffset(0)] public QuestDrawBridgeParameterElement element__arr0;
        [FieldOffset(20)] public QuestDrawBridgeParameterElement element__arr1;
        [FieldOffset(40)] public QuestDrawBridgeParameterElement element__arr2;
    }

}