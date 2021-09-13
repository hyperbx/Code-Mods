#pragma once

#include <Psapi.h>

inline bool sigValid = true;

inline MODULEINFO moduleInfo;

inline const MODULEINFO& getModuleInfo()
{
    if (moduleInfo.SizeOfImage)
        return moduleInfo;

    ZeroMemory(&moduleInfo, sizeof(MODULEINFO));
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(MODULEINFO));

    return moduleInfo;
}

inline void* sigScan(const char* signature, const char* mask)
{
    const MODULEINFO& moduleInfo = getModuleInfo();
    const size_t length = strlen(mask);

    for (size_t i = 0; i < moduleInfo.SizeOfImage; i++)
    {
        char* memory = (char*)moduleInfo.lpBaseOfDll + i;

        size_t j;
        for (j = 0; j < length; j++)
        {
            if (mask[j] != '?' && signature[j] != memory[j])
                break;
        }

        if (j == length)
            return memory;
    }

    return nullptr;
}

#define SIG_SCAN(x, signature, mask) \
    void* _##x; \
    void* x() \
    { \
        if (!_##x) \
        { \
            _##x = sigScan(signature, mask); \
            sigValid = false; \
        } \
        printf("[Signature] %s received: 0x%08x\n", #x, _##x); \
        return _##x; \
    }