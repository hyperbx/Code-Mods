#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <cstdint>
#include <cstdio>
#include <unordered_map>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Fix Analog Deadzone"
#define MOD_AUTHOR "Hyper"
#define LOG_SOURCE MOD_NAME

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 0, 0 } };
