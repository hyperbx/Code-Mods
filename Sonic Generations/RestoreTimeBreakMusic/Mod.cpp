float timeBreakTimer = 8.0f;

void PlayTimeBreakMusic()
{
	PlayMusic("Time_Break", 0.0);
}

void StopTimeBreakMusic()
{
	StopMusic("Time_Break", 0.0);
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

		call [StopTimeBreakMusic]

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