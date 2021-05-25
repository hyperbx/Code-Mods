// Declare class variables.
const char* StateHooks::stageID = (const char*)0x1E774D4;

#pragma region ----- Hooked Functions -----

void OnLoad()
{
	// Get the ranks for the current stage.
	ScoreListener::rankTable = ScoreListener::RankTable::GetRanks();

	// Disable the score counter for forbidden stages.
	if (HudSonicStage::IsStageForbidden())
	{
		// Skip Casino Night score instructions.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x78);

		// Disable results hooks.
		StateHooks::HookResults(false);
	}
	else
	{
		// Execute Casino Night score instructions.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x00);

		// Hook to results for local score.
		StateHooks::HookResults(true);
	}
}

int CalculateRank()
{
	if (ScoreListener::score < ScoreListener::rankTable.S)
	{
		if (ScoreListener::score < ScoreListener::rankTable.A)
		{
			if (ScoreListener::score < ScoreListener::rankTable.D)
			{
				return 0; // D rank
			}
			else
			{
				return 1; // C rank
			}
		}
		else
		{
			return 2; // B rank
		}
	}
	else
	{
		return 3; // A rank
	}
}

#pragma endregion

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

__declspec(naked) void ResultsScoreCalculateMidAsmHook()
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
}

__declspec(naked) void ResultsRankCalculateMidAsmHook()
{
	static void* returnAddress = (void*)0x10B410A;

	__asm
	{
		//mov [ebx + 4], CalculateRank

		jmp [returnAddress]
	}
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
/// Hooks to the results screen for calculating the local score.
/// </summary>
/// <param name="enabled">Enables/disables the hooks.</param>
void StateHooks::HookResults(bool enabled)
{
	if (enabled)
	{
		// Calculate results with local statistics.
		WRITE_JUMP(0x10B403B, &ResultsScoreCalculateMidAsmHook);
		WRITE_JUMP(0x10B40B1, &ResultsRankCalculateMidAsmHook);
	}
	else
	{
		// Restore default results calculation.
		WRITE_MEMORY(0x10B403B, uint8_t, 0xF3, 0x0F, 0x2C, 0xC0, 0x89);
		WRITE_MEMORY(0x10B40B1, uint8_t, 0x7C, 0x11, 0xF3, 0x0F, 0x10);
	}
}

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

	// Reset statistics upon results finishing.
	WRITE_JUMP(0xCFAEE2, &ResultsEndMidAsmHook);
}