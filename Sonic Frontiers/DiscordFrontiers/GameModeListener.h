#pragma once

class GameModeListener
{
public:
	inline static std::unordered_map<std::string, std::string> Worlds =
	{
		{ "w1r03", "LocationKronos" },
		{ "w2r01", "LocationAres" },
		{ "w3r01", "LocationChaos" },
		{ "w1r05", "LocationRhea" },
		{ "w1r04", "LocationOuranos" },
		{ "w6d01", "1-1" },
		{ "w8d01", "1-2" },
		{ "w9d04", "1-3" },
		{ "w6d02", "1-4" },
		{ "w7d04", "1-5" },
		{ "w6d06", "1-6" },
		{ "w9d06", "1-7" },
		{ "w6d05", "2-1" },
		{ "w8d03", "2-2" },
		{ "w7d02", "2-3" },
		{ "w7d06", "2-4" },
		{ "w8d04", "2-5" },
		{ "w6d03", "2-6" },
		{ "w8d05", "2-7" },
		{ "w6d04", "3-1" },
		{ "w6d08", "3-2" },
		{ "w8d02", "3-3" },
		{ "w6d09", "3-4" },
		{ "w6d07", "3-5" },
		{ "w8d06", "3-6" },
		{ "w7d03", "3-7" },
		{ "w7d08", "4-1" },
		{ "w9d02", "4-2" },
		{ "w7d01", "4-3" },
		{ "w9d03", "4-4" },
		{ "w6d10", "4-5" },
		{ "w7d07", "4-6" },
		{ "w9d05", "4-7" },
		{ "w7d05", "4-8" },
		{ "w9d07", "4-9" }
	};

	inline static std::vector<std::string> Islands =
	{
		"w1",
		"w2",
		"w3",
		"w5"
	};

	inline static std::string Island;
	inline static std::string Stage;

	static void Install();

	static void Update(std::string in_stageId, bool in_isCyberSpace = false);

	static std::string GetNameFromStageId(std::string in_stageId)
	{
		if (Worlds.find(in_stageId) == Worlds.end())
			return "unknown";

		return Worlds[in_stageId];
	}
};

CL_SCAN_SIGNATURE(m_SigGameModeTitleCtor, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x49\x8B\xD8\x48\x8B\xF2\x48\x8B\xF9\xE8\xCC\xCC\xCC\xCC\x48\x8D", "xxxxxxxxxxxxxxxxxxxxxxxxx????xx");
CL_SCAN_SIGNATURE(m_SigGameModeTutorialCtor, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x20\x4C\x89\xC3\x48\x89\xD7\x48\x89\xCE\xE8\xCC\xCC\xCC\xCC\x48\x8D\x05\xCC\xCC\xCC\xCC\x41\xB8\x10\x00\x00\x00\x48\x89\x06\x48\x8D\x8E\xF8", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGameModeFishingCtor, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x49\x8B\xD8\x48\x8B\xF9\xE8\xCC\xCC\xCC\xCC\x48\x8D\x05\xCC\xCC\xCC\xCC\x41", "xxxxxxxxxxxxxxxxx????xxx????x");
CL_SCAN_SIGNATURE(m_SigGameModeHackingCtor, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x49\x8B\xD8\x48\x8B\xFA\x48\x8B\xF1\xE8\xCC\xCC\xCC\xCC\x48\x8D", "xxxxxxxxxxxxxxxxxxxxxxxxx????xx");
CL_SCAN_SIGNATURE(m_SigGameModeStageCtor, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x20\x4C\x89\xC3\x48\x89\xD7\x48\x89\xCE\xE8\xCC\xCC\xCC\xCC\x48\x8D\x05\xCC\xCC\xCC\xCC\x41\xB8\x10\x00\x00\x00\x48\x89\x06\x48\x8D\x8E\x60", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGameModeCyberStageCtor, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x4C\x89\xC3\x48\x89\xD7\x48\x89\xCE\xE8\xCC\xCC\xCC\xCC\x48", "xxxxxxxxxxxxxxxxxxxxxxxxx????x");
CL_SCAN_SIGNATURE(m_SigGameModeStaffRollCtor, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x49\x8B\xD8\x48\x8B\xF9\xE8\xCC\xCC\xCC\xCC\x48\x8D\x05\xCC\xCC\xCC\xCC\x48\x89", "xxxxxxxxxxxxxxxxx????xxx????xx");
CL_SCAN_SIGNATURE(m_SigGameModeStageUpdate, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x4C\x89\x74\x24\x20\x55\x48\x8D\xAC\x24\x20\xFE", "xxxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGameModeCyberStageUpdate, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\xFF\xFF\xFF\x48\x81\xEC\x00\x02\x00\x00\x41", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGameModeCyberStageRetryFromMenuInit, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x30\x48\x89\xD7\xBA", "xxxxxxxxxxxxxx");