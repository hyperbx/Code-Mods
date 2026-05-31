#pragma once

// Code Mods Framework

#ifdef __cplusplus
#include <cstdint>
#endif

#include "System/System.h"

#if defined(__cplusplus) && !defined(CMF_EXCLUDE_NAMESPACE_ALIASES)
namespace cmf = CMF;

namespace CMF
{
    namespace sys = System;

    namespace System
    {
        namespace col = Collections;
        namespace cfg = Configuration;
        namespace glb = Globalization;
        namespace hash = Hashing;
        namespace io = IO;
        namespace mem = Memory;
        namespace num = Numerics;
        namespace utils = Utilities;
    }
}
#endif