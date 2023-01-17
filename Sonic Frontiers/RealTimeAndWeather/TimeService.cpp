HOOK(int64_t, __fastcall, SetTime, 0x147E22D20, Time* in_time, int in_days, int in_hours, int in_minutes, float in_seconds)
{
	auto clock = TimeHelper::GetSystemTime();

	auto* daily = &WeatherListener::m_CurrentInfo.m_DailyRecords;

	if (!daily->m_Time.empty())
	{
		for (int i = 0; i < daily->m_Time.size() - 1; i++)
		{
			time_t sys = TimeHelper::GetSystemEpoch();

			if (sys >= daily->m_Time[i] && sys <= daily->m_Time[i + 1])
			{
				tm realSunrise = TimeHelper::GetTimeFromEpoch(daily->m_Sunrise[i]);
				tm realSunset = TimeHelper::GetTimeFromEpoch(daily->m_Sunset[i]);
#if _DEBUG
				printf("[RealTimeAndWeather] Time:    %02d:%02d:%02d\n", clock.tm_hour, clock.tm_min, clock.tm_sec);
				printf("[RealTimeAndWeather] Sunrise: %d:%d\n", realSunrise.tm_hour, realSunrise.tm_min);
				printf("[RealTimeAndWeather] Sunset:  %d:%d\n", realSunset.tm_hour, realSunset.tm_min);
#endif
				
				if (clock.tm_hour <= realSunset.tm_hour)
				{
					auto hour = clock.tm_hour;

					if (clock.tm_hour < realSunrise.tm_hour)
					{
						hour += 24;
					}

					TimeService::m_Hours = in_time->m_Hours = std::lerp(4.0f, 20.0f, (24 - (TimeService::m_GameSunset.tm_hour - ((hour - realSunrise.tm_hour) / (float)realSunrise.tm_hour))) - TimeService::m_GameSunrise.tm_hour);
				}
				else
				{
					// night here lmao
					// Bri'ish time go 16 - 8
					// frontiers go 20 - 4

					auto hour = clock.tm_hour;

					if (clock.tm_hour < realSunrise.tm_hour)
					{
						hour += 24;
					}

					TimeService::m_Hours = in_time->m_Hours = ((float)hour - (float)realSunrise.tm_hour) / (float)realSunrise.tm_hour * (realSunset.tm_hour % TimeService::m_GameSunset.tm_hour) + TimeService::m_GameSunrise.tm_hour;
				}

				TimeService::m_Minutes = in_time->m_Minutes = clock.tm_min;
			}
		}
	}

	return originalSetTime(in_time, 0, 0, 0, 0);
}

SIG_SCAN
(
	m_SigSetTimeSpeed,

	0x147EBD7F6,

	/* 0x147EBD7F6 */
	"\xE8\xCC\xCC\xCC\xCC\x41\xFF\x0E\x4C\x8D\xBB\x00\x01\x00\x00", "x????xxxxxxxxxx"
);

void TimeService::Install()
{
	INSTALL_HOOK(SetTime);

	/* Replace function calls to set time speed with NOPs.
	 
	   These calls cause the game to get stuck in an infinite
	   loop during loading screens sometimes.
	   
	   We don't need them anyway. */
	WRITE_NOP(m_SigSetTimeSpeed(), 5);				   // 0x147EBD7F6
	WRITE_NOP((int64_t)m_SigSetTimeSpeed() + 0x31, 5); // 0x147EBD827
}