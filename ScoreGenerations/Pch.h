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
#include <set>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

// Dependencies
#include "dependencies\inipp.h"

// Internal headers
#include "ArchiveTreePatcher.h"
#include "Helpers.h"
#include "Mod.h"
#include "ObjectHooks.h"
#include "Patches.h"
#include "ScoreListener.h"
#include "StatisticsListener.h"
#include "StateHooks.h"