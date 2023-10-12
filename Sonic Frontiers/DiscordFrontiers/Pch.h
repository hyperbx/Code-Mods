#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <unordered_map>
#include <vector>

// Dependencies
#include <Discord/x64/include/discord_register.h>
#include <Discord/x64/include/discord_rpc.h>
#include <Helpers.h>
#include <INIReader.h>
#include <LanguageHelper.h>
#include <ModInfo.h>
#include <Signature.h>
#include <StringHelper.h>
#include <TimeHelper.h>

// Internal headers
#include "Configuration.h"
#include "Discord.h"
#include "BossListener.h"
#include "GameModeListener.h"