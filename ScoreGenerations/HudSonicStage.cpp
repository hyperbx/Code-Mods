FUNCTION_PTR(void, __thiscall, ProcessMsgSetPinballHud, 0x1095D40, void* thisDeclaration, const HudSonicStage::MsgSetPinballHud& msgSetPinballHud);

HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, void* pUpdateInfo)
{
	HudSonicStage::MsgSetPinballHud msgSetPinballHud;
	msgSetPinballHud.flags = 1;
	msgSetPinballHud.score = ScoreListener::score;

	// Makes sure the current stage isn't forbidden before sending the message.
	if (!HudSonicStage::IsStageForbidden())
		ProcessMsgSetPinballHud(thisDeclaration, msgSetPinballHud);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

bool HudSonicStage::IsStageForbidden()
{
	// Check if the current stage ID matches any in the list.
	for (vector<string>::const_iterator i = Configuration::forbiddenStages.begin(); i != Configuration::forbiddenStages.end(); ++i)
	{
		// Stage ID matches - HUD must be special.
		if (StringHelper::Compare(StateHooks::stageID, i->c_str()))
			return true;
	}

	return false;
}

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void HudSonicStage::Install()
{
	// Install hook to update the score counter.
	INSTALL_HOOK(CHudSonicStageUpdate);
}