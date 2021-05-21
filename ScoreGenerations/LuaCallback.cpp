bool IsLuaSafe(lua_State* L, int result)
{
	/* LUA_OK implies everything was successful,
	   we use that to check if the current state is safe. */
	if (result != LUA_OK)
	{
		printf("[Score Generations] Lua error: %s\n", lua_tostring(L, -1));

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
	PushExposedUnsignedInteger(L, "minSeconds", ScoreListener::rankTable.minSeconds);
	PushExposedUnsignedInteger(L, "maxSeconds", ScoreListener::rankTable.maxSeconds);
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

#if _DEBUG
	printf("[Score Generations] Failed to load the math library!\n");
#endif

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

#if _DEBUG
		printf("[Score Generations] The overridden mod doesn't have a Lua script - reverting to default script...\n");
#endif
	}

	// Try loading the external library.
	if (IsLuaSafe(L, luaL_dofile(L, lib.c_str())))
		return true;

#if _DEBUG
	printf("[Score Generations] Failed to load the external library!\n");
#endif

	return false;
}

unsigned int LuaCallback::GetBonus(string algorithm)
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
		unsigned int result = (unsigned int)lua_tonumber(L, -1);

#if _DEBUG
		printf("[Score Generations] %s = %d\n", algorithm.c_str(), result);
#endif

		// Clean up the Lua virtual machine.
		lua_close(L);

		return result;
	}

	// Clean up the Lua virtual machine.
	lua_close(L);

	return 0;
}