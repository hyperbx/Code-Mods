// https://github.com/PTKickass/ModUpdates/blob/master/DLLModsSource/SonicGenerations/SonicUnleashedHUD/UnleashedHUD/DataHelper.cpp#L87
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, float* pUpdateInfo)
{
	// Always clamp boost to 100.
	*BlueBlurCommon::GetBoost() = min(*BlueBlurCommon::GetBoost(), 100.0f);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

void HudSonicStage::Install()
{
	// Install hook to update the boost gauge.
	INSTALL_HOOK(CHudSonicStageUpdate);
}