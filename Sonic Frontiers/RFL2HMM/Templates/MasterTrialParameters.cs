using System.Numerics;
using System.Runtime.InteropServices;

public class MasterTrialParametersClass
{
    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct MasterTrialStageParameter
    {
        [FieldOffset(0)]  public byte prerequisite;
        [FieldOffset(4)]  public float limitTime;
        [FieldOffset(8)]  public float speedUpScale;
        [FieldOffset(12)] public float recoveryHpTime;
        [FieldOffset(16)] public uint recoveryHpPoint;
        [FieldOffset(20)] public uint limitMistake;
    }

    [StructLayout(LayoutKind.Explicit, Size = 100)]
    public struct MasterTrialParameterElement
    {
        [FieldOffset(0)] public int applicableFailedCount;
        [FieldOffset(4)] public MasterTrialStageParameter stages__arr0;
        [FieldOffset(28)] public MasterTrialStageParameter stages__arr1;
        [FieldOffset(52)] public MasterTrialStageParameter stages__arr2;
        [FieldOffset(76)] public MasterTrialStageParameter stages__arr3;
    }

    [StructLayout(LayoutKind.Explicit, Size = 324)]
    public struct MasterTrialParameters
    {
        [FieldOffset(0)]  public float subjectViewTime;
        [FieldOffset(4)]  public float readyTime;
        [FieldOffset(8)]  public float clearTime;
        [FieldOffset(12)] public float failedTime;
        [FieldOffset(16)] public float clearWaitTime;
        [FieldOffset(20)] public float failedWaitTime;
        [FieldOffset(24)] public MasterTrialParameterElement element__arr0;
        [FieldOffset(124)] public MasterTrialParameterElement element__arr1;
        [FieldOffset(224)] public MasterTrialParameterElement element__arr2;
    }

}