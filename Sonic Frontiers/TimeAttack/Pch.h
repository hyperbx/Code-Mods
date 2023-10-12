#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

// Dependencies
#include <Helpers.h>
#include <rangers-api/rangers-api/rangers-api.h>
#include <ModInfo.h>
#include <Signature.h>
#include <StringHelper.h>

// Internal headers
#include "BlackboardStatus.h"
#include "BlackboardHelper.h"