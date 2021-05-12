#include <fstream>

#include "Mod.h"
#include "SonicHud.h"
#include "ObjectHooks.h"
#include "StateHooks.h"
#include "Patches.h"
#include "StringHelper.h"

#include "dependencies\inipp.h"

using namespace std;

// Declare class variables.
bool Mod::scoreDisplay = false;
bool Mod::ringFormatter = false;
bool Mod::homingReticle = false;
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
	inipp::extract(StringHelper::ToLower(ini.sections["Appearance"]["scoreDisplay"]), Mod::scoreDisplay);
	inipp::extract(StringHelper::ToLower(ini.sections["Appearance"]["ringFormatter"]), Mod::ringFormatter);
	inipp::extract(StringHelper::ToLower(ini.sections["Appearance"]["homingReticle"]), Mod::homingReticle);
	inipp::extract(StringHelper::Unquote(ini.sections["Appearance"]["scoreFormat"]), Mod::scoreFormat);

	file.close();
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	ReadINI();

	// Apply simple patches.
	Patches::Install();

	// Install mid-ASM hooks for HUD stuff.
	SonicHud::Install();

	// Only hook these when score is displayed.
	if (Mod::scoreDisplay)
	{
		// Install mid-ASM hooks for object and state stuff.
		ObjectHooks::Install();
		StateHooks::Install();
	}
}