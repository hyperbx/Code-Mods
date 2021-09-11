using namespace std;

#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <string>

// Dependencies
#include "Configuration.h"
#include <Helpers.h>
#include <INIReader.h>
#include <IOHelper.h>
#include <Signature.h>
#include <StringHelper.h>