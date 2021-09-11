string Configuration::gaugeType = ".\\ui\\gauge\\";
string Configuration::tailsSave = ".\\ui\\lives\\";

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Main
	Configuration::gaugeType = reader.Get("Main", "IncludeDir1", gaugeType);
	Configuration::tailsSave = reader.Get("Main", "IncludeDir2", tailsSave);
}