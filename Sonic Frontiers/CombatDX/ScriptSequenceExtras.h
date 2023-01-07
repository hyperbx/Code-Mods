#pragma once

class ScriptSequenceExtras : public app::ScriptSequence
{
	app::player::BlackboardBattle* GetBlackboardBattle()
	{
		auto* pDocument = GetDocument();

		if (!pDocument)
			return nullptr;

		auto* pSonic = pDocument->GetGameObject<app::player::Sonic>();

		if (!pSonic)
			return nullptr;

		auto* pPlayerBlackboard = pSonic->GetComponent<app::player::GOCPlayerBlackboard>();

		if (!pPlayerBlackboard)
			return nullptr;

		return pPlayerBlackboard->pBlackboard->GetBlackboardContent<app::player::BlackboardBattle>();
	}

public:
	inline static bool s_isPlayerInCombat = false;
	inline static const char* s_pAnimationName;
	inline static float s_framerate = 0.0f;

	struct Timer
	{
		float m_time;

		bool m_isRunning;

		Timer()
		{
			m_time      = 0.0f;
			m_isRunning = true;
		}

		Timer(bool in_isRunning)
		{
			m_time      = 0.0f;
			m_isRunning = in_isRunning;
		}

		Timer(float in_time, bool in_isRunning)
		{
			m_time      = in_time;
			m_isRunning = in_isRunning;
		}
	};

	inline static std::unordered_map<const char*, Timer> s_timers;

	static void Install();

	/*
		Function signature: IsPlayerInCombat() : boolean
	*/
	int IsPlayerInCombat(lua_State* in_pLuaState)
	{
		lua_pushboolean(in_pLuaState, s_isPlayerInCombat);

		return 1;
	}

	/*
		Function signature: GetCurrentAnimationName() : string
	*/
	int GetCurrentAnimationName(lua_State* in_pLuaState)
	{
		lua_pushstring(in_pLuaState, s_pAnimationName);

		return 1;
	}

	/*
		Function signature: GetPhantomRushGauge() : number
	*/
	int GetPhantomRushGauge(lua_State* in_pLuaState)
	{
		auto pBlackboardBattle = GetBlackboardBattle();

		if (pBlackboardBattle != nullptr)
			lua_pushnumber(in_pLuaState, pBlackboardBattle->PhantomRushGauge);

		return 1;
	}

	/*
		Function signature: SetPhantomRushGauge(number)
	*/
	int SetPhantomRushGauge(lua_State* in_pLuaState)
	{
		auto pBlackboardBattle = GetBlackboardBattle();

		if (pBlackboardBattle != nullptr)
			pBlackboardBattle->PhantomRushGauge = lua_tonumber(in_pLuaState, 1);

		return 0;
	}

	/*
		Function signature: GetQuickCyloopGauge() : number
	*/
	int GetQuickCyloopGauge(lua_State* in_pLuaState)
	{
		auto pBlackboardBattle = GetBlackboardBattle();

		if (pBlackboardBattle != nullptr)
			lua_pushnumber(in_pLuaState, pBlackboardBattle->QuickCyloopGauge);

		return 1;
	}

	/*
		Function signature: SetQuickCyloopGauge(number)
	*/
	int SetQuickCyloopGauge(lua_State* in_pLuaState)
	{
		auto pBlackboardBattle = GetBlackboardBattle();

		if (pBlackboardBattle != nullptr)
			pBlackboardBattle->QuickCyloopGauge = lua_tonumber(in_pLuaState, 1);

		return 0;
	}

	/*
		Function signature: GetDeltaTime() : number
	*/
	int GetDeltaTime(lua_State* in_pLuaState)
	{
		lua_pushnumber(in_pLuaState, 1.0f / s_framerate);

		return 1;
	}

	/*
		Function signatures;
		- CreateTimer(string) : number
		- CreateTimer(string, boolean) : number
	*/
	int CreateTimer(lua_State* in_pLuaState)
	{
		auto key = lua_tostring(in_pLuaState, 1);

		auto val = Timer
		(
			// Always return true if no enabled state was specified.
			lua_gettop(in_pLuaState) > 1
				? lua_toboolean(in_pLuaState, 2)
				: true
		);

		if (s_timers.find(key) == s_timers.end())
		{
			s_timers.emplace(key, val);
		}
		else
		{
			val = s_timers[key];
		}

		lua_pushnumber(in_pLuaState, val.m_time);

		return 1;
	}

	/*
		Function signature: DestroyTimer(string)
	*/
	int DestroyTimer(lua_State* in_pLuaState)
	{
		auto key = lua_tostring(in_pLuaState, 1);

		if (s_timers.find(key) != s_timers.end())
		{
			s_timers.erase(key);
		}
		else
		{
			printf("[Combat DX] Timer \"%s\" does not exist!\n", key);
		}

		return 0;
	}

	/*
		Function signature: GetTimer(string) : number
	*/
	int GetTimer(lua_State* in_pLuaState)
	{
		auto key = lua_tostring(in_pLuaState, 1);

		if (s_timers.find(key) == s_timers.end())
		{
			printf("[Combat DX] Timer \"%s\" does not exist!\n", key);

			lua_pushnumber(in_pLuaState, 0.0f);

			return 1;
		}

		lua_pushnumber(in_pLuaState, s_timers[key].m_time);

		return 1;
	}

	/*
		Function signatures;
		- SetTimer(string, number)
		- SetTimer(string, boolean)
		- SetTimer(string, number, boolean)
	*/
	int SetTimer(lua_State* in_pLuaState)
	{
		auto key = lua_tostring(in_pLuaState, 1);

		if (s_timers.find(key) != s_timers.end())
		{
			if (lua_gettop(in_pLuaState) > 2)
			{
				s_timers[key] = Timer(lua_tonumber(in_pLuaState, 2), lua_toboolean(in_pLuaState, 3));
			}
			else
			{
				if (lua_isboolean(in_pLuaState, 2))
				{
					s_timers[key].m_isRunning = lua_toboolean(in_pLuaState, 2);
				}
				else
				{
					s_timers[key].m_time = lua_tonumber(in_pLuaState, 2);
				}
			}
		}
		else
		{
			printf("[Combat DX] Timer \"%s\" does not exist!\n", key);
		}

		return 0;
	}
};