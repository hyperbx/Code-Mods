#pragma once

#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#define DECLARE_SIGNATURE_SCAN(NAME, ...) \
    FORCEINLINE void* NAME();             \
    inline void* x_##NAME = NAME();       \
    FORCEINLINE void* NAME() { return x_##NAME ? x_##NAME : (x_##NAME = CMF::System::Memory::SignatureScanner::Scan({ __VA_ARGS__ })); }

namespace CMF::System::Memory
{
    struct SignatureScannerStatus
    {
        bool Success{ true };
        const char* pMessage{};
        const char* pPattern{};
        const char* pMask{};

        std::string GetPatternString() const
        {
            if (!pPattern || !pMask)
                return "";
            
            std::stringstream result{};
            const auto length = strlen(pMask);
            
            for (size_t i = 0; i < length; i++)
            {
                result << "\\x"
                       << std::uppercase
                       << std::hex
                       << std::setw(2)
                       << std::setfill('0')
                       << static_cast<uint32_t>(static_cast<uint8_t>(pPattern[i]));
            }
            
            return result.str();
        }
    };

    class SignatureScanner
    {
        static void* ScanImpl(const char* in_pPattern, const char* in_pMask, void* in_pBegin, const size_t in_length);

    public:
        inline static SignatureScannerStatus Status{};

        static void Reset()
        {
            Status = { true };
        }

        static void* Scan(const char* in_pPattern, const char* in_pMask, void* in_pBegin = nullptr);
        static void* Scan(std::vector<std::tuple<const char*, const char*>> in_patterns);
    };
}

#include "SignatureScannerImpl.inl"

#if defined(CMF_USE_COMMONLOADER_SIGNATURE_SCANNER)
#include "SignatureScannerCommonLoader.inl"
#elif defined(WIN32)
#include "SignatureScannerWin32.inl"
#endif