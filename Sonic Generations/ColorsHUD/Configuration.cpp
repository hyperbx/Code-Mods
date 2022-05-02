bool Configuration::GaugeShake = true;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Main
	Configuration::GaugeShake = reader.GetBoolean("Main", "GaugeShake", GaugeShake);
}