const char* StateHooks::stageID = (const char*)0x1E774D4;
bool StateHooks::isResultsHooked = false;

#pragma region ----- Hooked Functions -----

void OnLoad()
{
	// Reset statistics.
	ScoreListener::Reset();

	// Disable the score counter for forbidden stages.
	if (HudSonicStage::IsStageForbidden())
	{
		// Use Sonic Generations' HUD XNCP.
		if (!Configuration::customXNCP)
			WRITE_MEMORY(0x168E333, uint8_t, "_default\0");

		// Skip Casino Night score instructions.
		if (!HudSonicStage::IsCasino())
			WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x78);

		// Disable results hooks.
		StateHooks::HookResults(false);
	}
	else
	{
		if (!Configuration::customXNCP)
		{
			if (StringHelper::GetDigits(Configuration::scoreFormat) == 6)
			{
				// Use Score Generations' HUD XNCP for six digit padding.
				WRITE_MEMORY(0x168E333, uint8_t, "_low_padding\0");
			}
			else
			{
				// Use Score Generations' HUD XNCP for high amounts of padding.
				WRITE_MEMORY(0x168E333, uint8_t, "_high_padding\0");
			}
		}

		// Execute Casino Night score instructions.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x00);

		// Hook to results for local score.
		StateHooks::HookResults(true);
	}
}

HOOK(bool, __cdecl, IsPerfectBonus, 0x10B8A90)
{
	if (!StateHooks::isResultsHooked)
		return originalIsPerfectBonus();

	switch (Configuration::perfectBonus)
	{
		case 0:
			return false;

		case 1:
		{
			// Give perfect bonus only for A rank.
			if (ResultListener::resultDescription.rank == 3)
				return originalIsPerfectBonus() ? true : false;

			return false;
		}

		case 2:
			return originalIsPerfectBonus();
	}
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void Loading_MidAsmHook()
{
	static void* interruptAddress = (void*)0x65FCC0;
	static void* returnAddress = (void*)0x448E98;

	__asm
	{
		// Perform actions on the loading screen.
		call OnLoad

		call [interruptAddress]

		jmp [returnAddress]
	}
}

__declspec(naked) void GameOver_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x58477C;

	// Reset the last checkpoint score.
	ScoreListener::lastCheckpointScore = 0;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
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

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ResultsCalculate_MidAsmHook()
{
	static void* returnAddress = (void*)0xD5A191;

	__asm
	{
		// Gather the results.
		call ResultListener::Result

		// Reset statistics.
		call ScoreListener::Reset

		// Load descriptors for results.
		lea eax, ResultListener::resultDescription

		jmp [returnAddress]
	}
}

#pragma endregion

void StateHooks::HookResults(bool enabled)
{
	if (enabled)
	{
		// Calculate results with local statistics.
		WRITE_JUMP(0xD5A18C, &ResultsCalculate_MidAsmHook);

		isResultsHooked = true;
	}
	else
	{
		// Restore default results calculation.
		WRITE_MEMORY(0xD5A18C, uint8_t, 0xE8, 0x1F, 0x9C, 0x35, 0x00);

		isResultsHooked = false;
	}
}

void StateHooks::Install()
{
	// Update local loading function.
	WRITE_JUMP(0x448E93, &Loading_MidAsmHook);

	// Reset statistics upon exiting.
	WRITE_JUMP(0x584777, &GameOver_MidAsmHook);
	WRITE_JUMP(0x42AD71, &Exit_MidAsmHook);

	// Install hook to set perfect bonus.
	INSTALL_HOOK(IsPerfectBonus);
}