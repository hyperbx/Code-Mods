#pragma once

class HudSonicStage
{
public:
    static void Install();

    /// <summary>
    /// Timer calculated in delta time for rewarding score to Super Sonic.
    /// </summary>
    static float superSonicTimer;

    /// <summary>
    /// Sends MsgSetPinballHud to the message receiver.
    /// </summary>
    static void ProcessMsgSetPinballHud(void* thisDeclaration);

    /// <summary>
    /// Updates the Super Sonic timer and rewards score.
    /// </summary>
    static void UpdateSuperSonicTimer(float* pUpdateInfo);

    /// <summary>
    /// Determines if the current stage ID is forbidden.
    /// </summary>
    static bool IsStageForbidden();

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

