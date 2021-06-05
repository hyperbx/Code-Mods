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
	// Push needed exposed variables to the stack.
	PushExposedUnsignedInteger(L, "totalRingCount", StatisticsListener::totalRingCount);
	PushExposedUnsignedInteger(L, "totalVelocity", StatisticsListener::totalVelocity);
	PushExposedUnsignedInteger(L, "ringCount", StatisticsListener::ringCount);
	PushExposedUnsignedInteger(L, "minutes", StatisticsListener::minutes);
	PushExposedUnsignedInteger(L, "seconds", StatisticsListener::seconds);
	PushExposedUnsignedInteger(L, "elapsedTime", StatisticsListener::GetElapsedTime());
	PushExposedUnsignedInteger(L, "score", ScoreListener::score);
	PushExposedUnsignedInteger(L, "scoreLimit", Configuration::scoreLimit);
	PushExposedUnsignedInteger(L, "minSeconds", ResultListener::rankTables[StateHooks::stageID].minSeconds);
	PushExposedUnsignedInteger(L, "maxSeconds", ResultListener::rankTables[StateHooks::stageID].maxSeconds);
}

void LuaCallback::PushExposedUnsignedInteger(lua_State* L, string name, unsigned int pushToStack)
{
	// Push the input value to the stack.
	lua_pushnumber(L, pushToStack);

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
		printf("[Score Generations] [Lua Debug] totalRingCount = %d\n", StatisticsListener::totalRingCount);
		printf("[Score Generations] [Lua Debug] totalVelocity = %d\n", StatisticsListener::totalVelocity);
		printf("[Score Generations] [Lua Debug] ringCount = %d\n", StatisticsListener::ringCount);
		printf("[Score Generations] [Lua Debug] minutes = %d\n", StatisticsListener::minutes);
		printf("[Score Generations] [Lua Debug] seconds = %d\n", StatisticsListener::seconds);
		printf("[Score Generations] [Lua Debug] elapsedTime = %d\n", StatisticsListener::GetElapsedTime());
		printf("[Score Generations] [Lua Debug] score = %d\n", ScoreListener::score);
		printf("[Score Generations] [Lua Debug] scoreLimit = %d\n", Configuration::scoreLimit);
		printf("[Score Generations] [Lua Debug] minSeconds = %d\n", ResultListener::rankTables[StateHooks::stageID].minSeconds);
		printf("[Score Generations] [Lua Debug] maxSeconds = %d\n", ResultListener::rankTables[StateHooks::stageID].maxSeconds);
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
		int result = (unsigned int)lua_tonumber(L, -1);

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