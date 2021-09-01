bool Configuration::ringFormatter = true;
bool Configuration::homingReticle = true;
bool Configuration::windowTitle = true;
bool Configuration::boostText = true;
int Configuration::buttonType = 0;
int Configuration::difficultyType = 1;
bool Configuration::alwaysActiveReticle = true;
int Configuration::trickSounds = 1;
bool Configuration::homingSound = true;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Appearance
	Configuration::ringFormatter = reader.GetBoolean("Appearance", "ringFormatter", ringFormatter);
	Configuration::homingReticle = reader.GetBoolean("Appearance", "homingReticle", homingReticle);
	Configuration::windowTitle   = reader.GetBoolean("Appearance", "windowTitle", windowTitle);
	Configuration::boostText     = reader.GetBoolean("Appearance", "boostText", boostText);
	Configuration::buttonType    = reader.GetInteger("Appearance", "buttonType", buttonType);

	// Behaviour
	Configuration::difficultyType      = reader.GetInteger("Behaviour", "difficultyType", difficultyType);
	Configuration::alwaysActiveReticle = reader.GetBoolean("Behaviour", "alwaysActiveReticle", alwaysActiveReticle);

	// CPKs
	Configuration::trickSounds = reader.GetInteger("CPKs", "trickSounds", trickSounds);
	Configuration::homingSound = reader.GetBoolean("CPKs", "homingSound", homingSound);
}