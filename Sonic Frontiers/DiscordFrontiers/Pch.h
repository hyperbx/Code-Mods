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
#include <Discord/x64/include/discord_register.h>
#include <Discord/x64/include/discord_rpc.h>
#include <Helpers.h>
#include <INIReader.h>
#include <Signature.h>
#include <StringHelper.h>
#include <TimeHelper.h>

// Internal headers
#include "Discord.h"
#include "BossListener.h"
#include "GameModeListener.h"