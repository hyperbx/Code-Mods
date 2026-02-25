#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#undef min
#undef max

#include <cstdint>
#include <cstdio>

#include <Framework.h>
#include <ModInfo.h>

#define MOD_NAME   "$projectname$"
#define MOD_AUTHOR "$username$"

inline ModInfo g_ModInfo = { MOD_NAME, MOD_AUTHOR, { 1, 0, 0 } };
