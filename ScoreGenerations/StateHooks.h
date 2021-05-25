#pragma once

class StateHooks
{
public:
    static void Install();
    static void HookResults(bool enabled);

    /// <summary>
    /// The currently loaded stage ID.
    /// </summary>
    static const char* stageID;
};