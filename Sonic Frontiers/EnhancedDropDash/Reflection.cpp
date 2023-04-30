#define CMN_DROPDASH_STEERINGSPEED1 400.0f
#define CMN_DROPDASH_STEERINGSPEED2 200.0f
#define CMN_DROPDASH_BRAKE          2.5f

HOOK(int64_t, __fastcall, LoadAsset, m_SigLoadAsset(), int64_t a1, const char* in_assetName, const char** in_resourceType)
{
    auto result = originalLoadAsset(a1, in_assetName, in_resourceType);

    if (StringHelper::Compare(*in_resourceType, "ResReflection") && StringHelper::Compare(in_assetName, "player_common"))
    {
        Reflection::PlayerParameters = reinterpret_cast<PlayerParameters*>(*(int64_t*)(result + 0x60));

        if (!Reflection::PlayerParameters)
            return result;

        if (Configuration::IsEnhancedIslandPhysics)
        {
            Reflection::PlayerParameters->forwardView.dropDash.steeringSpeed1 = CMN_DROPDASH_STEERINGSPEED1;
            Reflection::PlayerParameters->forwardView.dropDash.steeringSpeed2 = CMN_DROPDASH_STEERINGSPEED2;
            Reflection::PlayerParameters->forwardView.dropDash.brake          = CMN_DROPDASH_BRAKE;
        }

        if (Configuration::IsEnhancedCyberPhysics)
        {
            Reflection::PlayerParameters->cyberspace.dropDash.steeringSpeed1 = CMN_DROPDASH_STEERINGSPEED1;
            Reflection::PlayerParameters->cyberspace.dropDash.steeringSpeed2 = CMN_DROPDASH_STEERINGSPEED2;
            Reflection::PlayerParameters->cyberspace.dropDash.brake          = CMN_DROPDASH_BRAKE;

            Reflection::PlayerParameters->cyberspaceSV.dropDash.steeringSpeed1 = CMN_DROPDASH_STEERINGSPEED1;
            Reflection::PlayerParameters->cyberspaceSV.dropDash.steeringSpeed2 = CMN_DROPDASH_STEERINGSPEED2;
            Reflection::PlayerParameters->cyberspaceSV.dropDash.brake          = CMN_DROPDASH_BRAKE;
        }

        if (Configuration::IsEnhancedIslandPhysics || Configuration::IsEnhancedCyberPhysics)
        {
            if (m_SigDropDashTurningDelay() != nullptr)
                WRITE_NOP(m_SigDropDashTurningDelay(), 2);
        }

        // Reflection::PlayerParameters->forwardView.speed.normal2.initial = 15.0f;
        // Reflection::PlayerParameters->forwardView.speed.normal2.max = 60.0f;
    }

    return result;
}

void Reflection::Install()
{
    INSTALL_HOOK(LoadAsset);
}