bool Configuration::alwaysActiveReticle = true;
bool Configuration::doubleJump          = true;
bool Configuration::groundHoming        = true;
bool Configuration::stompBounce         = true;
bool Configuration::boostOnRT           = true;
bool Configuration::homingOnX           = true;
bool Configuration::lightDashOnLS       = true;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Behaviour
	Configuration::alwaysActiveReticle = reader.GetBoolean("Behaviour", "alwaysActiveReticle", alwaysActiveReticle);
	Configuration::doubleJump          = reader.GetBoolean("Behaviour", "doubleJump", doubleJump);
	Configuration::groundHoming        = reader.GetBoolean("Behaviour", "groundHoming", groundHoming);
	Configuration::stompBounce         = reader.GetBoolean("Behaviour", "stompBounce", stompBounce);

	// Controls
	Configuration::boostOnRT     = reader.GetBoolean("Controls", "boostOnRT", boostOnRT);
	Configuration::homingOnX     = reader.GetBoolean("Controls", "homingOnX", homingOnX);
	Configuration::lightDashOnLS = reader.GetBoolean("Controls", "lightDashOnLS", lightDashOnLS);
}