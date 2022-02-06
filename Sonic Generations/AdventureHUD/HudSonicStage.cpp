float currentTime;

__declspec(naked) void AddTime_MidAsmHook()
{
	static void* returnAddress = (void*)0xD02E50;

	__asm
	{
		movss xmm1, dword ptr[edx + 184h]
		movss [currentTime], xmm1

		jmp [returnAddress]
	}
}

/// <summary>
/// Replaces the lap time with the current time.
/// </summary>
/// <param name="buffer">Character buffer from EDX.</param>
char* __fastcall SetLapTimeToCurrentTime(char* buffer)
{
	int minute = (int)(currentTime / 60.0f);
	int seconds = (int)(currentTime - 60.0f * (float)minute);

	sprintf(buffer, "%02d:%02d", minute, seconds);

	return buffer;
}

__declspec(naked) void SetLapTime_MidAsmHook()
{
	static void* returnAddress = (void*)0x1097957;

	__asm
	{
		mov ecx, edx
		call SetLapTimeToCurrentTime
		mov edx, eax

		jmp [returnAddress]
	}
}

void HudSonicStage::Install()
{
	// Jump to timer setup to get the current time.
	WRITE_JUMP(0xD02E48, &AddTime_MidAsmHook);

	// Jump to lap time setup to set the string format.
	WRITE_JUMP(0x1097952, &SetLapTime_MidAsmHook);

	// Always displays the lap time, regardless of record.
	WRITE_NOP(0x10976EF, 6);

	// Always use green lap time display.
	WRITE_NOP(0x109793F, 2);

	// Disable the boost gauge if requested.
	if (Configuration::disableGauge)
		WRITE_NOP(0x109B8DD, 2);
}