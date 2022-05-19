#pragma once

class StatisticsListener
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Gets the current time.
    /// </summary>
    static void GetTime(Sonic::CGameDocument* pGameDocument, size_t* minutes, size_t* seconds, size_t* milliseconds);

    /// <summary>
    /// Calculates the elapsed time from the minutes and seconds.
    /// </summary>
    static float GetElapsedTime(Sonic::CGameDocument* pGameDocument);

    /// <summary>
    /// Current player totals.
    /// </summary>
    static Statistics::Totals totals;
};