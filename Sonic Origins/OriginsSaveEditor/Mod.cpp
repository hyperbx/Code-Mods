HMODULE m_Bridge;

EXPORT void Init()
{
	if (!(m_Bridge = LoadLibraryA("OriginsSaveEditor.Bridge.dll")))
	{
		MessageBoxA(nullptr, "Failed to initialise bridge module.", "Origins Save Editor", MB_ICONERROR);
		exit(-1);
		return;
	}

	GetProcAddress(m_Bridge, "Init")();

	Editor::Install();
}