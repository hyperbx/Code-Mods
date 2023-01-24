WeatherService::EWeatherType WeatherService::GetWeather()
{
	// TODO: temporary for testing.
	return Sunny;

	auto* hourly = &WeatherListener::m_CurrentInfo.m_HourlyRecords;

	if (!hourly->m_Time.empty())
	{
		for (int i = 0; i < hourly->m_Time.size() - 1; i++)
		{
			time_t sys = TimeHelper::GetSystemEpoch();

			if (sys >= hourly->m_Time[i] && sys <= hourly->m_Time[i + 1])
			{
#if _DEBUG
				printf("[RealTimeAndWeather] Current code: %d\n", hourly->m_WeatherCode[i]);
#endif
				switch (hourly->m_WeatherCode[i])
				{
					case WeatherListener::DrizzleLight:
					case WeatherListener::DrizzleModerate:
					case WeatherListener::DrizzleHeavy:
					case WeatherListener::RainLight:
					case WeatherListener::RainModerate:
					case WeatherListener::RainHeavy:
					case WeatherListener::RainFreezingLight:
					case WeatherListener::RainFreezingHeavy:
					case WeatherListener::RainShowerLight:
					case WeatherListener::RainShowerModerate:
					case WeatherListener::RainShowerHeavy:
					{
						/* Ares has some strange behaviour when using Rainy weather
						   conditions, so we're gonna force it to use Cloudy conditions. */
						return StageListener::m_IslandType == StageListener::Ares
							? Cloudy
							: Rainy;
					}

					case WeatherListener::CloudyLight:
					case WeatherListener::CloudyModerate:
					case WeatherListener::CloudyHeavy:
					{
						return Cloudy;
					}
				}
			}
		}
	}

	return Sunny;
}

HOOK(int64_t, __fastcall, SetWeather, 0x1401EE3C0, int64_t a1)
{
	return Configuration::m_IsRealWeather
		? WeatherService::GetWeather()
		: originalSetWeather(a1);
}

HOOK(int64_t, __fastcall, SetWeatherKronos, 0x1401EE4B0, int64_t a1)
{
	// Yes, they actually have a separate (and near-identical) function for Kronos.

	if (TimeService::m_Hours <= 3 || TimeService::m_Hours >= 21)
	{
		/* Kronos, Rhea and Ouranos do not have lighting conditions
		   throughout the hours 12am-4am and 9pm-11pm for Rainy and
		   Cloudy weather conditions, resulting in a black screen.
		   
		   This is a bit of a hacky workaround to solve this issue,
		   but I do love me some hacky workarounds.
		   
		   TODO: find a way to remove lighting changes for weather
		         conditions during these hours. */

		return originalSetWeatherKronos(a1);
	}

	return Configuration::m_IsRealWeather
		? WeatherService::GetWeather()
		: originalSetWeatherKronos(a1);
}

void WeatherService::Install()
{
	INSTALL_HOOK(SetWeather);
	INSTALL_HOOK(SetWeatherKronos);
}