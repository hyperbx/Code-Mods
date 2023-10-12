#include "Pch.h"
#include "Configuration.h"

#define SHIPPING false

void Configuration::Read(bool in_isUpdate)
{
#pragma region Implementation
#if SHIPPING
	// TODO: resolve message boxes preventing updates.
	if (!in_isUpdate)
	{
		INIReader reader(StringHelper::WideCharToString(ConfigInfoFilePath.c_str()));
		{
			INI_BEGIN_SECTION("Info");
			{
				INI_READ_STRING_B(ConfigVersion);
				INI_READ_BOOLEAN_B(IsConfigWatchInfoDisplayed);
			}
			INI_END_SECTION();
		}

		if (!StringHelper::Compare(ConfigVersion, CONFIG_VERSION) || reader.GetInteger("StompDash", "StompDashWorldType", -1) != -1)
		{
			MessageBoxA
			(
				nullptr,
				"It appears that you haven't configured Enhanced Moveset for the latest version, so the default configuration will be used instead.\n\n"
				"To update your configuration, open the config window for Enhanced Moveset in Hedge Mod Manager and click OK.",
				"Enhanced Moveset",
				MB_ICONWARNING
			);

			IsConfigWarningDismissed = true;

			return;
		}

		if (!IsConfigWatchInfoDisplayed)
		{
			MessageBoxA
			(
				nullptr,
				"Enhanced Moveset supports real-time configuration.\n\n"
				"Whilst the game is running, you can open the config window in Hedge Mod Manager and reconfigure Enhanced Moveset without having to restart.",
				"Enhanced Moveset",
				MB_ICONWARNING
			);

			IsConfigWatchInfoDisplayed = true;

			IOHelper::WriteString
			(
				ConfigInfoFilePath,

				std::format
				(
					"[Info]\n"
					"ConfigVersion=\"{}\"\n"
					"IsConfigWatchInfoDisplayed={}",

					CONFIG_VERSION,
					IsConfigWatchInfoDisplayed ? "true" : "false"
				)
			);
		}
	}
#endif
#pragma endregion

#pragma region Properties
	INIReader reader(StringHelper::WideCharToString(ConfigFilePath.c_str()));
	{
		INI_BEGIN_SECTION("AirDash");
		{
			INI_READ_BOOLEAN_B(IsAirDash);
			INI_READ_ENUM_B(EWorldType, AirDashWorldType);
			INI_READ_ENUM_B(EUncurlType, AirDashUncurlTypeSV);
			INI_READ_ENUM_B(EUncurlType, AirDashUncurlType);
			INI_READ_FLOAT_B(AirDashInitialVelocitySV);
			INI_READ_FLOAT_B(AirDashInitialVelocity);
			INI_READ_BOOLEAN_B(IsAirDashNoCameraDelay);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("AirTricks");
		{
			INI_READ_BOOLEAN_B(IsAirTricksEnhanced);
			INI_READ_FLOAT_B(AirTrickMinBoostReward);
			INI_READ_FLOAT_B(AirTrickMaxBoostReward);
			INI_READ_FLOAT_B(AirTrickSamePenalty);
			INI_READ_FLOAT_B(AirTrickFatigueTime);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("BulletDash");
		{
			INI_READ_BOOLEAN_B(IsBulletDash);
			INI_READ_ENUM_B(EWorldType, BulletDashWorldType);
			INI_READ_FLOAT_B(BulletDashInitialVelocitySV);
			INI_READ_FLOAT_B(BulletDashInitialVelocity);
			INI_READ_ENUM_B(EBulletDashCameraStickType, BulletDashCameraStickType);
			INI_READ_FLOAT_B(BulletDashYawSensitivity);
			INI_READ_FLOAT_B(BulletDashPitchSensitivity);
			INI_READ_FLOAT_B(BulletDashActiveBoostConsumption);
			INI_READ_FLOAT_B(BulletDashMinPitchBoostConsumption);
			INI_READ_FLOAT_B(BulletDashMaxPitchBoostConsumption);
			INI_READ_BOOLEAN_B(IsBulletDashNoBoostReplenishment);
			INI_READ_BOOLEAN_B(IsBulletDashSuperStompTrajectory);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("DropDash");
		{
			INI_READ_ENUM_B(EViewType, DropDashAirTrickCancel);
			INI_READ_BOOLEAN_B(IsDropDashCancelWhenUngrounded);
			INI_READ_BOOLEAN_B(IsDropDashNoCameraDelay);
			INI_READ_BOOLEAN_B(IsDropDashNoFans);
			INI_READ_BOOLEAN_B(IsDropDashSideViewRollFix);
			INI_READ_BOOLEAN_B(IsDropDashEnhancedCyberPhysics);
			INI_READ_BOOLEAN_B(IsDropDashEnhancedIslandPhysics);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("FlurryRush");
		{
			INI_READ_BOOLEAN_B(IsFlurryRush);
			INI_READ_FLOAT_B(FlurryRushDuration);
			INI_READ_BOOLEAN_B(IsFlurryRushNoWildRush);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("LightSpeedAttack");
		{
			INI_READ_BOOLEAN_B(IsLightSpeedAttack);
			INI_READ_ENUM_B(EWorldType, LightSpeedAttackWorldType);
			INI_READ_FLOAT_B(LightSpeedAttackChargeDuration);
			INI_READ_FLOAT_B(LightSpeedAttackDuration);
			INI_READ_BOOLEAN_B(IsLightSpeedAttackChargeVFX);
			INI_READ_BOOLEAN_B(IsLightSpeedAttackLightDashExit);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("SlideDash");
		{
			INI_READ_ENUM_B(ESlideDashActionType, SlideDashActionTypeSV);
			INI_READ_ENUM_B(ESlideDashActionType, SlideDashActionType);
			INI_READ_BOOLEAN_B(IsSlideDashNoDropDashCameraDelay);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("SpinBoost");
		{
			INI_READ_ENUM_B(EInitialVelocityType, SpinBoostInitialVelocityType);
			INI_READ_FLOAT_B(SpinBoostInitialVelocitySV);
			INI_READ_FLOAT_B(SpinBoostInitialVelocity);
			INI_READ_BOOLEAN_B(IsSpinBoostAlwaysTrickableExit);
			INI_READ_BOOLEAN_B(IsSpinBoostInputReleaseCancel);
			INI_READ_BOOLEAN_B(IsSpinBoostJumpRestore);
			INI_READ_BOOLEAN_B(IsSpinBoostEnhancedCyberPhysics);
			INI_READ_BOOLEAN_B(IsSpinBoostEnhancedIslandPhysics);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("SpinCharge");
		{
			INI_READ_INTEGER_B(SpinChargeCameraShakeType);
			INI_READ_ENUM_B(ESpinChargeControlType, SpinChargeControlType);
			INI_READ_FLOAT_B(SpinChargeMultiplier); SpinChargeMultiplier /= 10.0f;
			INI_READ_FLOAT_B(SpinChargeHoldMultiplier); SpinChargeHoldMultiplier /= 10.0f;
			INI_READ_FLOAT_B(SpinChargeInitialReleaseVelocitySV);
			INI_READ_FLOAT_B(SpinChargeInitialReleaseVelocity);
			INI_READ_FLOAT_B(SpinChargeTerminalReleaseVelocity);
			INI_READ_FLOAT_B(SpinChargeVelocityDecayRate);
			INI_READ_BOOLEAN_B(IsSpinChargeInputCharge);
			INI_READ_BOOLEAN_B(IsSpinChargeNoAirCamera);
			INI_READ_BOOLEAN_B(IsSpinChargeNoAirDeceleration);
			INI_READ_BOOLEAN_B(IsSpinChargeNoGroundCamera);
			INI_READ_BOOLEAN_B(IsSpinChargeBoostRelease);
			INI_READ_BOOLEAN_B(IsSpinChargeVibration);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("SpinMove");
		{
			INI_READ_ENUM_B(EViewType, SpinMoveTerminalVelocityType);
			INI_READ_FLOAT_B(SpinMoveVelocityThresholdSV);
			INI_READ_FLOAT_B(SpinMoveVelocityThreshold);
			INI_READ_BOOLEAN_B(IsSpinMoveAirBoostCancel);
			INI_READ_BOOLEAN_B(IsSpinMoveStompCancel);
			INI_READ_BOOLEAN_B(IsSpinMoveCancelWhenUngrounded);
			INI_READ_BOOLEAN_B(IsSpinMoveEnhancedCyberPhysics);
			INI_READ_BOOLEAN_B(IsSpinMoveEnhancedIslandPhysics);
		}
		INI_END_SECTION();

		INI_BEGIN_SECTION("QuickStompDash");
		{
			INI_READ_BOOLEAN_B(IsQuickStompDash);
			INI_READ_ENUM_B(EWorldType, QuickStompDashWorldType);
			INI_READ_ENUM_B(EUncurlType, QuickStompDashUncurlTypeSV);
			INI_READ_ENUM_B(EUncurlType, QuickStompDashUncurlType);
			INI_READ_FLOAT_B(QuickStompDashVelocityThresholdSV);
			INI_READ_FLOAT_B(QuickStompDashVelocityThreshold);
			INI_READ_BOOLEAN_B(IsQuickStompDashNoCameraDelay);
			INI_READ_BOOLEAN_B(IsQuickStompDashRequireAirBoost);
		}
		INI_END_SECTION();
	}
#pragma endregion
}