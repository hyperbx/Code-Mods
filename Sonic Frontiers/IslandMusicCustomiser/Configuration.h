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

	static const char* s_bgmList[36];

	static void Read();

	static EBgmType s_kronosBgmType;

	static EBgmType s_aresBgmType;

	static EBgmType s_chaosBgmType;

	static EBgmType s_rheaBgmType;

	static EBgmType s_ouranosBgmType;

	static EBgmRandomType s_kronosBgmRandomType;

	static EBgmRandomType s_aresBgmRandomType;

	static EBgmRandomType s_chaosBgmRandomType;

	static EBgmRandomType s_rheaBgmRandomType;

	static EBgmRandomType s_ouranosBgmRandomType;

	static std::string s_exclusionList;

	static std::vector<Configuration::EBgmType> s_excludedBgm;
};