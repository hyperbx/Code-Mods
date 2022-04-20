// https://github.com/brianuuu/DllMods/blob/master/Source/Sonic06HUD/Stage.cpp#L166
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, float* pUpdateInfo)
{
	// Always clamp boost to 100.
	*BlueBlurCommon::GetBoost() = min(*BlueBlurCommon::GetBoost(), 100.0f);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

// https://github.com/brianuuu/DllMods/blob/master/Source/Sonic06HUD/Stage.cpp#L174
HOOK(int, __fastcall, MsgRestartStage, 0xE76810, uint32_t* thisDeclaration, void* edx, void* message)
{
	// Force disable extended boost.
	*(uint32_t*)((uint32_t)*BlueBlurCommon::PlayerContext + 0x680) = 1;

	return originalMsgRestartStage(thisDeclaration, edx, message);
}

void HudSonicStage::Install()
{
	// Install hook to cap the boost gauge to 100%.
	INSTALL_HOOK(CHudSonicStageUpdate);

	// Install hook to disable the extended boost gauge.
	INSTALL_HOOK(MsgRestartStage);
}