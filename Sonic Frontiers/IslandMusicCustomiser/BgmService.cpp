Configuration::EBgmType BgmService::ms_lastBgmType;

SIG_SCAN
(
	m_sigSetIslandBgm,

	/* 0x14C1A3750 */
	"\x48\x85\xD2\x0F\x84\x46\x01\x00\x00\x48\x89\xE0",
	"xxxxxxxxxxxx"
);

HOOK(void, __fastcall, SetIslandBgm, m_sigSetIslandBgm(), app::snd::BgmIdExtension* in_pBgmIdExtension, int64_t a2, const char** out_ppMusicId)
{
	originalSetIslandBgm(in_pBgmIdExtension, a2, out_ppMusicId);

	Configuration::EBgmType bgmType = Configuration::bgm_none;

	if (StringHelper::ContainsSubstring(*out_ppMusicId, "w1r02"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_kronosBgmType, Configuration::s_kronosBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w2r01"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_aresBgmType, Configuration::s_aresBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w3r01"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_chaosBgmType, Configuration::s_chaosBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w1r05"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_rheaBgmType, Configuration::s_rheaBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w1r04"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_ouranosBgmType, Configuration::s_ouranosBgmRandomType);
	}

#if _DEBUG
	printf("[IslandMusicCustomiser] Index: %d\n", bgmType);
#endif

	if (bgmType != Configuration::bgm_none)
		*out_ppMusicId = Configuration::s_bgmList[bgmType];
}

void BgmService::Install()
{
	INSTALL_HOOK(SetIslandBgm);
}