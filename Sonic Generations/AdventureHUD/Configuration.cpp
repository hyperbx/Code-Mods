bool Configuration::disableGauge = true;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Behaviour
	Configuration::disableGauge = reader.GetBoolean("Behaviour", "disableGauge", disableGauge);
}