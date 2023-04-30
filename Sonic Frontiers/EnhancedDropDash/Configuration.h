#pragma once

#define INI_FILE "EnhancedDropDash.ini"

class Configuration
{
public:
	static enum EUncurlType
	{
		EUncurlType_None,
		EUncurlType_Immediate,
		EUncurlType_Grounded
	};

	static enum EWorldType
	{
		EWorldType_Both,
		EWorldType_CyberOnly,
		EWorldType_IslandOnly
	};

	static enum EStompDashInputType
	{
		EStompDashInputType_Hold,
		EStompDashInputType_Press
	};

	// Behaviour
	inline static bool IsSlideDash = true;
	inline static bool IsUncurlWhenUngrounded = false;
	inline static bool IsGrindDoubleJumpFix = true;
	inline static bool IsRetainAirVelocity = true;

	// Air Dash
	inline static bool IsAirDash = false;
	inline static EWorldType AirDashWorldType = EWorldType_Both;
	inline static EUncurlType AirDashUncurlType = EUncurlType_None;
	inline static float AirDashInitialVelocity = 30.0f;
	inline static float AirDashInitialVelocitySV = 10.0f;

	// Stomp Dash
	inline static bool IsStompDash = false;
	inline static EWorldType StompDashWorldType = EWorldType_IslandOnly;
	inline static EStompDashInputType StompDashInputType = EStompDashInputType_Hold;
	inline static float StompDashInitialVelocity = 50.0f;
	inline static float StompDashInitialVelocitySV = 10.0f;

	// Quick Stomp Dash
	inline static bool IsQuickStompDash = false;
	inline static EWorldType QuickStompDashWorldType = EWorldType_IslandOnly;
	inline static bool IsQuickStompDashRequireAirBoost = true;
	inline static EUncurlType QuickStompDashUncurlType = EUncurlType_None;
	inline static float QuickStompDashVelocityThreshold = 25.0f;
	inline static float QuickStompDashVelocityThresholdSV = 15.0f;

	// Physics
	inline static bool IsEnhancedIslandPhysics = true;
	inline static bool IsEnhancedCyberPhysics = true;

	// Camera
	inline static bool IsNoCameraDelay = false;
	inline static bool IsNoAirDashCameraDelay = false;
	inline static bool IsNoSlideDashCameraDelay = false;
	inline static bool IsNoStompDashCameraDelay = false;
	inline static bool IsNoQuickStompDashCameraDelay = false;

	static void Read();
};