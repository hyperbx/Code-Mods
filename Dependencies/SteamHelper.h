#pragma once

#include <format>
#include <fstream>
#include <iostream>
#include <Shlwapi.h>
#include <string>
#include <StringHelper.h>
#include <sstream>

#define APPID_SONICFRONTIERS 1237320

class SteamHelper
{
public:
	static std::string GetWorkingDirectory()
	{
		wchar_t path[MAX_PATH];
		GetModuleFileNameW(NULL, path, MAX_PATH);
		PathRemoveFileSpecW(path);
		return StringHelper::WideCharToString(path);
	}

	static std::string GetSteamAppsDirectory()
	{
		return StringHelper::GetSubstringBeforeLastChar(GetWorkingDirectory(), '\\', 1);
	}

	static std::string GetSteamUserId(size_t in_appId)
	{
		std::string manifest = GetSteamAppsDirectory().append(std::format("\\appmanifest_{}.acf", in_appId));

		std::ifstream file(manifest);
		std::string line;
		std::string lastOwner;

		while (std::getline(file, line))
		{
			if (line.find("LastOwner") != std::string::npos)
			{
				std::stringstream ss(line);
				std::string key, value;
				ss >> key >> value;
				lastOwner = value.substr(1, value.length() - 2);
				break;
			}
		}

		return lastOwner;
	}
};