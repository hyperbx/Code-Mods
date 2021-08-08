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
			a2[4] = 0.2f; // transition time
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

__declspec(naked) void MillisecondsCalculate_MidAsmHook()
{
	static void* returnAddress = (void*)0x10B3847;

	__asm
	{
		imul edx, 3E8h
		sub ecx, edx
		jmp [returnAddress]
	}
}

void HudSonicStage::Install()
{
	// Install HUD update hook.
	INSTALL_HOOK(CHudSonicStageUpdate);

	// Install hooks to improve fading transitions.
	INSTALL_HOOK(MsgFadeIn);
	INSTALL_HOOK(MsgFadeOut);
	INSTALL_HOOK(FadeOutCountDec);

	// Calculate correct 3 digit milliseconds for stage time
	static double const secMultiplier = 1000;
	WRITE_MEMORY(0x10B37BF, double*, &secMultiplier);
	WRITE_MEMORY(0x10B37F7, uint32_t, 9162597); // 9162597/2^39 ~= 1/60000
	WRITE_MEMORY(0x10B3830, int32_t, -60000); // sec = total_sec + min * (-60000) = total_sec % 60000
	WRITE_MEMORY(0x10B3837, uint32_t, 137438954); // 137438954/2^37 ~= 1/1000
	WRITE_JUMP(0x10B3842, MillisecondsCalculate_MidAsmHook);
	WRITE_MEMORY(0x10B3823, uint32_t, 999); // maximum milliseconds
	WRITE_MEMORY(0x1098D75, uint32_t, 0x168E8E0); // %03d 

	// Other instances using sub_10B37B0
	WRITE_STRING(0x1689274, "--:--.---");
	WRITE_STRING(0x1689280, "%02d:%02d.%03d");
	WRITE_STRING(0x1689290, "--:--.---");
	WRITE_STRING(0x168929C, "%02d:%02d.%03d");
	WRITE_STRING(0x168CD0C, "99:59.999");
	WRITE_STRING(0x168CD18, "%02d:%02d.%03d");
	WRITE_STRING(0x16941C0, "%02d:%02d.%03d");
	WRITE_MEMORY(0x117BF38, uint32_t, 0x168E8E0); // %03d 
	WRITE_MEMORY(0x11CCCC2, uint32_t, 0x168E8E0); // %03d

	// Fixed default result time to 99:59.999
	WRITE_MEMORY(0x10B685B, uint32_t, 0x168CD0C);
}
