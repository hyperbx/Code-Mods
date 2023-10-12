#pragma once

#include <Signature.h>
#include <Xinput.h>
#include <Steamworks/steam/steam_api.h>
#include <Steamworks/steam/isteamdualsense.h>

#define IsButtonPressed(in_actionType) Input::IsPressed(in_pSonicContext, in_actionType)
#define IsButtonDown(in_actionType) Input::IsDown(in_pSonicContext, in_actionType)
#define IsButtonReleased(in_actionType) Input::IsReleased(in_pSonicContext, in_actionType)

CL_SCAN_SIGNATURE(m_SigIsPressed, 0x1408F6400, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x63\xFA\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD8\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD0\x48\x8B\xCB\xE8\xCC\xCC\xCC\xCC\x48\x8B\x5C\x24\x30\x48\x8B\x80\x90\x00\x00\x00\x48\x8B\x48\x78\x0F\xB6\x44\xF9\x07\xD0", "xxxxxxxxxxxxxx????xxxx????xxxxxxx????xxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigIsDown, 0x1408F65D0, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x63\xFA\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD8\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD0\x48\x8B\xCB\xE8\xCC\xCC\xCC\xCC\x48\x8B\x5C\x24\x30\x48\x8B\x80\x90\x00\x00\x00\x48\x8B\x48\x78\x0F\xB6\x44\xF9\x07\xF6", "xxxxxxxxxxxxxx????xxxx????xxxxxxx????xxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigIsReleased, 0x1408F6580, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x63\xFA\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD8\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD0\x48\x8B\xCB\xE8\xCC\xCC\xCC\xCC\x48\x8B\x5C\x24\x30\x48\x8B\x80\x90\x00\x00\x00\x48\x8B\x48\x78\x0F\xB6\x44\xF9\x07\xC0", "xxxxxxxxxxxxxx????xxxx????xxxxxxx????xxxxxxxxxxxxxxxxxxxxxx");

enum EPlayerActionType
{
	// A
	EPlayerActionType_PlayerJump = 0,

	// Y
	EPlayerActionType_PlayerCyloop = 1,

	// X
	EPlayerActionType_PlayerAttack = 2,

	// LS
	EPlayerActionType_PlayerLightDash = 3,

	// RT
	EPlayerActionType_PlayerBoost = 4,

	// Unknown
	EPlayerActionType_PlayerDrift = 5,

	// Unknown
	EPlayerActionType_PlayerChangeSuperSonic = 6,

	// LB
	EPlayerActionType_PlayerLeftStep = 7,

	// RB
	EPlayerActionType_PlayerRightStep = 8,

	// B
	EPlayerActionType_PlayerStomping = 9,

	// Unknown
	EPlayerActionType_PlayerAction = 10,

	// Unknown
	EPlayerActionType_PlayerActionAlways = 11,

	// Unknown
	EPlayerActionType_PlayerSmash = 12,

	// RS
	EPlayerActionType_CameraGaze = 13,

	// LT
	EPlayerActionType_PlayerSonicboom = 14
};

class Input
{
	inline static XINPUT_STATE m_XInputState;

	inline static bool m_IsXInputInitialised = false;

	inline static float m_LeftMotor = 0;
	inline static float m_RightMotor = 0;
	inline static float m_LeftTriggerMotor = 0;
	inline static float m_RightTriggerMotor = 0;

public:
	static enum EInputIndex
	{
		EInputIndex_Left,
		EInputIndex_Right
	};

	static bool IsPressed(int64_t in_pSonicContext, EPlayerActionType in_actionType)
	{
		FUNCTION_PTR(bool, __fastcall, fpIsPressed, m_SigIsPressed(), int64_t in_pSonicContext, EPlayerActionType in_actionType);

		return fpIsPressed(in_pSonicContext, in_actionType);
	}

	static bool IsDown(int64_t in_pSonicContext, EPlayerActionType in_actionType)
	{
		FUNCTION_PTR(bool, __fastcall, fpIsDown, m_SigIsDown(), int64_t in_pSonicContext, EPlayerActionType in_actionType);

		return !fpIsDown(in_pSonicContext, in_actionType);
	}

	static bool IsReleased(int64_t in_pSonicContext, EPlayerActionType in_actionType)
	{
		FUNCTION_PTR(bool, __fastcall, fpIsReleased, m_SigIsReleased(), int64_t in_pSonicContext, EPlayerActionType in_actionType);

		return fpIsReleased(in_pSonicContext, in_actionType);
	}

	static uint32_t GetState()
	{
		if (!m_IsXInputInitialised)
		{
			ZeroMemory(&m_XInputState, sizeof(XINPUT_STATE));

			m_IsXInputInitialised = true;
		}

		return XInputGetState(0, &m_XInputState);
	}

	static csl::math::Vector2 GetAnalog(EInputIndex in_index = EInputIndex_Left, bool in_testDeadZone = true)
	{
		bool isKeyboard = false;
		float x = 0.0f;
		float y = 0.0f;

		if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
		{
			y = 1.0f;
			isKeyboard = true;
		}

		if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
		{
			y = -1.0f;
			isKeyboard = true;
		}

		if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
		{
			x = -1.0f;
			isKeyboard = true;
		}

		if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
		{
			x = 1.0f;
			isKeyboard = true;
		}

		if (isKeyboard)
			return csl::math::Vector2(x, y);

		if (GetState() == ERROR_SUCCESS)
		{
			csl::math::Vector2 v;

			switch (in_index)
			{
				case EInputIndex_Left:
					v = csl::math::Vector2(m_XInputState.Gamepad.sThumbLX / 32767.0f, m_XInputState.Gamepad.sThumbLY / 32767.0f);
					break;

				case EInputIndex_Right:
					v = csl::math::Vector2(m_XInputState.Gamepad.sThumbRX / 32767.0f, m_XInputState.Gamepad.sThumbRY / 32767.0f);
					break;
			}

			if (in_testDeadZone)
			{
				v = IsAnalogNeutral(in_index)
					? *csl::math::Vector2::Zero
					: v;
			}

			return v;
		}

		return *csl::math::Vector2::Zero;
	}

	static bool IsAnalogNeutral(EInputIndex in_index)
	{
		if (GetState() != ERROR_SUCCESS)
			return true;

		switch (in_index)
		{
			case EInputIndex_Left:
			{
				auto x = m_XInputState.Gamepad.sThumbLX;
				auto y = m_XInputState.Gamepad.sThumbLY;

				return x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			}

			case EInputIndex_Right:
			{
				auto x = m_XInputState.Gamepad.sThumbRX;
				auto y = m_XInputState.Gamepad.sThumbRY;

				return x < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					x > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					y > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			}
		}

		return true;
	}

	static void SetRumbleMotor(EInputIndex in_index, float in_value)
	{
		auto handle = SteamInput()->GetControllerForGamepadIndex(0);

		switch (in_index)
		{
			case EInputIndex_Left:
				m_LeftMotor = in_value;
				break;

			case EInputIndex_Right:
				m_RightMotor = in_value;
				break;
		}

		SteamInput()->TriggerVibrationExtended
		(
			handle,
			FLOAT_PERCENT_TO_UINT16(m_LeftMotor),
			FLOAT_PERCENT_TO_UINT16(m_RightMotor),
			FLOAT_PERCENT_TO_UINT16(m_LeftTriggerMotor),
			FLOAT_PERCENT_TO_UINT16(m_RightTriggerMotor)
		);
	}

	static void SetRumbleMotors(float in_value)
	{
		SetRumbleMotor(EInputIndex_Left, in_value);
		SetRumbleMotor(EInputIndex_Right, in_value);
	}

	static void ResetRumbleMotors()
	{
		SetRumbleMotor(EInputIndex_Left, 0.0f);
		SetRumbleMotor(EInputIndex_Right, 0.0f);
	}

	static void SetTriggerMotor(EInputIndex in_index, float in_value)
	{
		auto handle = SteamInput()->GetControllerForGamepadIndex(0);

		ScePadTriggerEffectParam param;
		memset(&param, 0, sizeof(param));

		param.triggerMask = SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_L2;

		switch (in_index)
		{
			case EInputIndex_Left:
				m_LeftTriggerMotor = in_value;
				param.triggerMask = SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_L2;
				break;

			case EInputIndex_Right:
				m_RightTriggerMotor = in_value;
				param.triggerMask = SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_R2;
				break;
		}

		/* Valve, why the fuck is your example passing
		   in a constant that starts at index 1? */
		int triggerIndex = param.triggerMask - 1;

		param.command[triggerIndex].mode = SCE_PAD_TRIGGER_EFFECT_MODE_VIBRATION;
		param.command[triggerIndex].commandData.vibrationParam.position = 0;
		param.command[triggerIndex].commandData.vibrationParam.amplitude = 5;
		param.command[triggerIndex].commandData.vibrationParam.frequency = FLOAT_PERCENT_TO_UINT8(in_value);

		SteamInput()->SetDualSenseTriggerEffect(handle, &param);

		SteamInput()->TriggerVibrationExtended
		(
			handle,
			FLOAT_PERCENT_TO_UINT16(m_LeftMotor),
			FLOAT_PERCENT_TO_UINT16(m_RightMotor),
			FLOAT_PERCENT_TO_UINT16(m_LeftTriggerMotor),
			FLOAT_PERCENT_TO_UINT16(m_RightTriggerMotor)
		);
	}

	static void SetTriggerMotors(float in_value)
	{
		SetTriggerMotor(EInputIndex_Left, in_value);
		SetTriggerMotor(EInputIndex_Right, in_value);
	}

	static void ResetTriggerMotors()
	{
		SetTriggerMotor(EInputIndex_Left, 0.0f);
		SetTriggerMotor(EInputIndex_Right, 0.0f);
	}

	static void ResetMotors()
	{
		ResetRumbleMotors();
		ResetTriggerMotors();
	}
};

