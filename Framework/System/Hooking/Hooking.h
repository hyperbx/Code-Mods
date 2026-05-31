#pragma once

#ifdef WIN32
#   include "HookingWin32.h"
#else
#   ifdef N64RECOMP
#       include "HookingN64Recomp.h"
#   else
#       include "HookingNop.h"
#   endif
#endif
