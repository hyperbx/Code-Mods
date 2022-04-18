HOOK(int, __cdecl, MeteorSmashConstructor, 0xC880B0, int a1)
{
	BlueBlurCommon::PlayMusic("vs_Silver2", 0.25);

	return originalMeteorSmashConstructor(a1);
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	INSTALL_HOOK(MeteorSmashConstructor);
}