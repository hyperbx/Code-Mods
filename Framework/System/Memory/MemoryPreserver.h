#pragma once

#include <unordered_map>

namespace CMF::System::Memory
{
    class MemoryPreserver
    {
        inline static std::unordered_map<const void*, std::vector<uint8_t>> m_PreservedMemory{};

    public:
        static void Preserve(const void* in_pAddress, const size_t in_length, const bool in_overwrite = false);
        static void Restore(const void* in_pAddress);
    };
}

#include "MemoryPreserver.inl"
