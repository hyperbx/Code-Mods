// TODO: split this file into multiple for maintainability.

#define SONIC_CONTEXT_IS_GROUNDED(in_pSonicContext) *(bool*)((*(int64_t*)(in_pSonicContext + 72) + 400) + 53) & 2

std::bitset<6> m_DropDashStateFlags;
std::bitset<4> m_InputFlags;
std::bitset<11> m_PersistentStateFlags;

enum ECollisionType : uint8_t
{
	ECollisionType_Default,
	ECollisionType_Hit = 2
};

enum EDropDashStateFlags
{
	EDropDashStateFlags_IsAirDash,
	EDropDashStateFlags_IsAirDashRelease,
	EDropDashStateFlags_IsDropDash,
	EDropDashStateFlags_IsDropDashCharge,
	EDropDashStateFlags_IsGroundedOnce,
	EDropDashStateFlags_IsSlideDash
};

enum EInputFlags
{
	EInputFlags_IsJumpInputBuffered,
	EInputFlags_IsLeftTriggerBuffered,
	EInputFlags_IsRightTriggerBuffered,
	EInputFlags_IsUncurlInputBuffered
};

enum EPersistentStateFlags
{
	EPersistentStateFlags_IsAirDashExitDoubleJump,
	EPersistentStateFlags_IsAirDashExitRecovery,
	EPersistentStateFlags_IsAirDashFromRecoveryJump,
	EPersistentStateFlags_IsAirTrickFatigueBegin,
	EPersistentStateFlags_IsDoubleJumpFromSpinBoost,
	EPersistentStateFlags_IsFocusDash,
	EPersistentStateFlags_IsFocusDashCharge,
	EPersistentStateFlags_IsFocusDashForwardRestored,
	EPersistentStateFlags_IsFocusDashRelease,
	EPersistentStateFlags_IsSpinChargeRelease,
	EPersistentStateFlags_IsQuickStompDash
};

enum EStateID
{
	EStateID_Default = -1,
	EStateID_StateRun = 4,
	EStateID_StateDoubleJump = 9,
	EStateID_StateStompingBounce = 11,
	EStateID_StateRecoveryJump = 12,
	EStateID_StateFall = 15,
	EStateID_StateRecovery = 16,
	EStateID_StateSquat = 19,
	EStateID_StateAirBoost = 23,
	EStateID_StateLightDash = 25,
	EStateID_StateGrindDoubleJump = 48,
	EStateID_StateStomping = 54,
	EStateID_StateStompingLand = 57,
	EStateID_StateSliding = 59,
	EStateID_StateQuickStep = 65,
	EStateID_StateQuickStepLeft = 71,
	EStateID_StateQuickStepRight = 72,
	EStateID_StateDropDash = 112,
	EStateID_StateSpin = 113,
	EStateID_StateSpinBoostCharge = 115,
	EStateID_StateSpinBoost = 116,
	EStateID_StateSpinMove = 117,
	EStateID_StateFan = 168
};

// TODO: clean up some of this garbage, put in structs or something.

float* m_Boost;
float* m_BoostMax;
float* m_InfiniteBoostTime;
bool m_CanBoost = true;
bool m_IsInfiniteBoostGaugeCode = false;

float m_DeltaTime = 0.0f;

float m_DropDashDelayTime = 0.0f;

Quaternion m_Rotation = Quaternion::Identity();
float m_Velocity = 0.0f;
float m_HorizontalVelocity = 0.0f;

float m_SpinChargeMultiplier = 0.0f;
float m_SpinChargeReleaseVelocity = 0.0f;

Vector3 m_FocusDashForward = Vector3::Zero();
float m_FocusDashYawScale = 0.0f;
float m_FocusDashPitchScale = 0.0f;
int m_FocusDashSoundHandle;

int m_SpinMoveSoundHandle;

float m_TrickReward = 1.0f;
float m_TrickBoostFatigue = 0.0f;
int m_LastTrickDirection = 0;

EStateID m_LastStateID = EStateID_Default;

FUNCTION_PTR(bool, __fastcall, fpSetCurrentState, m_SigSetCurrentState(), int64_t a1, int a2, int a3);
FUNCTION_PTR(void, __fastcall, fpPlayAnimation, m_SigPlayAnimation(), int64_t in_pGOCPlayerVisual, const char* in_pAnimationName, uint8_t a3);
FUNCTION_PTR(double, __fastcall, fpSetAnimationParameter, m_SigSetAnimationParameter(), int64_t in_pGOCPlayerVisual, const char* in_pAnimationParameterName, float in_value);
FUNCTION_PTR(bool, __fastcall, fpPlayEffect, m_SigPlayEffect(), int64_t in_pSonicContext, const char* in_effectName);
FUNCTION_PTR(int64_t, __fastcall, fpStopEffects, m_SigStopEffects(), int64_t in_pSonicContext);
FUNCTION_PTR(int*, __fastcall, fpPlaySound, m_SigPlaySound(), int64_t in_pGOCSound, int* a2, const char* in_soundName, float a4);
FUNCTION_PTR(void, __fastcall, fpStopSound, READ_CALL(m_SigStopSoundCaller()), int* in_pSoundHandle);
FUNCTION_PTR(int64_t, __fastcall, fpGetFxParamBulletTimeExtension, READ_CALL(m_SigGetFxParamBulletTimeExtensionCaller()), int64_t in_pFxParamManager);
FUNCTION_PTR(int64_t, __fastcall, fpGetStatePluginCollision, m_SigGetStatePluginCollision(), int64_t in_pSonicContext);
FUNCTION_PTR(void, __fastcall, fpTogglePlayerEntityCollision, m_SigTogglePlayerEntityCollision(), int64_t in_pSonicContext, bool in_enabled);
FUNCTION_PTR(int64_t, __fastcall, fpSetCollisionSphere, m_SigSetCollisionSphere(), int64_t in_pStatePluginCollision, uint8_t in_type, float in_radius);
FUNCTION_PTR(int64_t, __fastcall, fpStartBulletTime, m_SigStartBulletTime(), int64_t in_pFxParamBulletTimeExtension, float in_fadeInTime);
FUNCTION_PTR(void, __fastcall, fpEndBulletTime, m_SigEndBulletTime(), int64_t in_pFxParamBulletTimeExtension, float in_fadeOutTime);
FUNCTION_PTR(int64_t, __fastcall, fpStartSpinChargeCamera, m_SigStartSpinChargeCamera(), int64_t in_pStatePluginCamera, const char* in_pCameraName);
FUNCTION_PTR(int64_t, __fastcall, fpSendMessageToGameObject, READ_CALL(m_SigSendMessageToGameObjectCaller()), hh::game::GameObject* in_pGameObject, hh::fnd::Message& in_Message);
FUNCTION_PTR(int64_t, __fastcall, fpGetPlugin, m_SigGetPlugin(), int64_t a1, int in_pluginNameHash);

bool SetCurrentState(int64_t in_pSonicContext, EStateID in_stateId)
{
	return fpSetCurrentState(*(int64_t*)(in_pSonicContext + 56), in_stateId, 0);
}

void PlayAnimation(const char* in_pAnimationName)
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return;

	auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

	if (!pSonic)
		return;

	return fpPlayAnimation((int64_t)(pSonic->GetComponent("GOCPlayerVisual")), in_pAnimationName, 0xFE);
}

double SetAnimationParameter(const char* in_pAnimationParameterName, float in_value)
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return 0.0;

	auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

	if (!pSonic)
		return 0.0;

	return fpSetAnimationParameter((int64_t)(pSonic->GetComponent("GOCPlayerVisual")), in_pAnimationParameterName, in_value);
}

void SetHitSphere(int64_t in_pSonicContext, bool in_enabled)
{
	fpSetCollisionSphere(fpGetStatePluginCollision(in_pSonicContext), in_enabled ? ECollisionType_Hit : ECollisionType_Default, 1.0f);
	fpTogglePlayerEntityCollision(in_pSonicContext, !in_enabled);
}

int* PlaySound(const char* in_pSoundName)
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return 0;

	auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

	if (!pSonic)
		return 0;

	int zero = 0; // no idea what this is lol

	return fpPlaySound((int64_t)(pSonic->GetComponent("GOCSound")), &zero, in_pSoundName, 0.0f);
}

bool IsGrounded()
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return false;

	auto* pLevelInfo = pGameDocument->GetService<app::level::LevelInfo>();

	if (!pLevelInfo)
		return false;

	return pLevelInfo->playerInfos[0]->IsGrounded;
}

void SetTimeScale(float in_timeScale)
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return;

	auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

	if (!pSonic)
		return;

	app::game::MsgChangeLayerTimeScale msg { "ninja", in_timeScale, 0x30002F0, 0.0f };

	fpSendMessageToGameObject(pSonic, msg);
}

void ToggleBulletTime(int64_t in_pSonicContext, bool in_isEnabled, float in_timeScale = 0.125f, float in_fadeTime = 0.25f)
{
	auto* pGameDocument = app::GameDocument::GetSingleton();

	if (!pGameDocument)
		return;

	auto pFxParamManager = pGameDocument->GetService("FxParamManager");

	if (!pFxParamManager)
		return;

	int64_t pFxParamBulletTimeExtension = fpGetFxParamBulletTimeExtension((int64_t)pFxParamManager);

	if (!pFxParamBulletTimeExtension)
		return;

	if (in_isEnabled)
	{
		SetTimeScale(in_timeScale);

		if (Configuration::IsFocusDashVFX)
			fpStartBulletTime(pFxParamBulletTimeExtension, in_fadeTime);

		if (Configuration::IsFocusDashSE)
			m_FocusDashSoundHandle = *PlaySound("miniboss_blade01_time_stop");
	}
	else
	{
		SetTimeScale(1.0f);

		if (Configuration::IsFocusDashVFX)
			fpEndBulletTime(pFxParamBulletTimeExtension, in_fadeTime);

		if (Configuration::IsFocusDashSE)
			fpStopSound(&m_FocusDashSoundHandle);
	}
}

void StartSpinChargeCamera(int64_t in_pSonicContext)
{
	auto pStatePluginManager = *(int64_t*)(*(int64_t*)(in_pSonicContext + 0x38) + 0x108);

	if (!pStatePluginManager)
		return;

	auto pStatePluginCamera = fpGetPlugin(pStatePluginManager, 0x2EBFB349);

	if (!pStatePluginCamera)
		return;

	fpStartSpinChargeCamera(pStatePluginCamera, "SpinBoostCharge");
}

bool CanConsumeBoost()
{
	return !m_IsInfiniteBoostGaugeCode && m_Boost != nullptr && m_InfiniteBoostTime != nullptr && *m_InfiniteBoostTime <= 0.0f;
}

bool IsNormalDropDash()
{
	return m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsSlideDash) &&
		!m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash);
}

bool IsGroundDropDash()
{
	return m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash) &&
		!m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) &&
		!m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash);
}

bool IsNoCameraDelay()
{
	return Configuration::IsDropDashNoCameraDelay && IsNormalDropDash() ||
		Configuration::IsAirDashNoCameraDelay && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) ||
		Configuration::IsSlideDashNoDropDashCameraDelay && m_DropDashStateFlags.test(EDropDashStateFlags_IsSlideDash) ||
		Configuration::IsSpinDashNoDropDashCameraDelay && m_PersistentStateFlags.test(EPersistentStateFlags_IsSpinChargeRelease) ||
		Configuration::IsQuickStompDashNoCameraDelay && m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash);
}

bool IsMoveAvailable(Configuration::EWorldType in_worldType)
{
	return (BlackboardHelper::IsCyberSpace()
		? (in_worldType == Configuration::EWorldType_Both || in_worldType == Configuration::EWorldType_CyberOnly)
		: (in_worldType == Configuration::EWorldType_Both || in_worldType == Configuration::EWorldType_IslandOnly));
}

bool IsCyberSpaceOrSideView()
{
	return BlackboardHelper::IsCyberSpace() || BlackboardHelper::IsSideView();
}

bool IsImmediateExit()
{
	if (IsCyberSpaceOrSideView())
		return false;

	return (Configuration::AirDashUncurlType == Configuration::ECommonUncurlType_Immediate && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash)) ||
		(Configuration::QuickStompDashUncurlType == Configuration::ECommonUncurlType_Immediate && m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash));
}

bool IsUngroundedExit(bool in_configValue)
{
	if (IsCyberSpaceOrSideView())
		return false;

	return in_configValue;
}

bool IsGroundedExit()
{
	return (Configuration::AirDashUncurlType == Configuration::ECommonUncurlType_Grounded && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) ||
		Configuration::QuickStompDashUncurlType == Configuration::ECommonUncurlType_Grounded && m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash));
}

void BufferInputFlags()
{
	m_InputFlags.set(EInputFlags_IsJumpInputBuffered, InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A));
	m_InputFlags.set(EInputFlags_IsUncurlInputBuffered, InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B));
	m_InputFlags.set(EInputFlags_IsLeftTriggerBuffered, InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) > TRIGGER_THRESHOLD);
	m_InputFlags.set(EInputFlags_IsRightTriggerBuffered, InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD);
}

void UnbufferInputFlags()
{
	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
		m_InputFlags.reset(EInputFlags_IsJumpInputBuffered);

	if (!InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
		m_InputFlags.reset(EInputFlags_IsUncurlInputBuffered);

	if (InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) < TRIGGER_THRESHOLD)
		m_InputFlags.reset(EInputFlags_IsLeftTriggerBuffered);

	if (InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) < TRIGGER_THRESHOLD)
		m_InputFlags.reset(EInputFlags_IsRightTriggerBuffered);
}

HOOK(int64_t, __fastcall, StateDropDashStart, m_SigStateDropDashStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	m_DropDashStateFlags.set(EDropDashStateFlags_IsDropDash);

	BufferInputFlags();

	if (IsNoCameraDelay())
	{
		if (m_SigDropDashCameraDelay() != nullptr)
			WRITE_MEMORY(m_SigDropDashCameraDelay(), uint8_t, 0xEB);
	}

	return originalStateDropDashStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateDropDashUpdate, m_SigStateDropDashUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = SONIC_CONTEXT_IS_GROUNDED(in_pSonicContext);

	UnbufferInputFlags();

	m_PersistentStateFlags.set(EPersistentStateFlags_IsAirDashExitRecovery, m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash));

	// Exit StateDropDash into StateSpinBoostCharge whilst LT is held.
	if (!m_InputFlags.test(EInputFlags_IsLeftTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) > TRIGGER_THRESHOLD)
	{
		SetCurrentState(in_pSonicContext, EStateID_StateSpinBoostCharge);
		return true;
	}

	// Exit StateDropDash into StateRecovery immediately (if enabled).
	if (IsImmediateExit())
	{
		SetCurrentState(in_pSonicContext, EStateID_StateRecovery);
		return true;
	}

	/* Set flag if we've been grounded at least once. This'll be used
	   for other conditions later that we must check when grounded. */
	if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsGroundedOnce))
		m_DropDashStateFlags.set(EDropDashStateFlags_IsGroundedOnce, isGrounded);

	if (isGrounded)
	{
		// Exit StateDropDash into StateRun when grounded (if enabled) or whilst RT is held.
		if (IsGroundedExit() || (!m_InputFlags.test(EInputFlags_IsRightTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD))
		{
			BlackboardHelper::GetStatus()->StateFlags |= BlackboardHelper::EStateFlags::EStateFlags_IsBoost;

			SetCurrentState(in_pSonicContext, EStateID_StateRun);

			return true;
		}
	}
	else
	{
		// Set double jump flag for when we enter the fall state later after cancelling Air Dash.
		if (!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
		{
			m_PersistentStateFlags.set(EPersistentStateFlags_IsAirDashExitDoubleJump);
		}

		// Exit StateDropDash into StateRecovery when ungrounded (if enabled).
		if (IsUngroundedExit(Configuration::IsDropDashCancelWhenUngrounded) && m_DropDashStateFlags.test(EDropDashStateFlags_IsGroundedOnce))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateRecovery);
			return true;
		}

		// Exit StateDropDash into StateAirBoost whilst RT is held when airborne.
		if (Configuration::IsDropDashAirBoostCancel && (!m_InputFlags.test(EInputFlags_IsRightTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateAirBoost);
			return true;
		}

		// Exit StateDropDash into StateStomping.
		if (Configuration::IsDropDashStompCancel && (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B)))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateStomping);
			return true;
		}
	}

	// Exit StateDropDash into StateQuickStep.
	if (Configuration::IsDropDashQuickStepCancel && (InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_LEFT_SHOULDER) || InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)))
	{
		SetCurrentState(in_pSonicContext, EStateID_StateQuickStep);
		return true;
	}

	// Exit StateDropDash into either StateRun or StateFall whilst B or A are held.
	if (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B) ||
		!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A))
	{
		SetCurrentState(in_pSonicContext, isGrounded ? EStateID_StateRun : EStateID_StateFall);
		return true;
	}

	return originalStateDropDashUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, StateDropDashExit, m_SigStateDropDashExit(), int64_t in_pThis, int64_t in_pSonicContext)
{
	m_DropDashStateFlags.reset();
	m_SpinChargeReleaseVelocity = 0.0f;

	if (m_SigDropDashCameraDelay() != nullptr)
		RESTORE_MEMORY((uint64_t)m_SigDropDashCameraDelay());

	return originalStateDropDashExit(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, PostureDropDashUpdate, m_SigPostureDropDashUpdate(), int64_t in_pThis, double in_deltaTime)
{
	if (Configuration::IsDropDashSideViewRollFix && m_SigFixDropDashSideView() != nullptr)
	{
		if (BlackboardHelper::IsSideView())
		{
			WRITE_MEMORY(m_SigFixDropDashSideView(), uint8_t, 0xEB);
		}
		else
		{
			RESTORE_MEMORY((uint64_t)m_SigFixDropDashSideView());
		}
	}

	return originalPostureDropDashUpdate(in_pThis, in_deltaTime);
}

HOOK(int64_t, __fastcall, StartSpinChargeCameraStart, m_SigStartSpinChargeCamera(), int64_t in_pStatePluginCamera, const char* in_pCameraName)
{
	originalStartSpinChargeCameraStart(in_pStatePluginCamera, in_pCameraName);

	auto pPlayerCameraParameter = *(int64_t*)(in_pStatePluginCamera + 0x28);
	auto pLocalEyeOffset = (Vector3*)(pPlayerCameraParameter + 0x60);

	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge))
	{
		pLocalEyeOffset->Z = 4.75f;
	}
	else
	{
		pLocalEyeOffset->Z = 3.5f;
	}

	return originalStartSpinChargeCameraStart(in_pStatePluginCamera, in_pCameraName);
}

HOOK(int64_t, __fastcall, StateSpinBoostChargeStart, m_SigStateSpinBoostChargeStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = SONIC_CONTEXT_IS_GROUNDED(in_pSonicContext);

	BufferInputFlags();

	if (isGrounded)
	{
		if (Configuration::IsSpinDashEnhancedIslandPhysics)
			RFL_GET_PARAM(forwardView.spinBoost.chargeRotateForce) = 100.0f;

		if (Configuration::SpinChargeCameraShakeType != -1 && Configuration::SpinChargeCameraShakeType <= 3)
			RFL_GET_CONTEXTUAL_PARAM(spinBoost.cameraShakeName.value) = Configuration::CameraShakeNames[Configuration::SpinChargeCameraShakeType].c_str();
	}
	else
	{
		if (!m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge))
		{
			if (Configuration::IsSpinChargeNoAirCamera)
			{
				RFL_GET_CONTEXTUAL_PARAM(spinBoost.chargeRotateForce) = 500.0f;
				RFL_GET_CONTEXTUAL_PARAM(spinBoost.cameraShakeName.value) = "";

				goto Exit;
			}
		}
	}

	/* Start the normal Spin Charge camera if the
	   "Disable Spin Charge Camera" code isn't on. */
	if (!IS_NOP(m_SigDisableSpinChargeCameraCode()))
		StartSpinChargeCamera(in_pSonicContext);

Exit:
	return originalStateSpinBoostChargeStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateSpinBoostChargeUpdate, m_SigStateSpinBoostChargeUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = SONIC_CONTEXT_IS_GROUNDED(in_pSonicContext);

	UnbufferInputFlags();

	// Begin Focus Dash.
	if (Configuration::IsFocusDash && IsMoveAvailable(Configuration::FocusDashWorldType) &&
		!m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge) &&
		!isGrounded && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_LEFT_THUMB))
	{
		m_PersistentStateFlags.set(EPersistentStateFlags_IsFocusDashCharge);

		ToggleBulletTime(in_pSonicContext, true);
		StartSpinChargeCamera(in_pSonicContext);
	}

	FUNCTION_PTR(bool, __fastcall, fpCheckInput, m_SigCheckInput(), int64_t in_pSonicContext, int a2);
	{
		if (fpCheckInput(in_pSonicContext, 14))
		{
			// Add to the multiplier every time the Spin Dash is charged.
			m_SpinChargeMultiplier += Configuration::SpinChargeMultiplier;
		}
	}

	// Exit StateSpinBoostCharge into StateRecovery if we're out of boost when charging a Focus Dash.
	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge) && m_Boost != nullptr && *m_Boost < 0.0f)
	{
		SetCurrentState(in_pSonicContext, EStateID_StateRecovery);
		return true;
	}

	// Exit StateSpinBoostCharge into StateSpinBoost whilst RT is held.
	if (!m_InputFlags.test(EInputFlags_IsRightTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		SetCurrentState(in_pSonicContext, EStateID_StateSpinBoost);
		return true;
	}

	return originalStateSpinBoostChargeUpdate(in_pThis, in_pSonicContext);
}

HOOK(int64_t, __fastcall, StateSpinBoostChargeExit, m_SigStateSpinBoostChargeExit(), int64_t in_pThis, int64_t in_pSonicContext, int64_t a3)
{
	// Reset Focus Dash data.
	{
		ToggleBulletTime(in_pSonicContext, false);

		m_PersistentStateFlags.reset(EPersistentStateFlags_IsFocusDashForwardRestored);

		if (m_SigDisableSpinChargeMovement() != nullptr)
			RESTORE_MEMORY((int64_t)m_SigDisableSpinChargeMovement());

		if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDash))
		{
			float minConsume = Configuration::FocusDashMinPitchBoostConsumption;
			float maxConsume = Configuration::FocusDashMaxPitchBoostConsumption;

			// Subtract boost upon release, amount depending on Sonic's pitch direction.
			if (minConsume < maxConsume && CanConsumeBoost())
				*m_Boost -= RANGE(m_FocusDashPitchScale, -1.0f, 1.0f, minConsume, maxConsume);
		}

		m_FocusDashYawScale = 0.0f;
		m_FocusDashPitchScale = 0.0f;
	}

	return originalStateSpinBoostChargeExit(in_pThis, in_pSonicContext, a3);
}

HOOK(int64_t, __fastcall, StateSpinBoostStart, m_SigStateSpinBoostStart(), int64_t in_pThis, int64_t in_pSonicContext, int64_t a3)
{
	BufferInputFlags();

	return originalStateSpinBoostStart(in_pThis, in_pSonicContext, a3);
}

HOOK(bool, __fastcall, StateSpinBoostUpdate, m_SigStateSpinBoostUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = SONIC_CONTEXT_IS_GROUNDED(in_pSonicContext);

	UnbufferInputFlags();

	// Allow exiting StateSpinBoost into StateDoubleJump when ungrounded.
	if (!m_PersistentStateFlags.test(EPersistentStateFlags_IsDoubleJumpFromSpinBoost) && !isGrounded &&
		(!m_InputFlags.test(EInputFlags_IsJumpInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_A)))
	{
		m_PersistentStateFlags.set(EPersistentStateFlags_IsDoubleJumpFromSpinBoost);

		SetCurrentState(in_pSonicContext, EStateID_StateDoubleJump);
		
		return true;
	}

	if (Configuration::SpinDashSlideActionType != Configuration::ESpinDashSlideActionType_None &&
		(!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B)))
	{
		auto exitState = (isGrounded ? EStateID_StateRun : EStateID_StateFall);

		switch (Configuration::SpinDashSlideActionType)
		{
			case Configuration::ESpinDashSlideActionType_Slide:
				exitState = (isGrounded ? EStateID_StateSliding : EStateID_StateFall);
				break;

			case Configuration::ESpinDashSlideActionType_SpinCharge:
				exitState = EStateID_StateSpinBoostCharge;
				break;

			case Configuration::ESpinDashSlideActionType_DropDash:
				exitState = EStateID_StateDropDash;
				break;
		}

		if (Configuration::IsSpinDashStompCancel && !isGrounded)
			exitState = EStateID_StateStomping;
		
		SetCurrentState(in_pSonicContext, exitState);

		if (!isGrounded)
			PlayAnimation("FALL");

		return true;
	}

	return originalStateSpinBoostUpdate(in_pThis, in_pSonicContext);
}

HOOK(double, __fastcall, StateSpinBoostExit, 0x1408A6810, int64_t in_pThis, int64_t in_pSonicContext, int a3)
{
	m_SpinChargeReleaseVelocity = 0.0f;

	return originalStateSpinBoostExit(in_pThis, in_pSonicContext, a3);
}

HOOK(int64_t, __fastcall, StateSpinMoveStart, m_SigStateSpinMoveStart(), int64_t in_pThis, int64_t in_pSonicContext)
{
	BufferInputFlags();

	return originalStateSpinMoveStart(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateSpinMoveUpdate, m_SigStateSpinMoveUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isGrounded = SONIC_CONTEXT_IS_GROUNDED(in_pSonicContext);
	bool isSideView = BlackboardHelper::IsSideView();

	float initialSpeed = RFL_GET_CONTEXTUAL_PARAM(spinBoost.speedBall.initialSpeed);
	float maxSpeed = RFL_GET_CONTEXTUAL_PARAM(spinBoost.speedBall.maxSpeed);

	// Exit StateSpinMove into either StateRun or StateFall if LT was buffered and released.
	if (m_InputFlags.test(EInputFlags_IsLeftTriggerBuffered) &&
		InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) < TRIGGER_THRESHOLD)
	{
		SetCurrentState(in_pSonicContext, isGrounded ? EStateID_StateRun : EStateID_StateFall);
		return true;
	}

	UnbufferInputFlags();

	// Set speed of rolling animation to match Sonic's speed.
	SetAnimationParameter("SPEED", min(max(m_Velocity / (initialSpeed - 5.0f), 0.0f), 1.0f));

	// Exit StateSpinMove to StateSpinBoost when exceeding terminal velocity.
	{
		auto type = Configuration::SpinMoveTerminalVelocityType;

		if (m_Velocity >= maxSpeed + 5.0f)
		{
			if ((type == Configuration::ESpinMoveTerminalVelocityType_SpinDash) ||
				(type == Configuration::ESpinMoveTerminalVelocityType_SpinDashSV && isSideView) ||
				(type == Configuration::ESpinMoveTerminalVelocityType_SpinDashFV && !isSideView))
			{
				SetCurrentState(in_pSonicContext, EStateID_StateSpinBoost);
				return true;
			}
		}
	}

	if (Configuration::SpinMoveEffectsType != Configuration::ESpinMoveEffectsType_Disabled)
	{
		if (Configuration::SpinMoveEffectsType == Configuration::ESpinMoveEffectsType_Always ||
			!isGrounded || m_HorizontalVelocity >= (initialSpeed + 5.0f))
		{
			SetHitSphere(in_pSonicContext, true);
			fpPlayEffect(in_pSonicContext, "SPIN");
		}
		else if (Configuration::SpinMoveEffectsType == Configuration::ESpinMoveEffectsType_VelocityBased)
		{
			SetHitSphere(in_pSonicContext, false);
			fpStopEffects(in_pSonicContext);
		}
	}

	if (isGrounded)
	{
		// Expire state when reaching minimum rotation and velocity.
		{
			float dot = Vector3::Dot(m_Rotation * Vector3::Up(), Vector3::Up());

			if (dot < 0.05f && m_Velocity < std::lerp(9.0f, 15.0f, -std::clamp(dot, -1.0f, 0.0f)))
			{
				SetCurrentState(in_pSonicContext, EStateID_StateFall);
				return true;
			}
		}

		// Exit StateSpinMove into StateRun whilst RT is held.
		if (!m_InputFlags.test(EInputFlags_IsRightTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
		{
			BlackboardHelper::GetStatus()->StateFlags |= BlackboardHelper::EStateFlags::EStateFlags_IsBoost;

			SetCurrentState(in_pSonicContext, EStateID_StateRun);

			return true;
		}
	}
	else
	{
		// Exit StateSpinMove into StateRecovery when ungrounded (if enabled).
		if (IsUngroundedExit(Configuration::IsSpinMoveCancelWhenUngrounded))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateRecovery);
			return true;
		}

		// Exit StateSpinMove into StateAirBoost whilst RT is held when airborne.
		if (Configuration::IsSpinMoveAirBoostCancel && (!m_InputFlags.test(EInputFlags_IsRightTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateAirBoost);
			return true;
		}

		// Exit StateSpinMove into StateStomping.
		if (Configuration::IsSpinMoveStompCancel && (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B)))
		{
			SetCurrentState(in_pSonicContext, EStateID_StateStomping);
			return true;
		}
	}

	// Exit StateSpinMove into StateSpinBoostCharge whilst LT is held.
	if (!m_InputFlags.test(EInputFlags_IsLeftTriggerBuffered) && InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) > TRIGGER_THRESHOLD)
	{
		SetCurrentState(in_pSonicContext, EStateID_StateSpinBoostCharge);
		return true;
	}

	// Exit StateSpinMove into either StateRun or StateFall whilst B is held.
	if (!m_InputFlags.test(EInputFlags_IsUncurlInputBuffered) && InputHelper::Instance->GetInputDown(XINPUT_GAMEPAD_B))
	{
		SetCurrentState(in_pSonicContext, isGrounded ? EStateID_StateRun : EStateID_StateFall);
		return true;
	}

	return originalStateSpinMoveUpdate(in_pThis, in_pSonicContext);
}

HOOK(double, __fastcall, StateSpinMoveExit, m_SigStateSpinMoveExit(), int64_t in_pThis, int64_t in_pSonicContext, int a3)
{
	SetHitSphere(in_pSonicContext, false);
	fpStopEffects(in_pSonicContext);

	return originalStateSpinMoveExit(in_pThis, in_pSonicContext, a3);
}

HOOK(int64_t, __fastcall, StatePluginAirTrickUpdate, m_SigStatePluginAirTrickUpdate(), int64_t in_pThis)
{
	int trickDirection = *(int*)(in_pThis + 0x34);

	float minReward = Configuration::AirTrickMinBoostReward;
	float maxReward = Configuration::AirTrickMaxBoostReward;
	float fatigueTime = Configuration::AirTrickFatigueTime;

	// Begins fatigue once at least one trick has been performed.
	m_PersistentStateFlags.set(EPersistentStateFlags_IsAirTrickFatigueBegin);

	if (minReward < maxReward)
	{
		m_TrickReward = std::clamp
		(
			m_TrickReward + (trickDirection == m_LastTrickDirection
				? -Configuration::AirTrickSamePenalty
				: minReward),

			minReward,

			fatigueTime == 0.0f
				? maxReward // Always reward maximum amount if the fatigue time is zero in the configuration.
				: std::clamp(RANGE(m_TrickBoostFatigue, 0.0f, fatigueTime, maxReward, minReward), minReward, maxReward)
		);
	}
	else
	{
		m_TrickReward = 0.0f;
	}

	m_LastTrickDirection = trickDirection;

	if (Configuration::IsAirTricksEnhanced)
		*m_Boost = std::clamp(*m_Boost + m_TrickReward, 0.0f, *m_BoostMax);

	return originalStatePluginAirTrickUpdate(in_pThis);
}

HOOK(int64_t, __fastcall, StatePluginBoostUpdate, m_SigStatePluginBoostUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	m_Boost = (float*)(in_pThis + 0x3C);
	m_BoostMax = (float*)(in_pThis + 0x38);
	m_InfiniteBoostTime = (float*)(in_pThis + 0x54);
	m_CanBoost = (*(int32_t*)(in_pThis + 0x80) & 8) != 8;
	m_IsInfiniteBoostGaugeCode = IS_NOP(m_SigInfiniteBoostGaugeCode());

	// Allow Focus Dash again after reaching 100% boost from tricks.
	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDash) && *m_Boost >= 100.0f)
		*(int32_t*)(in_pThis + 0x80) = 0;

	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge) && CanConsumeBoost())
		*m_Boost -= (Configuration::FocusDashActiveBoostConsumption * 100.0f) * in_deltaTime;

	return originalStatePluginBoostUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StatePluginBoostRechargeMode, m_SigStatePluginBoostRechargeMode(), int64_t in_pThis)
{
	// Disable automatic boost gauge replenishment for Focus Dash.
	if (Configuration::IsFocusDashNoBoostReplenishment &&
		m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDash))
	{
		return false;
	}

	return originalStatePluginBoostRechargeMode(in_pThis);
}

HOOK(bool, __fastcall, CommonStateFallExit, m_SigCommonStateFallExit(), int64_t a1, char a2)
{
	// Allow StateSpinMove and StateSpinBoost to climb slippery slopes.
	if (m_LastStateID == EStateID_StateSpinMove || m_LastStateID == EStateID_StateSpinBoost)
		return false;

	return originalCommonStateFallExit(a1, a2);
}

HOOK(bool, __fastcall, StateSquatUpdate, m_SigStateSquatUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	bool isSideView = BlackboardHelper::IsSideView();

	if ((isSideView && Configuration::SlideDashActionTypeSV == Configuration::ESlideDashActionType_DropDash) ||
		(!isSideView && Configuration::SlideDashActionType == Configuration::ESlideDashActionType_DropDash))
	{
		WRITE_MEMORY(m_SigPreventSquatToSlide(), uint8_t, 0xEB);
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigPreventSquatToSlide());
	}

	return originalStateSquatUpdate(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateFallSlopeUpdate, m_SigStateFallSlopeUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	// Exit StateFallSlope into StateSpinBoostCharge.
	if (!m_InputFlags.test(EInputFlags_IsLeftTriggerBuffered) &&
		InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) > TRIGGER_THRESHOLD && m_CanBoost)
	{
		SetCurrentState(in_pSonicContext, EStateID_StateSpinBoostCharge);
		return true;
	}

	return originalStateFallSlopeUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateGrindJumpUpdate, m_SigStateGrindJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	// Exit StateGrindJump into StateSpinBoostCharge when holding LT.
	if (InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) > TRIGGER_THRESHOLD)
	{
		SetCurrentState(in_pSonicContext, EStateID_StateSpinBoostCharge);
		return true;
	}

	return originalStateGrindJumpUpdate(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateStompingDownUpdate, m_SigStateStompingDownUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	// Play rolling animation to flow better into the Spin Dash.
	if (InputHelper::Instance->GetTriggerInput(VK_PAD_LTRIGGER) > TRIGGER_THRESHOLD)
		PlayAnimation("JUMP_BALL");

	return originalStateStompingDownUpdate(in_pThis, in_pSonicContext);
}

HOOK(bool, __fastcall, StateDoubleJumpUpdate, m_SigStateDoubleJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	m_DropDashStateFlags.set(EDropDashStateFlags_IsDropDashCharge, *(float*)(in_pThis + 180) > 0.0f);

	return originalStateDoubleJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, StateRecoveryJumpUpdate, m_SigStateRecoveryJumpUpdate(), int64_t in_pThis, int64_t in_pSonicContext, float in_deltaTime)
{
	m_DropDashStateFlags.set(EDropDashStateFlags_IsDropDashCharge, *(bool*)(in_pThis + 196));

	// Always allow air boost exit for Air Dash.
	if (!m_PersistentStateFlags.test(EPersistentStateFlags_IsAirDashFromRecoveryJump) &&
		m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDashCharge) &&
		InputHelper::Instance->GetTriggerInput(VK_PAD_RTRIGGER) > TRIGGER_THRESHOLD)
	{
		m_PersistentStateFlags.set(EPersistentStateFlags_IsAirDashFromRecoveryJump);

		SetCurrentState(in_pSonicContext, EStateID_StateAirBoost);
	}

	return originalStateRecoveryJumpUpdate(in_pThis, in_pSonicContext, in_deltaTime);
}

HOOK(bool, __fastcall, SendMoveImpulse, m_SigSendMoveImpulse(), int64_t in_pSonicContext, int64_t in_pMessage)
{
	bool isDashPanel = *(char*)(in_pMessage + 0x98) & 1;

	if (isDashPanel && m_LastStateID == EStateID_StateSpinMove)
		SetCurrentState(in_pSonicContext, EStateID_StateSpinBoost);

	return originalSendMoveImpulse(in_pSonicContext, in_pMessage);
}

HOOK(bool, __fastcall, ObjFanProcessMessage, m_SigObjFanProcessMessage(), int64_t in_pThis, int64_t a2)
{
	// Disable fans if we're rolling.
	if (Configuration::IsDropDashNoFans && m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash))
		return 1;

	return originalObjFanProcessMessage(in_pThis, a2);
}

HOOK(void, __fastcall, GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), int64_t in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	Player::CreateInput();

	m_DeltaTime = *in_pDeltaTime;

	if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDash))
		m_DropDashDelayTime += m_DeltaTime;

	originalGOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

HOOK(char, __fastcall, GOCPlayerHsmGroundStateUpdate, m_SigGOCPlayerHsmGroundStateUpdate(), int64_t* in_pThis, EStateID in_stateId)
{
#if _DEBUG
	printf("[Enhanced Dash] [GOCPlayerHsmGroundStateUpdate] m_LastStateID: %d\n", m_LastStateID);
	printf("[Enhanced Dash] [GOCPlayerHsmGroundStateUpdate] in_stateId:    %d\n", in_stateId);
#endif

	switch (in_stateId)
	{
		case EStateID_StateFall:
		{
			/* I was debating changing this implementation to just switch
			   the state from StateDropDash itself, but doing that cancels
			   all horizontal velocity, so we're gonna keep it the old way. */
			if (m_PersistentStateFlags.test(EPersistentStateFlags_IsAirDashExitDoubleJump))
			{
				m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirDashExitDoubleJump);

				// Redirect StateFall to StateDoubleJump.
				in_stateId = EStateID_StateDoubleJump;
			}

			break;
		}

		case EStateID_StateAirBoost:
		{
			if (!Configuration::IsAirDash)
				break;

			if (!IsMoveAvailable(Configuration::AirDashWorldType))
				break;

			if (m_DropDashStateFlags.test(EDropDashStateFlags_IsDropDashCharge) && !m_PersistentStateFlags.test(EPersistentStateFlags_IsAirDashExitRecovery))
			{
				m_DropDashStateFlags.set(EDropDashStateFlags_IsAirDash);

				// Redirect StateAirBoost to StateDropDash.
				in_stateId = EStateID_StateDropDash;
			}

			break;
		}

		case EStateID_StateGrindDoubleJump:
		{
			if (m_SigForceGrindJumpPosture() != nullptr)
				WRITE_NOP(m_SigForceGrindJumpPosture(), 2);

			// Redirect StateGrindDoubleJump to StateDoubleJump.
			in_stateId = EStateID_StateDoubleJump;

			break;
		}

		case EStateID_StateStomping:
		{
			if (!Configuration::IsQuickStompDash)
				break;

			if (!IsMoveAvailable(Configuration::QuickStompDashWorldType))
				break;

			if (Configuration::IsQuickStompDashRequireAirBoost && !BlackboardHelper::IsAirBoosting())
				break;

			if ((m_LastStateID == EStateID_StateAirBoost &&
				m_PersistentStateFlags.test(EPersistentStateFlags_IsQuickStompDash)))
			{
				break;
			}

			if (m_LastStateID == EStateID_StateRecovery ||
				m_LastStateID == EStateID_StateRecoveryJump)
			{
				break;
			}

			bool isVelocityAboveThreshold = BlackboardHelper::IsSideView()
				? m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThresholdSV
				: m_HorizontalVelocity >= Configuration::QuickStompDashVelocityThreshold;

			if (Configuration::IsQuickStompDashRequireAirBoost || isVelocityAboveThreshold)
			{
				m_PersistentStateFlags.set(EPersistentStateFlags_IsQuickStompDash);

				// Redirect StateStomping to StateDropDash.
				in_stateId = EStateID_StateDropDash;
			}

			break;
		}

		case EStateID_StateSliding:
		{
			switch (BlackboardHelper::IsSideView()
				? Configuration::SlideDashActionTypeSV
				: Configuration::SlideDashActionType)
			{
				case Configuration::ESlideDashActionType_DropDash:
				{
					if (m_DropDashDelayTime < 0.1f)
						return 0;

					m_DropDashDelayTime = 0.0f;

					m_DropDashStateFlags.set(EDropDashStateFlags_IsSlideDash);

					// Redirect StateSliding to StateDropDash.
					in_stateId = EStateID_StateDropDash;

					break;
				}

				case Configuration::ESlideDashActionType_SpinMove:
				{
					// Redirect StateSliding to StateSpinMove.
					in_stateId = EStateID_StateSpinMove;

					break;
				}
			}

			break;
		}

		case EStateID_StateSpinBoost:
		{
			if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge))
			{
				m_PersistentStateFlags.set(EPersistentStateFlags_IsFocusDash);
				m_PersistentStateFlags.set(EPersistentStateFlags_IsFocusDashRelease);

				m_PersistentStateFlags.reset(EPersistentStateFlags_IsFocusDashCharge);
			}
			else
			{
				m_PersistentStateFlags.set(EPersistentStateFlags_IsSpinChargeRelease);

				if (Configuration::SpinDashReleaseActionType == Configuration::ESpinDashReleaseActionType_DropDash)
				{
					// Redirect StateSpinBoost to StateDropDash.
					in_stateId = EStateID_StateDropDash;
				}
			}

			break;
		}

		default:
		{
			if (m_SigForceGrindJumpPosture() != nullptr)
				RESTORE_MEMORY((uint64_t)m_SigForceGrindJumpPosture());

			break;
		}
	}

	if (in_stateId != EStateID_StateRecovery && in_stateId != EStateID_StateRecoveryJump)
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirDashExitRecovery);
	
	// Reset Quick Stomp Dash flag for Immediate exit.
	if (in_stateId == EStateID_StateRecovery || in_stateId == EStateID_StateRecoveryJump)
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsQuickStompDash);

	// Always reset these flags for other states.
	m_DropDashStateFlags.reset(EDropDashStateFlags_IsDropDashCharge);
	m_PersistentStateFlags.reset(EPersistentStateFlags_IsFocusDashCharge);

	m_LastStateID = in_stateId;

	return originalGOCPlayerHsmGroundStateUpdate(in_pThis, in_stateId);
}

#if 0
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmAirStateUpdate, "\x41\x56\x48\x83\xEC\x30\x0F\xB6\x81\x1C", "xxxxxxxxxx");

HOOK(char, __fastcall, GOCPlayerHsmAirStateUpdate, m_SigGOCPlayerHsmAirStateUpdate(), int64_t* in_pThis, int in_stateId)
{
#if _DEBUG
	printf("[Enhanced Dash] [GOCPlayerHsmAirStateUpdate] in_stateId: %d\n", in_stateId);
#endif

	return originalGOCPlayerHsmAirStateUpdate(in_pThis, in_stateId);
}
#endif

HOOK(uint8_t, __fastcall, PlayerKinematicsGroundUpdate, m_SigPlayerKinematicsGroundUpdate(), int64_t in_pPlayerPostureContext, int64_t in_pGOCPlayerKinematicParams, uint32_t& in_pFlags)
{
	auto pVelocity = (Vector3*)(in_pGOCPlayerKinematicParams + 0xD0);
	auto pRotation = (Quaternion*)(in_pGOCPlayerKinematicParams + 0x90);

	auto forward = pRotation == nullptr
		? Vector3::Zero()
		: Quaternion::Forward(*pRotation);

	if (pVelocity == nullptr || pRotation == nullptr)
		goto Exit;

	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsSpinChargeRelease))
	{
		float initialVelocity = BlackboardHelper::IsSideView()
			? Configuration::SpinChargeInitialReleaseVelocitySV
			: Configuration::SpinChargeInitialReleaseVelocity;

		m_SpinChargeReleaseVelocity = std::clamp(initialVelocity * m_SpinChargeMultiplier, 0.0f, Configuration::SpinChargeTerminalReleaseVelocity);

		m_PersistentStateFlags.reset(EPersistentStateFlags_IsSpinChargeRelease);
	}

	if (m_SpinChargeReleaseVelocity > 0.0f)
	{
		m_SpinChargeMultiplier = 0.0f;
		m_SpinChargeReleaseVelocity -= Configuration::SpinChargeVelocityDecayRate * m_DeltaTime;

		*pVelocity += forward * m_SpinChargeReleaseVelocity;
	}

	m_Rotation = *pRotation;

Exit:
	return originalPlayerKinematicsGroundUpdate(in_pPlayerPostureContext, in_pGOCPlayerKinematicParams, in_pFlags);
}

HOOK(int64_t, __fastcall, PlayerKinematicsAirUpdate, READ_CALL(m_SigPlayerKinematicsAirUpdateCaller()), int64_t in_pThis, int64_t in_pGOCPlayerKinematicParams)
{
	auto pVelocity = (Vector3*)(in_pGOCPlayerKinematicParams + 0xD0);
	auto pRotation = (Quaternion*)(in_pGOCPlayerKinematicParams + 0x90);

	auto forward = pRotation == nullptr
		? Vector3::Zero()
		: Quaternion::Forward(*pRotation);

	if (pVelocity == nullptr || pRotation == nullptr)
		goto Exit;

	if (IsGrounded() || BlackboardHelper::IsGrinding() || BlackboardHelper::IsWallClimbing())
	{
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirDashFromRecoveryJump);
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsAirTrickFatigueBegin);
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsDoubleJumpFromSpinBoost);
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsFocusDash);
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsQuickStompDash);

		m_TrickBoostFatigue = 0.0f;
	}
	else
	{
		if (m_PersistentStateFlags.test(EPersistentStateFlags_IsAirTrickFatigueBegin))
			m_TrickBoostFatigue += m_DeltaTime;
	}

	if (!m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDashRelease) && m_DropDashStateFlags.test(EDropDashStateFlags_IsAirDash))
	{
		m_DropDashStateFlags.set(EDropDashStateFlags_IsAirDashRelease);

		*pVelocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::AirDashInitialVelocitySV
			: Configuration::AirDashInitialVelocity);
	}

	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashCharge))
	{
		float normAnalogX = (float)InputHelper::Instance->GetAnalogInput
		(
			Configuration::FocusDashCameraStickType == Configuration::EFocusDashCameraStickType_Left
				? VK_PAD_LTHUMB_LEFT
				: VK_PAD_RTHUMB_LEFT
		)
		/ 32767.0f;

		float normAnalogY = (float)InputHelper::Instance->GetAnalogInput
		(
			Configuration::FocusDashCameraStickType == Configuration::EFocusDashCameraStickType_Left
				? VK_PAD_LTHUMB_UP
				: VK_PAD_RTHUMB_UP
		)
		/ 32767.0f;

		float normAnalogDirX = (normAnalogX > 0.0f ? 1.0f : -1.0f);
		float normAnalogDirY = (normAnalogY > 0.0f ? 1.0f : -1.0f);

		Quaternion yaw;
		Quaternion pitch;

		// Yaw
		{
			float yawSpeed = Configuration::FocusDashYawSensitivity;
			float yawAcceleration = (abs(normAnalogX) * yawSpeed) * m_DeltaTime;

			// Disable the original movement implementation to reduce updates to yaw rotation that cause stutter.
			if (m_SigDisableSpinChargeMovement() != nullptr)
			{
				READ_JUMP(DisableSpinChargeMovement, (int64_t)m_SigDisableSpinChargeMovement());
				WRITE_JUMP((int64_t)m_SigDisableSpinChargeMovement(), DisableSpinChargeMovement);
			}

			m_FocusDashYawScale += yawAcceleration * normAnalogDirX;

			if (!m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashForwardRestored))
			{
				m_PersistentStateFlags.set(EPersistentStateFlags_IsFocusDashForwardRestored);
				m_FocusDashForward = forward;
			}

			yaw = Quaternion::LookRotation(Vector3::Normalized(m_FocusDashForward)) * (BlackboardHelper::IsSideView()
				? Quaternion::Identity() // Lock yaw to forward vector in side view to prevent left/right movement.
				: Quaternion::FromAngleAxis(-m_FocusDashYawScale, Vector3(0.0f, 1.0f, 0.0f)));
		}

		// Pitch
		{
			float pitchSpeed = Configuration::FocusDashPitchSensitivity;
			float pitchAcceleration = (abs(normAnalogY) * pitchSpeed) * m_DeltaTime;
			float pitchMaxAngle = 75.0f;

			// Disable pitch resetting to neutral to allow for smoother pitch rotation.
			WRITE_NOP(m_SigDisableSpinChargePitchReset(), 5);

			m_FocusDashPitchScale = std::clamp(m_FocusDashPitchScale + (pitchAcceleration * normAnalogDirY), -1.0f, 1.0f);

			pitch = Quaternion::FromAngleAxis(-m_FocusDashPitchScale * (pitchMaxAngle * DEG2RADf), Vector3(1.0f, 0.0f, 0.0f));
		}

		*pRotation = Quaternion::Identity() * yaw * pitch;
	}
	else
	{
		RESTORE_MEMORY((int64_t)m_SigDisableSpinChargePitchReset());
	}

	if (m_PersistentStateFlags.test(EPersistentStateFlags_IsFocusDashRelease))
	{
		m_PersistentStateFlags.reset(EPersistentStateFlags_IsFocusDashRelease);

		*pVelocity += forward * (BlackboardHelper::IsSideView()
			? Configuration::FocusDashInitialVelocitySV
			: Configuration::FocusDashInitialVelocity);
	}

	m_Velocity = Vector3::Magnitude(*pVelocity);
	m_HorizontalVelocity = Vector3::Magnitude(Vector3::ProjectOnPlane(*pVelocity, *pRotation * Vector3(0.0f, 1.0f, 0.0f)));

#if _DEBUG
	// printf("[Enhanced Dash] m_HorizontalVelocity: %f\n", m_HorizontalVelocity);
#endif

Exit:
	return originalPlayerKinematicsAirUpdate(in_pThis, in_pGOCPlayerKinematicParams);
}

void Player::Install()
{
	FrontiersInput::Install();

	// Kill original Spin Charge camera implementation, so we can toggle it ourselves.
	WRITE_MEMORY(m_SigDisableSpinChargeCamera(), uint8_t, 0xEB);

	// Stop StateSpinMove exiting into StateSpinBoostCharge.
	WRITE_NOP(m_SigDisableSpinChargeFromSpinMove(), 13);

	// Stop StateSpinMove exiting if not holding LT.
	WRITE_MEMORY(m_SigDisableSpinMoveExitInput(), uint8_t, 0xEB, 0x5C);

	// Stop StateSpinMove exiting to StateSpinBoost if holding RT.
	WRITE_MEMORY(m_SigDisableSpinBoostFromSpinMove(), uint8_t, 0xEB);

	PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargeMovement(), 6);
	PRESERVE_MEMORY((int64_t)m_SigDisableSpinChargePitchReset(), 5);
	PRESERVE_MEMORY((int64_t)m_SigDropDashCameraDelay(), 1);
	PRESERVE_MEMORY((int64_t)m_SigForceGrindJumpPosture(), 2);
	PRESERVE_MEMORY((int64_t)m_SigFixDropDashSideView(), 1);
	PRESERVE_MEMORY((int64_t)m_SigPreventSquatToSlide(), 1);

	if (m_SigCanRecoveryJump() != nullptr)
	{
		READ_THUNK(CanRecoveryJump, (int64_t)m_SigCanRecoveryJump());

		// Force allow recovery jump.
		WRITE_NOP(CanRecoveryJump + 0x8E, 2);
	}

	if (Configuration::IsSpinChargeNoAirDeceleration)
		WRITE_NOP(m_SigDisableSpinChargeDeceleration(), 5);

	INSTALL_HOOK(StateDropDashStart);
	INSTALL_HOOK(StateDropDashUpdate);
	INSTALL_HOOK(StateDropDashExit);
	INSTALL_HOOK(PostureDropDashUpdate);
	INSTALL_HOOK(StartSpinChargeCameraStart);
	INSTALL_HOOK(StateSpinBoostChargeStart);
	INSTALL_HOOK(StateSpinBoostChargeUpdate);
	INSTALL_HOOK(StateSpinBoostChargeExit);
	INSTALL_HOOK(StateSpinBoostStart);
	INSTALL_HOOK(StateSpinBoostUpdate);
	INSTALL_HOOK(StateSpinBoostExit);
	INSTALL_HOOK(StateSpinMoveStart);
	INSTALL_HOOK(StateSpinMoveUpdate);
	INSTALL_HOOK(StateSpinMoveExit);
	INSTALL_HOOK(StatePluginAirTrickUpdate);
	INSTALL_HOOK(StatePluginBoostUpdate);
	INSTALL_HOOK(StatePluginBoostRechargeMode);
	INSTALL_HOOK(CommonStateFallExit);
	INSTALL_HOOK(StateSquatUpdate);
	INSTALL_HOOK(StateFallSlopeUpdate);
	INSTALL_HOOK(StateGrindJumpUpdate);
	INSTALL_HOOK(StateStompingDownUpdate);
	INSTALL_HOOK(StateDoubleJumpUpdate);
	INSTALL_HOOK(StateRecoveryJumpUpdate);
	INSTALL_HOOK(SendMoveImpulse);
	INSTALL_HOOK(ObjFanProcessMessage);
	INSTALL_HOOK(GOCPlayerHsmUpdate);
	INSTALL_HOOK(GOCPlayerHsmGroundStateUpdate);
	INSTALL_HOOK(PlayerKinematicsGroundUpdate);
	INSTALL_HOOK(PlayerKinematicsAirUpdate);
}