#include <string>

using namespace std;

#pragma once

#define INI_FILE "ForcesHUD.ini"

class Mod
{
public:
	/// <summary>
	/// Determines whether or not the score should display.
	/// </summary>
	static bool scoreDisplay;

	/// <summary>
	/// Determines whether or not the ring formatter should have fixed justification.
	/// </summary>
	static bool ringFormatter;

	/// <summary>
	/// Determines whether or not the Forces homing reticle will be used.
	/// </summary>
	static bool homingReticle;

	/// <summary>
	/// Formatting used for the string printer for score.
	/// </summary>
	static string scoreFormat;
};