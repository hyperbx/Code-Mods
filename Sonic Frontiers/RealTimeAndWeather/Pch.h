#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <format>
#include <string>
#include <time.h>
#include <vector>

// Dependencies
#include <Helpers.h>
#include <HttpHelper.h>
#include <INIReader.h>
#include <IOHelper.h>
#include <json.h>
#include <Signature.h>
#include <StringHelper.h>
#include <TimeHelper.h>

using json = nlohmann::json;

// Internal headers
#include "Configuration.h"
#include "StageListener.h"
#include "Time.h"
#include "TimeService.h"
#include "WeatherListener.h"
#include "WeatherService.h"