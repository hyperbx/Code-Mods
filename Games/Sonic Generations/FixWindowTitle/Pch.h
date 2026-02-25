#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <cstdint>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Fix Window Title"
#define MOD_AUTHOR "Hyper"

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 0, 0 } };

#include "Resources.h"
