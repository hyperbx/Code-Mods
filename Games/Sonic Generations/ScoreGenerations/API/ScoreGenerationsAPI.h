#pragma once

#include <Windows.h>

#include <string>
#include <unordered_map>

#include "ScoreGenerationsTypes.h"

#define SCORE_GENS_STRINGIFY(X)  #X
#define SCORE_GENS_XSTRINGIFY(X) SCORE_GENS_STRINGIFY(X)

#define SCORE_GENS_MODULE        "ScoreGenerations.dll"
#define SCORE_GENS_EXPORT        extern "C" __declspec(dllexport)
#define SCORE_GENS_API           __cdecl

#ifndef SCORE_GENS_API_VERSION
#define SCORE_GENS_API_VERSION   2
#endif

#if SCORE_GENS_API_VERSION == 1
#include "ScoreGenerationsAPIv1.h"
#elif SCORE_GENS_API_VERSION == 2
#include "ScoreGenerationsAPIv2.h"
#endif
