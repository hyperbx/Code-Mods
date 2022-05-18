#pragma once

class StateHooks
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Determines whether or not the results are hooked.
    /// </summary>
    static bool isResultsHooked;
};