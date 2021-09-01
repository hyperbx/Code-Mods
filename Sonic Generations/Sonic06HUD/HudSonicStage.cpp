#include "HudSonicStage.h"
/// <summary>
/// Change 2 digit decisecond to 3 digit millsecond
/// </summary>
/// <param name="milliseconds">2 digit decisecond from ECX</param>
uint32_t __fastcall CreateRandomThirdDigit(uint32_t milliseconds)
{
	return milliseconds * 10 + rand() % 10;
}

/// <summary>
/// Change 2 digit decisecond to 3 digit millsecond
/// </summary>
/// <param name="buffer">buffer to print time (ecx)</param>
/// <param name="totalSeconds">remaining time INT32 (edx)</param>
void __fastcall SetMissionTime(char* buffer, int totalSeconds)
{
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	sprintf(buffer, "%02d:%02d.", minutes, seconds);
}

/// <summary>
/// Fade in transition hook to correct transition times.
/// </summary>
HOOK(float*, __fastcall, MsgFadeIn, 0x10CEC90, void* This, void* Edx, float* a2)
{
	uint8_t* color = (uint8_t*)((uint32_t)a2 + 21);

	if (color[0] == 0 && color[1] == 0 && color[2] == 0)
	{
		a2[6] = ((float*)This)[24]; // start alpha

		if (a2[6] > 0.0f)
			a2[4] = 0.2f; // transition time
	}

	return originalMsgFadeIn(This, Edx, a2);
}

/// <summary>
/// Fade out transition hook to correct transition times.
/// </summary>
HOOK(float*, __fastcall, MsgFadeOut, 0x10CEDB0, void* This, void* Edx, float* a2)
{
	uint8_t* color = (uint8_t*)((uint32_t)a2 + 21);

	if (color[0] == 0 && color[1] == 0 && color[2] == 0)
	{
		a2[4] = 0.0f; // transition time
		a2[6] = 1.0f; // start alpha
	}

	return originalMsgFadeOut(This, Edx, a2);
}

/// <summary>
/// Hook to lock player control whilst the fade out transition is occurring.
/// </summary>
HOOK(void, __stdcall, FadeOutCountDec, 0x10CE9A0)
{
	originalFadeOutCountDec();

	(*(uint32_t**)0x1E66B40)[2] = 0;
}

/// <summary>
/// HUD update hook to perform actions on every frame.
/// </summary>
HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, void* pUpdateInfo)
{
	// Always clamp boost to 100%.
	*PlayerListener::GetBoost() = clamp(*PlayerListener::GetBoost(), 0.0f, 100.0f);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

__declspec(naked) void MillisecondsCalculate_MidAsmHook()
{
	static void* returnAddress = (void*)0x10B3847;

	__asm
	{
		imul edx, 3E8h
		sub ecx, edx
		jmp [returnAddress]
	}
}

__declspec(naked) void MissionCurrentTime_MidAsmHook()
{
	static void* returnAddress = (void*)0x124F098;

	__asm
	{
		mov edx, esi
		call SetMissionTime
		pop esi
		sub esp, 0Ch
		jmp [returnAddress]
	}
}

__declspec(naked) void MissionNextRankMaxTime_MidAsmHook()
{
	static void* returnAddress = (void*)0x10B16D5;

	__asm
	{
		mov	esi, 99
		mov edx, 59
		mov ecx, 999
		jmp [returnAddress]
	}
}

__declspec(naked) void MissionNextRankRandomDigit_MidAsmHook()
{
	static void* returnAddress = (void*)0x10B16F9;

	__asm
	{
		push eax
		push edx
		push esi
		call CreateRandomThirdDigit
		mov ecx, eax
		pop esi
		pop edx
		pop eax

		push ecx
		push edx
		push esi
		lea ecx, [esp + 3Ch]
		jmp [returnAddress]
	}
}

__declspec(naked) void StageNextRankMaxTime_MidAsmHook()
{
	static void* returnAddress = (void*)0x10B6013;

	__asm
	{
		mov	esi, 99
		mov edx, 59
		mov ecx, 999
		jmp [returnAddress]
	}
}

__declspec(naked) void StageNextRankRandomDigit_MidAsmHook()
{
	static void* returnAddress = (void*)0x10B6037;

	__asm
	{
		push eax
		push edx
		push esi
		call CreateRandomThirdDigit
		mov ecx, eax
		pop esi
		pop edx
		pop eax

		push ecx
		push edx
		push esi
		lea ecx, [esp + 14h]
		jmp [returnAddress]
	}
}

void HudSonicStage::Install()
{
	// Install HUD update hook.
	INSTALL_HOOK(CHudSonicStageUpdate);

	// Install hooks to improve fading transitions.
	INSTALL_HOOK(MsgFadeIn);
	INSTALL_HOOK(MsgFadeOut);
	INSTALL_HOOK(FadeOutCountDec);

	// Calculate correct 3 digit milliseconds for stage time
	static double const secMultiplier = 1000;
	WRITE_MEMORY(0x10B37BF, double*, &secMultiplier);
	WRITE_MEMORY(0x10B37F7, uint32_t, 9162597); // 9162597/2^39 ~= 1/60000
	WRITE_MEMORY(0x10B3830, int32_t, -60000); // sec = total_sec + min * (-60000) = total_sec % 60000
	WRITE_MEMORY(0x10B3837, uint32_t, 137438954); // 137438954/2^37 ~= 1/1000
	WRITE_JUMP(0x10B3842, MillisecondsCalculate_MidAsmHook);
	WRITE_MEMORY(0x10B3823, uint32_t, 999); // maximum milliseconds
	WRITE_MEMORY(0x1098D75, uint32_t, 0x168E8E0); // %03d 

	// Set laptime always display current time
	WRITE_MEMORY(0x1032FD1, uint8_t, 0xEB);
	WRITE_MEMORY(0x1033040, uint8_t, 0xEB);
	WRITE_NOP(0x10330A0, 6);
	WRITE_JUMP(0x103312C, (void*)0x103313E);
	WRITE_MEMORY(0x10978E4, double*, &secMultiplier);
	WRITE_STRING(0x168ED20, "%02d:%02d.%03d");

	// Change mission countdown time to have MM:SS.xxx format
	WRITE_JUMP(0x124F08D, MissionCurrentTime_MidAsmHook);

	// Display a random 3rd digit for next rank time in mission
	WRITE_STRING(0x1693474, "%02d:%02d.%03d");
	WRITE_JUMP(0x10B16CB, MissionNextRankMaxTime_MidAsmHook);
	WRITE_JUMP(0x10B16F2, MissionNextRankRandomDigit_MidAsmHook);

	// Display a random 3rd digit for next rank time in stages
	WRITE_STRING(0x16940F4, "%02d:%02d.%03d");
	WRITE_JUMP(0x10B6009, StageNextRankMaxTime_MidAsmHook);
	WRITE_JUMP(0x10B6030, StageNextRankRandomDigit_MidAsmHook);

	// Other instances using sub_10B37B0
	WRITE_STRING(0x1689274, "--:--.---");
	WRITE_STRING(0x1689280, "%02d:%02d.%03d");
	WRITE_STRING(0x1689290, "--:--.---");
	WRITE_STRING(0x168929C, "%02d:%02d.%03d");
	WRITE_STRING(0x168CD0C, "99:59.999");
	WRITE_STRING(0x168CD18, "%02d:%02d.%03d");
	WRITE_STRING(0x16941C0, "%02d:%02d.%03d");
	WRITE_MEMORY(0x117BF38, uint32_t, 0x168E8E0); // %03d 
	WRITE_MEMORY(0x11CCCC2, uint32_t, 0x168E8E0); // %03d

	// Fixed default result time to 99:59.999
	WRITE_MEMORY(0x10B685B, uint32_t, 0x168CD0C);

	// Set mission count down have 3 digit millisecond
	WRITE_MEMORY(0x124F0B1, double*, &secMultiplier);
	WRITE_MEMORY(0x124F0BF, uint32_t, 0x168E8E0); // %03d
}
