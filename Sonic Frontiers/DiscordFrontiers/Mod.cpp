EXPORT void Init(ModInfo* in_modInfo)
{
	Configuration::Read();

#if _DEBUG
	printf("[Discord Frontiers] Language: %s\n", Configuration::Language.c_str());
#endif

	LanguageHelper::Read(StringHelper::GetSubstringBeforeLastChar(in_modInfo->CurrentMod->Path, '\\').append(std::format("\\Languages\\{}.json", Configuration::Language)));
}

EXPORT void PostInit()
{
	Discord::Init();
	BattleRushListener::Init();
	BossListener::Init();
	GameModeListener::Init();
	PlayerListener::Init();
}

EXPORT void OnFrame()
{
	StageListener::Update();
}