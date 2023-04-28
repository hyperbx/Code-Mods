EXPORT void Init()
{
	if (!m_IsSigValid)
	{
		MessageBoxA
		(
			nullptr,
			"This mod is incompatible with your current game version.\nThe last known working version is Sonic Frontiers v1.20.",
			"Enhanced Drop Dash",
			MB_ICONERROR
		);

		exit(-1);
	}

	Configuration::Read();

	Reflection::Install();
	Player::Install();
}