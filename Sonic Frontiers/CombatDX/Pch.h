#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <cstdint>
#include <cstdio>
#include <unordered_map>

// Dependencies
#include <Helpers.h>
#include <rangers-api/rangers-api/rangers-api.h>
#include <Signature.h>

// Internal headers
#include "ScriptSequenceExtras.h"