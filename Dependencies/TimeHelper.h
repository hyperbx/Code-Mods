#pragma once

class TimeHelper
{
public:
	static time_t GetSystemEpoch()
	{
		return time(nullptr);
	}

	static tm GetTimeFromEpoch(time_t epoch, time_t offset = 0)
	{
		tm* result {};
		{
			result = gmtime(&epoch + offset);
		}

		return *result;
	}

	static tm GetSystemTime()
	{
		return GetTimeFromEpoch(GetSystemEpoch());
	}

	static int SecondsToMilliseconds(int seconds)
	{
		return seconds / 1000;
	}

	static bool CompareTime(tm* left, tm* right)
	{
		if (left->tm_year != right->tm_year)
			return left->tm_year < right->tm_year;

		if (left->tm_mon != right->tm_mon)
			return left->tm_mon < right->tm_mon;

		if (left->tm_mday != right->tm_mday)
			return left->tm_mday < right->tm_mday;

		if (left->tm_hour != right->tm_hour)
			return left->tm_hour < right->tm_hour;

		if (left->tm_min != right->tm_min)
			return left->tm_min < right->tm_min;

		return left->tm_sec < right->tm_sec;
	}
};