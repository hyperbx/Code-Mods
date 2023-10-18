#pragma once

class BattleRushListener
{
private:
	inline static std::unordered_map<uint8_t, std::tuple<std::string, std::string>> m_kronosPhaseMap =
	{
		{ 0, { "StateEnemySoldier",  "w1b01_soldier" } },
		{ 1, { "StateGuardianNinja", "w1b01_ninja"   } },
		{ 2, { "StateEnemyBubble",   "w1b01_bubble"  } },
		{ 3, { "StateEnemyShell",    "w1b01_shell"   } },
		{ 4, { "StateEnemyBanger",   "w1b01_banger"  } },
		{ 5, { "StateGuardianSquid", "wxbxx_squid"   } },
		{ 6, { "StateEnemyCyclone",  "wxbxx_cyclone" } },
		{ 7, { "StateGuardianTower", "w1b01_tower"   } },
		{ 8, { "StateGuardianAsura", "w1b01_asura"   } },
		{ 9, { "StateBossGiganto",   "giganto"       } }
	};

	inline static std::unordered_map<uint8_t, std::tuple<std::string, std::string>> m_aresPhaseMap =
	{
		{ 0, { "StateEnemySoldier",    "w2b01_soldier"   } },
		{ 1, { "StateEnemyHopper",     "w2b01_hopper"    } },
		{ 2, { "StateGuardianShark",   "w2b01_shark"     } },
		{ 3, { "StateEnemySniper",     "w2b01_sniper"    } },
		{ 4, { "StateEnemyJellyfish",  "w2b01_jellyfish" } },
		{ 5, { "StateGuardianSumo",    "w2b01_sumo"      } },
		{ 6, { "StateGuardianTank",    "w2b01_tank"      } },
		{ 7, { "StateEnemyCapture",    "wxbxx_capture"   } },
		{ 8, { "StateGuardianStrider", "w2b01_strider"   } },
		{ 9, { "StateBossWyvern",      "wyvern"          } }
	};

	inline static std::unordered_map<uint8_t, std::tuple<std::string, std::string>> m_chaosPhaseMap =
	{
		{ 0, { "StateGuardianSquid",     "wxbxx_squid"     } },
		{ 1, { "StateEnemySoldier",      "w3b01_soldier"   } },
		{ 2, { "StateGuardianShinobi",   "w3b01_shinobi"   } },
		{ 3, { "StateGuardianExcavator", "w3b01_excavator" } },
		{ 4, { "StateEnemyCyclone",      "wxbxx_cyclone"   } },
		{ 5, { "StateEnemyEagle",        "w3b01_eagle"     } },
		{ 6, { "StateGuardianSpider",    "w3b01_spider"    } },
		{ 7, { "StateGuardianFortress",  "w3b01_fortress"  } },
		{ 8, { "StateBossKnight",        "knight"          } }
	};

	inline static std::unordered_map<uint8_t, std::tuple<std::string, std::string>> m_ouranosPhaseMap =
	{
		{ 0,  { "StateGuardianRedPillar",    "w1b02_redpillar"    } },
		{ 1,  { "StateEnemySoldier",         "w1b02_soldier"      } },
		{ 2,  { "StateGuardianCaterpillar",  "w1b02_caterpillar"  } },
		{ 3,  { "StateEnemyWolf",            "w1b02_wolf"         } },
		{ 4,  { "StateGuardianKunoichi",     "w1b02_kunoichi"     } },
		{ 5,  { "StateEnemyBalloon",         "w1b02_balloon"      } },
		{ 6,  { "StateGuardianSilverHammer", "w1b02_silverhammer" } },
		{ 7,  { "StateEnemyCapture",         "wxbxx_capture"      } },
		{ 8,  { "StateGuardianMasterNinja",  "w1b02_masterninja"  } },
		{ 9,  { "StateGuardianGhost",        "w1b02_ghost"        } },
		{ 10, { "StateBossSupreme",          "supreme"            } }
	};

	inline static std::unordered_map<StageHelper::EIsland, std::unordered_map<uint8_t, std::tuple<std::string, std::string>>> m_phaseMaps =
	{
		{ StageHelper::EIsland_Kronos, m_kronosPhaseMap },
		{ StageHelper::EIsland_Ares, m_aresPhaseMap },
		{ StageHelper::EIsland_Chaos, m_chaosPhaseMap },
		{ StageHelper::EIsland_Ouranos, m_ouranosPhaseMap }
	};

public:
	static inline bool IsBattleRush = false;
	static inline bool IsBattleRushAll = false;

	static inline int Phase = 0;
	static inline int PhaseAll = 0;

	static void Init();

	static int GetPhase()
	{
		auto island = StageHelper::GetCurrentIsland();

#if _DEBUG
		printf("[Discord Frontiers] Phase: %d\n", Phase);
#endif

		if (island == StageHelper::EIsland_Unknown)
			return Phase;

		if (IsBattleRushAll)
		{
			// I'm going to fucking die.
			switch (island)
			{
				case StageHelper::EIsland_Ares:
					PhaseAll = Phase - m_kronosPhaseMap.size();
					break;

				case StageHelper::EIsland_Chaos:
					PhaseAll = Phase - m_kronosPhaseMap.size() - m_aresPhaseMap.size();
					break;

				case StageHelper::EIsland_Ouranos:
					PhaseAll = Phase - m_kronosPhaseMap.size() - m_aresPhaseMap.size() - m_chaosPhaseMap.size();
					break;
			}

			PhaseAll = max(0, PhaseAll);

#if _DEBUG
			printf("[Discord Frontiers] PhaseAll: %d\n", PhaseAll);
#endif

			return PhaseAll;
		}

		return Phase;
	}

	static std::string GetStatus()
	{
		auto island = StageHelper::GetCurrentIsland();

#if _DEBUG
		printf("[Discord Frontiers] Island: %d\n", island);
#endif

		if (island == StageHelper::EIsland_Unknown)
			return "";

		return LanguageHelper::Localise(std::get<0>(m_phaseMaps[island][GetPhase()]));
	}

	static std::string GetLargeImageKey()
	{
		return std::get<1>(m_phaseMaps[StageHelper::GetCurrentIsland()][GetPhase()]);
	}
};

CL_SCAN_SIGNATURE(m_SigGameModeBattleRushExtensionProcessMessage, 0x1401C7600, "\x48\x89\x5C\x24\x18\x48\x89\x74\x24\x20\x57\x48\x81\xEC\xC0", "xxxxxxxxxxxxxxx");