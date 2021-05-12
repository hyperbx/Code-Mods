#include "SonicHud.h"
#include "ScoreListener.h"
#include "Mod.h"
#include "StateHooks.h"

// Declare class variables.
unsigned int SonicHud::totalRingCount = 0;
unsigned int SonicHud::ringCount = 0;
unsigned int SonicHud::elapsedTime = 0;

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="buffer">Character buffer from EDX.</param>
/// <param name="rings">Ring count from ESI.</param>
char* __fastcall HideZeroesInRingDisplay(char* buffer, unsigned int rings)
{
	if (Mod::scoreDisplay)
	{
		// Update current ring count.
		SonicHud::ringCount = rings;

		// Update total ring count.
		if (rings > SonicHud::totalRingCount)
		{
			SonicHud::totalRingCount = rings;
		}
	}

	// Change string format justification.
	sprintf(buffer, Mod::ringFormatter ? "%3d" : "%03d", rings);

	if (Mod::ringFormatter)
	{
		char hidden = '-';

		if (rings < 10)
		{
			// The first two leading nulls will be replaced.
			buffer[0] = hidden;
			buffer[1] = hidden;
		}
		else if (rings < 100)
		{
			// The first single null will be replaced.
			buffer[0] = hidden;
		}
	}

	return buffer;
}

__declspec(naked) void DefaultRingFormatterMidAsmHook()
{
	static void* returnAddress = (void*)0x1098E76;

	__asm
	{
		mov ecx, edx
		mov edx, esi
		call HideZeroesInRingDisplay
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void FinalBossRingFormatterMidAsmHook()
{
	static void* returnAddress = (void*)0x122824A;

	__asm
	{
		mov ebx, ecx
		mov ecx, edx
		push ebx
		pop edx
		call HideZeroesInRingDisplay
		mov edx, eax

		jmp [returnAddress]
	}
}

/// <summary>
/// Updates the elapsed time.
/// </summary>
/// <param name="minutes">Minutes from EDI.</param>
/// <param name="seconds">Seconds from EAX.</param>
void __fastcall GetElapsedTime(unsigned int minutes, unsigned int seconds)
{
	// Update real-time elapsed time.
	SonicHud::elapsedTime = (minutes * 60) + seconds;
}

__declspec(naked) void TimeFormatterMidAsmHook()
{
	static void* interruptAddress = (void*)0xA6901D;
	static void* returnAddress = (void*)0x1098D52;

	__asm
	{
		call [interruptAddress]

		mov ecx, eax
		mov edx, edi
		call GetElapsedTime
		mov edx, eax

		jmp [returnAddress]
	}
}

FUNCTION_PTR(void, __thiscall, ProcMsgSetPinballHud, 0x1095D40, void* This, const SonicHud::MsgSetPinballHud& msgSetPinballHud);

HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* This, void* Edx, void* pUpdateInfo)
{
	SonicHud::MsgSetPinballHud msgSetPinballHud { };
	msgSetPinballHud.flags = 1;
	msgSetPinballHud.score = ScoreListener::score;

	// Checks if the current stage is Casino Night before assigning the local score.
	if (strcmp(StateHooks::stageID, "cnz100") != 0)
		ProcMsgSetPinballHud(This, msgSetPinballHud);

	originalCHudSonicStageUpdate(This, Edx, pUpdateInfo);
}

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void SonicHud::Install()
{
	// Jump to ring formatters to fix leading zeroes.
	WRITE_JUMP(0x1098E71, &DefaultRingFormatterMidAsmHook);
	WRITE_JUMP(0x1228245, &FinalBossRingFormatterMidAsmHook);

	if (Mod::scoreDisplay)
	{
		// Display the Casino Night score.
		WRITE_NOP(0x109C1DA, 2);

		// Set score string format.
		WRITE_MEMORY(0x1095D7D, char*, Mod::scoreFormat.c_str());

		// Install hook to update the score counter.
		INSTALL_HOOK(CHudSonicStageUpdate);

		// Jump to store elapsed time locally for time bonus.
		WRITE_JUMP(0x1098D4D, &TimeFormatterMidAsmHook);
	}
	else
	{
#if _DEBUG
		printf("[Forces HUD] Score display is disabled!\n");
#endif
	}
}