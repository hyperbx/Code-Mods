Configuration::EBgmType Configuration::s_kronosBgmType  = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_aresBgmType    = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_chaosBgmType   = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_rheaBgmType    = Configuration::EBgmType::bgm_none;
Configuration::EBgmType Configuration::s_ouranosBgmType = Configuration::EBgmType::bgm_none;

Configuration::EBgmRandomType Configuration::s_kronosBgmRandomType  = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_aresBgmRandomType    = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_chaosBgmRandomType   = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_rheaBgmRandomType    = Configuration::EBgmRandomType::None;
Configuration::EBgmRandomType Configuration::s_ouranosBgmRandomType = Configuration::EBgmRandomType::None;

std::string Configuration::s_exclusionList;

std::vector<Configuration::EBgmType> Configuration::s_excludedBgm;

const char* Configuration::s_bgmList[] =
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
	Configuration::s_kronosBgmType  = (Configuration::EBgmType)reader.GetInteger("Music", "kronosBgmType",  s_kronosBgmType);
	Configuration::s_aresBgmType    = (Configuration::EBgmType)reader.GetInteger("Music", "aresBgmType",    s_aresBgmType);
	Configuration::s_chaosBgmType   = (Configuration::EBgmType)reader.GetInteger("Music", "chaosBgmType",   s_chaosBgmType);
	Configuration::s_rheaBgmType    = (Configuration::EBgmType)reader.GetInteger("Music", "rheaBgmType",    s_rheaBgmType);
	Configuration::s_ouranosBgmType = (Configuration::EBgmType)reader.GetInteger("Music", "ouranosBgmType", s_ouranosBgmType);

	// Random
	Configuration::s_kronosBgmRandomType  = (Configuration::EBgmRandomType)reader.GetInteger("Random", "kronosBgmRandomType",  s_kronosBgmRandomType);
	Configuration::s_aresBgmRandomType    = (Configuration::EBgmRandomType)reader.GetInteger("Random", "aresBgmRandomType",    s_aresBgmRandomType);
	Configuration::s_chaosBgmRandomType   = (Configuration::EBgmRandomType)reader.GetInteger("Random", "chaosBgmRandomType",   s_chaosBgmRandomType);
	Configuration::s_rheaBgmRandomType    = (Configuration::EBgmRandomType)reader.GetInteger("Random", "rheaBgmRandomType",    s_rheaBgmRandomType);
	Configuration::s_ouranosBgmRandomType = (Configuration::EBgmRandomType)reader.GetInteger("Random", "ouranosBgmRandomType", s_ouranosBgmRandomType);
	Configuration::s_exclusionList        = reader.Get("Random", "exclusionList", s_exclusionList);

	// Populate exclusion list.
	for (auto& str : StringHelper::GetCommaSeparatedStrings(Configuration::s_exclusionList))
		s_excludedBgm.push_back((Configuration::EBgmType)stoi(str));

#if _DEBUG
	for (int i = 0; i < s_excludedBgm.size(); i++)
		printf("[IslandMusicCustomiser] s_excludedBgm[%d]: %d\n", i, s_excludedBgm[i]);
#endif
}