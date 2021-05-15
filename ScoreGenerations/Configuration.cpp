using namespace std;

// Declare class variables.
INIReader Configuration::config;
string Configuration::scoreFormat = "%06d";
bool Configuration::customXNCP = false;

/// <summary>
/// Reads the mod configuration file.
/// </summary>
void Configuration::Read(string path = "")
{
	Configuration::config = path.empty() ? INI_FILE : path;

	// Appearance
	Configuration::scoreFormat = config.Get("Appearance", "scoreFormat", "%06d");

	// Developer
	Configuration::customXNCP = config.GetBoolean("Developer", "customXNCP", false);

	// Get the score for the objects.
	ScoreListener::scoreTable = ScoreListener::ScoreTable::GetScore();

	// Get the bonuses.
	ScoreListener::bonusTable = ScoreListener::BonusTable::GetBonuses();
}