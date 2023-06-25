typedef int (app::ScriptSequence::* SequenceFuncPtr)(lua_State*);

#define PUSH_LUA_LIB(in_pLuaState, in_pLibName, in_function) \
	luaL_requiref(in_pLuaState, in_pLibName, in_function, 1); \
	lua_pop(in_pLuaState, 1);

CL_SCAN_SIGNATURE(m_SigRegisterLuaCallback, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xF9\x48\x8B\xCA", "xxxxxxxxxxxxxxxxxxxxx");

HOOK(void, __fastcall, RegisterLuaCallback, m_SigRegisterLuaCallback(), app::ScriptSequence* in_pThis, app::game::Script* in_pScript)
{
	originalRegisterLuaCallback(in_pThis, in_pScript);

	auto* luaWrapper = in_pScript->GetLuaWrapper();
	auto* pLuaState = luaWrapper->pLuaState;

	if (pLuaState != LUA_OK)
	{
		auto result = lua_tostring(pLuaState, -1);

		if (result != nullptr)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			fprintf(stderr, "[Lua] %s\n", result);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}

	PUSH_LUA_LIB(pLuaState, "", luaopen_base);
	PUSH_LUA_LIB(pLuaState, LUA_COLIBNAME, luaopen_coroutine);
	PUSH_LUA_LIB(pLuaState, LUA_TABLIBNAME, luaopen_table);
	PUSH_LUA_LIB(pLuaState, LUA_STRLIBNAME, luaopen_string);
	PUSH_LUA_LIB(pLuaState, LUA_UTF8LIBNAME, luaopen_utf8);
	PUSH_LUA_LIB(pLuaState, LUA_MATHLIBNAME, luaopen_math);
	PUSH_LUA_LIB(pLuaState, LUA_DBLIBNAME, luaopen_debug);
	PUSH_LUA_LIB(pLuaState, LUA_LOADLIBNAME, luaopen_package);
	PUSH_LUA_LIB(pLuaState, LUA_IOLIBNAME, luaopen_io);

	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::IsPlayerInCombat)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::GetCurrentAnimationName)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::GetPhantomRushGauge)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::SetPhantomRushGauge)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::GetQuickCyloopGauge)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::SetQuickCyloopGauge)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::GetDeltaTime)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::CreateTimer)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::DestroyTimer)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::GetTimer)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::SetTimer)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&ScriptSequenceExtras::GetTime)>();
}

CL_SCAN_SIGNATURE(m_SigSetLifeGaugeVisibility, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x81\xEC\x80\x00\x00\x00\x0F\xB6", "xxxxxxxxxxxxxxxxxxxxxxxxx");

HOOK(uint64_t, __fastcall, SetLifeGaugeVisibility, m_SigSetLifeGaugeVisibility(), int64_t a1, char in_showHealth)
{
	ScriptSequenceExtras::s_IsPlayerInCombat = in_showHealth == 1;

	return originalSetLifeGaugeVisibility(a1, in_showHealth);
}

CL_SCAN_SIGNATURE(m_SigChangeAnimation, "\x40\x53\x48\x83\xEC\x20\xF6\x81\x78\x01\x00\x00\x10\x48\x8B\xDA", "xxxxxxxxxxxxxxxx");

HOOK(int64_t, __fastcall, ChangeAnimation, m_SigChangeAnimation(), int64_t a1, const char* in_pAnimationName, char a3)
{
	ScriptSequenceExtras::s_pAnimationName = in_pAnimationName;

	return originalChangeAnimation(a1, in_pAnimationName, a3);
}

CL_SCAN_SIGNATURE(m_SigFrameLimiter, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x50\xF3", "xxxxxxxxxxxxxxxx");

HOOK(float, __fastcall, FrameLimiter, m_SigFrameLimiter(), int64_t a1, char a2)
{
	ScriptSequenceExtras::s_Framerate = *(float*)(a1 + 0x14);

	if (!ScriptSequenceExtras::s_timers.empty())
	{
		for (auto& t : ScriptSequenceExtras::s_timers)
		{
			auto& timer = ScriptSequenceExtras::s_timers[t.first];

			if (timer.m_IsRunning)
				timer.m_Time += 1.0f / ScriptSequenceExtras::s_Framerate;
		}
	}

	return originalFrameLimiter(a1, a2);
}

CL_SCAN_SIGNATURE(m_SigSetTime, "\xF3\x0F\x10\x44\x24\x28\xF3\x0F\x58\x41\x0C", "xxxxxxxxxxx");

HOOK(int64_t, __fastcall, SetTime, m_SigSetTime(), Time* in_time, int in_days, int in_hours, int in_minutes, float in_seconds)
{
	if (in_time)
		ScriptSequenceExtras::s_pTime = in_time;

	return originalSetTime(in_time, in_days, in_hours, in_minutes, in_seconds);
}

void ScriptSequenceExtras::Install()
{
	INSTALL_HOOK(RegisterLuaCallback);
	INSTALL_HOOK(SetLifeGaugeVisibility);
	INSTALL_HOOK(ChangeAnimation);
	INSTALL_HOOK(FrameLimiter);
	INSTALL_HOOK(SetTime);
}