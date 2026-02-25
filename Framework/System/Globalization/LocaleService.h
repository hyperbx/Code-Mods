#pragma once

#include <filesystem>
#include <json.h>

namespace CMF::System::Globalization
{
    class LocaleService
    {
        inline static nlohmann::json m_Resource;

    public:
        static void Read(const std::filesystem::path& in_rPath);
        static void Merge(const std::filesystem::path& in_rPath);
        static void Merge(const nlohmann::json& in_rResource);
        static std::string Get(std::string in_rKey);
    };
}

#include "LocaleService.inl"
