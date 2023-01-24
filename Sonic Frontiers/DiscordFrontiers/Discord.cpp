void Discord::Initialise()
{
    Discord_Initialize(APPLICATION_ID, NULL, 1, NULL);

    memset(&Client, 0, sizeof(Client));

    Discord::Update(State, Details, LargeImageKey, SmallImageKey, 0);
}

void Discord::Update(std::string in_state, std::string in_details, std::string in_largeImageKey, std::string in_smallImageKey, time_t in_startTime)
{
    Discord::State         = Client.state = in_state.c_str();
    Discord::Details       = Client.details       = in_details.c_str();
    Discord::LargeImageKey = Client.largeImageKey = in_largeImageKey.c_str();
    Client.largeImageText  = in_details.c_str();
    Discord::SmallImageKey = Client.smallImageKey = in_smallImageKey.c_str();
    Client.smallImageText  = Name.c_str();
    Discord::StartTime     = Client.startTimestamp = in_startTime;

    Discord_UpdatePresence(&Client);
}