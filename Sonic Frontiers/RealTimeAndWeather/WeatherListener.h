#pragma once

class WeatherListener
{
public:
	enum EWeatherCode : int
	{
		Clear = 0,

		CloudyLight    = 1,
		CloudyModerate = 2,
		CloudyHeavy    = 3,

		Fog = 45,

		FogFreezing = 48,

		DrizzleLight    = 51,
		DrizzleModerate = 53,
		DrizzleHeavy    = 55,

		DrizzleFreezingLight = 56,
		DrizzleFreezingHeavy = 57,

		RainLight    = 61,
		RainModerate = 63,
		RainHeavy    = 65,

		RainFreezingLight = 66,
		RainFreezingHeavy = 67,

		SnowLight    = 71,
		SnowModerate = 73,
		SnowHeavy    = 75,
		SnowGrains   = 77,

		RainShowerLight    = 80,
		RainShowerModerate = 81,
		RainShowerHeavy    = 82,

		SnowShowerLight = 85,
		SnowShowerHeavy = 86
	};

	struct WeatherInfo
	{
		int m_TimeZoneOffset;

		struct HourlyRecords
		{
			std::vector<time_t> m_Time;
			std::vector<EWeatherCode> m_WeatherCode;

			HourlyRecords() { }

			HourlyRecords(std::vector<time_t> in_time, std::vector<EWeatherCode> in_weatherCode)
			{
				m_Time        = in_time;
				m_WeatherCode = in_weatherCode;
			}
		};

		HourlyRecords m_HourlyRecords;

		struct DailyRecords
		{
			std::vector<time_t> m_Time;
			std::vector<time_t> m_Sunrise;
			std::vector<time_t> m_Sunset;

			DailyRecords() { }

			DailyRecords(std::vector<time_t> in_time, std::vector<time_t> in_sunrise, std::vector<time_t> in_sunset)
			{
				m_Time    = in_time;
				m_Sunrise = in_sunrise;
				m_Sunset  = in_sunset;
			}
		};

		DailyRecords m_DailyRecords;

		WeatherInfo() { }

		WeatherInfo(std::string in_json)
		{
#if !_DEBUG
			try
			{
#endif
				json j = json::parse(in_json);
				{
					m_TimeZoneOffset = j["utc_offset_seconds"];

					auto& hourly = j["hourly"];
					{
						std::vector<time_t> time              = hourly["time"];
						std::vector<EWeatherCode> weatherCode = hourly["weathercode"];

						m_HourlyRecords = WeatherInfo::HourlyRecords(time, weatherCode);
					}

					auto& daily = j["daily"];
					{
						std::vector<time_t> time    = daily["time"];
						std::vector<time_t> sunrise = daily["sunrise"];
						std::vector<time_t> sunset  = daily["sunset"];

						m_DailyRecords = WeatherInfo::DailyRecords(time, sunrise, sunset);
					}
				}

				// Adjust times using current user time zone.
				{
					for (time_t time : m_HourlyRecords.m_Time)
						time += TimeHelper::SecondsToMilliseconds(m_TimeZoneOffset);

					for (time_t time : m_DailyRecords.m_Time)
						time += TimeHelper::SecondsToMilliseconds(m_TimeZoneOffset);

					for (time_t time : m_DailyRecords.m_Sunrise)
						time += TimeHelper::SecondsToMilliseconds(m_TimeZoneOffset);

					for (time_t time : m_DailyRecords.m_Sunset)
						time += TimeHelper::SecondsToMilliseconds(m_TimeZoneOffset);
				}
#if !_DEBUG
			}
			catch (...)
			{
				Configuration::m_IsRealWeather = false;

				MessageBoxA
				(
					nullptr,
					"Failed to parse Open-Meteo weather information...\nReal-time weather is now disabled.",
					"Real Time and Weather",
					MB_ICONERROR
				);
			}
#endif
		}
	};

	static inline WeatherInfo m_CurrentInfo;

	static WeatherInfo GetWeatherInfo()
	{
		std::string response = HttpHelper::ReadStringFromUrl
		(
			std::format
			(
				"https://api.open-meteo.com/v1/forecast?latitude={}&longitude={}&hourly=weathercode&daily=sunrise,sunset&timeformat=unixtime&timezone=auto",

				Configuration::m_Latitude,
				Configuration::m_Longitude
			)
		);

		if (response.empty())
		{
			MessageBoxA
			(
				nullptr,
				"Unable to contact Open-Meteo for weather information...\nReal-time weather is now disabled.",
				"Real Time and Weather",
				MB_ICONWARNING
			);

			return WeatherInfo();
		}

		return WeatherInfo(response);
	}
};
