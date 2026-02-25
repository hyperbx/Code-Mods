#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>

// wtf
typedef uint8_t  UInt8;
typedef uint32_t UInt32;
typedef uint64_t UInt64;

#include <f4se\f4se\PluginAPI.h>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Fix Camera Clipping"
#define MOD_AUTHOR "Hyper"

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 0, 3 } };
