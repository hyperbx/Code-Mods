extern "C" _declspec(dllexport) void Init()
{
	Configuration::Read();

	StageListener::Install();

	WeatherListener::m_CurrentInfo = WeatherListener::GetWeatherInfo();

	if (Configuration::m_IsRealTime)
		TimeService::Install();

	if (Configuration::m_IsRealWeather)
		WeatherService::Install();
}