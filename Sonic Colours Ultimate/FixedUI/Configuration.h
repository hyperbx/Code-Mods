#pragma once

#define INI_FILE "mod.ini"

class Configuration
{
public:
	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read();

	/// <summary>
	/// The design used for the boost gauge.
	/// </summary>
	static string gaugeType;

	/// <summary>
	/// Determines whether or not Tails Save should be used in place of lives.
	/// </summary>
	static string tailsSave;
};