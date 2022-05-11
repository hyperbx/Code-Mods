// https://github.com/brianuuu/DllMods/blob/master/Source/Sonic06HUD/Stage.cpp#L166
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, float* pUpdateInfo)
{
	// Force disable extended boost.
	*(uint32_t*)((uint32_t)*CONTEXT->ms_pInstance + 0x680) = 1;

	// Always clamp boost to 100.
	CONTEXT->m_ChaosEnergy = min(CONTEXT->m_ChaosEnergy, 100.0f);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

// https://github.com/brianuuu/DllMods/blob/master/Source/NavigationLightdashSound/NavigationSound.cpp#L14
HOOK(void, __fastcall, MsgStartCommonButtonSign, 0x5289A0, void* thisDeclaration, void* edx, uint32_t a2)
{
	// Disable Y button prompt.
	if (*(uint32_t*)(a2 + 16) == 3)
		return;

	originalMsgStartCommonButtonSign(thisDeclaration, edx, a2);
}

void HudSonicStage::Install()
{
	INSTALL_HOOK(CHudSonicStageUpdate);
	INSTALL_HOOK(MsgStartCommonButtonSign);

	// Patch ring counter to use four digits.
	WRITE_MEMORY(0x168D33C, const char, "%04d");
	WRITE_MEMORY(0x168E8E0, const char, "%04d");

	// Disable boost button guide animation.
	if (!Configuration::GaugeShake)
		WRITE_NOP(0x124F4A1, 2);
}