int millisecondsDigit3 = 0;

HOOK(float*, __fastcall, MsgFadeIn, 0x10CEC90, void* This, void* Edx, float* a2)
{
	a2[6] = ((float*)This)[24]; // start alpha

	if (a2[6] > 0.0f)
	{
		a2[4] = 0.2f; // transition time
	}

	return originalMsgFadeIn(This, Edx, a2);
}

HOOK(float*, __fastcall, MsgFadeOut, 0x10CEDB0, void* This, void* Edx, float* a2)
{
	a2[4] = 0.0f; // transition time
	a2[6] = 1.0f; // start alpha

	return originalMsgFadeOut(This, Edx, a2);
}

HOOK(void, __stdcall, FadeOutCountDec, 0x10CE9A0)
{
	originalFadeOutCountDec();

	(*(uint32_t**)0x1E66B40)[2] = 0;
}

/// <summary>
/// Calculates a new set of milliseconds so it's compatible with three digits.
/// </summary>
/// <param name="buffer">Character buffer from EDX.</param>
/// <param name="milliseconds">Milliseconds from ESI.</param>
char* __fastcall CreateTripleDigits(char* buffer, int milliseconds)
{
	// Write zeroes to buffer.
	sprintf(buffer, "%03d", 0);

	// Reset third digit.
	if (millisecondsDigit3 > 9)
		millisecondsDigit3 = 0;

	// Write new milliseconds to buffer.
	if (milliseconds != 0)
		sprintf(buffer, "%03d", (milliseconds * 10) + millisecondsDigit3++);

	return buffer;
}

__declspec(naked) void MillisecondsFormatter_MidAsmHook()
{
	static void* returnAddress = (void*)0x1098D7F;

	__asm
	{
		mov ecx, eax
		mov edx, esi
		call CreateTripleDigits
		mov edx, eax

		jmp [returnAddress]
	}
}

void HudSonicStage::Install()
{
	// Jump to milliseconds formatter to create triple digits.
	WRITE_JUMP(0x1098D7A, &MillisecondsFormatter_MidAsmHook);

	/**** brianuuu hooks ****/

	// Install hook to lock player control during loading transitions.
	INSTALL_HOOK(FadeOutCountDec);

	// Install hooks to fix fading transitions.
	INSTALL_HOOK(MsgFadeIn);
	INSTALL_HOOK(MsgFadeOut);
}