/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="buffer">Character buffer from EDX.</param>
/// <param name="rings">Ring count from ESI.</param>
char* __fastcall HideZeroesInRingDisplay(char* buffer, unsigned int rings)
{
	// Change string format justification.
	sprintf(buffer, "%3d", rings);

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

	return buffer;
}

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="buffer">Character buffer from EDX.</param>
char* __fastcall HideZeroesInScoreDisplay(char* buffer)
{
	int score = ScoreGenerationsAPI::GetScore();

	// Change string format justification.
	sprintf(buffer, "%6d", score);

	if (score < 100000)
	{
		// Evil ternary condition...
		for (int i = 0; i < (score < 10 ? 5 : score < 100 ? 4 : score < 1000 ? 3 : score < 10000 ? 2 : 1); i++)
			buffer[i] = '-';
	}

	return buffer;
}

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

__declspec(naked) void ScoreFormatter_MidAsmHook()
{
	static void* returnAddress = (void*)0x1095D87;

	__asm
	{
		mov ecx, eax
		call HideZeroesInScoreDisplay
		mov edx, eax

		jmp[returnAddress]
	}
}

void HudSonicStage::Install()
{
	// Jump to formatters to fix leading zeroes.
	WRITE_JUMP(0x1098E71, &MillisecondsFormatter_MidAsmHook);
	WRITE_JUMP(0x1228245, &FinalBossRingFormatter_MidAsmHook);
	WRITE_JUMP(0x1095D82, &ScoreFormatter_MidAsmHook);
}