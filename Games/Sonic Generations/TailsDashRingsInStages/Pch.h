#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Tails' Dash Rings in Stages"
#define MOD_AUTHOR "Hyper"
#define LOG_SOURCE MOD_NAME

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 1, 0 } };

#include "Configuration.h"
