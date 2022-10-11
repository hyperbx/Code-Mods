bool Configuration::alwaysActiveReticle = true;
bool Configuration::doubleJump          = true;
bool Configuration::groundHoming        = true;
bool Configuration::stompBounce         = true;
bool Configuration::boostOnRT           = true;
bool Configuration::homingOnX           = true;
bool Configuration::lightDashOnLS       = true;

float Configuration::doubleJumpVelocity       = 15.0f;
float Configuration::doubleJumpVelocityWater  = 10.0f;
float Configuration::dropDashVelocity         = 75.0f;
float Configuration::spinAttackRollDuration   = 3.5f;
float Configuration::stompBounceDelay         = 0.08f;
float Configuration::stompBounceVelocity      = 20.0f;
float Configuration::stompBounceVelocityWater = 100.0f;

Configuration::DropDashType Configuration::dropDashType = Configuration::DropDashType::ForwardView;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Behaviour
	Configuration::alwaysActiveReticle      = reader.GetBoolean("Behaviour", "alwaysActiveReticle", alwaysActiveReticle);
	Configuration::doubleJump               = reader.GetBoolean("Behaviour", "doubleJump", doubleJump);
	Configuration::groundHoming             = reader.GetBoolean("Behaviour", "groundHoming", groundHoming);
	Configuration::stompBounce              = reader.GetBoolean("Behaviour", "stompBounce", stompBounce);
	Configuration::dropDashType             = (Configuration::DropDashType)reader.GetInteger("Behaviour", "dropDashType", dropDashType);
	Configuration::doubleJumpVelocity       = reader.GetReal("Behaviour", "doubleJumpVelocity", doubleJumpVelocity);
	Configuration::doubleJumpVelocityWater  = reader.GetReal("Behaviour", "doubleJumpVelocityWater", doubleJumpVelocityWater);
	Configuration::dropDashVelocity         = reader.GetReal("Behaviour", "dropDashVelocity", dropDashVelocity);
	Configuration::spinAttackRollDuration   = reader.GetReal("Behaviour", "spinAttackRollDuration", spinAttackRollDuration);
	Configuration::stompBounceDelay         = reader.GetReal("Behaviour", "stompBounceDelay", stompBounceDelay);
	Configuration::stompBounceVelocity      = reader.GetReal("Behaviour", "stompBounceVelocity", stompBounceVelocity);
	Configuration::stompBounceVelocityWater = reader.GetReal("Behaviour", "stompBounceVelocityWater", stompBounceVelocityWater);

	// Controls
	Configuration::boostOnRT     = reader.GetBoolean("Controls", "boostOnRT", boostOnRT);
	Configuration::homingOnX     = reader.GetBoolean("Controls", "homingOnX", homingOnX);
	Configuration::lightDashOnLS = reader.GetBoolean("Controls", "lightDashOnLS", lightDashOnLS);
}