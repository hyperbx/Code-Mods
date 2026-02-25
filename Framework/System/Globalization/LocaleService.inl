#include "../System/IO/File.h"

namespace CMF::System::Globalization
{
    inline void LocaleService::Read(const std::filesystem::path& in_rPath)
    {
        if (!std::filesystem::exists(in_rPath))
            return;

        m_Resource = nlohmann::json::parse(CMF::System::IO::File::ReadAllText(in_rPath));
    }

    inline void LocaleService::Merge(const std::filesystem::path& in_rPath)
    {
        if (!std::filesystem::exists(in_rPath))
            return;

        m_Resource.merge_patch(nlohmann::json::parse(CMF::System::IO::File::ReadAllText(in_rPath)));
    }

    inline void LocaleService::Merge(const nlohmann::json& in_rJson)
    {
        m_Resource.merge_patch(in_rJson);
    }

    inline std::string LocaleService::Get(std::string in_rKey)
    {
        if (in_rKey.empty())
            return in_rKey;

        if (m_Resource.empty())
            return in_rKey;

        if (!m_Resource.contains(in_rKey))
            return in_rKey;

        return m_Resource[in_rKey];
    }
}
