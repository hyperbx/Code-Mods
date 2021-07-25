using namespace std;

#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <algorithm>
#include <cstdint>
#include <cstdio>

// Dependencies
#include <Helpers.h>

// Internal headers
#include "HudSonicStage.h"
#include "Patches.h"
#include "PlayerListener.h"