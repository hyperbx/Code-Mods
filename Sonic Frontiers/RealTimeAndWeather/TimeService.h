#pragma once

class TimeService
{
public:
	static inline tm m_GameSunrise = { 0, 0, 4, 0, 0, 0 }; // 4:00AM

	static inline tm m_GameSunset = { 25, 0, 20, 0, 0, 0 }; // 8:25PM

	static inline int m_Hours = 0;

	static inline int m_Minutes = 0;

	static inline float m_Seconds = 0.0f;

	static void Install();
};

