// Declare class variables.
const char* StateHooks::stageID = (const char*)0x1E774D4;

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

__declspec(naked) void ResultsEndMidAsmHook()
{
	static void* interruptAddress = (void*)0x773250;
	static void* returnAddress = (void*)0xCFAEE7;

	__asm
	{
		call[interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp[returnAddress]
	}
}

__declspec(naked) void ResultsCalculateMidAsmHook()
{
	static void* returnAddress = (void*)0x10B41A5;

	// Calculate bonuses.
	ScoreListener::Bonus();

	__asm
	{
		// Move locally calculated score to final results registers.
		cvtsi2ss xmm0, ScoreListener::score
		cvtss2sd xmm1, xmm0

		jmp [returnAddress]
	}

	// Reset statistics.
	ScoreListener::Reset();
}

void OnLoad()
{
	// Disable the score counter for Shadow's boss fight.
	if (StringHelper::Compare(StateHooks::stageID, "bsd"))
	{
		// Jump over Casino Night score initialiser.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x78);
	}
	else
	{
		// Restore Casino Night score instructions.
		WRITE_MEMORY(0x109C1DA, uint8_t, 0xEB, 0x00);
	}
}

__declspec(naked) void LoadingMidAsmHook()
{
	static void* interruptAddress = (void*)0x65FCC0;
	static void* returnAddress = (void*)0x448E98;

	__asm
	{
		call OnLoad

		call [interruptAddress]

		jmp [returnAddress]
	}
}

FUNCTION_PTR(void, __thiscall, ProcessMsgSetPinballHud, 0x1095D40, void* thisDeclaration, const StateHooks::MsgSetPinballHud& msgSetPinballHud);

HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, void* pUpdateInfo)
{
	StateHooks::MsgSetPinballHud msgSetPinballHud{};
	msgSetPinballHud.flags = 1;
	msgSetPinballHud.score = ScoreListener::score;

	// Makes sure the current stage isn't Casino Night before sending the message.
	if (!StringHelper::Compare(StateHooks::stageID, "cnz100"))
		ProcessMsgSetPinballHud(thisDeclaration, msgSetPinballHud);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void StateHooks::Install()
{
	WRITE_JUMP(0x448E93, &LoadingMidAsmHook)

	WRITE_JUMP(0xDEB83C, &ClassicSonicPrepareRestartMidAsmHook);
	WRITE_JUMP(0xE28C76, &ModernSonicPrepareRestartMidAsmHook);

	WRITE_JUMP(0x42AD71, &ExitMidAsmHook);

	// WRITE_JUMP(0x10B419D, &ResultsCalculateMidAsmHook);
	WRITE_JUMP(0xCFAEE2, &ResultsEndMidAsmHook);

	// Install hook to update the score counter.
	INSTALL_HOOK(CHudSonicStageUpdate);
}