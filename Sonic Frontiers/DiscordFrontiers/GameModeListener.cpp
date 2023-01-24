HOOK(void*, __fastcall, GameModeTitleCtor, m_SigGameModeTitleCtor(), void* a1, int64_t a2, int64_t a3)
{
	Discord::Update("Main Menu", "", "default", "", 0);

	return originalGameModeTitleCtor(a1, a2, a3);
}

HOOK(void*, __fastcall, GameModeTutorialCtor, m_SigGameModeTutorialCtor(), void* a1, int64_t a2, int64_t a3)
{
	Discord::Update("Training Simulator", "", "training", "default", TimeHelper::GetSystemEpoch());

	return originalGameModeTutorialCtor(a1, a2, a3);
}

HOOK(void*, __fastcall, GameModeFishingCtor, m_SigGameModeFishingCtor(), void* a1, int64_t a2, int64_t a3)
{
	Discord::Update("Fishing", Discord::Details, Discord::LargeImageKey, Discord::SmallImageKey, TimeHelper::GetSystemEpoch());

	return originalGameModeFishingCtor(a1, a2, a3);
}

HOOK(void*, __fastcall, GameModeHackingCtor, m_SigGameModeHackingCtor(), void* a1, int64_t a2, int64_t a3)
{
	if (StringHelper::Compare(GameModeListener::Island, "w5r01"))
	{
		Discord::Update("vs. The End", "", GameModeListener::Island, Discord::SmallImageKey, TimeHelper::GetSystemEpoch());
	}
	else
	{
		Discord::Update("Hacking", "", "hacking", "default", TimeHelper::GetSystemEpoch());
	}

	return originalGameModeHackingCtor(a1, a2, a3);
}

HOOK(void*, __fastcall, GameModeStageCtor, m_SigGameModeStageCtor(), void* a1, int64_t a2, int64_t a3)
{
	GameModeListener::Update(GameModeListener::Island);

	return originalGameModeStageCtor(a1, a2, a3);
}

HOOK(void*, __fastcall, GameModeCyberStageCtor, m_SigGameModeCyberStageCtor(), void* a1, int64_t a2, int64_t a3)
{
	GameModeListener::Update(GameModeListener::Stage, true);

	return originalGameModeCyberStageCtor(a1, a2, a3);
}

HOOK(void*, __fastcall, GameModeStaffRollCtor, m_SigGameModeStaffRollCtor(), void* a1, int64_t a2, int64_t a3)
{
	Discord::Update("Credits", "", "default", "", 0);

	return originalGameModeStaffRollCtor(a1, a2, a3);
}

HOOK(int64_t, __fastcall, GameModeStageUpdate, m_SigGameModeStageUpdate(), int64_t a1, int64_t a2, int* a3)
{
	auto worldId = (const char*)(a1 + 0xA0);

	if
	(
		worldId && !StringHelper::Compare(worldId, "w1f01") &&

		/* It'd be nice if std::vector just had a .contains() function. */
		std::find(GameModeListener::Islands.begin(), GameModeListener::Islands.end(), std::string(worldId).substr(0, 2)) != GameModeListener::Islands.end()
	)
	{
		GameModeListener::Island = worldId;
	}

	Discord::State = "Exploring";

	return originalGameModeStageUpdate(a1, a2, a3);
}

HOOK(int64_t, __fastcall, GameModeCyberStageUpdate, m_SigGameModeCyberStageUpdate(), int64_t a1, int64_t a2, int* a3)
{
	GameModeListener::Stage = (const char*)(a1 + 0xA0);

	return originalGameModeCyberStageUpdate(a1, a2, a3);
}

HOOK(char, __fastcall, GameModeCyberStageRetryFromMenuInit, m_SigGameModeCyberStageRetryFromMenuInit(), int64_t a1, int64_t a2)
{
	Discord::ResetTime();

	return originalGameModeCyberStageRetryFromMenuInit(a1, a2);
}

void GameModeListener::Update(std::string in_stageId, bool in_isCyberSpace)
{
#if _DEBUG
	printf("[Discord Frontiers] World: %s\n", in_stageId.c_str());
#endif

	auto name = GetNameFromStageId(in_stageId);

	if (in_isCyberSpace)
	{
		Discord::Update
		(
			name == "unknown" ? "Unknown" : name,
			"Cyber Space",
			name == "unknown" ? name : in_stageId,
			"default",
			TimeHelper::GetSystemEpoch()
		);
	}
	else
	{
		Discord::Update
		(
			Discord::State,
			name == "unknown" ? "Unknown" : name,
			name == "unknown" ? name : in_stageId,
			"default",
			TimeHelper::GetSystemEpoch()
		);
	}
}

void GameModeListener::Install()
{
	INSTALL_HOOK(GameModeTitleCtor);
	INSTALL_HOOK(GameModeTutorialCtor);
	INSTALL_HOOK(GameModeFishingCtor);
	INSTALL_HOOK(GameModeHackingCtor);
	INSTALL_HOOK(GameModeStageCtor);
	INSTALL_HOOK(GameModeCyberStageCtor);
	INSTALL_HOOK(GameModeStaffRollCtor);
	INSTALL_HOOK(GameModeStageUpdate);
	INSTALL_HOOK(GameModeCyberStageUpdate);
	INSTALL_HOOK(GameModeCyberStageRetryFromMenuInit);
}