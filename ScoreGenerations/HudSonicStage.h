#pragma once

class HudSonicStage
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Sends MsgSetPinballHud to the message receiver.
    /// </summary>
    static void ProcessMsgSetPinballHud(void* thisDeclaration);

    /// <summary>
    /// Updates the multipliers.
    /// </summary>
    static void UpdateMultipliers(float* pUpdateInfo);

    /// <summary>
    /// Updates the Super Sonic timer and rewards score.
    /// </summary>
    static void UpdateSuperSonicTimer(float* pUpdateInfo);

    /// <summary>
    /// Determines if the current stage ID is forbidden.
    /// </summary>
    static bool IsStageForbidden();

    /// <summary>
    /// Determines if the current stage ID is Casino Night Zone.
    /// </summary>
    /// <returns></returns>
    static bool IsCasino();

    /// <summary>
    /// Determines if the current stage is a mission.
    /// </summary>
    static bool isMission;

    /// <summary>
    /// Reverse-engineered struct for MsgSetPinballHud - by Skyth.
    /// </summary>
    struct MsgSetPinballHud
    {
        uint8_t padding_1[0x10];
        uint32_t flags;
        uint32_t score;
        uint8_t padding_2[0x8];
    };
};

