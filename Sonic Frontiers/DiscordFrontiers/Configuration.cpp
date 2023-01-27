void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// General
	Language = reader.Get("General", "language", Language);
}