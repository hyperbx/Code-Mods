using System.Numerics;
using System.Runtime.InteropServices;

public class QuestDarumaBattleParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct QuestDarumaTimerParameter
    {
        [FieldOffset(0)]  public float timeLimitSeconds;
        [FieldOffset(4)]  public float cautionTime;
        [FieldOffset(8)]  public float warningTime;
        [FieldOffset(12)] public bool useCautionAnimation;
        [FieldOffset(13)] public bool useWarningAnimation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct QuestDarumaBattleParameterElement
    {
        [FieldOffset(0)]  public int applicableFailedCount;
        [FieldOffset(4)]  public float collectionColliderRadius;
        [FieldOffset(8)]  public float collectionColliderHeight;
        [FieldOffset(12)] public QuestDarumaTimerParameter timerParam;
    }

    [StructLayout(LayoutKind.Explicit, Size = 84)]
    public struct QuestDarumaBattleParameter
    {
        [FieldOffset(0)] public QuestDarumaBattleParameterElement element__arr0;
        [FieldOffset(28)] public QuestDarumaBattleParameterElement element__arr1;
        [FieldOffset(56)] public QuestDarumaBattleParameterElement element__arr2;
    }

}