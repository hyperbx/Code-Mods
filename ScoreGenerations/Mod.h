using namespace std;

#pragma once

#define INI_FILE "ScoreGenerations.ini"

class Mod
{
public:
	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void ReadINI();

	/// <summary>
	/// Formatting used for the string printer for score.
	/// </summary>
	static string scoreFormat;
};