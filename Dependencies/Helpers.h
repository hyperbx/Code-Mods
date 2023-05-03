#pragma once

#ifndef offsetof
#define offsetof(s, m) ((size_t)&(((s*)0)->m))
#endif

#define EXPORT extern "C" __declspec(dllexport)

#define PRINT_BOOL(a) printf(#a " = %s\n", a ? "TRUE" : "FALSE")

#define INI_READ_STRING(section, var)     var = reader.Get(section, #var, var)
#define INI_READ_BOOLEAN(section, var)    var = reader.GetBoolean(section, #var, var)
#define INI_READ_FLOAT(section, var)      var = reader.GetFloat(section, #var, var)
#define INI_READ_INTEGER(section, var)    var = reader.GetInteger(section, #var, var)
#define INI_READ_DOUBLE(section, var)     var = reader.GetReal(section, #var, var)
#define INI_READ_ENUM(section, type, var) var = (type)reader.GetInteger(section, #var, var)

#define READ_CALL(addr) ((int64_t)addr + *(int32_t*)((int64_t)addr + 1)) + 5

#define READ_JUMP(name, addr) \
size_t name = 0; \
int8_t jmpType##name = 0; \
uint8_t opcode##name = *(uint8_t*)((size_t)addr); \
if ((opcode##name & 0xF0) == 0x70) \
{ \
    jmpType##name = 0;\
} \
else \
{ \
    switch (opcode##name) \
    { \
        case 0xE3: \
        case 0xEB: \
            jmpType##name = 0; \
            break; \
        case 0xE9: \
            jmpType##name = 1; \
            break; \
        case 0x0F: \
            jmpType##name = 2; \
            break; \
        case 0xFF: \
            jmpType##name = 3; \
            break; \
    } \
} \
switch (jmpType##name) \
{ \
    case 0: \
        name = ((size_t)addr + *(int8_t*)((size_t)addr + 1)) + 2; \
        break; \
    case 1: \
        name = ((size_t)addr + *(int32_t*)((size_t)addr + 1)) + 5; \
        break; \
    case 2: \
        name = ((size_t)addr + *(int32_t*)((size_t)addr + 2)) + 6; \
        break; \
    case 3: \
        name = *(int64_t*)((size_t)addr + 6); \
        break; \
} \

#define _CONCAT2(x, y) x##y
#define CONCAT2(x, y) _CONCAT(x, y)
#define INSERT_PADDING(length) \
    uint8_t CONCAT2(pad, __LINE__)[length]

#define ASSERT_OFFSETOF(type, field, offset) \
    static_assert(offsetof(type, field) == offset, "offsetof assertion failed")

#define ASSERT_SIZEOF(type, size) \
    static_assert(sizeof(type) == size, "sizeof assertion failed")

#ifdef BASE_ADDRESS
const HMODULE MODULE_HANDLE = GetModuleHandle(nullptr);

#define ASLR(address) \
    ((size_t)MODULE_HANDLE + (size_t)address - (size_t)BASE_ADDRESS)
#endif

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
    returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)

#define INLINE_FUNCTION_PTR(functionPtr, function, ...) \
    functionPtr; function(__VA_ARGS__)
    
#define PROC_ADDRESS(libraryName, procName) \
    GetProcAddress(LoadLibrary(TEXT(libraryName)), procName)

#define LIB_FUNCTION(returnType, libraryName, procName, ...) \
    typedef returnType _##procName(__VA_ARGS__); \
    _##procName* procName = (_##procName*)GetProcAddress(GetModuleHandle(TEXT(libraryName)), #procName);

#define ASM_HOOK(startAddress, functionName) \
	static uint32_t functionName##StartAddress = startAddress; \
	void __declspec(naked) functionName()

#define HOOK(returnType, callingConvention, functionName, location, ...) \
    typedef returnType callingConvention functionName(__VA_ARGS__); \
    functionName* original##functionName = (functionName*)(location); \
    returnType callingConvention implOf##functionName(__VA_ARGS__)

#define INLINE_HOOK(returnType, callingConvention, functionName, location, ...) \
    typedef returnType callingConvention functionName(__VA_ARGS__); \
    inline static functionName* original##functionName = (functionName*)(location); \
    inline static returnType callingConvention implOf##functionName(__VA_ARGS__)

#define INSTALL_HOOK(functionName) \
{ \
    DetourTransactionBegin(); \
    DetourUpdateThread(GetCurrentThread()); \
    DetourAttach((void**)&original##functionName, implOf##functionName); \
    DetourTransactionCommit(); \
}

#define VTABLE_HOOK(returnType, callingConvention, className, functionName, ...) \
    typedef returnType callingConvention className##functionName(className* This, __VA_ARGS__); \
    className##functionName* original##className##functionName; \
    returnType callingConvention implOf##className##functionName(className* This, __VA_ARGS__)

#define INSTALL_VTABLE_HOOK(className, object, functionName, functionIndex) \
    do { \
        if (original##className##functionName == nullptr) \
        { \
            original##className##functionName = (*(className##functionName***)object)[functionIndex]; \
            DetourTransactionBegin(); \
            DetourUpdateThread(GetCurrentThread()); \
            DetourAttach((void**)&original##className##functionName, implOf##className##functionName); \
            DetourTransactionCommit(); \
        } \
    } while(0)

#define WRITE_MEMORY(location, type, ...) \
{ \
    const type data[] = { __VA_ARGS__ }; \
    DWORD oldProtect; \
    VirtualProtect((void*)(location), sizeof(data), PAGE_EXECUTE_READWRITE, &oldProtect); \
    memcpy((void*)(location), data, sizeof(data)); \
    VirtualProtect((void*)(location), sizeof(data), oldProtect, &oldProtect); \
}

#define WRITE_STATIC_MEMORY(location, data, size) \
{ \
    DWORD oldProtect; \
    VirtualProtect((void*)(location), size, PAGE_EXECUTE_READWRITE, &oldProtect); \
    memcpy((void*)(location), data, size); \
    VirtualProtect((void*)(location), size, oldProtect, &oldProtect); \
}

#define WRITE_JUMP(source, destination) \
{ \
    int length = (size_t)(destination) - (size_t)(source); \
    if (length - 2 <= 0x7F) \
    { \
        WRITE_MEMORY(source, uint8_t, 0xEB); \
        WRITE_MEMORY(source + 1, uint8_t, length - 2); \
    } \
    else \
    { \
        WRITE_MEMORY(source, uint8_t, 0xE9); \
        WRITE_MEMORY(source + 1, uint32_t, length - 5); \
    } \
}

#define INSTALL_ASM_HOOK(functionName) \
    WRITE_JUMP(functionName##StartAddress, &functionName);

#define WRITE_CALL(location, function) \
{ \
    WRITE_MEMORY(location, uint8_t, 0xE8); \
    WRITE_MEMORY(location + 1, uint32_t, (uint32_t)(function) - (size_t)(location) - 5); \
}

#define WRITE_NOP(location, count) \
{ \
    DWORD oldProtect; \
    VirtualProtect((void*)(location), (size_t)(count), PAGE_EXECUTE_READWRITE, &oldProtect); \
    for (size_t i = 0; i < (size_t)(count); i++) \
        *((uint8_t*)(location) + i) = 0x90; \
    VirtualProtect((void*)(location), (size_t)(count), oldProtect, &oldProtect); \
}

#define WRITE_STRING(location, STR) \
{ \
    DWORD oldProtect; \
    VirtualProtect((void*)location, sizeof(STR), PAGE_EXECUTE_READWRITE, &oldProtect); \
    memcpy((void*)location, STR, sizeof(STR)); \
    VirtualProtect((void*)location, sizeof(STR), oldProtect, NULL); \
}

#define READ_POINTER(name, location, ...) \
const std::vector<uint32_t> name##offsets = { __VA_ARGS__ }; \
uint32_t name = *(uint32_t*)location; \
{ \
    for (uint32_t i = 0; i < name##offsets.size(); i++) \
    { \
        uint32_t const& offset = name##offsets[i]; \
        { \
            name += offset; \
            if (i < name##offsets.size() - 1) \
                name = *(uint32_t*)name; \
        } \
    } \
}

#define LERP(a, b, t) (a + (b - a) * t)

#define SIGN(a) (a < 0 ? a * -1 : a)