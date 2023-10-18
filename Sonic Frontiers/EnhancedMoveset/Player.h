#pragma once

#include "ESonicState.h"
#include "MsgChangeLayerTimeScale.h"

#define GET_UNCURL_TYPE_BY_VIEW(config) (BlackboardHelper::IsSideView() ? config##SV : config)

// Function Pointers
CL_SCAN_SIGNATURE(m_SigSetState, 0x140802400, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xD9\x41\x8B\xF8\x48\x81\xC1\x88\x00\x00\x00\x8B\xF2\xE8\xCC\xCC\xCC\xCC\x3B", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????x");
CL_SCAN_SIGNATURE(m_SigSetAnimation, 0x1408122E0, "\x40\x53\x48\x83\xEC\x20\xF6\x81\x78\x01\x00\x00\x10\x48\x8B\xDA", "xxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSetAnimationParameter, 0x140813140, "\x40\x53\x48\x83\xEC\x30\x48\x8B\x81\x10\x01\x00\x00\x48\x8B\xDA", "xxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigPlayAnimationEffect, 0x140901E20, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xF2\x48\x8B\xF9\xE8\xCC\xCC\xCC\xCC\x48\x8B\xD8", "xxxxxxxxxxxxxxxxxxxxxx????xxx");
CL_SCAN_SIGNATURE(m_SigStopAnimationEffects, 0x14BC65500, "\x40\x53\x48\x83\xEC\x20\x48\x89\xCB\xE8\xCC\xCC\xCC\xCC\x48\x85\xC0", "xxxxxxxxxx????xxx");
CL_SCAN_SIGNATURE(m_SigPlaySound, 0x140AE69F0, "\x4C\x8B\xDC\x49\x89\x5B\x08\x57\x48\x81\xEC\x80\x00\x00\x00", "xxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStopSoundCaller, 0x1405A90FF, "\xE8\xCC\xCC\xCC\xCC\x48\x8B\xCF\xE8\xCC\xCC\xCC\xCC\x33\xD2\x48\x8B\xCF\xF3\x0F\x10\x90\x90\x00\x00\x00", "x????xxxx????xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGetStatePluginCollision, 0x14086A0B0, "\x40\x56\x48\x83\xEC\x20\x48\x8B\x41\x38\x48\x8B\xB0\x08\x01\x00\x00\x48\x85\xF6\x74\x65\x48\x8B\x46\x20\x48\x89\x5C\x24\x30\x48\x8B\x5E\x18\x48\x89\x7C\x24\x38\x48\x8D\x3C\xC3\x48\x3B\xDF\x74\x19\x48\x8B\x0B\x48\x8B\x01\xFF\x50\xCC\x3D\x8E\xB4\x47\x3B", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxx");
CL_SCAN_SIGNATURE(m_SigTogglePlayerEntityCollision, 0x14BB87C00, "\x40\x53\x48\x83\xEC\x20\x48\x8B\x41\x50\x0F\xB6\xDA", "xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSetCollisionSphere, 0x1408ED200, "\x40\x53\x48\x83\xEC\x50\x0F\x28\x05\xCC\xCC\xCC\xCC\x48\x8B\xD9\x88\x54\x24\x20", "xxxxxxxxx????xxxxxxx");
CL_SCAN_SIGNATURE(m_SigSendMessageToGameObjectCaller, 0x140679CED, "\xE8\xCC\xCC\xCC\xCC\x48\x8D\x4D\xB0\xE8\xCC\xCC\xCC\xCC\x48\x8B\x15\xCC\xCC\xCC\xCC\x0F\x28\x74\x24\x60", "x????xxxxx????xxx????xxxxx");
CL_SCAN_SIGNATURE(m_SigGetFxParamBulletTimeExtensionCaller, 0x1402A1D0B, "\xE8\xCC\xCC\xCC\xCC\x48\x85\xC0\x74\x0B\x0F\x28\xCF\x48\x8B\xC8\xE8\xCC\xCC\xCC\xCC\xE8", "x????xxxxxxxxxxxx????x");
CL_SCAN_SIGNATURE(m_SigStartBulletTime, 0x140219440, "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x70\x20\x55\x57\x41\x56\x48\x8D\x68\xA1\x48\x81\xEC\xB0\x00\x00\x00\x80\x79\x24\x00", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigEndBulletTime, 0x140219270, "\x40\x53\x48\x83\xEC\x30\x80\x79\x24\x00", "xxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGetStatePluginEffect, 0x140124200, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x20\x48\x8B\x59\x18\x8B", "xxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigPlayEffect, 0x1408DF420, "\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x18\x48\x89\x70\x20\x57\x48\x81\xEC\xA0\x00\x00\x00\xF3", "xxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStopEffect, 0x14B912E80, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x8B\x41\x30\x48\x8D", "xxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigCheckBlackboardFlags, 0x1407DE270, "\x8B\xC2\x83\xE0\x3F\x44\x0F\xB6\xC0\x8B\xC2\x48\xC1\xE8\x06\x48\x8B\x44\xC1\x28", "xxxxxxxxxxxxxxxxxxxx");

// Hooks
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmUpdate, 0x1408AA540, "\x40\x53\x55\x48\x83\xEC\x28\x49", "xxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmAirStateUpdate, 0x1408024E0, "\x41\x56\x48\x83\xEC\x30\x0F\xB6\x81\x1C", "xxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmGroundStateUpdate, 0x1408025D0, "\x40\x53\x41\x56\x41\x57\x48\x83\xEC\x20\xF6\x81\x1C", "xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigPlayerKinematicsAirUpdateCaller, 0x14082C1C6, "\xE8\xCC\xCC\xCC\xCC\x80\xBF\x10\x01\x00\x00\x00", "x????xxxxxxx");
CL_SCAN_SIGNATURE(m_SigPlayerKinematicsGroundUpdate, 0x14085B850, "\x48\x8B\xC4\x55\x56\x48\x8D\x68\xA1\x48\x81\xEC\xF8\x00\x00\x00\x48", "xxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigEffectForetasteUpdate, 0x1407E98B0, "\x40\x53\x48\x83\xEC\x30\x48\x83\x79\x50\x00\x48\x8B\xD9\x74", "xxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigHitStopUpdate, 0x147580590, "\x48\x89\x5C\x24\x18\x56\x48\x83\xEC\x50\x48\x6B", "xxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSonicProcessMessage, 0x140864C00, "\x48\x89\x5C\x24\x20\x55\x56\x57\x41\x56\x41\x57\x48\x8D\xAC\x24\xC0\xFE\xFF\xFF", "xxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigCheckHomingTarget, 0x140952494, "\x4C\x8D\x44\x24\x30\x48\x8D\x15\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x48\x83\xC3\x30", "xxxxxxxx????x????xxxx");

// Required Patches
CL_SCAN_SIGNATURE(m_SigIsRecoveryJumpAvailable, 0x14B40B706, "\xE8\xCC\xCC\xCC\xCC\x84\xC0\x74\x26\x45\x31\xC0", "x????xxxxxxx");
CL_SCAN_SIGNATURE(m_SigWallActionCheck, 0x1408F2E60, "\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x10\x55\x57\x41\x56\x48\x8D\xA8\x58\xFF\xFF\xFF", "xxxxxxxxxxxxxxxxxxxxxx");

enum ECollisionType : uint8_t
{
	ECollisionType_Default,
	ECollisionType_Damage = 2,
	ECollisionType_DamageHoming = 3
};

enum EPlayerFlags
{
	EPlayerFlags_IsForetasteActive
};

class Player
{
public:
	inline static std::bitset<1> Flags;

	inline static float DeltaTime = 0.0f;

	inline static bool IsDamage = true;
	inline static bool IsHitStop = true;
	inline static bool IsHomingTarget = false;

	inline static bool* pIsForetasteActive;
	inline static float ForetasteActiveTime = 0.0f;

	inline static ESonicState CurrentState = ESonicState_Default;
	inline static ESonicState LastState = ESonicState_Default;

	static app::player::Sonic* GetSonic()
	{
		auto* pGameDocument = hh::game::GameManager::GetSingleton();

		if (!pGameDocument)
			return nullptr;

		return pGameDocument->GetGameObject<app::player::Sonic>();
	}

	static app::player::GOCPlayerKinematicParams* GetKinematics()
	{
		auto* pSonic = GetSonic();

		if (!pSonic)
			return nullptr;

		return pSonic->GetGOC<app::player::GOCPlayerKinematicParams>();
	}

	static bool IsGrounded()
	{
		auto* pGameDocument = hh::game::GameManager::GetSingleton();

		if (!pGameDocument)
			return false;

		auto* pLevelInfo = pGameDocument->GetService<app::level::LevelInfo>();

		if (!pLevelInfo)
			return false;

		return pLevelInfo->pPlayerInfos[0]->IsGrounded;
	}

	static bool IsGroundedSpecial()
	{
		return IsGrounded() ||
			BlackboardHelper::IsGrinding() ||
			BlackboardHelper::IsSpringJump() ||
			BlackboardHelper::IsWallClimbing();
	}

	static bool IsStateAvailableInWorld(EWorldType in_worldType)
	{
		return (BlackboardHelper::IsCyberSpace()
			? (in_worldType == EWorldType_Both || in_worldType == EWorldType_CyberOnly)
			: (in_worldType == EWorldType_Both || in_worldType == EWorldType_IslandOnly));
	}

	static bool IsStateAvailableInView(EViewType in_viewType)
	{
		if (in_viewType == EViewType_Disabled)
			return false;

		if (in_viewType == EViewType_Always)
			return true;

		return (BlackboardHelper::IsSideView()
			? in_viewType == EViewType_SideViewOnly
			: in_viewType == EViewType_ForwardViewOnly);
	}

	static bool IsSpinDashUnlocked()
	{
		auto blackboardStatus = BlackboardHelper::GetBlackboardStatus();

		if (!blackboardStatus)
			return false;

		FUNCTION_PTR(bool, __fastcall, fpCheckBlackboardFlags, m_SigCheckBlackboardFlags(), app::player::BlackboardStatus* in_pBlackboardStatus, uint32_t in_flags);

		/* I could easily check this myself, but I'm using the function pointer
		   so I don't have to check for the "Always Unlocked Spin Dash" code. */
		return fpCheckBlackboardFlags(blackboardStatus, 0x3B);
	}

	static void SendMessageToGameObject(hh::game::GameObject* in_pGameObject, hh::fnd::Message& in_rMessage)
	{
		FUNCTION_PTR(int64_t, __fastcall, fpSendMessageToGameObject, READ_CALL(m_SigSendMessageToGameObjectCaller()), hh::game::GameObject* in_pGameObject, hh::fnd::Message& in_rMessage);

		fpSendMessageToGameObject(in_pGameObject, in_rMessage);
	}

	static void SetAnimation(const char* in_pAnimationName)
	{
		auto* pSonic = GetSonic();

		if (!pSonic)
			return;

		FUNCTION_PTR(void, __fastcall, fpSetAnimation, m_SigSetAnimation(), int64_t in_pGOCPlayerVisual, const char* in_pAnimationName, uint8_t a3);

		return fpSetAnimation((int64_t)(pSonic->GetGOC("GOCPlayerVisual")), in_pAnimationName, 0xFE);
	}

	static void SetAnimationEffect(int64_t in_pSonicContext, bool in_enabled, const char* in_pEffectName = "")
	{
		if (in_enabled)
		{
			FUNCTION_PTR(bool, __fastcall, fpPlayAnimationEffect, m_SigPlayAnimationEffect(), int64_t in_pSonicContext, const char* in_effectName);

			fpPlayAnimationEffect(in_pSonicContext, in_pEffectName);
		}
		else
		{
			FUNCTION_PTR(int64_t, __fastcall, fpStopAnimationEffects, m_SigStopAnimationEffects(), int64_t in_pSonicContext);

			fpStopAnimationEffects(in_pSonicContext);
		}
	}

	static double SetAnimationParameter(const char* in_pAnimationParameterName, float in_value)
	{
		auto* pSonic = GetSonic();

		if (!pSonic)
			return 0.0;

		FUNCTION_PTR(double, __fastcall, fpSetAnimationParameter, m_SigSetAnimationParameter(), int64_t in_pGOCPlayerVisual, const char* in_pAnimationParameterName, float in_value);

		return fpSetAnimationParameter((int64_t)(pSonic->GetGOC("GOCPlayerVisual")), in_pAnimationParameterName, in_value);
	}

	static void SetDamageSphere(int64_t in_pSonicContext, bool in_enabled, float in_radius = 1.0f)
	{
		FUNCTION_PTR(int64_t, __fastcall, fpGetStatePluginCollision, m_SigGetStatePluginCollision(), int64_t in_pSonicContext);
		FUNCTION_PTR(void, __fastcall, fpTogglePlayerEntityCollision, m_SigTogglePlayerEntityCollision(), int64_t in_pSonicContext, bool in_enabled);
		FUNCTION_PTR(int64_t, __fastcall, fpSetCollisionSphere, m_SigSetCollisionSphere(), int64_t in_pStatePluginCollision, uint8_t in_type, float in_radius);

		fpSetCollisionSphere(fpGetStatePluginCollision(in_pSonicContext), in_enabled ? ECollisionType_Damage : ECollisionType_Default, in_radius);
		fpTogglePlayerEntityCollision(in_pSonicContext, !in_enabled);
	}

	static int64_t GetStatePluginEffect(int64_t in_pSonicContext)
	{
		FUNCTION_PTR(int64_t, __fastcall, fpGetStatePluginEffect, m_SigGetStatePluginEffect(), int64_t in_pStatePluginManager, int in_stringHash);

		return fpGetStatePluginEffect(*(int64_t*)(*(int64_t*)(in_pSonicContext + 0x38) + 0x108), 0x326CA9B5);
	}

	static void PlayEffect(int64_t in_pSonicContext, const char* in_pHandleName, const char* in_pEffectName)
	{
		int64_t pStatePluginEffect = GetStatePluginEffect(in_pSonicContext);

		if (!pStatePluginEffect)
			return;

		FUNCTION_PTR(int64_t, __fastcall, fpPlayEffect, m_SigPlayEffect(), int64_t in_pStatePluginEffect, int in_stringHash, const char* in_pEffectName);

		fpPlayEffect(pStatePluginEffect, csl::ut::StringMapOperation::hash(in_pHandleName), in_pEffectName);
	}

	static void StopEffect(int64_t in_pSonicContext, const char* in_pHandleName)
	{
		int64_t pStatePluginEffect = GetStatePluginEffect(in_pSonicContext);

		if (!pStatePluginEffect)
			return;

		FUNCTION_PTR(int64_t, __fastcall, fpStopEffect, m_SigStopEffect(), int64_t in_pStatePluginEffect, int in_stringHash);

		fpStopEffect(pStatePluginEffect, csl::ut::StringMapOperation::hash(in_pHandleName));
	}

	static void PlayVoice(int64_t in_pSonicContext, int in_index)
	{
		FUNCTION_PTR(int64_t, __fastcall, fpPlayVoice, 0x14BC4BA20, size_t* in_pStringHash, int64_t in_pSonicContext, int in_index);

		auto hash = csl::ut::StringMapOperation::hash("voice");

		fpPlayVoice(&hash, in_pSonicContext, in_index);
	}

	static void SetState(int64_t in_pSonicContext, ESonicState in_stateId)
	{
		if (in_stateId == ESonicState_StateSpinBoostCharge ||
			in_stateId == ESonicState_StateSpinBoost ||
			in_stateId == ESonicState_StateSpinMove)
		{
			if (!Player::IsSpinDashUnlocked())
				return;
		}

		FUNCTION_PTR(bool, __fastcall, fpSetState, m_SigSetState(), int64_t in_pGOCPlayerHsm, int in_stateId, int a3);

		fpSetState(*(int64_t*)(in_pSonicContext + 0x38), in_stateId, 0);
	}

	static void SetTimeScale(float in_timeScale, const char* in_pLayerName = "ninja", int in_flags = 0x30002F0)
	{
		auto* pSonic = GetSonic();

		if (!pSonic)
			return;

		app::game::MsgChangeLayerTimeScale msg { in_pLayerName, in_timeScale, in_flags, 0.0f };

		SendMessageToGameObject(pSonic, msg);
	}

	static void SetBulletTime(bool in_isEnabled, float in_timeScale = 0.125f, float in_fadeTime = 0.25f, const char* in_pLayerName = "ninja", int in_flags = 0x30002F0)
	{
		auto* pGameDocument = hh::game::GameManager::GetSingleton();

		if (!pGameDocument)
			return;

		auto pFxParamManager = pGameDocument->GetService("FxParamManager");

		if (!pFxParamManager)
			return;

		FUNCTION_PTR(int64_t, __fastcall, fpGetFxParamBulletTimeExtension, READ_CALL(m_SigGetFxParamBulletTimeExtensionCaller()), int64_t in_pFxParamManager);

		int64_t pFxParamBulletTimeExtension = fpGetFxParamBulletTimeExtension((int64_t)pFxParamManager);

		if (!pFxParamBulletTimeExtension)
			return;

		FUNCTION_PTR(int64_t, __fastcall, fpStartBulletTime, m_SigStartBulletTime(), int64_t in_pFxParamBulletTimeExtension, float in_fadeInTime);
		FUNCTION_PTR(void, __fastcall, fpEndBulletTime, m_SigEndBulletTime(), int64_t in_pFxParamBulletTimeExtension, float in_fadeOutTime);

		if (in_isEnabled)
		{
			Player::SetTimeScale(in_timeScale, in_pLayerName, in_flags);
			fpStartBulletTime(pFxParamBulletTimeExtension, in_fadeTime);
		}
		else
		{
			Player::SetTimeScale(1.0f, in_pLayerName, in_flags);
			fpEndBulletTime(pFxParamBulletTimeExtension, in_fadeTime);
		}
	}

	static int PlaySound(const char* in_pSoundName)
	{
		auto* pGameDocument = hh::game::GameManager::GetSingleton();

		if (!pGameDocument)
			return 0;

		auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

		if (!pSonic)
			return 0;

		int zero = 0; // no idea what this is lol

		FUNCTION_PTR(int*, __fastcall, fpPlaySound, m_SigPlaySound(), int64_t in_pGOCSound, int* a2, const char* in_soundName, float a4);

		return *fpPlaySound((int64_t)(pSonic->GetGOC("GOCSound")), &zero, in_pSoundName, 0.0f);
	}

	static void StopSound(int* in_pSoundHandle)
	{
		FUNCTION_PTR(void, __fastcall, fpStopSound, READ_CALL(m_SigStopSoundCaller()), int* in_pSoundHandle);

		fpStopSound(in_pSoundHandle);
	}

	static void Install();
};

