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
#include <HttpHelper.h>
#include <INIReader.h>
#include <LanguageHelper.h>
#include <ModInfo.h>
#include <rangers-api/rangers-api/rangers-api.h>
#include <Signature.h>
#include <StringHelper.h>
#include <TimeHelper.h>

CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmUpdate, 0x1408AA540, "\x40\x53\x55\x48\x83\xEC\x28\x49", "xxxxxxxx");

// Internal headers
#include "Configuration.h"
#include "Discord.h"
#include "StageHelper.h"
#include "BattleRushListener.h"
#include "MasterTrialListener.h"
#include "BossListener.h"
#include "PlayerListener.h"
#include "GameModeListener.h"
#include "StageListener.h"