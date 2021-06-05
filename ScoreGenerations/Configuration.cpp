bool Configuration::overrideFlag = false;

INIReader Configuration::config;
string Configuration::configPath = INI_FILE;
unsigned int Configuration::scoreLimit = 999999;
string Configuration::scoreFormat = "%06d";
unsigned int Configuration::superSonicTimer = 2;
bool Configuration::customXNCP = false;
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
	ScoreListener::scoreTable = ScoreListener::ScoreTable::GetScore();

	// Get the bonuses.
	ResultListener::bonusTable = ResultListener::BonusTable::GetBonuses();

	// Behaviour
	Configuration::scoreLimit = config.GetInteger("Behaviour", "scoreLimit", 999999);
	Configuration::superSonicTimer = config.GetInteger("Behaviour", "superSonicTimer", 2);

	// Appearance
	Configuration::scoreFormat = config.Get("Appearance", "scoreFormat", "%06d");

	// Override checks for Developer
	{
		if (overrideFlag)
		{
			bool overrideCustomXNCP = config.GetBoolean("Developer", "customXNCP", false);

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
	}

	// Developer
	Configuration::customXNCP = config.GetBoolean("Developer", "customXNCP", false);
	Configuration::overrideForbiddenCasino = config.GetBoolean("Developer", "overrideForbiddenCasino", false);
	Configuration::forbiddenStages = StringHelper::GetCommaSeparatedStrings(StringHelper::RemoveSpaces(config.Get("Developer", "forbiddenStages", "")));

	// Get the ranks.
	ResultListener::RankTable::GetRanks();

	// Set the override flag now that we have read a config.
	overrideFlag = true;
}