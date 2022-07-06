HOOK(void, __fastcall, CPlayerSpeedStatePluginTimeBreakUpdate, 0x111B030, Hedgehog::Universe::TStateMachine<Sonic::Player::CPlayerSpeedContext>::TState* thisDeclaration)
{
	BlueBlurCommon::PlayMusic("Time_Break", 0.0);

	if (thisDeclaration->m_Time > 8.0f)
		originalCPlayerSpeedStatePluginTimeBreakUpdate(thisDeclaration);
}

HOOK(void, __fastcall, CPlayerSpeedStatePluginTimeBreakEnd, 0x111AE00, Hedgehog::Universe::TStateMachine<Sonic::Player::CPlayerSpeedContext>::TState* thisDeclaration)
{
	BlueBlurCommon::StopMusic("Time_Break", 0.0);

	originalCPlayerSpeedStatePluginTimeBreakEnd(thisDeclaration);
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	INSTALL_HOOK(CPlayerSpeedStatePluginTimeBreakUpdate);
	INSTALL_HOOK(CPlayerSpeedStatePluginTimeBreakEnd);
}