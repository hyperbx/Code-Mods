#pragma once

#define APPLICATION_ID "1067048896657903637"

class Discord
{
public:
	inline static DiscordRichPresence Client;
	
	inline static std::string Name = "Sonic Frontiers";

	inline static std::string Details = "Idle";
	inline static std::string State   = "";

	inline static std::string LargeImageKey = "default";
	inline static std::string SmallImageKey = "";

	inline static time_t StartTime = TimeHelper::GetSystemEpoch();

	static void Initialise();

	static void Update(std::string in_state, std::string in_details, std::string in_largeImageKey, std::string in_smallImageKey = SmallImageKey, time_t in_startTime = StartTime);

	static void ResetTime()
	{
		Update(State, Details, LargeImageKey, SmallImageKey, TimeHelper::GetSystemEpoch());
	}
};

