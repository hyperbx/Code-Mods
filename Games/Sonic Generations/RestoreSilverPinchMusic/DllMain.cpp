DECLARE_FUNCTION_PTR(uint32_t, __stdcall, fpPlayMusic, 0xD62440,
	Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> in_pGameDocument, const Hedgehog::Base::CSharedString& in_rCueName, float in_fadeInTime);

DECLARE_HOOK(int, __cdecl, CRivalSilverContext_CState_MeteorSmash_Ctor, 0xC880B0, int a1)
{
	fpPlayMusic(Sonic::CGameDocument::GetInstance(), "vs_Silver2", 0.25);

	return original_CRivalSilverContext_CState_MeteorSmash_Ctor(a1);
}

EXPORT void Init()
{
	INSTALL_HOOK(CRivalSilverContext_CState_MeteorSmash_Ctor);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
