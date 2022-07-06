#pragma once

class ControllerPatcher
{
public:
	/// <summary>
	/// Installs the patched XNCP names.
	/// </summary>
	static void Install();

	static const char* ui_gp_btn_guide;
	static const char* ui_window;
	static const char* ui_pam;
	static const char* ui_gp_trick;
	static const char* ui_howto;
	static const char* ui_btn_guide;
	static const char* ui_gameplay;
};