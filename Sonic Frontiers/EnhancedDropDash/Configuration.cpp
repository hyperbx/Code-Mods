void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Behaviour
	INI_READ_BOOLEAN("Behaviour", IsSlideDash);
	INI_READ_BOOLEAN("Behaviour", IsUncurlWhenUngrounded);
	INI_READ_BOOLEAN("Behaviour", IsNoFansWhenRolling);
	INI_READ_BOOLEAN("Behaviour", IsGrindDoubleJumpFix);
	INI_READ_BOOLEAN("Behaviour", IsSideViewRollFix);

	// Air Dash
	INI_READ_BOOLEAN("AirDash", IsAirDash);
	INI_READ_ENUM("AirDash", EWorldType, AirDashWorldType);
	INI_READ_ENUM("AirDash", EUncurlType, AirDashUncurlType);
	INI_READ_FLOAT("AirDash", AirDashInitialVelocity);
	INI_READ_FLOAT("AirDash", AirDashInitialVelocitySV);

	// Stomp Dash
	INI_READ_BOOLEAN("StompDash", IsStompDash);
	INI_READ_ENUM("StompDash", EWorldType, StompDashWorldType);
	INI_READ_ENUM("StompDash", EStompDashInputType, StompDashInputType);
	INI_READ_ENUM("StompDash", EStompDashInputType, StompDashInputTypeCyber);
	INI_READ_FLOAT("StompDash", StompDashInitialVelocity);
	INI_READ_FLOAT("StompDash", StompDashInitialVelocitySV);

	// Quick Stomp Dash
	INI_READ_BOOLEAN("QuickStompDash", IsQuickStompDash);
	INI_READ_ENUM("QuickStompDash", EWorldType, QuickStompDashWorldType);
	INI_READ_BOOLEAN("QuickStompDash", IsQuickStompDashRequireAirBoost);
	INI_READ_ENUM("QuickStompDash", EUncurlType, QuickStompDashUncurlType);
	INI_READ_FLOAT("QuickStompDash", QuickStompDashVelocityThreshold);
	INI_READ_FLOAT("QuickStompDash", QuickStompDashVelocityThresholdSV);

	// Physics
	INI_READ_BOOLEAN("Physics", IsEnhancedIslandPhysics);
	INI_READ_BOOLEAN("Physics", IsEnhancedCyberPhysics);

	// Camera
	INI_READ_BOOLEAN("Camera", IsNoCameraDelay);
	INI_READ_BOOLEAN("Camera", IsNoSlideDashCameraDelay);
	INI_READ_BOOLEAN("Camera", IsNoAirDashCameraDelay);
	INI_READ_BOOLEAN("Camera", IsNoStompDashCameraDelay);
	INI_READ_BOOLEAN("Camera", IsNoQuickStompDashCameraDelay);
}