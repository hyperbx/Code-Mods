#pragma once

#include <vector>

#ifdef BASE_ADDRESS
#define ASLR(ADDRESS)                                     CMF::System::Memory::TransformVirtualAddressToASLR((void*)(ADDRESS), BASE_ADDRESS)
#else                                                     
#define ASLR(ADDRESS)                                     (void*)(ADDRESS)
#endif                                                    
                                                          
#define IS_NOP(ADDRESS)                                   CMF::System::Memory::IsNop((void*)(ADDRESS))

#define READ(ADDRESS, TYPE)                               CMF::System::Memory::Read<TYPE>((void*)(ADDRESS))
#define READ_INSTR_ADDRESS(ADDRESS, TYPE, OFFSET, STRIDE) CMF::System::Memory::ReadInstructionAddress<TYPE>((void*)(ADDRESS), OFFSET, STRIDE)
#define READ_CALL(ADDRESS)                                CMF::System::Memory::ReadCall((void*)(ADDRESS))
#define READ_JUMP(NAME, ADDRESS)                          CMF::System::Memory::ReadJump((void*)(ADDRESS))

#define WRITE(ADDRESS, TYPE, ...)                         CMF::System::Memory::Write<TYPE>((void*)(ADDRESS), { __VA_ARGS__ })
#define WRITE_ARRAY(ADDRESS, TYPE, DATA)                  CMF::System::Memory::Write<TYPE>((void*)(ADDRESS), DATA)
#define WRITE_CALL(ADDRESS, DESTINATION)                  CMF::System::Memory::WriteCall((void*)(ADDRESS), (void*)(DESTINATION))
#define WRITE_JUMP(ADDRESS, DESTINATION)                  CMF::System::Memory::WriteJump((void*)(ADDRESS), (void*)(DESTINATION))
#define WRITE_NOP(ADDRESS, LENGTH)                        CMF::System::Memory::WriteNop((void*)(ADDRESS), LENGTH)
#define WRITE_STRING(ADDRESS, STR)                        CMF::System::Memory::WriteString((void*)(ADDRESS), STR)

namespace CMF::System::Memory
{
    static void* TransformVirtualAddressToASLR(void* in_pAddress, void* in_pBaseAddress);

    static bool IsNop(void* in_pAddress);

    template <typename T>
    static T Read(void* in_pAddress);

    template <typename T>
    static void* ReadInstructionAddress(void* in_pAddress, size_t in_offset, size_t in_stride);

    static void* ReadCall(void* in_pAddress);
    static void* ReadJump(void* in_pAddress);

    template <typename T>
    static void Write(void* in_pAddress, T in_data);

    template <typename T>
    static void Write(void* in_pAddress, const std::vector<T> in_data);

    static void WriteCall(void* in_pAddress, void* in_pDestination);
    static void WriteJump(void* in_pAddress, void* in_pDestination, bool in_isCall = false);
    static void WriteNop(void* in_pAddress, size_t in_length);
    static void WriteString(void* in_pAddress, const char* in_pStr);
}

#include "MemoryPreserver.h"
#include "SignatureScanner.h"

#ifdef WIN32
#include "MemoryWin32.h"
#endif