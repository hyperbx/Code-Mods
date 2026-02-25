#include "ScoreHooks.h"
#include "ScoreProvider.h"

using namespace ScoreGenerations;

DECLARE_ASM_HOOK_32(Ring_MidAsmHook, 0x1054420)
{
	static void* s_interruptAddress = (void*)0x10534B0;
	static void* s_returnAddress = (void*)0x1054425;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 0
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Enemy_MidAsmHook, 0xBDDD9A)
{
	static void* s_returnAddress = (void*)0xBDDDA1;

	__asm
	{
		inc  word ptr [esi + 0xE0]
		mov  ecx, 1
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Physics_MidAsmHook, 0xEA5412)
{
	static void* s_interruptAddress = (void*)0xEA50B0;
	static void* s_returnAddress = (void*)0xEA5417;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 2
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(PlanetWispFallBlock_MidAsmHook, 0x1131D97)
{
	static void* s_interruptAddress = (void*)0x6621A0;
	static void* s_returnAddress = (void*)0x1131D9C;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 2
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(PointMarker_MidAsmHook, 0x457D49)
{
	static void* s_interruptAddress = (void*)0x76AA80;
	static void* s_returnAddress = (void*)0x457D4E;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 3
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(RedRing_MidAsmHook, 0x11A9CC9)
{
	static void* s_interruptAddress = (void*)0x6621A0;
	static void* s_returnAddress = (void*)0x11A9CCE;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 4
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(ItemBox_MidAsmHook, 0x105586F)
{
	static void* s_interruptAddress = (void*)0x6621A0;
	static void* s_returnAddress = (void*)0x1055874;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 6
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(SuperRing_MidAsmHook, 0x11F36AC)
{
	static void* s_interruptAddress = (void*)0x11F2F10;
	static void* s_returnAddress = (void*)0x11F36B1;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 7
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(TrickFinish_MidAsmHook, 0xE4BC3D)
{
	static void* s_returnAddress = (void*)0xE4BC44;

	__asm
	{
		mov  [ebp + 0x60], 0
		mov  ecx, 8
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Trick_MidAsmHook, 0xE4B6E7)
{
	static void* s_interruptAddress = (void*)0x6644C0;
	static void* s_returnAddress = (void*)0xE4B6EC;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 9
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Life_MidAsmHook, 0xE6D86B)
{
	static void* s_interruptAddress = (void*)0xE75520;
	static void* s_returnAddress = (void*)0xE6D870;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 10
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(DashRing_MidAsmHook, 0x115AAA4)
{
	static void* s_interruptAddress = (void*)0x6644C0;
	static void* s_returnAddress = (void*)0x115AAA9;

	__asm
	{
		call [s_interruptAddress]

		// If the model index is not zero, reward Dash Ring score.
		cmp  dword ptr [esi + 114h], 0
		jnz  RewardDashRingScore

		// Reward player with Rainbow Ring score.
		mov  ecx, 5
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  Return

	RewardDashRingScore:
		// Reward player with Dash Ring score.
		mov  ecx, 11
		call ScoreProvider::AddScoreByType
		mov  edx, eax

	Return:
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(QuickStep_MidAsmHook, 0xDFE300)
{
	static void* s_interruptAddress = (void*)0x6621A0;
	static void* s_returnAddress = (void*)0xDFE305;

	__asm
	{
		call   [s_interruptAddress]

		// Skip reward if the player isn't running.
		comisd xmm0, xmm1
		jnbe   Return

		// Reward player with Quick Step score.
		mov    ecx, 12
		call   ScoreProvider::AddScoreByType
		mov    edx, eax

	Return:
		jmp    [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Drift_MidAsmHook, 0xDF2F17)
{
	static void* s_interruptAddress = (void*)0x6621A0;
	static void* s_returnAddress = (void*)0xDF2F1C;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 13
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Balloon_MidAsmHook, 0x1017E59)
{
	static void* s_interruptAddress = (void*)0x65FBE0;
	static void* s_returnAddress = (void*)0x1017E5E;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 14
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(BoardTrick_MidAsmHook, 0x11A128F)
{
	static void* s_interruptAddress = (void*)0xE5D990;
	static void* s_returnAddress = (void*)0x11A1294;

	__asm
	{
		call [s_interruptAddress]
		mov  ecx, 16
		call ScoreProvider::AddScoreByType
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

void ScoreHooks::Install()
{
	INSTALL_ASM_HOOK_32(Ring_MidAsmHook);
	INSTALL_ASM_HOOK_32(Enemy_MidAsmHook);
	INSTALL_ASM_HOOK_32(Physics_MidAsmHook);
	INSTALL_ASM_HOOK_32(PlanetWispFallBlock_MidAsmHook);
	INSTALL_ASM_HOOK_32(PointMarker_MidAsmHook);
	INSTALL_ASM_HOOK_32(RedRing_MidAsmHook);
	INSTALL_ASM_HOOK_32(ItemBox_MidAsmHook);
	INSTALL_ASM_HOOK_32(SuperRing_MidAsmHook);
	INSTALL_ASM_HOOK_32(TrickFinish_MidAsmHook);
	INSTALL_ASM_HOOK_32(Trick_MidAsmHook);
	INSTALL_ASM_HOOK_32(Life_MidAsmHook);
	INSTALL_ASM_HOOK_32(DashRing_MidAsmHook);
	INSTALL_ASM_HOOK_32(QuickStep_MidAsmHook);
	INSTALL_ASM_HOOK_32(Drift_MidAsmHook);
	INSTALL_ASM_HOOK_32(Balloon_MidAsmHook);
	INSTALL_ASM_HOOK_32(BoardTrick_MidAsmHook);
}
