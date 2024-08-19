#pragma once

#define INI std::map<std::string, std::map<std::string, std::string>>

class BasicIniReader
{
public:
    inline static INI Read(const std::string& in_path)
    {
        INI result;

        std::ifstream file(in_path);

        if (!file.is_open())
            return result;

        std::string section = "";
        std::string line;

        // Add root section.
        result[section] = std::map<std::string, std::string>();

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            if (line.front() == '[' && line.back() == ']')
            {
                section = line.substr(1, line.length() - 2);
                result[section] = std::map<std::string, std::string>();
                continue;
            }

            if (line.front() == ';' || line.front() == '#')
                continue;

            size_t delimiterIndex = line.find('=');

            if (delimiterIndex == std::string::npos)
                continue;

            std::string key = line.substr(0, delimiterIndex);
            std::string value = line.substr(delimiterIndex + 1);

            if (value.front() == '"' && value.back() == '"' && value.length() > 1)
                value = value.substr(1, value.length() - 2);

            result[section][key] = value;
        }

        return result;
    }
};

