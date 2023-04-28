#define CMN_DROPDASH_STEERINGSPEED1 400.0f
#define CMN_DROPDASH_STEERINGSPEED2 200.0f
#define CMN_DROPDASH_BRAKE          2.5f

HOOK(int64_t, __fastcall, LoadAsset, m_SigLoadAsset(), int64_t a1, const char* in_assetName, const char** in_resourceType)
{
    auto result = originalLoadAsset(a1, in_assetName, in_resourceType);

    if (StringHelper::Compare(*in_resourceType, "ResReflection") && StringHelper::Compare(in_assetName, "player_common"))
    {
        auto playerParameters = reinterpret_cast<PlayerParameters*>(*(int64_t*)(result + 0x60));

        if (Configuration::IsEnhancedIslandPhysics)
        {
            playerParameters->forwardView.dropDash.steeringSpeed1 = CMN_DROPDASH_STEERINGSPEED1;
            playerParameters->forwardView.dropDash.steeringSpeed2 = CMN_DROPDASH_STEERINGSPEED2;
            playerParameters->forwardView.dropDash.brake          = CMN_DROPDASH_BRAKE;
        }

        if (Configuration::IsEnhancedCyberPhysics)
        {
            playerParameters->cyberspace.dropDash.steeringSpeed1 = CMN_DROPDASH_STEERINGSPEED1;
            playerParameters->cyberspace.dropDash.steeringSpeed2 = CMN_DROPDASH_STEERINGSPEED2;
            playerParameters->cyberspace.dropDash.brake          = CMN_DROPDASH_BRAKE;

            playerParameters->cyberspaceSV.dropDash.steeringSpeed1 = CMN_DROPDASH_STEERINGSPEED1;
            playerParameters->cyberspaceSV.dropDash.steeringSpeed2 = CMN_DROPDASH_STEERINGSPEED2;
            playerParameters->cyberspaceSV.dropDash.brake          = CMN_DROPDASH_BRAKE;
        }

        if (Configuration::IsEnhancedIslandPhysics || Configuration::IsEnhancedCyberPhysics)
        {
            if (m_SigDropDashTurningDelay() != nullptr)
                WRITE_NOP(m_SigDropDashTurningDelay(), 2);
        }
    }

    return result;
}

void Reflection::Install()
{
    INSTALL_HOOK(LoadAsset);
}