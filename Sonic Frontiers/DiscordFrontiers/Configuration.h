#pragma once

#define INI_FILE "DiscordFrontiers.ini"

class Configuration
{
public:
	inline static std::string Language = "en-GB";

	static void Read();
	static void ReadMods(ModInfo* in_pModInfo);
};