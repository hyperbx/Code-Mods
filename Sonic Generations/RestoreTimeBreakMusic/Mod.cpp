float timeBreakTimer = 8.0f;

FUNCTION_PTR(unsigned int, __stdcall, PlayAudioFromCueName, 0xD62440, int* gameDocument, Hedgehog::Base::CSharedString& cueName, float fadeInTime);

void PlayTimeBreakMusic()
{
	Hedgehog::Base::CSharedString timeBreak = Hedgehog::Base::CSharedString("Time_Break");
	PlayAudioFromCueName(*(int**)0x1E0BE5C, timeBreak, 0.0);
}

void PlayStageMusic()
{
	Hedgehog::Base::CSharedString timeBreak = Hedgehog::Base::CSharedString("Planet_Wisp_Classic");
	PlayAudioFromCueName(*(int**)0x1E0BE5C, timeBreak, 0.0);
}

__declspec(naked) void TimeBreakBegin_MidAsmHook()
{
	static void* interruptAddress = (void*)0x76AD90;
	static void* returnAddress = (void*)0x111B042;

	__asm
	{
		call [interruptAddress]

		call [PlayTimeBreakMusic]

		jmp [returnAddress]
	}
}

__declspec(naked) void TimeBreakEnd_MidAsmHook()
{
	static void* interruptAddress = (void*)0x65FBE0;
	static void* returnAddress = (void*)0x111AE26;

	__asm
	{
		call [interruptAddress]

		call [PlayStageMusic]

		jmp [returnAddress]
	}
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Play Time Break music upon activation.
	WRITE_JUMP(0x111B03D, &TimeBreakBegin_MidAsmHook);

	// Restore original stage music upon ending.
	WRITE_JUMP(0x111AE21, &TimeBreakEnd_MidAsmHook);

	// Increase Time Break timer to fit the length of the soundtrack.
	WRITE_MEMORY(0x111B044, float*, &timeBreakTimer);
}