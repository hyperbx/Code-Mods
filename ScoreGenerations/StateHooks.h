#pragma once

class StateHooks
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Hooks to the results screen for calculating the local score.
    /// </summary>
    /// <param name="enabled">Enables/disables the hooks.</param>
    static void HookResults(bool enabled);

    /// <summary>
    /// The currently loaded stage ID.
    /// </summary>
    static const char* stageID;
};