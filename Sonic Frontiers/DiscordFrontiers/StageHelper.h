#pragma once

#define IS_ATTRIBUTE_FLAG(in_flag) \
	(StageHelper::GetCurrentStageData() != nullptr && (StageHelper::GetCurrentStageData()->AttributeFlags & (1L << (int)app::level::StageData::in_flag)) != 0)

class StageHelper
{
public:
	enum EIsland
	{
		EIsland_Unknown = -1,
		EIsland_Kronos,
		EIsland_Ares,
		EIsland_Chaos,
		EIsland_Rhea,
		EIsland_Ouranos
	};

public:
	static app::level::StageData* GetCurrentStageData();
	static std::string GetCurrentStageID();

	static EIsland GetCurrentIsland()
	{
		EIsland result = EIsland_Unknown;

		auto stage = GetCurrentStageID();

		if (stage == "w1r03" || stage == "w1b01")
		{
			result = EIsland_Kronos;
		}
		else if (stage == "w2r01" || stage == "w2b01")
		{
			result = EIsland_Ares;
		}
		else if (stage == "w3r01" || stage == "w3b01")
		{
			result = EIsland_Chaos;
		}
		else if (stage == "w1r05")
		{
			result = EIsland_Rhea;
		}
		else if (stage == "w1r04" || stage == "w1r06" || stage == "w1b02")
		{
			result = EIsland_Ouranos;
		}

		return result;
	}
};

