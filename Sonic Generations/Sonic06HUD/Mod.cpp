/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Apply simple patches.
	Patches::Install();

	// Install mid-ASM hooks for HUD stuff.
	HudSonicStage::Install();
}