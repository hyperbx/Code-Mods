CL_SCAN_SIGNATURE(m_SigActionProcessor, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x60\x48\x0F\xBE\xF2", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSetCurrentStateCaller, "\xE8\xCC\xCC\xCC\xCC\x48\x8B\x47\x50\xBA\xFF\xF5\xD5\x14\x48\x8B\x88\x80\x00\x00\x00\xE8\xCC\xCC\xCC\xCC\x40\x0F\xB6\xD6", "x????xxxxxxxxxxxxxxxxx????xxxx");

CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableAirTricksFromTerrain, "\x74\x19\x41\xB0\x01\x8B\x0D", "xxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableAirTricksFromTraversalObjects, "\xB0\x01\x88\x46\x3E", "xxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableCyloop, "\x0F\x84\xC8\x00\x00\x00\xC0\xE8\x06", "xxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableGrandSlam, "\xE8\xCC\xCC\xCC\xCC\x48\x8B\x5C\x24\x60\x0F\x28\x7C\x24\x20", "x????xxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisablePhantomRush, "\x72\x09\x66\x83\x89\xF0\x00\x00\x00\x40\xC3\x0F\x2F\xC2\x77\x0C\xB8\xBF\xFF\x00\x00\x66\x21\x81\xF0\x00\x00\x00\xC3", "x?xxx????xxxxxx?xxxxxxxx????x");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisablePhantomRushUI, "\x0F\x84\x98\x00\x00\x00\xBA\x4C\x23\x00\x00", "xxxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableQuickCyloopUI, "\x80\x4F\x38\x01\x48\x8B\xCE", "xxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableRecoverySmash, "\x0F\x84\xD5\x00\x00\x00\x48\x8B\xD7\x49\x8B\xCD", "xxxxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableSonicBoomSpinChargeCheck, "\x75\x3F\xBA\x0E\x00\x00\x00\x48\x8B\xCF", "xxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableSpinSlash, "\x74\x79\xBA\x2E\x00\x00\x00", "xxxxxxx");

enum EAction : int8_t
{
	EAction_Root,
	EAction_HomingAttack,
	EAction_AerialHomingAttack,
	EAction_Pursuit,             // Pursuit Kick (unused)
	EAction_Stomping,            // Stomp Attack
	EAction_LoopKick,
	EAction_Crasher,             // Wild Rush
	EAction_SpinSlash,
	EAction_SonicBoom,
	EAction_CrossSlash,
	EAction_HomingShot,
	EAction_ChargeAttack,        // Cyclone Kick
	EAction_QuickCyloop,
	EAction_AerialQuickCyloop,
	EAction_AcceleCombo1,
	EAction_AcceleCombo2,
	EAction_AcceleCombo3,
	EAction_AcceleCombo4,
	EAction_AerialAcceleCombo1,
	EAction_AerialAcceleCombo2,
	EAction_AerialAcceleCombo3,
	EAction_AerialAcceleCombo4,
	EAction_ComboFinish,
	EAction_SpinJump,
	EAction_Smash,              // Grand Slam
	EAction_Behind,
	EAction_Guarded,
	EAction_Avoid,
	EAction_AirBoost,
	EAction_AfterAirBoost
};

FUNCTION_PTR(char, __fastcall, fpSetCurrentState, READ_CALL((int64_t)m_SigSetCurrentStateCaller()), int64_t in_gocPlayerHsmField56, int in_stateIndex, int a3);

HOOK(bool, __fastcall, SetCurrentState, READ_CALL((int64_t)m_SigSetCurrentStateCaller()), int64_t in_gocPlayerHsmField56, int in_stateIndex, int a3)
{
	if (Configuration::IsNoSonicBoom && in_stateIndex == 151)
		return false;

	return originalSetCurrentState(in_gocPlayerHsmField56, in_stateIndex, a3);
}

HOOK(int64_t, __fastcall, ActionProcessor, m_SigActionProcessor(), int64_t a1, EAction in_action, int8_t a3, int64_t a4, char a5)
{
#if _DEBUG
	printf("[DisableSkills] in_attackId: %d\n", in_action);
#endif

	switch (in_action)
	{
		case EAction_CrossSlash:
			return Configuration::IsNoCrossSlash ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_ChargeAttack:
			return Configuration::IsNoCycloneKick ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_Smash:
		{
			// This ID is shared between Grand Slam and Recovery Smash...
			if (Configuration::IsNoGrandSlam && !Configuration::IsNoRecoverySmash)
				return originalActionProcessor(a1, in_action, a3, a4, a5);

			return Configuration::IsNoGrandSlam ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);
		}

		case EAction_HomingShot:
		{
			if (!Configuration::IsNoHomingShot)
				break;
			
			// Switch to StateHomingAttack.
			fpSetCurrentState(a1, 62, 0);

			return 0;
		}

		case EAction_LoopKick:
			return Configuration::IsNoLoopKick ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_QuickCyloop:
			return Configuration::IsNoQuickCyloop ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_SpinSlash:
			return Configuration::IsNoSpinSlash ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_Stomping:
			return Configuration::IsNoStompAttack ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_Crasher:
			return Configuration::IsNoWildRush ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);

		case EAction_SonicBoom:
			return Configuration::IsNoSonicBoom ? 0 : originalActionProcessor(a1, in_action, a3, a4, a5);
	}

	return originalActionProcessor(a1, in_action, a3, a4, a5);
}

EXPORT void Init()
{
	if (!m_IsSigValid)
	{
		MessageBoxA
		(
			nullptr,
			"A signature scan failed validation...\n\nThis mod may be incompatible with your current game version, or is conflicting with another DLL mod.",
			"Disable Skills",
			MB_ICONERROR
		);

		exit(-1);
	}

	Configuration::Read();

	INSTALL_HOOK(ActionProcessor);
	INSTALL_HOOK(SetCurrentState);

	if (Configuration::IsNoAirTrick)
	{
		if (m_SigDisableAirTricksFromTerrain() != nullptr && m_SigDisableAirTricksFromTraversalObjects() != nullptr)
		{
			WRITE_MEMORY((int64_t)m_SigDisableAirTricksFromTerrain(), uint8_t, 0xEB);
			WRITE_NOP((int64_t)m_SigDisableAirTricksFromTraversalObjects(), 2);
		}
	}

	if (Configuration::IsNoCyloop)
	{
		if (m_SigDisableCyloop() != nullptr)
		{
			READ_JUMP(DisableCyloop, m_SigDisableCyloop());
			WRITE_JUMP((int64_t)m_SigDisableCyloop(), DisableCyloop);
		}
	}

	if (Configuration::IsNoGrandSlam)
	{
		if (m_SigDisableGrandSlam() != nullptr)
			WRITE_NOP((int64_t)m_SigDisableGrandSlam(), 5);
	}

	if (Configuration::IsNoPhantomRush)
	{
		if (m_SigDisablePhantomRush() != nullptr && m_SigDisablePhantomRushUI() != nullptr)
		{
			WRITE_MEMORY((int64_t)m_SigDisablePhantomRush(), uint8_t, 0xEB);

			READ_JUMP(DisablePhantomRushUI, m_SigDisablePhantomRushUI());
			WRITE_JUMP((int64_t)m_SigDisablePhantomRushUI(), DisablePhantomRushUI);
		}
	}

	if (Configuration::IsNoQuickCyloop)
	{
		if (m_SigDisableQuickCyloopUI() != nullptr)
			WRITE_NOP((int64_t)m_SigDisableQuickCyloopUI(), 4);
	}

	if (Configuration::IsNoRecoverySmash)
	{
		if (m_SigDisableRecoverySmash() != nullptr)
		{
			READ_JUMP(DisableRecoverySmash, m_SigDisableRecoverySmash());
			WRITE_JUMP((int64_t)m_SigDisableRecoverySmash(), DisableRecoverySmash);
		}
	}

	if (Configuration::IsNoSonicBoom)
	{
		if (m_SigDisableSonicBoomSpinChargeCheck() != nullptr)
			WRITE_NOP(m_SigDisableSonicBoomSpinChargeCheck(), 2);
	}

	if (Configuration::IsNoSpinSlash)
	{
		if (m_SigDisableSpinSlash() != nullptr)
			WRITE_MEMORY((int64_t)m_SigDisableSpinSlash(), uint8_t, 0xEB);
	}
}