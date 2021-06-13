#pragma once

class PlayerListener
{
public:
    static void** const CSonicContext;
    static bool isGrounded;

    static void Install();
    static bool IsContextSafe();
    static const uint32_t GetContext();
    static float GetVelocity();
    static bool IsSuper();
};