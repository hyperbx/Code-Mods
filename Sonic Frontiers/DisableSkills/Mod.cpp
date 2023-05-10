CL_SCAN_SIGNATURE(m_SigAttackProcessor, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x60\x48", "xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigSetCurrentStateCaller, "\xE8\xCC\xCC\xCC\xCC\x48\x8D\x4D\xC0\xE8\xCC\xCC\xCC\xCC\x48\x8B\x47\x50", "x????xxxxx????xxxx");

CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableAirTricksFromTerrain, "\x74\x10\x41\xB0\x01\xBA\x28\x00\x00\x00", "xxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableAirTricksFromTraversalObjects, "\xB0\x01\x88\x46\x3E", "xxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableCyloop, "\x0F\x84\xC8\x00\x00\x00\xC0\xE8\x06", "xxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableGrandSlam, "\xE8\xCC\xCC\xCC\xCC\x48\x8B\x5C\x24\x60\x0F\x28\x7C\x24\x20", "x????xxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisablePhantomRush, "\x72\x09\x66\x83\x89\xF0\x00\x00\x00\x40\xC3\x0F\x2F\xC2\x77\x0C\xB8\xBF\xFF\x00\x00\x66\x21\x81\xF0\x00\x00\x00\xC3", "x?xxx????xxxxxx?xxxxxxxx????x");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisablePhantomRushUI, "\x0F\x84\x98\x00\x00\x00\xBA\x1C\x23\x00\x00", "xxxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableQuickCyloopUI, "\x80\x4F\x38\x01\x48\x8B\xCE", "xxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableRecoverySmash, "\x0F\x84\xD5\x00\x00\x00\x48\x8B\xD7\x49\x8B\xCD", "xxxxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableSonicBoom, "\xE8\xCC\xCC\xCC\xCC\xB0\x01\x48\x8B\x5C\x24\x70\x48\x83\xC4\x60\x5F\xC3\x48\x8B\x5C\x24\x70", "x????xxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDisableSpinSlash, "\x74\x79\xBA\x2D\x00\x00\x00", "xxxxxxx");

enum EAttackID : uint8_t
{
	EAttackID_Default = 0,
	EAttackID_HomingAttack = 1,
	EAttackID_StompAttack = 4,
	EAttackID_LoopKick = 5,
	EAttackID_WildRush = 6,
	EAttackID_SpinSlash = 7,
	EAttackID_CrossSlash = 9,
	EAttackID_HomingShot = 10,
	EAttackID_CycloneKick = 11,
	EAttackID_QuickCyloop = 12,
	EAttackID_Attack01 = 14,
	EAttackID_Attack02 = 15,
	EAttackID_Attack03 = 16,
	EAttackID_Attack04 = 17,
	EAttackID_AttackFinal = 22,
	EAttackID_GrandSlam = 24
};

FUNCTION_PTR(char, __fastcall, fpSetCurrentState, READ_CALL((int64_t)m_SigSetCurrentStateCaller()), int64_t in_gocPlayerHsmField56, int in_stateIndex, int a3);

HOOK(int64_t, __fastcall, AttackProcessor, m_SigAttackProcessor(), int64_t a1, EAttackID in_attackId, uint8_t a3, int64_t a4)
{
#if _DEBUG
	printf("[DisableSkills] in_attackId: %d\n", in_attackId);
#endif

	switch (in_attackId)
	{
		case EAttackID_CrossSlash:
			return Configuration::IsNoCrossSlash ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);

		case EAttackID_CycloneKick:
			return Configuration::IsNoCycloneKick ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);

		case EAttackID_GrandSlam:
		{
			// This ID is shared between Grand Slam and Recovery Smash...
			if (Configuration::IsNoGrandSlam && !Configuration::IsNoRecoverySmash)
				return originalAttackProcessor(a1, in_attackId, a3, a4);

			return Configuration::IsNoGrandSlam ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);
		}

		case EAttackID_HomingShot:
		{
			if (!Configuration::IsNoHomingShot)
				break;
			
			// Switch to StateHomingAttack.
			fpSetCurrentState(a1, 60, 0);

			return 0;
		}

		case EAttackID_LoopKick:
			return Configuration::IsNoLoopKick ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);

		case EAttackID_QuickCyloop:
			return Configuration::IsNoQuickCyloop ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);

		case EAttackID_SpinSlash:
			return Configuration::IsNoSpinSlash ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);

		case EAttackID_StompAttack:
			return Configuration::IsNoStompAttack ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);

		case EAttackID_WildRush:
			return Configuration::IsNoWildRush ? 0 : originalAttackProcessor(a1, in_attackId, a3, a4);
	}

	return originalAttackProcessor(a1, in_attackId, a3, a4);
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

	INSTALL_HOOK(AttackProcessor);

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
		if (m_SigDisableSonicBoom() != nullptr)
			WRITE_NOP((int64_t)m_SigDisableSonicBoom(), 5);
	}

	if (Configuration::IsNoSpinSlash)
	{
		if (m_SigDisableSpinSlash() != nullptr)
			WRITE_MEMORY((int64_t)m_SigDisableSpinSlash(), uint8_t, 0xEB);
	}
}