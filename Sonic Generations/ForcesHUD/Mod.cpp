/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Read the mod configuration file.
	Configuration::Read();

	// Patch the archive tree to load the homing sound.
	ArchiveTreePatcher::Install();

	// Apply simple patches.
	Patches::Install();

	// Install mid-ASM hooks for HUD stuff.
	SonicHud::Install();

	// Patches the game to use different button prompts.
	ControllerPatcher::Install();
}