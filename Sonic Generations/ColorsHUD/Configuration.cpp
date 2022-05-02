bool Configuration::GaugeShake = true;
std::string Configuration::UIType = "ui";

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Main
	Configuration::UIType = reader.Get("Main", "IncludeDir2", UIType);
	Configuration::GaugeShake = reader.GetBoolean("Main", "GaugeShake", GaugeShake);
}