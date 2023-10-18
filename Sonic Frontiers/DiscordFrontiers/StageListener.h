#pragma once

#define CACHE_URL "https://raw.githubusercontent.com/Big-Endian-32/Networking/main/Sonic%20Frontiers/Discord%20Frontiers/.cache/{}.png"

class StageListener
{
private:
	inline static std::unordered_map<std::string, std::string> m_stageMap =
	{
		{ "w1r03", "DetailsLocationKronos"  },
		{ "w2r01", "DetailsLocationAres"    },
		{ "w3r01", "DetailsLocationChaos"   },
		{ "w1r05", "DetailsLocationRhea"    },
		{ "w1r04", "DetailsLocationOuranos" },
		{ "w1r06", "DetailsLocationOuranos" }
	};

public:
	static void Update();
	static void Commit(std::string in_stageId);

	static std::string GetLocalisedStageID(std::string in_stageId)
	{
		if (m_stageMap.find(in_stageId) == m_stageMap.end())
			return "unknown";

		return m_stageMap[in_stageId];
	}
};