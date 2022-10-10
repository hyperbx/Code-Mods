#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// BlueBlur must be included before STL
#include "..\BlueBlurCommon.h"

// Standard library
#include <cstdint>
#include <cstdio>

// Dependencies
#include <Helpers.h>
#include <INIReader.h>
#include <StringHelper.h>

// Internal headers
#include "Configuration.h"
#include "HudSonicStage.h"
#include "Player.h"