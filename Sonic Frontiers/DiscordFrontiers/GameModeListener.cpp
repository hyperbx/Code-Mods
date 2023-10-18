bool m_isCyberSpaceChallengeTimeStarted = false;

HOOK(void*, __fastcall, GameModeTitleCtor, m_SigGameModeTitleCtor(), int64_t in_pThis, int64_t a2, int64_t a3)
{
	Discord::Commit(LanguageHelper::Localise("DetailsGameModeTitle"), "", "default", "", 0);

	BattleRushListener::IsBattleRush = false;
	GameModeListener::IsCyberSpaceChallenge = false;
	m_isCyberSpaceChallengeTimeStarted = false;

	return originalGameModeTitleCtor(in_pThis, a2, a3);
}

HOOK(int64_t, __fastcall, GameModeStageUpdate, m_SigGameModeStageUpdate(), int64_t in_pThis, int64_t a2, int* a3)
{
	// The game mode updates when switching to Super Sonic 2, for some reason.
	if (Discord::LargeImageKey == "supreme2")
		return originalGameModeStageUpdate(in_pThis, a2, a3);

	Discord::State = LanguageHelper::Localise("StateExploring");

	return originalGameModeStageUpdate(in_pThis, a2, a3);
}

HOOK(int64_t, __fastcall, GameModeCyberStageChallengeCtor, m_SigGameModeCyberStageChallengeCtor(), int64_t in_pThis, int64_t a2, int64_t a3)
{
	GameModeListener::IsCyberSpaceChallenge = true;

	if (!m_isCyberSpaceChallengeTimeStarted)
	{
		Discord::StartTime = TimeHelper::GetSystemEpoch();
		m_isCyberSpaceChallengeTimeStarted = true;
	}

	return originalGameModeCyberStageChallengeCtor(in_pThis, a2, a3);
}

HOOK(char, __fastcall, GameModeRetryFromMenuInit, m_SigGameModeRetryFromMenuInit(), int64_t in_pThis, int64_t a2)
{
	Discord::ResetTime();

	return originalGameModeRetryFromMenuInit(in_pThis, a2);
}

HOOK(int64_t, __fastcall, GameModeCyberStageChallengeRetryFromMenuInit, m_SigGameModeCyberStageChallengeRetryFromMenuInit(), int64_t in_pThis, int64_t a2)
{
	Discord::ResetTime();

	return originalGameModeCyberStageChallengeRetryFromMenuInit(in_pThis, a2);
}

HOOK(void*, __fastcall, GameModeStaffRollCtor, m_SigGameModeStaffRollCtor(), int64_t in_pThis, int64_t a2, int64_t a3)
{
	Discord::Commit(LanguageHelper::Localise("DetailsGameModeCredits"), "", "default", "", 0);

	return originalGameModeStaffRollCtor(in_pThis, a2, a3);
}

void GameModeListener::Init()
{
	INSTALL_HOOK(GameModeTitleCtor);
	INSTALL_HOOK(GameModeStageUpdate);
	INSTALL_HOOK(GameModeCyberStageChallengeCtor);
	INSTALL_HOOK(GameModeRetryFromMenuInit);
	INSTALL_HOOK(GameModeCyberStageChallengeRetryFromMenuInit);
	INSTALL_HOOK(GameModeStaffRollCtor);
}