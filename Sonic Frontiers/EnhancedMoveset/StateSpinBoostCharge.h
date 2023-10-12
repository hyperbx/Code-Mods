#pragma once

// Function Pointers
CL_SCAN_SIGNATURE(m_SigGetPlugin, 0x140124200, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x20\x48\x8B\x59\x18\x8B\xEA", "xxxxxxxxxxxxxxxxxxxxxxxxxx");

// Hooks
CL_SCAN_SIGNATURE(m_SigStateSpinBoostChargeStart, 0x1408A6590, "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x68\x18\x48\x89\x70\x20\x57\x48\x83\xEC\x70\xF3\x0F\x10\x05", "xxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateSpinBoostChargeUpdate, 0x1408A6CB0, "\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x70\x48\x8B\xFA\x48\x8B\xF1", "xxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateSpinBoostChargeEnd, 0x1408A6A60, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\x42\x38\x48\x8B\xF1\x41\x8B\xF8", "xxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStartSpinChargeCamera, 0x1408D5C60, "\x48\x89\x74\x24\x18\x48\x89\x7C\x24\x20\x41\x56\x48\x83\xEC\x20\x48\x8B\x41\x28\x45\x33\xF6\x48\x8B\xF2", "xxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateGrindJumpUpdate, 0x14089E330, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x40\x48\x8B\xDA\x48\x8B\xF9\xE8\xCC\xCC\xCC\xCC\xB2\x01", "xxxxxxxxxxxxxxxxx????xx");
CL_SCAN_SIGNATURE(m_SigStateStompingDownUpdate, 0x1408AD9F0, "\x48\x89\x5C\x24\x18\x48\x89\x7C\x24\x20\x55\x48\x8D\x6C\x24\xA9\x48\x81\xEC\xC0\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxxxx");

// Required Patches
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeCamera, 0x1408A67A0, "\x75\x3F\xBA\x05\x00\x00\x00", "xxxxxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeDeceleration, 0x14084DFB5, "\xE8\xCC\xCC\xCC\xCC\x0F\xB6\x5E\x28", "x????xxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeOriginalChargeInput, 0x1408A6CC8, "\xE8\xCC\xCC\xCC\xCC\x84\xC0\x0F\x84\xF9\x00\x00\x00\x0F\x57\xC9", "x????xxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeOriginalReleaseInput, 0x1408A6DEC, "\x74\x18\xE8\xCC\xCC\xCC\xCC\x84\xC0\x74\x5D", "xxx????xxxx");
CL_SCAN_SIGNATURE(m_SigDisableSpinChargeRelease, 0x1408A6E21, "\x74\x1C\x45\x33\xC0\x41\x8D\x50\x74", "xxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigRunToSpinBoostCaller, 0x1408A3A18, "\xE8\xCC\xCC\xCC\xCC\x84\xC0\x75\x80", "x????xxxx");

// Patches
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableSpinChargeCameraCode, 0x1408A67DC, "\xE8\xCC\xCC\xCC\xCC\x48\x8B\xCF\xE8\xCC\xCC\xCC\xCC\x48\x8B\xC8\x45\x33\xC0\xB2\x24", "x????xxxx????xxxxxxxx");

enum EStateSpinBoostChargeFlags
{
	EStateSpinBoostChargeFlags_IsReleased,
	EStateSpinBoostChargeFlags_IsStartGrounded
};

class StateSpinBoostCharge
{
public:
	inline static std::bitset<2> Flags;

	inline static float ChargeMultiplier = 0.0f;
	inline static float ChargeTime = 0.0f;
	inline static float ReleaseVelocity = 0.0f;

	inline static csl::math::Vector3 ReleaseForward;

	static void StartSpinChargeCamera(int64_t in_pSonicContext)
	{
		auto pStatePluginManager = *(int64_t*)(*(int64_t*)(in_pSonicContext + 0x38) + 0x108);

		if (!pStatePluginManager)
			return;

		FUNCTION_PTR(int64_t, __fastcall, fpGetPlugin, m_SigGetPlugin(), int64_t in_pStatePluginManager, int in_pluginNameHash);

		auto pStatePluginCamera = fpGetPlugin(pStatePluginManager, 0x2EBFB349);

		if (!pStatePluginCamera)
			return;

		FUNCTION_PTR(int64_t, __fastcall, fpStartSpinChargeCamera, m_SigStartSpinChargeCamera(), int64_t in_pStatePluginCamera, const char* in_pCameraName);

		fpStartSpinChargeCamera(pStatePluginCamera, "SpinBoostCharge");
	}

	static void ConfigLazyUpdate();
	static void Install();
};

