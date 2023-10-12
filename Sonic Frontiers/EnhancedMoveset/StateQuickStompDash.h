#pragma once

enum EStateQuickStompDashFlags
{
	EStateQuickStompDashFlags_IsActive,
	EStateQuickStompDashFlags_IsDropDashEnd
};

class StateQuickStompDash
{
public:
	inline static std::bitset<2> Flags;

	static void Install();
};