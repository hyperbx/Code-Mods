static HMODULE g_hModule{};

HICON __stdcall LoadSonicGenerationsIcon(HMODULE hModule, LPCSTR lpIconName)
{
	return LoadIconA(g_hModule, (LPCSTR)IDI_ICON);
}

EXPORT void Init()
{
	// Redirect title text to SEGA-less variant.
	WRITE(0xE7A99D, uint8_t, 0x3C);

	// Use Sonic Generations' icon for the window.
	WRITE_CALL(0xE7B843, &LoadSonicGenerationsIcon);
	WRITE_NOP(0xE7B848, 1);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	g_hModule = hModule;

	return TRUE;
}
