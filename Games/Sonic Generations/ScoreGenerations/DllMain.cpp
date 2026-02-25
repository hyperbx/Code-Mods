#include "../Dependencies/ArchiveTree.h"
#include "BonusProvider.h"
#include "ScoreHooks.h"
#include "ScoreHud.h"
#include "StatisticsProvider.h"

using namespace ScoreGenerations;

EXPORT void Init(ModInfo_t* in_pModInfo)
{
#ifdef _DEBUG
	MessageBoxA(nullptr, "Attach debugger!", MOD_NAME, MB_ICONWARNING);
#endif

	cmf::sys::Logger::Init();

	for (const auto& pMod : *in_pModInfo->ModList)
	{
		auto cfgPath = std::filesystem::path(pMod->Path).remove_filename() / INI_FILE;

		if (!std::filesystem::exists(cfgPath))
			continue;

		LOGFN_UTILITY("Found Score Generations configuration: {}", cfgPath.string());

		Configuration::Read(cfgPath);
	}

	if (!Configuration::IsCustomUI)
	{
		// Patch archive tree for Score Generations HUD.
		ArchiveTree::Archives.push_back({ "SonicActionCommonScoreHud", { "SonicActionCommonHud" } });
		ArchiveTree::Install();
	}

	BonusProvider::Install();
	ScoreHooks::Install();
	ScoreHud::Install();
	StatisticsProvider::Install();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
