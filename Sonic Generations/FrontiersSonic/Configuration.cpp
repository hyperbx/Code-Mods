bool Configuration::alwaysActiveReticle   = true;
bool Configuration::cameraShake           = true;
bool Configuration::disableBoostCollision = true;
bool Configuration::doubleJump            = true;
bool Configuration::groundHoming          = true;
bool Configuration::homingSlowMotion      = true;
bool Configuration::stompBounce           = true;
bool Configuration::boostOnRT             = true;
bool Configuration::homingOnX             = true;
bool Configuration::lightDashOnLS         = true;

float Configuration::doubleJumpVelocity          = 15.0f;
float Configuration::doubleJumpVelocityWater     = 10.0f;
float Configuration::dropDashVelocitySideView    = 45.0f;
float Configuration::dropDashVelocityForwardView = 75.0f;
float Configuration::spinAttackRollDuration      = 3.5f;
float Configuration::stompBounceDelay            = 0.08f;
float Configuration::stompBounceVelocity         = 20.0f;
float Configuration::stompBounceVelocityWater    = 10.0f;

int Configuration::stompBounceCount = 2;

Configuration::DropDashType Configuration::dropDashType = Configuration::DropDashType::ForwardView;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Behaviour
	Configuration::alwaysActiveReticle         = reader.GetBoolean("Behaviour", "alwaysActiveReticle", alwaysActiveReticle);
	Configuration::cameraShake                 = reader.GetBoolean("Behaviour", "cameraShake", cameraShake);
	Configuration::disableBoostCollision       = reader.GetBoolean("Behaviour", "disableBoostCollision", disableBoostCollision);
	Configuration::doubleJump                  = reader.GetBoolean("Behaviour", "doubleJump", doubleJump);
	Configuration::groundHoming                = reader.GetBoolean("Behaviour", "groundHoming", groundHoming);
	Configuration::homingSlowMotion            = reader.GetBoolean("Behaviour", "homingSlowMotion", homingSlowMotion);
	Configuration::stompBounce                 = reader.GetBoolean("Behaviour", "stompBounce", stompBounce);
	Configuration::dropDashType                = Configuration::DropDashType::Both; // TODO: = (Configuration::DropDashType)reader.GetInteger("Behaviour", "dropDashType", dropDashType);
	Configuration::dropDashVelocitySideView    = reader.GetReal("Behaviour", "dropDashVelocitySideView", dropDashVelocitySideView);
	Configuration::dropDashVelocityForwardView = reader.GetReal("Behaviour", "dropDashVelocityForwardView", dropDashVelocityForwardView);
	Configuration::doubleJumpVelocity          = reader.GetReal("Behaviour", "doubleJumpVelocity", doubleJumpVelocity);
	Configuration::doubleJumpVelocityWater     = reader.GetReal("Behaviour", "doubleJumpVelocityWater", doubleJumpVelocityWater);
	Configuration::spinAttackRollDuration      = reader.GetReal("Behaviour", "spinAttackRollDuration", spinAttackRollDuration);
	Configuration::stompBounceCount            = reader.GetInteger("Behaviour", "stompBounceCount", stompBounceCount);
	Configuration::stompBounceDelay            = reader.GetReal("Behaviour", "stompBounceDelay", stompBounceDelay);
	Configuration::stompBounceVelocity         = reader.GetReal("Behaviour", "stompBounceVelocity", stompBounceVelocity);
	Configuration::stompBounceVelocityWater    = reader.GetReal("Behaviour", "stompBounceVelocityWater", stompBounceVelocityWater);

	// Controls
	Configuration::boostOnRT     = reader.GetBoolean("Controls", "boostOnRT", boostOnRT);
	Configuration::homingOnX     = reader.GetBoolean("Controls", "homingOnX", homingOnX);
	Configuration::lightDashOnLS = reader.GetBoolean("Controls", "lightDashOnLS", lightDashOnLS);
}