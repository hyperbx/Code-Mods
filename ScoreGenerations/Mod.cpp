#include <fstream>

#include "Mod.h"
#include "SonicHud.h"
#include "ObjectHooks.h"
#include "StateHooks.h"
#include "StringHelper.h"

#include "dependencies\inipp.h"

using namespace std;

// Declare class variables.
string Mod::scoreFormat = "%d";

/// <summary>
/// Reads the mod configuration file.
/// </summary>
void ReadINI()
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
	ReadINI();

	SonicHud::Install();
	ObjectHooks::Install();
	StateHooks::Install();
}