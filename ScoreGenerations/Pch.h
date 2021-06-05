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
#include <regex>
#include <set>
#include <sstream>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

// Dependencies
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
#include "Patches.h"
#include "PlayerListener.h"
#include "ResultListener.h"
#include "ScoreHooks.h"
#include "ScoreListener.h"
#include "StatisticsListener.h"
#include "StringHelper.h"