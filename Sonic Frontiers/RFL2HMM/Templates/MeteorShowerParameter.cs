using System.Numerics;
using System.Runtime.InteropServices;

public class MeteorShowerParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 96)]
    public struct MeteorShowerEffectParameter
    {
        [FieldOffset(0)]  public float spawnIntervalMax;
        [FieldOffset(4)]  public float spawnIntervalMin;
        [FieldOffset(8)]  public float spawnHeightMax;
        [FieldOffset(12)] public float spawnHeightMin;
        [FieldOffset(16)] public float spawnHorizonMax;
        [FieldOffset(20)] public float spawnHorizonMin;
        [FieldOffset(24)] public float speedMax;
        [FieldOffset(28)] public float speedMin;
        [FieldOffset(32)] public float lengthMax;
        [FieldOffset(36)] public float lengthMin;
        [FieldOffset(40)] public float width;
        [FieldOffset(44)] public float angleMax;
        [FieldOffset(48)] public float angleMin;
        [FieldOffset(52)] public float moveTimeMax;
        [FieldOffset(56)] public float moveTimeMin;
        [FieldOffset(60)] public float fadeTimeMax;
        [FieldOffset(64)] public float fadeTimeMin;
        [FieldOffset(68)] public float spawnAngle;
        [FieldOffset(80)] public Vector3 color;
    }

    public enum Symbol : sbyte
    {
        Invalid = -1,
        Seven = 0,
        Bar = 1,
        Fruit = 2,
        Bell = 3,
        NumSymbols = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct ReelParam
    {
        [FieldOffset(0)]  public Symbol symbols__arr0;
        [FieldOffset(1)] public Symbol symbols__arr1;
        [FieldOffset(2)] public Symbol symbols__arr2;
        [FieldOffset(3)] public Symbol symbols__arr3;
        [FieldOffset(4)] public Symbol symbols__arr4;
        [FieldOffset(5)] public Symbol symbols__arr5;
        [FieldOffset(6)] public Symbol symbols__arr6;
        [FieldOffset(7)] public Symbol symbols__arr7;
        [FieldOffset(8)] public Symbol symbols__arr8;
        [FieldOffset(9)] public Symbol symbols__arr9;
        [FieldOffset(10)] public Symbol symbols__arr10;
        [FieldOffset(11)] public Symbol symbols__arr11;
        [FieldOffset(12)] public Symbol symbols__arr12;
        [FieldOffset(13)] public Symbol symbols__arr13;
        [FieldOffset(14)] public Symbol symbols__arr14;
        [FieldOffset(15)] public Symbol symbols__arr15;
        [FieldOffset(16)] public float spinSpeedMin;
        [FieldOffset(20)] public float spinSpeedMax;
        [FieldOffset(24)] public float autoStopTimeMin;
        [FieldOffset(28)] public float autoStopTimeMax;
    }

    public enum RateInfo_Symbol : sbyte
    {
        RateInfo_Symbol_Invalid = -1,
        RateInfo_Symbol_Seven = 0,
        RateInfo_Symbol_Bar = 1,
        RateInfo_Symbol_Fruit = 2,
        RateInfo_Symbol_Bell = 3,
        RateInfo_Symbol_NumSymbols = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct RateInfo
    {
        [FieldOffset(0)] public RateInfo_Symbol symbols__arr0;
        [FieldOffset(1)] public RateInfo_Symbol symbols__arr1;
        [FieldOffset(2)] public RateInfo_Symbol symbols__arr2;
        [FieldOffset(4)] public float rate;
    }

    public enum CeilingInfo_Symbol : sbyte
    {
        CeilingInfo_Symbol_Invalid = -1,
        CeilingInfo_Symbol_Seven = 0,
        CeilingInfo_Symbol_Bar = 1,
        CeilingInfo_Symbol_Fruit = 2,
        CeilingInfo_Symbol_Bell = 3,
        CeilingInfo_Symbol_NumSymbols = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct CeilingInfo
    {
        [FieldOffset(0)] public CeilingInfo_Symbol symbols__arr0;
        [FieldOffset(1)] public CeilingInfo_Symbol symbols__arr1;
        [FieldOffset(2)] public CeilingInfo_Symbol symbols__arr2;
        [FieldOffset(4)] public uint rollCount;
    }

    public enum PayoutInfo_Symbol : sbyte
    {
        PayoutInfo_Symbol_Invalid = -1,
        PayoutInfo_Symbol_Seven = 0,
        PayoutInfo_Symbol_Bar = 1,
        PayoutInfo_Symbol_Fruit = 2,
        PayoutInfo_Symbol_Bell = 3,
        PayoutInfo_Symbol_NumSymbols = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public struct PayoutInfo
    {
        [FieldOffset(0)] public PayoutInfo_Symbol symbols__arr0;
        [FieldOffset(1)] public PayoutInfo_Symbol symbols__arr1;
        [FieldOffset(2)] public PayoutInfo_Symbol symbols__arr2;
        [FieldOffset(4)] public uint payout;
    }

    [StructLayout(LayoutKind.Explicit, Size = 216)]
    public struct ObjBonusSlotConfig
    {
        [FieldOffset(0)]   public ReelParam reelParams__arr0;
        [FieldOffset(32)] public ReelParam reelParams__arr1;
        [FieldOffset(64)] public ReelParam reelParams__arr2;
        [FieldOffset(96)]  public float spinInterval;
        [FieldOffset(100)] public RateInfo rateInfos__arr0;
        [FieldOffset(108)] public RateInfo rateInfos__arr1;
        [FieldOffset(116)] public RateInfo rateInfos__arr2;
        [FieldOffset(124)] public RateInfo rateInfos__arr3;
        [FieldOffset(132)] public CeilingInfo ceilingInfos__arr0;
        [FieldOffset(140)] public CeilingInfo ceilingInfos__arr1;
        [FieldOffset(148)] public CeilingInfo ceilingInfos__arr2;
        [FieldOffset(156)] public CeilingInfo ceilingInfos__arr3;
        [FieldOffset(164)] public PayoutInfo payoutInfos__arr0;
        [FieldOffset(172)] public PayoutInfo payoutInfos__arr1;
        [FieldOffset(180)] public PayoutInfo payoutInfos__arr2;
        [FieldOffset(188)] public PayoutInfo payoutInfos__arr3;
        [FieldOffset(196)] public uint payoutOnBlank;
        [FieldOffset(200)] public bool WinEvenWithPush;
        [FieldOffset(204)] public float retrySpeed;
        [FieldOffset(208)] public float backSpeed;
        [FieldOffset(212)] public float stepSpeed;
    }

    [StructLayout(LayoutKind.Explicit, Size = 352)]
    public struct MeteorShowerParameter
    {
        [FieldOffset(0)]   public float rangeFromSonicObjectsDontRespawn;
        [FieldOffset(4)]   public uint intervalDay;
        [FieldOffset(8)]   public uint startHour;
        [FieldOffset(12)]  public uint startMinute;
        [FieldOffset(16)]  public uint durationHour;
        [FieldOffset(20)]  public uint durationMinute;
        [FieldOffset(32)]  public MeteorShowerEffectParameter effect;
        [FieldOffset(128)] public ObjBonusSlotConfig bonusSlotConfig;
    }

}