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
	PushExposedUnsignedInteger(L, "secondsForA", ScoreListener::rankTable.secondsForA);
	PushExposedUnsignedInteger(L, "secondsForC", ScoreListener::rankTable.secondsForC);
}

void LuaCallback::PushExposedUnsignedInteger(lua_State* L, string name, unsigned int pushToStack)
{
	// Push the input value to the stack.
	lua_pushnumber(L, pushToStack);

	// Set the current stack value to the name of the variable.
	lua_setglobal(L, name.c_str());
}

bool LuaCallback::LoadExternalLibrary(lua_State* L)
{
	// Load Lua libraries.
	luaL_openlibs(L);

	// Try loading the external library.
	if (IsLuaSafe(L, luaL_dofile(L, LUA_FILE)))
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

	// Try loading the external library.
	if (!LoadExternalLibrary(L))
		return 0;

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