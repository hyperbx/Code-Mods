#pragma once

#include <IOHelper.h>
#include <json.h>

using json = nlohmann::json;

class LanguageHelper
{
	static inline json m_resource;

public:
	static void Read(std::string in_resourcePath)
	{
		if (!IOHelper::FileExists(in_resourcePath))
			return;

		m_resource = json::parse(IOHelper::ReadString(in_resourcePath));
	}

	static void Merge(std::string in_resourcePath)
	{
		if (!IOHelper::FileExists(in_resourcePath))
			return;

		auto source = json::parse(IOHelper::ReadString(in_resourcePath));

		m_resource.merge_patch(source);
	}

	static std::string Localise(std::string in_key)
	{
		if (in_key.empty())
			return in_key;

		if (m_resource.empty())
			return in_key;

		if (!m_resource.contains(in_key))
			return in_key;

		return m_resource[in_key];
	}
};
