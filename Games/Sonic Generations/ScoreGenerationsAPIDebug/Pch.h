#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <cstdint>
#include <cstdio>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "Score Generations API Tests"
#define MOD_AUTHOR "Hyper"
#define LOG_SOURCE "Score Generations"

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 0, 0 } };

#define SCORE_GENS_API_VERSION 2

#include "../ScoreGenerations/API/ScoreGenerationsAPI.h"
