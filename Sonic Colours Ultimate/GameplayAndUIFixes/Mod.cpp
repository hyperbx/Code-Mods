/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	Configuration::Read();

	CLevelInfo::Init();
}

/// <summary>
/// Actions performed every frame.
/// </summary>
extern "C" _declspec(dllexport) void OnFrame()
{
	CLevelInfo::OnFrame();
}