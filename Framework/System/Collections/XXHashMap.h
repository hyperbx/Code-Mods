#pragma once

#include <unordered_map>
#include "..\..\Dependencies\xxHash\xxh3.h"

namespace CMF::System::Collections
{
    struct XXHashKey
    {
        uint64_t operator()(const XXH64_hash_t& in_hash) const noexcept
        {
            return in_hash;
        }
    };

    template <typename T>
    using XXHashMap = std::unordered_map<XXH64_hash_t, T, XXHashKey>;
}