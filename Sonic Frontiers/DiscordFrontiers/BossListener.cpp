HOOK(void*, __fastcall, StatePluginBossBattleCtor, m_SigStatePluginBossBattleCtor(), void* a1, int64_t a2)
{
	if (StringHelper::Compare(GameModeListener::Island, "w1r03"))
	{
		BossListener::Update("vs. Giganto");
	}
	else if (StringHelper::Compare(GameModeListener::Island, "w2r01"))
	{
		BossListener::Update("vs. Wyvern");
	}
	else if (StringHelper::Compare(GameModeListener::Island, "w3r01"))
	{
		BossListener::Update("vs. Knight");
	}
	else if (StringHelper::Compare(GameModeListener::Island, "w1r04"))
	{
		BossListener::Update("vs. Supreme");
	}

	return originalStatePluginBossBattleCtor(a1, a2);
}

void BossListener::Update(std::string in_state)
{
#if _DEBUG
	printf("[Discord Frontiers] Boss: %s\n", in_state.c_str());
#endif

	Discord::Update
	(
		in_state,
		Discord::Details,
		Discord::LargeImageKey,
		Discord::SmallImageKey,
		TimeHelper::GetSystemEpoch()
	);
}

void BossListener::Install()
{
	INSTALL_HOOK(StatePluginBossBattleCtor);
}