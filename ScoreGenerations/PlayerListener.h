#pragma once

class PlayerListener
{
public:
    /// <summary>
    /// The current player context.
    /// </summary>
    static void** const context;

    static bool IsContextSafe();
    static const uint32_t GetContext();
    static float GetVelocity();
};