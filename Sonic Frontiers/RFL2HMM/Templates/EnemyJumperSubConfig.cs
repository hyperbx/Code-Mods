using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyJumperSubConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct EnemyJumperSubCommonParam
    {
        [FieldOffset(0)]  public float killWaitTime;
        [FieldOffset(4)]  public float colliderRadius;
        [FieldOffset(8)]  public float colliderHeight;
        [FieldOffset(12)] public float damageColliderRadiusOffset;
        [FieldOffset(16)] public float eyesightDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct EnemyJumperSubCommonLevelParam
    {
        [FieldOffset(0)]  public int maxHealthPoint;
        [FieldOffset(4)]  public float attackRate;
        [FieldOffset(8)]  public ushort expItemNum;
        [FieldOffset(10)] public ushort exp;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct EnemyJumperSubLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public EnemyJumperSubCommonLevelParam common;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct EnemyJumperSubLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    [StructLayout(LayoutKind.Explicit, Size = 120)]
    public struct EnemyJumperSubConfig
    {
        [FieldOffset(0)]   public EnemyJumperSubCommonParam commonParam;
        [FieldOffset(20)]  public EnemyJumperSubLevelParam levelParams__arr0;
        [FieldOffset(36)] public EnemyJumperSubLevelParam levelParams__arr1;
        [FieldOffset(52)] public EnemyJumperSubLevelParam levelParams__arr2;
        [FieldOffset(68)] public EnemyJumperSubLevelParam levelParams__arr3;
        [FieldOffset(84)] public EnemyJumperSubLevelParam levelParams__arr4;
        [FieldOffset(100)] public EnemyJumperSubLevelBand levelBand__arr0;
        [FieldOffset(104)] public EnemyJumperSubLevelBand levelBand__arr1;
        [FieldOffset(108)] public EnemyJumperSubLevelBand levelBand__arr2;
        [FieldOffset(112)] public EnemyJumperSubLevelBand levelBand__arr3;
        [FieldOffset(116)] public EnemyJumperSubLevelBand levelBand__arr4;
    }

}