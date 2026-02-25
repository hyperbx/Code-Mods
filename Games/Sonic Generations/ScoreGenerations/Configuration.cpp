#include "Configuration.h"
#include "LuaSystem.h"
#include "TableProvider.h"

#define INI_V1_BACKCOMPAT_GET(TYPE, SECTION, KEY, DEFAULT_VALUE) Ini.Get<TYPE>(SECTION, KEY, Ini.Get<TYPE>(SECTION, g_v1KeyMap.at(KEY), DEFAULT_VALUE))

using namespace ScoreGenerations;

static const std::unordered_map<std::string, std::string> g_v1KeyMap =
{
	{ "IsRewardSpeedBonus", "rewardSpeedBonus" },
	{ "IsScoreTimeout", "scoreTimeout" },
	{ "IsRestoreLastCheckpointScore", "restoreLastCheckpointScore" },
	{ "MaxScore", "scoreLimit" },
	{ "PerfectBonusType", "perfectBonus" },
	{ "ScoreFormat", "scoreFormat" },
	{ "IsCustomUI", "customXNCP" },
	{ "IsOverrideCasinoNightZone", "overrideForbiddenCasino" },
	{ "ProhibitedStages", "forbiddenStages" }
};

void Configuration::Read(const std::filesystem::path& in_rPath)
{
	Ini = cmf::sys::cfg::Ini(in_rPath);

	// Sets the Lua path to the one in the current working directory.
	if (!LuaSystem::SetScript(std::filesystem::path(in_rPath).remove_filename() / LUA_FILE_MAIN))
		LOGFN_WARNING("The overridden mod doesn't have a Lua script, reverting to previous script.");
	
	TableProvider::Read(Ini);

	IsRewardSpeedBonus = INI_V1_BACKCOMPAT_GET(bool, "GameplayBonus", "IsRewardSpeedBonus", IsRewardSpeedBonus);
	IsScoreTimeout = INI_V1_BACKCOMPAT_GET(bool, "Timer", "IsScoreTimeout", IsScoreTimeout);
	IsRestoreLastCheckpointScore = INI_V1_BACKCOMPAT_GET(bool, "Behaviour", "IsRestoreLastCheckpointScore", IsRestoreLastCheckpointScore);
	MaxScore = INI_V1_BACKCOMPAT_GET(int, "Behaviour", "MaxScore", MaxScore);
	PerfectBonusType = INI_V1_BACKCOMPAT_GET(enum PerfectBonusType, "Behaviour", "PerfectBonusType", PerfectBonusType);
	ScoreFormat = INI_V1_BACKCOMPAT_GET(std::string, "Appearance", "ScoreFormat", ScoreFormat);

	if (m_IsOverridden)
	{
		auto isOverrideIsCustomUI = INI_V1_BACKCOMPAT_GET(bool, "Developer", "IsCustomUI", IsCustomUI);

		if (Configuration::IsCustomUI && !isOverrideIsCustomUI)
		{
			MessageBoxA
			(
				nullptr,
				MOD_NAME " has detected a HUD mod loaded with incorrect priority, please increase its priority.",
				MOD_NAME,
				MB_ICONWARNING
			);
		}
	}

	IsCustomUI = INI_V1_BACKCOMPAT_GET(bool, "Developer", "IsCustomUI", IsCustomUI);
	IsOverrideCasinoNightZone = INI_V1_BACKCOMPAT_GET(bool, "Developer", "IsOverrideCasinoNightZone", IsOverrideCasinoNightZone);

	auto prohibitedStagesCsv = INI_V1_BACKCOMPAT_GET(std::string, "Developer", "ProhibitedStages",
		cmf::sys::utils::StringHelper::Join(", ", ProhibitedStages));

	if (!prohibitedStagesCsv.empty())
		ProhibitedStages = cmf::sys::utils::StringHelper::Split(prohibitedStagesCsv, ", ");

	// Set the override flag now that we've read a config.
	m_IsOverridden = true;

	LOGFN_UTILITY("IsRewardSpeedBonus ----------- : {}", IsRewardSpeedBonus);
	LOGFN_UTILITY("IsScoreTimeout --------------- : {}", IsScoreTimeout);
	LOGFN_UTILITY("IsRestoreLastCheckpointScore - : {}", IsRestoreLastCheckpointScore);
	LOGFN_UTILITY("MaxScore --------------------- : {}", MaxScore);
	LOGFN_UTILITY("PerfectBonusType ------------- : {}", int(PerfectBonusType));
	LOGFN_UTILITY("ScoreFormat ------------------ : {}", ScoreFormat);
	LOGFN_UTILITY("IsCustomUI ------------------- : {}", IsCustomUI);
	LOGFN_UTILITY("IsOverrideCasinoNightZone ---- : {}", IsOverrideCasinoNightZone);
	LOGFN_UTILITY("ProhibitedStages ------------- : {}", prohibitedStagesCsv);
}
