void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// General
	Configuration::m_IsRealTime    = reader.GetBoolean("General", "isRealTime", m_IsRealTime);
	Configuration::m_IsRealWeather = reader.GetBoolean("General", "isRealWeather", m_IsRealWeather);

	// Location
	Configuration::m_IsFirstTimeSetup = reader.GetBoolean("Location", "isFirstTimeSetup", m_IsFirstTimeSetup);
	Configuration::m_Latitude         = reader.GetReal("Location", "latitude", m_Latitude);
	Configuration::m_Longitude        = reader.GetReal("Location", "longitude", m_Longitude);

	if (Configuration::m_IsFirstTimeSetup)
	{
		if (!IOHelper::FileExists("RealTimeAndWeather.Utility.exe"))
		{
			MessageBoxA
			(
				nullptr,
				"The utility tool is missing! Please redownload this mod from an official source.",
				"Real Time and Weather",
				MB_ICONERROR
			);

			exit(-1);

			return;
		}

		system("RealTimeAndWeather.Utility.exe -DLL");

		/* Re-read the configuration to get
		   the latitude and longitude. */
		Configuration::Read();
	}
}