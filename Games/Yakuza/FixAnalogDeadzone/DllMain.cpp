#include "Signatures.h"

using namespace CMF::System::Memory;

static float* g_pAnalogDeadzone{};
static constexpr float g_kGamepadDeadzone{ 1.0f };
static constexpr float g_kKeyboardDeadzone{ 1.3157895f };

DECLARE_HOOK(void, __fastcall, ProcessInputs, Sig_ProcessInputs(), void* a1, void* a2, double a3)
{
    // Use gamepad deadzone.
    if (g_pAnalogDeadzone)
        WRITE(g_pAnalogDeadzone, float, g_kGamepadDeadzone);

    original_ProcessInputs(a1, a2, a3);
}

DECLARE_HOOK(bool, __fastcall, IsKeyDown, Sig_IsKeyDown(), uint32_t in_keyCode)
{
    auto result = original_IsKeyDown(in_keyCode);

    // Use keyboard deadzone.
    if (result && g_pAnalogDeadzone)
        WRITE(g_pAnalogDeadzone, float, g_kKeyboardDeadzone);

    return result;
}

static void Init()
{
#ifdef _DEBUG
    cmf::sys::Logger::Init(true);
#else
    cmf::sys::Logger::Init();
#endif

    if (!SignatureScanner::Status.Success)
    {
        LOGFN_ERROR("Error: {}\n{}", SignatureScanner::Status.pMessage, SignatureScanner::Status.GetPatternString());
        MessageBoxA(nullptr, "Failed to install patches.", MOD_NAME, MB_ICONERROR);
        return;
    }

    // Read address from VMULSS instruction.
    // Yakuza 3 (Steam, GOG): 0x140DBAE58, 0x140D5D408
    // Yakuza 4 (Steam, GOG): 0x141437ED8, 0x1413BCDF8
    // Yakuza 5 (Steam, GOG): 0x14196676C, 0x1418E912C
    g_pAnalogDeadzone = (float*)READ_INSTR_ADDRESS(Sig_AnalogDeadzoneInstr(), uint32_t, 4, 8);

    INSTALL_HOOK(ProcessInputs);
    INSTALL_HOOK(IsKeyDown);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        Init();

	return TRUE;
}
