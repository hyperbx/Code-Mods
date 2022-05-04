std::string Loader::GetExecutablePath()
{
	char buffer[MAX_PATH];

	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	return buffer;
}

std::string Loader::GetWorkingDirectory()
{
	std::string executablePath = Loader::GetExecutablePath();

	return executablePath.substr(0, executablePath.find_last_of("\\"));
}

std::string Loader::GetCpkRedirConfig()
{
	return Loader::GetWorkingDirectory() + "\\cpkredir.ini";
}

std::string Loader::GetModsDatabase()
{
	std::string cpkRedirConfig = Loader::GetCpkRedirConfig();

	std::string modsDatabase;

	if (IOHelper::FileExists(cpkRedirConfig))
	{
		INIReader reader(cpkRedirConfig);

		modsDatabase = reader.Get("CPKREDIR", "ModsDbIni", MODS_DEFAULT);
	}

	// Early builds of Hedge Mod Manager use relative paths.
	if (StringHelper::Compare(StringHelper::ToLower(modsDatabase), StringHelper::ToLower(MODS_DEFAULT)))
		return Loader::GetWorkingDirectory() + "\\" + MODS_DEFAULT;

	return modsDatabase;
}

std::string Loader::GetModsDirectory()
{
	std::string modsDirectory = Loader::GetModsDatabase();

	return modsDirectory.substr(0, modsDirectory.find_last_of("\\"));
}

void Loader::ConfigureScoreGenerations()
{
	std::string modsDatabase = Loader::GetModsDatabase();

	if (IOHelper::FileExists(modsDatabase))
	{
		INIReader reader(modsDatabase);

		bool reverseLoadOrder;
		{
			// Used to flip the for loop direction.
			reverseLoadOrder = reader.GetBoolean("Main", "ReverseLoadOrder", 0);
		}

		int count;
		{
			// Used for iterating the for loop.
			count = reader.GetInteger("Main", "ActiveModCount", 0);
		}

		// (reverseLoadOrder == true)  = for (int i = 0; i < count; i++)
		// (reverseLoadOrder == false) = for (int i = count - 1; i + 1 > 0; i--)
		for (int i = reverseLoadOrder ? 0 : count - 1; reverseLoadOrder ? i < count : i + 1 > 0; reverseLoadOrder ? i++ : i--)
		{
			Loader::ModInformation modInfo;

			std::string guid;
			{
				guid = reader.Get("Main", "ActiveMod" + std::to_string(i), "");
			}

			std::string config;
			{
				config = reader.Get("Mods", guid, "");

#if _DEBUG
				// Get mod information so we can put the mod name into the console.
				modInfo = Loader::ModInformation::ReadConfig(config);
#endif
			}

			std::string scoreGenerationsConfig = config.substr(0, config.find_last_of("\\")) + "\\" + INI_FILE;

			if (IOHelper::FileExists(scoreGenerationsConfig))
			{
				Configuration::Read(scoreGenerationsConfig);

#if _DEBUG
				printf("[Score Generations] Configuration overridden by %s\n", modInfo.title.c_str());
#endif
			}
		}
	}
}