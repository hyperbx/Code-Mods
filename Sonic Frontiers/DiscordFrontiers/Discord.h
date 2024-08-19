#pragma once

#define APPLICATION_ID "1067048896657903637"

class Discord
{
private:
	inline static std::vector<std::string> m_hostedAssets;
	inline static std::unordered_map<std::string, long> m_responses;

public:
	inline static DiscordRichPresence Client;

	inline static std::unordered_map<std::string, std::string> ImageURLs;

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

	static std::vector<std::string> GetHostedAssets()
	{
		std::vector<std::string> result{};

		auto url = std::format("https://discordapp.com/api/v6/oauth2/applications/{}/assets", APPLICATION_ID);
		auto response = HttpHelper::GetResponse(url);

		if (response != 200)
		{
			PRINT_ERROR("[Discord Frontiers] Failed to get Discord assets.");
			return result;
		}

		auto resource = json::parse(HttpHelper::ReadStringFromUrl(url));

		for (const auto& item : resource)
			result.push_back(item.at("name"));

		return result;
	}

	static bool IsDiscordAsset(std::string in_key)
	{
		if (std::find(m_hostedAssets.begin(), m_hostedAssets.end(), in_key) != m_hostedAssets.end())
			return true;

		return false;
	}

	static std::string GetImageFromSource(std::string in_imageKey, bool in_isSmallImage)
	{
		if (in_imageKey.empty())
			return in_imageKey;

		std::string imageKey = in_isSmallImage
			? "unknown_small"
			: "unknown";

		if (ImageURLs.count(in_imageKey))
		{
			imageKey = ImageURLs[in_imageKey];

			printf("[Discord Frontiers] %s: %s\n", in_imageKey.c_str(), imageKey.c_str());
		}
		else
		{
			return IsDiscordAsset(in_imageKey) ? in_imageKey : imageKey;
		}

		auto response = -1;

		if (m_responses.count(imageKey))
		{
			// Get last response to reduce connections.
			response = m_responses[imageKey];
		}
		else
		{
			// Get new response if we haven't tried already.
			response = HttpHelper::GetResponse(imageKey);

			m_responses.insert({ imageKey, response });
		}

		if (response != 200)
		{
			imageKey = in_isSmallImage
				? "missing_small"
				: "missing";

			constexpr std::string_view err = "Error: failed to load image \"{}\" ({})";

			if (response == -1)
			{
				PRINT_ERROR("[Discord Frontiers] %s\n", std::format(err, in_imageKey, "curl error").c_str());
			}
			else
			{
				PRINT_ERROR("[Discord Frontiers] %s\n", std::format(err, in_imageKey, std::format("response {}", response)).c_str());
			}
		}

		return imageKey;
	}
};