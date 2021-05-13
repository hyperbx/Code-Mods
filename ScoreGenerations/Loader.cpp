string Loader::GetExecutablePath()
{
	char buffer[MAX_PATH];

	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	return buffer;
}

string Loader::GetWorkingDirectory()
{
	string executablePath = Loader::GetExecutablePath();

	return executablePath.substr(0, executablePath.find_last_of("\\"));
}

string Loader::GetCpkRedirConfig()
{
	return Loader::GetWorkingDirectory() + "\\cpkredir.ini";
}

string Loader::GetModsDatabase()
{
	string cpkRedirConfig = Loader::GetCpkRedirConfig();

	string modsDatabase;

	if (IOHelper::FileExists(cpkRedirConfig))
	{
		inipp::Ini<char> ini;
		std::ifstream file(cpkRedirConfig);
		ini.parse(file);

		inipp::extract(StringHelper::Unquote(ini.sections["CPKREDIR"]["ModsDbIni"]), modsDatabase);

		file.close();
	}

	// Early builds of Hedge Mod Manager use relative paths.
	if (!strcmp(StringHelper::ToLower(modsDatabase).c_str(), StringHelper::ToLower(MODS_DEFAULT).c_str()))
		return Loader::GetWorkingDirectory() + "\\" + MODS_DEFAULT;

	return modsDatabase;
}

string Loader::GetModsDirectory()
{
	string modsDirectory = Loader::GetModsDatabase();

	return modsDirectory.substr(0, modsDirectory.find_last_of("\\"));
}

void Loader::ConfigureScoreGenerations()
{
	string modsDatabase = Loader::GetModsDatabase();

	if (IOHelper::FileExists(modsDatabase))
	{
		inipp::Ini<char> ini;
		std::ifstream file(modsDatabase);
		ini.parse(file);

		bool reverseLoadOrder;
		{
			int loadOrder = 0;

			// Used to flip the for loop direction.
			inipp::extract(ini.sections["Main"]["ReverseLoadOrder"], loadOrder);

			reverseLoadOrder = loadOrder == 1 ? true : false;
		}

		int count;
		{
			// Used for iterating the for loop.
			inipp::extract(ini.sections["Main"]["ActiveModCount"], count);
		}

		// (reverseLoadOrder == true)  = for (int i = 0; i < count; i++)
		// (reverseLoadOrder == false) = for (int i = count - 1; i + 1 > 0; i--)
		for (int i = reverseLoadOrder ? 0 : count - 1; reverseLoadOrder ? i < count : i + 1 > 0; reverseLoadOrder ? i++ : i--)
		{
			Loader::ModInformation modInfo;

			string guid;
			{
				inipp::extract(StringHelper::Unquote(ini.sections["Main"]["ActiveMod" + to_string(i)]), guid);
			}

			string config;
			{
				inipp::extract(StringHelper::Unquote(ini.sections["Mods"][guid]), config);

#if _DEBUG
				// Get mod information so we can put the mod name into the console.
				modInfo = Loader::ModInformation::ReadConfig(config);
#endif
			}

			string scoreGenerationsConfig = config.substr(0, config.find_last_of("\\")) + "\\" + INI_FILE;

			if (IOHelper::FileExists(scoreGenerationsConfig))
			{
				Mod::ReadConfig(scoreGenerationsConfig);

#if _DEBUG
				printf("[Score Generations] Configuration overridden by %s\n", modInfo.title.c_str());
#endif
			}
		}

		file.close();
	}
}