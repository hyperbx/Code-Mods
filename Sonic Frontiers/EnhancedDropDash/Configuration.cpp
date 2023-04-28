void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Physics
	INI_READ_BOOLEAN("Physics", IsEnhancedIslandPhysics);
	INI_READ_BOOLEAN("Physics", IsEnhancedCyberPhysics);

	// Controls
	INI_READ_BOOLEAN("Controls", IsDropDashOnSlide);
	INI_READ_BOOLEAN("Controls", IsDropDashOnStomp);
	INI_READ_FLOAT("Controls", StompVelocityThreshold);

	// Behaviour
	INI_READ_BOOLEAN("Behaviour", IsUncurlWhenUngrounded);
	INI_READ_BOOLEAN("Behaviour", IsStompDashUncurlImmediate);
	INI_READ_BOOLEAN("Behaviour", IsGrindDoubleJumpFix);

	// Camera
	INI_READ_BOOLEAN("Camera", IsNoCameraDelay);
	INI_READ_BOOLEAN("Camera", IsNoSlideCameraDelay);
	INI_READ_BOOLEAN("Camera", IsNoStompCameraDelay);
}