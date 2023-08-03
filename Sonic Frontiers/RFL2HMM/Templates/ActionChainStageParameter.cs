using System.Numerics;
using System.Runtime.InteropServices;

public class ActionChainStageParameterClass
{
    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public struct ActionChainScoreThresholdParameter
    {
        [FieldOffset(0)]  public uint scoreS;
        [FieldOffset(4)]  public uint scoreA;
        [FieldOffset(8)]  public uint scoreB;
        [FieldOffset(12)] public uint scoreC;
    }

    [StructLayout(LayoutKind.Explicit, Size = 68)]
    public struct ActionChainPlaceParameter
    {
        [FieldOffset(0)]  public float time;
        [FieldOffset(4)]  public ActionChainScoreThresholdParameter scoreEasy;
        [FieldOffset(20)] public ActionChainScoreThresholdParameter scoreNormal;
        [FieldOffset(36)] public ActionChainScoreThresholdParameter scoreHard;
        [FieldOffset(52)] public ActionChainScoreThresholdParameter scoreVeryHard;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1088)]
    public struct ActionChainStageParameter
    {
        [FieldOffset(0)] public ActionChainPlaceParameter placeParam__arr0;
        [FieldOffset(68)] public ActionChainPlaceParameter placeParam__arr1;
        [FieldOffset(136)] public ActionChainPlaceParameter placeParam__arr2;
        [FieldOffset(204)] public ActionChainPlaceParameter placeParam__arr3;
        [FieldOffset(272)] public ActionChainPlaceParameter placeParam__arr4;
        [FieldOffset(340)] public ActionChainPlaceParameter placeParam__arr5;
        [FieldOffset(408)] public ActionChainPlaceParameter placeParam__arr6;
        [FieldOffset(476)] public ActionChainPlaceParameter placeParam__arr7;
        [FieldOffset(544)] public ActionChainPlaceParameter placeParam__arr8;
        [FieldOffset(612)] public ActionChainPlaceParameter placeParam__arr9;
        [FieldOffset(680)] public ActionChainPlaceParameter placeParam__arr10;
        [FieldOffset(748)] public ActionChainPlaceParameter placeParam__arr11;
        [FieldOffset(816)] public ActionChainPlaceParameter placeParam__arr12;
        [FieldOffset(884)] public ActionChainPlaceParameter placeParam__arr13;
        [FieldOffset(952)] public ActionChainPlaceParameter placeParam__arr14;
        [FieldOffset(1020)] public ActionChainPlaceParameter placeParam__arr15;
    }

}