void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// General
	Language = INI_READ_STRING("General", Language);

	// Visualiser
	URL = INI_READ_STRING("Visualiser", URL);
}