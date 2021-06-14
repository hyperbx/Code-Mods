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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Dependencies
#include <MemoryHelper.h>
#include <IniReader.h>

// Internal headers
#include "ArchiveTreePatcher.h"
#include "Configuration.h"
#include "Patches.h"