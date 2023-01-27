extern "C" _declspec(dllexport) void Init(ModInfo* in_modInfo)
{
	Configuration::Read();

#if _DEBUG
	printf("[Discord Frontiers] Language: %s\n", Configuration::Language.c_str());
#endif

	LanguageHelper::Read(StringHelper::GetSubstringBeforeLastChar(in_modInfo->CurrentMod->Path, '\\').append(std::format("\\Languages\\{}.json", Configuration::Language)));
}

extern "C" _declspec(dllexport) void PostInit()
{
	Discord::Initialise();

	BossListener::Install();
	GameModeListener::Install();
}