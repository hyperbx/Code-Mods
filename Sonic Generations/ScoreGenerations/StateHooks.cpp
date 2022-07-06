bool StateHooks::isResultsHooked = false;

#pragma region ----- Hooked Functions -----

void OnLoad()
{
	// Set results hook state.
	StateHooks::isResultsHooked = HudSonicStage::IsStageForbidden() ? false : true;

	if (HudSonicStage::isVisible)
	{
		if (HudSonicStage::IsStageForbidden())
		{
			// Use Sonic Generations' HUD XNCP.
			if (!Configuration::customXNCP)
				WRITE_MEMORY(0x168E333, const char, "_default");

			goto SkipScoreDraw;
		}
		else
		{
			if (!Configuration::customXNCP)
			{
				if (StringHelper::GetDigits(Configuration::scoreFormat) == 6)
				{
					// Use Score Generations' HUD XNCP for six digit padding.
					WRITE_MEMORY(0x168E333, const char, "_low_padding");
				}
				else
				{
					// Use Score Generations' HUD XNCP for high amounts of padding.
					WRITE_MEMORY(0x168E333, const char, "_high_padding");
				}
			}

			// Execute Casino Night score instructions.
			WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x00);
		}
	}
	else
	{
	SkipScoreDraw:
		// Skip Casino Night score instructions.
		if (!HudSonicStage::IsCasino())
			WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x78);
	}
}

HOOK(bool, __cdecl, IsPerfectBonus, 0x10B8A90)
{
	if (!StateHooks::isResultsHooked)
		return originalIsPerfectBonus();

	switch (Configuration::perfectBonus)
	{
		case Configuration::PerfectBonusType::Disabled:
			return false;

		case Configuration::PerfectBonusType::OnlyForA:
		{
			// Give perfect bonus only for A rank.
			if (ResultListener::resultDescription.rank == 3)
				return originalIsPerfectBonus() ? true : false;

			return false;
		}

		case Configuration::PerfectBonusType::Enabled:
			return originalIsPerfectBonus();
	}
}

HOOK(int*, __cdecl, MsgChangeResultState, 0x587C40, void* a1, int* a2, int* rank, int* a4)
{
	FUNCTION_PTR(bool, __cdecl, IsPerfectBonus, 0x10B8A90);

	// Set correct rank animation if there's no perfect bonus.
	if (!IsPerfectBonus())
		*rank = ResultListener::resultDescription.rank;

	return originalMsgChangeResultState(a1, a2, rank, a4);
}

HOOK(int, __fastcall, MsgRestartStage, 0xE76810, int* thisDeclaration, void* edx, int* message)
{
	ScoreListener::Reset
	(
		Configuration::restoreLastCheckpointScore &&		 // Check if last checkpoint score should be used.
		BlueBlurCommon::HasFlag(CONTEXT->eStateFlag_Dead) && // Check if the player is currently dead.
		StatisticsListener::totals.totalPointMarkers > 0	 // Check if the total passed point markers is at least 1.
	);

	OnLoad();

	return originalMsgRestartStage(thisDeclaration, edx, message);
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void GameOver_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x58477C;

	__asm
	{
		call [interruptAddress]

		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void Exit_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6AE910;
	static void* returnAddress = (void*)0x42AD76;

	__asm
	{
		call [interruptAddress]

		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ResultsCalculate_MidAsmHook()
{
	static void* interruptAddress = (void*)0x10B3DB0;
	static void* returnAddress = (void*)0xD5A191;

	__asm
	{
		cmp StateHooks::isResultsHooked, 0
		jnz Hooked

		// Call original results function.
		call [interruptAddress]
		jmp Exit

	Hooked:
		// Gather the results.
		call ResultListener::Result

		// Load descriptors for results.
		lea eax, ResultListener::resultDescription

	Exit:
		jmp [returnAddress]
	}
}

#pragma endregion

void StateHooks::Install()
{
	// Install hook to set perfect bonus.
	INSTALL_HOOK(IsPerfectBonus);

	// Install hook to push the modified rank to MsgChangeResultState.
	INSTALL_HOOK(MsgChangeResultState);

	// Install hook to update during restart.
	INSTALL_HOOK(MsgRestartStage);

	// Reset statistics upon exiting.
	WRITE_JUMP(0x584777, &GameOver_MidAsmHook);
	WRITE_JUMP(0x42AD71, &Exit_MidAsmHook);

	// Calculate results with local statistics.
	WRITE_JUMP(0xD5A18C, &ResultsCalculate_MidAsmHook);
}