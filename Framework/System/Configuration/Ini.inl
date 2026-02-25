#include <fstream>
#include "../Utilities/StringHelper.h"

namespace CMF::System::Configuration
{
    inline void Ini::Read(const std::filesystem::path& in_rPath)
    {
        std::ifstream file(in_rPath);

        if (!file.is_open() || file.bad())
            return;

        std::string section{};
        std::string line{};

        // Add root section.
        Data[section] = std::map<std::string, std::string>();

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            if (line.front() == '[' && line.back() == ']')
            {
                section = line.substr(1, line.length() - 2);
                Data[section] = std::map<std::string, std::string>();
                continue;
            }

            if (line.front() == ';' || line.front() == '#')
                continue;

            auto delimiterIndex = line.find('=');

            if (delimiterIndex == std::string::npos)
                continue;

            auto key = line.substr(0, delimiterIndex);
            auto value = line.substr(delimiterIndex + 1);

            if (value.front() == '"' && value.back() == '"' && value.length() > 1)
                value = value.substr(1, value.length() - 2);

            Data[section][key] = value;
        }
    }

    inline std::vector<std::string> Ini::GetSections() const
    {
        std::vector<std::string> result{};

        for (const auto& [rKey, rValue] : Data)
            result.push_back(rKey);

        return result;
    }

    inline std::vector<std::map<std::string, std::string>> Ini::GetValues(const std::string& in_rSection) const
    {
        std::vector<std::map<std::string, std::string>> result{};

        for (const auto& [rKey, rValue] : Data)
        {
            if (!in_rSection.empty() && in_rSection != rKey)
                continue;

            result.push_back(rValue);
        }

        return result;
    }

    template <typename T>
    inline T Ini::Get(const std::string& in_rSection, const std::string& in_rKey, const T in_defaultValue)
    {
        if (!Data.count(in_rSection))
            return in_defaultValue;

        if (!Data[in_rSection].count(in_rKey))
            return in_defaultValue;

        auto& value = Data[in_rSection][in_rKey];

        if constexpr (std::is_same_v<T, std::string&>)
        {
            return value;
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            return std::string(value);
        }
        else if constexpr (std::is_same_v<T, const char*>)
        {
            return value.c_str();
        }
        else
        {
            T result{};

            if (!CMF::System::Utilities::StringHelper::TryParse<T>(value, result))
                return in_defaultValue;

            return result;
        }

        return in_defaultValue;
    }
}
