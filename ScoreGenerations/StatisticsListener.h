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
};