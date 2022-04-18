/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	HudResult::Install();
	HudSonicStage::Install();
}