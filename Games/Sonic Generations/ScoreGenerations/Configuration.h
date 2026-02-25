#pragma once

#define INI_FILE "ScoreGenerations.ini"

enum class PerfectBonusType
{
	Disabled,
	OnlyForARank,
	Enabled
};

class Configuration
{
	/// <summary>
	/// Determines if the configuration was overridden.
	/// </summary>
	inline static bool m_IsOverridden{};

public:
	/// <summary>
	/// The configuration being used for settings.
	/// </summary>
	inline static cmf::sys::cfg::Ini Ini{};

	/// <summary>
	/// Determines if you should be rewarded with a bonus for your current speed passing through a checkpoint.
	/// </summary>
	inline static bool IsRewardSpeedBonus{ true };

	/// <summary>
	/// Determines if the score should stop counting up after you surpass the maximum amount of time for a time bonus.
	/// </summary>
	inline static bool IsScoreTimeout{ false };

	/// <summary>
	/// Determines if the score should reset back to what you had at your last checkpoint upon dying.
	/// </summary>
	inline static bool IsRestoreLastCheckpointScore{ false };

	/// <summary>
	/// The maximum amount of score the player can obtain.
	/// </summary>
	inline static int MaxScore{ 999999 };

	/// <summary>
	/// Determines how the perfect bonus will behave.
	/// </summary>
	inline static PerfectBonusType PerfectBonusType{ PerfectBonusType::OnlyForARank };

	/// <summary>
	/// The string format used for the score text.
	/// </summary>
	inline static std::string ScoreFormat{ "%06d" };

	/// <summary>
	/// Determines if the mod overriding the configuration uses a custom UI layout.
	/// </summary>
	inline static bool IsCustomUI{};

	/// <summary>
	/// Determines if the custom score counter should override Casino Night Zone's score counter.
	/// <para>Only use this if absolutely necessary.</para>
	/// </summary>
	inline static bool IsOverrideCasinoNightZone{};

	/// <summary>
	/// Stages that should not display the score counter.
	/// </summary>
	inline static std::vector<std::string> ProhibitedStages
	{
		// Boss: Metal Sonic
		"bms",
		"bms001",

		// Boss: Death Egg
		"bde",
		"bde001",

		// Boss: Shadow
		"bsd",
		"bsd001",

		// Boss: Perfect Chaos
		"bpc",
		"bpc001",

		// Boss: Silver
		"bsl",
		"bsl001",

		// Boss: Egg Dragoon
		"bne",
		"bne001",

		// Boss: Time Eater
		"blb",
		"blb001"
	};

	static void Read(const std::filesystem::path& in_rPath);
};
