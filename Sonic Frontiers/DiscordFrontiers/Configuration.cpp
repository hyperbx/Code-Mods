void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// General
	Language = INI_READ_STRING("General", Language);
}

void Configuration::ReadMods(ModInfo* in_pModInfo)
{
	for (auto pMod : *in_pModInfo->ModList)
	{
		auto path = StringHelper::GetSubstringBeforeLastChar(pMod->Path, '\\').append("\\DiscordFrontiers.ini");

		printf("%s\n", path.c_str());

		if (!IOHelper::FileExists(path))
			continue;

		printf("[Discord Frontiers] Loading configuration from \"%s\"\n", path.c_str());

		auto ini = BasicIniReader::Read(path);

		if (ini.count("Stages"))
		{
			// Load custom stage image URLs.
			for (auto key : ini["Stages"])
			{
				if (StageListener::CustomStageMap.count(key.first))
				{
					StageListener::CustomStageMap[key.first] = key.second;
					continue;
				}

				StageListener::CustomStageMap.insert({ key.first, key.second });
			}
		}

		if (ini.count("Characters"))
		{
			// Load custom character image URLs.
			for (auto key : ini["Characters"])
			{
				if (PlayerListener::CharacterInfoMap.count(key.first))
				{
					PlayerListener::CharacterInfoMap[key.first] = key.second;
					continue;
				}

				PlayerListener::CharacterInfoMap.insert({ key.first, key.second });
			}
		}
	}
}