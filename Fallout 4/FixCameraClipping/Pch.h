#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>

// Dependencies
#include <Helpers.h>
#include <Signature.h>

// wtf
typedef uint8_t  UInt8;
typedef uint32_t UInt32;
typedef uint64_t UInt64;

#include <f4se\f4se\PluginAPI.h>