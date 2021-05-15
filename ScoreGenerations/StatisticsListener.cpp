// Declare class variables.
unsigned int StatisticsListener::totalRingCount = 0;
unsigned int StatisticsListener::totalVelocity = 0;
unsigned int StatisticsListener::elapsedTime = 0;
unsigned int StatisticsListener::ringCount = 0;

#pragma region ----- Hooked Functions -----

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="rings">Ring count from input register.</param>
void __fastcall UpdateRingCount(unsigned int rings)
{
	// Update current ring count.
	StatisticsListener::ringCount = rings;

	// Update total ring count.
	if (rings > StatisticsListener::totalRingCount)
	{
		StatisticsListener::totalRingCount = rings;
	}
}

/// <summary>
/// Updates the elapsed time.
/// </summary>
/// <param name="minutes">Minutes from EDI.</param>
/// <param name="seconds">Seconds from EAX.</param>
void __fastcall UpdateElapsedTime(unsigned int minutes, unsigned int seconds)
{
	// Update real-time elapsed time.
	StatisticsListener::elapsedTime = (minutes * 60) + seconds;
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----
__declspec(naked) void DefaultRingFormatterMidAsmHook()
{
	static void* returnAddress = (void*)0x1098E59;

	__asm
	{
		// Get ring count from registers.
		mov ecx, [esp + 100h + 0xFFFFFF30]
		mov esi, [ecx + 10h]

		mov ecx, esi
		call UpdateRingCount
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void FinalBossRingFormatterMidAsmHook()
{
	static void* interruptAddress = (void*)0x41CAA0;
	static void* returnAddress = (void*)0x12281C5;

	__asm
	{
		call [interruptAddress]

		// Get ring count from registers.
		mov eax, [esp + 50h + 0xFFFFFFD8]
		mov [esp + 50h + 0xFFFFFFC0], eax

		mov ecx, eax
		call UpdateRingCount
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void TimeFormatterMidAsmHook()
{
	static void* interruptAddress = (void*)0xA6901D;
	static void* returnAddress = (void*)0x1098D52;

	__asm
	{
		call[interruptAddress]

		mov ecx, eax
		mov edx, edi
		call UpdateElapsedTime
		mov edx, eax

		jmp[returnAddress]
	}
}
#pragma endregion

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void StatisticsListener::Install()
{
	// Set score string format.
	WRITE_MEMORY(0x1095D7D, char*, Configuration::scoreFormat.c_str());

	// Store elapsed time locally for the time bonus.
	WRITE_JUMP(0x1098D4D, &TimeFormatterMidAsmHook);

	// Update the ring count.
	WRITE_JUMP(0x1098E4C, &DefaultRingFormatterMidAsmHook);
	WRITE_JUMP(0x12281B8, &FinalBossRingFormatterMidAsmHook);
}