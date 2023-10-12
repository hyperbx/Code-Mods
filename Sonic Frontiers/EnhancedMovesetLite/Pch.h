#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <format>
#include <string>
#include <thread>

// Dependencies
#include <Helpers.h>
#include <INIReader.h>
#include <IOHelper.h>
#include <MemoryPreserver.h>
#include <ModInfo.h>
#include <rangers-api/rangers-api/rangers-api.h>
#include "Input.h"
#include <Signature.h>
#include "SoundManager.h"
#include <StringHelper.h>

// Internal headers
#include "Reflection.h"
#include "Configuration.h"
#include "BlackboardHelper.h"
#include "Player.h"
#include "StateAirDash.h"
#include "StateFallSlope.h"
#include "StateGrindDoubleJump.h"
#include "StatePluginBoost.h"
#include "StatePluginCyloop.h"
#include "StatePluginAirTrick.h"
#include "StateQuickStompDash.h"
#include "StateSlideDash.h"
#include "StateSpinBoost.h"
#include "StateSpinBoostCharge.h"
#include "StateSpinMove.h"
#include "StateDropDash.h"
#include "StateSpringJumpHeadLand.h"