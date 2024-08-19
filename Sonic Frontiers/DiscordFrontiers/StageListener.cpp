std::string m_lastStageID = "";

HOOK(bool, __fastcall, UIMainMenuStateLoadListUpdate, m_SigUIMainMenuStateLoadListUpdate(), int64_t in_pThis, int* a2)
{
	bool result = originalUIMainMenuStateLoadListUpdate(in_pThis, a2);

	if (result)
		StageListener::IsLazyUpdate = true;

	return result;
}

void StageListener::Init()
{
	INSTALL_HOOK(UIMainMenuStateLoadListUpdate);
}

void StageListener::Update()
{
	auto currentStageID = StageHelper::GetCurrentStageID();

	if (m_lastStageID != currentStageID)
	{
		m_lastStageID = currentStageID;

		if (m_lastStageID.empty())
			return;

		IsLazyUpdate = true;
	}

	if (!IsLazyUpdate)
		return;

	// The stage has changed during Battle Rush, assume playing all islands.
	if (BattleRushListener::IsBattleRush)
	{
		BattleRushListener::IsBattleRushAll = true;

#if _DEBUG
		printf("[Discord Frontiers] Playing all islands in Battle Rush?\n");
#endif
	}

	Commit(currentStageID);

	IsLazyUpdate = false;
}

void StageListener::Commit(std::string in_stageId)
{
#if _DEBUG
	printf("[Discord Frontiers] World: %s\n", in_stageId.c_str());
#endif

	BossListener::IsBoss = false;
	MasterTrialListener::IsBossRush = false;

	auto pStageData = StageHelper::GetCurrentStageData();

	if (!pStageData)
	{
		printf("[Discord Frontiers] Cannot retrieve info about current stage.\n");
		printf("[Discord Frontiers] Error: app::level::StageData returned nullptr...\n");
		return;
	}

	if (IS_ATTRIBUTE_FLAG(eAttributeFlags_BattleRush))
	{
		BattleRushListener::IsBattleRush = true;
		BattleRushListener::Phase = 0;
		BattleRushListener::PhaseAll = 0;
		return;
	}

	if (IS_ATTRIBUTE_FLAG(eAttributeFlags_BossRush))
	{
		MasterTrialListener::IsBossRush = true;
		MasterTrialListener::CommitBossRush(in_stageId);
		return;
	}
	
	if (IS_ATTRIBUTE_FLAG(eAttributeFlags_Cyber))
	{
		auto name = std::string(pStageData->CyberName.begin(), pStageData->CyberName.end());

		/* This assumes a custom stage has set a unique "cyber_name" string.
		   Otherwise, this will default to regular Cyber Space. */
		bool isCustomStage = name[1] != '-';

		std::string location = isCustomStage
			? "DetailsLocationCustomStage"
			: "DetailsGameModeCyberStage";

		if (GameModeListener::IsCyberSpaceChallenge)
			location = "DetailsGameModeCyberStageChallenge";

		auto imgSrc = Discord::GetCustomImageSource(CustomStageMap, in_stageId, name);

		Discord::Commit
		(
			name,

			location,

			isCustomStage ? std::get<0>(imgSrc) : StringHelper::ToLower(name),
			isCustomStage ? std::get<1>(imgSrc) : name,

			PlayerListener::GetCharacterImageKey(),
			PlayerListener::GetCharacterName(),
			
			GameModeListener::IsCyberSpaceChallenge
				? Discord::StartTime
				: TimeHelper::GetSystemEpoch()
		);
	}
	else if (IS_ATTRIBUTE_FLAG(eAttributeFlags_Minigame))
	{
		Discord::CommitState("StateGameModeFishing");
		Discord::ResetTime();
	}
	else if (IS_ATTRIBUTE_FLAG(eAttributeFlags_Hacking))
	{
		if (IS_ATTRIBUTE_FLAG(eAttributeFlags_LastBoss))
		{
			Discord::Commit("StateBossTheEnd", "", "w5r01", "StateBossTheEnd", "supersonic", "PlayerSuperSonic", TimeHelper::GetSystemEpoch());
		}
		else
		{
			Discord::Commit("StateGameModeHacking", "", "hacking", "StateGameModeHacking", "sonic", "PlayerSonic", TimeHelper::GetSystemEpoch());
		}
	}
	else if (IS_ATTRIBUTE_FLAG(eAttributeFlags_MasterTrial))
	{
		MasterTrialListener::CommitMasterTrial(in_stageId);
	}
	else if (IS_ATTRIBUTE_FLAG(eAttributeFlags_Tutorial))
	{
		Discord::Commit("StateGameModeTutorial", "", "training", "StateGameModeTutorial", "sonic", "PlayerSonic", TimeHelper::GetSystemEpoch());
	}
	else
	{
		auto name = GetLocalisedStageID(in_stageId);

		if (name == "unknown")
		{
			Discord::Commit
			(
				"",

				"DetailsLocationUnknown",

				"unknown",
				"DetailsLocationUnknown",

				PlayerListener::GetCharacterImageKey(),
				PlayerListener::GetCharacterName(),

				TimeHelper::GetSystemEpoch()
			);
		}
		else
		{
			Discord::Commit
			(
				Discord::State,

				name,

				StringHelper::ToLower(in_stageId),
				name,

				PlayerListener::GetCharacterImageKey(),
				PlayerListener::GetCharacterName(),

				TimeHelper::GetSystemEpoch()
			);
		}
	}
}