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

void LuaCallback::PushExposedData(lua_State* L)
{
	// Push needed exposed integers to the stack.
	PushExposedInteger(L, "totalRingCount", StatisticsListener::totals.totalRingCount);
	PushExposedInteger(L, "totalEnemies", StatisticsListener::totals.totalEnemies);
	PushExposedInteger(L, "totalPhysics", StatisticsListener::totals.totalPhysics);
	PushExposedInteger(L, "totalPointMarkers", StatisticsListener::totals.totalPointMarkers);
	PushExposedInteger(L, "totalRedRings", StatisticsListener::totals.totalRedRings);
	PushExposedInteger(L, "totalRainbowRings", StatisticsListener::totals.totalRainbowRings);
	PushExposedInteger(L, "totalItemBoxes", StatisticsListener::totals.totalItemBoxes);
	PushExposedInteger(L, "totalSuperRings", StatisticsListener::totals.totalSuperRings);
	PushExposedInteger(L, "totalTricks", StatisticsListener::totals.totalTricks);
	PushExposedInteger(L, "totalDashRings", StatisticsListener::totals.totalDashRings);
	PushExposedInteger(L, "totalQuickSteps", StatisticsListener::totals.totalQuickSteps);
	PushExposedInteger(L, "totalDrifts", StatisticsListener::totals.totalDrifts);
	PushExposedInteger(L, "totalBalloons", StatisticsListener::totals.totalBalloons);
	PushExposedInteger(L, "totalVelocity", StatisticsListener::totals.totalVelocity);
	PushExposedInteger(L, "ringCount", StatisticsListener::totals.ringCount);
	PushExposedInteger(L, "minutes", StatisticsListener::totals.minutes);
	PushExposedInteger(L, "seconds", StatisticsListener::totals.seconds);
	PushExposedInteger(L, "elapsedTime", StatisticsListener::GetElapsedTime());
	PushExposedInteger(L, "score", ScoreListener::score);
	PushExposedInteger(L, "scoreLimit", Configuration::scoreLimit);
	PushExposedInteger(L, "minSeconds", TableListener::rankTables[StateHooks::stageID].minSeconds);
	PushExposedInteger(L, "maxSeconds", TableListener::rankTables[StateHooks::stageID].maxSeconds);

	// Push needed exposed strings to the stack.
	PushExposedString(L, "stageID", StateHooks::stageID);
}

void LuaCallback::PushExposedInteger(lua_State* L, string name, unsigned int pushToStack)
{
	// Push the input value to the stack.
	lua_pushnumber(L, pushToStack);

	// Set the current stack value to the name of the variable.
	lua_setglobal(L, name.c_str());
}

void LuaCallback::PushExposedString(lua_State* L, string name, string value)
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

	string lib = Configuration::GetConfigDirectory() + "\\" + LUA_FILE;

	/* If the mod overriding the configuration doesn't have a Lua script,
	   then just use the one provided in Score Generations. */
	if (!IOHelper::FileExists(lib))
	{
		lib = LUA_FILE;

		if (Configuration::debugLua)
			printf("[Score Generations] [Lua Debug] The overridden mod doesn't have a Lua script - reverting to default script...\n");
	}

	// Try loading the external library.
	if (IsLuaSafe(L, luaL_dofile(L, lib.c_str())))
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
		printf("[Score Generations] [Lua Debug] totalVelocity = %d\n", StatisticsListener::totals.totalVelocity);
		printf("[Score Generations] [Lua Debug] ringCount = %d\n", StatisticsListener::totals.ringCount);
		printf("[Score Generations] [Lua Debug] minutes = %d\n", StatisticsListener::totals.minutes);
		printf("[Score Generations] [Lua Debug] seconds = %d\n", StatisticsListener::totals.seconds);
		printf("[Score Generations] [Lua Debug] elapsedTime = %d\n", StatisticsListener::GetElapsedTime());
		printf("[Score Generations] [Lua Debug] score = %d\n", ScoreListener::score);
		printf("[Score Generations] [Lua Debug] scoreLimit = %d\n", Configuration::scoreLimit);
		printf("[Score Generations] [Lua Debug] minSeconds = %d\n", TableListener::rankTables[StateHooks::stageID].minSeconds);
		printf("[Score Generations] [Lua Debug] maxSeconds = %d\n", TableListener::rankTables[StateHooks::stageID].maxSeconds);
		printf("[Score Generations] [Lua Debug] stageID = %s\n", StateHooks::stageID);
	}
}

int LuaCallback::RunAlgorithm(string algorithm)
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
	if (IsLuaSafe(L, luaL_dostring(L, string("return " + algorithm).c_str())))
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