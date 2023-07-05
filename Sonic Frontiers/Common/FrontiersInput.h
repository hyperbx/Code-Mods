#pragma once

#define TRIGGER_THRESHOLD 3

#define FINPUT FrontiersInput::GetOptionData()->controls

#include <Signature.h>
#include <InputHelper.h>

inline static int64_t m_OptionDataSingleton;

CL_SCAN_SIGNATURE(m_SigOptionDataReader, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x60\x48\x89\xD7\x48\x89\xCB\x48\x8D\x15\xCC\xCC\xCC\xCC\x45\x31\xC0\x48\x8D\x0D\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x84\xC0\xC7\x44\x24\x24\x03\x00\x00\x00\x48\x8D\x0D\xCC\xCC\xCC\xCC\xBE\x01\x00\x00\x00\x4C\x8D\x05\xCC\xCC\xCC\xCC\x48\x89\x74\x24\x40\x4C\x0F\x44\xC1\x89", "xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx????x????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigOptionDataWriter, "\x48\x89\x5C\x24\x10\x56\x48\x81\xEC\xA0\x00\x00\x00\x4C\x8B\x81\x98\x00\x00\x00\x48\x89", "xxxxxxxxxxxxxxxxxxxxxx");

INLINE_HOOK(int64_t, __fastcall, OptionDataReader, m_SigOptionDataReader(), int64_t* a1, int64_t* a2)
{
	m_OptionDataSingleton = (*(int64_t*)a1[19]) + 0x150B80;

	return originalOptionDataReader(a1, a2);
}

INLINE_HOOK(int64_t, __fastcall, OptionDataWriter, m_SigOptionDataWriter(), int64_t* a1, int64_t* a2)
{
	m_OptionDataSingleton = (*(int64_t*)a1[19]) + 0x150B80;

	return originalOptionDataWriter(a1, a2);
}

class FrontiersInput
{
public:
	enum Status : int8_t
	{
		STATUS_ZERO_FILL = 0,
		STATUS_INITIALIZED = 1,
	};

	enum Sequence : int8_t
	{
		Island1 = 0,
		Island2 = 1,
		Island3 = 2,
		Island4 = 3,
		Island5 = 4,
		FinalBossBefore = 5,
		FinalBossAfter = 6,
	};

	enum SaveDataIcon : int8_t
	{
		IconNoData = 0,
		IconIsland1 = 1,
		IconIsland2 = 2,
		IconIsland3 = 3,
		IconIsland4 = 4,
		IconIsland5 = 5,
		IconLastBoss = 6,
	};

	enum AppVersion : uint8_t
	{
		AppVersion_1_10 = 0,
		AppVersion_1_20 = 1,
		AppVersion_1_30 = 2,
		AppVersion_1_40 = 3,
	};

	typedef struct
	{
		/// <summary>
		/// シグニチャ
		/// </summary>
		uint32_t signature;

		/// <summary>
		/// バージョン
		/// </summary>
		uint8_t version;

		/// <summary>
		/// ステータス
		/// </summary>
		Status status;

		/// <summary>
		/// コンフィグ
		/// </summary>
		uint8_t config;

		/// <summary>
		/// シーケンス
		/// </summary>
		Sequence sequence;

		/// <summary>
		/// プレイ時間
		/// </summary>
		uint32_t playTime;

		/// <summary>
		/// セーブデータアイコン
		/// </summary>
		SaveDataIcon icon;

		/// <summary>
		/// アプリバージョン
		/// </summary>
		AppVersion appVersion;

		/// <summary>
		/// コンフィグ2
		/// </summary>
		uint8_t config2;

		/// <summary>
		/// reserved1
		/// </summary>
		uint8_t reserved1;

		/// <summary>
		/// 保存日時
		/// </summary>
		uint32_t saveDate;

		/// <summary>
		/// index
		/// </summary>
		uint8_t index;

		/// <summary>
		/// reserved
		/// </summary>
		uint32_t reserved[4];

	} HeaderData;

	enum VoiceLanguageType : int8_t
	{
		VOICE_LANGUAGE_ENGLISH = 0,
		VOICE_LANGUAGE_FRENCH = 1,
		VOICE_LANGUAGE_ITALIAN = 2,
		VOICE_LANGUAGE_GERMAN = 3,
		VOICE_LANGUAGE_SPANISH = 4,
		VOICE_LANGUAGE_JAPANESE = 5,
		NUM_VOICE_LANGUAGES = 6,
	};

	enum LanguageType : int8_t
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
		NUM_LANGUAGES = 12,
	};

	enum VibrationLevel : int8_t
	{
		None = 0,
		Low = 1,
		Medium = 2,
		High = 3,
	};

	enum Value : int8_t
	{
		Easy = 0,
		Normal = 1,
		Hard = 2,
		Num = 3,
		VeryHard = 3,
		NumInVeryHard = 4,
	};

	typedef struct
	{
		/// <summary>
		/// 初速レート
		/// </summary>
		uint8_t initialSpeedRate;

		/// <summary>
		/// 初速レート/ブースト
		/// </summary>
		uint8_t boostInitialSpeedRate;

		/// <summary>
		/// 加速度レート
		/// </summary>
		uint8_t acceleRate;

		/// <summary>
		/// 最高速度レート
		/// </summary>
		uint8_t maxSpeedRate;

		/// <summary>
		/// 旋回速度レート
		/// </summary>
		uint8_t minTurnSpeedRate;

		/// <summary>
		/// 旋回速度レート/ブースト
		/// </summary>
		uint8_t boostMinTurnSpeedRate;

		/// <summary>
		/// 旋回力レート
		/// </summary>
		uint8_t rotateForceRate;

		/// <summary>
		/// バンプジャンプ重力レート
		/// </summary>
		uint8_t bumpJumpGravityRate;

		/// <summary>
		/// 音声言語
		/// </summary>
		VoiceLanguageType speech;

		/// <summary>
		/// 文字言語
		/// </summary>
		LanguageType text;

		/// <summary>
		/// 振動強度
		/// </summary>
		VibrationLevel vibrationLevel;

		/// <summary>
		/// 難易度
		/// </summary>
		Value diffculty;

		/// <summary>
		/// コンフィグ
		/// </summary>
		uint8_t config;

		/// <summary>
		/// パッド感度
		/// </summary>
		uint8_t padSensibilityRate;

		/// <summary>
		/// マウス感度
		/// </summary>
		uint8_t mouseSensibilityRate;

		/// <summary>
		/// ニュートラル停止減衰率
		/// </summary>
		uint8_t neutralDecelerationRate;

		/// <summary>
		/// [DLC]ソニック衣装
		/// </summary>
		uint8_t dlcSonicCostume;

		/// <summary>
		/// [DLC]ココの見た目
		/// </summary>
		uint8_t dlcKodamaModel;

		/// <summary>
		/// [DLC]リング取得音
		/// </summary>
		uint8_t dlcRingSE;

		/// <summary>
		/// [DLC]コンフィグ
		/// </summary>
		uint8_t dlcConfig;

		/// <summary>
		/// コンフィグ2
		/// </summary>
		uint8_t config2;

		/// <summary>
		/// 島の見た目
		/// </summary>
		uint8_t islandVisual;

		/// <summary>
		/// NPCの見た目
		/// </summary>
		uint8_t npcVisual;

		/// <summary>
		/// 基本空気抵抗スケールレート
		/// </summary>
		uint8_t baseAirDragScaleRate;

		/// <summary>
		/// ステータス
		/// </summary>
		uint32_t status;

		/// <summary>
		/// reserved2
		/// </summary>
		uint32_t reserved2;

	} OptionGamePlayData;

	enum InputKey : int32_t
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
		NumAppKeys = 150,
	};

	inline static int VirtualKeys[] =
	{
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_A,
		VK_PAD_LTHUMB_LEFT,
		VK_PAD_LTHUMB_UP,
		VK_PAD_RTHUMB_LEFT,
		VK_PAD_RTHUMB_UP,
		VK_PAD_LSHOULDER,
		VK_PAD_LTRIGGER,
		XINPUT_GAMEPAD_LEFT_THUMB,
		VK_PAD_RSHOULDER,
		VK_PAD_RTRIGGER,
		XINPUT_GAMEPAD_RIGHT_THUMB,
		VK_PAD_LTHUMB_LEFT,
		VK_PAD_LTHUMB_RIGHT,
		VK_PAD_LTHUMB_UP,
		VK_PAD_LTHUMB_DOWN,
		VK_PAD_RTHUMB_LEFT,
		VK_PAD_RTHUMB_RIGHT,
		VK_PAD_RTHUMB_UP,
		VK_PAD_RTHUMB_DOWN,
		VK_PAD_START,
		VK_PAD_BACK,
		VK_PAD_LTRIGGER,
		VK_PAD_LTRIGGER,
		VK_PAD_RTRIGGER,
		VK_PAD_RTRIGGER,
		-1, // InputKey_Keyboard_Nop
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		VK_RETURN,
		VK_ESCAPE,
		VK_BACK,
		VK_TAB,
		VK_SPACE,
		VK_OEM_MINUS,
		VK_RMENU,
		'@',
		'(',
		VK_OEM_5,
		')',
		VK_OEM_1,
		VK_OEM_1,
		VK_OEM_COMMA,
		VK_OEM_PERIOD,
		VK_OEM_2,
		VK_CAPITAL,
		VK_F1,
		VK_F2,
		VK_F3,
		VK_F4,
		VK_F5,
		VK_F6,
		VK_F7,
		VK_F8,
		VK_F9,
		VK_F10,
		VK_F11,
		VK_F12,
		VK_INSERT,
		VK_HOME,
		VK_PRIOR,
		VK_DELETE,
		VK_END,
		VK_NEXT,
		VK_LEFT,
		VK_RIGHT,
		VK_UP,
		VK_DOWN,
		VK_DIVIDE,
		VK_MULTIPLY,
		VK_SUBTRACT,
		VK_ADD,
		VK_RETURN,
		VK_NUMPAD1,
		VK_NUMPAD2,
		VK_NUMPAD3,
		VK_NUMPAD4,
		VK_NUMPAD5,
		VK_NUMPAD6,
		VK_NUMPAD7,
		VK_NUMPAD8,
		VK_NUMPAD9,
		VK_NUMPAD0,
		VK_DECIMAL,
		VK_LCONTROL,
		VK_RCONTROL,
		VK_LSHIFT,
		VK_RSHIFT,
		VK_LMENU,
		VK_RMENU,
		VK_LWIN,
		VK_RWIN,
		-1, // InputKey_Mouse_X
		-1, // InputKey_Mouse_Y
		VK_LBUTTON,
		VK_RBUTTON,
		VK_MBUTTON,
		VK_XBUTTON1,
		VK_XBUTTON2,
		-1, // InputKey_Mouse_Wheel
		-1, // InputKey_Mouse_WheelUp
		-1, // InputKey_Mouse_WheelDown
		VK_OEM_3,
		VK_OEM_PLUS,
		VK_OEM_7,
		VK_OEM_102,
		-1, // InputKey_Keyboard_ABNT_C1
		-1, // InputKey_Keyboard_ABNT_C2
		VK_SHIFT,
		VK_CONTROL
	};

	enum ActionType
	{
		ActionType_UI_Confirm = 16,
		ActionType_UI_MoveToCyberSpace = 17,
		ActionType_UI_Back = 18,
		ActionType_ACT_PauseMenu = 19,
		ActionType_ACT_Map = 20,
		ActionType_UI_ResetMap = 21,
		ActionType_UI_ReturnToDefault = 22,
		ActionType_ACT_ShowTutorialAgain = 23,
		ActionType_UI_TabLeft = 24,
		ActionType_UI_TabRight = 25,
		ActionType_ACT_MoveLeft = 26,
		ActionType_ACT_MoveRight = 27,
		ActionType_ACT_MoveForward = 28,
		ActionType_ACT_MoveBack = 29,
		ActionType_ACT_Attack = 31,
		ActionType_ACT_Jump = 32,
		ActionType_ACT_Cyloop = 33,
		ActionType_ACT_LightDash = 34,
		ActionType_ACT_Boost = 35,
		ActionType_ACT_QuickStepLeft = 38,
		ActionType_ACT_QuickStepRight = 39,
		ActionType_ACT_StompAttack = 40,
		ActionType_ACT_Attack2 = 41,
		ActionType_ACT_SonicBoom = 43,
		ActionType_ACT_CyberSpace = 44,
		ActionType_ACT_StopSlotMachine = 45,
		ActionType_ACT_LockOn = 52,
		ActionType_ACT_LockOn2 = 53,
		ActionType_UI_MoveCursorLeft = 54,
		ActionType_UI_MoveCursorRight = 55,
		ActionType_UI_MoveCursorUp = 56,
		ActionType_UI_MoveCursorDown = 57
	};

	struct OptionControlsData
	{
		/// <summary>
		/// ゲームパッド/マッピング
		/// </summary>
		InputKey padMappings[62];

		/// <summary>
		/// キーボード/マッピング/メイン
		/// </summary>
		InputKey mainMappings[62];

		/// <summary>
		/// キーボード/マッピング/サブ
		/// </summary>
		InputKey subMappings[62];

		InputKey GetInputKeyFromActionType(InputKey* in_inputKeyArr, ActionType in_actionType)
		{
			return in_inputKeyArr[in_actionType];
		}

		int GetVirtualKeyFromInputKey(InputKey in_inputKey)
		{
			return VirtualKeys[in_inputKey];
		}

		int GetVirtualKeyFromActionType(InputKey* in_inputKeyArr, ActionType in_actionType)
		{
			return VirtualKeys[GetInputKeyFromActionType(in_inputKeyArr, in_actionType)];
		}

		int GetVirtualKeyFromPadActionType(ActionType in_actionType)
		{
			return GetVirtualKeyFromActionType(padMappings, in_actionType);
		}

		int GetVirtualKeyFromKeyboardActionType(ActionType in_actionType, bool in_useSubMappings = false)
		{
			return GetVirtualKeyFromActionType(in_useSubMappings ? subMappings : mainMappings, in_actionType);
		}

		std::pair<int, int> GetVirtualKeysFromActionType(ActionType in_inputType)
		{
			return
			{
				GetVirtualKeyFromPadActionType(in_inputType),
				GetVirtualKeyFromKeyboardActionType(in_inputType)
			};
		}
	};

	enum MovementStyle : int8_t
	{
		PadSimulate = 0,
		Aiming = 1,
	};

	typedef struct
	{
		/// <summary>
		/// パッド操作時の回転速度
		/// </summary>
		float rotateSpeedPad;

		/// <summary>
		/// マウス操作時の垂直回転速度
		/// </summary>
		float rotateSpeedVertMouse;

		/// <summary>
		/// マウス操作時の水平回転速度
		/// </summary>
		float rotateSpeedHorzMouse;

		/// <summary>
		/// パッド操作時の照準速度
		/// </summary>
		float reticleSpeedPad;

		/// <summary>
		/// マウス操作時の垂直照準速度
		/// </summary>
		float reticleSpeedVertMouse;

		/// <summary>
		/// マウス操作時の水平照準速度
		/// </summary>
		float reticleSpeedHorzMouse;

		/// <summary>
		/// 回転速度レート
		/// </summary>
		uint8_t rotateSpeedRate;

		/// <summary>
		/// 距離レート
		/// </summary>
		uint8_t distanceRate;

		/// <summary>
		/// 画角レート
		/// </summary>
		uint8_t fovyRate;

		/// <summary>
		/// 移動制御
		/// </summary>
		MovementStyle movementStyle;

		/// <summary>
		/// コンフィグ
		/// </summary>
		uint8_t config;

		/// <summary>
		/// reserved
		/// </summary>
		uint32_t reserved[4];

	} OptionCameraData;

	enum MusicSelect : int8_t
	{
		MUSIC_SELECT_ON = 0,
		MUSIC_SELECT_OFF = 1,
	};

	enum MusicSelectType : int8_t
	{
		MUSIC_SELECT_NORMAL = 0,
		MUSIC_SELECT_SHUFFLE = 1,
		MUSIC_SELECT_LOOP = 2,
	};

	typedef struct
	{
		/// <summary>
		/// マスタボリューム
		/// </summary>
		uint8_t masterVolume;

		/// <summary>
		/// SEボリューム
		/// </summary>
		uint8_t sfxVolume;

		/// <summary>
		/// 音楽ボリューム
		/// </summary>
		uint8_t musicVolume;

		/// <summary>
		/// ボイスボリューム
		/// </summary>
		uint8_t voiceVolume;

		/// <summary>
		/// ミュージックセレクト機能のON・OFF
		/// </summary>
		MusicSelect musicSelectEnable;

		/// <summary>
		/// ミュージックセレクト機能の再生タイプ
		/// </summary>
		MusicSelectType musicSelectType;

		/// <summary>
		/// フラグ
		/// </summary>
		uint8_t flags;

		/// <summary>
		/// padding
		/// </summary>
		uint8_t padding;

		/// <summary>
		/// reserved
		/// </summary>
		uint32_t reserved[3];

	} OptionAudioData;

	enum Resolution : int8_t
	{
		Reso3840x2160 = 0,
		Reso2560x1440 = 1,
		Reso1920x1080 = 2,
		Reso1280x720 = 3,
	};

	enum GraphicQuality : int8_t
	{
		GraphicQuality_High = 0,
		GraphicQuality_Low = 1,
		Custom = 2,
	};

	enum FrameRate : int8_t
	{
		FPS60 = 0,
		FPS30 = 1,
		FPSNoLimit = 2,
	};

	enum AntiAliasing : int8_t
	{
		TAA = 0,
		FXAA = 1,
		AntiAliasing_None = 2,
	};

	enum AnisotropicFiltering : int8_t
	{
		AnisotropicFiltering_None = 0,
		AnisotropicFiltering_Low = 1,
		AnisotropicFiltering_Medium = 2,
		AnisotropicFiltering_High = 3,
	};

	enum DOF : int8_t
	{
		Disabled = 0,
		DOF_Low = 1,
		DOF_Medium = 2,
		DOF_High = 3,
	};

	enum Bloom : int8_t
	{
		Bloom_High = 0,
		Bloom_Low = 1,
	};

	enum Shadow : int8_t
	{
		Shadow_High = 0,
		Shadow_Low = 1,
	};

	enum VolumetricLight : int8_t
	{
		VolumetricLight_High = 0,
		VolumetricLight_Low = 1,
	};

	enum RederingScale : int8_t
	{
		RederingScale_High = 0,
		RederingScale_Medium = 1,
		RederingScale_Low = 2,
	};

	typedef struct
	{
		/// <summary>
		/// 解像度
		/// </summary>
		Resolution resolution;

		/// <summary>
		/// グラフィック品質
		/// </summary>
		GraphicQuality graphicQuality;

		/// <summary>
		/// FPS
		/// </summary>
		FrameRate frameRate;

		/// <summary>
		/// Brightness
		/// </summary>
		uint8_t brightness;

		/// <summary>
		/// AA
		/// </summary>
		AntiAliasing antiAliasing;

		/// <summary>
		/// AF
		/// </summary>
		AnisotropicFiltering anisotropicFiltering;

		/// <summary>
		/// DOF
		/// </summary>
		DOF depthOfField;

		/// <summary>
		/// Bloom
		/// </summary>
		Bloom bloom;

		/// <summary>
		/// コンフィグ
		/// </summary>
		uint8_t config;

		/// <summary>
		/// HUDの表示
		/// </summary>
		uint8_t hudVisible;

		/// <summary>
		/// 影の品質
		/// </summary>
		Shadow shadow;

		/// <summary>
		/// ボリューメトリックライト
		/// </summary>
		VolumetricLight volumetricLight;

		/// <summary>
		/// レンダリングスケール
		/// </summary>
		RederingScale renderingScale;

		/// <summary>
		/// reserved1
		/// </summary>
		uint8_t reserved1;

		/// <summary>
		/// 幅
		/// </summary>
		uint16_t width;

		/// <summary>
		/// 高さ
		/// </summary>
		uint16_t height;

		/// <summary>
		/// padding0
		/// </summary>
		uint16_t padding0;

		/// <summary>
		/// reserved
		/// </summary>
		uint32_t reserved[2];

	} OptionGraphicsData;

	typedef struct
	{
		/// <summary>
		/// ヘッダ
		/// </summary>
		HeaderData header;

		/// <summary>
		/// ゲームプレイ
		/// </summary>
		OptionGamePlayData gameplay;

		/// <summary>
		/// コントロール
		/// </summary>
		OptionControlsData controls;

		/// <summary>
		/// カメラ
		/// </summary>
		OptionCameraData camera;

		/// <summary>
		/// 音声
		/// </summary>
		OptionAudioData audio;

		/// <summary>
		/// グラフィックス
		/// </summary>
		OptionGraphicsData graphics;

	} OptionData;

	static OptionData* GetOptionData()
	{
		if (!m_OptionDataSingleton)
			return nullptr;

		return reinterpret_cast<OptionData*>(m_OptionDataSingleton);
	}

	static void Install()
	{
		INSTALL_HOOK(OptionDataReader);
		INSTALL_HOOK(OptionDataWriter);

		InputHelper::Install();
	}
};