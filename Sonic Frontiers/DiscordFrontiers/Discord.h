#pragma once

#define APPLICATION_ID "1067048896657903637"

class Discord
{
public:
	inline static DiscordRichPresence Client;
	
	inline static std::string Details = "";
	inline static std::string State   = "";
	inline static std::string LargeImageKey = "default";
	inline static std::string SmallImageKey = "";

	inline static time_t StartTime = TimeHelper::GetSystemEpoch();

	static void Init();
	static void Commit(std::string in_state, std::string in_details, std::string in_largeImageKey, std::string in_smallImageKey = SmallImageKey, time_t in_startTime = StartTime);

	static void CommitState(std::string in_state)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting state to \"%s\".\n", in_state.c_str());
#endif

		Commit(in_state, Details, LargeImageKey, SmallImageKey, StartTime);
	}

	static void CommitDetails(std::string in_details)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting details to \"%s\".\n", in_details.c_str());
#endif

		Commit(State, in_details, LargeImageKey, SmallImageKey, StartTime);
	}

	static void CommitLargeImage(std::string in_largeImageKey)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting large image to \"%s\".\n", in_largeImageKey.c_str());
#endif

		Commit(State, Details, in_largeImageKey, SmallImageKey, StartTime);
	}

	static void CommitSmallImage(std::string in_smallImageKey)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting small image to \"%s\".\n", in_smallImageKey.c_str());
#endif

		Commit(State, Details, LargeImageKey, in_smallImageKey, StartTime);
	}

	static void CommitTime(time_t in_startTime)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting time to \"%lld\".\n", in_startTime);
#endif

		Commit(State, Details, LargeImageKey, SmallImageKey, in_startTime);
	}

	static void ResetTime()
	{
#if _DEBUG
		printf("[Discord Frontiers] Time reset!\n");
#endif

		Commit(State, Details, LargeImageKey, SmallImageKey, TimeHelper::GetSystemEpoch());
	}
};