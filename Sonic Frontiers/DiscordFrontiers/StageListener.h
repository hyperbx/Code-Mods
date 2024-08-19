#pragma once

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
	inline static bool IsLazyUpdate = false;

	static void Init();
	static void Update();
	static void Commit(std::string in_stageId);

	static std::string GetLocalisedStageID(std::string in_stageId)
	{
		if (m_stageMap.find(in_stageId) == m_stageMap.end())
			return "unknown";

		return m_stageMap[in_stageId];
	}
};

CL_SCAN_SIGNATURE(m_SigUIMainMenuStateLoadListUpdate, 0x140AA0C20, "\x40\x55\x53\x56\x48\x8D\x6C\x24\xB9\x48\x81\xEC\x90\x00\x00\x00\x80\x79", "xxxxxxxxxxxxxxxxxx");