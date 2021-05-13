#pragma once

class StatisticsListener
{
public:
    static void Install();

    /// <summary>
    /// Total number of rings obtained by the player.
    /// </summary>
    static unsigned int totalRingCount;

    /// <summary>
    /// Current number of rings obtained by the player.
    /// </summary>
    static unsigned int ringCount;

    /// <summary>
    /// Elapsed time counted by the game.
    /// </summary>
    static unsigned int elapsedTime;

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