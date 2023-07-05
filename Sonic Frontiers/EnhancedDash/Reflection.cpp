void SetCommonDriftParameters(PlayerParamDrift& in_pPlayerParamDrift)
{
    in_pPlayerParamDrift.checkFallTime = 0.1f;
    in_pPlayerParamDrift.maxNeutralSteerSpeed = 99999.0f;
    in_pPlayerParamDrift.maxSpeed = 60.0f;
    in_pPlayerParamDrift.maxSpeedMax = 80.0f;
    in_pPlayerParamDrift.minSpeed = 40.0f;
    in_pPlayerParamDrift.minSpeedMax = 60.0f;
    in_pPlayerParamDrift.neutralSteerAccel = 2500.0f;
    in_pPlayerParamDrift.steerAccel = 99999.0f;
}

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

HOOK(int64_t, __fastcall, LoadAsset, m_SigLoadAsset(), int64_t a1, const char* in_assetName, const char** in_resourceType)
{
    auto result = originalLoadAsset(a1, in_assetName, in_resourceType);

    if (StringHelper::Compare(*in_resourceType, "ResReflection") && StringHelper::Compare(in_assetName, "player_common"))
    {
        Reflection::SonicParameters = reinterpret_cast<SonicParameters*>(*(int64_t*)(result + 0x60));

        if (!Reflection::SonicParameters)
            return result;

#if _DEBUG
        printf("[Enhanced Dash] Reflection::SonicParameters initialised!\n");
#endif

        // Drift
        {
            if (Configuration::IsDriftEnhancedCyberPhysics)
                SetCommonDriftParameters(Reflection::SonicParameters->cyberspace.drift);

            if (Configuration::IsDriftEnhancedIslandPhysics)
                SetCommonDriftParameters(Reflection::SonicParameters->forwardView.drift);
        }

        // Drop Dash
        {
            if (Configuration::IsDropDashEnhancedCyberPhysics)
            {
                SetCommonDropDashParameters(Reflection::SonicParameters->cyberspace.dropDash);

                Reflection::SonicParameters->cyberspace.dropDash.minDashSpeed = 45.0f;
            }

            if (Configuration::IsDropDashEnhancedIslandPhysics)
                SetCommonDropDashParameters(Reflection::SonicParameters->forwardView.dropDash);

            if (Configuration::IsDropDashEnhancedCyberPhysics || Configuration::IsDropDashEnhancedIslandPhysics)
            {
                SetCommonDropDashParameters(Reflection::SonicParameters->cyberspaceSV.dropDash);

                if (m_SigDropDashTurningDelay() != nullptr)
                    WRITE_NOP(m_SigDropDashTurningDelay(), 2);
            }
        }

        // Spin Dash
        // TODO: finish this?
        {
            if (Configuration::IsSpinDashEnhancedCyberPhysics)
            {
                Reflection::SonicParameters->cyberspace.spinBoost.speedBoost.maxSpeed = 60.0f;
            }

            if (Configuration::IsSpinDashEnhancedIslandPhysics)
            {
                Reflection::SonicParameters->forwardView.spinBoost.speedBoost.maxSpeed = 60.0f;
            }
        }

        // Spin Move
        {
            if (Configuration::IsSpinMoveEnhancedCyberPhysics)
                SetCommonSpinMoveParameters(Reflection::SonicParameters->cyberspace.spinBoost.speedBall);

            if (Configuration::IsSpinMoveEnhancedIslandPhysics)
                SetCommonSpinMoveParameters(Reflection::SonicParameters->forwardView.spinBoost.speedBall);

            if (Configuration::IsSpinMoveEnhancedCyberPhysics || Configuration::IsSpinMoveEnhancedIslandPhysics)
            {
                Reflection::SonicParameters->cyberspaceSV.spinBoost.speedBall.initialSpeed = 10.0f;
                Reflection::SonicParameters->cyberspaceSV.spinBoost.speedBall.maxSpeed = 40.0f;
                Reflection::SonicParameters->cyberspaceSV.spinBoost.speedBall.accele.force = 10.0f;
                Reflection::SonicParameters->cyberspaceSV.spinBoost.speedBall.accele.force2 = 10.0f;
            }
        }
    }

    return result;
}

void Reflection::Install()
{
    INSTALL_HOOK(LoadAsset);
}