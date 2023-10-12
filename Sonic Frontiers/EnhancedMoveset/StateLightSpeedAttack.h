#pragma once

CL_SCAN_SIGNATURE(m_SigEnemyAquaballStateCaptureStart, 0x1404B9E90, "\x48\x89\x5C\x24\x10\x57\x48\x81\xEC\xB0\x00\x00\x00\x48\x8B\x79\x28", "xxxxxxxxxxxxxxxxx");

enum EStateLightSpeedAttackFlags
{
	EStateLightSpeedAttackFlags_IsActive,
	EStateLightSpeedAttackFlags_IsHoming
};

class StateLightSpeedAttack
{
public:
	inline static std::bitset<2> Flags;

	inline static float ChargeTime = 0.0f;
	inline static float ChainTime = 0.0f;

	static void Install();
};

