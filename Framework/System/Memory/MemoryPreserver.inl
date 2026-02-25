#include "Memory.h"

namespace CMF::System::Memory
{
    inline void MemoryPreserver::Preserve(const void* in_pAddress, const size_t in_length, const bool in_overwrite)
    {
        if (!in_pAddress)
            return;

        if (m_PreservedMemory.find(in_pAddress) != m_PreservedMemory.end())
        {
            if (in_overwrite)
            {
                m_PreservedMemory.erase(in_pAddress);
            }
            else
            {
                return;
            }
        }

        auto pBuffer = new uint8_t[in_length];
        
        memcpy_s(pBuffer, in_length, in_pAddress, in_length);

        m_PreservedMemory.emplace(in_pAddress, std::vector<uint8_t>(pBuffer, pBuffer + in_length));

        delete pBuffer;
    }

    inline void MemoryPreserver::Restore(const void* in_pAddress)
    {
        if (!in_pAddress)
            return;

        if (m_PreservedMemory.find(in_pAddress) == m_PreservedMemory.end())
            return;

        auto& v = m_PreservedMemory.at(in_pAddress);

        for (size_t i = 0; i < v.size(); i++)
            Write<uint8_t>(((uint8_t*)in_pAddress) + i, v[i]);
    }
}