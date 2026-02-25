#include <Windows.h>
#include <Psapi.h>

namespace CMF::System::Memory
{
    inline void* SignatureScanner::Scan(const char* in_pPattern, const char* in_pMask, void* in_pBegin)
    {
        MODULEINFO moduleInfo{};

        ZeroMemory(&moduleInfo, sizeof(moduleInfo));
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(moduleInfo));

        if (!in_pBegin)
            in_pBegin = moduleInfo.lpBaseOfDll;

        return ScanImpl(in_pPattern, in_pMask, in_pBegin, moduleInfo.SizeOfImage);
    }
}
