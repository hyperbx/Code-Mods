#pragma once

class StateHooks
{
public:
    static void Install();

    /// <summary>
    /// The currently loaded stage ID.
    /// </summary>
    static const char* const stageID;
};