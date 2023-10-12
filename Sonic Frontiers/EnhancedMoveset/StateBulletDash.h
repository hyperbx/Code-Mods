#pragma once

// Hooks
CL_SCAN_SIGNATURE(m_SigStateStompingLandStart, 0x1408AC9F0, "\x48\x8B\xC4\x53\x48\x83\xEC\x60\x48\x89", "xxxxxxxxxx");

// Required Patches
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeMovement, 0x14084E089, "\x0F\x85\x83\x02\x00\x00\x0F\x10\x9F\x20\x01\x00\x00", "xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinChargePitchReset, 0x1407F158F, "\xE8\xCC\xCC\xCC\xCC\xB8\x60\x00\x00\x00\x48\x8D\x93\x50\x01\x00\x00", "x????xxxxxxxxxxxx");

enum EStateBulletDashFlags
{
	EStateBulletDashFlags_IsActive,
	EStateBulletDashFlags_IsCharging,
	EStateBulletDashFlags_IsForwardRestored,
	EStateBulletDashFlags_IsReleased,
	EStateBulletDashFlags_IsSuperStompTrajectory,
	EStateBulletDashFlags_IsSuperStompLand
};

class StateBulletDash
{
public:
	inline static std::bitset<6> Flags;

	inline static csl::math::Vector3 Forward;

	inline static float YawScale = 0.0f;
	inline static float PitchScale = 0.0f;

	static void Install();
};

