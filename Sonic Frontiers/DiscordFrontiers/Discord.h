#pragma once

#define APPLICATION_ID "1067048896657903637"

class Discord
{
public:
	inline static DiscordRichPresence Client;

	inline static std::string State          = "";
	inline static std::string Details        = "";
	inline static std::string LargeImageKey  = "default";
	inline static std::string LargeImageText = "Game";
	inline static std::string SmallImageKey  = "";
	inline static std::string SmallImageText = "";

	inline static time_t StartTime = TimeHelper::GetSystemEpoch();

	static void Init();
	static void Commit(std::string in_state, std::string in_details, std::string in_largeImageKey, std::string in_largeImageText, std::string in_smallImageKey, std::string in_smallImageText, time_t in_startTime = StartTime, bool in_isLocalised = true);

	static void CommitState(std::string in_state, bool in_isLocalised = true)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting state to \"%s\".\n", in_state.c_str());
#endif

		Commit(in_isLocalised ? LanguageHelper::Localise(in_state) : in_state, Details, LargeImageKey, LargeImageText, SmallImageKey, SmallImageText, StartTime, false);
	}

	static void CommitDetails(std::string in_details, bool in_isLocalised = true)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting details to \"%s\".\n", in_details.c_str());
#endif

		Commit(State, in_isLocalised ? LanguageHelper::Localise(in_details) : in_details, LargeImageKey, LargeImageText, SmallImageKey, SmallImageText, StartTime, false);
	}

	static void CommitLargeImage(std::string in_largeImageKey)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting large image to \"%s\".\n", in_largeImageKey.c_str());
#endif

		Commit(State, Details, in_largeImageKey, LargeImageText, SmallImageKey, SmallImageText, StartTime, false);
	}

	static void CommitLargeImageText(std::string in_largeImageText, bool in_isLocalised = true)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting large image text to \"%s\".\n", in_largeImageText.c_str());
#endif

		Commit(State, Details, LargeImageKey, in_isLocalised ? LanguageHelper::Localise(in_largeImageText) : in_largeImageText, SmallImageKey, SmallImageText, StartTime, false);
	}

	static void CommitSmallImage(std::string in_smallImageKey)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting small image to \"%s\".\n", in_smallImageKey.c_str());
#endif

		Commit(State, Details, LargeImageKey, LargeImageText, in_smallImageKey, SmallImageText, StartTime, false);
	}

	static void CommitSmallImageText(std::string in_smallImageText, bool in_isLocalised = true)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting small image text to \"%s\".\n", in_smallImageText.c_str());
#endif

		Commit(State, Details, LargeImageKey, LargeImageText, SmallImageKey, in_isLocalised ? LanguageHelper::Localise(in_smallImageText) : in_smallImageText, StartTime, false);
	}

	static void CommitTime(time_t in_startTime)
	{
#if _DEBUG
		printf("[Discord Frontiers] Setting time to \"%lld\".\n", in_startTime);
#endif

		Commit(State, Details, LargeImageKey, LargeImageText, SmallImageKey, SmallImageText, in_startTime, false);
	}

	static void ResetTime()
	{
#if _DEBUG
		printf("[Discord Frontiers] Time reset!\n");
#endif

		Commit(State, Details, LargeImageKey, LargeImageText, SmallImageKey, SmallImageText, TimeHelper::GetSystemEpoch(), false);
	}
};