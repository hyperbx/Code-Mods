extern "C" _declspec(dllexport) void PostInit()
{
	Discord::Initialise();

	BossListener::Install();
	GameModeListener::Install();
}