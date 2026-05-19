#pragma once

#include <Windows.h>

namespace CMF::System::Memory
{
    inline static const HMODULE g_hModule = GetModuleHandle(nullptr);

    inline void* TransformVirtualAddressToASLR(void* in_pAddress, void* in_pBaseAddress)
    {
        return (void*)((size_t)g_hModule + (size_t)in_pAddress - (size_t)in_pBaseAddress);
    }

    inline bool IsNop(void* in_pAddress)
    {
        return in_pAddress && Read<uint8_t>(in_pAddress) == 0x90;
    }

    template <typename T>
    inline T Read(void* in_pAddress)
    {
        return *(T*)in_pAddress;
    }

    template <typename T>
    inline void* ReadInstructionAddress(void* in_pAddress, size_t in_offset, size_t in_stride)
    {
        if (!in_pAddress)
            return nullptr;

        return (void*)(((size_t)in_pAddress + *(T*)((size_t)in_pAddress + in_offset)) + in_stride);
    }

    inline void* ReadCall(void* in_pAddress)
    {
        if (!in_pAddress)
            return nullptr;

        return ReadInstructionAddress<int32_t>(in_pAddress, 1, 5);
    }

    inline void* ReadJump(void* in_pAddress)
    {
        if (!in_pAddress)
            return nullptr;

        void* result{};

        auto opcode = Read<uint8_t>(in_pAddress);
        auto jmpType = -1;
        
        if ((opcode & 0xF0) == 0x70)
        {
            jmpType = 0;
        }
        else
        {
            switch (opcode)
            {
                case 0xE3:
                case 0xEB:
                    jmpType = 0;
                    break;

                case 0xE9:
                    jmpType = 1;
                    break;

                case 0x0F:
                    jmpType = 2;
                    break;

                case 0xFF:
                    jmpType = 3;
                    break;
            }
        }
        
        switch (jmpType)
        {
            case 0:
                result = ReadInstructionAddress<int8_t>(in_pAddress, 1, 2);
                break;

            case 1:
                result = ReadInstructionAddress<int32_t>(in_pAddress, 1, 5);
                break;

            case 2:
                result = ReadInstructionAddress<int32_t>(in_pAddress, 2, 6);
                break;

            case 3:
                result = ReadInstructionAddress<int64_t>(in_pAddress, 6, 0);
                break;
        }
        
        return result;
    }

    template <typename T>
    inline void Write(void* in_pAddress, T in_data)
    {
        if (!in_pAddress)
            return;

        DWORD oldProtect{};

        VirtualProtect(in_pAddress, sizeof(in_data), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(in_pAddress, &in_data, sizeof(in_data));
        VirtualProtect(in_pAddress, sizeof(in_data), oldProtect, &oldProtect);
    }

    template <typename T>
    inline void Write(void* in_pAddress, const std::vector<T> in_data)
    {
        if (!in_pAddress)
            return;

        DWORD oldProtect{};

        auto length = sizeof(T) * in_data.size();

        VirtualProtect(in_pAddress, length, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(in_pAddress, in_data.data(), length);
        VirtualProtect(in_pAddress, length, oldProtect, &oldProtect);
    }

    inline void WriteCall(void* in_pAddress, void* in_pDestination)
    {
        WriteJump(in_pAddress, in_pDestination, true);
    }

    inline void WriteJump(void* in_pAddress, void* in_pDestination, bool in_isCall)
    {
        if (!in_pAddress)
            return;

        auto length = (size_t)in_pDestination - (size_t)in_pAddress;

        if (length - 2 <= 0x7F && !in_isCall)
        {
            Write<uint8_t>(in_pAddress, 0xEB);
            Write<uint8_t>(((uint8_t*)in_pAddress) + 1, uint8_t(length - 2));
        }
        else
        {
            if (length - 5 <= 0x7FFFFFFF)
            {
                Write<uint8_t>(in_pAddress, in_isCall ? 0xE8 : 0xE9);
                Write<uint32_t>(((uint8_t*)in_pAddress) + 1, uint32_t(length - 5));
            }
#ifdef WIN64
            else
            {
                Write<uint8_t>(in_pAddress, 0xFF);
                Write<uint8_t>(((uint8_t*)in_pAddress) + 1, in_isCall ? 0x15 : 0x25);
                Write<uint32_t>(((uint8_t*)in_pAddress) + 2, 0);
                Write<uint64_t>(((uint8_t*)in_pAddress) + 6, uint64_t(length - 14));
            }
#endif
        }
    }

    inline void WriteNop(void* in_pAddress, size_t in_length)
    {
        if (!in_pAddress)
            return;

        DWORD oldProtect{};

        VirtualProtect(in_pAddress, in_length, PAGE_EXECUTE_READWRITE, &oldProtect);

        for (size_t i = 0; i < in_length; i++)
            *(((uint8_t*)in_pAddress) + i) = 0x90;

        VirtualProtect(in_pAddress, in_length, oldProtect, &oldProtect);
    }

    inline void WriteString(void* in_pAddress, const char* in_pStr)
    {
        if (!in_pAddress)
            return;

        DWORD oldProtect{};

        auto length = strlen(in_pStr);

        VirtualProtect(in_pAddress, length, PAGE_EXECUTE_READWRITE, &oldProtect);
        strcpy((char*)in_pAddress, in_pStr);
        VirtualProtect(in_pAddress, length, oldProtect, &oldProtect);
    }
}
