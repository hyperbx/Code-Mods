#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <cstdint>
#include <cstdio>
#include <string>
#include <list>

// Dependencies
#include <Helpers.h>

// Hedgehog Engine
#include "BgmIdExtension.h"

// Internal headers
#include "Configuration.h"
#include "INIReader.h"
#include "StringHelper.h"
#include "BgmService.h"