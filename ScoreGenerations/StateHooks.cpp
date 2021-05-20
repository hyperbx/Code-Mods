// Declare class variables.
const char* StateHooks::stageID = (const char*)0x1E774D4;

void OnLoad()
{
	// Get the ranks for the current stage.
	ScoreListener::rankTable = ScoreListener::RankTable::GetRanks(StateHooks::stageID, -1);

	// Disable the score counter for forbidden stages.
	if (HudSonicStage::IsStageForbidden())
	{
		// Skip Casino Night score instructions.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x78);
	}
	else
	{
		// Execute Casino Night score instructions.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x00);
	}
}

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void LoadingMidAsmHook()
{
	static void* interruptAddress = (void*)0x65FCC0;
	static void* returnAddress = (void*)0x448E98;

	__asm
	{
		// Perform actions on the loading screen.
		call OnLoad

		call[interruptAddress]

		jmp[returnAddress]
	}
}

__declspec(naked) void ClassicSonicPrepareRestartMidAsmHook()
{
	static void* interruptAddress = (void*)0xDD6740;
	static void* returnAddress = (void*)0xDEB841;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ModernSonicPrepareRestartMidAsmHook()
{
	static void* interruptAddress = (void*)0xE14350;
	static void* returnAddress = (void*)0xE28C7B;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ExitMidAsmHook()
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

__declspec(naked) void ResultsCalculateMidAsmHook()
{
	static void* returnAddress = (void*)0x10B4044;

	// Calculate bonuses.
	ScoreListener::Bonus();

	__asm
	{
		// Move locally calculated score to final results registers.
		mov eax, ScoreListener::score
		mov [ebx], eax
		movss xmm0, ScoreListener::score

		jmp [returnAddress]
	}

	// Reset statistics.
	ScoreListener::Reset();
}

__declspec(naked) void ResultsEndMidAsmHook()
{
	static void* interruptAddress = (void*)0x773250;
	static void* returnAddress = (void*)0xCFAEE7;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

#pragma endregion

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void StateHooks::Install()
{
	// Update local loading function.
	WRITE_JUMP(0x448E93, &LoadingMidAsmHook)

	// Reset statistics upon restarting.
	WRITE_JUMP(0xDEB83C, &ClassicSonicPrepareRestartMidAsmHook);
	WRITE_JUMP(0xE28C76, &ModernSonicPrepareRestartMidAsmHook);

	// Reset statistics upon exiting.
	WRITE_JUMP(0x42AD71, &ExitMidAsmHook);

	// Calculate results screen with local score.
	WRITE_JUMP(0x10B403B, &ResultsCalculateMidAsmHook);

	// Reset statistics upon results finishing.
	WRITE_JUMP(0xCFAEE2, &ResultsEndMidAsmHook);
}