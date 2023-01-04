Configuration::EBgmType Configuration::s_KronosBgmType  = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_AresBgmType    = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_ChaosBgmType   = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_RheaBgmType    = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_OuranosBgmType = Configuration::EBgmType::bgm_none;

Configuration::EBgmRandomType Configuration::s_KronosBgmRandomType  = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_AresBgmRandomType    = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_ChaosBgmRandomType   = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_RheaBgmRandomType    = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_OuranosBgmRandomType = Configuration::EBgmRandomType::None;

std::string Configuration::s_ExclusionList;

std::vector<Configuration::EBgmType> Configuration::s_ExcludedBgm;

const char* Configuration::s_BgmList[] =
{
	"bgm_ending1",
	"bgm_ending2",
	"bgm_enemy",
	"bgm_hacking",
	"bgm_maintheme",
	"bgm_oneokrock",
	"bgm_pinball",
	"bgm_quest_00",
	"bgm_quest_02",
	"bgm_quest_05",
	"bgm_sys_arcademode",
	"bgm_talk_kodama",
	"bgm_w1r02_1",
	"bgm_w1r02_2",
	"bgm_w1r02_3",
	"bgm_w1r02_4",
	"bgm_w1r02_5",
	"bgm_w1r02_6",
	"bgm_w1r02_7",
	"bgm_w1r04_1",
	"bgm_w1r04_4",
	"bgm_w1r05",
	"bgm_w2r01_1",
	"bgm_w2r01_2",
	"bgm_w2r01_3",
	"bgm_w2r01_4",
	"bgm_w2r01_5",
	"bgm_w2r01_6",
	"bgm_w2r01_7",
	"bgm_w3r01_1",
	"bgm_w3r01_2",
	"bgm_w3r01_3",
	"bgm_w3r01_4",
	"bgm_w3r01_5",
	"bgm_w3r01_6",
	"bgm_w3r01_7"
};

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// Music
	Configuration::s_KronosBgmType  = (Configuration::EBgmType)reader.GetInteger("Music", "kronosBgmType",  s_KronosBgmType);
	Configuration::s_AresBgmType    = (Configuration::EBgmType)reader.GetInteger("Music", "aresBgmType",    s_AresBgmType);
	Configuration::s_ChaosBgmType   = (Configuration::EBgmType)reader.GetInteger("Music", "chaosBgmType",   s_ChaosBgmType);
	Configuration::s_RheaBgmType    = (Configuration::EBgmType)reader.GetInteger("Music", "rheaBgmType",    s_RheaBgmType);
	Configuration::s_OuranosBgmType = (Configuration::EBgmType)reader.GetInteger("Music", "ouranosBgmType", s_OuranosBgmType);

	// Random
	Configuration::s_KronosBgmRandomType  = (Configuration::EBgmRandomType)reader.GetInteger("Random", "kronosBgmRandomType",  s_KronosBgmRandomType);
	Configuration::s_AresBgmRandomType    = (Configuration::EBgmRandomType)reader.GetInteger("Random", "aresBgmRandomType",    s_AresBgmRandomType);
	Configuration::s_ChaosBgmRandomType   = (Configuration::EBgmRandomType)reader.GetInteger("Random", "chaosBgmRandomType",   s_ChaosBgmRandomType);
	Configuration::s_RheaBgmRandomType    = (Configuration::EBgmRandomType)reader.GetInteger("Random", "rheaBgmRandomType",    s_RheaBgmRandomType);
	Configuration::s_OuranosBgmRandomType = (Configuration::EBgmRandomType)reader.GetInteger("Random", "ouranosBgmRandomType", s_OuranosBgmRandomType);
	Configuration::s_ExclusionList        = reader.Get("Random", "exclusionList", s_ExclusionList);

	// Populate exclusion list.
	for (auto& str : StringHelper::GetCommaSeparatedStrings(Configuration::s_ExclusionList))
		s_ExcludedBgm.push_back((Configuration::EBgmType)stoi(str));

#if _DEBUG
	for (int i = 0; i < s_ExcludedBgm.size(); i++)
		printf("[IslandMusicCustomiser] s_ExcludedBgm[%d]: %d\n", i, s_ExcludedBgm[i]);
#endif
}