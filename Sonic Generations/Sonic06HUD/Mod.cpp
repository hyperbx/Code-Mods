/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Use single digit for life counter.
	WRITE_MEMORY(0x1098CCA, char*, "%d");

	// Install mid-ASM hooks for HUD stuff.
	SonicHud::Install();
}