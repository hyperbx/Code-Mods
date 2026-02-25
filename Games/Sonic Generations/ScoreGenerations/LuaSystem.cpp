#include "LuaSystem.h"
#include "ScoreProvider.h"
#include "StatisticsProvider.h"
#include "TableProvider.h"

#define LUA_V1_BACKCOMPAT_PUSH_VAR(LUA_STATE, V2_NAME, V1_NAME, VALUE) \
	PushVariable(LUA_STATE, V2_NAME, VALUE);                           \
	PushVariable(LUA_STATE, V1_NAME, VALUE);

using namespace ScoreGenerations;

bool LuaSystem::IsLuaSafe(lua_State* in_pLuaState, int in_result)
{
	if (in_result != LUA_OK)
	{
		LOGFN_ERROR("Lua Error: {}", lua_tostring(in_pLuaState, -1));
		return false;
	}

	return true;
}

bool LuaSystem::SetScript(const std::filesystem::path& in_rPath)
{
	if (!std::filesystem::exists(in_rPath))
		return false;

	m_LuaPath = std::filesystem::path(in_rPath);

	auto mathLuaPath = std::filesystem::path(in_rPath).remove_filename() / LUA_FILE_MATH;

	if (std::filesystem::exists(mathLuaPath))
		m_MathLuaPath = mathLuaPath;

	return true;
}

void LuaSystem::PushVariables(lua_State* in_pLuaState)
{
	auto& rStatistics = StatisticsProvider::GetStatistics();
	auto& rRankTable = TableProvider::GetRankTables()[g_pStageID];

	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalRingCount", "totalRingCount", rStatistics.TotalRingCount);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalEnemies", "totalEnemies", rStatistics.TotalEnemies);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalPhysics", "totalPhysics", rStatistics.TotalPhysics);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalPointMarkers", "totalPointMarkers", rStatistics.TotalPointMarkers);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalRedRings", "totalRedRings", rStatistics.TotalRedRings);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalRainbowRings", "totalRainbowRings", rStatistics.TotalRainbowRings);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalItemBoxes", "totalItemBoxes", rStatistics.TotalItemBoxes);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalSuperRings", "totalSuperRings", rStatistics.TotalSuperRings);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalTricks", "totalTricks", rStatistics.TotalTricks);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalDashRings", "totalDashRings", rStatistics.TotalDashRings);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalQuickSteps", "totalQuickSteps", rStatistics.TotalQuickSteps);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalDrifts", "totalDrifts", rStatistics.TotalDrifts);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalBalloons", "totalBalloons", rStatistics.TotalBalloons);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "TotalSpeed", "totalVelocity", rStatistics.TotalSpeed);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "HighestSpeed", "maxVelocity", rStatistics.HighestSpeed);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "RingCount", "ringCount", rStatistics.RingCount);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "ElapsedTime", "elapsedTime", rStatistics.ElapsedTime);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "Minutes", "minutes", rStatistics.Minutes);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "Seconds", "seconds", rStatistics.Seconds);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "Milliseconds", "milliseconds", rStatistics.Milliseconds);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "Score", "score", ScoreProvider::GetCurrentScore());
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "MaxScore", "scoreLimit", Configuration::MaxScore);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "MinSeconds", "minSeconds", rRankTable.MinSeconds);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "MaxSeconds", "maxSeconds", rRankTable.MaxSeconds);
	LUA_V1_BACKCOMPAT_PUSH_VAR(in_pLuaState, "StageID", "stageID", g_pStageID);
}

template <typename T>
void LuaSystem::PushVariable(lua_State* in_pLuaState, const char* in_pName, T in_value)
{
	if constexpr (std::is_integral_v<T> || std::is_same_v<T, float> || std::is_same_v<T, double>)
	{
		lua_pushnumber(in_pLuaState, in_value);
	}
	else if constexpr (std::is_same_v<T, std::string>)
	{
		lua_pushstring(in_pLuaState, in_value.c_str());
	}
	else if constexpr (std::is_same_v<T, std::string_view>)
	{
		lua_pushstring(in_pLuaState, in_value.data());
	}
	else if constexpr (std::is_same_v<T, const char*>)
	{
		lua_pushstring(in_pLuaState, in_value);
	}

	lua_setglobal(in_pLuaState, in_pName);
}

void LuaSystem::LoadLibrary(lua_State* in_pLuaState, const char* in_pName, lua_CFunction in_function)
{
	luaL_requiref(in_pLuaState, in_pName, in_function, 1);
	lua_pop(in_pLuaState, 1);
}

bool LuaSystem::LoadInternalLibrary(lua_State* in_pLuaState)
{
	LoadLibrary(in_pLuaState, "", luaopen_base);
	LoadLibrary(in_pLuaState, LUA_LOADLIBNAME, luaopen_package);
	LoadLibrary(in_pLuaState, LUA_TABLIBNAME, luaopen_table);
	LoadLibrary(in_pLuaState, LUA_STRLIBNAME, luaopen_string);
	LoadLibrary(in_pLuaState, LUA_MATHLIBNAME, luaopen_math);

	LOGFN_UTILITY("LoadInternalLibrary: {}", m_MathLuaPath.string().c_str());

	return IsLuaSafe(in_pLuaState, luaL_dofile(in_pLuaState, m_MathLuaPath.string().c_str()));
}

bool LuaSystem::LoadExternalLibrary(lua_State* in_pLuaState)
{
	lua_getglobal(in_pLuaState, LUA_GNAME);
	luaL_setfuncs(in_pLuaState, m_Functions, 0);

	LOGFN_UTILITY("LoadExternalLibrary: {}", m_LuaPath.string().c_str());

	return IsLuaSafe(in_pLuaState, luaL_dofile(in_pLuaState, m_LuaPath.string().c_str()));
}

static int print(lua_State* in_pLuaState)
{
	auto argCount = lua_gettop(in_pLuaState);

	for (auto i = 1; i <= argCount; i++)
		std::cout << lua_tostring(in_pLuaState, i);

	std::cout << std::endl;

	return 0;
}

luaL_Reg LuaSystem::m_Functions[] =
{
	{ "print", print },
	{ NULL, NULL }
};
