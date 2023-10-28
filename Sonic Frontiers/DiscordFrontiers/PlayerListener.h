#pragma once

class PlayerListener
{
private:
	static inline std::unordered_map<uint8_t, std::string> m_playerImageKeyMap =
	{
		{ 0, "sonic"    },
		{ 1, "amy"      },
		{ 2, "knuckles" },
		{ 3, "tails"    }
	};

	static inline std::unordered_map<uint8_t, std::string> m_playerNameMap =
	{
		{ 0, "PlayerSonic"    },
		{ 1, "PlayerAmy"      },
		{ 2, "PlayerKnuckles" },
		{ 3, "PlayerTails"    }
	};

public:
	static inline bool IsSuperSonic2 = false;

	static void Init();
	static void Commit();

	static bool IsSuper(hh::game::GameObject* in_pPlayer = nullptr)
	{
		if (!in_pPlayer)
		{
			auto pGameManager = hh::game::GameManager::GetSingleton();

			if (!pGameManager)
				return false;

			in_pPlayer = pGameManager->GetGameObject<app::player::Sonic>();

			if (!in_pPlayer)
				return false;
		}

		auto pGOCPlayerBlackboard = in_pPlayer->GetGOC<app::player::GOCPlayerBlackboard>();

		if (!pGOCPlayerBlackboard)
			return false;

		auto pBlackboard = pGOCPlayerBlackboard->pBlackboard;

		if (!pBlackboard)
			return false;

		auto pBlackboardStatus = pBlackboard->GetBlackboardContent<app::player::BlackboardStatus>();

		if (!pBlackboardStatus)
			return false;

		return pBlackboardStatus->IsSuper;
	}

	static int GetCharacterIndex()
	{
		auto pGameManager = hh::game::GameManager::GetSingleton();

		if (!pGameManager)
			return 0;

		auto pLevelInfo = pGameManager->GetService<app::level::LevelInfo>();

		if (!pLevelInfo)
			return 0;

		return pLevelInfo->GetPlayerInformation()->CharacterIndex;
	}

	static std::string GetCharacterImageKey()
	{
		int idx = GetCharacterIndex();

		if (idx == 0 && IsSuper())
			return IsSuperSonic2 ? "supersonic2" : "supersonic";

		return m_playerImageKeyMap[idx];
	}

	static std::string GetCharacterName()
	{
		int idx = GetCharacterIndex();

		if (idx == 0 && IsSuper())
			return "PlayerSuperSonic";

		return m_playerNameMap[GetCharacterIndex()];
	}
};

CL_SCAN_SIGNATURE(m_SigPlayerCtor, 0x14AC7B060, "\x40\x53\x48\x83\xEC\x20\x48\x89\xCB\xE8\xCC\xCC\xCC\xCC\x48\x8D\x05\xCC\xCC\xCC\xCC\x48\x8D\x8B\x50", "xxxxxxxxxx????xxx????xxxx");
CL_SCAN_SIGNATURE(m_SigChangePlayerVisualToSuperSonic, 0x1409DDB80, "\x40\x53\x48\x83\xEC\x30\x80\xB9\x18", "xxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigChangePlayerVisualToSuperSonic2, 0x1409DD9F0, "\x40\x56\x48\x83\xEC\x30\x80\xB9\x18", "xxxxxxxxx");