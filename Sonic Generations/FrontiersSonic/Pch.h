#pragma once

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

// Detours
#include <Windows.h>
#include <detours.h>

// BlueBlur must be included before STL
#include "..\BlueBlurCommon.h"

// Standard library
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <math.h>

// Dependencies
#include <Helpers.h>
#include <INIReader.h>
#include <StringHelper.h>

// Internal headers
#include "Camera.h"
#include "Configuration.h"
#include "HudSonicStage.h"
#include "Impulse.h"
#include "Patches.h"
#include "Player.h"