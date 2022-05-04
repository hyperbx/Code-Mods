bool Configuration::overrideFlag = false;

INIReader Configuration::config;
std::string Configuration::configPath = INI_FILE;
bool Configuration::rewardSpeedBonus = true;
bool Configuration::scoreTimeout = false;
bool Configuration::restoreLastCheckpointScore = false;
int Configuration::scoreLimit = 999999;
Configuration::PerfectBonusType Configuration::perfectBonus = OnlyForA;
std::string Configuration::scoreFormat = "%06d";
bool Configuration::customXNCP = false;
bool Configuration::debugLua = false;
bool Configuration::overrideForbiddenCasino = false;
std::vector<std::string> Configuration::forbiddenStages;

std::string Configuration::GetConfigDirectory()
{
	return configPath.substr(0, configPath.find_last_of("\\"));
}

void Configuration::Read(std::string path = "")
{
	// Sets the config path and reads it.
	Configuration::config = configPath = path.empty() ? INI_FILE : path;

	// Sets the Lua path to the current working directory.
	if (!LuaCallback::SetLuaPath(Configuration::GetConfigDirectory() + "\\" + LUA_FILE))
	{
		if (Configuration::debugLua)
			printf("[Score Generations] [Lua Debug] The overridden mod doesn't have a Lua script - reverting to previous script...\n");
	}

	// Get the score for the objects.
	TableListener::scoreTable = TableListener::GetScore();

	// Get the bonuses.
	TableListener::bonusTable = TableListener::GetBonuses();

	// Get the multipliers.
	TableListener::multiplierTable = TableListener::GetMultipliers();

	// Get the timers.
	TableListener::timerTable = TableListener::GetTimers();

	// GameplayBonus
	Configuration::rewardSpeedBonus = config.GetBoolean("GameplayBonus", "rewardSpeedBonus", rewardSpeedBonus);

	// Timer
	Configuration::scoreTimeout = config.GetBoolean("Timer", "scoreTimeout", scoreTimeout);

	// Behaviour
	Configuration::restoreLastCheckpointScore = config.GetBoolean("Behaviour", "restoreLastCheckpointScore", restoreLastCheckpointScore);
	Configuration::scoreLimit = config.GetInteger("Behaviour", "scoreLimit", scoreLimit);
	Configuration::perfectBonus = (PerfectBonusType)config.GetInteger("Behaviour", "perfectBonus", perfectBonus);

	// Appearance
	Configuration::scoreFormat = config.Get("Appearance", "scoreFormat", scoreFormat);

	// Override checks for Developer
	if (overrideFlag)
	{
		bool overrideCustomXNCP = config.GetBoolean("Developer", "customXNCP", customXNCP);

		// Compare current flag with updated INI flag - if they mismatch, then give the warning.
		if (Configuration::customXNCP && !overrideCustomXNCP)
		{
			MessageBox
			(
				nullptr,
				TEXT("Score Generations has detected a HUD mod loaded with incorrect priority - please make it higher priority!"),
				TEXT("Score Generations"),
				MB_ICONWARNING
			);
		}
	}

	// Developer
	Configuration::customXNCP = config.GetBoolean("Developer", "customXNCP", customXNCP);
	Configuration::debugLua = config.GetBoolean("Developer", "debugLua", debugLua);
	Configuration::overrideForbiddenCasino = config.GetBoolean("Developer", "overrideForbiddenCasino", overrideForbiddenCasino);

	// Get forbidden stages.
	std::string forbiddenStagesCSV = config.Get("Developer", "forbiddenStages", "");
	{
		// Set configuration if the returned CSV list is populated.
		if (!forbiddenStagesCSV.empty())
			Configuration::forbiddenStages = StringHelper::GetCommaSeparatedStrings(StringHelper::RemoveSpaces(forbiddenStagesCSV));
	}

	// Get the ranks.
	TableListener::GetRanks();

	// Set the override flag now that we have read a config.
	overrideFlag = true;

#if _DEBUG
	// Force enable non-default debugging features.
	Configuration::Debug();
#endif
}

void Configuration::Debug()
{
	printf("[Score Generations] Debug build detected! Overriding non-default debugging features...\n");

	Configuration::debugLua = true;
}