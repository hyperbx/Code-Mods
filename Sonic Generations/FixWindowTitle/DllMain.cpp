HINSTANCE handle;

BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD reason, _In_ LPVOID reserved)
{
	handle = hInstance;

	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}

	return TRUE;
}

/// <summary>
/// Hooked function that returns the icon - following the same pattern as LoadIconA.
/// </summary>
HICON __stdcall LoadSonicGenerationsIcon(HINSTANCE hInstance, LPCSTR lpIconName)
{
	return LoadIconA(handle, (LPCSTR)IDI_ICON);
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	// Redirect title text to SEGA-less variant.
	WRITE_MEMORY(0xE7A99D, uint8_t, 0x3C);

	// Use Sonic Generations' icon for the window.
	WRITE_CALL(0xE7B843, &LoadSonicGenerationsIcon);
	WRITE_NOP(0xE7B848, 1);
}