typedef int (app::ScriptSequence::* SequenceFuncPtr)(lua_State*);

SIGNATURE_SCAN
(
	m_sigRegisterLuaCallback,

	0x14087EF20,

	"\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xF9\x48\x8B\xCA", "xxxxxxxxxxxxxxxxxxxxx"
);

HOOK(void, __fastcall, RegisterLuaCallback, m_sigRegisterLuaCallback(), app::ScriptSequence* in_pThis, app::game::Script* in_pScript)
{
	originalRegisterLuaCallback(in_pThis, in_pScript);

	auto* luaWrapper = in_pScript->GetLuaWrapper();

	if (luaWrapper->pLuaState != LUA_OK)
	{
		auto result = lua_tostring(luaWrapper->pLuaState, -1);

		if (result != nullptr)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			fprintf(stderr, "[Lua] %s\n", result);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}

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
}

SIGNATURE_SCAN
(
	m_sigSetLifeGaugeVisibility,

	0x1404FC490,

	"\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x81\xEC\x80\x00\x00\x00\x0F\xB6", "xxxxxxxxxxxxxxxxxxxxxxxxx"
);

HOOK(uint64_t, __fastcall, SetLifeGaugeVisibility, m_sigSetLifeGaugeVisibility(), int64_t a1, char in_showHealth)
{
	ScriptSequenceExtras::s_IsPlayerInCombat = in_showHealth == 1;

	return originalSetLifeGaugeVisibility(a1, in_showHealth);
}

SIGNATURE_SCAN
(
	m_sigChangeAnimation,

	0x1407A7710,

	"\x40\x53\x48\x83\xEC\x20\x48\x8B\xDA\x41\x80", "xxxxxxxxxxx"
);

HOOK(int64_t, __fastcall, ChangeAnimation, m_sigChangeAnimation(), int64_t a1, const char* in_animationName, char a3)
{
	ScriptSequenceExtras::s_pAnimationName = in_animationName;

	return originalChangeAnimation(a1, in_animationName, a3);
}

SIGNATURE_SCAN
(
	m_sigFrameLimiter,

	0x140BB9ED0,

	"\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x50\xF3", "xxxxxxxxxxxxxxxx"
);

HOOK(float, __fastcall, FrameLimiter, m_sigFrameLimiter(), int64_t a1, char a2)
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

void ScriptSequenceExtras::Install()
{
	INSTALL_HOOK(RegisterLuaCallback);
	INSTALL_HOOK(SetLifeGaugeVisibility);
	INSTALL_HOOK(ChangeAnimation);
	INSTALL_HOOK(FrameLimiter);
}