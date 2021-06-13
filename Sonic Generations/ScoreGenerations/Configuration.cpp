bool Configuration::overrideFlag = false;

INIReader Configuration::config;
string Configuration::configPath = INI_FILE;
bool Configuration::scoreTimeout = false;
int Configuration::scoreLimit = 999999;
int Configuration::perfectBonus = 1;
string Configuration::scoreFormat = "%06d";
bool Configuration::customXNCP = false;
bool Configuration::debugLua = false;
bool Configuration::overrideForbiddenCasino = false;
vector<string> Configuration::forbiddenStages;

string Configuration::GetConfigDirectory()
{
	return configPath.substr(0, configPath.find_last_of("\\"));
}

void Configuration::Read(string path = "")
{
	// Sets the config path and reads it.
	Configuration::config = configPath = path.empty() ? INI_FILE : path;

	// Get the score for the objects.
	Tables::scoreTable = Tables::ScoreTable::GetScore();

	// Get the bonuses.
	Tables::bonusTable = Tables::BonusTable::GetBonuses();

	// Get the multipliers.
	Tables::multiplierTable = Tables::MultiplierTable::GetMultipliers();

	// Get the timers.
	Tables::timerTable = Tables::TimerTable::GetTimers();

	// Timer
	Configuration::scoreTimeout = config.GetBoolean("Timer", "scoreTimeout", scoreTimeout);

	// Behaviour
	Configuration::scoreLimit = config.GetInteger("Behaviour", "scoreLimit", scoreLimit);
	Configuration::perfectBonus = config.GetInteger("Behaviour", "perfectBonus", perfectBonus);

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
	Configuration::forbiddenStages = StringHelper::GetCommaSeparatedStrings(StringHelper::RemoveSpaces(config.Get("Developer", "forbiddenStages", "")));

	// Get the ranks.
	Tables::RankTable::GetRanks();

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