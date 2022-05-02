/// <summary>
/// Hooked function that returns Sonic Forces' icon - following the same pattern as LoadIconA.
/// </summary>
HICON __stdcall LoadSonicForcesIcon(HINSTANCE hInstance, LPCSTR lpIconName)
{
	return LoadIconA(DllMain::handle, (LPCSTR)IDI_ICON);
}

void Patches::Install()
{
	if (Configuration::windowTitle)
	{
		// Write 'SONIC FORCES' in the title bar.
		WRITE_MEMORY(0xE7A99D, uint8_t, 0x3C);
		WRITE_MEMORY(0x1606C3C, uint8_t, "SONIC FORCES\0");

		// Use Sonic Forces' icon for the window.
		WRITE_CALL(0xE7B843, &LoadSonicForcesIcon);
		WRITE_NOP(0xE7B848, 1);
	}

	// Freeze lives.
	WRITE_NOP(0xD59A67, 6);

	// Disable 1-UP from rings.
	WRITE_NOP(0xE68562, 5);

	// Remove 1-UP object.
	WRITE_MEMORY(0x166463C, uint8_t, 0x00);

	// Remove 1-UP item box.
	WRITE_MEMORY(0x167DDE4, uint8_t, 0x00);

	// Disable chaos energy particles.
	WRITE_JUMP(0x112435C, (void*)0x112440C);
	WRITE_NOP(0x1124733, 5);

	// Disable title loading video (fixes hang on title screen).
	WRITE_JUMP(0xD69666, (void*)0xD69787);

	// Disable loading hints (fixes mission text appearing on the loading screen).
	WRITE_JUMP(0x448959, (void*)0x448A70);

	// Use Sonic Unleashed's intro XNCP for normal stages.
	WRITE_MEMORY(0x168F1F8, uint8_t, "_b\0");

	// Instantly collect Chaos Energy from enemies (code by brianuuu).
	WRITE_NOP(0x1124433, 6);
	WRITE_JUMP(0x1124489, (void*)0x11244BD);
	WRITE_NOP(0x11244C1, 6);
	WRITE_NOP(0x11244D0, 6);
	WRITE_MEMORY(0x112459B, uint32_t, 0xFFFFFFFF);

	if (!Configuration::homingReticle)
	{
		// Use Sonic Generations' lock-on XNCP.
		WRITE_MEMORY(0x15E36E4, uint8_t, "_b\0");
		WRITE_MEMORY(0x155E5E8, uint8_t, "_b\0");

#if _DEBUG
		printf("[Forces HUD] Homing reticle is disabled!\n");
#endif
	}

	if (Configuration::boostText)
	{
		// Force enable the boost button prompt (in case of patch conflicts).
		WRITE_MEMORY(0x109BC7C, uint8_t, 0x8B, 0x8D, 0x5C, 0x02, 0x00, 0x00);
	}
	else
	{
		// Force disable the boost button prompt based on configuration.
		WRITE_MEMORY(0x109BC7C, uint8_t, 0xE9, 0x71, 0x01, 0x00, 0x00);
	}

	switch (Configuration::trickSounds)
	{
		case 1:
		case 2:
			WRITE_MEMORY(0xE4A45A, uint32_t, 0x313E5); // 2002_trick01
			WRITE_MEMORY(0xE4A464, uint32_t, 0x313E6); // 2002_trick02
			WRITE_MEMORY(0xE4A46E, uint32_t, 0x313E7); // 2002_trick03
			WRITE_MEMORY(0xE4B9DB, uint32_t, 0x31447); // 2002_trickfinish

		case 3:
		{
			// The case for option 2 bleeds into this one, so we'll break here.
			if (Configuration::trickSounds == 2)
				break;

			WRITE_MEMORY(0x11A129C, uint32_t, 0x313E6); // 2002_bdtrick_succ
			break;
		}
	}

	if (Configuration::homingSound)
	{
		// Use custom sound ID for the homing sound.
		WRITE_MEMORY(0xDEBDB7, uint32_t, 0x31429);
	}
}