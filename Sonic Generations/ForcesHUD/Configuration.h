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
	/// Determines whether the ring formatter should have fixed justification.
	/// </summary>
	static bool ringFormatter;

	/// <summary>
	/// Determines whether the Forces homing reticle will be used.
	/// </summary>
	static bool homingReticle;

	/// <summary>
	/// Determines whether the Forces window title will be used.
	/// </summary>
	static bool windowTitle;

	/// <summary>
	/// Determines whether the BOOST text is visible below the boost gauge.
	/// </summary>
	static bool boostText;

	static enum ButtonType
	{
		Xbox,
		PlayStation,
		Switch
	};

	/// <summary>
	/// Controls what button prompts to show in-game.
	/// </summary>
	static ButtonType buttonType;

	/// <summary>
	/// Controls what difficulty is used like Forces.
	/// 
	/// Normal (0) - 100 ring cap
	/// Hard   (1) - 999 ring cap
	/// </summary>
	static int difficultyType;

	/// <summary>
	/// Determines whether the homing reticle will be active at all times.
	/// </summary>
	static bool alwaysActiveReticle;

	/// <summary>
	/// Determines how Forces' trick sounds should be used.
	/// </summary>
	static int trickSounds;

	/// <summary>
	/// Determines whether Forces' homing sound will be used.
	/// </summary>
	static bool homingSound;
};