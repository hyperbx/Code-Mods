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
#include <vector>

// Dependencies
#include "dependencies\INIReader.h"

// Internal headers
#include "ArchiveTreePatcher.h"
#include "Configuration.h"
#include "Helpers.h"
#include "IOHelper.h"
#include "Loader.h"
#include "LuaCallback.h"
#include "ObjectHooks.h"
#include "Patches.h"
#include "PlayerListener.h"
#include "StateHooks.h"
#include "ScoreListener.h"
#include "StatisticsListener.h"
#include "StringHelper.h"