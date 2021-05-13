#pragma once

class StateHooks
{
public:
    static void Install();

    /// <summary>
    /// The currently loaded stage ID.
    /// </summary>
    static const char* stageID;

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