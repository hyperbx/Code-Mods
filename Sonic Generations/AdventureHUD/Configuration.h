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
	/// Determines whether or not the boost gauge is hidden.
	/// </summary>
	static bool disableGauge;
};

