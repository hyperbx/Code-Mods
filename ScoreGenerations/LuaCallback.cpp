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
	PushExposedInteger(L, "totalRingCount", StatisticsListener::stats.totalRingCount);
	PushExposedInteger(L, "totalEnemies", StatisticsListener::stats.totalEnemies);
	PushExposedInteger(L, "totalPhysics", StatisticsListener::stats.totalPhysics);
	PushExposedInteger(L, "totalPointMarkers", StatisticsListener::stats.totalPointMarkers);
	PushExposedInteger(L, "totalRedRings", StatisticsListener::stats.totalRedRings);
	PushExposedInteger(L, "totalRainbowRings", StatisticsListener::stats.totalRainbowRings);
	PushExposedInteger(L, "totalItemBoxes", StatisticsListener::stats.totalItemBoxes);
	PushExposedInteger(L, "totalSuperRings", StatisticsListener::stats.totalSuperRings);
	PushExposedInteger(L, "totalTricks", StatisticsListener::stats.totalTricks);
	PushExposedInteger(L, "totalDashRings", StatisticsListener::stats.totalDashRings);
	PushExposedInteger(L, "totalQuickSteps", StatisticsListener::stats.totalQuickSteps);
	PushExposedInteger(L, "totalDrifts", StatisticsListener::stats.totalDrifts);
	PushExposedInteger(L, "totalBalloons", StatisticsListener::stats.totalBalloons);
	PushExposedInteger(L, "totalVelocity", StatisticsListener::stats.totalVelocity);
	PushExposedInteger(L, "ringCount", StatisticsListener::stats.ringCount);
	PushExposedInteger(L, "minutes", StatisticsListener::stats.minutes);
	PushExposedInteger(L, "seconds", StatisticsListener::stats.seconds);
	PushExposedInteger(L, "elapsedTime", StatisticsListener::GetElapsedTime());
	PushExposedInteger(L, "score", ScoreListener::score);
	PushExposedInteger(L, "scoreLimit", Configuration::scoreLimit);
	PushExposedInteger(L, "minSeconds", Tables::rankTables[StateHooks::stageID].minSeconds);
	PushExposedInteger(L, "maxSeconds", Tables::rankTables[StateHooks::stageID].maxSeconds);

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

bool LuaCallback::LoadMathLibrary(lua_State* L)
{
	// Load Lua libraries.
	luaL_openlibs(L);

	// Try loading the external library.
	if (IsLuaSafe(L, luaL_dofile(L, "Math.lua")))
		return true;

	if (Configuration::debugLua)
		printf("[Score Generations] [Lua Debug] Failed to load the math library!\n");

	return false;
}

bool LuaCallback::LoadExternalLibrary(lua_State* L)
{
	// Get global variable.
	lua_getglobal(L, "_G");

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
		printf("[Score Generations] [Lua Debug] totalRingCount = %d\n", StatisticsListener::stats.totalRingCount);
		printf("[Score Generations] [Lua Debug] totalEnemies = %d\n", StatisticsListener::stats.totalEnemies);
		printf("[Score Generations] [Lua Debug] totalPhysics = %d\n", StatisticsListener::stats.totalPhysics);
		printf("[Score Generations] [Lua Debug] totalPointMarkers = %d\n", StatisticsListener::stats.totalPointMarkers);
		printf("[Score Generations] [Lua Debug] totalRedRings = %d\n", StatisticsListener::stats.totalRedRings);
		printf("[Score Generations] [Lua Debug] totalRainbowRings = %d\n", StatisticsListener::stats.totalRainbowRings);
		printf("[Score Generations] [Lua Debug] totalItemBoxes = %d\n", StatisticsListener::stats.totalItemBoxes);
		printf("[Score Generations] [Lua Debug] totalSuperRings = %d\n", StatisticsListener::stats.totalSuperRings);
		printf("[Score Generations] [Lua Debug] totalTricks = %d\n", StatisticsListener::stats.totalTricks);
		printf("[Score Generations] [Lua Debug] totalDashRings = %d\n", StatisticsListener::stats.totalDashRings);
		printf("[Score Generations] [Lua Debug] totalQuickSteps = %d\n", StatisticsListener::stats.totalQuickSteps);
		printf("[Score Generations] [Lua Debug] totalDrifts = %d\n", StatisticsListener::stats.totalDrifts);
		printf("[Score Generations] [Lua Debug] totalBalloons = %d\n", StatisticsListener::stats.totalBalloons);
		printf("[Score Generations] [Lua Debug] totalVelocity = %d\n", StatisticsListener::stats.totalVelocity);
		printf("[Score Generations] [Lua Debug] ringCount = %d\n", StatisticsListener::stats.ringCount);
		printf("[Score Generations] [Lua Debug] minutes = %d\n", StatisticsListener::stats.minutes);
		printf("[Score Generations] [Lua Debug] seconds = %d\n", StatisticsListener::stats.seconds);
		printf("[Score Generations] [Lua Debug] elapsedTime = %d\n", StatisticsListener::GetElapsedTime());
		printf("[Score Generations] [Lua Debug] score = %d\n", ScoreListener::score);
		printf("[Score Generations] [Lua Debug] scoreLimit = %d\n", Configuration::scoreLimit);
		printf("[Score Generations] [Lua Debug] minSeconds = %d\n", Tables::rankTables[StateHooks::stageID].minSeconds);
		printf("[Score Generations] [Lua Debug] maxSeconds = %d\n", Tables::rankTables[StateHooks::stageID].maxSeconds);
		printf("[Score Generations] [Lua Debug] stageID = %s\n", StateHooks::stageID);
	}
}

int LuaCallback::GetBonus(string algorithm)
{
	// Create Lua virtual machine.
	lua_State* L = luaL_newstate();

	// Try loading the math library.
	if (!LoadMathLibrary(L))
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