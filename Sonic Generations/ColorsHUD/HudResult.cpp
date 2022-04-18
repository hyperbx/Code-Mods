// https://github.com/ActualMandM/DllMods/blob/master/Source/CustomizableResultsMusic/Mod.cpp#L163
__declspec(naked) void ResultTimer_MidAsmHook()
{
	static void* returnAddress = (void*)0x00CFD566;
	static double timer = 8.56;

	__asm
	{
		push eax
		lea eax, timer
		movsd xmm1, [eax]
		pop eax
		jmp [returnAddress]
	}
}

// https://github.com/brianuuu/DllMods/blob/master/Source/Sonic06HUD/ResultUI.cpp#L38
HOOK(int, __fastcall, CStateGoalFadeBefore, 0xCFE080, uint32_t* thisDeclaration)
{
	/* Adjust the results camera position so Sonic appears to
	   be sitting on top of the bottom UI element like Colours. */

	WRITE_MEMORY(0x1A48C7C, float, -0.2f);	 // X Position
	WRITE_MEMORY(0x1A48C80, float, 1.25f);	 // Y Position
	WRITE_MEMORY(0x1A48C84, float, 9);		 // Z Position
	WRITE_MEMORY(0x1A48C88, float, 2);		 // X Rotation
	WRITE_MEMORY(0x1A48C8C, float, -10.25f); // Y Rotation

	return originalCStateGoalFadeBefore(thisDeclaration);
}

void HudResult::Install()
{
	// Do not modify the results timer if Customizable Results Music is enabled.
	if (GetModuleHandle(TEXT("CustomizableResultsMusic.dll")) == nullptr)
		WRITE_JUMP(0xCFD55E, &ResultTimer_MidAsmHook);

	INSTALL_HOOK(CStateGoalFadeBefore);
}