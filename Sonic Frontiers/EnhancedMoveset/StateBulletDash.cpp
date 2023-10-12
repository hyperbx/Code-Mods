#include "MsgShakeCameraName.h"

int m_BulletDashSoundHandle = -1;

float m_BulletDashSuperStompVibration = 0.0f;

HOOK(bool, __fastcall, _StateBulletDash_StateSpinBoostChargeUpdate, m_SigStateSpinBoostChargeUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	if (!Configuration::IsBulletDash)
		return original_StateBulletDash_StateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);

	if (!Player::IsStateAvailableInWorld(Configuration::BulletDashWorldType))
		return original_StateBulletDash_StateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsCharging))
	{
		// Always release Spin Boost on RT regardless of setting.
		if (IsButtonPressed(EPlayerActionType_PlayerBoost))
		{
			Player::SetState(in_pSonicContext, ESonicState_StateSpinBoost);
			return true;
		}

		if (*StatePluginBoost::pCapacity <= 0.0f)
			Player::SetState(in_pSonicContext, ESonicState_StateFall);

		return original_StateBulletDash_StateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);
	}

	auto expectedInput = (Configuration::BulletDashCameraStickType == EBulletDashCameraStickType_Left
		? EPlayerActionType_PlayerLightDash
		: EPlayerActionType_CameraGaze);

	if (IsButtonPressed(expectedInput) && !Player::IsGrounded())
	{
		StateBulletDash::Flags.set(EStateBulletDashFlags_IsCharging);

		Player::SetBulletTime(true);

		StateSpinBoostCharge::StartSpinChargeCamera(in_pSonicContext);
	}

	return original_StateBulletDash_StateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, _StateBulletDash_StateSpinBoostChargeEnd, m_SigStateSpinBoostChargeEnd(), int64_t in_pThis, int64_t in_pSonicContext, int64_t a3)
{
	Player::SetBulletTime(false);

	StateBulletDash::Flags.reset(EStateBulletDashFlags_IsForwardRestored);

	RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeMovement());

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsActive))
	{
		float minConsume = Configuration::BulletDashMinPitchBoostConsumption;
		float maxConsume = Configuration::BulletDashMaxPitchBoostConsumption;

		// Subtract boost upon release, amount depending on Sonic's pitch direction.
		if (minConsume < maxConsume && StatePluginBoost::CanConsumeBoost())
			*StatePluginBoost::pCapacity -= RANGE(StateBulletDash::PitchScale, -1.0f, 1.0f, minConsume, maxConsume);

		if (Configuration::IsBulletDashSuperStompTrajectory)
			StateBulletDash::Flags.set(EStateBulletDashFlags_IsSuperStompTrajectory, StateBulletDash::PitchScale <= -0.25f);
	}

	StateBulletDash::YawScale = 0.0f;
	StateBulletDash::PitchScale = 0.0f;

	return original_StateBulletDash_StateSpinBoostChargeEnd(in_pThis, in_pSonicContext, a3);
}

HOOK(bool, __fastcall, _StateBulletDash_GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, ESonicState in_stateId)
{
	if (in_stateId == ESonicState_StateSpinBoost)
	{
		if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsCharging))
		{
			StateBulletDash::Flags.set(EStateBulletDashFlags_IsActive);
			StateBulletDash::Flags.set(EStateBulletDashFlags_IsReleased);

			if (Configuration::IsBulletDashNoBoostReplenishment)
				StatePluginBoost::IsRecharge = false;
		}
	}

	StateBulletDash::Flags.reset(EStateBulletDashFlags_IsCharging);

	return original_StateBulletDash_GOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

HOOK(int64_t, __fastcall, _StateBulletDash_PlayerKinematicsAirUpdate, READ_CALL(m_SigPlayerKinematicsAirUpdateCaller()), int64_t in_pThis, app::player::GOCPlayerKinematicParams* in_pGOCPlayerKinematicParams)
{
	auto forward = in_pGOCPlayerKinematicParams->Rotation.GetForward();

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsCharging))
	{
		float normAnalogX = (Configuration::BulletDashCameraStickType == EBulletDashCameraStickType_Left
			? Input::GetAnalog(Input::EInputIndex_Left).x()
			: Input::GetAnalog(Input::EInputIndex_Right).x());
		
		float normAnalogY = (Configuration::BulletDashCameraStickType == EBulletDashCameraStickType_Left
			? Input::GetAnalog(Input::EInputIndex_Left).y()
			: Input::GetAnalog(Input::EInputIndex_Right).y());

		float normAnalogDirX = (normAnalogX > 0.0f ? 1.0f : -1.0f);
		float normAnalogDirY = (normAnalogY > 0.0f ? 1.0f : -1.0f);

		csl::math::Quaternion yaw;
		csl::math::Quaternion pitch;

		// Yaw
		{
			float yawSpeed = Configuration::BulletDashYawSensitivity;
			float yawAcceleration = (abs(normAnalogX) * yawSpeed) * Player::DeltaTime;

			// Disable the original movement implementation to reduce updates to yaw rotation that cause stutter.
			if (m_SigDisableSpinChargeMovement() != nullptr)
			{
				PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeMovement(), 6);
				WRITE_JUMP((int64_t)m_SigDisableSpinChargeMovement(), ReadJump((int64_t)m_SigDisableSpinChargeMovement()));
			}

			StateBulletDash::YawScale += yawAcceleration * normAnalogDirX;

			if (!StateBulletDash::Flags.test(EStateBulletDashFlags_IsForwardRestored))
			{
				StateBulletDash::Flags.set(EStateBulletDashFlags_IsForwardRestored);
				StateBulletDash::Forward = forward;
			}

			yaw = csl::math::Quaternion::LookRotation(StateBulletDash::Forward) * (BlackboardHelper::IsSideView()
				? csl::math::Quaternion::Identity // Lock yaw to forward vector in side view to prevent left/right movement.
				: csl::math::Quaternion::FromAngleAxis(-StateBulletDash::YawScale, csl::math::Vector3(0.0f, 1.0f, 0.0f)));
		}

		// Pitch
		{
			float pitchSpeed = Configuration::BulletDashPitchSensitivity;
			float pitchAcceleration = (abs(normAnalogY) * pitchSpeed) * Player::DeltaTime;
			float pitchMaxAngle = 75.0f;

			// Disable pitch resetting to neutral to allow for smoother pitch rotation.
			if (m_SigDisableSpinChargePitchReset() != nullptr)
			{
				PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargePitchReset(), 5);
				WRITE_NOP(m_SigDisableSpinChargePitchReset(), 5);
			}

			StateBulletDash::PitchScale = std::clamp(StateBulletDash::PitchScale + (pitchAcceleration * normAnalogDirY), -1.0f, 1.0f);

			pitch = csl::math::Quaternion::FromAngleAxis(-StateBulletDash::PitchScale * (pitchMaxAngle * DEG2RADf), csl::math::Vector3(1.0f, 0.0f, 0.0f));
		}

		in_pGOCPlayerKinematicParams->Rotation = (csl::math::Quaternion::Identity * yaw * pitch);
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeMovement());
		RESTORE_MEMORY((int64_t)m_SigDisableSpinChargePitchReset());
	}

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsReleased))
	{
		StateBulletDash::Flags.reset(EStateBulletDashFlags_IsReleased);

		in_pGOCPlayerKinematicParams->Velocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::BulletDashInitialVelocitySV
			: Configuration::BulletDashInitialVelocity);
	}

	return original_StateBulletDash_PlayerKinematicsAirUpdate(in_pThis, in_pGOCPlayerKinematicParams);
}

HOOK(int64_t, __fastcall, _StateBulletDash_StartSpinChargeCameraStart, m_SigStartSpinChargeCamera(), int64_t in_pStatePluginCamera, const char* in_pCameraName)
{
	original_StateBulletDash_StartSpinChargeCameraStart(in_pStatePluginCamera, in_pCameraName);

	auto pPlayerCameraParameter = *(int64_t*)(in_pStatePluginCamera + 0x28);
	auto pLocalEyeOffset = (Vector3*)(pPlayerCameraParameter + 0x60);

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsCharging))
	{
		pLocalEyeOffset->Z = 4.75f;
	}
	else
	{
		pLocalEyeOffset->Z = 3.5f;
	}

	return original_StateBulletDash_StartSpinChargeCameraStart(in_pStatePluginCamera, in_pCameraName);
}

// This hook is a hack to obtain app::player::SonicContext, since the singleton from app::player::Sonic doesn't seem to work properly.
HOOK(int64_t, __fastcall, _StateBulletDash_StatePluginBoostUpdate, m_SigStatePluginBoostUpdate(), int64_t in_pThis, int64_t a2, float in_deltaTime)
{
	// Ignore bad naming convention, used for macro.
	int64_t in_pSonicContext = *(int64_t*)(in_pThis + 0x20);

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsActive))
	{
		// Allow Bullet Dash again after reaching 100% boost from tricks.
		if (*StatePluginBoost::pCapacity >= 100.0f)
			*(int32_t*)(in_pThis + 0x80) = 0;

		if (Configuration::IsBulletDashSuperStompTrajectory)
		{
			if (Player::IsGrounded() && StateBulletDash::Flags.test(EStateBulletDashFlags_IsSuperStompTrajectory))
				Player::SetState(in_pSonicContext, ESonicState_StateStompingDown);
		}
	}

	if (Player::IsGroundedSpecial())
	{
		StateBulletDash::Flags.reset(EStateBulletDashFlags_IsActive);
		StatePluginBoost::IsRecharge = true;
	}

	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsSuperStompLand))
	{
		m_BulletDashSuperStompVibration = max(std::lerp(m_BulletDashSuperStompVibration - 1.25f, 0.0f, Player::DeltaTime), 0.0f);

		Input::SetRumbleMotors(m_BulletDashSuperStompVibration);

		if (m_BulletDashSuperStompVibration <= 0)
			StateBulletDash::Flags.reset(EStateBulletDashFlags_IsSuperStompLand);
	}

	// Drain boost energy when charging Bullet Dash.
	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsCharging) && StatePluginBoost::CanConsumeBoost())
	{
		*StatePluginBoost::pCapacity -= (Configuration::BulletDashActiveBoostConsumption * 100.0f) * in_deltaTime;
	}

	return original_StateBulletDash_StatePluginBoostUpdate(in_pThis, a2, in_deltaTime);
}

HOOK(double, __fastcall, _StateBulletDash_StateStompingLandStart, m_SigStateStompingLandStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	if (StateBulletDash::Flags.test(EStateBulletDashFlags_IsSuperStompTrajectory))
	{
		// Force highest stomp count for shockwave.
		*(int*)(in_pThis + 0xB0) = 2;

		m_BulletDashSuperStompVibration = 100.0f;

		StateBulletDash::Flags.set(EStateBulletDashFlags_IsSuperStompLand);
		StateBulletDash::Flags.reset(EStateBulletDashFlags_IsSuperStompTrajectory);
	}

	return original_StateBulletDash_StateStompingLandStart(in_pThis, in_pSonicContext);
}

void StateBulletDash::Install()
{
	INSTALL_HOOK(_StateBulletDash_StateSpinBoostChargeUpdate);
	INSTALL_HOOK(_StateBulletDash_StateSpinBoostChargeEnd);
	INSTALL_HOOK(_StateBulletDash_GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(_StateBulletDash_PlayerKinematicsAirUpdate);
	INSTALL_HOOK(_StateBulletDash_StartSpinChargeCameraStart);
	INSTALL_HOOK(_StateBulletDash_StatePluginBoostUpdate);
	INSTALL_HOOK(_StateBulletDash_StateStompingLandStart);
}