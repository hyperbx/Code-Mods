Configuration::ColourType Configuration::colourType = Configuration::ColourType::Green;
Configuration::SoundType Configuration::soundType = Configuration::SoundType::DashRing;
bool Configuration::overrideTailsDashRing = false;
bool Configuration::useCustomRainbowRings = false;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Appearance
	Configuration::colourType			 = (Configuration::ColourType)reader.GetInteger("Appearance", "colourType", colourType);
	Configuration::soundType			 = (Configuration::SoundType)reader.GetInteger("Appearance", "soundType", soundType);
	Configuration::overrideTailsDashRing = reader.GetBoolean("Appearance", "overrideTailsDashRing", overrideTailsDashRing);
	Configuration::useCustomRainbowRings = reader.GetBoolean("Appearance", "useCustomRainbowRings", useCustomRainbowRings);
}