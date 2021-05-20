#pragma once

class HudSonicStage
{
public:
    static void Install();

    /// <summary>
    /// Determines if the current stage ID uses a special HUD.
    /// </summary>
    /// <returns></returns>
    static bool IsHudSpecial();

    /// <summary>
    /// Reverse-engineered struct for MsgSetPinballHud - thanks Skyth!
    /// </summary>
    struct MsgSetPinballHud
    {
        uint8_t padding_1[0x10];
        uint32_t flags;
        uint32_t score;
        uint8_t padding_2[0x8];
    };
};

