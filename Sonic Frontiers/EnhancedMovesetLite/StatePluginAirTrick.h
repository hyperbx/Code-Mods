#pragma once

CL_SCAN_SIGNATURE(m_SigStatePluginAirTrickUpdate, 0x1408CC830, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x55\x57\x41\x56\x48\x8D\x6C\x24\xB9\x48\x81\xEC\xC0\x00\x00\x00\x48\x8B\x71\x20", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

enum EStatePluginAirTrickFlags
{
	EStatePluginAirTrickFlags_IsFatigueStart
};

class StatePluginAirTrick
{
public:
	inline static std::bitset<1> Flags;

	inline static float TrickReward = 0.0f;
	inline static float TrickFatigueTimer = 0.0f;

	inline static int LastTrickDirection = 0;

	static void Install();
};

