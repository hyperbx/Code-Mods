#pragma once

#if defined(WIN32)
#include "HookingWin32.h"
#elif defined(N64RECOMP)
#include "HookingN64Recomp.h"
#endif
