#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <random>
#include <string>

// Dependencies
#include <Helpers.h>
#include <INIReader.h>
#include <Signature.h>
#include <StringHelper.h>

// Hedgehog Engine
#include "BgmIdExtension.h"

// Internal headers
#include "Configuration.h"
#include "BgmService.h"