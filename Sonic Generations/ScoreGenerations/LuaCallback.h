#pragma once

#define LUA_FILE "ScoreGenerations.lua"

class LuaCallback
{
	static std::string LuaPath;

public:
	static bool SetLuaPath(std::string path);
	static void PushExposedData(lua_State* L);

	template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	static void PushExposedNumber(lua_State* L, std::string name, T pushToStack);

	static void PushExposedString(lua_State* L, std::string name, std::string value);
	static void PushLuaLibrary(lua_State* L, const char* name, lua_CFunction function);
	static bool LoadInternalLibrary(lua_State* L);
	static bool LoadExternalLibrary(lua_State* L);
	static void PrintExposedData();
	static int RunAlgorithm(std::string algorithm);

	static int print(lua_State* L)
	{
		int nargs = lua_gettop(L);

		// Print characters from string.
		for (int i = 1; i <= nargs; ++i)
			std::cout << lua_tostring(L, i);

		// Print line break.
		std::cout << std::endl;

		return 0;
	}

	static const struct luaL_Reg Functions[];
};