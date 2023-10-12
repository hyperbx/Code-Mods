void SetCommonDropDashParameters(PlayerParamDropDash& in_pPlayerParamDropDash)
{
    in_pPlayerParamDropDash.brake = 2.5f;
    in_pPlayerParamDropDash.steeringSpeed1 = 400.0f;
    in_pPlayerParamDropDash.steeringSpeed2 = 200.0f;
}

void SetCommonSpinMoveParameters(PlayerParamSpinBoostSpeed& in_pPlayerParamSpinBoostSpeed)
{
    in_pPlayerParamSpinBoostSpeed.initialSpeed = 20.0f;
    in_pPlayerParamSpinBoostSpeed.maxSpeed = 120.0f;
    in_pPlayerParamSpinBoostSpeed.accele.force = 15.0f;
    in_pPlayerParamSpinBoostSpeed.accele.force2 = 15.0f;
    in_pPlayerParamSpinBoostSpeed.baseRotateForce = 3500.0f;
    in_pPlayerParamSpinBoostSpeed.minTurnSpeed = 200.0f;
}

void Reflection::Refresh()
{
    if (!Reflection::pSonicParameters)
        return;

    // Drop Dash
    {
        if (Configuration::IsDropDashEnhancedCyberPhysics)
        {
            SetCommonDropDashParameters(RFL_GET_PARAM(cyberspace.dropDash));

            RFL_SET_PARAM(cyberspace.dropDash.minDashSpeed, 45.0f);
        }

        if (Configuration::IsDropDashEnhancedIslandPhysics)
            SetCommonDropDashParameters(RFL_GET_PARAM(forwardView.dropDash));

        if (Configuration::IsDropDashEnhancedCyberPhysics || Configuration::IsDropDashEnhancedIslandPhysics)
        {
            SetCommonDropDashParameters(RFL_GET_PARAM(cyberspaceSV.dropDash));

            if (m_SigDropDashTurningDelay() != nullptr)
                WRITE_NOP(m_SigDropDashTurningDelay(), 2);
        }
    }

    // Spin Boost
    // TODO: finish this?
    {
        if (Configuration::IsSpinBoostEnhancedCyberPhysics)
        {
            RFL_SET_PARAM(cyberspace.spinBoost.speedBoost.maxSpeed, 60.0f);
            RFL_SET_PARAM(cyberspace.spinBoost.speedBoost.baseRotateForce, 2250.0f);
        }

        if (Configuration::IsSpinBoostEnhancedIslandPhysics)
        {
            RFL_SET_PARAM(forwardView.spinBoost.speedBoost.maxSpeed, 60.0f);
        }
    }

    // Spin Move
    {
        if (Configuration::IsSpinMoveEnhancedCyberPhysics)
            SetCommonSpinMoveParameters(RFL_GET_PARAM(cyberspace.spinBoost.speedBall));

        if (Configuration::IsSpinMoveEnhancedIslandPhysics)
            SetCommonSpinMoveParameters(RFL_GET_PARAM(forwardView.spinBoost.speedBall));

        if (Configuration::IsSpinMoveEnhancedCyberPhysics || Configuration::IsSpinMoveEnhancedIslandPhysics)
        {
            RFL_SET_PARAM(cyberspaceSV.spinBoost.speedBall.initialSpeed, 10.0f);
            RFL_SET_PARAM(cyberspaceSV.spinBoost.speedBall.maxSpeed, 40.0f);
            RFL_SET_PARAM(cyberspaceSV.spinBoost.speedBall.accele.force, 10.0f);
            RFL_SET_PARAM(cyberspaceSV.spinBoost.speedBall.accele.force2, 10.0f);
        }
    }
}

HOOK(int64_t, __fastcall, LoadAsset, READ_CALL(m_SigLoadAssetCaller()), int64_t a1, const char* in_assetName, const char** in_resourceType)
{
    auto result = originalLoadAsset(a1, in_assetName, in_resourceType);

    if (StringHelper::Compare(*in_resourceType, "ResReflection") && StringHelper::Compare(in_assetName, "player_common"))
    {
        Reflection::pSonicParameters = reinterpret_cast<SonicParameters*>(*(int64_t*)(result + 0x60));

        if (Reflection::pSonicParameters && !Reflection::IsParametersBackedUp)
        {
            Reflection::OriginalSonicParameters = *Reflection::pSonicParameters;
            Reflection::IsParametersBackedUp = true;
        }

        if (!Reflection::pSonicParameters)
            return result;

#if _DEBUG
        printf("[Enhanced Moveset] Reflection::SonicParameters initialised!\n");
#endif

        Reflection::Refresh();
    }

    return result;
}

void Reflection::Install()
{
    INSTALL_HOOK(LoadAsset);
}