#pragma once

#define INI_FILE "ScoreGenerations.ini"

class Configuration
{
	/// <summary>
	/// Determines if the configuration was overridden.
	/// </summary>
	static bool overrideFlag;

public:
	/// <summary>
	/// The configuration being used for settings.
	/// </summary>
	static INIReader config;

	/// <summary>
	/// The path to the configuration.
	/// </summary>
	static string configPath;

	/// <summary>
	/// Gets the directory containing the configuration.
	/// </summary>
	static string GetConfigDirectory();

	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read(string path);

	/// <summary>
	/// Force enables non-default debugging features.
	/// </summary>
	static void Debug();

	/// <summary>
	/// Determines if you should be rewarded with a bonus for your current speed passing through a checkpoint.
	/// </summary>
	static bool rewardVelocityBonus;

	/// <summary>
	/// Determines if the score should stop counting up after you surpass the maximum amount of time for a time bonus.
	/// </summary>
	static bool scoreTimeout;

	/// <summary>
	/// Determines if the score should reset back to what you had at your last checkpoint upon dying.
	/// </summary>
	static bool restoreLastCheckpointScore;

	/// <summary>
	/// The maximum amount of score the player can obtain.
	/// </summary>
	static int scoreLimit;

	/// <summary>
	/// The state that determines how the perfect bonus will behave.
	/// </summary>
	static int perfectBonus;

	/// <summary>
	/// Formatting used for the string printer for score.
	/// </summary>
	static string scoreFormat;

	/// <summary>
	/// Determines if the mod overriding the configuration uses a custom XNCP.
	/// </summary>
	static bool customXNCP;

	/// <summary>
	/// Determines if Lua debug comments should be shown.
	/// </summary>
	static bool debugLua;

	/// <summary>
	/// Not as intimidating as it sounds - just tells Score Generations that you're never in Casino Night Zone regardless.
	/// </summary>
	static bool overrideForbiddenCasino;

	/// <summary>
	/// List of forbidden stages that should not display the score counter.
	/// </summary>
	static vector<string> forbiddenStages;
};