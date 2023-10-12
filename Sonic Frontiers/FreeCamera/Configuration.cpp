#define INI_WRITE_SECTION(name) writer << "[" name "]" << std::endl;
#define INI_WRITE_BOOL(name) writer << #name "=" << std::boolalpha << name << std::endl;

void Configuration::Load()
{
	INIReader reader(INI_FILE);

	// General
	IsAutomaticMouseUnhook = reader.GetBoolean("General", "IsAutomaticMouseUnhook", IsAutomaticMouseUnhook);
}

void Configuration::Save()
{
	// TODO: fix this not writing to mod directory.
	std::ofstream writer(INI_FILE);

	if (!writer.is_open())
	{
		printf("[Free Camera] Failed to write configuration data.\n");
		return;
	}

	// General
	INI_WRITE_SECTION("General");
	INI_WRITE_BOOL(IsAutomaticMouseUnhook);

	writer.close();
}