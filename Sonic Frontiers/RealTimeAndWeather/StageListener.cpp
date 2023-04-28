CL_SCAN_SIGNATURE(m_SigGameModeStageUpdate, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x4C\x89\x74\x24\x20\x55\x48\x8D\xAC\x24\x20\xFE", "xxxxxxxxxxxxxxxxxxxxxxxxxxx");

HOOK(int64_t, __fastcall, GameModeStageUpdate, m_SigGameModeStageUpdate(), int64_t a1, int64_t a2, int* a3)
{
	int64_t result = originalGameModeStageUpdate(a1, a2, a3);

	const char* stageId = (const char*)(a1 + 0xA0);

	if (StringHelper::Compare(stageId, "w1r02"))
	{
		StageListener::m_IslandType = StageListener::Kronos;
	}
	else if (StringHelper::Compare(stageId, "w2r01"))
	{
		StageListener::m_IslandType = StageListener::Ares;
	}
	else if (StringHelper::Compare(stageId, "w3r01"))
	{
		StageListener::m_IslandType = StageListener::Chaos;
	}
	else if (StringHelper::Compare(stageId, "w1r05"))
	{
		StageListener::m_IslandType = StageListener::Rhea;
	}
	else if (StringHelper::Compare(stageId, "w1r04"))
	{
		StageListener::m_IslandType = StageListener::Ouranos;
	}

	return result;
}

void StageListener::Install()
{
	INSTALL_HOOK(GameModeStageUpdate);
}