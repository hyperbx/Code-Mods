// https://github.com/ActualMandM/DllMods/blob/master/Source/CustomizableResultsMusic/Mod.cpp#L163
__declspec(naked) void ResultTimer_MidAsmHook()
{
	static void* returnAddress = (void*)0x00CFD566;
	static double timer = 8.01;

	__asm
	{
		push eax
		lea eax, timer
		movsd xmm1, [eax]
		pop eax
		jmp [returnAddress]
	}
}

void HudResult::Install()
{
	// Do not modify the results timer if Customizable Results Music is enabled.
	if (GetModuleHandle(TEXT("CustomizableResultsMusic.dll")) == nullptr)
		WRITE_JUMP(0xCFD55E, &ResultTimer_MidAsmHook);
}