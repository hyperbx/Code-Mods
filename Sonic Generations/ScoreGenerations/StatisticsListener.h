#pragma once

class StatisticsListener
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Calculates the elapsed time from the minutes and seconds.
    /// </summary>
    static int GetElapsedTime();

    /// <summary>
    /// Current player totals.
    /// </summary>
    static Statistics::Totals totals;
};