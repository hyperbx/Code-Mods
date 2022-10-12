bool hasStompBounced      = false;
bool isAirBoostToFall     = false;
bool isBoostToFall        = false;
bool isRolling            = false;
bool updateDropDash       = false;
bool updateSpinAttackRoll = false;

float bounceDeltaTime = 0.0f;
float spinAttackRollDeltaTime = 0.0f;

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

            4
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

bool IsSpinJumpAnimation(const char* animName)
{
    std::vector<const char*> animations =
    {
        "Homing",
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
           !(Configuration::dropDashType == Configuration::DropDashType::ForwardView && CONTEXT->m_Is2DMode);
}

void DriftUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    if
    (
        !context->m_Is2DMode &&
        !context->StateFlag(eStateFlag_InvokeSkateBoard) &&
        !context->StateFlag(eStateFlag_OutOfControl)
    )
    {
        // TODO: fix this for board.
        if (input.IsDown(Sonic::eKeyState_LeftTrigger))
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

void DropDashUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    if (!CanDropDash())
        goto ExitDropDash;

    if (input.IsDown(Sonic::eKeyState_A))
    {
        if (updateDropDash)
        {
            Impulse::VelocityZ(Configuration::dropDashVelocity);

            updateDropDash = false;
            updateSpinAttackRoll = true;
        }
    }
    else
    {
    ExitDropDash:
        updateDropDash = false;
    }
}

void DoubleJumpUpdate()
{
    if (!Configuration::doubleJump)
        return;

    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    // Disable jump dashing if homing is on A.
    if (!Configuration::homingOnX)
        CONTEXT->StateFlag(eStateFlag_EnableHomingAttack) = 0;

    if (input.IsTapped(Sonic::eKeyState_A) && !CONTEXT->StateFlag(eStateFlag_Dead))
    {
        if (GetDoubleJumpFlag())
        {
            if (!updateDropDash && CanDropDash())
            {
                CONTEXT->PlaySound(2002055, 1);

                updateDropDash = true;
            }
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

void SpinAttackRollEnd(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    if (isRolling)
    {
        DestroySpinJumpParticle(context->m_pPlayer);

        context->ChangeAnimation("Walk");
    }

    isRolling = false;
    updateSpinAttackRoll = false;

    spinAttackRollDeltaTime = 0.0f;
}

void SpinAttackRollUpdate(Sonic::Player::CPlayerSpeedContext* context, const hh::fnd::SUpdateInfo& updateInfo)
{
    if (!updateSpinAttackRoll || CONTEXT->StateFlag(eStateFlag_OnWater))
        return;

    auto velocityMag = context->GetVelocity().norm();
    {
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
            }

            // Force SpinAttack animation for this state.
            if (!StringHelper::Compare(context->GetCurrentAnimationName().c_str(), "SpinAttack"))
                context->ChangeAnimation("SpinAttack");

            #pragma region WIP Physics
            // auto front = context->GetFrontDirection().dot(Hedgehog::Math::CVector(0, 1, 0));
            // auto vel = (velocityMag * cos(front));
               
            // float slopeFactor = 0.125f;
            // float slopeFactorUp = 0.25;
            // float slopeFactorDown = 0.75;
               
            // vel -= vel * (front * (vel > 0.0f && sin(front) > 0.0f ? slopeFactorUp : slopeFactorDown)) / 2;
               
            // printf("Front:       %f\n", front);
            // printf("Front (sin): %f\n", sin(front));
            // printf("Front (cos): %f\n", cos(front));
            // printf("Velocity:    %f\n", vel);
            #pragma endregion

            Impulse::VelocityZ(velocityMag);

            isRolling = true;
        }
        else
        {
        EndSpinAttackRoll:
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

                        context->ChangeState("Jump");

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
            FUNCTION_PTR(char, __fastcall, HomingUpdate, 0xDFFE30, Sonic::Player::CPlayerSpeedContext * _this, void* _, int a2);
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

    if (!IsSpinJumpAnimation(currentAnim))
        DestroySpinJumpParticle(context->m_pPlayer);

    lastAnimation = currentAnim;

    originalCPlayerSpeedUpdateParallel(_this, _, updateInfo);
}

HOOK(int, __fastcall, CSonicStateHomingAttackStart, 0x1232040, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();
    {
        CreateSpinJumpParticle(context->m_pPlayer);
    }

    return originalCSonicStateHomingAttackStart(_this);
}

HOOK(int, __fastcall, CSonicStateHomingAttackEnd, 0x1231F80, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();
    {
        DestroySpinJumpParticle(context->m_pPlayer);
    }

    return originalCSonicStateHomingAttackEnd(_this);
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
        !CONTEXT->StateFlag(eStateFlag_OutOfControl);

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
                CONTEXT->ChangeState("Jump");

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

    DoubleJumpUpdate();

    originalCSonicStateFallUpdate(_this);
}

HOOK(int, __fastcall, CSonicStateFallEnd, 0x1118F20, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    isAirBoostToFall = false;
    isBoostToFall    = false;

    return originalCSonicStateFallEnd(_this);
}

HOOK(int, __fastcall, CSonicStateJumpBallUpdate, 0x11BCB00, float* _this)
{
    DoubleJumpUpdate();

    return originalCSonicStateJumpBallUpdate(_this);
}

HOOK(void, __fastcall, CStateJumpShortStart, 0x1255820, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    DoubleJumpUpdate();

    if (!BlueBlurCommon::IsSuper())
    {
        auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();
        {
            CreateSpinJumpParticle(context->m_pPlayer);
        }
    }

    originalCStateJumpShortStart(_this);
}

HOOK(void, __fastcall, CStateJumpShortEnd, 0x11BF3A0, hh::fnd::CStateMachineBase::CStateBase* _this)
{
    if (!BlueBlurCommon::IsSuper())
    {
        auto context = (Sonic::Player::CPlayerSpeedContext*)_this->GetContextBase();
        {
            DestroySpinJumpParticle(context->m_pPlayer);
        }
    }

    originalCStateJumpShortEnd(_this);
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

ASM_HOOK(0x123332B, AirBoostFall)
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

ASM_HOOK(0x1119125, FallStart)
{
    static void* returnAddress = (void*)0x111912A;
    static void* interruptAddress = (void*)0x9BF710;
    static void* skipAddress = (void*)0x1119188;

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
    INSTALL_HOOK(CSonicStateHomingAttackStart);
    INSTALL_HOOK(CSonicStateHomingAttackEnd);
    INSTALL_HOOK(CSonicContextHomingUpdate);
    INSTALL_HOOK(CSonicStateFallStart);
    INSTALL_HOOK(CSonicStateFallUpdate);
    INSTALL_HOOK(CSonicStateFallEnd);
    INSTALL_HOOK(CSonicStateJumpBallUpdate);
    INSTALL_HOOK(CStateJumpShortStart);
    INSTALL_HOOK(CStateJumpShortEnd);

    INSTALL_ASM_HOOK(AirBoostFall);
    INSTALL_ASM_HOOK(FallStart);

    // Restore XButtonHoming string to disable the HMM code.
    WRITE_STRING(0x15FA418, "XButtonHoming");

    // Loop dash ring animations.
    WRITE_MEMORY(0x1276D20, uint8_t, 0x1D);
    WRITE_MEMORY(0x1276D87, uint8_t, 0x1D);

    // Replace animations with the jump ball.
    WRITE_MEMORY(0x12733A2, const char*, "sn_ball_loop"); // JumpShortBegin
    WRITE_MEMORY(0x1273409, const char*, "sn_ball_loop"); // JumpShort
    WRITE_MEMORY(0x1273470, const char*, "sn_ball_loop"); // JumpShortTop
    WRITE_MEMORY(0x127380A, const char*, "sn_ball_loop"); // JumpHurdleL
    WRITE_MEMORY(0x1273876, const char*, "sn_ball_loop"); // JumpHurdleR
    WRITE_MEMORY(0x1273A12, const char*, "sn_ball_loop"); // SquatToJump

    // Disable boost particles.
    WRITE_MEMORY(0x15A3568, uint8_t, 0x00); // ef_bo_sha_yh1_boost1
    WRITE_MEMORY(0x15E9048, uint8_t, 0x00); // ef_ch_sng_yh1_boost1
    WRITE_MEMORY(0x15E9060, uint8_t, 0x00); // ef_ch_sng_yh1_boost2
    WRITE_MEMORY(0x15EE774, uint8_t, 0x00); // ef_bo_sha_yh1_hyper_sn
    WRITE_MEMORY(0x15EE78C, uint8_t, 0x00); // ef_bo_sha_yh1_hyper_sn
    WRITE_MEMORY(0x15F99F8, uint8_t, 0x00); // ef_ch_sps_yh1_boost1
    WRITE_MEMORY(0x15F9A10, uint8_t, 0x00); // ef_ch_sps_yh1_boost2
    WRITE_MEMORY(0x164330C, uint8_t, 0x00); // ef_st_ssh_yh1_bobsled_boost

    // Disable spin dash on dash panels.
    WRITE_MEMORY(0xE0AC1C, uint8_t, 0xE9, 0x27, 0x01, 0x00, 0x00);
    WRITE_MEMORY(0xE0C734, uint8_t, 0xE9, 0x27, 0x01, 0x00, 0x00);

    // Right mouth bones.
    WRITE_MEMORY(0x015E8F9C, const char*, "MouthR_Reference");
    WRITE_MEMORY(0x015E8FA4, const char*, "MouthR_Position");
    WRITE_MEMORY(0x015E8FAC, const char*, "MouthR_Jaw");
    WRITE_MEMORY(0x015E8FB4, const char*, "MouthR_Teeth_Low");
    WRITE_MEMORY(0x015E8FBC, const char*, "MouthR_Lip_C");
    WRITE_MEMORY(0x015E8FC4, const char*, "MouthR_Teeth_Up");
    WRITE_MEMORY(0x015E8FCC, const char*, "MouthR_Lip_L");
    WRITE_MEMORY(0x015E8FD4, const char*, "MouthR_Lip_R");
    WRITE_MEMORY(0x015E8FDC, const char*, "MouthR_Nose");

    // Left mouth bones.
    WRITE_MEMORY(0x015E8FE4, const char*, "MouthL_Reference");
    WRITE_MEMORY(0x015E8FEC, const char*, "MouthL_Position");
    WRITE_MEMORY(0x015E8FF4, const char*, "MouthL_Jaw");
    WRITE_MEMORY(0x015E8FFC, const char*, "MouthL_Teeth_Low");
    WRITE_MEMORY(0x015E9004, const char*, "MouthL_Lip_C");
    WRITE_MEMORY(0x015E900C, const char*, "MouthL_Teeth_Up");
    WRITE_MEMORY(0x015E9014, const char*, "MouthL_Lip_L");
    WRITE_MEMORY(0x015E901C, const char*, "MouthL_Lip_R");
    WRITE_MEMORY(0x015E9024, const char*, "MouthL_Nose");

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