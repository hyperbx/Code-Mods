using namespace std;

// Declare class variables.
string Mod::scoreFormat = "%06d";
bool Mod::customHUD = false;

/// <summary>
/// Reads the mod configuration file.
/// </summary>
void Mod::ReadModINI(string path = "")
{
	inipp::Ini<char> ini;
	std::ifstream file(path.empty() ? INI_FILE : path);
	ini.parse(file);

	// Appearance
	inipp::extract(StringHelper::Unquote(ini.sections["Appearance"]["scoreFormat"]), Mod::scoreFormat);

	// Developer
	inipp::extract(StringHelper::Unquote(ini.sections["Developer"]["customHUD"]), Mod::customHUD);

	file.close();
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Loader::ConfigureScoreGenerations();

	Patches::Install();

	ArchiveTreePatcher::Install();
	StatisticsListener::Install();
	ObjectHooks::Install();
	StateHooks::Install();
}