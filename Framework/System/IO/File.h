#pragma once

#include <filesystem>
#include <string>

#include "../Hashing/IHashProvider.h"

namespace CMF::System::IO
{
    class File
    {
    public:
        template <typename THashType, typename THashProvider = CMF::System::Hashing::IHashProvider<THashType>>
        static bool TryComputeHash(const std::filesystem::path& in_rPath, THashType& out_rHash);
        static bool Compare(const std::filesystem::path& in_rPathA, const std::filesystem::path& in_rPathB);
        static std::string ReadAllText(const std::filesystem::path& in_rPath);
        static bool WriteAllText(const std::filesystem::path& in_rPath, const std::string& in_rData);
    };
}

#include "File.inl"
