/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Apply simple patches.
	Patches::Install();
}