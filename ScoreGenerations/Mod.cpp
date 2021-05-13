#include "StringHelper.h"

using namespace std;

// Declare class variables.
string Mod::scoreFormat = "%06d";

/// <summary>
/// Reads the mod configuration file.
/// </summary>
void Mod::ReadINI()
{
	inipp::Ini<char> ini;
	std::ifstream file(INI_FILE);
	ini.parse(file);

	// Appearance
	inipp::extract(StringHelper::Unquote(ini.sections["Appearance"]["scoreFormat"]), Mod::scoreFormat);

	file.close();
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Mod::ReadINI();

	Patches::Install();

	ArchiveTreePatcher::Install();
	StatisticsListener::Install();
	ObjectHooks::Install();
	StateHooks::Install();
}