#include "StateHooks.h"
#include "ScoreListener.h"
#include "SonicHud.h"
#include "Mod.h"

// Declare class variables.
const char* const StateHooks::stageID = (const char*)0x1E774D4;

__declspec(naked) void ClassicSonicRestartMidAsmHook()
{
	static void* interruptAddress = (void*)0xDD6740;
	static void* returnAddress = (void*)0xDEB841;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ModernSonicRestartMidAsmHook()
{
	static void* interruptAddress = (void*)0xE14350;
	static void* returnAddress = (void*)0xE28C7B;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ExitMidAsmHook()
{
	static void* interruptAddress = (void*)0x6AE910;
	static void* returnAddress = (void*)0x42AD76;

	__asm
	{
		call [interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp [returnAddress]
	}
}

__declspec(naked) void ResultsEndMidAsmHook()
{
	static void* interruptAddress = (void*)0x773250;
	static void* returnAddress = (void*)0xCFAEE7;

	__asm
	{
		call[interruptAddress]

		// Reset statistics.
		call ScoreListener::Reset

		jmp[returnAddress]
	}
}

__declspec(naked) void ResultsCalculateMidAsmHook()
{
	static void* returnAddress = (void*)0x10B41A5;

	// Calculate bonuses.
	ScoreListener::Bonus();

	__asm
	{
		// Move locally calculated score to final results registers.
		cvtsi2ss xmm0, ScoreListener::score
		cvtss2sd xmm1, xmm0

		jmp [returnAddress]
	}

	// Reset statistics.
	ScoreListener::Reset();
}

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void StateHooks::Install()
{
	WRITE_JUMP(0xDEB83C, &ClassicSonicRestartMidAsmHook);
	WRITE_JUMP(0xE28C76, &ModernSonicRestartMidAsmHook);
	WRITE_JUMP(0x42AD71, &ExitMidAsmHook);
	WRITE_JUMP(0xCFAEE2, &ResultsEndMidAsmHook);
	WRITE_JUMP(0x10B419D, &ResultsCalculateMidAsmHook);
}