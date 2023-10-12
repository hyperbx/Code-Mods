#pragma once

#include <filesystem>
#include <IOHelper.h>
#include <miniaudio.h>
#include <rangers-api/rangers-api/rangers-api.h>
#include <string>
#include <unordered_map>

class SoundManager
{
	inline static ma_engine m_Engine;
	inline static bool m_IsInitialised = false;
	inline static std::filesystem::path m_ResourcePath;
	inline static std::unordered_map<size_t, ma_sound> m_Sounds;

public:
	static bool Init()
	{
		if (m_IsInitialised)
			return true;

		if (ma_engine_init(NULL, &m_Engine) != MA_SUCCESS)
			return false;

		return (m_IsInitialised = true);
	}

	static bool IsContextSafe()
	{
		return Init() && !m_ResourcePath.empty();
	}

	static void SetResourcePath(std::filesystem::path in_resourcePath)
	{
		m_ResourcePath = in_resourcePath;
	}

	static void PlayFile(std::string in_fileName)
	{
		if (!IsContextSafe())
			return;

		auto path = m_ResourcePath / (in_fileName + std::string(".wav"));

		if (!IOHelper::FileExists(path.string()))
			return;

		ma_engine_play_sound(&m_Engine, path.string().c_str(), NULL);
	}
};

