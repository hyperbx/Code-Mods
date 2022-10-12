#pragma once

#define INI_FILE "mod.ini"

class Configuration
{
public:
	static enum DropDashType
	{
		Disabled,
		SideView,
		ForwardView,
		Both
	};

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
	/// Determines how Sonic can perform the drop dash.
	/// </summary>
	static DropDashType dropDashType;

	/// <summary>
	/// Determines how high Sonic will double jump.
	/// </summary>
	static float doubleJumpVelocity;

	/// <summary>
	/// Determines how high Sonic will double jump underwater.
	/// </summary>
	static float doubleJumpVelocityWater;

	/// <summary>
	/// Determines how fast Sonic will be propelled when performing a drop dash in 2D.
	/// </summary>
	static float dropDashVelocitySideView;

	/// <summary>
	/// Determines how fast Sonic will be propelled when performing a drop dash in 3D.
	/// </summary>
	static float dropDashVelocityForwardView;

	/// <summary>
	/// Determines how long Sonic will remain in a ball after rolling.
	/// </summary>
	static float spinAttackRollDuration;

	/// <summary>
	/// Determines how many times Sonic can bounce.
	/// </summary>
	static int stompBounceCount;

	/// <summary>
	/// Determines how long the B button must be held for Sonic to bounce.
	/// </summary>
	static float stompBounceDelay;

	/// <summary>
	/// Determines how high Sonic will bounce.
	/// </summary>
	static float stompBounceVelocity;

	/// <summary>
	/// Determines how high Sonic will bounce underwater.
	/// </summary>
	static float stompBounceVelocityWater;

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

