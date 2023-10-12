#pragma once

#include <d3d11.h>
#include "imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"

class DearImGuiContext
{
public:
    inline static bool IsVisible = true;
    inline static bool IsMouseCursorVisible = false;

    static void Update();
    static void Install();
};

CL_SCAN_SIGNATURE(m_SigSwapChainHook, "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x56\x57\x41\x56\x48\x81\xEC\xF0\x02", "xxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigWndProcHook, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x48\x89\x7C\x24\x20\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x70\x48\x83", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");