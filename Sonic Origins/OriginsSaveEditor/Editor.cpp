int64_t m_pGameData;

CL_SCAN_SIGNATURE(m_SigLoadGameData, 0x140461A7C, "\xE8\xCC\xCC\xCC\xCC\x4C\x8D\xB3\x60\x02\x00\x00\x4C\x8B\xF8", "x????xxxxxxxxxx");

HOOK(int64_t, __fastcall, LoadGameData, READ_CALL(m_SigLoadGameData()), int64_t a1, int64_t a2)
{
	m_pGameData = **(int64_t**)(a1 + 0xA0) + 0x48;

	return originalLoadGameData(a1, a2);
}

void Editor::Install()
{
	INSTALL_HOOK(LoadGameData);
}