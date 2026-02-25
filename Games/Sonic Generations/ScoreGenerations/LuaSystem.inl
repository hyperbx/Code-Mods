namespace ScoreGenerations
{
	template <typename T>
	inline T LuaSystem::RunExpression(const std::string& in_rCode)
	{
		auto result = T();
		auto pLuaState = luaL_newstate();

		if (!LoadInternalLibrary(pLuaState) || !LoadExternalLibrary(pLuaState))
			return result;

		PushVariables(pLuaState);

		if (IsLuaSafe(pLuaState, luaL_dostring(pLuaState, ("return " + in_rCode).c_str())))
		{
			if constexpr (std::is_integral_v<T> || std::is_same_v<T, float> || std::is_same_v<T, double>)
			{
				result = static_cast<T>(lua_tonumber(pLuaState, -1));

				LOGFN_UTILITY("{} = {}", in_rCode.c_str(), result);
			}
			else
			{
				LOGFN_UTILITY("Unknown Lua return type.");
			}
		}

		lua_close(pLuaState);

		return result;
	}
}
