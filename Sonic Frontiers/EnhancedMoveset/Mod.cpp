EXPORT void Init(ModInfo* in_modInfo)
{
	Configuration::StartWatcher(std::string(in_modInfo->CurrentMod->Path));

	Player::Install();
	Reflection::Install();
}