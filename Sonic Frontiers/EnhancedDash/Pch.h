#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <unordered_map>

// Dependencies
#include <Helpers.h>
#include "../Common/FrontiersInput.h"
#include <gmath/Vector3.hpp>
#include <INIReader.h>
#include <IOHelper.h>
#include <MemoryPreserver.h>
#include <rangers-api/rangers-api/rangers-api.h>
#include <Signature.h>
#include <StringHelper.h>

// Internal headers
#include "Configuration.h"
#include "Reflection.h"
#include "BlackboardStatus.h"
#include "BlackboardHelper.h"
#include "MsgChangeLayerTimeScale.h"
#include "Player.h"