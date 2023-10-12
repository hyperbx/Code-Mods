#pragma once

CL_SCAN_SIGNATURE(m_SigStateAvoidProcessMessage, 0x1408707F0, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x20\x41\x8B", "xxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigActionProcessor, 0x1408FBC00, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x60\x48\x0F\xBE\xF2", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

enum EStateFlurryRushFlags
{
	EStateFlurryRushFlags_IsActive
};

class StateFlurryRush
{
public:
	inline static std::bitset<1> Flags;

	inline static float FlurryRushTimer = 0.0f;

	static void Install();
};

