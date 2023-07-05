#pragma once

#define CONFIG_VERSION "3.0.0"
#define INI_FILE "EnhancedDash.ini"

class Configuration
{
public:
	static inline const std::string CameraShakeNames[] =
	{
		"sn_homingattack",   // Low
		"SpinBoostCharge",   // Medium
		"sn_enemy_defeat0",  // High
		"sn_miniboss_defeat" // Extreme
	};

	static enum ECommonUncurlType
	{
		ECommonUncurlType_None,
		ECommonUncurlType_Immediate,
		ECommonUncurlType_Grounded
	};

	static enum EFocusDashCameraStickType
	{
		EFocusDashCameraStickType_Left,
		EFocusDashCameraStickType_Right
	};

	static enum ESlideDashActionType
	{
		ESlideDashActionType_Disabled,
		ESlideDashActionType_DropDash,
		ESlideDashActionType_SpinMove
	};

	static enum ESpinDashReleaseActionType
	{
		ESpinDashReleaseActionType_SpinBoost,
		ESpinDashReleaseActionType_DropDash
	};

	static enum ESpinDashSlideActionType
	{
		ESpinDashSlideActionType_None,
		ESpinDashSlideActionType_Exit,
		ESpinDashSlideActionType_Slide,
		ESpinDashSlideActionType_SpinCharge,
		ESpinDashSlideActionType_DropDash
	};

	static enum ESpinMoveEffectsType
	{
		ESpinMoveEffectsType_Disabled,
		ESpinMoveEffectsType_VelocityBased,
		ESpinMoveEffectsType_Always
	};

	static enum ESpinMoveTerminalVelocityType
	{
		ESpinMoveTerminalVelocityType_Disabled,
		ESpinMoveTerminalVelocityType_SpinDashSV,
		ESpinMoveTerminalVelocityType_SpinDashFV,
		ESpinMoveTerminalVelocityType_SpinDash
	};

	static enum EWorldType
	{
		EWorldType_Both,
		EWorldType_CyberOnly,
		EWorldType_IslandOnly
	};

	// Info
	inline static std::string ConfigVersion = CONFIG_VERSION;

	// Air Dash
	inline static bool IsAirDash = true;
	inline static EWorldType AirDashWorldType = EWorldType_Both;
	inline static ECommonUncurlType AirDashUncurlType = ECommonUncurlType_None;
	inline static float AirDashInitialVelocitySV = 10.0f;
	inline static float AirDashInitialVelocity = 30.0f;
	inline static bool IsAirDashNoCameraDelay = false;

	// Air Tricks
	inline static bool IsAirTricksEnhanced = true;
	inline static float AirTrickMinBoostReward = 1.0f;
	inline static float AirTrickMaxBoostReward = 5.0f;
	inline static float AirTrickSamePenalty = 0.5f;
	inline static float AirTrickFatigueTime = 75.0f;

	// Drift
	inline static bool IsDriftEnhancedCyberPhysics = true;
	inline static bool IsDriftEnhancedIslandPhysics = true;

	// Drop Dash
	inline static bool IsDropDashAirBoostCancel = true;
	inline static bool IsDropDashQuickStepCancel = true;
	inline static bool IsDropDashStompCancel = true;
	inline static bool IsDropDashCancelWhenUngrounded = false;
	inline static bool IsDropDashNoCameraDelay = false;
	inline static bool IsDropDashNoFans = true;
	inline static bool IsDropDashSideViewRollFix = true;
	inline static bool IsDropDashEnhancedCyberPhysics = true;
	inline static bool IsDropDashEnhancedIslandPhysics = true;

	// Focus Dash
	inline static bool IsFocusDash = true;
	inline static EWorldType FocusDashWorldType = EWorldType_IslandOnly;
	inline static float FocusDashInitialVelocitySV = 50.0f;
	inline static float FocusDashInitialVelocity = 75.0f;
	inline static EFocusDashCameraStickType FocusDashCameraStickType = EFocusDashCameraStickType_Left;
	inline static float FocusDashYawSensitivity = 6.5f;
	inline static float FocusDashPitchSensitivity = 3.25f;
	inline static float FocusDashActiveBoostConsumption = 2.5f;
	inline static float FocusDashMinPitchBoostConsumption = 5.0f;
	inline static float FocusDashMaxPitchBoostConsumption = 50.0f;
	inline static bool IsFocusDashNoBoostReplenishment = true;
	inline static bool IsFocusDashVFX = true;
	inline static bool IsFocusDashSE = true;

	// Slide Dash
	inline static ESlideDashActionType SlideDashActionTypeSV = ESlideDashActionType_SpinMove;
	inline static ESlideDashActionType SlideDashActionType = ESlideDashActionType_DropDash;
	inline static bool IsSlideDashNoDropDashCameraDelay = false;

	// Spin Charge
	inline static int SpinChargeCameraShakeType = 1;
	inline static float SpinChargeInitialReleaseVelocitySV = 5.0f;
	inline static float SpinChargeInitialReleaseVelocity = 10.0f;
	inline static float SpinChargeMultiplier = 0.25f;
	inline static float SpinChargeTerminalReleaseVelocity = 100.0f;
	inline static float SpinChargeVelocityDecayRate = 10.0f;
	inline static bool IsSpinChargeNoAirCamera = true;
	inline static bool IsSpinChargeNoAirDeceleration = true;

	// Spin Dash
	inline static ESpinDashReleaseActionType SpinDashReleaseActionType = ESpinDashReleaseActionType_SpinBoost;
	inline static ESpinDashSlideActionType SpinDashSlideActionType = ESpinDashSlideActionType_SpinCharge;
	inline static bool IsSpinDashStompCancel = false;
	inline static bool IsSpinDashNoDropDashCameraDelay = true;
	inline static bool IsSpinDashEnhancedCyberPhysics = true;
	inline static bool IsSpinDashEnhancedIslandPhysics = true;

	// Spin Move
	inline static ESpinMoveEffectsType SpinMoveEffectsType = ESpinMoveEffectsType_VelocityBased;
	inline static ESpinMoveTerminalVelocityType SpinMoveTerminalVelocityType = ESpinMoveTerminalVelocityType_SpinDashSV;
	inline static bool IsSpinMoveAirBoostCancel = true;
	inline static bool IsSpinMoveStompCancel = true;
	inline static bool IsSpinMoveCancelWhenUngrounded = false;
	inline static bool IsSpinMoveEnhancedCyberPhysics = true;
	inline static bool IsSpinMoveEnhancedIslandPhysics = true;

	// Quick Stomp Dash
	inline static bool IsQuickStompDash = false;
	inline static EWorldType QuickStompDashWorldType = EWorldType_IslandOnly;
	inline static ECommonUncurlType QuickStompDashUncurlType = ECommonUncurlType_None;
	inline static float QuickStompDashVelocityThresholdSV = 15.0f;
	inline static float QuickStompDashVelocityThreshold = 25.0f;
	inline static bool IsQuickStompDashNoCameraDelay = false;
	inline static bool IsQuickStompDashRequireAirBoost = true;

	static void Read();
};