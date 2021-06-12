using namespace std; // lol

#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
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
#include <unordered_map>
#include <vector>
#include <xmmintrin.h>

// Dependencies
#include "dependencies\Lua542\include\lua.hpp"
#include "dependencies\INIReader.h"
#include "Configuration.h"
#include "StateHooks.h"

// Internal headers
#include "ArchiveTreePatcher.h"
#include "Helpers.h"
#include "HudSonicStage.h"
#include "IOHelper.h"
#include "Loader.h"
#include "LuaCallback.h"
#include "MultiplierListener.h"
#include "Patches.h"
#include "PlayerListener.h"
#include "ResultListener.h"
#include "ScoreHooks.h"
#include "ScoreListener.h"
#include "StatisticsListener.h"
#include "StringHelper.h"
#include "Tables.h"