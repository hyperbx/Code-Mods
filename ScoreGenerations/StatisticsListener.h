#pragma once

class StatisticsListener
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Total number of rings obtained by the player.
    /// </summary>
    static unsigned int totalRingCount;

    /// <summary>
    /// Total amount of speed from checkpoints.
    /// </summary>
    static unsigned int totalVelocity;

    /// <summary>
    /// Current number of rings obtained by the player.
    /// </summary>
    static unsigned int ringCount;

    /// <summary>
    /// Minutes counted by the game.
    /// </summary>
    static unsigned int minutes;

    /// <summary>
    /// Seconds counted by the game.
    /// </summary>
    static unsigned int seconds;

    /// <summary>
    /// Calculates the elapsed time from the minutes and seconds.
    /// </summary>
    /// <returns>Elapsed time as an unsigned integer.</returns>
    static unsigned int GetElapsedTime();
};