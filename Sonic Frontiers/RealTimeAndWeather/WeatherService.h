#pragma once

class WeatherService
{
public:
	enum EWeatherType
	{
		Sunny = -1,
		Cloudy,
		Sandstorm,
		Rainy
	};

	static void Install();

	static EWeatherType GetWeather();
};