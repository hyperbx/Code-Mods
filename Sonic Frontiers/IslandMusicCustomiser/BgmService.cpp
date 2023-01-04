Configuration::EBgmType BgmService::m_bgmStack[];

HOOK(void, __fastcall, SetIslandBgm, 0x14C1A3750, app::snd::BgmIdExtension* in_pBgmIdExtension, int64_t a2, const char** out_ppMusicId)
{
	originalSetIslandBgm(in_pBgmIdExtension, a2, out_ppMusicId);

	Configuration::EBgmType bgmType = Configuration::bgm_none;

	if (StringHelper::ContainsSubstring(*out_ppMusicId, "w1r02"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_KronosBgmType, Configuration::s_KronosBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w2r01"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_AresBgmType, Configuration::s_AresBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w3r01"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_ChaosBgmType, Configuration::s_ChaosBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w1r05"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_RheaBgmType, Configuration::s_RheaBgmRandomType);
	}
	else if (StringHelper::ContainsSubstring(*out_ppMusicId, "w1r04"))
	{
		bgmType = BgmService::GetBgmType(Configuration::s_OuranosBgmType, Configuration::s_OuranosBgmRandomType);
	}

#if _DEBUG
	printf("[IslandMusicRandomiser] Index: %d\n", bgmType);
#endif

	if (bgmType != Configuration::bgm_none)
		*out_ppMusicId = Configuration::s_BgmList[bgmType];
}

void BgmService::Install()
{
	// Fill array with -1 to prevent zero being identified as a duplicate.
	std::fill_n(m_bgmStack, 8, Configuration::EBgmType::bgm_none);

	INSTALL_HOOK(SetIslandBgm);
}