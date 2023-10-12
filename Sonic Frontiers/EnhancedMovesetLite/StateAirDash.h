#pragma once

enum EStateAirDashFlags
{
	EStateAirDashFlags_IsActive,
	EStateAirDashFlags_IsReleased,
	EStateAirDashFlags_IsReleasedFromRecoveryJump
};

class StateAirDash
{
public:
	inline static std::bitset<3> Flags;

	static void Install();
};

