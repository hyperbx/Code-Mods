#pragma once

#include <IOHelper.h>
#include <json.h>

using json = nlohmann::json;

class LanguageHelper
{
	static inline json m_Resource;

public:
	static void Read(std::string in_resourcePath)
	{
		if (!IOHelper::FileExists(in_resourcePath))
			return;

		m_Resource = json::parse(IOHelper::ReadString(in_resourcePath));
	}

	static std::string Localise(std::string in_key)
	{
		if (m_Resource.empty())
			return "Error";

		return m_Resource[in_key];
	}
};
