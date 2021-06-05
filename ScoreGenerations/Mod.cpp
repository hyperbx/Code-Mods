/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
#if !_DEBUG
	// Redirect console output for release.
	freopen("CONOUT$", "w", stdout);
#endif

	Loader::ConfigureScoreGenerations();

	// Patch archive tree for Score Generations HUD.
	if (!Configuration::customXNCP)
		ArchiveTreePatcher::Install();

	StatisticsListener::Install();
	HudSonicStage::Install();
	ScoreHooks::Install();
	StateHooks::Install();
	Patches::Install();
}