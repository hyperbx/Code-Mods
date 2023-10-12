#pragma once

#define INI_FILE "FreeCamera.ini"

class Configuration
{
public:
	inline static bool IsAutomaticMouseUnhook = true;

	static void Load();
	static void Save();
};

