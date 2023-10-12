#pragma once

// Patches
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigForceGrindJumpPosture, 0x14B1FBA88, "\x73\x09\x0F\x28\x1D\xCC\xCC\xCC\xCC\xEB\x35\x0F\x2F\xDA", "xxxxx????xxxxx");

class StateGrindDoubleJump
{
public:
	static void Install();
};

