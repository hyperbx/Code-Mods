/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Configuration::Read();

	HudSonicStage::Install();
	Player::Install();
}

extern "C" __declspec(dllexport) void PostInit()
{
	if (GetModuleHandle(TEXT("DoubleJump.dll")) != nullptr)
	{
		MessageBox
		(
			nullptr,
			TEXT
			(
				"Double Jump is incompatible with Frontiers Sonic.\n\n" \
				"" \
				"Please disable it for the best experience."
			),
			TEXT("Frontiers Sonic"),
			MB_ICONWARNING
		);
	}
}