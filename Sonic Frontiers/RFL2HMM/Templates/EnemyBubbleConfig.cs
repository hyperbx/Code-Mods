using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyBubbleConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct EnemyBubbleApproachConfig
    {
        [FieldOffset(0)] public float moveMinDistance;
        [FieldOffset(4)] public float moveSpeedMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct EnemyBubbleBlitzProtectionReadyConfig
    {
        [FieldOffset(0)]  public float moveMinDistance;
        [FieldOffset(4)]  public float moveSpeedMax;
        [FieldOffset(8)]  public float blitzProtectionMaxDistance;
        [FieldOffset(12)] public float blitzProtectionReadyTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct EnemyBubbleBlitzProtectionConfig
    {
        [FieldOffset(0)]  public float moveMinDistance;
        [FieldOffset(4)]  public float moveSpeedMax;
        [FieldOffset(8)]  public float blitzProtectionAttackTime;
        [FieldOffset(12)] public float blitzProtectionIntervalTime;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct EnemyBubbleShellConfig
    {
        [FieldOffset(0)]  public float baseHeight;
        [FieldOffset(4)]  public float innerDistance;
        [FieldOffset(8)]  public float outerDistance;
        [FieldOffset(12)] public float innerRadius;
        [FieldOffset(16)] public float outerRadius;
        [FieldOffset(20)] public float innerAccelMax;
        [FieldOffset(24)] public float outerAccelMax;
        [FieldOffset(28)] public float innerSpeedMax;
        [FieldOffset(32)] public float outerSpeedMax;
        [FieldOffset(36)] public byte innerNum;
        [FieldOffset(37)] public byte outerNum;
    }

    [StructLayout(LayoutKind.Explicit, Size = 124)]
    public struct EnemyBubbleCommonParam
    {
        [FieldOffset(0)]  public float killWaitTime;
        [FieldOffset(4)]  public float colliderRadius;
        [FieldOffset(8)]  public float damageColliderRadiusOffset;
        [FieldOffset(12)] public float attackColliderRadiusOffset;
        [FieldOffset(16)] public float eyesightDistance;
        [FieldOffset(20)] public float moveAccerleration;
        [FieldOffset(24)] public float moveDeceleration;
        [FieldOffset(28)] public float rotationAngleMax;
        [FieldOffset(32)] public float mass;
        [FieldOffset(36)] public float slopeAngleMax;
        [FieldOffset(40)] public float knockBackTime;
        [FieldOffset(44)] public EnemyBubbleApproachConfig approachConfig;
        [FieldOffset(52)] public EnemyBubbleBlitzProtectionReadyConfig blitzReadyConfig;
        [FieldOffset(68)] public EnemyBubbleBlitzProtectionConfig blitzConfig;
        [FieldOffset(84)] public EnemyBubbleShellConfig shellConfig;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct EnemyBubbleCommonLevelParam
    {
        [FieldOffset(0)]  public int maxHealthPoint;
        [FieldOffset(4)]  public float attackRate;
        [FieldOffset(8)]  public ushort expItemNum;
        [FieldOffset(10)] public ushort exp;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct EnemyBubbleLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public EnemyBubbleCommonLevelParam common;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct EnemyBubbleLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    [StructLayout(LayoutKind.Explicit, Size = 224)]
    public struct EnemyBubbleConfig
    {
        [FieldOffset(0)]   public EnemyBubbleCommonParam commonParam;
        [FieldOffset(124)] public EnemyBubbleLevelParam levelParams__arr0;
        [FieldOffset(140)] public EnemyBubbleLevelParam levelParams__arr1;
        [FieldOffset(156)] public EnemyBubbleLevelParam levelParams__arr2;
        [FieldOffset(172)] public EnemyBubbleLevelParam levelParams__arr3;
        [FieldOffset(188)] public EnemyBubbleLevelParam levelParams__arr4;
        [FieldOffset(204)] public EnemyBubbleLevelBand levelBand__arr0;
        [FieldOffset(208)] public EnemyBubbleLevelBand levelBand__arr1;
        [FieldOffset(212)] public EnemyBubbleLevelBand levelBand__arr2;
        [FieldOffset(216)] public EnemyBubbleLevelBand levelBand__arr3;
        [FieldOffset(220)] public EnemyBubbleLevelBand levelBand__arr4;
    }

}