#pragma once

CL_SCAN_SIGNATURE(m_SigStateFallSlopeStart, 0x1408FCC20, "\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x57\x48\x83\xEC\x70\x0F\xB6\xDA", "xxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateFallSlopeUpdate, 0x140898300, "\x48\x89\x5C\x24\x18\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x40\x48\x8B\xF1\x0F\x29\x74\x24\x30\x8B\x89\xA8\x00\x00\x00\x0F\x28\xF2\x48\x8B\xFA\x85\xC9\x0F\x84\x8D", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

class StateFallSlope
{
public:
	static void Install();
};

