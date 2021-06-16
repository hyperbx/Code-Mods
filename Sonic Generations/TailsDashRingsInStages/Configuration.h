#pragma once

#define INI_FILE "TailsDashRingsInStages.ini"

class Configuration
{
public:
	static enum ColourType
	{
		Orange,
		Red,
		Green,
		GreenDiffuse,
		Purple,
		Blue
	};

	static enum SoundType
	{
		DashRing,
		RainbowRing,
		DashPanel,
		ClassicSpring,
		ModernSpring
	};

	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read();

	/// <summary>
	/// The colour of the dash ring.
	/// </summary>
	static ColourType colourType;

	/// <summary>
	/// The sound that plays when interacting with the dash ring.
	/// </summary>
	static SoundType soundType;

	/// <summary>
	/// Determines if the dash ring in Tails' mission should be modified too.
	/// </summary>
	static bool overrideTailsDashRing;

	/// <summary>
	/// Determines if the custom rainbow rings should be loaded.
	/// </summary>
	static bool useCustomRainbowRings;
};