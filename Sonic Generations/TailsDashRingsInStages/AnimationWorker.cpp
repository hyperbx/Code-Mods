const char* defaultDashRing = "cmn_obj_dashring_HD";

void __fastcall SetAnimations(int index)
{
#if _DEBUG
	printf("[Tails' Dash Rings in Stages] Current model index = %d\n", index);
#endif

	switch (index)
	{
		case 0:
		{
			// Push rainbow ring material animations.
			WRITE_MEMORY(0x115ACE8, const char*, "rnb_obj_TailsDashring_light1");
			WRITE_MEMORY(0x115AC6A, const char*, Configuration::useCustomRainbowRings ? "rnb_obj_TailsDashring_light2" : "cmn_obj_rainbowring_HD");
			WRITE_MEMORY(0x115AD66, const char*, "rnb_obj_TailsDashring_light3");

			break;
		}

		case 1:
		{
		PushDashRingNames:
			// Push dash ring material animations.
			WRITE_MEMORY(0x115ACE8, const char*, "cmn_obj_TailsDashring_light1");
			WRITE_MEMORY(0x115AC6A, const char*, "cmn_obj_TailsDashring_light2");
			WRITE_MEMORY(0x115AD66, const char*, "cmn_obj_TailsDashring_light3");

			// Push Tails' dash ring material animations if we're using the default materials.
			if (Configuration::colourType == Configuration::GreenDiffuse)
				Configuration::overrideTailsDashRing = false;
			else
				break;
		}

		case 2:
		{
			// Push Tails' dash ring material animations.
			WRITE_MEMORY(0x115ACE8, const char*, "mis_obj_TailsDashring_light1");
			WRITE_MEMORY(0x115AC6A, const char*, "mis_obj_TailsDashring_light2");
			WRITE_MEMORY(0x115AD66, const char*, "mis_obj_TailsDashring_light3");

			// Push dash ring material animations if we're overriding Tails' ones.
			if (Configuration::overrideTailsDashRing)
				goto PushDashRingNames;

			break;
		}
	}
}

__declspec(naked) void DashRingInit_MidAsmHook()
{
	static void* interruptAddress = (void*)0x6621A0;
	static void* returnAddress = (void*)0x115AE1E;

	// Patch new dash ring model.
	Patches::PatchDashRingNames();

	__asm
	{
		call [interruptAddress]

		jmp [returnAddress]
	}
}

__declspec(naked) void DashRingAnimationInit_MidAsmHook()
{
	static void* returnAddress = (void*)0x115AC69;

	__asm
	{
		mov ecx, eax
		call [SetAnimations]
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void MissionNumberDashRingInit_MidAsmHook()
{
	static void* interruptAddress = (void*)0x65FFF0;
	static void* returnAddress = (void*)0xEDBD7F;

	// Restore original dash ring model.
	Patches::PatchDashRingNames(defaultDashRing);

	__asm
	{
		call [interruptAddress]

		jmp [returnAddress]
	}
}

void AnimationWorker::Install()
{
	WRITE_JUMP(0x115AE19, &DashRingInit_MidAsmHook);

	WRITE_JUMP(0x115AC63, &DashRingAnimationInit_MidAsmHook);
	WRITE_NOP(0x115AC68, 1);

	WRITE_JUMP(0xEDBD7A, &MissionNumberDashRingInit_MidAsmHook);
}