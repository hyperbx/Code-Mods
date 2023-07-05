EXPORT void Init()
{
	if (!m_IsSigValid)
	{
		MessageBoxA
		(
			nullptr,
			"A signature scan failed validation...\n\nThis mod may be incompatible with your current game version, or is conflicting with another DLL mod.",
			"Enhanced Dash",
			MB_ICONERROR
		);

		exit(-1);
	}

	Configuration::Read();

	Reflection::Install();
	Player::Install();
}