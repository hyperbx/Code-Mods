#include "dependencies\Lua542\include\lua.hpp"

#pragma once

#define LUA_FILE "ScoreGenerations.lua"

class LuaCallback
{
public:
	static void PushExposedData(lua_State* L);
	static void PushExposedUnsignedInteger(lua_State* L, string name, unsigned int pushToStack);
	static bool LoadExternalLibrary(lua_State* L);
	static unsigned int GetBonus(string algorithm);
};