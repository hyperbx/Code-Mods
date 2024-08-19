EXPORT void Init(ModInfo* in_pModInfo)
{
	Configuration::Read();

#if _DEBUG
	printf("[Discord Frontiers] Language: %s\n", Configuration::Language.c_str());
#endif

	LanguageHelper::Read(StringHelper::GetSubstringBeforeLastChar(in_pModInfo->CurrentMod->Path, '\\').append(std::format("\\Languages\\{}.json", Configuration::Language)));
}

EXPORT void PostInit(ModInfo* in_pModInfo)
{
	Configuration::ReadMods(in_pModInfo);
	Discord::Init();
	BattleRushListener::Init();
	BossListener::Init();
	GameModeListener::Init();
	PlayerListener::Init();
	StageListener::Init();
}

EXPORT void OnFrame()
{
	StageListener::Update();
}