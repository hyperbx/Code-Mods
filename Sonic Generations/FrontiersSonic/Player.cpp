bool hasStompBounced      = false;
bool isAirBoostToFall     = false;
bool isBoostToFall        = false;
bool isJumpShort          = false;
bool isRolling            = false;
bool updateDropDash       = false;
bool updateHomingAfter    = false;
bool updateSpinAttackRoll = false;

float bounceDeltaTime                 = 0.0f;
float Player::DeltaTime               = 0.0f;
float dropDashDeltaTime               = 0.0f;
float homingAfterDeltaTime            = 0.0f;
float originalCameraPositionSensitive = 100.0f;
float spinAttackRollDeltaTime         = 0.0f;

int bounceCount = 0;

boost::shared_ptr<void> spinJumpParticleHandle;

Hedgehog::Base::CSharedString lastAnimation;

void CreateSpinJumpParticle(Sonic::Player::CPlayer* player)
{
    if (!spinJumpParticleHandle)
    {
        BlueBlurCommon::CreateParticle
        (
            player->m_spContext.get(),
            spinJumpParticleHandle,
            BlueBlurCommon::GetMatrixNode(),

            CONTEXT->StateFlag(eStateFlag_InvokeSuperSonic)
                ? "ef_ch_sps_yh1_spinattack"
                : "ef_ch_sng_yh1_spinattack",

            1
        );
    }
}

void DestroySpinJumpParticle(Sonic::Player::CPlayer* player)
{
    if (spinJumpParticleHandle)
        BlueBlurCommon::DestroyParticle(player->m_spContext.get(), spinJumpParticleHandle, true);
}

bool GetDoubleJumpFlag()
{
    return CONTEXT->StateFlag(eStateFlag_DoubleJumping);
}

void SetDoubleJumpFlag(bool value)
{
    CONTEXT->StateFlag(eStateFlag_DoubleJumping) = value;
}

bool IsBlacklistedAnimation(std::vector<const char*> animations, const char* animName)
{
    for (auto name : animations)
    {
        if (StringHelper::ContainsSubstring(animName, name))
            return true;
    }

    return false;
}

bool IsGrinding(const char* animName)
{
    std::vector<const char*> animations =
    {
        "Grind"
    };

    return IsBlacklistedAnimation(animations, animName);
}

bool IsDeathBySpinAttack(const char* animName)
{
    std::vector<const char*> animations =
    {
        "Homing",
        "JumpBall",
        "SpinAttack"
    };

    return IsBlacklistedAnimation(animations, animName);
}

bool IsSpinJump(const char* animName)
{
    std::vector<const char*> animations =
    {
        "JumpBall",
        "JumpHurdle",
        "JumpShort",
        "SpinAttack"
    };

    return IsBlacklistedAnimation(animations, animName);
}

bool IsWalkFall()
{
    return StringHelper::Compare(lastAnimation.c_str(), "Walk") && !StringHelper::Compare(lastAnimation.c_str(), "Land");
}

bool CanDropDash()
{
    return Configuration::dropDashType != Configuration::DropDashType::Disabled &&
           !CONTEXT->StateFlag(eStateFlag_OnWater) &&
           !(Configuration::dropDashType == Configuration::DropDashType::SideView && !CONTEXT->m_Is2DMode) &&
           !(Configuration::dropDashType == Configuration::DropDashType::ForwardView && CONTEXT->m_Is2DMode) &&
           !IsGrinding(CONTEXT->GetCurrentAnimationName().c_str()) &&
           !BlueBlurCommon::IsCurrentStageBoss();
}

bool CanSpinAttackRoll()
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    // TODO: reset on springs and jump boards.

    return !CONTEXT->StateFlag(eStateFlag_OnWater) &&
           !CONTEXT->StateFlag(eStateFlag_Boost) &&
           !CONTEXT->StateFlag(eStateFlag_Drifting) &&
           !(input.IsTapped(Sonic::eKeyState_LeftBumper) || input.IsTapped(Sonic::eKeyState_RightBumper)) &&
           !IsGrinding(CONTEXT->GetCurrentAnimationName().c_str());
}

void DriftUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    if
    (
        !context->m_Is2DMode &&
        !context->StateFlag(eStateFlag_InvokeSkateBoard) &&
        !context->StateFlag(eStateFlag_OutOfControl) &&
        !IsGrinding(context->GetCurrentAnimationName().c_str())
    )
    {
        // TODO: fix this for board.
        if (input.IsDown(Sonic::eKeyState_LeftTrigger) && input.LeftStickVertical > -0.65f)
        {
            if (!context->StateFlag(eStateFlag_Drifting))
                context->ChangeState("Drift");
        }
        else
        {
            if (context->StateFlag(eStateFlag_Drifting))
                context->ChangeState("Walk");
        }
    }
}

void DropDashStart(Sonic::Player::CPlayerSpeedContext* context)
{
    if (!updateDropDash && CanDropDash())
    {
        context->PlaySound(2002055, 1);

        updateDropDash = true;
    }
}

void DropDashEnd()
{
    updateDropDash = false;
    dropDashDeltaTime = 0.0f;
}

void DropDashUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    // Restore camera gradually.
    // TODO: apply to 2D.
    BlueBlurCommon::SetCameraParam
    (
        BlueBlurCommon::POSITION_SENSITIVE,

        LERP
        (
            BlueBlurCommon::GetCameraParam(BlueBlurCommon::POSITION_SENSITIVE),
            originalCameraPositionSensitive,
            dropDashDeltaTime / 8
        )
    );

    dropDashDeltaTime += updateInfo.DeltaTime;

    if (context->m_Grounded)
    {
        if (input.IsDown(Sonic::eKeyState_A))
        {
            if (updateDropDash && CanDropDash())
            {
                // Delay camera.
                BlueBlurCommon::SetCameraParam(BlueBlurCommon::POSITION_SENSITIVE, 25.0f);

                Impulse::VelocityZ
                (
                    context->GetVelocity().norm() + (context->m_Is2DMode
                        ? Configuration::dropDashVelocitySideView
                        : Configuration::dropDashVelocityForwardView)
                );

                DropDashEnd();

                updateSpinAttackRoll = true;
            }
        }
        else
        {
            DropDashEnd();
        }
    }
}

void DoubleJumpUpdate(Sonic::Player::CPlayerSpeedContext* context)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    if (Configuration::doubleJump)
    {
        // Disable jump dashing if homing is on A.
        if (!Configuration::homingOnX)
            CONTEXT->StateFlag(eStateFlag_EnableHomingAttack) = 0;

        if (input.IsTapped(Sonic::eKeyState_A))
        {
            if (GetDoubleJumpFlag())
            {
                DropDashStart(context);
            }
            else
            {
                CONTEXT->PlaySound(2002027, 1);

                CONTEXT->ChangeState("Jump");

                BlueBlurCommon::SetVelocityY
                (
                    (CONTEXT->GetVelocity().y() - CONTEXT->m_PreviousVelocity.y()) + CONTEXT->StateFlag(eStateFlag_OnWater)
                    ? Configuration::doubleJumpVelocityWater
                    : Configuration::doubleJumpVelocity
                );

                // Don't set double jump flag underwater.
                if (!CONTEXT->StateFlag(eStateFlag_OnWater))
                    SetDoubleJumpFlag(true);
            }
        }
    }
    else
    {
        if (input.IsTapped(Sonic::eKeyState_A))
            DropDashStart(context);
    }
}

void HomingAfterEnd()
{
    updateHomingAfter = false;

    homingAfterDeltaTime = 0.0f;
}

void HomingAfterUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    if (updateHomingAfter)
    {
        BlueBlurCommon::SetGameSpeed(LERP(BlueBlurCommon::GetGameSpeed(), 1.0f, homingAfterDeltaTime / 0.5f));

        homingAfterDeltaTime += updateInfo.DeltaTime;

        if (BlueBlurCommon::GetGameSpeed() >= 0.999999f)
        {
            BlueBlurCommon::SetGameSpeed(1.0f);

            HomingAfterEnd();
        }
    }
}

void SpinAttackRollEnd(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    isRolling            = false;
    updateSpinAttackRoll = false;

    spinAttackRollDeltaTime = 0.0f;

    // Reset camera.
    BlueBlurCommon::SetCameraParam(BlueBlurCommon::POSITION_SENSITIVE, originalCameraPositionSensitive);
}

void SpinAttackRollUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto velocityMag = context->GetVelocity().norm();
    {
        if (!updateSpinAttackRoll || !CanSpinAttackRoll())
            goto EndSpinAttackRoll;

        spinAttackRollDeltaTime += updateInfo.DeltaTime;
        {
            if (spinAttackRollDeltaTime > Configuration::spinAttackRollDuration)
                goto EndSpinAttackRoll;
        }

        if (velocityMag > 10.0f)
        {
            if (!isRolling)
            {
                CreateSpinJumpParticle(context->m_pPlayer);

                context->PlaySound(2002056, 1);

                isRolling = true;
            }

            // Force SpinAttack animation for this state.
            if (!StringHelper::Compare(context->GetCurrentAnimationName().c_str(), "SpinAttack"))
                context->ChangeAnimation("SpinAttack");

            auto front = context->GetFrontDirection().dot(Hedgehog::Math::CVector(0, 1, 0));
            {
                // NOTE: I have no idea what I'm doing, but it seems to work.

                float toAngle = sin(front) * 90;

                float slopeFactor     = 0.045;
                float slopeFactorUp   = 0.03;
                float slopeFactorDown = -0.06;

#if _DEBUG
                printf("front:       %f\n", front);
                printf("sin(Front):  %f\n", sin(front));
                printf("velocity:    %f\n", velocityMag);
#endif

                Impulse::VelocityZ
                (
                    velocityMag + ((sin(front) < 0.1f && sin(front) > -0.1f)
                        ? toAngle * slopeFactor
                        : (sin(front) > 0.0f
                            ? toAngle * slopeFactorUp
                            : toAngle * slopeFactorDown))
                );
            }

            BlueBlurCommon::SetCollision(context, BlueBlurCommon::TypeSonicBoost, true);
        }
        else
        {
            context->ChangeAnimation("Walk");

        EndSpinAttackRoll:
            DestroySpinJumpParticle(context->m_pPlayer);

            SpinAttackRollEnd(context, updateInfo);
        }
    }
}

void StompBounceUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto currentAnim = context->GetCurrentAnimationName().c_str();
    auto input       = Sonic::CInputState::GetInstance()->GetPadState();

    if (input.IsDown(Sonic::eKeyState_B))
    {
        if (StringHelper::Compare(currentAnim, "StompingSquat"))
        {
            if (!hasStompBounced)
            {
                if (Configuration::stompBounceCount != -1 && bounceCount >= Configuration::stompBounceCount)
                    return;

                bounceDeltaTime += updateInfo.DeltaTime;
                {
                    if (bounceDeltaTime > Configuration::stompBounceDelay)
                    {
                        hasStompBounced = true;

                        bounceDeltaTime = 0.0f;

                        context->ChangeState
                        (
                            context->StateFlag(eStateFlag_OnWater)
                                ? "HomingAttackAfter"
                                : "Jump"
                        );

                        if (context->StateFlag(eStateFlag_OnWater))
                        {
                            context->ChangeAnimation("SpinAttack");

                            CreateSpinJumpParticle(context->m_pPlayer);
                        }

                        Impulse::VelocityY
                        (
                            context->GetVelocity().y() + context->StateFlag(eStateFlag_OnWater)
                                ? Configuration::stompBounceVelocityWater
                                : Configuration::stompBounceVelocity
                        );

                        bounceCount++;
                    }
                }
            }
        }
    }
    else
    {
        hasStompBounced = true;

        bounceCount = 0;
    }
}

void StompBounceEnd(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    hasStompBounced = false;
}

HOOK(void, __fastcall, CPlayerSpeedUpdateParallel, 0xE6BF20, Sonic::Player::CPlayerSpeed* _this, void* _, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto context     = _this->GetContext();
    auto currentAnim = context->GetCurrentAnimationName().c_str();
    auto input       = Sonic::CInputState::GetInstance()->GetPadState();

    // printf("%s\n", currentAnim);

    Player::DeltaTime = updateInfo.DeltaTime;

    if (Configuration::disableBoostCollision)
    {
        if (BlueBlurCommon::IsCurrentStageBoss())
        {
            // Restore boost hit collision.
            WRITE_MEMORY(0x1117A6A, uint8_t, 0x8B, 0x0D, 0x84, 0x1B, 0xE6, 0x01);
        }
        else
        {
            // Disable boost hit collision.
            WRITE_JUMP(0x1117A6A, 0x1117A78);
        }
    }

    if (Configuration::homingSlowMotion)
        HomingAfterUpdate(context, updateInfo);

    if (context->StateFlag(eStateFlag_Dead))
        goto Return;

    if (context->m_Grounded)
    {
        SetDoubleJumpFlag(false);

        SpinAttackRollUpdate(context, updateInfo);

        if (Configuration::boostOnRT)
            DriftUpdate(context, updateInfo);

        if (Configuration::dropDashType != Configuration::DropDashType::Disabled)
            DropDashUpdate(context, updateInfo);

        if (Configuration::groundHoming)
        {
            FUNCTION_PTR(char, __fastcall, HomingUpdate, 0xDFFE30, Sonic::Player::CPlayerSpeedContext* _this, void* _, int a2);
            {
                HomingUpdate(context, (void*)0xDFFE30, -1);
            }
        }

        #pragma region WIP Rolling
        // if (Configuration::spinAttackRoll)
        // {
        //     if (context->m_Is2DMode && (input.LeftStickVertical <= -0.875f || input.IsDown(Sonic::eKeyState_DpadDown)))
        //         updateSpinAttackRoll = true;
        // }
        #pragma endregion

        if (Configuration::stompBounce)
            StompBounceUpdate(context, updateInfo);
    }
    else
    {
        SpinAttackRollEnd(context, updateInfo);
        StompBounceEnd(context, updateInfo);
    }

    if (!IsSpinJump(currentAnim) && !isRolling)
        DestroySpinJumpParticle(context->m_pPlayer);

    lastAnimation = currentAnim;

Return:
    originalCPlayerSpeedUpdateParallel(_this, _, updateInfo);
}

HOOK(char, __fastcall, CSonicContextHomingUpdate, 0xDFFE30, int* _this, void* _, int a2)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    if (Configuration::homingOnX)
    {
        // Disallow A button input.
        if (input.IsTapped(Sonic::eKeyState_A))
            return 0;
    }

    bool canHomingAttack = _this[934] != 0 &&
        !CONTEXT->StateFlag(eStateFlag_InvokeSkateBoard) &&
        !CONTEXT->StateFlag(eStateFlag_OutOfControl) &&
        !IsGrinding(CONTEXT->GetCurrentAnimationName().c_str());

    if
    (
        canHomingAttack &&

        input.IsTapped
        (
            Configuration::homingOnX
                ? Sonic::eKeyState_X
                : Sonic::eKeyState_A
        )
    )
    {
        if (Configuration::groundHoming)
        {
            if (CONTEXT->m_Grounded)
            {
                CONTEXT->ChangeState
                (
                    CONTEXT->StateFlag(eStateFlag_OnWater)
                        ? "HomingAttackAfter"
                        : "Jump"
                );
            }

            CONTEXT->ChangeState("HomingAttack");
        }
        else
        {
            if (!CONTEXT->m_Grounded)
                CONTEXT->ChangeState("HomingAttack");
        }

        return 1;
    }

    return originalCSonicContextHomingUpdate(_this, _, a2);
}

HOOK(int, __fastcall, CSonicStateJumpBallUpdate, 0x11BCB00, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    DoubleJumpUpdate((Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase());

    return originalCSonicStateJumpBallUpdate(_this);
}

HOOK(int, __fastcall, CSonicStateHomingAttackStart, 0x1232040, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    CreateSpinJumpParticle(((Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase())->m_pPlayer);

    return originalCSonicStateHomingAttackStart(_this);
}

HOOK(int, __fastcall, CSonicStateHomingAttackEnd, 0x1231F80, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    DestroySpinJumpParticle(((Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase())->m_pPlayer);

    return originalCSonicStateHomingAttackEnd(_this);
}

HOOK(void, __fastcall, CStateJumpShortStart, 0x1255820, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();
    {
        DoubleJumpUpdate(context);

        if (!BlueBlurCommon::IsSuper())
            CreateSpinJumpParticle(context->m_pPlayer);
    }

    isJumpShort = true;

    originalCStateJumpShortStart(_this);
}

HOOK(void, __fastcall, CStateJumpShortEnd, 0x11BF3A0, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    DestroySpinJumpParticle(((Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase())->m_pPlayer);

    originalCStateJumpShortEnd(_this);
}

HOOK(void, __fastcall, CStateLandJumpShortUpdate, 0x111C870, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    DestroySpinJumpParticle(((Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase())->m_pPlayer);

    originalCStateLandJumpShortUpdate(_this);
}

HOOK(int, __fastcall, CSonicStateFallStart, 0x1118FB0, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();

    isBoostToFall = context->StateFlag(eStateFlag_Boost) && !isAirBoostToFall;

    if (isAirBoostToFall || isBoostToFall)
    {
        // Don't transition animation.
        WRITE_MEMORY(0x1118DE5, uint8_t, 0xEB);
        WRITE_MEMORY(0x1118E94, uint8_t, 0xEB);
        WRITE_MEMORY(0x111910F, uint8_t, 0xEB);

        if (isBoostToFall)
            context->ChangeAnimation("AirBoost");
    }
    else
    {
        WRITE_MEMORY(0x1118DE5, uint8_t, 0x75);
        WRITE_MEMORY(0x1118E94, uint8_t, 0x76);
        WRITE_MEMORY(0x111910F, uint8_t, 0x75);
    }

    return originalCSonicStateFallStart(_this);
}

HOOK(void, __fastcall, CSonicStateFallUpdate, 0x1118C50, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();

    if (isBoostToFall && !context->StateFlag(eStateFlag_Boost))
    {
        isBoostToFall = false;

        context->ChangeAnimation("Fall");

        // Allow animation to change to Fall and FallLarge.
        WRITE_MEMORY(0x1118DE5, uint8_t, 0x75);
        WRITE_MEMORY(0x1118E94, uint8_t, 0x76);
    }

    DoubleJumpUpdate(context);

    if (updateDropDash)
    {
        CreateSpinJumpParticle(context->m_pPlayer);

        context->ChangeAnimation("SpinAttack");
    }
    else
    {
        DestroySpinJumpParticle(context->m_pPlayer);

        if (isJumpShort)
        {
            context->ChangeAnimation("Fall");

            isJumpShort = false;
        }
    }

    originalCSonicStateFallUpdate(_this);
}

HOOK(int, __fastcall, CSonicStateFallEnd, 0x1118F20, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    isAirBoostToFall = false;
    isBoostToFall    = false;

    return originalCSonicStateFallEnd(_this);
}

HOOK(int, __fastcall, MsgRestartStage, 0xE76810, int* _this, void* _, int* message)
{
    DropDashEnd();
    SpinAttackRollEnd(CONTEXT, hh::fnd::SUpdateInfo());
    StompBounceEnd(CONTEXT, hh::fnd::SUpdateInfo());

    return originalMsgRestartStage(_this, _, message);
}

ASM_HOOK(0xF368BF, CObjPlaTramCarBoostButtonChange)
{
    static void* returnAddress  = (void*)0xF3691D;
    static void* successAddress = (void*)0xF368C4;

    __asm
    {
        test word ptr[esi], 0x8000
        jz   Return

        jmp [successAddress]

    Return:
        jmp [returnAddress]
    }
}

ASM_HOOK(0x123332B, AirBoostToFallFlag)
{
    static void* returnAddress = (void*)0x1233330;

    static const char* animName = "Fall";

    __asm
    {
        mov isAirBoostToFall, 1

        push [animName]

        jmp [returnAddress]
    }
}

void __fastcall OnDestroyEnemy()
{
    if
    (
        BlueBlurCommon::IsClassic() ||
        !IsDeathBySpinAttack(CONTEXT->GetCurrentAnimationName().c_str())
    )
    {
        return;
    }

    if (Configuration::cameraShake)
        Camera::Shake(0.125f, 0.025f, 0.5f);

    if (Configuration::homingSlowMotion)
    {
        BlueBlurCommon::SetGameSpeed(0.125f);

        updateHomingAfter = true;
    }
}

ASM_HOOK(0xBDDD9A, DestroyEnemy)
{
    static void* returnAddress = (void*)0xBDDDA1;

    __asm
    {
        inc word ptr [esi + 0E0h]

        call OnDestroyEnemy
        mov  edx, eax

        jmp [returnAddress]
    }
}

ASM_HOOK(0x1119125, WalkFallFlag)
{
    static void* returnAddress    = (void*)0x111912A;
    static void* interruptAddress = (void*)0x9BF710;
    static void* skipAddress      = (void*)0x1119188;

    __asm
    {
        call [interruptAddress]

        cmp IsWalkFall, 0
        jnz SkipFall

        jmp [returnAddress]

    SkipFall:
        jmp [skipAddress]
    }
}

void Player::Install()
{
    INSTALL_HOOK(CPlayerSpeedUpdateParallel);
    INSTALL_HOOK(CSonicContextHomingUpdate);
    INSTALL_HOOK(CSonicStateJumpBallUpdate);
    INSTALL_HOOK(CSonicStateHomingAttackStart);
    INSTALL_HOOK(CSonicStateHomingAttackEnd);
    INSTALL_HOOK(CStateJumpShortStart);
    INSTALL_HOOK(CStateJumpShortEnd);
    INSTALL_HOOK(CStateLandJumpShortUpdate);
    INSTALL_HOOK(CSonicStateFallStart);
    INSTALL_HOOK(CSonicStateFallUpdate);
    INSTALL_HOOK(CSonicStateFallEnd);
    INSTALL_HOOK(MsgRestartStage);

    INSTALL_ASM_HOOK(AirBoostToFallFlag);
    INSTALL_ASM_HOOK(DestroyEnemy);
    INSTALL_ASM_HOOK(WalkFallFlag);

    if (Configuration::boostOnRT)
    {
        // https://github.com/brianuuu/DllMods/blob/master/Source/Sonic06DefinitiveExperience/NextGenPhysics.cpp

        WRITE_MEMORY(0xDFDF4C,  uint32_t, 32); // Air Boost
        WRITE_MEMORY(0xDFF25B,  uint32_t, 32); // Grind Boost
        WRITE_MEMORY(0xE3D991,  uint32_t, 32); // Blast Off
        WRITE_MEMORY(0xE4776B,  uint32_t, 32); // Dummy Boost
        WRITE_MEMORY(0x11177EE, uint32_t, 32); // Boost
        WRITE_MEMORY(0x1118CEE, uint32_t, 32); // Fall Boost
        WRITE_MEMORY(0x111BE61, uint32_t, 32); // Null Boost?
        WRITE_MEMORY(0x111BEE8, uint32_t, 32); // Dummy Boost plugin
        WRITE_MEMORY(0x111D801, uint32_t, 32); // Board Fall Boost
        WRITE_MEMORY(0x11A0716, uint32_t, 32); // Dummy Boost External
        WRITE_MEMORY(0x11A07D7, uint32_t, 32); // Speed external control
        WRITE_MEMORY(0x11A0DA8, uint32_t, 32); // Speed external control
        WRITE_MEMORY(0x11BD057, uint32_t, 32); // DivingDive start
        WRITE_MEMORY(0x124AF01, uint32_t, 32); // DivingDive end

        // PlaTramCar
        INSTALL_ASM_HOOK(CObjPlaTramCarBoostButtonChange);

        // Unmap drift.
        WRITE_MEMORY(0xDF2DFF,  uint32_t, -1);
        WRITE_MEMORY(0xDFF62B,  uint32_t, -1);
        WRITE_MEMORY(0xDFF816,  uint32_t, -1);
        WRITE_MEMORY(0x1119549, uint32_t, -1);
        WRITE_MEMORY(0x119910D, uint32_t, -1);
    }

    if (Configuration::lightDashOnLS)
    {
        WRITE_MEMORY(0xDFFD5F,  uint32_t, 31); // LightSpeedDashReady
        WRITE_MEMORY(0x111761A, uint32_t, 31); // LightSpeedDash
    }
}