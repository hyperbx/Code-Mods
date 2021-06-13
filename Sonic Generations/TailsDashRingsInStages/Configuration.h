#pragma once

#define INI_FILE "TailsDashRingsInStages.ini"

class Configuration
{
public:
	static enum SoundType
	{
		DashRing,
		DashPanel
	};

	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read();

	/// <summary>
	/// The 
	/// </summary>
	static SoundType soundType;
};