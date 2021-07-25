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

	// Patch "Boost Particles go to Sonic"
	WRITE_MEMORY(0x10967B4, uint8_t, 0xA1, 0xF0, 0xE2, 0xE5, 0x01, 0x85, 0xC0, 0x0F, 0x84, 0x27, 0x01, 0x00, 0x00, 0x8B, 0x80, 0x10);
	WRITE_MEMORY(0x10967C4, uint8_t, 0x01, 0x00, 0x00, 0x8B, 0x80, 0xAC, 0x00, 0x00, 0x00, 0x85, 0xC0, 0x0F, 0x84, 0x13, 0x01, 0x00);
	WRITE_MEMORY(0x10967D4, uint8_t, 0x00, 0x8B, 0x40, 0x10, 0xF3, 0x0F, 0x10, 0x50, 0x74, 0xBA, 0x00, 0x00, 0x00, 0x3F, 0x66, 0x0F);
	WRITE_MEMORY(0x10967E4, uint8_t, 0x6E, 0xC2, 0xF3, 0x0F, 0x58, 0xD0, 0xF3, 0x0F, 0x10, 0x40, 0x70, 0xF3, 0x0F, 0x10, 0x48, 0x78);
	WRITE_MEMORY(0x10967F4, uint8_t, 0x8B, 0x55, 0x08, 0xF3, 0x0F, 0x11, 0x42, 0x10, 0xF3, 0x0F, 0x11, 0x52, 0x14, 0xF3, 0x0F, 0x11);
	WRITE_MEMORY(0x1096804, uint8_t, 0x4A, 0x18, 0xE9, 0xDD, 0x00, 0x00, 0x00);
}