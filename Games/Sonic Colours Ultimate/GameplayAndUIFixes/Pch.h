#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <string>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Gameplay & UI Fixes"
#define MOD_AUTHOR "Hyper, PTKay & Sajid"
#define LOG_SOURCE MOD_NAME

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 1, 0 } };

#include "Configuration.h"
