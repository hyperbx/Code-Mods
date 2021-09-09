FUNCTION_PTR(unsigned int, __stdcall, PlayAudioFromCueName, 0xD62440, int* gameDocument, Hedgehog::Base::CSharedString& cueName, float fadeInTime);

void PlayPinchMusic()
{
	Hedgehog::Base::CSharedString vsSilver2 = Hedgehog::Base::CSharedString("vs_Silver2");
	PlayAudioFromCueName(*(int**)0x1E0BE5C, vsSilver2, 0.25);
}

HOOK(int, __cdecl, MeteorSmashConstructor, 0xC880B0, int a1)
{
	PlayPinchMusic();

	return originalMeteorSmashConstructor(a1);
}

/// <summary>
/// The main entry point for the injection.
/// </summary>
extern "C" _declspec(dllexport) void Init()
{
	INSTALL_HOOK(MeteorSmashConstructor);
}