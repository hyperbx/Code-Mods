#pragma once

#include <Windows.h>
#include <Detours\include\detours.h>

#define DECLARE_FUNCTION_PTR(RETURN_TYPE, CALLING_CONVENTION, FUNCTION_NAME, ADDRESS, ...) \
    RETURN_TYPE (CALLING_CONVENTION* FUNCTION_NAME)(__VA_ARGS__) = (RETURN_TYPE (CALLING_CONVENTION*)(__VA_ARGS__))(ADDRESS)

#define DECLARE_LIB_FUNCTION_PTR(RETURN_TYPE, LIBRARY_NAME, FUNCTION_NAME, ...) \
    typedef RETURN_TYPE _##FUNCTION_NAME(__VA_ARGS__);                          \
    _##FUNCTION_NAME* FUNCTION_NAME = (_##FUNCTION_NAME*)GetProcAddress(GetModuleHandle(TEXT(LIBRARY_NAME)), #FUNCTION_NAME);

#define DECLARE_HOOK(RETURN_TYPE, CALLING_CONVENTION, FUNCTION_NAME, ADDRESS, ...) \
    typedef RETURN_TYPE CALLING_CONVENTION FUNCTION_NAME(__VA_ARGS__);             \
    FUNCTION_NAME* original_##FUNCTION_NAME = (FUNCTION_NAME*)(ADDRESS);           \
    RETURN_TYPE CALLING_CONVENTION impl_##FUNCTION_NAME(__VA_ARGS__)

#define DECLARE_VTABLE_HOOK(RETURN_TYPE, CALLING_CONVENTION, CLASS_NAME, FUNCTION_NAME, ...)             \
    typedef RETURN_TYPE CALLING_CONVENTION CLASS_NAME##_##FUNCTION_NAME(CLASS_NAME* pThis, __VA_ARGS__); \
    CLASS_NAME##_##FUNCTION_NAME* original_##CLASS_NAME##_##FUNCTION_NAME;                               \
    RETURN_TYPE CALLING_CONVENTION impl_##CLASS_NAME##_##FUNCTION_NAME(CLASS_NAME* pThis, __VA_ARGS__)

#define DECLARE_ASM_HOOK_32(NAME, ADDRESS) \
    static uint32_t x_##NAME = ADDRESS;    \
    void __declspec(naked) NAME()

#define DECLARE_ASM_HOOK_64(NAME, ADDRESS)  \
    extern "C" uint64_t x_##NAME = ADDRESS; \
    extern "C" void* original_##NAME;       \
    extern "C" void* impl_##NAME;

#define INSTALL_HOOK(FUNCTION_NAME)                                            \
    do                                                                         \
    {                                                                          \
        DetourTransactionBegin();                                              \
        DetourUpdateThread(GetCurrentThread());                                \
        DetourAttach((void**)&original_##FUNCTION_NAME, impl_##FUNCTION_NAME); \
        DetourTransactionCommit();                                             \
    }                                                                          \
    while (0)

#define INSTALL_HOOK_EXPLICIT(FUNCTION_NAME, ADDRESS)                           \
    do                                                                          \
    {                                                                           \
        *(void**)&original_##FUNCTION_NAME = (void*)ADDRESS;                    \
        DetourTransactionBegin();                                               \
        DetourUpdateThread(GetCurrentThread());                                 \
        DetourAttach((void**)&original_##FUNCTION_NAME, &impl_##FUNCTION_NAME); \
        DetourTransactionCommit();                                              \
    }                                                                           \
    while (0)

#define INSTALL_VTABLE_HOOK(CLASS_NAME, OBJECT, FUNCTION_NAME, FUNCTION_INDEX)                                  \
    do                                                                                                          \
    {                                                                                                           \
        if (original_##CLASS_NAME##_##FUNCTION_NAME == nullptr)                                                 \
        {                                                                                                       \
            original_##CLASS_NAME##FUNCTION_NAME = (*(CLASS_NAME##_##FUNCTION_NAME***)OBJECT)[FUNCTION_INDEX];  \
            DetourTransactionBegin();                                                                           \
            DetourUpdateThread(GetCurrentThread());                                                             \
            DetourAttach((void**)&original##CLASS_NAME##_##FUNCTION_NAME, impl_##CLASS_NAME##_##FUNCTION_NAME); \
            DetourTransactionCommit();                                                                          \
        }                                                                                                       \
    }                                                                                                           \
    while (0)

#define INSTALL_ASM_HOOK_32(NAME) \
    WRITE_JUMP(x_##NAME, &NAME)

#define INSTALL_ASM_HOOK_32_EXPLICIT(NAME, ADDRESS) \
    WRITE_JUMP(ADDRESS, &NAME)

#define INSTALL_ASM_HOOK_64(NAME) \
    INSTALL_HOOK_ADDRESSED(NAME, x_##NAME)

#define INSTALL_ASM_HOOK_64_EXPLICIT(NAME, ADDRESS) \
    INSTALL_HOOK_ADDRESSED(NAME, ADDRESS)
