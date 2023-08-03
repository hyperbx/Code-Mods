using System.Numerics;
using System.Runtime.InteropServices;

public class EnemyJumperConfigClass
{
    [StructLayout(LayoutKind.Explicit, Size = 52)]
    public struct EnemyJumperPatrolConfig
    {
        [FieldOffset(0)]  public float rotateSpeedMin;
        [FieldOffset(4)]  public float rotateSpeedMax;
        [FieldOffset(8)]  public float speedMin;
        [FieldOffset(12)] public float speedMax;
        [FieldOffset(16)] public float changeTimeIdlePatrolMin;
        [FieldOffset(20)] public float changeTimeIdlePatrolMax;
        [FieldOffset(24)] public float lockonDistance;
        [FieldOffset(28)] public float unlockDistance;
        [FieldOffset(32)] public float distance;
        [FieldOffset(36)] public float minElevation;
        [FieldOffset(40)] public float maxElevation;
        [FieldOffset(44)] public float panningSuspensionK;
        [FieldOffset(48)] public float interiorPanningSuspensionK;
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct EnemyJumperAutoLockonParam
    {
        [FieldOffset(0)]  public float distance;
        [FieldOffset(4)]  public float lockOnMinDistance;
        [FieldOffset(16)] public Vector3 playerOffset;
    }

    [StructLayout(LayoutKind.Explicit, Size = 128)]
    public struct EnemyJumperCommonParam
    {
        [FieldOffset(0)]  public float killWaitTime;
        [FieldOffset(4)]  public float colliderRadius;
        [FieldOffset(8)]  public float colliderHeight;
        [FieldOffset(12)] public float headRadius;
        [FieldOffset(16)] public float headHeight;
        [FieldOffset(20)] public float damageColliderRadiusOffset;
        [FieldOffset(24)] public float eyesightDistance;
        [FieldOffset(28)] public float maxSpeed;
        [FieldOffset(32)] public float checkBarrierDistance;
        [FieldOffset(36)] public EnemyJumperPatrolConfig patrolConfig;
        [FieldOffset(96)] public EnemyJumperAutoLockonParam lockonCamera;
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct EnemyJumperCommonLevelParam
    {
        [FieldOffset(0)]  public int maxHealthPoint;
        [FieldOffset(4)]  public float attackRate;
        [FieldOffset(8)]  public ushort expItemNum;
        [FieldOffset(10)] public ushort exp;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct EnemyJumperLevelParam
    {
        [FieldOffset(0)] public int level;
        [FieldOffset(4)] public EnemyJumperCommonLevelParam common;
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct EnemyJumperLevelBand
    {
        [FieldOffset(0)] public int level;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct CharacterControllerCollision
    {
        [FieldOffset(0)]  public float height;
        [FieldOffset(4)]  public float radius;
        [FieldOffset(16)] public Vector3 offset;
        [FieldOffset(32)] public Vector3 scale;
    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct MovementParam
    {
        [FieldOffset(0)]  public float rotateSpeedMin;
        [FieldOffset(4)]  public float rotateSpeedMax;
        [FieldOffset(8)]  public float speedMin;
        [FieldOffset(12)] public float speedMax;
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct SpringPlayer
    {
        [FieldOffset(0)] public float velocity;
        [FieldOffset(4)] public float targetCursorMaxDistance;
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct BattleParam
    {
        [FieldOffset(0)]  public float stompingRange;
        [FieldOffset(4)]  public float stompingTotalNum;
        [FieldOffset(8)]  public float interpalTimeFinal;
        [FieldOffset(12)] public float range;
        [FieldOffset(16)] public float riseDistance;
        [FieldOffset(20)] public float riseTime;
        [FieldOffset(24)] public float upLoopTime;
        [FieldOffset(28)] public float chaseSpeed;
        [FieldOffset(32)] public float speed;
        [FieldOffset(36)] public float groundImpactRadius;
        [FieldOffset(40)] public SpringPlayer springPlayer;
    }

    [StructLayout(LayoutKind.Explicit, Size = 352)]
    public struct EnemyJumperConfig
    {
        [FieldOffset(0)]   public EnemyJumperCommonParam commonParam;
        [FieldOffset(128)] public EnemyJumperLevelParam levelParams__arr0;
        [FieldOffset(144)] public EnemyJumperLevelParam levelParams__arr1;
        [FieldOffset(160)] public EnemyJumperLevelParam levelParams__arr2;
        [FieldOffset(176)] public EnemyJumperLevelParam levelParams__arr3;
        [FieldOffset(192)] public EnemyJumperLevelParam levelParams__arr4;
        [FieldOffset(208)] public EnemyJumperLevelBand levelBand__arr0;
        [FieldOffset(212)] public EnemyJumperLevelBand levelBand__arr1;
        [FieldOffset(216)] public EnemyJumperLevelBand levelBand__arr2;
        [FieldOffset(220)] public EnemyJumperLevelBand levelBand__arr3;
        [FieldOffset(224)] public EnemyJumperLevelBand levelBand__arr4;
        [FieldOffset(240)] public CharacterControllerCollision characterControllerCollision;
        [FieldOffset(288)] public MovementParam movement;
        [FieldOffset(304)] public BattleParam battleParam;
    }

}