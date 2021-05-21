#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void RingMidAsmHook()
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

__declspec(naked) void ClassicSonicDamageSuccessMidAsmHook()
{
	static void* interruptAddress = (void*)0xDDAE80;
	static void* returnAddress = (void*)0xDEB121;

	__asm
	{
		call [interruptAddress]

		// Reward player with Enemy score.
		mov ecx, 1
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void ModernSonicDamageSuccessMidAsmHook()
{
	static void* interruptAddress = (void*)0xE18260;
	static void* returnAddress = (void*)0xE2855B;

	__asm
	{
		call[interruptAddress]

		// Reward player with Enemy score.
		mov ecx, 1
		call ScoreListener::Reward
		mov edx, eax

		jmp[returnAddress]
	}
}

__declspec(naked) void ObjectPhysicsMidAsmHook()
{
	static void* interruptAddress = (void*)0xEA50B0;
	static void* returnAddress = (void*)0xEA5417;

	__asm
	{
		call [interruptAddress]

		// Reward player with Object score.
		mov ecx, 2
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void PointMarkerMidAsmHook()
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

__declspec(naked) void RedRingMidAsmHook()
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

__declspec(naked) void RainbowRingMidAsmHook()
{
	static void* returnAddress = (void*)0xE28AB3;

	__asm
	{
		// Reward player with Rainbow Ring score.
		mov ecx, 5
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void ItemBoxMidAsmHook()
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

__declspec(naked) void SuperRingMidAsmHook()
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

__declspec(naked) void TrickFinishMidAsmHook()
{
	static void* interruptAddress = (void*)0x661550;
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

__declspec(naked) void TrickMidAsmHook()
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

__declspec(naked) void LifeMidAsmHook()
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

__declspec(naked) void DashRingMidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x115A9B2;

	__asm
	{
		call [interruptAddress]

		// Reward player with Dash Ring score.
		mov ecx, 11
		call ScoreListener::Reward
		mov edx, eax

		jmp [returnAddress]
	}
}

#pragma endregion

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void ObjectHooks::Install()
{
	// Hook objects to add score to the counter.
	WRITE_JUMP(0x1054420, &RingMidAsmHook);
	WRITE_JUMP(0xDEB11C, &ClassicSonicDamageSuccessMidAsmHook);
	WRITE_JUMP(0xE28556, &ModernSonicDamageSuccessMidAsmHook);
	WRITE_JUMP(0xEA5412, &ObjectPhysicsMidAsmHook);
	WRITE_JUMP(0x457D49, &PointMarkerMidAsmHook);
	WRITE_JUMP(0x11A9CC9, &RedRingMidAsmHook);
	WRITE_JUMP(0xE28AAE, &RainbowRingMidAsmHook);
	WRITE_JUMP(0x105586F, &ItemBoxMidAsmHook);
	WRITE_JUMP(0x11F36AC, &SuperRingMidAsmHook);
	WRITE_JUMP(0xE4BC3D, &TrickFinishMidAsmHook);
	WRITE_JUMP(0xE4B6E7, &TrickMidAsmHook);
	WRITE_JUMP(0xE6D86B, &LifeMidAsmHook);
	WRITE_JUMP(0x115A9AD, &DashRingMidAsmHook);
}