#pragma once

class MasterTrialListener
{
private:
	static inline std::unordered_map<std::string, std::string> m_trialMap =
	{
		{ "w5t02", "DetailsLocationMasterTrialDragon" },
		{ "w5t03", "DetailsLocationMasterTrialSnake"  },
		{ "w5t04", "DetailsLocationMasterTrialTiger"  },
		{ "w5t05", "DetailsLocationMasterTrialCrane"  }
	};

public:
	static inline bool IsBossRush = false;

	static void CommitBossRush(std::string in_stageId)
	{
		Discord::CommitDetails(LanguageHelper::Localise("DetailsLocationMasterTrialKing"));
		Discord::CommitSmallImage("sonic");

		if (in_stageId == "w1t01")
		{
			Discord::CommitState(LanguageHelper::Localise("StateBossGiganto"));
			Discord::CommitLargeImage("giganto");
		}
		else if (in_stageId == "w2t01")
		{
			Discord::CommitState(LanguageHelper::Localise("StateBossWyvern"));
			Discord::CommitLargeImage("wyvern");
		}
		else if (in_stageId == "w3t01")
		{
			Discord::CommitState(LanguageHelper::Localise("StateBossKnight"));
			Discord::CommitLargeImage("knight");
		}
	}

	static void CommitMasterTrial(std::string in_stageId)
	{
		std::string state = "DetailsLocationUnknown";

		if (in_stageId == "w5t02")
		{
			state = "StateEnemySoldier";
		}
		else if (in_stageId == "w5t03")
		{
			state = "StateEnemyShell";
		}
		else if (in_stageId == "w5t04")
		{
			state = "StateEnemyWolf";
		}
		else if (in_stageId == "w5t05")
		{
			state = "StateGuardianNinja";
		}

		Discord::Commit
		(
			LanguageHelper::Localise(state),
			LanguageHelper::Localise(m_trialMap[in_stageId]),
			in_stageId,
			"sonic",
			TimeHelper::GetSystemEpoch()
		);
	}
};