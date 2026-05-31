#pragma once

namespace CMF::System::Configuration::Registry
{
    static bool Init();

    template <typename T>
    static bool Read(const std::filesystem::path& in_rPath, T& out_rData);

    template <typename T>
    static bool Write(const std::filesystem::path& in_rPath, const T& out_rData);
}

#ifdef WIN32
#include "RegistryWin32.inl"
#endif
