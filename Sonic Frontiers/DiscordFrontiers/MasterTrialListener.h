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
		Discord::CommitDetails("DetailsLocationMasterTrialKing");
		Discord::CommitSmallImage("sonic");

		if (in_stageId == "w1t01")
		{
			Discord::CommitState("StateBossGiganto");
			Discord::CommitLargeImage("giganto");
			Discord::CommitLargeImageText("StateBossGiganto");
		}
		else if (in_stageId == "w2t01")
		{
			Discord::CommitState("StateBossWyvern");
			Discord::CommitLargeImage("wyvern");
			Discord::CommitLargeImageText("StateBossWyvern");
		}
		else if (in_stageId == "w3t01")
		{
			Discord::CommitState("StateBossKnight");
			Discord::CommitLargeImage("knight");
			Discord::CommitLargeImageText("StateBossKnight");
		}
	}

	static void CommitMasterTrial(std::string in_stageId)
	{
		std::string state = "DetailsLocationUnknown";
		std::string details = m_trialMap[in_stageId];

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

		Discord::Commit(state, details, in_stageId, details, "sonic", "PlayerSonic", TimeHelper::GetSystemEpoch());
	}
};