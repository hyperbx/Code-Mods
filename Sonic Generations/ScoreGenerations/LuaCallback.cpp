std::string LuaCallback::LuaPath = LUA_FILE;

const struct luaL_Reg LuaCallback::Functions[] =
{
	{ "print", LuaCallback::print },
	{ NULL, NULL }
};

bool IsLuaSafe(lua_State* L, int result)
{
	/* LUA_OK implies everything was successful,
	   we use that to check if the current state is safe. */
	if (result != LUA_OK)
	{
		if (Configuration::debugLua)
			printf("[Score Generations] [Lua Debug] Lua error: %s\n", lua_tostring(L, -1));

		return false;
	}

	return true;
}

bool LuaCallback::SetLuaPath(std::string path)
{
	if (!IOHelper::FileExists(path))
		return false;

	// Set new active Lua path.
	LuaPath = path;

	return true;
}

void LuaCallback::PushExposedData(lua_State* L)
{
	// Push needed exposed integers to the stack.
	PushExposedNumber<int>(L, "totalRingCount", StatisticsListener::totals.totalRingCount);
	PushExposedNumber<int>(L, "totalEnemies", StatisticsListener::totals.totalEnemies);
	PushExposedNumber<int>(L, "totalPhysics", StatisticsListener::totals.totalPhysics);
	PushExposedNumber<int>(L, "totalPointMarkers", StatisticsListener::totals.totalPointMarkers);
	PushExposedNumber<int>(L, "totalRedRings", StatisticsListener::totals.totalRedRings);
	PushExposedNumber<int>(L, "totalRainbowRings", StatisticsListener::totals.totalRainbowRings);
	PushExposedNumber<int>(L, "totalItemBoxes", StatisticsListener::totals.totalItemBoxes);
	PushExposedNumber<int>(L, "totalSuperRings", StatisticsListener::totals.totalSuperRings);
	PushExposedNumber<int>(L, "totalTricks", StatisticsListener::totals.totalTricks);
	PushExposedNumber<int>(L, "totalDashRings", StatisticsListener::totals.totalDashRings);
	PushExposedNumber<int>(L, "totalQuickSteps", StatisticsListener::totals.totalQuickSteps);
	PushExposedNumber<int>(L, "totalDrifts", StatisticsListener::totals.totalDrifts);
	PushExposedNumber<int>(L, "totalBalloons", StatisticsListener::totals.totalBalloons);
	PushExposedNumber<float>(L, "totalVelocity", StatisticsListener::totals.totalVelocity);
	PushExposedNumber<float>(L, "maxVelocity", StatisticsListener::totals.maxVelocity);
	PushExposedNumber<int>(L, "ringCount", StatisticsListener::totals.ringCount);
	PushExposedNumber<float>(L, "elapsedTime", StatisticsListener::totals.elapsedTime);
	PushExposedNumber<int>(L, "minutes", StatisticsListener::totals.minutes);
	PushExposedNumber<int>(L, "seconds", StatisticsListener::totals.seconds);
	PushExposedNumber<int>(L, "milliseconds", StatisticsListener::totals.milliseconds);
	PushExposedNumber<int>(L, "score", ScoreListener::score);
	PushExposedNumber<int>(L, "scoreLimit", Configuration::scoreLimit);
	PushExposedNumber<int>(L, "minSeconds", TableListener::rankTables[BlueBlurCommon::GetStageID()].minSeconds);
	PushExposedNumber<int>(L, "maxSeconds", TableListener::rankTables[BlueBlurCommon::GetStageID()].maxSeconds);

	// Push needed exposed strings to the stack.
	PushExposedString(L, "stageID", BlueBlurCommon::GetStageID());
}
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type*>
void LuaCallback::PushExposedNumber(lua_State* L, std::string name, T pushToStack)
{
	// Push the input value to the stack.
	lua_pushnumber(L, pushToStack);

	// Set the current stack value to the name of the variable.
	lua_setglobal(L, name.c_str());
}

void LuaCallback::PushExposedString(lua_State* L, std::string name, std::string value)
{
	// Push the input value to the stack.
	lua_pushstring(L, value.c_str());

	// Set the current stack value to the name of the variable.
	lua_setglobal(L, name.c_str());
}

void LuaCallback::PushLuaLibrary(lua_State* L, const char* name, lua_CFunction function)
{
	// Load Lua function to require.
	luaL_requiref(L, name, function, 1);

	// Pop function from stack.
	lua_pop(L, 1);
}

bool LuaCallback::LoadInternalLibrary(lua_State* L)
{
	// Load Lua libraries.
	PushLuaLibrary(L, "", luaopen_base);
	PushLuaLibrary(L, LUA_LOADLIBNAME, luaopen_package);
	PushLuaLibrary(L, LUA_TABLIBNAME, luaopen_table);
	PushLuaLibrary(L, LUA_STRLIBNAME, luaopen_string);
	PushLuaLibrary(L, LUA_MATHLIBNAME, luaopen_math);

	// Try loading the internal math library.
	if (IsLuaSafe(L, luaL_dofile(L, "Math.lua")))
		return true;

	if (Configuration::debugLua)
		printf("[Score Generations] [Lua Debug] Failed to load the math library!\n");

	return false;
}

bool LuaCallback::LoadExternalLibrary(lua_State* L)
{
	// Get global variable.
	lua_getglobal(L, LUA_GNAME);

	// Load C++ callback functions.
	luaL_setfuncs(L, Functions, 0);

	// Try loading the external library.
	if (IsLuaSafe(L, luaL_dofile(L, LuaPath.c_str())))
		return true;

	if (Configuration::debugLua)
		printf("[Score Generations] [Lua Debug] Failed to load the external library!\n");

	return false;
}

void LuaCallback::PrintExposedData()
{
	if (Configuration::debugLua)
	{
		printf("[Score Generations] [Lua Debug] totalRingCount = %d\n", StatisticsListener::totals.totalRingCount);
		printf("[Score Generations] [Lua Debug] totalEnemies = %d\n", StatisticsListener::totals.totalEnemies);
		printf("[Score Generations] [Lua Debug] totalPhysics = %d\n", StatisticsListener::totals.totalPhysics);
		printf("[Score Generations] [Lua Debug] totalPointMarkers = %d\n", StatisticsListener::totals.totalPointMarkers);
		printf("[Score Generations] [Lua Debug] totalRedRings = %d\n", StatisticsListener::totals.totalRedRings);
		printf("[Score Generations] [Lua Debug] totalRainbowRings = %d\n", StatisticsListener::totals.totalRainbowRings);
		printf("[Score Generations] [Lua Debug] totalItemBoxes = %d\n", StatisticsListener::totals.totalItemBoxes);
		printf("[Score Generations] [Lua Debug] totalSuperRings = %d\n", StatisticsListener::totals.totalSuperRings);
		printf("[Score Generations] [Lua Debug] totalTricks = %d\n", StatisticsListener::totals.totalTricks);
		printf("[Score Generations] [Lua Debug] totalDashRings = %d\n", StatisticsListener::totals.totalDashRings);
		printf("[Score Generations] [Lua Debug] totalQuickSteps = %d\n", StatisticsListener::totals.totalQuickSteps);
		printf("[Score Generations] [Lua Debug] totalDrifts = %d\n", StatisticsListener::totals.totalDrifts);
		printf("[Score Generations] [Lua Debug] totalBalloons = %d\n", StatisticsListener::totals.totalBalloons);
		printf("[Score Generations] [Lua Debug] totalVelocity = %f\n", StatisticsListener::totals.totalVelocity);
		printf("[Score Generations] [Lua Debug] maxVelocity = %f\n", StatisticsListener::totals.maxVelocity);
		printf("[Score Generations] [Lua Debug] ringCount = %d\n", StatisticsListener::totals.ringCount);
		printf("[Score Generations] [Lua Debug] elapsedTime = %f\n", StatisticsListener::totals.elapsedTime);
		printf("[Score Generations] [Lua Debug] minutes = %d\n", StatisticsListener::totals.minutes);
		printf("[Score Generations] [Lua Debug] seconds = %d\n", StatisticsListener::totals.seconds);
		printf("[Score Generations] [Lua Debug] milliseconds = %d\n", StatisticsListener::totals.milliseconds);
		printf("[Score Generations] [Lua Debug] score = %d\n", ScoreListener::score);
		printf("[Score Generations] [Lua Debug] scoreLimit = %d\n", Configuration::scoreLimit);
		printf("[Score Generations] [Lua Debug] minSeconds = %d\n", TableListener::rankTables[BlueBlurCommon::GetStageID()].minSeconds);
		printf("[Score Generations] [Lua Debug] maxSeconds = %d\n", TableListener::rankTables[BlueBlurCommon::GetStageID()].maxSeconds);
		printf("[Score Generations] [Lua Debug] stageID = %s\n", BlueBlurCommon::GetStageID());
	}
}

int LuaCallback::RunAlgorithm(std::string algorithm)
{
	// Create Lua virtual machine.
	lua_State* L = luaL_newstate();

	// Try loading the internal libraries.
	if (!LoadInternalLibrary(L))
		return 0;

	// Try loading the external library.
	LoadExternalLibrary(L);

	// Get needed exposed variables.
	PushExposedData(L);

	// Try running the in-line Lua script.
	if (IsLuaSafe(L, luaL_dostring(L, std::string("return " + algorithm).c_str())))
	{
		// Return and store the Lua result.
		int result = lua_tonumber(L, -1);

		if (Configuration::debugLua)
			printf("[Score Generations] [Lua Debug] %s = %d\n", algorithm.c_str(), result);

		// Clean up the Lua virtual machine.
		lua_close(L);

		return result;
	}

	// Clean up the Lua virtual machine.
	lua_close(L);

	return 0;
}