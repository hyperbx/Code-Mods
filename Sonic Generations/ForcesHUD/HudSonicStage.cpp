bool isTrick = false;

#pragma region ----- Hooked Functions -----

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="buffer">Character buffer from EDX.</param>
/// <param name="rings">Ring count from ESI.</param>
char* __fastcall HideZeroesInRingDisplay(char* buffer, unsigned int rings)
{
	// Clamps the rings based on the selected difficulty.
	if (Configuration::difficultyType == 0)
	{
		if (rings >= 100)
			rings = 100;
	}
	else
	{
		if (rings >= 999)
			rings = 999;
	}

	// Change string format justification.
	sprintf(buffer, "%3d", rings);

	if (Configuration::ringFormatter)
	{
		char hidden = '-';

		if (rings < 10)
		{
			// The first two leading nulls will be replaced.
			buffer[0] = hidden;
			buffer[1] = hidden;
		}
		else if (rings < 100)
		{
			// The first single null will be replaced.
			buffer[0] = hidden;
		}
	}

	return buffer;
}

/// <summary>
/// HUD update hook to perform actions on every frame.
/// </summary>
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, void* pUpdateInfo)
{
	// Call the homing update function using the current player context if we're Modern Sonic.
	if (Configuration::alwaysActiveReticle && !BlueBlurCommon::IsClassic())
	{
		FUNCTION_PTR(int, __stdcall, HomingUpdate, 0xE5FF10, Sonic::Player::CPlayerSpeedContext* thisDeclaration);
		HomingUpdate(CONTEXT);
	}

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void MillisecondsFormatter_MidAsmHook()
{
	static void* returnAddress = (void*)0x1098E76;

	__asm
	{
		mov ecx, edx
		mov edx, esi
		call HideZeroesInRingDisplay
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void FinalBossRingFormatter_MidAsmHook()
{
	static void* returnAddress = (void*)0x122824A;

	__asm
	{
		mov ebx, ecx
		mov ecx, edx
		push ebx
		pop edx
		call HideZeroesInRingDisplay
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void Trick_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6644C0;
	static void* returnAddress = (void*)0xE4B6EC;

	__asm
	{
		call [interruptAddress]

		mov isTrick, 1

		jmp [returnAddress]
	}
}

__declspec(naked) void TrickFinish_MidAsmHook()
{
	static void* returnAddress = (void*)0xE4BC44;

	__asm
	{
		mov [ebp + 60h], 0

		mov isTrick, 0

		jmp [returnAddress]
	}
}

#pragma endregion

void HudSonicStage::Install()
{
	// Jump to ring formatters to fix leading zeroes.
	WRITE_JUMP(0x1098E71, &MillisecondsFormatter_MidAsmHook);
	WRITE_JUMP(0x1228245, &FinalBossRingFormatter_MidAsmHook);

	// Jump to trick hooks to intercept the chaos energy hook.
	WRITE_JUMP(0xE4B6E7, &Trick_MidAsmHook);
	WRITE_JUMP(0xE4BC3D, &TrickFinish_MidAsmHook);

	// Install HUD update hook.
	INSTALL_HOOK(CHudSonicStageUpdate);
}