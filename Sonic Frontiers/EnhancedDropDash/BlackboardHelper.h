#pragma once

#define STATUS_PARAM_BOOST          0x01
#define STATUS_PARAM_RECOVERYJUMP   0x02
#define STATUS_PARAM_AIRBOOST       0x04
#define STATUS_PARAM_GRINDJUMP      0x06
#define STATUS_PARAM_GRIND          0x07
#define STATUS_PARAM_JUMP           0x08
#define STATUS_PARAM_DOUBLEJUMP     0x09
#define STATUS_PARAM_STOMPBOUNCE    0x0A
#define STATUS_PARAM_FALL		    0x0B
#define STATUS_PARAM_STOMP          0x0C
#define STATUS_PARAM_SKYDIVE        0x0D
#define STATUS_PARAM_SKYDIVEBOOST   0x0E
#define STATUS_PARAM_CYLOOP         0x11
#define STATUS_PARAM_CYLOOPEND      0x12
#define STATUS_PARAM_DRIFT          0x13
#define STATUS_PARAM_DRIFTDASH      0x14
#define STATUS_PARAM_HOMING         0x17
#define STATUS_PARAM_PARRY          0x18
#define STATUS_PARAM_WALLCLIMB      0x19
#define STATUS_PARAM_IDLE		    0x1A
#define STATUS_PARAM_BOARDING       0x1E
#define STATUS_PARAM_IMPULSE_TARGET 0x21
#define STATUS_PARAM_PHANTOMRUSH    0x26

#define STATUS_30_SIDEVIEW    0x1A
#define STATUS_30_POWERBOOST  0x27
#define STATUS_30_ISLANDSTAGE 0x31

class BlackboardHelper
{
public:
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

	inline static uint8_t CheckStatusFieldFlags(int64_t in_field, uint32_t in_flags)
	{
		return _bittest64(&in_field, in_flags);
	}

	inline static uint8_t CheckStatusField30Flags(uint32_t in_flags)
	{
		auto status = GetStatus();

		if (!status)
			return false;

		return CheckStatusFieldFlags(status->field_30, in_flags);
	}

	inline static uint8_t CheckStateParameterFlags(uint32_t in_flags)
	{
		auto status = GetStatus();

		if (!status)
			return false;

		return CheckStatusFieldFlags(status->StateParameter, in_flags);
	}

	inline static bool IsAirBoosting()
	{
		return BlackboardHelper::CheckStateParameterFlags(STATUS_PARAM_AIRBOOST);
	}

	inline static bool IsRunning()
	{
		return GetStatus()->StateParameter == 0;
	}

	inline static bool IsBoarding()
	{
		return CheckStateParameterFlags(STATUS_PARAM_BOARDING);
	}

	inline static bool IsBoosting()
	{
		return CheckStateParameterFlags(STATUS_PARAM_BOOST);
	}

	inline static bool IsCyberSpace()
	{
		return !CheckStatusField30Flags(STATUS_30_ISLANDSTAGE);
	}

	inline static bool IsCylooping()
	{
		return CheckStateParameterFlags(STATUS_PARAM_CYLOOP);
	}

	inline static bool IsDrifting()
	{
		return CheckStateParameterFlags(STATUS_PARAM_DRIFT);
	}

	inline static bool IsGrinding()
	{
		return CheckStateParameterFlags(STATUS_PARAM_GRIND);
	}

	inline static bool IsJumping()
	{
		return CheckStateParameterFlags(STATUS_PARAM_JUMP);
	}

	inline static bool IsSideView()
	{
		return CheckStatusField30Flags(STATUS_30_SIDEVIEW);
	}

	inline static bool IsWallClimbing()
	{
		return CheckStateParameterFlags(STATUS_PARAM_WALLCLIMB);
	}
};