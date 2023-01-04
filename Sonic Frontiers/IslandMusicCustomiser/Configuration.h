#pragma once

#define INI_FILE "IslandMusicCustomiser.ini"

class Configuration
{
public:
	static enum EBgmType : int
	{
		bgm_none = -1,
		bgm_ending1,
		bgm_ending2,
		bgm_enemy,
		bgm_hacking,
		bgm_maintheme,
		bgm_oneokrock,
		bgm_pinball,
		bgm_quest_00,
		bgm_quest_02,
		bgm_quest_05,
		bgm_sys_arcademode,
		bgm_talk_kodama,
		bgm_w1r02_1,
		bgm_w1r02_2,
		bgm_w1r02_3,
		bgm_w1r02_4,
		bgm_w1r02_5,
		bgm_w1r02_6,
		bgm_w1r02_7,
		bgm_w1r04_1,
		bgm_w1r04_4,
		bgm_w1r05,
		bgm_w2r01_1,
		bgm_w2r01_2,
		bgm_w2r01_3,
		bgm_w2r01_4,
		bgm_w2r01_5,
		bgm_w2r01_6,
		bgm_w2r01_7,
		bgm_w3r01_1,
		bgm_w3r01_2,
		bgm_w3r01_3,
		bgm_w3r01_4,
		bgm_w3r01_5,
		bgm_w3r01_6,
		bgm_w3r01_7
	};

	static enum EBgmRandomType : int
	{
		None,
		Any,
		IslandAny,
		KronosAny,
		AresAny,
		ChaosAny
	};

	static const char* s_BgmList[36];

	static void Read();

	static EBgmType s_KronosBgmType;

	static EBgmType s_AresBgmType;

	static EBgmType s_ChaosBgmType;

	static EBgmType s_RheaBgmType;

	static EBgmType s_OuranosBgmType;

	static EBgmRandomType s_KronosBgmRandomType;

	static EBgmRandomType s_AresBgmRandomType;

	static EBgmRandomType s_ChaosBgmRandomType;

	static EBgmRandomType s_RheaBgmRandomType;

	static EBgmRandomType s_OuranosBgmRandomType;

	static std::string s_ExclusionList;

	static std::vector<Configuration::EBgmType> s_ExcludedBgm;
};