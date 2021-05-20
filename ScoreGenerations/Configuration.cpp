// Declare class variables.
INIReader Configuration::config;
string Configuration::configPath = INI_FILE;
unsigned int Configuration::scoreLimit = 999999;
string Configuration::scoreFormat = "%06d";
bool Configuration::customXNCP = false;
vector<string> Configuration::forbiddenStages;

/// <summary>
/// Gets the directory containing the configuration.
/// </summary>
string Configuration::GetConfigDirectory()
{
	return configPath.substr(0, configPath.find_last_of("\\"));
}

/// <summary>
/// Reads the INI configuration file for the mod.
/// </summary>
void Configuration::Read(string path = "")
{
	// Sets the config path and reads it.
	Configuration::config = configPath = path.empty() ? INI_FILE : path;

	// Get the score for the objects.
	ScoreListener::scoreTable = ScoreListener::ScoreTable::GetScore();

	// Get the bonuses.
	ScoreListener::bonusTable = ScoreListener::BonusTable::GetBonuses();

	// Behaviour
	Configuration::scoreLimit = config.GetInteger("Behaviour", "scoreLimit", 999999);

	// Appearance
	Configuration::scoreFormat = config.Get("Appearance", "scoreFormat", "%06d");

	// Developer
	Configuration::customXNCP = config.GetBoolean("Developer", "customXNCP", false);
	Configuration::forbiddenStages = StringHelper::GetCommaSeparatedStrings(StringHelper::RemoveSpaces(config.Get("Developer", "forbiddenStages", "")));
}