#pragma once

// Yakuza 3 (Steam, GOG): 0x140A31317, 0x1409E6147
// Yakuza 4 (Steam, GOG): 0x140F5AF47, 0x140EF9117
// Yakuza 5 (Steam, GOG): 0x1412AEFA4, 0x14124E894
DECLARE_SIGNATURE_SCAN
(
    Sig_AnalogDeadzoneInstr,

    // Yakuza 3 & 4
    { "\xC5\xFA\x59\x25\xCC\xCC\xCC\xCC\xC5\xF8\x28\xDA\xC5\xB2\x5E\xD6\xC5\xEA\x59\xCC\xC5\xF2\x5F\xD3\xC5\xF8\x28\xCA\xC5\xF2\x5D\xD5\xC5\xFA\x11\x55\x00", "xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxx" },

    // Yakuza 5
    { "\xC5\xFA\x59\x25\xCC\xCC\xCC\xCC\xC5\xF0\x57\xC9\xC5\xAA\x5E\xC7\xC5\xFA\x59\xD4\xC5\xEA\x5F\x0D\xCC\xCC\xCC\xCC\xC5\xF2\x5D\xD6\xC5\xFA\x11\x55\x00", "xxxx????xxxxxxxxxxxxxxxx????xxxxxxxxx" }
);

// Yakuza 3 (Steam, GOG): 0x140A33880, 0x1409E86B0
// Yakuza 4 (Steam, GOG): 0x140F5DE00, 0x140EFBFD0
// Yakuza 5 (Steam, GOG): 0x1412B3060, 0x141252950
DECLARE_SIGNATURE_SCAN
(
    Sig_ProcessInputs,

    // Yakuza 3 & 4
    { "\x48\x85\xD2\x0F\x84\x4C", "xxxxxx" },

    // Yakuza 5
    { "\x48\x85\xD2\x0F\x84\x16\x05", "xxxxxxx" }
);

// Yakuza 3 (Steam, GOG): 0x140A30FD0, 0x1409E5E00
// Yakuza 4 (Steam, GOG): 0x140F5AB80, 0x140EF8D50
// Yakuza 5 (Steam, GOG): 0x1412AE0B0, 0x14124D9A0
DECLARE_SIGNATURE_SCAN
(
    Sig_IsKeyDown,

    { "\x40\x53\x48\x83\xEC\x20\x8B\xD9\x8B\xD1\x48\x8B\x0D\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x84\xC0\x74\x08\x33\xC0\x48\x83\xC4\x20\x5B\xC3\x48", "xxxxxxxxxxxxx????x????xxxxxxxxxxxxx" }
);
