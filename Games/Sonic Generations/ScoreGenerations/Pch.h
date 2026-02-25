#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <BlueBlur.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <stdint.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <xmmintrin.h>

#include <HE1ML/Source/ModLoader.h>
#include <Lua/include/lua.hpp>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Score Generations"
#define MOD_AUTHOR "Hyper"
#define LOG_SOURCE MOD_NAME

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 2, 0, 0 } };

#include "Configuration.h"

inline static const char* g_pStageID = (const char*)0x1E774D4;
