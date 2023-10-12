#pragma once

// Hooks
CL_SCAN_SIGNATURE(m_SigStateSpinBoostStart, 0x1408A6300, "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x20\x56\x57\x41\x56\x48\x83\xEC\x50\x45\x8B\xF0", "xxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateSpinBoostUpdate, 0x1408A6B30, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x60\x0F\x29\x74\x24\x50", "xxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateSpinBoostEnd, 0x1408A6810, "\x48\x8B\xC4\x55\x56\x48\x83\xEC\x68", "xxxxxxxxx");

// Patches
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigAlwaysTrickableSpinBoostExit, 0x1408A5B97, "\x41\x8D\x50\x04\x48\x8B\xCF\xE8\xCC\xCC\xCC\xCC\xB0\x01", "xxxxxxxx????xx");

enum EStateSpinBoostFlags
{
	EStateSpinBoostFlags_IsDoubleJump,
	EStateSpinBoostFlags_IsJump,
	EStateSpinBoostFlags_IsSpinMove,
	EStateSpinBoostFlags_IsRecoveryJump
};

class StateSpinBoost
{
public:
	inline static std::bitset<4> Flags;

	static void Install();
};

