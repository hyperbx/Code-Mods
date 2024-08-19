#pragma once

class PlayerListener
{
private:
	inline static std::tuple<std::string, std::string> m_currentSource = { "unknown_small", "DetailsLocationUnknown" };

	inline static std::string m_defaultImageKeys[6] =
	{
		"sonic",
		"amy",
		"knuckles",
		"tails",
		"supersonic",
		"supersonic2"
	};

	inline static std::string m_characterImageSourceKeys[4] =
	{
		"SonicURL",
		"AmyURL",
		"KnucklesURL",
		"TailsURL"
	};

	inline static std::string m_characterNameSourceKeys[4] =
	{
		"SonicName",
		"AmyName",
		"KnucklesName",
		"TailsName"
	};

public:
	inline static std::unordered_map<std::string, std::string> CharacterInfoMap =
	{				      
		{ "SonicURL",        "sonic"             },
		{ "SonicName",       "PlayerSonic"       },
		{ "AmyURL",          "amy"               },
		{ "AmyName",         "PlayerAmy"         },
		{ "KnucklesURL",     "knuckles"          },
		{ "KnucklesName",    "PlayerKnuckles"    },
		{ "TailsURL",        "tails"             },
		{ "TailsName",       "PlayerTails"       },
		{ "SuperSonicURL",   "supersonic"        },
		{ "SuperSonicName",  "PlayerSuperSonic"  },
		{ "SuperSonic2URL",  "supersonic2"       },
		{ "SuperSonic2Name", "PlayerSuperSonic2" }
	};

	inline static bool IsSuperSonic2 = false;

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

	static std::tuple<std::string, std::string> GetCharacterImageSource()
	{
		auto idx = GetCharacterIndex();

		auto imageSourceKey = m_characterImageSourceKeys[idx];
		auto nameSourceKey = m_characterNameSourceKeys[idx];

		if (idx == 0 && IsSuper())
		{
			imageSourceKey = IsSuperSonic2
				? "SuperSonic2URL"
				: "SuperSonicURL";

			nameSourceKey = IsSuperSonic2
				? "SuperSonic2Name"
				: "SuperSonicName";
		}

		auto name = CharacterInfoMap[nameSourceKey];

		// Don't reload resources from the internet if the current source is identical.
		if (std::get<0>(m_currentSource) == imageSourceKey && std::get<1>(m_currentSource) == name)
			return m_currentSource;

		for (int i = 0; i < 6; i++)
		{
			// Check if image key is default and return it if so.
			if (m_defaultImageKeys[i] == CharacterInfoMap[imageSourceKey])
				return std::make_tuple(m_defaultImageKeys[i], name);
		}

		return m_currentSource = Discord::GetCustomImageSource(CharacterInfoMap, imageSourceKey, name, true);
	}

	static std::string GetCharacterImageKey()
	{
		return std::get<0>(GetCharacterImageSource());
	}

	static std::string GetCharacterName()
	{
		return std::get<1>(GetCharacterImageSource());
	}
};

CL_SCAN_SIGNATURE(m_SigPlayerCtor, 0x14AC7B060, "\x40\x53\x48\x83\xEC\x20\x48\x89\xCB\xE8\xCC\xCC\xCC\xCC\x48\x8D\x05\xCC\xCC\xCC\xCC\x48\x8D\x8B\x50", "xxxxxxxxxx????xxx????xxxx");
CL_SCAN_SIGNATURE(m_SigChangePlayerVisualToSuperSonic, 0x1409DDB80, "\x40\x53\x48\x83\xEC\x30\x80\xB9\x18", "xxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigChangePlayerVisualToSuperSonic2, 0x1409DD9F0, "\x40\x56\x48\x83\xEC\x30\x80\xB9\x18", "xxxxxxxxx");