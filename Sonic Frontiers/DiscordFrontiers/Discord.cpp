void Discord::Init()
{
    Discord_Initialize(APPLICATION_ID, NULL, 1, NULL);

    m_hostedAssets = GetHostedAssets();

    memset(&Client, 0, sizeof(Client));

    Discord::Commit(State, Details, LargeImageKey, LargeImageText, SmallImageKey, SmallImageText, 0, true);
}

void Discord::Commit
(
    std::string in_state,
    std::string in_details,
    std::string in_largeImageKey,
    std::string in_largeImageText,
    std::string in_smallImageKey,
    std::string in_smallImageText,
    time_t in_startTime,
    bool in_isLocalised
)
{
    if (in_isLocalised)
    {
        in_state = LanguageHelper::Localise(in_state);
        in_details = LanguageHelper::Localise(in_details);
        in_largeImageText = LanguageHelper::Localise(in_largeImageText);
        in_smallImageText = LanguageHelper::Localise(in_smallImageText);
    }

    Discord::State = Client.state = in_state.c_str();
    Discord::Details = Client.details = in_details.c_str();

    auto largeImageSource = GetImageFromSource(in_largeImageKey, false);

    Discord::LargeImageKey = in_largeImageKey.c_str();
    Client.largeImageKey = largeImageSource.c_str();

    Discord::LargeImageText = Client.largeImageText = in_largeImageText.c_str();

    auto smallImageSource = GetImageFromSource(in_smallImageKey, true);

    Discord::SmallImageKey = in_smallImageKey.c_str();
    Client.smallImageKey = smallImageSource.c_str();

    Discord::SmallImageText = Client.smallImageText = in_smallImageText.c_str();

    Discord::StartTime = Client.startTimestamp = in_startTime;

    Discord_UpdatePresence(&Client);
}