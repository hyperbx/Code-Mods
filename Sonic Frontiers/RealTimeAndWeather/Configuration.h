#pragma once

#define INI_FILE "RealTimeAndWeather.ini"

class Configuration
{
public:
	static inline bool m_IsRealTime = true;

	static inline bool m_IsRealWeather = true;

	static inline bool m_IsFirstTimeSetup = true;

	static inline float m_Latitude = 0.0f;

	static inline float m_Longitude = 0.0f;

	static void Read();
};

