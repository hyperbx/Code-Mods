#pragma once

class Patches
{
public:
	/// <summary>
	/// Patches the dash ring names.
	/// </summary>
	static void PatchDashRingNames(const char* overrideName = "");

	/// <summary>
	/// Installs the patches.
	/// </summary>
	static void Install();
};