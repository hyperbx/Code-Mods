#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace CMF::System::Configuration
{
    class Ini
    {
    public:
        std::map<std::string, std::map<std::string, std::string>> Data{};

        Ini() {}

        Ini(const std::filesystem::path& in_rPath)
        {
            Read(in_rPath);
        }

        void Read(const std::filesystem::path& in_rPath);
        std::vector<std::string> GetSections() const;
        std::vector<std::map<std::string, std::string>> GetValues(const std::string& in_rSection = "") const;

        template <typename T = std::string>
        T Get(const std::string& in_rSection, const std::string& in_rKey, const T in_defaultValue = T());
    };
}

#include "Ini.inl"
