using System.Numerics;
using System.Runtime.InteropServices;

public class OptionDataClass
{
    public enum Status : sbyte
    {
        STATUS_ZERO_FILL = 0,
        STATUS_INITIALIZED = 1
    }

    public enum Sequence : sbyte
    {
        Island1 = 0,
        Island2 = 1,
        Island3 = 2,
        Island4 = 3,
        Island5 = 4,
        FinalBossBefore = 5,
        FinalBossAfter = 6
    }

    public enum SaveDataIcon : sbyte
    {
        IconNoData = 0,
        IconIsland1 = 1,
        IconIsland2 = 2,
        IconIsland3 = 3,
        IconIsland4 = 4,
        IconIsland5 = 5,
        IconLastBoss = 6
    }

    public enum AppVersion : byte
    {
        AppVersion_1_10 = 0,
        AppVersion_1_20 = 1,
        AppVersion_1_30 = 2,
        AppVersion_1_40 = 3
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct HeaderData
    {
        [FieldOffset(0)]  public uint signature;
        [FieldOffset(4)]  public byte version;
        [FieldOffset(5)]  public Status status;
        [FieldOffset(6)]  public byte config;
        [FieldOffset(7)]  public Sequence sequence;
        [FieldOffset(8)]  public uint playTime;
        [FieldOffset(12)] public SaveDataIcon icon;
        [FieldOffset(13)] public AppVersion appVersion;
        [FieldOffset(14)] public byte config2;
        [FieldOffset(15)] public byte reserved1;
        [FieldOffset(16)] public uint saveDate;
        [FieldOffset(20)] public byte index;
        [FieldOffset(24)] public uint reserved__arr0;
        [FieldOffset(28)] public uint reserved__arr1;
        [FieldOffset(32)] public uint reserved__arr2;
        [FieldOffset(36)] public uint reserved__arr3;
    }

    public enum VoiceLanguageType : sbyte
    {
        VOICE_LANGUAGE_ENGLISH = 0,
        VOICE_LANGUAGE_FRENCH = 1,
        VOICE_LANGUAGE_ITALIAN = 2,
        VOICE_LANGUAGE_GERMAN = 3,
        VOICE_LANGUAGE_SPANISH = 4,
        VOICE_LANGUAGE_JAPANESE = 5,
        NUM_VOICE_LANGUAGES = 6
    }

    public enum LanguageType : sbyte
    {
        LANGUAGE_ENGLISH = 0,
        LANGUAGE_FRENCH = 1,
        LANGUAGE_ITALIAN = 2,
        LANGUAGE_GERMAN = 3,
        LANGUAGE_SPANISH = 4,
        LANGUAGE_POLISH = 5,
        LANGUAGE_PORTUGUESE = 6,
        LANGUAGE_RUSSIAN = 7,
        LANGUAGE_JAPANESE = 8,
        LANGUAGE_ZHONGWEN = 9,
        LANGUAGE_ZHONGWEN_S = 10,
        LANGUAGE_KOREAN = 11,
        NUM_LANGUAGES = 12
    }

    public enum VibrationLevel : sbyte
    {
        None = 0,
        Low = 1,
        Medium = 2,
        High = 3
    }

    public enum Value : sbyte
    {
        Easy = 0,
        Normal = 1,
        Hard = 2,
        Num = 3,
        VeryHard = 3,
        NumInVeryHard = 4
    }

    [StructLayout(LayoutKind.Explicit, Size = 32)]
    public struct OptionGamePlayData
    {
        [FieldOffset(0)]  public byte initialSpeedRate;
        [FieldOffset(1)]  public byte boostInitialSpeedRate;
        [FieldOffset(2)]  public byte acceleRate;
        [FieldOffset(3)]  public byte maxSpeedRate;
        [FieldOffset(4)]  public byte minTurnSpeedRate;
        [FieldOffset(5)]  public byte boostMinTurnSpeedRate;
        [FieldOffset(6)]  public byte rotateForceRate;
        [FieldOffset(7)]  public byte bumpJumpGravityRate;
        [FieldOffset(8)]  public VoiceLanguageType speech;
        [FieldOffset(9)]  public LanguageType text;
        [FieldOffset(10)] public VibrationLevel vibrationLevel;
        [FieldOffset(11)] public Value diffculty;
        [FieldOffset(12)] public byte config;
        [FieldOffset(13)] public byte padSensibilityRate;
        [FieldOffset(14)] public byte mouseSensibilityRate;
        [FieldOffset(15)] public byte neutralDecelerationRate;
        [FieldOffset(16)] public byte dlcSonicCostume;
        [FieldOffset(17)] public byte dlcKodamaModel;
        [FieldOffset(18)] public byte dlcRingSE;
        [FieldOffset(19)] public byte dlcConfig;
        [FieldOffset(20)] public byte config2;
        [FieldOffset(21)] public byte islandVisual;
        [FieldOffset(22)] public byte npcVisual;
        [FieldOffset(23)] public byte baseAirDragScaleRate;
        [FieldOffset(24)] public uint status;
        [FieldOffset(28)] public uint reserved2;
    }

    public enum InputKey : int
    {
        Invalid = -1,
        GamePad_DPadLeft = 0,
        GamePad_DPadRight = 1,
        GamePad_DPadUp = 2,
        GamePad_DPadDown = 3,
        GamePad_ButtonLeft = 4,
        GamePad_ButtonRight = 5,
        GamePad_ButtonTop = 6,
        GamePad_ButtonBottom = 7,
        GamePad_LeftX = 8,
        GamePad_LeftY = 9,
        GamePad_RightX = 10,
        GamePad_RightY = 11,
        GamePad_LeftShoulder = 12,
        GamePad_LeftTrigger = 13,
        GamePad_LeftClick = 14,
        GamePad_RightShoulder = 15,
        GamePad_RightTrigger = 16,
        GamePad_RightClick = 17,
        GamePad_LeftStickLeft = 18,
        GamePad_LeftStickRight = 19,
        GamePad_LeftStickUp = 20,
        GamePad_LeftStickDown = 21,
        GamePad_RightStickLeft = 22,
        GamePad_RightStickRight = 23,
        GamePad_RightStickUp = 24,
        GamePad_RightStickDown = 25,
        GamePad_Start = 26,
        GamePad_Select = 27,
        GamePad_LeftSideTriggerLeft = 28,
        GamePad_LeftSideTriggerRight = 29,
        GamePad_RightSideTriggerLeft = 30,
        GamePad_RightSideTriggerRight = 31,
        Keyboard_Nop = 32,
        Keyboard_A = 33,
        Keyboard_B = 34,
        Keyboard_C = 35,
        Keyboard_D = 36,
        Keyboard_E = 37,
        Keyboard_F = 38,
        Keyboard_G = 39,
        Keyboard_H = 40,
        Keyboard_I = 41,
        Keyboard_J = 42,
        Keyboard_K = 43,
        Keyboard_L = 44,
        Keyboard_M = 45,
        Keyboard_N = 46,
        Keyboard_O = 47,
        Keyboard_P = 48,
        Keyboard_Q = 49,
        Keyboard_R = 50,
        Keyboard_S = 51,
        Keyboard_T = 52,
        Keyboard_U = 53,
        Keyboard_V = 54,
        Keyboard_W = 55,
        Keyboard_X = 56,
        Keyboard_Y = 57,
        Keyboard_Z = 58,
        Keyboard_1 = 59,
        Keyboard_2 = 60,
        Keyboard_3 = 61,
        Keyboard_4 = 62,
        Keyboard_5 = 63,
        Keyboard_6 = 64,
        Keyboard_7 = 65,
        Keyboard_8 = 66,
        Keyboard_9 = 67,
        Keyboard_0 = 68,
        Keyboard_Enter = 69,
        Keyboard_Escape = 70,
        Keyboard_BackSpace = 71,
        Keyboard_Tab = 72,
        Keyboard_Spacebar = 73,
        Keyboard_Minus = 74,
        Keyboard_Accent = 75,
        Keyboard_Atmark = 76,
        Keyboard_LeftBracket = 77,
        Keyboard_BackSlash = 78,
        Keyboard_RightBracket = 79,
        Keyboard_SemiColon = 80,
        Keyboard_Colon = 81,
        Keyboard_Comma = 82,
        Keyboard_Period = 83,
        Keyboard_Slash = 84,
        Keyboard_CapsLock = 85,
        Keyboard_F1 = 86,
        Keyboard_F2 = 87,
        Keyboard_F3 = 88,
        Keyboard_F4 = 89,
        Keyboard_F5 = 90,
        Keyboard_F6 = 91,
        Keyboard_F7 = 92,
        Keyboard_F8 = 93,
        Keyboard_F9 = 94,
        Keyboard_F10 = 95,
        Keyboard_F11 = 96,
        Keyboard_F12 = 97,
        Keyboard_Insert = 98,
        Keyboard_Home = 99,
        Keyboard_PageUp = 100,
        Keyboard_Delete = 101,
        Keyboard_End = 102,
        Keyboard_PageDown = 103,
        Keyboard_LeftArrow = 104,
        Keyboard_RightArrow = 105,
        Keyboard_UpArrow = 106,
        Keyboard_DownArrow = 107,
        Keyboard_PadSlash = 108,
        Keyboard_PadAsterisk = 109,
        Keyboard_PadMinus = 110,
        Keyboard_PadPlus = 111,
        Keyboard_PadEnter = 112,
        Keyboard_PadNum1 = 113,
        Keyboard_PadNum2 = 114,
        Keyboard_PadNum3 = 115,
        Keyboard_PadNum4 = 116,
        Keyboard_PadNum5 = 117,
        Keyboard_PadNum6 = 118,
        Keyboard_PadNum7 = 119,
        Keyboard_PadNum8 = 120,
        Keyboard_PadNum9 = 121,
        Keyboard_PadNum0 = 122,
        Keyboard_PadPeriod = 123,
        Keyboard_LeftCtrl = 124,
        Keyboard_RightCtrl = 125,
        Keyboard_LeftShift = 126,
        Keyboard_RightShift = 127,
        Keyboard_LeftAlt = 128,
        Keyboard_RightAlt = 129,
        Keyboard_LeftGui = 130,
        Keyboard_RightGui = 131,
        Mouse_X = 132,
        Mouse_Y = 133,
        Mouse_ButtonLeft = 134,
        Mouse_ButtonRight = 135,
        Mouse_ButtonMiddle = 136,
        Mouse_ButtonX1 = 137,
        Mouse_ButtonX2 = 138,
        Mouse_Wheel = 139,
        Mouse_WheelUp = 140,
        Mouse_WheelDown = 141,
        Keyboard_Grave = 142,
        Keyboard_Equals = 143,
        Keyboard_Apostrophe = 144,
        Keyboard_OEM_102 = 145,
        Keyboard_ABNT_C1 = 146,
        Keyboard_ABNT_C2 = 147,
        Keyboard_Shift = 148,
        Keyboard_Ctrl = 149,
        NumAppKeys = 150
    }

    [StructLayout(LayoutKind.Explicit, Size = 744)]
    public struct OptionControlsData
    {
        [FieldOffset(0)]   public InputKey padMappings__arr0;
        [FieldOffset(4)] public InputKey padMappings__arr1;
        [FieldOffset(8)] public InputKey padMappings__arr2;
        [FieldOffset(12)] public InputKey padMappings__arr3;
        [FieldOffset(16)] public InputKey padMappings__arr4;
        [FieldOffset(20)] public InputKey padMappings__arr5;
        [FieldOffset(24)] public InputKey padMappings__arr6;
        [FieldOffset(28)] public InputKey padMappings__arr7;
        [FieldOffset(32)] public InputKey padMappings__arr8;
        [FieldOffset(36)] public InputKey padMappings__arr9;
        [FieldOffset(40)] public InputKey padMappings__arr10;
        [FieldOffset(44)] public InputKey padMappings__arr11;
        [FieldOffset(48)] public InputKey padMappings__arr12;
        [FieldOffset(52)] public InputKey padMappings__arr13;
        [FieldOffset(56)] public InputKey padMappings__arr14;
        [FieldOffset(60)] public InputKey padMappings__arr15;
        [FieldOffset(64)] public InputKey padMappings__arr16;
        [FieldOffset(68)] public InputKey padMappings__arr17;
        [FieldOffset(72)] public InputKey padMappings__arr18;
        [FieldOffset(76)] public InputKey padMappings__arr19;
        [FieldOffset(80)] public InputKey padMappings__arr20;
        [FieldOffset(84)] public InputKey padMappings__arr21;
        [FieldOffset(88)] public InputKey padMappings__arr22;
        [FieldOffset(92)] public InputKey padMappings__arr23;
        [FieldOffset(96)] public InputKey padMappings__arr24;
        [FieldOffset(100)] public InputKey padMappings__arr25;
        [FieldOffset(104)] public InputKey padMappings__arr26;
        [FieldOffset(108)] public InputKey padMappings__arr27;
        [FieldOffset(112)] public InputKey padMappings__arr28;
        [FieldOffset(116)] public InputKey padMappings__arr29;
        [FieldOffset(120)] public InputKey padMappings__arr30;
        [FieldOffset(124)] public InputKey padMappings__arr31;
        [FieldOffset(128)] public InputKey padMappings__arr32;
        [FieldOffset(132)] public InputKey padMappings__arr33;
        [FieldOffset(136)] public InputKey padMappings__arr34;
        [FieldOffset(140)] public InputKey padMappings__arr35;
        [FieldOffset(144)] public InputKey padMappings__arr36;
        [FieldOffset(148)] public InputKey padMappings__arr37;
        [FieldOffset(152)] public InputKey padMappings__arr38;
        [FieldOffset(156)] public InputKey padMappings__arr39;
        [FieldOffset(160)] public InputKey padMappings__arr40;
        [FieldOffset(164)] public InputKey padMappings__arr41;
        [FieldOffset(168)] public InputKey padMappings__arr42;
        [FieldOffset(172)] public InputKey padMappings__arr43;
        [FieldOffset(176)] public InputKey padMappings__arr44;
        [FieldOffset(180)] public InputKey padMappings__arr45;
        [FieldOffset(184)] public InputKey padMappings__arr46;
        [FieldOffset(188)] public InputKey padMappings__arr47;
        [FieldOffset(192)] public InputKey padMappings__arr48;
        [FieldOffset(196)] public InputKey padMappings__arr49;
        [FieldOffset(200)] public InputKey padMappings__arr50;
        [FieldOffset(204)] public InputKey padMappings__arr51;
        [FieldOffset(208)] public InputKey padMappings__arr52;
        [FieldOffset(212)] public InputKey padMappings__arr53;
        [FieldOffset(216)] public InputKey padMappings__arr54;
        [FieldOffset(220)] public InputKey padMappings__arr55;
        [FieldOffset(224)] public InputKey padMappings__arr56;
        [FieldOffset(228)] public InputKey padMappings__arr57;
        [FieldOffset(232)] public InputKey padMappings__arr58;
        [FieldOffset(236)] public InputKey padMappings__arr59;
        [FieldOffset(240)] public InputKey padMappings__arr60;
        [FieldOffset(244)] public InputKey padMappings__arr61;
        [FieldOffset(248)] public InputKey mainMappings__arr0;
        [FieldOffset(252)] public InputKey mainMappings__arr1;
        [FieldOffset(256)] public InputKey mainMappings__arr2;
        [FieldOffset(260)] public InputKey mainMappings__arr3;
        [FieldOffset(264)] public InputKey mainMappings__arr4;
        [FieldOffset(268)] public InputKey mainMappings__arr5;
        [FieldOffset(272)] public InputKey mainMappings__arr6;
        [FieldOffset(276)] public InputKey mainMappings__arr7;
        [FieldOffset(280)] public InputKey mainMappings__arr8;
        [FieldOffset(284)] public InputKey mainMappings__arr9;
        [FieldOffset(288)] public InputKey mainMappings__arr10;
        [FieldOffset(292)] public InputKey mainMappings__arr11;
        [FieldOffset(296)] public InputKey mainMappings__arr12;
        [FieldOffset(300)] public InputKey mainMappings__arr13;
        [FieldOffset(304)] public InputKey mainMappings__arr14;
        [FieldOffset(308)] public InputKey mainMappings__arr15;
        [FieldOffset(312)] public InputKey mainMappings__arr16;
        [FieldOffset(316)] public InputKey mainMappings__arr17;
        [FieldOffset(320)] public InputKey mainMappings__arr18;
        [FieldOffset(324)] public InputKey mainMappings__arr19;
        [FieldOffset(328)] public InputKey mainMappings__arr20;
        [FieldOffset(332)] public InputKey mainMappings__arr21;
        [FieldOffset(336)] public InputKey mainMappings__arr22;
        [FieldOffset(340)] public InputKey mainMappings__arr23;
        [FieldOffset(344)] public InputKey mainMappings__arr24;
        [FieldOffset(348)] public InputKey mainMappings__arr25;
        [FieldOffset(352)] public InputKey mainMappings__arr26;
        [FieldOffset(356)] public InputKey mainMappings__arr27;
        [FieldOffset(360)] public InputKey mainMappings__arr28;
        [FieldOffset(364)] public InputKey mainMappings__arr29;
        [FieldOffset(368)] public InputKey mainMappings__arr30;
        [FieldOffset(372)] public InputKey mainMappings__arr31;
        [FieldOffset(376)] public InputKey mainMappings__arr32;
        [FieldOffset(380)] public InputKey mainMappings__arr33;
        [FieldOffset(384)] public InputKey mainMappings__arr34;
        [FieldOffset(388)] public InputKey mainMappings__arr35;
        [FieldOffset(392)] public InputKey mainMappings__arr36;
        [FieldOffset(396)] public InputKey mainMappings__arr37;
        [FieldOffset(400)] public InputKey mainMappings__arr38;
        [FieldOffset(404)] public InputKey mainMappings__arr39;
        [FieldOffset(408)] public InputKey mainMappings__arr40;
        [FieldOffset(412)] public InputKey mainMappings__arr41;
        [FieldOffset(416)] public InputKey mainMappings__arr42;
        [FieldOffset(420)] public InputKey mainMappings__arr43;
        [FieldOffset(424)] public InputKey mainMappings__arr44;
        [FieldOffset(428)] public InputKey mainMappings__arr45;
        [FieldOffset(432)] public InputKey mainMappings__arr46;
        [FieldOffset(436)] public InputKey mainMappings__arr47;
        [FieldOffset(440)] public InputKey mainMappings__arr48;
        [FieldOffset(444)] public InputKey mainMappings__arr49;
        [FieldOffset(448)] public InputKey mainMappings__arr50;
        [FieldOffset(452)] public InputKey mainMappings__arr51;
        [FieldOffset(456)] public InputKey mainMappings__arr52;
        [FieldOffset(460)] public InputKey mainMappings__arr53;
        [FieldOffset(464)] public InputKey mainMappings__arr54;
        [FieldOffset(468)] public InputKey mainMappings__arr55;
        [FieldOffset(472)] public InputKey mainMappings__arr56;
        [FieldOffset(476)] public InputKey mainMappings__arr57;
        [FieldOffset(480)] public InputKey mainMappings__arr58;
        [FieldOffset(484)] public InputKey mainMappings__arr59;
        [FieldOffset(488)] public InputKey mainMappings__arr60;
        [FieldOffset(492)] public InputKey mainMappings__arr61;
        [FieldOffset(496)] public InputKey subMappings__arr0;
        [FieldOffset(500)] public InputKey subMappings__arr1;
        [FieldOffset(504)] public InputKey subMappings__arr2;
        [FieldOffset(508)] public InputKey subMappings__arr3;
        [FieldOffset(512)] public InputKey subMappings__arr4;
        [FieldOffset(516)] public InputKey subMappings__arr5;
        [FieldOffset(520)] public InputKey subMappings__arr6;
        [FieldOffset(524)] public InputKey subMappings__arr7;
        [FieldOffset(528)] public InputKey subMappings__arr8;
        [FieldOffset(532)] public InputKey subMappings__arr9;
        [FieldOffset(536)] public InputKey subMappings__arr10;
        [FieldOffset(540)] public InputKey subMappings__arr11;
        [FieldOffset(544)] public InputKey subMappings__arr12;
        [FieldOffset(548)] public InputKey subMappings__arr13;
        [FieldOffset(552)] public InputKey subMappings__arr14;
        [FieldOffset(556)] public InputKey subMappings__arr15;
        [FieldOffset(560)] public InputKey subMappings__arr16;
        [FieldOffset(564)] public InputKey subMappings__arr17;
        [FieldOffset(568)] public InputKey subMappings__arr18;
        [FieldOffset(572)] public InputKey subMappings__arr19;
        [FieldOffset(576)] public InputKey subMappings__arr20;
        [FieldOffset(580)] public InputKey subMappings__arr21;
        [FieldOffset(584)] public InputKey subMappings__arr22;
        [FieldOffset(588)] public InputKey subMappings__arr23;
        [FieldOffset(592)] public InputKey subMappings__arr24;
        [FieldOffset(596)] public InputKey subMappings__arr25;
        [FieldOffset(600)] public InputKey subMappings__arr26;
        [FieldOffset(604)] public InputKey subMappings__arr27;
        [FieldOffset(608)] public InputKey subMappings__arr28;
        [FieldOffset(612)] public InputKey subMappings__arr29;
        [FieldOffset(616)] public InputKey subMappings__arr30;
        [FieldOffset(620)] public InputKey subMappings__arr31;
        [FieldOffset(624)] public InputKey subMappings__arr32;
        [FieldOffset(628)] public InputKey subMappings__arr33;
        [FieldOffset(632)] public InputKey subMappings__arr34;
        [FieldOffset(636)] public InputKey subMappings__arr35;
        [FieldOffset(640)] public InputKey subMappings__arr36;
        [FieldOffset(644)] public InputKey subMappings__arr37;
        [FieldOffset(648)] public InputKey subMappings__arr38;
        [FieldOffset(652)] public InputKey subMappings__arr39;
        [FieldOffset(656)] public InputKey subMappings__arr40;
        [FieldOffset(660)] public InputKey subMappings__arr41;
        [FieldOffset(664)] public InputKey subMappings__arr42;
        [FieldOffset(668)] public InputKey subMappings__arr43;
        [FieldOffset(672)] public InputKey subMappings__arr44;
        [FieldOffset(676)] public InputKey subMappings__arr45;
        [FieldOffset(680)] public InputKey subMappings__arr46;
        [FieldOffset(684)] public InputKey subMappings__arr47;
        [FieldOffset(688)] public InputKey subMappings__arr48;
        [FieldOffset(692)] public InputKey subMappings__arr49;
        [FieldOffset(696)] public InputKey subMappings__arr50;
        [FieldOffset(700)] public InputKey subMappings__arr51;
        [FieldOffset(704)] public InputKey subMappings__arr52;
        [FieldOffset(708)] public InputKey subMappings__arr53;
        [FieldOffset(712)] public InputKey subMappings__arr54;
        [FieldOffset(716)] public InputKey subMappings__arr55;
        [FieldOffset(720)] public InputKey subMappings__arr56;
        [FieldOffset(724)] public InputKey subMappings__arr57;
        [FieldOffset(728)] public InputKey subMappings__arr58;
        [FieldOffset(732)] public InputKey subMappings__arr59;
        [FieldOffset(736)] public InputKey subMappings__arr60;
        [FieldOffset(740)] public InputKey subMappings__arr61;
    }

    public enum MovementStyle : sbyte
    {
        PadSimulate = 0,
        Aiming = 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public struct OptionCameraData
    {
        [FieldOffset(0)]  public float rotateSpeedPad;
        [FieldOffset(4)]  public float rotateSpeedVertMouse;
        [FieldOffset(8)]  public float rotateSpeedHorzMouse;
        [FieldOffset(12)] public float reticleSpeedPad;
        [FieldOffset(16)] public float reticleSpeedVertMouse;
        [FieldOffset(20)] public float reticleSpeedHorzMouse;
        [FieldOffset(24)] public byte rotateSpeedRate;
        [FieldOffset(25)] public byte distanceRate;
        [FieldOffset(26)] public byte fovyRate;
        [FieldOffset(27)] public MovementStyle movementStyle;
        [FieldOffset(28)] public byte config;
        [FieldOffset(32)] public uint reserved__arr0;
        [FieldOffset(36)] public uint reserved__arr1;
        [FieldOffset(40)] public uint reserved__arr2;
        [FieldOffset(44)] public uint reserved__arr3;
    }

    public enum MusicSelect : sbyte
    {
        MUSIC_SELECT_ON = 0,
        MUSIC_SELECT_OFF = 1
    }

    public enum MusicSelectType : sbyte
    {
        MUSIC_SELECT_NORMAL = 0,
        MUSIC_SELECT_SHUFFLE = 1,
        MUSIC_SELECT_LOOP = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 20)]
    public struct OptionAudioData
    {
        [FieldOffset(0)] public byte masterVolume;
        [FieldOffset(1)] public byte sfxVolume;
        [FieldOffset(2)] public byte musicVolume;
        [FieldOffset(3)] public byte voiceVolume;
        [FieldOffset(4)] public MusicSelect musicSelectEnable;
        [FieldOffset(5)] public MusicSelectType musicSelectType;
        [FieldOffset(6)] public byte flags;
        [FieldOffset(7)] public byte padding;
        [FieldOffset(8)] public uint reserved__arr0;
        [FieldOffset(12)] public uint reserved__arr1;
        [FieldOffset(16)] public uint reserved__arr2;
    }

    public enum Resolution : sbyte
    {
        Reso3840x2160 = 0,
        Reso2560x1440 = 1,
        Reso1920x1080 = 2,
        Reso1280x720 = 3
    }

    public enum GraphicQuality : sbyte
    {
        GraphicQuality_High = 0,
        GraphicQuality_Low = 1,
        Custom = 2
    }

    public enum FrameRate : sbyte
    {
        FPS60 = 0,
        FPS30 = 1,
        FPSNoLimit = 2
    }

    public enum AntiAliasing : sbyte
    {
        TAA = 0,
        FXAA = 1,
        AntiAliasing_None = 2
    }

    public enum AnisotropicFiltering : sbyte
    {
        AnisotropicFiltering_None = 0,
        AnisotropicFiltering_Low = 1,
        AnisotropicFiltering_Medium = 2,
        AnisotropicFiltering_High = 3
    }

    public enum DOF : sbyte
    {
        Disabled = 0,
        DOF_Low = 1,
        DOF_Medium = 2,
        DOF_High = 3
    }

    public enum Bloom : sbyte
    {
        Bloom_High = 0,
        Bloom_Low = 1
    }

    public enum Shadow : sbyte
    {
        Shadow_High = 0,
        Shadow_Low = 1
    }

    public enum VolumetricLight : sbyte
    {
        VolumetricLight_High = 0,
        VolumetricLight_Low = 1
    }

    public enum RederingScale : sbyte
    {
        RederingScale_High = 0,
        RederingScale_Medium = 1,
        RederingScale_Low = 2
    }

    [StructLayout(LayoutKind.Explicit, Size = 28)]
    public struct OptionGraphicsData
    {
        [FieldOffset(0)]  public Resolution resolution;
        [FieldOffset(1)]  public GraphicQuality graphicQuality;
        [FieldOffset(2)]  public FrameRate frameRate;
        [FieldOffset(3)]  public byte brightness;
        [FieldOffset(4)]  public AntiAliasing antiAliasing;
        [FieldOffset(5)]  public AnisotropicFiltering anisotropicFiltering;
        [FieldOffset(6)]  public DOF depthOfField;
        [FieldOffset(7)]  public Bloom bloom;
        [FieldOffset(8)]  public byte config;
        [FieldOffset(9)]  public byte hudVisible;
        [FieldOffset(10)] public Shadow shadow;
        [FieldOffset(11)] public VolumetricLight volumetricLight;
        [FieldOffset(12)] public RederingScale renderingScale;
        [FieldOffset(13)] public byte reserved1;
        [FieldOffset(14)] public ushort width;
        [FieldOffset(16)] public ushort height;
        [FieldOffset(18)] public ushort padding0;
        [FieldOffset(20)] public uint reserved__arr0;
        [FieldOffset(24)] public uint reserved__arr1;
    }

    [StructLayout(LayoutKind.Explicit, Size = 912)]
    public struct OptionData
    {
        [FieldOffset(0)]   public HeaderData header;
        [FieldOffset(40)]  public OptionGamePlayData gameplay;
        [FieldOffset(72)]  public OptionControlsData controls;
        [FieldOffset(816)] public OptionCameraData camera;
        [FieldOffset(864)] public OptionAudioData audio;
        [FieldOffset(884)] public OptionGraphicsData graphics;
    }

}