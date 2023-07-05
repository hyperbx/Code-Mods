#pragma once

#include <memory>
#include <unordered_map>
#include <Xinput.h>

class InputHelper
{
public:
	struct AnalogKey
	{
		int m_LowKey;
		int m_HighKey;

		AnalogKey() { }

		AnalogKey(int in_lowKey, int in_highKey)
		{
			m_LowKey  = in_lowKey;
			m_HighKey = in_highKey;
		}
	};

private:
	std::unordered_map<int, int> m_InputMap;
	std::unordered_map<int, AnalogKey> m_AnalogMap;
	std::unordered_map<int, int> m_TriggerMap;

	XINPUT_STATE m_PadState;

public:
	inline static std::unique_ptr<InputHelper> Instance;

	InputHelper()
	{
		ZeroMemory(&m_PadState, sizeof(XINPUT_STATE));
	}

	static void Install()
	{
		Instance.reset(new InputHelper());
	}

	void AddInput(int in_button, int in_key = 0)
	{
		m_InputMap.emplace(in_button, in_key);
	}

	void AddInput(std::pair<int, int> in_buttonKeyPair)
	{
		m_InputMap.emplace(in_buttonKeyPair.first, in_buttonKeyPair.second);
	}

	void RemoveInput(int in_button)
	{
		m_InputMap.erase(in_button);
	}

	void SetInputMap(std::unordered_map<int, int> in_inputMap)
	{
		m_InputMap = in_inputMap;
	}

	void AddAnalog(int in_analog, AnalogKey in_key = { 0, 0 })
	{
		m_AnalogMap.emplace(in_analog, in_key);
	}

	void RemoveAnalog(int in_analog)
	{
		m_AnalogMap.erase(in_analog);
	}

	void SetAnalogMap(std::unordered_map<int, AnalogKey> in_analogMap)
	{
		m_AnalogMap = in_analogMap;
	}

	void AddTrigger(int in_trigger, int in_key = 0)
	{
		m_TriggerMap.emplace(in_trigger, in_key);
	}

	void AddTrigger(std::pair<int, int> in_triggerKeyPair)
	{
		m_TriggerMap.emplace(in_triggerKeyPair.first, in_triggerKeyPair.second);
	}

	void RemoveTrigger(int in_trigger)
	{
		m_TriggerMap.erase(in_trigger);
	}

	void SetTriggerMap(std::unordered_map<int, int> in_triggerMap)
	{
		m_TriggerMap = in_triggerMap;
	}

	int16_t GetAnalogInput(int in_analog, bool in_testDeadzone = true, int in_playerIndex = 0)
	{
		DWORD result = XInputGetState(in_playerIndex, &m_PadState);
		AnalogKey key = m_AnalogMap[in_analog];

		if (GetAsyncKeyState(key.m_LowKey) & 0x8000)
		{
			return -65535;
		}
		else if (GetAsyncKeyState(key.m_HighKey) & 0x8000)
		{
			return 65535;
		}

		if (result == ERROR_SUCCESS)
		{
			short analog = 0;

			switch (in_analog)
			{
				case VK_PAD_LTHUMB_LEFT:
				case VK_PAD_LTHUMB_RIGHT:
					analog = m_PadState.Gamepad.sThumbLX;
					break;

				case VK_PAD_LTHUMB_UP:
				case VK_PAD_LTHUMB_DOWN:
					analog = m_PadState.Gamepad.sThumbLY;
					break;

				case VK_PAD_RTHUMB_LEFT:
				case VK_PAD_RTHUMB_RIGHT:
					analog = m_PadState.Gamepad.sThumbRX;
					break;

				case VK_PAD_RTHUMB_UP:
				case VK_PAD_RTHUMB_DOWN:
					analog = m_PadState.Gamepad.sThumbRY;
					break;

				default:
					analog = 0;
					break;
			}

			if (in_testDeadzone)
				analog = IsAnalogNeutral(in_analog, in_playerIndex) ? 0 : analog;

			return analog;
		}
	}

	bool IsAnalogNeutral(int in_analog, int in_playerIndex = 0)
	{
		switch (in_analog)
		{
			case VK_PAD_LTHUMB_UP:
			case VK_PAD_LTHUMB_DOWN:
			case VK_PAD_LTHUMB_LEFT:
			case VK_PAD_LTHUMB_RIGHT:
			{
				auto x = GetAnalogInput(VK_PAD_LTHUMB_LEFT, in_playerIndex);
				auto y = GetAnalogInput(VK_PAD_LTHUMB_UP, in_playerIndex);

				return x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			}

			case VK_PAD_RTHUMB_UP:
			case VK_PAD_RTHUMB_DOWN:
			case VK_PAD_RTHUMB_LEFT:
			case VK_PAD_RTHUMB_RIGHT:
			{
				auto x = GetAnalogInput(VK_PAD_RTHUMB_LEFT, in_playerIndex);
				auto y = GetAnalogInput(VK_PAD_RTHUMB_UP, in_playerIndex);

				return x < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					x > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					y > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			}
		}
	}

	uint8_t GetTriggerInput(int in_trigger, int in_playerIndex = 0)
	{
		DWORD result = XInputGetState(in_playerIndex, &m_PadState);
		int key = m_TriggerMap[in_trigger];

		if (GetAsyncKeyState(key) & 0x8000)
			return 255;

		if (result == ERROR_SUCCESS)
		{
			switch (in_trigger)
			{
				case VK_PAD_LTRIGGER:
					return m_PadState.Gamepad.bLeftTrigger;

				case VK_PAD_RTRIGGER:
					return m_PadState.Gamepad.bRightTrigger;

				default:
					return 0;
			}
		}
	}

	bool GetInputDown(int in_button, int in_playerIndex = 0)
	{
		DWORD result = XInputGetState(in_playerIndex, &m_PadState);
		int key = m_InputMap[in_button];

		if (GetAsyncKeyState(key) & 0x8000)
			return true;

		if (result == ERROR_SUCCESS)
		{
			if (m_PadState.Gamepad.wButtons & in_button)
				return true;
		}

		return false;
	}
};