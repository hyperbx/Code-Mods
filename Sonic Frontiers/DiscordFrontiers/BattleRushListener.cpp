HOOK(void, __fastcall, GameModeBattleRushExtensionProcessMessage, m_SigGameModeBattleRushExtensionProcessMessage(), int64_t in_pThis, int a2)
{
	auto pGameManager = hh::game::GameManager::GetSingleton();

	if (!pGameManager)
		return originalGameModeBattleRushExtensionProcessMessage(in_pThis, a2);

	auto pChallengeTimeManager = pGameManager->GetService<app::level::ChallengeTimeManager>();

	if (!pChallengeTimeManager)
		return originalGameModeBattleRushExtensionProcessMessage(in_pThis, a2);

	BattleRushListener::Phase = pChallengeTimeManager->ChallengePhase;

#if _DEBUG
	printf("[Discord Frontiers] Phase: %d\n", BattleRushListener::Phase);
#endif

	Discord::Commit
	(
		BattleRushListener::GetStatus(),
		LanguageHelper::Localise("DetailsGameModeBattleRush"),
		BattleRushListener::GetLargeImageKey(),
		PlayerListener::GetCharacterName(),

		(BattleRushListener::IsBattleRushAll || BattleRushListener::Phase > 0)
			? Discord::StartTime
			: TimeHelper::GetSystemEpoch()
	);

	return originalGameModeBattleRushExtensionProcessMessage(in_pThis, a2);
}

void BattleRushListener::Init()
{
	INSTALL_HOOK(GameModeBattleRushExtensionProcessMessage);
}