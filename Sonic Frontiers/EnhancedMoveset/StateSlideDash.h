#pragma once

// Hooks
CL_SCAN_SIGNATURE(m_SigStateSquatUpdate, 0x14B604760, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x0F\xB6\x99\xB0\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxxx");

// Required Patches
CL_SCAN_SIGNATURE(m_SigPreventSquatToSlide, 0x14B604792, "\x75\x27\x45\x31\xC0\x48\x89\xF9", "xxxxxxxx");

enum EStateSlideDashFlags
{
	EStateSlideDashFlags_IsActive
};

class StateSlideDash
{
public:
	inline static std::bitset<1> Flags;

	static void Install();
};

