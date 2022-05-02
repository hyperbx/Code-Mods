/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Configuration::Read();

	Patches::Install();
	HudResult::Install();
	HudSonicStage::Install();
}