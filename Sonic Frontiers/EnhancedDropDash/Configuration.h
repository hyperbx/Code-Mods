#pragma once

#define INI_FILE "EnhancedDropDash.ini"

class Configuration
{
public:
	// Physics
	inline static bool IsEnhancedIslandPhysics = true;
	inline static bool IsEnhancedCyberPhysics  = true;

	// Controls
	inline static bool IsDropDashOnSlide = true;
	inline static bool IsDropDashOnStomp = false;
	inline static float StompVelocityThreshold = 25.0f;

	// Behaviour
	inline static bool IsUncurlWhenUngrounded         = false;
	inline static bool IsStompAllowedUngroundedUncurl = false;
	inline static bool IsGrindDoubleJumpFix           = true;

	// Camera
	inline static bool IsNoCameraDelay      = false;
	inline static bool IsNoSlideCameraDelay = false;
	inline static bool IsNoStompCameraDelay = false;

	static void Read();
};