int millisecondsDigit3 = 0;

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

/// <summary>
/// Fade in transition hook to correct transition times.
/// </summary>
HOOK(float*, __fastcall, MsgFadeIn, 0x10CEC90, void* This, void* Edx, float* a2)
{
	uint8_t* color = (uint8_t*)((uint32_t)a2 + 21);
	if (color[0] == 0 && color[1] == 0 && color[2] == 0)
	{
		a2[6] = ((float*)This)[24]; // start alpha
		if (a2[6] > 0.0f)
		{
			a2[4] = 0.2f; // transition time
		}
	}

	return originalMsgFadeIn(This, Edx, a2);
}

/// <summary>
/// Fade out transition hook to correct transition times.
/// </summary>
HOOK(float*, __fastcall, MsgFadeOut, 0x10CEDB0, void* This, void* Edx, float* a2)
{
	uint8_t* color = (uint8_t*)((uint32_t)a2 + 21);
	if (color[0] == 0 && color[1] == 0 && color[2] == 0)
	{
		a2[4] = 0.0f; // transition time
		a2[6] = 1.0f; // start alpha
	}

	return originalMsgFadeOut(This, Edx, a2);
}

/// <summary>
/// Hook to lock player control whilst the fade out transition is occurring.
/// </summary>
HOOK(void, __stdcall, FadeOutCountDec, 0x10CE9A0)
{
	originalFadeOutCountDec();

	(*(uint32_t**)0x1E66B40)[2] = 0;
}

/// <summary>
/// HUD update hook to perform actions on every frame.
/// </summary>
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, void* pUpdateInfo)
{
	// Always clamp boost to 100%.
	*PlayerListener::GetBoost() = clamp(*PlayerListener::GetBoost(), 0.0f, 100.0f);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
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

	// Install HUD update hook.
	INSTALL_HOOK(CHudSonicStageUpdate);

	// Install hooks to improve fading transitions.
	INSTALL_HOOK(MsgFadeIn);
	INSTALL_HOOK(MsgFadeOut);
	INSTALL_HOOK(FadeOutCountDec);
}