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

	/// <summary>
	/// Index-based ring life type.
	/// </summary>
	enum RingLifeType
	{
		Disabled,
		Once,
		Enabled
	};

	/// <summary>
	/// Determines whether or not you receive an extra life for getting 100 rings.
	/// </summary>
	static RingLifeType ringLifeType;

	/// <summary>
	/// Determines whether or not the navigator is forced off.
	/// </summary>
	static bool forceDisableNavi;
};