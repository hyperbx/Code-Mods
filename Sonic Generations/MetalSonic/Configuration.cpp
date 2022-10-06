bool Configuration::soundEffects = true;
bool Configuration::disableDrowning = true;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Behaviour
	Configuration::soundEffects    = reader.GetBoolean("Behaviour", "soundEffects", soundEffects);
	Configuration::disableDrowning = reader.GetBoolean("Behaviour", "disableDrowning", disableDrowning);
}