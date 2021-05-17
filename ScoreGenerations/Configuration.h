#pragma once

#define INI_FILE "ScoreGenerations.ini"

class Configuration
{
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
	/// Formatting used for the string printer for score.
	/// </summary>
	static string scoreFormat;

	/// <summary>
	/// Determines if the mod overriding the configuration uses a custom XNCP.
	/// </summary>
	static bool customXNCP;
};