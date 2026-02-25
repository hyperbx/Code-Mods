#pragma once

#define LUA_FILE_MAIN "ScoreGenerations.lua"
#define LUA_FILE_MATH "Math.lua"

#undef LoadLibrary

namespace ScoreGenerations
{
	class LuaSystem
	{
		inline static std::filesystem::path m_LuaPath{ LUA_FILE_MAIN };
		inline static std::filesystem::path m_MathLuaPath{ LUA_FILE_MATH };

		static luaL_Reg m_Functions[];

	public:
		static bool IsLuaSafe(lua_State* in_pLuaState, int in_result);

		static bool SetScript(const std::filesystem::path& in_rPath);

		template <typename T>
		static T RunExpression(const std::string& in_rCode);

		static void PushVariables(lua_State* in_pLuaState);

		template <typename T>
		static void PushVariable(lua_State* in_pLuaState, const char* in_pName, T in_value);

		static void LoadLibrary(lua_State* in_pLuaState, const char* in_pName, lua_CFunction in_function);
		static bool LoadInternalLibrary(lua_State* in_pLuaState);
		static bool LoadExternalLibrary(lua_State* in_pLuaState);
	};
}

#include "LuaSystem.inl"
