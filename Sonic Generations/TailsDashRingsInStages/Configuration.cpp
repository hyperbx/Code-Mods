Configuration::SoundType Configuration::soundType = Configuration::SoundType::DashRing;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Appearance
	Configuration::soundType = (Configuration::SoundType)reader.GetInteger("Appearance", "soundType", soundType);
}