void Configuration::Read()
{
	INIReader reader("info.ini");

	INI_READ_STRING("Info", ConfigVersion);

	reader = INIReader(INI_FILE);

	if (!StringHelper::Compare(ConfigVersion, CONFIG_VERSION) || reader.GetInteger("StompDash", "StompDashWorldType", -1) != -1)
	{
		MessageBoxA
		(
			nullptr,
			"It appears that you haven't configured Enhanced Dash for the latest version, so the default configuration will be used instead.\n\n"
			"To update your configuration, open the config window for Enhanced Dash in Hedge Mod Manager and click OK.",
			"Enhanced Dash",
			MB_ICONWARNING
		);

		return;
	}

	// Air Dash
	INI_READ_BOOLEAN("AirDash", IsAirDash);
	INI_READ_ENUM("AirDash", EWorldType, AirDashWorldType);
	INI_READ_ENUM("AirDash", ECommonUncurlType, AirDashUncurlType);
	INI_READ_FLOAT("AirDash", AirDashInitialVelocitySV);
	INI_READ_FLOAT("AirDash", AirDashInitialVelocity);
	INI_READ_BOOLEAN("AirDash", IsAirDashNoCameraDelay);

	// Air Tricks
	INI_READ_BOOLEAN("AirTricks", IsAirTricksEnhanced);
	INI_READ_FLOAT("AirTricks", AirTrickMinBoostReward);
	INI_READ_FLOAT("AirTricks", AirTrickMaxBoostReward);
	INI_READ_FLOAT("AirTricks", AirTrickSamePenalty);
	INI_READ_FLOAT("AirTricks", AirTrickFatigueTime);

	// Drift
	INI_READ_BOOLEAN("Drift", IsDriftEnhancedCyberPhysics);
	INI_READ_BOOLEAN("Drift", IsDriftEnhancedIslandPhysics);

	// Drop Dash
	INI_READ_BOOLEAN("DropDash", IsDropDashAirBoostCancel);
	INI_READ_BOOLEAN("DropDash", IsDropDashQuickStepCancel);
	INI_READ_BOOLEAN("DropDash", IsDropDashStompCancel);
	INI_READ_BOOLEAN("DropDash", IsDropDashCancelWhenUngrounded);
	INI_READ_BOOLEAN("DropDash", IsDropDashNoCameraDelay);
	INI_READ_BOOLEAN("DropDash", IsDropDashNoFans);
	INI_READ_BOOLEAN("DropDash", IsDropDashSideViewRollFix);
	INI_READ_BOOLEAN("DropDash", IsDropDashEnhancedCyberPhysics);
	INI_READ_BOOLEAN("DropDash", IsDropDashEnhancedIslandPhysics);

	// Focus Dash
	INI_READ_BOOLEAN("FocusDash", IsFocusDash);
	INI_READ_ENUM("FocusDash", EWorldType, FocusDashWorldType);
	INI_READ_FLOAT("FocusDash", FocusDashInitialVelocitySV);
	INI_READ_FLOAT("FocusDash", FocusDashInitialVelocity);
	INI_READ_ENUM("FocusDash", EFocusDashCameraStickType, FocusDashCameraStickType);
	INI_READ_FLOAT("FocusDash", FocusDashYawSensitivity);
	INI_READ_FLOAT("FocusDash", FocusDashPitchSensitivity);
	INI_READ_FLOAT("FocusDash", FocusDashActiveBoostConsumption);
	INI_READ_FLOAT("FocusDash", FocusDashMinPitchBoostConsumption);
	INI_READ_FLOAT("FocusDash", FocusDashMaxPitchBoostConsumption);
	INI_READ_BOOLEAN("FocusDash", IsFocusDashNoBoostReplenishment);
	INI_READ_BOOLEAN("FocusDash", IsFocusDashVFX);
	INI_READ_BOOLEAN("FocusDash", IsFocusDashSE);

	// Slide Dash
	INI_READ_ENUM("SlideDash", ESlideDashActionType, SlideDashActionTypeSV);
	INI_READ_ENUM("SlideDash", ESlideDashActionType, SlideDashActionType);
	INI_READ_BOOLEAN("SlideDash", IsSlideDashNoDropDashCameraDelay);

	// Spin Charge
	INI_READ_INTEGER("SpinCharge", SpinChargeCameraShakeType);
	INI_READ_FLOAT("SpinCharge", SpinChargeInitialReleaseVelocitySV);
	INI_READ_FLOAT("SpinCharge", SpinChargeInitialReleaseVelocity);
	INI_READ_FLOAT("SpinCharge", SpinChargeMultiplier);
	INI_READ_FLOAT("SpinCharge", SpinChargeTerminalReleaseVelocity);
	INI_READ_FLOAT("SpinCharge", SpinChargeVelocityDecayRate);
	INI_READ_BOOLEAN("SpinCharge", IsSpinChargeNoAirCamera);
	INI_READ_BOOLEAN("SpinCharge", IsSpinChargeNoAirDeceleration);

	// Spin Dash
	INI_READ_ENUM("SpinDash", ESpinDashReleaseActionType, SpinDashReleaseActionType);
	INI_READ_ENUM("SpinDash", ESpinDashSlideActionType, SpinDashSlideActionType);
	INI_READ_BOOLEAN("SpinDash", IsSpinDashStompCancel);
	INI_READ_BOOLEAN("SpinDash", IsSpinDashNoDropDashCameraDelay);
	INI_READ_BOOLEAN("SpinDash", IsSpinDashEnhancedCyberPhysics);
	INI_READ_BOOLEAN("SpinDash", IsSpinDashEnhancedIslandPhysics);

	// Spin Move
	INI_READ_ENUM("SpinMove", ESpinMoveEffectsType, SpinMoveEffectsType);
	INI_READ_BOOLEAN("SpinMove", IsSpinMoveAirBoostCancel);
	INI_READ_BOOLEAN("SpinMove", IsSpinMoveStompCancel);
	INI_READ_BOOLEAN("SpinMove", IsSpinMoveCancelWhenUngrounded);
	INI_READ_ENUM("SpinMove", ESpinMoveTerminalVelocityType,  SpinMoveTerminalVelocityType);
	INI_READ_BOOLEAN("SpinDash", IsSpinMoveEnhancedCyberPhysics);
	INI_READ_BOOLEAN("SpinDash", IsSpinMoveEnhancedIslandPhysics);
	
	// Quick Stomp Dash
	INI_READ_BOOLEAN("QuickStompDash", IsQuickStompDash);
	INI_READ_ENUM("QuickStompDash", EWorldType, QuickStompDashWorldType);
	INI_READ_ENUM("QuickStompDash", ECommonUncurlType, QuickStompDashUncurlType);
	INI_READ_FLOAT("QuickStompDash", QuickStompDashVelocityThresholdSV);
	INI_READ_FLOAT("QuickStompDash", QuickStompDashVelocityThreshold);
	INI_READ_BOOLEAN("QuickStompDash", IsQuickStompDashNoCameraDelay);
	INI_READ_BOOLEAN("QuickStompDash", IsQuickStompDashRequireAirBoost);
}