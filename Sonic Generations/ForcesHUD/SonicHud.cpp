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
/// Rewards the player with chaos energy.
/// </summary>
void RewardChaosEnergy()
{
	if ((*PlayerListener::GetBoost() + 10) < 100.0f || isTrick)
	{
		/* Immediately add chaos energy to the boost gauge when
		   enemies are destroyed. The default function would only add
		   boost in small amounts and it was a bit jarring without the particles.

		   5 points are added for tricks and 10 points are added for enemies;
		   both amounts are rough guesses on how much the game gives by default. */
		if (isTrick)
		{
			*PlayerListener::GetBoost() += 5;
		}
		else if (!(*PlayerListener::GetBoost() >= 100.0f))
		{
			*PlayerListener::GetBoost() = clamp((int)(*PlayerListener::GetBoost() + 10), 0, 100);
		}
	}
}

/// <summary>
/// Homing update hook for updating on every frame.
/// </summary>
HOOK(int, __stdcall, HomingUpdate, 0xE5FF10, int thisDeclaration)
{
	return originalHomingUpdate(thisDeclaration);
}

/// <summary>
/// HUD update hook to perform actions on every frame.
/// </summary>
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, void* pUpdateInfo)
{
	// Call the homing update function using the current player context if we're Modern Sonic.
	if (Configuration::alwaysActiveReticle && !PlayerListener::IsClassic())
		originalHomingUpdate(PlayerListener::GetContext());

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void DefaultRingFormatterMidAsmHook()
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

__declspec(naked) void FinalBossRingFormatterMidAsmHook()
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

__declspec(naked) void ChaosEnergyMidAsmHook()
{
	static void* interruptAddress = (void*)0x65FBE0;
	static void* returnAddress = (void*)0x11246A9;

	__asm
	{
		call [interruptAddress]

		call RewardChaosEnergy
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void TrickMidAsmHook()
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

__declspec(naked) void TrickFinishMidAsmHook()
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

void SonicHud::Install()
{
	// Jump to ring formatters to fix leading zeroes.
	WRITE_JUMP(0x1098E71, &DefaultRingFormatterMidAsmHook);
	WRITE_JUMP(0x1228245, &FinalBossRingFormatterMidAsmHook);

	// Jump to chaos energy hook.
	WRITE_JUMP(0x11246A4, &ChaosEnergyMidAsmHook);

	// Jump to trick hooks to intercept the chaos energy hook.
	WRITE_JUMP(0xE4B6E7, &TrickMidAsmHook);
	WRITE_JUMP(0xE4BC3D, &TrickFinishMidAsmHook);

	// Install HUD update hook.
	INSTALL_HOOK(CHudSonicStageUpdate);
}