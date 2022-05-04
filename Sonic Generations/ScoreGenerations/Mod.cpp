std::vector<ModIntegrity::Hash> Hashes =
{
	{ "disk\\bb\\SonicActionCommonScoreHud.ar.00", "3fcf87b4d6ef72142e070645e022f6f3" },
	{ "disk\\bb\\SonicActionCommonScoreHud.arl", "cab307ae5ea4de45a0feb60382928be9" }
};

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Verify the integrity of the mod data and author.
	if (!ModIntegrity::VerifyData(Hashes) || !ModIntegrity::VerifyAuthor("Hyper"))
	{
		ModIntegrity::Throw("Score Generations", "", "https://gamebanana.com/mods/292798");

		return;
	}

	// Load configuration from current file.
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

	Memory::Preserve();

	// Patch archive tree for Score Generations HUD.
	if (!Configuration::customXNCP)
		ArchiveTreePatcher::Install();

	// Install listeners.
	StatisticsListener::Install();

	// Install hooks.
	HudSonicStage::Install();
	ScoreHooks::Install();
	StateHooks::Install();

	// Apply simple patches.
	Patches::Install();
}
