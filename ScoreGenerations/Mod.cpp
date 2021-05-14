/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Loader::ConfigureScoreGenerations();

	Patches::Install();

	// Patch archive tree for Score Generations HUD.
	if (!Configuration::customXNCP)
		ArchiveTreePatcher::Install();

	StatisticsListener::Install();
	ObjectHooks::Install();
	StateHooks::Install();
}