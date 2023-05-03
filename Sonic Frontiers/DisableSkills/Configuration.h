#pragma once

#define INI_FILE "DisableSkills.ini"

class Configuration
{
public:
	inline static bool IsNoAirTrick = false;
	inline static bool IsNoCrossSlash = false;
	inline static bool IsNoCycloneKick = false;
	inline static bool IsNoCyloop = false;
	inline static bool IsNoGrandSlam = false;
	inline static bool IsNoHomingShot = false;
	inline static bool IsNoLoopKick = false;
	inline static bool IsNoPhantomRush = false;
	inline static bool IsNoQuickCyloop = false;
	inline static bool IsNoRecoverySmash = false;
	inline static bool IsNoSonicBoom = false;
	inline static bool IsNoSpinSlash = false;
	inline static bool IsNoStompAttack = false;
	inline static bool IsNoWildRush = false;

	static void Read();
};

