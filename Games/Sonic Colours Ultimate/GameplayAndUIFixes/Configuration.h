#pragma once

#define INI_FILE "mod.ini"

enum class RingLifeType
{
	Disabled,
	Once,
	Enabled
};

class Configuration
{
public:
	/// <summary>
	/// Determines if Tails Save should be used in place of lives.
	/// </summary>
	inline static bool IsTailsSave{};

	/// <summary>
	/// Determines how collecting 100 rings should give you an extra life.
	/// </summary>
	inline static RingLifeType RingLifeType{};

	static void Read();
};
