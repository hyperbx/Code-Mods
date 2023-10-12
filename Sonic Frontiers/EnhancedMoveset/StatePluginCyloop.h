#pragma once

CL_SCAN_SIGNATURE(m_SigStateEffectCyloopUpdate, 0x1407ED7C0, "\x48\x8B\xC4\x55\x48\x83\xEC\x70\x48\x89\x58\x08\x48\x8B\xE9", "xxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSetMeshVisiblity, 0x140811910, "\x40\x55\x41\x56\x48\x81\xEC\xC8", "xxxxxxxx");

class StatePluginCyloop
{
public:
	inline static bool IsForceCyloopAura = false;

	static void Install();
};

