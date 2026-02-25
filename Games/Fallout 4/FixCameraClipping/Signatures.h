#pragma once

DECLARE_SIGNATURE_SCAN
(
    Sig_BSShaderUtil_SetCameraFOV,

    // 1.10.980 (Steam): 0x14206B620
    // 1.10.984 (Steam): 0x14206BD40
    // 1.11.137 (Steam): 0x1421BB580
    { "\x48\x8B\xC4\x53\x48\x81\xEC\x90\x00\x00\x00\x0F\x29\x70\xE8\x0F\x28", "xxxxxxxxxxxxxxxxx" },

    // 1.1.29 (Steam):   0x142CD2AE0
    // 1.3.47 (Steam):   0x14283DBE0
    // 1.10.130 (Steam): 0x142820310
    // 1.10.138 (Steam): 0x142820310
    // 1.10.155 (Steam): 0x142820420
    // 1.10.162 (Steam): 0x142820430
    // 1.10.163 (Steam): 0x142820430
    { "\x48\x8B\xC4\x53\x48\x81\xEC\x90\x00\x00\x00\x0F\x29\x70\xE8\x0F\x29\x78\xD8\x44\x0F\x29\x40\xC8\xF3", "xxxxxxxxxxxxxxxxxxxxxxxxx" }
);
