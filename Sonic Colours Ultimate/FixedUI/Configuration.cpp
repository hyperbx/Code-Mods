string Configuration::gaugeType = ".\\ui\\gauge\\";
string Configuration::tailsSave = ".\\ui\\lives\\";
Configuration::RingLifeType Configuration::ringLifeType = Configuration::RingLifeType::Disabled;
bool Configuration::forceDisableNavi = false;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Main
	Configuration::gaugeType = reader.Get("Main", "IncludeDir1", gaugeType);
	Configuration::tailsSave = reader.Get("Main", "IncludeDir2", tailsSave);
	Configuration::ringLifeType = (Configuration::RingLifeType)reader.GetInteger("Main", "ringLifeType", ringLifeType);
	Configuration::forceDisableNavi = reader.GetBoolean("Main", "forceDisableNavi", forceDisableNavi);
}