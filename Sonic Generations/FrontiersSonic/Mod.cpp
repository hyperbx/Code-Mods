std::unordered_map<std::string, std::string> incompatibleMods =
{
	{ "Double Jump", "DoubleJump.dll" },
	{ "SA2 Bounce", "SA2Bounce.dll" }
};

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Configuration::Read();

	Camera::Install();
	HudSonicStage::Install();
	Patches::Install();
	Player::Install();
}

extern "C" __declspec(dllexport) void PostInit()
{
	bool isIncompatible = false;

	for (auto mod : incompatibleMods)
	{
		if (GetModuleHandle(TEXT(mod.second.c_str())) != nullptr)
		{
			MessageBox
			(
				nullptr,
				TEXT(std::string(mod.first + " is incompatible with Frontiers Sonic.").c_str()),
				TEXT("Frontiers Sonic"),
				MB_ICONERROR
			);

			isIncompatible = true;
		}
	}

	if (isIncompatible)
		exit(-1);
}