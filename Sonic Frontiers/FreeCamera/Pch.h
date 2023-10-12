#pragma once

#define WIN32_LEAN_AND_MEAN
#define IMGUI_DEFINE_MATH_OPERATORS

// Detours
#include <Windows.h>
#include <detours.h>

// Standard library
#include <cstdint>
#include <cstdio>
#include <fstream>

// Dependencies
#include "gmath/Quaternion.hpp"
#include <Helpers.h>
#include "..\Common\InputHelper.h"
#include "..\Common\OptionData.h"
#include "INIReader.h"
#include <rangers-api/rangers-api/rangers-api.h>
#include "Signature.h"

// Internal headers
#include "Configuration.h"
#include "Camera.h"
#include "DearImGuiContext.h"
#include "MsgPhotoModeStart.h"
#include "MsgPlayAnimation.h"
#include "MsgResumeWorld.h"
#include "MsgSuspendWorld.h"
#include "MsgUISetGameCockpitEnabled.h"
#include "MsgUISetGameCockpitVisibility.h"