#pragma once

namespace CMF::System::Hashing
{
    template <typename T>
    class IHashProvider
    {
    public:
        virtual bool Reset() = 0;
        virtual bool Update(const uint8_t* in_pData, const size_t in_length) = 0;
        virtual T Digest() = 0;
    };
}