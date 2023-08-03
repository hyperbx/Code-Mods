using System.Numerics;
using System.Runtime.InteropServices;

public class TalkEventCameraPresetParametersClass
{
    public enum GazePositionType : sbyte
    {
        Base = 0,
        Head = 1,
        Eye = 2,
        Center = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 36)]
    public struct TalkEventCameraPresetParameter
    {
        [FieldOffset(0)]  public bool enable;
        [FieldOffset(1)]  public GazePositionType primaryTarget;
        [FieldOffset(2)]  public GazePositionType secondaryTarget;
        [FieldOffset(4)]  public float targetRatio;
        [FieldOffset(8)]  public float rotateDegreePitch;
        [FieldOffset(12)] public float rotateDegreeYaw;
        [FieldOffset(16)] public float cameraOffsetRatio;
        [FieldOffset(20)] public float fovy;
        [FieldOffset(24)] public float targetOffsetX;
        [FieldOffset(28)] public float targetOffsetY;
        [FieldOffset(32)] public float targetOffsetZ;
    }

    [StructLayout(LayoutKind.Explicit, Size = 576)]
    public struct TalkEventCameraPresetParameters
    {
        [FieldOffset(0)] public TalkEventCameraPresetParameter param__arr0;
        [FieldOffset(36)] public TalkEventCameraPresetParameter param__arr1;
        [FieldOffset(72)] public TalkEventCameraPresetParameter param__arr2;
        [FieldOffset(108)] public TalkEventCameraPresetParameter param__arr3;
        [FieldOffset(144)] public TalkEventCameraPresetParameter param__arr4;
        [FieldOffset(180)] public TalkEventCameraPresetParameter param__arr5;
        [FieldOffset(216)] public TalkEventCameraPresetParameter param__arr6;
        [FieldOffset(252)] public TalkEventCameraPresetParameter param__arr7;
        [FieldOffset(288)] public TalkEventCameraPresetParameter param__arr8;
        [FieldOffset(324)] public TalkEventCameraPresetParameter param__arr9;
        [FieldOffset(360)] public TalkEventCameraPresetParameter param__arr10;
        [FieldOffset(396)] public TalkEventCameraPresetParameter param__arr11;
        [FieldOffset(432)] public TalkEventCameraPresetParameter param__arr12;
        [FieldOffset(468)] public TalkEventCameraPresetParameter param__arr13;
        [FieldOffset(504)] public TalkEventCameraPresetParameter param__arr14;
        [FieldOffset(540)] public TalkEventCameraPresetParameter param__arr15;
    }

}