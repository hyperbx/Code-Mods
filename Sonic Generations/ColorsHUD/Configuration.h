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
	/// Determines whether the gauge plays a shaking animation.
	/// </summary>
	static bool GaugeShake;
};

