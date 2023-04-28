#pragma once

#include <CommonLoaderAPI.h>
#include <Psapi.h>

inline bool m_IsSigValid = true;

#if CL_SCANNER

#define CL_SCAN_SIGNATURE(x, ...) \
FORCEINLINE void* x(); \
inline void* x##Addr = x(); \
FORCEINLINE void* x() \
{ \
    if (x##Addr) \
        return x##Addr; \
    CommonLoader_GetAPI()->SetState(CMN_LOADER_STATE_SKIP_SIG_VALIDATION, 1); \
    x##Addr = CommonLoader_GetAPI()->ScanSignature(__VA_ARGS__); \
    printf("[Signature] %s received: 0x%llx\n", #x, x##Addr); \
    if (x##Addr == nullptr) \
        m_IsSigValid = false; \
    return x##Addr; \
}

#define CL_SCAN_SIGNATURE_ALLOW_NULL(x, ...) \
FORCEINLINE void* x(); \
inline void* x##Addr = x(); \
FORCEINLINE void* x() \
{ \
    if (x##Addr) \
        return x##Addr; \
    CommonLoader_GetAPI()->SetState(CMN_LOADER_STATE_SKIP_SIG_VALIDATION, 1); \
    x##Addr = CommonLoader_GetAPI()->ScanSignature(__VA_ARGS__); \
    printf("[Signature] %s received: 0x%llx\n", #x, x##Addr); \
    return x##Addr; \
}

#else

inline MODULEINFO moduleInfo;

inline const MODULEINFO& GetModuleInfo()
{
    if (moduleInfo.SizeOfImage)
        return moduleInfo;

    ZeroMemory(&moduleInfo, sizeof(MODULEINFO));
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(MODULEINFO));

    return moduleInfo;
}

inline void* ScanSignature(const char* signature, const char* mask)
{
    const MODULEINFO& moduleInfo = GetModuleInfo();
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

#define CL_SCAN_SIGNATURE(x, ...) \
FORCEINLINE void* x(); \
inline void* x##Addr = x(); \
FORCEINLINE void* x() \
{ \
    if (x##Addr) \
        return x##Addr; \
    x##Addr = ScanSignature(__VA_ARGS__); \
    printf("[Signature] %s received: 0x%llx\n", #x, x##Addr); \
    if (x##Addr == nullptr) \
        m_IsSigValid = false; \
    return x##Addr; \
}

#define CL_SCAN_SIGNATURE_ALLOW_NULL(x, ...) \
FORCEINLINE void* x(); \
inline void* x##Addr = x(); \
FORCEINLINE void* x() \
{ \
    if (x##Addr) \
        return x##Addr; \
    x##Addr = ScanSignature(__VA_ARGS__); \
    printf("[Signature] %s received: 0x%llx\n", #x, x##Addr); \
    return x##Addr; \
}

#endif