using namespace std;

// Declare class variables.
string Mod::scoreFormat = "%06d";
bool Mod::customXNCP = false;

/// <summary>
/// Reads the mod configuration file.
/// </summary>
void Mod::ReadConfig(string path = "")
{
	inipp::Ini<char> ini;
	std::ifstream file(path.empty() ? INI_FILE : path);
	ini.parse(file);

	// Appearance
	inipp::extract(StringHelper::Unquote(ini.sections["Appearance"]["scoreFormat"]), Mod::scoreFormat);

	// Developer
	inipp::extract(StringHelper::Unquote(ini.sections["Developer"]["customXNCP"]), Mod::customXNCP);

	file.close();
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Loader::ConfigureScoreGenerations();

	Patches::Install();

	// Patch archive tree for Score Generations HUD.
	if (!Mod::customXNCP)
		ArchiveTreePatcher::Install();

	StatisticsListener::Install();
	ObjectHooks::Install();
	StateHooks::Install();
}