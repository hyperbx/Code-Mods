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
	/// Determines whether or not the ring formatter should have fixed justification.
	/// </summary>
	static bool ringFormatter;

	/// <summary>
	/// Determines whether or not the Forces homing reticle will be used.
	/// </summary>
	static bool homingReticle;

	/// <summary>
	/// Determines whether or not the Forces window title will be used.
	/// </summary>
	static bool windowTitle;

	/// <summary>
	/// Determines whether or not the BOOST text is visible below the boost gauge.
	/// </summary>
	static bool boostText;

	/// <summary>
	/// Controls what button prompts to show in game.
	/// 
	/// Xbox        (0)
	/// PlayStation (1)
	/// Switch      (2)
	/// </summary>
	static int buttonType;

	/// <summary>
	/// Controls what difficulty is used like Forces.
	/// 
	/// Normal (0) - 100 ring cap
	/// Hard   (1) - 999 ring cap
	/// </summary>
	static int difficultyType;

	/// <summary>
	/// Determines whether or not the homing reticle will be active at all times.
	/// </summary>
	static bool alwaysActiveReticle;

	/// <summary>
	/// Determines whether or not Forces' homing sound will be used.
	/// </summary>
	static bool homingSound;
};