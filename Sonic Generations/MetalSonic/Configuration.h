#pragma once

#define INI_FILE "MetalSonic.ini"

class Configuration
{
public:
	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read();

	/// <summary>
	/// Determines if the custom sound effects should play for Metal Sonic.
	/// </summary>
	static bool soundEffects;

	/// <summary>
	/// Determines if Metal Sonic can drown underwater.
	/// </summary>
	static bool disableDrowning;
};

