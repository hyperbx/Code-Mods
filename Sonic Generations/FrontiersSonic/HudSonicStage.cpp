HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* _this, void* edx, void* pUpdateInfo)
{
	if (Configuration::alwaysActiveReticle && !BlueBlurCommon::IsClassic())
	{
		FUNCTION_PTR(int, __stdcall, HomingTargetUpdate, 0xE5FF10, Sonic::Player::CPlayerSpeedContext* _this);
		{
			HomingTargetUpdate(CONTEXT);
		}
	}

	originalCHudSonicStageUpdate(_this, edx, pUpdateInfo);
}

void HudSonicStage::Install()
{
	INSTALL_HOOK(CHudSonicStageUpdate);
}