#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// BlueBlur must be included before STL
#include "..\BlueBlurCommon.h"

// Standard library
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Dependencies
#include <Helpers.h>
#include <INIReader.h>
#include "Resources.h"

// Internal headers
#include "ArchiveTreePatcher.h"
#include "Configuration.h"
#include "ControllerPatcher.h"
#include "DllMain.h"
#include "HudSonicStage.h"
#include "Patches.h"