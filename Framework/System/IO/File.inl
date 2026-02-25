#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "../Hashing/XXHash64Provider.h"

namespace CMF::System::IO
{
    template <typename THashType, typename THashProvider>
    inline bool TryComputeHash(const std::filesystem::path& in_rPath, THashType& out_rHash)
    {
        if (!std::filesystem::exists(in_rPath))
            return false;

        THashProvider hashProvider{};
        char buffer[0x10000]{};

        std::ifstream file(in_rPath, std::ios::binary);

        if (!file.is_open())
            return false;

        while (!file.eof() && !file.bad())
        {
            file.read(buffer, sizeof(buffer));
            hashProvider.Update(buffer, file.gcount());
        }

        if (file.bad())
            return false;

        out_rHash = hashProvider.Digest();

        return true;
    }

    inline bool File::Compare(const std::filesystem::path& in_rPathA, const std::filesystem::path& in_rPathB)
    {
        if (!std::filesystem::exists(in_rPathA) || !std::filesystem::exists(in_rPathB))
            return false;
        
        uint64_t fileAHash{};
        uint64_t fileBHash{};

        if (!TryComputeHash<uint64_t, CMF::System::Hashing::XXHash64Provider>(in_rPathA, fileAHash))
            return false;

        if (!TryComputeHash<uint64_t, CMF::System::Hashing::XXHash64Provider>(in_rPathB, fileBHash))
            return false;

        return fileAHash == fileBHash;
    }

    inline std::string File::ReadAllText(const std::filesystem::path& in_rPath)
    {
		std::stringstream result{};
		std::ifstream file(in_rPath);

		if (!file.is_open())
			return result.str();

        result << file.rdbuf();

		return result.str();
    }

    inline bool File::WriteAllText(const std::filesystem::path& in_rPath, const std::string& in_rData)
    {
		std::ofstream file(in_rPath);

		if (!file.is_open())
			return false;

		file << in_rData;
		file.close();

		return true;
    }
}