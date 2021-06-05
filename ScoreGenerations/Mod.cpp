/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Loader::ConfigureScoreGenerations();

#if !_DEBUG
	if (Configuration::debugLua)
	{
		if (IOHelper::FileExists("CONOUT$"))
		{
			// Redirect console output for release.
			freopen("CONOUT$", "w", stdout);
		}
		else
		{
			MessageBox
			(
				nullptr,
				TEXT("Please enable the debug console via Hedge Mod Manager to use the Lua debugger!"),
				TEXT("Score Generations"),
				MB_ICONERROR
			);
		}
	}
#endif

	// Patch archive tree for Score Generations HUD.
	if (!Configuration::customXNCP)
		ArchiveTreePatcher::Install();

	StatisticsListener::Install();
	HudSonicStage::Install();
	ScoreHooks::Install();
	StateHooks::Install();
	Patches::Install();
}