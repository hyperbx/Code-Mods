#pragma once

#include <tuple>
#include <type_traits>
#include <cstdio>
#include <typeinfo>

#include "rangers-api/rangers-api/rangers-api.h"

class ScriptSequenceHelper
{
private:
	// Tuple type template by Sajid (https://github.com/Sajidur78)

	template<int I = 0, typename ...TArgs>
	static typename std::enable_if<(I == std::tuple_size_v<std::tuple<TArgs...>>), void>::type GetLuaArgs(lua_State* in_pLuaState, const std::tuple<TArgs...>& tup) { }

	template<int I = 0, typename ...TArgs>
	static typename std::enable_if<(I < std::tuple_size_v<std::tuple<TArgs...>>), int>::type GetLuaArgs(lua_State* in_pLuaState, const std::tuple<TArgs...>& tup)
	{
		const char* type = typeid(std::tuple_element_t<I, std::remove_reference_t<decltype(tup)>>).name();

		if (!type)
			return 0;

		auto val = std::get<I>(tup);

		if (strcmp(type, "char const * __ptr64") == 0)
		{
			lua_pushstring(in_pLuaState, (const char*)val);
		}
		else if (strcmp(type, "int") == 0)
		{
			lua_pushinteger(in_pLuaState, (int)val);
		}
		else if ((strcmp(type, "float") == 0) || (strcmp(type, "double") == 0))
		{
			lua_pushnumber(in_pLuaState, *(float*)val);
		}
		else if (strcmp(type, "bool") == 0)
		{
			lua_pushboolean(in_pLuaState, (int)val);
		}

		GetLuaArgs<I + 1>(in_pLuaState, tup);

		return std::tuple_size<std::tuple<TArgs...>>();
	}

public:
	static lua_State* GetLuaState()
	{
		auto pGameManager = hh::game::GameManager::GetSingleton();

		if (!pGameManager)
			return nullptr;

		auto pScriptSequenceManager = pGameManager->GetService<app::ScriptSequenceManager>();

		if (!pScriptSequenceManager)
			return nullptr;

		auto pScriptSequence = pScriptSequenceManager->ScriptSequences[0];

		if (!pScriptSequence)
			return nullptr;

		auto pScript = pScriptSequence->pScripts[0];

		if (!pScript)
			return nullptr;

		return pScript->GetLuaWrapper()->pLuaState;
	}

	template<typename... TArgs>
	static void LuaCall(const char* in_pFunctionName, int in_resultCount, TArgs ...in_args)
	{
		auto pLuaState = GetLuaState();

		if (!pLuaState)
			return;

		lua_getglobal(pLuaState, in_pFunctionName);

		int argsCount = GetLuaArgs(pLuaState, std::make_tuple(in_args...));

		if (lua_pcallk(pLuaState, argsCount, in_resultCount, 0, 0, 0) != LUA_OK)
		{
			printf("[Lua] Error: %s\n", lua_tolstring(pLuaState, -1, 0));
			lua_pop(pLuaState, 1);
		}
	}

	template<typename... TArgs>
	static void LuaCall(const char* in_pFunctionName, TArgs ...in_args)
	{
		LuaCall(in_pFunctionName, 0, in_args);
	}

	static void LuaCall(const char* in_pFunctionName)
	{
		LuaCall(in_pFunctionName, 0, 0);
	}

	template<typename T, typename... TArgs>
	static T LuaCallT(const char* in_pFunctionName, TArgs ...in_args)
	{
		auto pLuaState = GetLuaState();

		if (!pLuaState)
			return 0;

		LuaCall(in_pFunctionName, 1, in_args...);

		auto type = typeid(T).name();

		if (!type)
			return 0;

		if (strcmp(type, "char const * __ptr64") == 0)
		{
			return (T)lua_tolstring(pLuaState, -1, 0);
		}
		else if (strcmp(type, "int") == 0)
		{
			return lua_tointeger(pLuaState, -1);
		}
		else if ((strcmp(type, "float") == 0) || (strcmp(type, "double") == 0))
		{
			return lua_tonumber(pLuaState, -1);
		}
		else if (strcmp(type, "bool") == 0)
		{
			return lua_toboolean(pLuaState, -1);
		}

		return 0;
	}

	template<typename T>
	static T LuaCallT(const char* in_pFunctionName)
	{
		return LuaCallT<T>(in_pFunctionName, 0);
	}
};
