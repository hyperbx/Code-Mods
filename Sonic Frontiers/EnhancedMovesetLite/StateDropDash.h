#pragma once

// Hooks
CL_SCAN_SIGNATURE(m_SigStateDropDashStart, 0x140896790, "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x50\x48\x8B\xE9\x48\x8B\xF2", "xxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDropDashUpdate, 0x1408969D0, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x30\x48\x8B\xF1\x0F", "xxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDropDashEnd, 0x140896950, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\xFA\x48\x8B\xCA\xE8\xCC\xCC\xCC\xCC\xB2", "xxxxxxxxxxxxxxxxxxxx????x");
CL_SCAN_SIGNATURE(m_SigPostureDropDashUpdate, 0x140837C60, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x81\xEC\x90\x00\x00\x00\x48\x8B\x71\x18", "xxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDoubleJumpUpdate, 0x14B52AA50, "\x48\x89\x5C\x24\x10\x57\x48\x83\xEC\x30\x0F\xB6\x81", "xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDoubleJumpEnd, 0x14B4FD680, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\x42\x50\x48\x89\xD7\x48\x89\xCE\x8B\x1D", "xxxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateRecoveryJumpUpdate, 0x1408A0A10, "\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x30\x48\x8B\xFA\x0F\x29\x74\x24\x20\x48\x8B\xF1", "xxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateRecoveryJumpEnd, 0x1408A0480, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x8B\xCA\x41\x8B\xD8\x48\x8B\xFA\xE8\xCC\xCC\xCC\xCC\x48\x8B\xCF", "xxxxxxxxxxxxxxxxxxxx????xxx");
CL_SCAN_SIGNATURE(m_SigObjFanProcessMessage, 0x148DEACE0, "\x48\x89\x5C\x24\x08\x55\x56\x57\x48\x8D\x6C\x24\xB9\x48\x81\xEC\x00\x01\x00\x00\x44", "xxxxxxxxxxxxxxxxxxxxx");

// Patches
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDropDashCameraDelay, 0x1408968E2, "\x73\x2A\xF3\x0F\x10\x05\xCC\xCC\xCC\xCC\x45\x33\xC9", "xxxxxx????xxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigFixDropDashSideView, 0x140837CB8, "\x74\x10\x0F\x28\xCF", "xxxxx");

enum EStateDropDashFlags
{
	EStateDropDashFlags_IsActive,
	EStateDropDashFlags_IsCharging,
	EStateDropDashFlags_IsGroundedOnce,
};

class StateDropDash
{
public:
	inline static std::bitset<3> Flags;

	static bool IsUngroundedExit()
	{
		if (BlackboardHelper::IsCyberSpace() || BlackboardHelper::IsSideView())
			return false;

		return Configuration::IsDropDashCancelWhenUngrounded;
	}

	static bool IsNormalDropDash()
	{
		return Flags.test(EStateDropDashFlags_IsActive) &&
			!StateAirDash::Flags.test(EStateAirDashFlags_IsActive) &&
			!StateSlideDash::Flags.test(EStateSlideDashFlags_IsActive) &&
			!StateQuickStompDash::Flags.test(EStateQuickStompDashFlags_IsActive);
	}

	static bool IsNoCameraDelay()
	{
		return Configuration::IsDropDashNoCameraDelay && IsNormalDropDash() ||
			Configuration::IsAirDashNoCameraDelay && StateAirDash::Flags.test(EStateAirDashFlags_IsActive) ||
			Configuration::IsSlideDashNoDropDashCameraDelay && StateSlideDash::Flags.test(EStateSlideDashFlags_IsActive) ||
			Configuration::IsQuickStompDashNoCameraDelay && StateQuickStompDash::Flags.test(EStateQuickStompDashFlags_IsActive);
	}

	static void Install();
};