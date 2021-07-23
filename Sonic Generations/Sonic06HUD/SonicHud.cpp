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

	// Change string format and write new milliseconds.
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

void SonicHud::Install()
{
	// Jump to milliseconds formatter to create triple digits.
	WRITE_JUMP(0x1098D7A, &MillisecondsFormatter_MidAsmHook);
}