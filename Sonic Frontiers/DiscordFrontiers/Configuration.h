#pragma once

#define INI_FILE "DiscordFrontiers.ini"

class Configuration
{
public:
	inline static std::string Language = "en-GB";
	inline static std::string URL = "";

	static void Read();
};