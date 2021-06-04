INIReader Configuration::config;
string Configuration::configPath = INI_FILE;
unsigned int Configuration::scoreLimit = 999999;
string Configuration::scoreFormat = "%06d";
unsigned int Configuration::superSonicTimer = 2;
bool Configuration::customXNCP = false;
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
	Configuration::scoreLimit      = config.GetInteger("Behaviour", "scoreLimit", 999999);
	Configuration::superSonicTimer = config.GetInteger("Behaviour", "superSonicTimer", 2);

	// Appearance
	Configuration::scoreFormat = config.Get("Appearance", "scoreFormat", "%06d");

	// Developer
	Configuration::customXNCP      = config.GetBoolean("Developer", "customXNCP", false);
	Configuration::forbiddenStages = StringHelper::GetCommaSeparatedStrings(StringHelper::RemoveSpaces(config.Get("Developer", "forbiddenStages", "")));

	// Ranks
	ResultListener::RankTable::GetRanks();
}