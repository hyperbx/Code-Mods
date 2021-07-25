/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Lock player control during loading transitions.
	WRITE_JUMP(0xD97EA4, (void*)0xD97EAF);

	// Use single digit for life counter.
	WRITE_MEMORY(0x1098CCA, char*, "%d");

	// Install mid-ASM hooks for HUD stuff.
	HudSonicStage::Install();
}