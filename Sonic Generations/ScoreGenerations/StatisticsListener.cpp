Statistics::Totals StatisticsListener::totals;

#pragma region ----- Hooked Functions -----

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="rings">Ring count from input register.</param>
void __fastcall UpdateRingCount(int rings)
{
	// Update current ring count.
	StatisticsListener::totals.ringCount = rings;

	// Update total ring count.
	if (rings > StatisticsListener::totals.totalRingCount)
	{
		StatisticsListener::totals.totalRingCount = rings;
	}
}

/// <summary>
/// Updates the elapsed time.
/// </summary>
/// <param name="minutes">Minutes from EDI.</param>
/// <param name="seconds">Seconds from EAX.</param>
void __fastcall UpdateElapsedTime(int minutes, int seconds)
{
	// Update real-time minutes and seconds.
	StatisticsListener::totals.minutes = minutes;
	StatisticsListener::totals.seconds = seconds;
}

/// <summary>
/// Updates current ring count.
/// </summary>
HOOK(void, __fastcall, CHudSonicStageUpdate_RingCount, 0x1098A50, void* thisDeclaration, void* edx, float* pUpdateInfo)
{
	if (CONTEXT != nullptr)
		UpdateRingCount(CONTEXT->m_RingCount);

	originalCHudSonicStageUpdate_RingCount(thisDeclaration, edx, pUpdateInfo);
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void RingFormatter_MidAsmHook()
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

__declspec(naked) void FinalBossRingFormatter_MidAsmHook()
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


__declspec(naked) void TimeFormatter_MidAsmHook()
{
	static void* returnAddress = (void*)0x1098D47;

	__asm
	{
		pop ecx
		pop edx
		push edx
		push ecx
		call UpdateElapsedTime
		mov edx, eax

		lea ecx, [esp + 94h]
		jmp [returnAddress]
	}
}

#pragma endregion

int StatisticsListener::GetElapsedTime()
{
	return (StatisticsListener::totals.minutes * 60) + StatisticsListener::totals.seconds;
}

void StatisticsListener::Install()
{
	// Set score string format.
	WRITE_MEMORY(0x1095D7D, const char*, Configuration::scoreFormat.c_str());

	// Store elapsed time locally for the time bonus.
	WRITE_JUMP(0x1098D40, &TimeFormatter_MidAsmHook);

	// Update the ring count.
	INSTALL_HOOK(CHudSonicStageUpdate_RingCount);
	WRITE_JUMP(0x12281B8, &FinalBossRingFormatter_MidAsmHook);
}