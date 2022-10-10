bool isDoubleJump    = false;
bool hasStompBounced = false;

float bounceDeltaTime = 0.0f;

HOOK(void, __fastcall, CPlayerSpeedUpdateParallel, 0xE6BF20, Sonic::Player::CPlayerSpeed* _this, void* _, const hh::fnd::SUpdateInfo& updateInfo)
{
    auto context     = _this->GetContext();
    auto currentAnim = context->GetCurrentAnimationName().c_str();
    auto input       = Sonic::CInputState::GetInstance()->GetPadState();

    if (context->m_Grounded)
    {
        isDoubleJump = false;

        if (Configuration::boostOnRT)
        {
            if
            (
                context->StateFlag(eStateFlag_Drifting) &&
                !input.IsDown(Sonic::eKeyState_LeftTrigger) &&
                input.IsDown(Sonic::eKeyState_RightTrigger)
            )
            {
                context->ChangeState("Walk");
            }
        }
        
        if (Configuration::groundHoming)
        {
            FUNCTION_PTR(char, __fastcall, HomingUpdate, 0xDFFE30, Sonic::Player::CPlayerSpeedContext* _this, void* _, int a2);
            {
                HomingUpdate(context, (void*)0xDFFE30, -1);
            }
        }

        if (Configuration::stompBounce)
        {
            if (input.IsDown(Sonic::eKeyState_B))
            {
                if (StringHelper::Compare(currentAnim, "StompingSquat"))
                {
                    if (!hasStompBounced)
                    {
                        bounceDeltaTime += updateInfo.DeltaTime;

                        if (bounceDeltaTime > 0.08f)
                        {
                            context->ChangeState("Jump");

                            context->m_Velocity.y() += 20.0f;

                            hasStompBounced = true;

                            bounceDeltaTime = 0.0f;
                        }
                    }
                }
            }
            else
            {
                hasStompBounced = true;
            }
        }
    }
    else
    {
        hasStompBounced = false;
    }

    originalCPlayerSpeedUpdateParallel(_this, _, updateInfo);
}

HOOK(int, __fastcall, JumpUpdate, 0x11BCB00, float* _this)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    // Disable jump dashing.
    if (Configuration::doubleJump && !Configuration::homingOnX)
        CONTEXT->StateFlag(eStateFlag_EnableHomingAttack) = 0;

    if (!isDoubleJump && input.IsTapped(Sonic::eKeyState_A))
    {
        CONTEXT->PlaySound(2002027, 1);

        CONTEXT->ChangeState("Jump");

        CONTEXT->m_Velocity.y() = (CONTEXT->m_Velocity.y() - CONTEXT->m_PreviousVelocity.y()) + 15.0f;

        isDoubleJump = true;
    }

    return originalJumpUpdate(_this);
}

HOOK(char, __fastcall, HomingUpdate, 0xDFFE30, int* _this, void* _, int a2)
{
    auto input = Sonic::CInputState::GetInstance()->GetPadState();

    if (Configuration::homingOnX)
    {
        // Disallow A button input.
        if (input.IsTapped(Sonic::eKeyState_A))
            return 0;
    }

    bool canHomingAttack = _this[934] != 0;
    {
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
                // Get Sonic off the ground!
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
    }

    return originalHomingUpdate(_this, _, a2);
}

void __declspec(naked) CObjPlaTramCarBoostButtonChange_MidAsmHook()
{
    static void* successAddress = (void*)0xF368C4;
    static void* returnAddress  = (void*)0xF3691D;

    __asm
    {
        test word ptr[esi], 0x8000
        jz   Return

        jmp [successAddress]

    Return:
        jmp [returnAddress]
    }
}

void Player::Install()
{
    INSTALL_HOOK(CPlayerSpeedUpdateParallel);
    INSTALL_HOOK(HomingUpdate);

    // Restore XButtonHoming string to disable the HMM code.
    WRITE_STRING(0x15FA418, "XButtonHoming");

    // Disable falling animations.
    WRITE_JUMP(0x111910F, 0x1119188);

    if (Configuration::doubleJump)
        INSTALL_HOOK(JumpUpdate);

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
        WRITE_JUMP(0xF368BF, CObjPlaTramCarBoostButtonChange_MidAsmHook);
    }

    if (Configuration::lightDashOnLS)
    {
        WRITE_MEMORY(0xDFFD5F,  uint32_t, 31); // LightSpeedDashReady
        WRITE_MEMORY(0x111761A, uint32_t, 31); // LightSpeedDash
    }
}