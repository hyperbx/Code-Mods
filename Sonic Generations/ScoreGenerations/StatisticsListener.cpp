Statistics::Totals StatisticsListener::totals;

HOOK(void, __fastcall, CHudSonicStageUpdateStatistics, 0x1098A50, Sonic::CGameObject* thisDeclaration, void* edx, float* pUpdateInfo)
{
	if (CONTEXT != nullptr)
	{
		int rings = CONTEXT->m_RingCount;

		// Update current ring count.
		StatisticsListener::totals.ringCount = rings;

		// Update total ring count.
		if (rings > StatisticsListener::totals.totalRingCount)
			StatisticsListener::totals.totalRingCount = rings;
	}

	// Update elapsed time.
	size_t minutes, seconds, milliseconds;
	StatisticsListener::GetTime(**thisDeclaration->m_pMember->m_pGameDocument, &minutes, &seconds, &milliseconds);
	{
		StatisticsListener::totals.elapsedTime = StatisticsListener::GetElapsedTime(**thisDeclaration->m_pMember->m_pGameDocument);
		StatisticsListener::totals.minutes = minutes;
		StatisticsListener::totals.seconds = seconds;
		StatisticsListener::totals.milliseconds = milliseconds;
	}

	originalCHudSonicStageUpdateStatistics(thisDeclaration, edx, pUpdateInfo);
}

void StatisticsListener::GetTime(Sonic::CGameDocument* pGameDocument, size_t* minutes, size_t* seconds, size_t* milliseconds)
{
	static void* pointerAddress = (void*)0xD61570;

	__asm
	{
		mov ecx, minutes
		mov edi, seconds
		mov esi, milliseconds
		mov eax, pGameDocument
		call [pointerAddress]
	}
}

float StatisticsListener::GetElapsedTime(Sonic::CGameDocument* pGameDocument)
{
	const auto pMember = (uint8_t*)pGameDocument->m_pMember;
	return max(0, max(0, *(float*)(pMember + 0x184)) + *(float*)(pMember + 0x18C));
}

void StatisticsListener::Install()
{
	// Set score string format.
	WRITE_MEMORY(0x1095D7D, const char*, Configuration::scoreFormat.c_str());

	// Update current statistics.
	INSTALL_HOOK(CHudSonicStageUpdateStatistics);
}