#pragma once

#define INI_FILE "FrontiersSonic.ini"

class Configuration
{
public:
	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read();

	/// <summary>
	/// Determines whether the homing reticle will be active at all times.
	/// </summary>
	static bool alwaysActiveReticle;

	/// <summary>
	/// Determines whether Sonic can perform a second jump after the first.
	/// </summary>
	static bool doubleJump;

	/// <summary>
	/// Determines whether Sonic can homing attack whilst grounded.
	/// </summary>
	static bool groundHoming;

	/// <summary>
	/// Determines whether Sonic will bounce after performing a stomp.
	/// </summary>
	static bool stompBounce;

	/// <summary>
	/// Determines whether Sonic will boost upon holding right trigger.
	/// </summary>
	static bool boostOnRT;

	/// <summary>
	/// Determines whether Sonic will homing attack upon pressing X.
	/// </summary>
	static bool homingOnX;

	/// <summary>
	/// Determines whether Sonic will light dash upon clicking the left stick.
	/// </summary>
	static bool lightDashOnLS;
};

