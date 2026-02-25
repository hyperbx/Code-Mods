#pragma once

// Code Mods Framework

#include <cstdint>

#include "System/System.h"

#ifndef CMF_EXCLUDE_NAMESPACE_ALIASES
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