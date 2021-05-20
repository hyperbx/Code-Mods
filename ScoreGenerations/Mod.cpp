/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Loader::ConfigureScoreGenerations();

	// Patch archive tree for Score Generations HUD.
	if (!Configuration::customXNCP)
		ArchiveTreePatcher::Install();

	StatisticsListener::Install();
	HudSonicStage::Install();
	ObjectHooks::Install();
	StateHooks::Install();
	Patches::Install();
}