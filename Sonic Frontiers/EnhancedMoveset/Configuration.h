#pragma once

#include "StateSpinBoostCharge.h"

#define CONFIG_VERSION "3.0.0"

static enum EBulletDashCameraStickType
{
	EBulletDashCameraStickType_Left,
	EBulletDashCameraStickType_Right
};

static enum EInitialVelocityType
{
	EInitialVelocityType_None,
	EInitialVelocityType_Static,
	EInitialVelocityType_Dynamic
};

static enum ESlideDashActionType
{
	ESlideDashActionType_Disabled,
	ESlideDashActionType_DropDash,
	ESlideDashActionType_SpinMove
};

static enum ESpinChargeControlType
{
	ESpinChargeControlType_Frontiers,
	ESpinChargeControlType_LostWorld
};

static enum EUncurlType
{
	EUncurlType_None,
	EUncurlType_Immediate,
	EUncurlType_Grounded
};

static enum EViewType
{
	EViewType_Disabled,
	EViewType_SideViewOnly,
	EViewType_ForwardViewOnly,
	EViewType_Always
};

static enum EWorldType
{
	EWorldType_Both,
	EWorldType_CyberOnly,
	EWorldType_IslandOnly
};

class Configuration
{
#pragma region Implementation
private:
	inline static std::thread m_WatchThread;

public:
	inline static std::string ConfigFileName = "EnhancedMoveset.ini";
	inline static std::string ConfigInfoFileName = "info.ini";

	inline static std::filesystem::path WorkingDirectory;
	inline static std::filesystem::path ConfigFilePath;
	inline static std::filesystem::path ConfigInfoFilePath;

	inline static bool IsConfigWarningDismissed = false;

	static void SetWorkingDirectory(std::string in_directory)
	{
		if (StringHelper::ContainsSubstring(in_directory, "mod.ini"))
		{
			WorkingDirectory = StringHelper::GetSubstringBeforeLastChar(in_directory, '\\');
		}
		else
		{
			WorkingDirectory = in_directory;
		}

		SoundManager::SetResourcePath(WorkingDirectory / "Resources" / "Sound");

		ConfigFilePath = WorkingDirectory / ConfigFileName;
		ConfigInfoFilePath = WorkingDirectory / ConfigInfoFileName;
	}

	static void Read(bool in_isUpdate = false);

	static void LazyUpdate()
	{
		StateSpinBoostCharge::ConfigLazyUpdate();
	}

	static void StartWatcher(std::string in_directory)
	{
		SetWorkingDirectory(in_directory);

		// Load configuration.
		Read();

		// Update states manually.
		LazyUpdate();

		m_WatchThread = std::thread(Watch);
	}

	static void Watch()
	{
		HANDLE handle = FindFirstChangeNotificationW(WorkingDirectory.c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);

		if (handle == INVALID_HANDLE_VALUE)
			return;

		while (true)
		{
			if (WaitForSingleObject(handle, INFINITE) == WAIT_OBJECT_0)
			{
				printf("[Enhanced Moveset] Configuration modified! Reloading...\n");

				// Reload configuration.
				Read(true);

				// Update reflection parameters.
				Reflection::Refresh();

				// Update states manually.
				LazyUpdate();

				// Reset notification handle.
				FindNextChangeNotification(handle);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}

		FindCloseChangeNotification(handle);
	}
#pragma endregion

#pragma region Properties
	static inline const std::string CameraShakeNames[] =
	{
		"sn_homingattack",   // Low
		"SpinBoostCharge",   // Medium
		"sn_enemy_defeat0",  // High
		"sn_miniboss_defeat" // Extreme
	};

	// Info
	inline static std::string ConfigVersion = CONFIG_VERSION;
	inline static bool IsConfigWatchInfoDisplayed = false;

	// Air Dash
	inline static bool IsAirDash = true;
	inline static EWorldType AirDashWorldType = EWorldType_Both;
	inline static EUncurlType AirDashUncurlTypeSV = EUncurlType_None;
	inline static EUncurlType AirDashUncurlType = EUncurlType_None;
	inline static float AirDashInitialVelocitySV = 10.0f;
	inline static float AirDashInitialVelocity = 30.0f;
	inline static bool IsAirDashNoCameraDelay = false;

	// Air Tricks
	inline static bool IsAirTricksEnhanced = true;
	inline static float AirTrickMinBoostReward = 1.0f;
	inline static float AirTrickMaxBoostReward = 5.0f;
	inline static float AirTrickSamePenalty = 0.5f;
	inline static float AirTrickFatigueTime = 75.0f;

	// Bullet Dash
	inline static bool IsBulletDash = true;
	inline static EWorldType BulletDashWorldType = EWorldType_IslandOnly;
	inline static float BulletDashInitialVelocitySV = 50.0f;
	inline static float BulletDashInitialVelocity = 75.0f;
	inline static EBulletDashCameraStickType BulletDashCameraStickType = EBulletDashCameraStickType_Left;
	inline static float BulletDashYawSensitivity = 6.5f;
	inline static float BulletDashPitchSensitivity = 3.25f;
	inline static float BulletDashActiveBoostConsumption = 2.5f;
	inline static float BulletDashMinPitchBoostConsumption = 5.0f;
	inline static float BulletDashMaxPitchBoostConsumption = 50.0f;
	inline static bool IsBulletDashNoBoostReplenishment = true;
	inline static bool IsBulletDashSuperStompTrajectory = true;

	// Drop Dash
	inline static EViewType DropDashAirTrickCancel = EViewType_ForwardViewOnly;
	inline static bool IsDropDashCancelWhenUngrounded = false;
	inline static bool IsDropDashNoCameraDelay = false;
	inline static bool IsDropDashNoFans = true;
	inline static bool IsDropDashSideViewRollFix = true;
	inline static bool IsDropDashEnhancedCyberPhysics = true;
	inline static bool IsDropDashEnhancedIslandPhysics = true;

	// Flurry Rush
	inline static bool IsFlurryRush = true;
	inline static float FlurryRushDuration = 6.0f;
	inline static float IsFlurryRushNoWildRush = false;

	// Light Speed Attack
	inline static bool IsLightSpeedAttack = true;
	inline static EWorldType LightSpeedAttackWorldType = EWorldType_Both;
	inline static float LightSpeedAttackChargeDuration = 3.5f;
	inline static float LightSpeedAttackDuration = 5.0f;
	inline static bool IsLightSpeedAttackChargeVFX = true;
	inline static bool IsLightSpeedAttackLightDashExit = true;

	// Slide Dash
	inline static ESlideDashActionType SlideDashActionTypeSV = ESlideDashActionType_SpinMove;
	inline static ESlideDashActionType SlideDashActionType = ESlideDashActionType_DropDash;
	inline static bool IsSlideDashNoDropDashCameraDelay = false;

	// Spin Boost
	inline static EInitialVelocityType SpinBoostInitialVelocityType = EInitialVelocityType_None;
	inline static float SpinBoostInitialVelocitySV = 10.0f;
	inline static float SpinBoostInitialVelocity = 20.0f;
	inline static bool IsSpinBoostAlwaysTrickableExit = true;
	inline static bool IsSpinBoostInputReleaseCancel = false;
	inline static bool IsSpinBoostJumpRestore = true;
	inline static bool IsSpinBoostEnhancedCyberPhysics = true;
	inline static bool IsSpinBoostEnhancedIslandPhysics = true;

	// Spin Charge
	inline static int SpinChargeCameraShakeType = 1;
	inline static ESpinChargeControlType SpinChargeControlType = ESpinChargeControlType_Frontiers;
	inline static float SpinChargeMultiplier = 1.5f;
	inline static float SpinChargeHoldMultiplier = 2.5f;
	inline static float SpinChargeInitialReleaseVelocitySV = 5.0f;
	inline static float SpinChargeInitialReleaseVelocity = 10.0f;
	inline static float SpinChargeTerminalReleaseVelocity = 100.0f;
	inline static float SpinChargeVelocityDecayRate = 10.0f;
	inline static bool IsSpinChargeInputCharge = true;
	inline static bool IsSpinChargeNoAirCamera = true;
	inline static bool IsSpinChargeNoAirDeceleration = true;
	inline static bool IsSpinChargeNoGroundCamera = false;
	inline static bool IsSpinChargeBoostRelease = true;
	inline static bool IsSpinChargeVibration = true;

	// Spin Move
	inline static EViewType SpinMoveTerminalVelocityType = EViewType_SideViewOnly;
	inline static float SpinMoveVelocityThresholdSV = 10.0f;
	inline static float SpinMoveVelocityThreshold = 15.0f;
	inline static bool IsSpinMoveAirBoostCancel = true;
	inline static bool IsSpinMoveStompCancel = true;
	inline static bool IsSpinMoveCancelWhenUngrounded = false;
	inline static bool IsSpinMoveEnhancedCyberPhysics = true;
	inline static bool IsSpinMoveEnhancedIslandPhysics = true;

	// Quick Stomp Dash
	inline static bool IsQuickStompDash = false;
	inline static EWorldType QuickStompDashWorldType = EWorldType_IslandOnly;
	inline static EUncurlType QuickStompDashUncurlTypeSV = EUncurlType_None;
	inline static EUncurlType QuickStompDashUncurlType = EUncurlType_None;
	inline static float QuickStompDashVelocityThresholdSV = 15.0f;
	inline static float QuickStompDashVelocityThreshold = 25.0f;
	inline static bool IsQuickStompDashNoCameraDelay = false;
	inline static bool IsQuickStompDashRequireAirBoost = true;
#pragma endregion
};