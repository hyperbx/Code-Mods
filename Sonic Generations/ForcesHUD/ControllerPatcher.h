#pragma once

#define XBOX 0
#define PLAYSTATION 1
#define SWITCH 2

class ControllerPatcher
{
public:
	/// <summary>
	/// Installs the patched XNCP names.
	/// </summary>
	static void Install();

	// Various methods to get the XNCP names of the different controllers.
	static void SetXboxNames();
	static void SetPlayStationNames();
	static void SetSwitchNames();

	// Controller ID based on pre-processor definitions.
	static int controllerType;

	static const char* ui_gp_btn_guide;
	static const char* ui_window;
	static const char* ui_pam;
	static const char* ui_gp_trick;
	static const char* ui_howto;
	static const char* ui_btn_guide;
	static const char* ui_gameplay;
};