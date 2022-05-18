#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void Ring_MidAsmHook()
{
	static void* interruptAddress = (void*)0x10534B0;
	static void* returnAddress = (void*)0x1054425;

	__asm
	{
		call[interruptAddress]

		// Reward player with Ring score.
		mov ecx, 0
		call ScoreListener::Reward
		mov edx, eax

		jmp[returnAddress]
	}
}

__declspec(naked) void Enemy_MidAsmHook()
{
	static void* returnAddress = (void*)0xBDDDA1;

	__asm
	{
		inc word ptr [esi + 0E0h]

		// Reward player with Enemy score.
		mov ecx, 1
		call ScoreListener::Reward
		mov edx, eax

		jmp[returnAddress]
	}
}

__declspec(naked) void Physics_MidAsmHook()
{
	static void* interruptAddress = (void*)0xEA50B0;
	static void* returnAddress = (void*)0xEA5417;

	__asm
	{
		call [interruptAddress]

		// Reward player with Physics score.
		mov ecx, 2
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void PlanetWispFallBlock_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x1131D9C;

	__asm
	{
		call [interruptAddress]

		// Reward player with Physics score.
		mov ecx, 2
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void PointMarker_MidAsmHook()
{
	static void* interruptAddress = (void*)0x76AA80;
	static void* returnAddress = (void*)0x457D4E;

	__asm
	{
		call [interruptAddress]

		// Reward player with Point Marker score.
		mov ecx, 3
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void RedRing_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x11A9CCE;

	__asm
	{
		call [interruptAddress]

		// Reward player with Red Ring score.
		mov ecx, 4
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void ItemBox_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x1055874;

	__asm
	{
		call [interruptAddress]

		// Reward player with Item Box score.
		mov ecx, 6
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void SuperRing_MidAsmHook()
{
	static void* interruptAddress = (void*)0x11F2F10;
	static void* returnAddress = (void*)0x11F36B1;

	__asm
	{
		call [interruptAddress]

		// Reward player with Super Ring score.
		mov ecx, 7
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void TrickFinish_MidAsmHook()
{
	static void* returnAddress = (void*)0xE4BC44;

	__asm
	{
		mov [ebp + 60h], 0

		// Reward player with Trick Finish score.
		mov ecx, 8
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void Trick_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6644C0;
	static void* returnAddress = (void*)0xE4B6EC;

	__asm
	{
		call [interruptAddress]

		// Reward player with Trick score.
		mov ecx, 9
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void Life_MidAsmHook()
{
	static void* interruptAddress = (void*)0xE75520;
	static void* returnAddress = (void*)0xE6D870;

	__asm
	{
		call [interruptAddress]

		// Reward player with Life score.
		mov ecx, 10
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void DashRing_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6644C0;
	static void* returnAddress = (void*)0x115AAA9;

	__asm
	{
		call [interruptAddress]

		// If the model index is not zero, reward Dash Ring score.
		cmp dword ptr [esi + 114h], 0
		jnz RewardDashRingScore

		// Reward player with Rainbow Ring score.
		mov ecx, 5
		call ScoreListener::Reward
		mov edx, eax
		jmp Return

	RewardDashRingScore:
		// Reward player with Dash Ring score.
		mov ecx, 11
		call ScoreListener::Reward
		mov edx, eax

	Return:
		jmp [returnAddress]
	}
}

__declspec(naked) void QuickStep_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0xDFE305;

	__asm
	{
		call [interruptAddress]

		// Skip reward if the player isn't running.
		comisd xmm0, xmm1
		jnbe Return

		// Reward player with Quick Step score.
		mov ecx, 12
		call ScoreListener::Reward
		mov edx, eax

	Return:
		jmp [returnAddress]
	}
}

__declspec(naked) void Drift_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0xDF2F1C;

	__asm
	{
		call [interruptAddress]

		// Reward player with Drift score.
		mov ecx, 13
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void Balloon_MidAsmHook()
{
	static void* interruptAddress = (void*)0x65FBE0;
	static void* returnAddress = (void*)0x1017E5E;

	__asm
	{
		call [interruptAddress]

		// Reward player with Balloon score.
		mov ecx, 14
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void BoardTrick_MidAsmHook()
{
	static void* interruptAddress = (void*)0xE5D990;
	static void* returnAddress = (void*)0x11A1294;

	__asm
	{
		call [interruptAddress]

		// Reward player with Board Trick score.
		mov ecx, 16
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

#pragma endregion

void ScoreHooks::Install()
{
	// Hook objects and states to add score to the counter.
	WRITE_JUMP(0x1054420, &Ring_MidAsmHook);
	WRITE_JUMP(0xBDDD9A, &Enemy_MidAsmHook);
	WRITE_JUMP(0xEA5412, &Physics_MidAsmHook);
	WRITE_JUMP(0x1131D97, &PlanetWispFallBlock_MidAsmHook);
	WRITE_JUMP(0x457D49, &PointMarker_MidAsmHook);
	WRITE_JUMP(0x11A9CC9, &RedRing_MidAsmHook);
	WRITE_JUMP(0x105586F, &ItemBox_MidAsmHook);
	WRITE_JUMP(0x11F36AC, &SuperRing_MidAsmHook);
	WRITE_JUMP(0xE4BC3D, &TrickFinish_MidAsmHook);
	WRITE_JUMP(0xE4B6E7, &Trick_MidAsmHook);
	WRITE_JUMP(0xE6D86B, &Life_MidAsmHook);
	WRITE_JUMP(0x115AAA4, &DashRing_MidAsmHook);
	WRITE_JUMP(0xDFE300, &QuickStep_MidAsmHook);
	WRITE_JUMP(0xDF2F17, &Drift_MidAsmHook);
	WRITE_JUMP(0x1017E59, &Balloon_MidAsmHook);
	WRITE_JUMP(0x11A128F, &BoardTrick_MidAsmHook);
}