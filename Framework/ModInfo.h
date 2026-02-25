#pragma once

#include <format>
#include <string>

struct ModVersion
{
    int Major{ 1 };
    int Minor{ 0 };
    int Revision{ 0 };

    constexpr uint32_t ToUInt32() const
    {
        return (Major >> 16) | (Minor >> 8) | Revision;
    }

    std::string ToString() const
    {
        return std::format("{}.{}.{}", Major, Minor, Revision);
    }
};

struct ModInfo
{
    std::string Name{};
    std::string Author{};
    ModVersion Version{};
};
