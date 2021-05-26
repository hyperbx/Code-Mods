#pragma once

class PlayerListener
{
public:
    static void** const CSonicContext;
    static void** const CSonicClassicContext;
    static void** const CSonicSpContext;

    static bool IsContextSafe();
    static const uint32_t GetContext();
    static float GetVelocity();
    static bool IsSuper();
};