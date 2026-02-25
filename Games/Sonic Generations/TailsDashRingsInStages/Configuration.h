#pragma once

#define INI_FILE "TailsDashRingsInStages.ini"

enum class ColourType
{
	GreenOriginal,
	Green,
	Orange,
	Red,
	Purple,
	Blue
};

enum class SoundType
{
	DashRing,
	RainbowRing,
	DashPanel,
	ClassicSpring,
	ModernSpring
};

class Configuration
{
public:
	/// <summary>
	/// The colour of the dash rings.
	/// </summary>
	inline static ColourType ColourType{};

	/// <summary>
	/// The sound that plays when interacting with dash rings.
	/// </summary>
	inline static SoundType SoundType{};

	/// <summary>
	/// Determines whether the dash rings in Tails' mission should be modified.
	/// </summary>
	inline static bool IsOverrideTailsDashRing{};

	/// <summary>
	/// Determines whether custom rainbow rings akin to Sonic Colours: Ultimate should be loaded.
	/// </summary>
	inline static bool UseCustomRainbowRings{};

	static void Read();
};