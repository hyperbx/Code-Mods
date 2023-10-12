#pragma once

// Hooks
CL_SCAN_SIGNATURE(m_SigStatePluginBoostUpdate, 0x1408D4250, "\x40\x53\x48\x83\xEC\x30\x48\x8B\xD9\x0F\x29\x74\x24\x20\x48\x8B\x49\x20\xBA", "xxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStatePluginBoostRechargeMode, 0x1408D35B0, "\x40\x53\x48\x83\xEC\x20\x0F\xBE\x91\x84\x00\x00\x00", "xxxxxxxxxxxxx");

// Patches
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigInfiniteBoostGaugeCode, 0x1408D45EA, "\xF3\x0F\x11\x4F\x3C\x48\x8B\xCF", "xxxxxxxx");

enum EStatePluginBoostFlags
{
	EStatePluginBoostFlags_IsBoostAvailable,
	EStatePluginBoostFlags_IsInfiniteBoostCode
};

class StatePluginBoost
{
public:
	inline static std::bitset<2> Flags;

	inline static float* pCapacity;
	inline static float* pCapacityMax;
	inline static float* pInfiniteGaugeTimer;

	inline static bool IsRecharge = true;

	static bool CanConsumeBoost()
	{
		return !Flags.test(EStatePluginBoostFlags_IsInfiniteBoostCode) &&
			pCapacity != nullptr &&
			pInfiniteGaugeTimer != nullptr &&
			*pInfiniteGaugeTimer <= 0.0f;
	}

	static void Install();
};

