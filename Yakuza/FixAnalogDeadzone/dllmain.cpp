#define MOD_NAME "Fix Analog Deadzone"

enum class Game
{
    Unknown,
    Yakuza3,
    Yakuza4,
    Yakuza5
};

static std::unordered_map<Game, const char*> g_gameNameMap =
{
    { Game::Unknown, "Unknown"  },
    { Game::Yakuza3, "Yakuza 3" },
    { Game::Yakuza4, "Yakuza 4" },
    { Game::Yakuza5, "Yakuza 5" }
};

static float* g_pAnalogDeadzone{};
static constexpr float g_kGamepadDeadzone{ 1.0f };
static constexpr float g_kKeyboardDeadzone{ 1.3157895f };

HOOK(void, __fastcall, InputHandler, 0, void* a1, void* a2, double a3)
{
    // Use gamepad deadzone.
    if (g_pAnalogDeadzone)
        WRITE_MEMORY(g_pAnalogDeadzone, float, g_kGamepadDeadzone);

    originalInputHandler(a1, a2, a3);
}

HOOK(bool, __fastcall, CheckKey, 0, uint32_t keyCode)
{
    auto result = originalCheckKey(keyCode);

    // Use keyboard deadzone.
    if (result && g_pAnalogDeadzone)
        WRITE_MEMORY(g_pAnalogDeadzone, float, g_kKeyboardDeadzone);

    return result;
}

static bool TryPatchYakuza3()
{
    // Yakuza 3: 0x140A31317
    // Yakuza 4: 0x140F5AF47
    auto pAnalogDeadzoneInstr = (uint64_t)ScanSignature
    (
        "\xC5\xFA\x59\x25\xCC\xCC\xCC\xCC\xC5\xF8\x28\xDA\xC5\xB2\x5E\xD6\xC5\xEA\x59\xCC\xC5\xF2\x5F\xD3\xC5\xF8\x28\xCA\xC5\xF2\x5D\xD5\xC5\xFA\x11\x55\x00",
        "xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
    );

    if (!pAnalogDeadzoneInstr)
        return false;

    // Read address from VMULSS instruction.
    // Yakuza 3: 0x140DBAE58
    // Yakuza 4: 0x141437ED8
    g_pAnalogDeadzone = (float*)(pAnalogDeadzoneInstr + (*((uint32_t*)(pAnalogDeadzoneInstr + 4)) + 8));

    if (!g_pAnalogDeadzone)
        return false;

    // Yakuza 3: 0x140A33880
    // Yakuza 4: 0x140F5DE00
    auto pInputHandler = (uint64_t)ScanSignature
    (
        "\x48\x85\xD2\x0F\x84\x4C",
        "xxxxxx"
    );

    if (!pInputHandler)
        return false;
    
    INSTALL_HOOK_ADDRESSED(InputHandler, pInputHandler);

    return true;
}

static bool TryPatchYakuza5()
{
    // Yakuza 5: 0x1412AEFA4
    auto pAnalogDeadzoneInstr = (uint64_t)ScanSignature
    (
        "\xC5\xFA\x59\x25\xCC\xCC\xCC\xCC\xC5\xF0\x57\xC9\xC5\xAA\x5E\xC7\xC5\xFA\x59\xD4\xC5\xEA\x5F\x0D\xCC\xCC\xCC\xCC\xC5\xF2\x5D\xD6\xC5\xFA\x11\x55\x00",
        "xxxx????xxxxxxxxxxxxxxxx????xxxxxxxxx"
    );

    if (!pAnalogDeadzoneInstr)
        return false;

    // Read address from VMULSS instruction.
    // Yakuza 5: 0x14196676C
    g_pAnalogDeadzone = (float*)(pAnalogDeadzoneInstr + (*((uint32_t*)(pAnalogDeadzoneInstr + 4)) + 8));

    if (!g_pAnalogDeadzone)
        return false;

    // Yakuza 5: 0x1412B3060
    auto pInputHandler = (uint64_t)ScanSignature
    (
        "\x48\x85\xD2\x0F\x84\x16\x05",
        "xxxxxxx"
    );

    if (!pInputHandler)
        return false;
    
    INSTALL_HOOK_ADDRESSED(InputHandler, pInputHandler);

    return true;
}

static bool TryPatchShared()
{
    // Yakuza 3: 0x140A30FD0
    // Yakuza 4: 0x140F5AB80
    // Yakuza 5: 0x1412AE0B0
    auto pCheckKey = (uint64_t)ScanSignature
    (
        "\x40\x53\x48\x83\xEC\x20\x8B\xD9\x8B\xD1\x48\x8B\x0D\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x84\xC0\x74\x08\x33\xC0\x48\x83\xC4\x20\x5B\xC3\x48",
        "xxxxxxxxxxxxx????x????xxxxxxxxxxxxx"
    );

    if (!pCheckKey)
        return false;

    INSTALL_HOOK_ADDRESSED(CheckKey, pCheckKey);

    return true;
}

static Game GetGame()
{
    Game result{};

    // Yakuza 3: 0x1404CF3E0
    // Yakuza 4: 0x1406EE600
    // Yakuza 5: 0x000000000 (expected to fail)
    auto pWindowNameInstr = (uint64_t)ScanSignature
    (
        "\x4C\x8D\x05\xCC\xCC\xCC\xCC\x48\x8B\x15\xCC\xCC\xCC\xCC\x33\xDB",
        "xxx????xxx????xx"
    );

    if (pWindowNameInstr)
    {
        // Read address from LEA instruction.
        // Yakuza 3: 0x140CFB3A0
        // Yakuza 4: 0x14130A010
        auto pWindowName = (const char*)(pWindowNameInstr + (*((uint32_t*)(pWindowNameInstr + 3)) + 7));

        if (strcmp(pWindowName, "Yakuza 3") == 0)
        {
            result = Game::Yakuza3;
        }
        else if (strcmp(pWindowName, "Yakuza 4") == 0)
        {
            result = Game::Yakuza4;
        }
    }
    else
    {
        result = Game::Yakuza5;
    }

    return result;
}

static void Init()
{
#ifdef _DEBUG
    INIT_CONSOLE();
#endif

    auto game = GetGame();
    
    printf("[" MOD_NAME "] Game: %s\n", g_gameNameMap[game]);

    auto isPatchSuccess = false;
    
    switch (game)
    {
        case Game::Yakuza3:
        case Game::Yakuza4:
            isPatchSuccess = TryPatchYakuza3();
            break;

        case Game::Yakuza5:
            isPatchSuccess = TryPatchYakuza5();
            break;

        default:
            MessageBoxA(nullptr, "Unsupported game.", MOD_NAME, MB_ICONERROR);
            return;
    }

    if (isPatchSuccess)
        isPatchSuccess = TryPatchShared();

    if (isPatchSuccess)
    {
        printf("[" MOD_NAME "] Patches succeeded.\n");
    }
    else
    {
        printf("[" MOD_NAME "] Patches failed.\n");

#ifndef _DEBUG
        MessageBoxA(nullptr, "Failed to install patches.", MOD_NAME, MB_ICONERROR);
#endif
    }
}

BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD reason, _In_ LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			Init();
			break;

		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}

	return TRUE;
}
