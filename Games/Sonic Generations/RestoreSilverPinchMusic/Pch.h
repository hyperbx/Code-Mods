#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <BlueBlur/BlueBlur.h>

#include <cstdint>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Restore Silver Pinch Music"
#define MOD_AUTHOR "Hyper"

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 0, 0 } };
