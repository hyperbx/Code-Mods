#pragma once

// Hooks
CL_SCAN_SIGNATURE(m_SigStateSpinMoveUpdate, 0x1408A7230, "\x40\x57\x48\x81\xEC\x30\x01\x00\x00\x48\x8B\xCA\x48\x8B\xFA\xE8\xCC\xCC\xCC\xCC\x48\x8B\xCF", "xxxxxxxxxxxxxxxx????xxx");
CL_SCAN_SIGNATURE(m_SigStateSpinMoveEnd, 0x1408A7940, "\x48\x89\x5C\x24\x10\x56\x48\x83\xEC\x50\x48\x8B\x4A\x48", "xxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSendMoveImpulse, 0x140862190, "\x40\x55\x56\x57\x48\x8D\xAC\x24\xE0\xFE\xFF\xFF", "xxxxxxxxxxxx");

// Required Patches
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeFromSpinMove, 0x1408A72A3, "\xE8\xCC\xCC\xCC\xCC\x84\xC0\x0F\x85\x36\x01\x00\x00\xB2\x01", "x????xxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinMoveExitInput, 0x1408A738F, "\x74\x10\x48\x8B\xC8\xE8\xCC\xCC\xCC\xCC\x0F\x57\xC9\x0F\x2F\xC1\x76\x36", "xxxxxx????xxxxxxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinMoveSpinBoostExit, 0x1408A7268, "\x74\x26\x48\x8B\xC8\xE8\xCC\xCC\xCC\xCC\x84\xC0\x74\x1A", "xxxxxx????xxxx");
CL_SCAN_SIGNATURE(m_SigPostureSpinBoostSlopeAccelFix, 0x14084D15A, "\x0F\x84\x2A\x01\x00\x00\x80\xBD\x78\x01\x00\x00\x00", "xxxxxxxxxxxxx");

class StateSpinMove
{
public:
	static bool IsUngroundedExit()
	{
		if (BlackboardHelper::IsCyberSpace() || BlackboardHelper::IsSideView())
			return false;

		return Configuration::IsSpinMoveCancelWhenUngrounded;
	}

	static void Install();
};