#pragma once

class BlackboardHelper
{
public:
	enum EStateFlags : int64_t
	{
		EStateFlags_IsBoost = 0x00,
		EStateFlags_IsRecoveryJump = 0x02,
		EStateFlags_IsAirBoost = 0x04,
		EStateFlags_IsGrindJump = 0x06,
		EStateFlags_IsGrind = 0x07,
		EStateFlags_IsJump = 0x08,
		EStateFlags_IsDoubleJump = 0x09,
		EStateFlags_IsBounceJump = 0x0A,
		EStateFlags_IsFall = 0x0B,
		EStateFlags_IsStomp = 0x0C,
		EStateFlags_IsDiving = 0x0D,
		EStateFlags_IsDivingBoost = 0x0E,
		EStateFlags_IsCyloop = 0x11,
		EStateFlags_IsCyloopEnd = 0x12,
		EStateFlags_IsDrift = 0x13,
		EStateFlags_IsDriftDash = 0x14,
		EStateFlags_IsHoming = 0x17,
		EStateFlags_IsParry = 0x18,
		EStateFlags_IsWallClimb = 0x19,
		EStateFlags_IsIdle = 0x1A,
		EStateFlags_IsBoarding = 0x1E,
		EStateFlags_IsSpringJump = 0x21,
		EStateFlags_IsPhantomRush = 0x26
	};

	// TODO: investigate IsDead and IsDamaged.
	enum EWorldFlags : int64_t
	{
		EWorldFlags_IsDead = 0x02,
		EWorldFlags_IsDamaged = 0x04,
		EWorldFlags_IsCyberSpace = 0x1D,
		EWorldFlags_IsPowerBoost = 0x26,
		EWorldFlags_IsHeightMapCollision = 0x31
	};

	inline static app::player::BlackboardStatus* GetStatus()
	{
		auto* pGameDocument = app::GameDocument::GetSingleton();

		if (!pGameDocument)
			return nullptr;

		auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

		if (!pSonic)
			return nullptr;

		auto* pPlayerBlackboard = pSonic->GetComponent<app::player::GOCPlayerBlackboard>();

		if (!pPlayerBlackboard)
			return nullptr;

		auto* pBlackboardStatus = pPlayerBlackboard->pBlackboard->GetBlackboardContent<app::player::BlackboardStatus>();

		if (!pBlackboardStatus)
			return nullptr;

		return pBlackboardStatus;
	}

	inline static bool CheckStateFlags(EStateFlags in_flags)
	{
		auto status = GetStatus();

		if (!status)
			return false;

		return _bittest64(&status->StateFlags, in_flags);
	}

	inline static bool CheckWorldFlags(EWorldFlags in_flags)
	{
		auto status = GetStatus();

		if (!status)
			return false;

		return _bittest64(&status->WorldFlags, in_flags);
	}

	inline static bool IsAirBoosting()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsAirBoost);
	}

	inline static bool IsBoosting()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsBoost);
	}

	inline static bool IsCyberSpace()
	{
		return CheckWorldFlags(EWorldFlags::EWorldFlags_IsCyberSpace);
	}

	inline static bool IsCylooping()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsCyloop);
	}

	inline static bool IsDrifting()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsDrift);
	}

	inline static bool IsGrinding()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsGrind);
	}

	inline static bool IsJumping()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsJump);
	}

	inline static bool IsSideView()
	{
		auto* pGameDocument = app::GameDocument::GetSingleton();

		if (!pGameDocument)
			return false;

		auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

		if (!pSonic)
			return false;

		auto* pPlayerParameter = pSonic->GetComponent("GOCPlayerParameter");

		if (!pPlayerParameter)
			return false;

		return *(int32_t*)(((int64_t)pPlayerParameter) + 0xB8) == 3;
	}

	inline static bool IsUnderwater()
	{
		auto* pGameDocument = app::GameDocument::GetSingleton();

		if (!pGameDocument)
			return false;

		auto* pSonic = pGameDocument->GetGameObject<app::player::Sonic>();

		if (!pSonic)
			return false;

		auto* pPlayerParameter = pSonic->GetComponent("GOCPlayerParameter");

		if (!pPlayerParameter)
			return false;

		return *(int32_t*)(((int64_t)pPlayerParameter) + 0xB8) == 1;
	}

	inline static bool IsWallClimbing()
	{
		return CheckStateFlags(EStateFlags::EStateFlags_IsWallClimb);
	}
};