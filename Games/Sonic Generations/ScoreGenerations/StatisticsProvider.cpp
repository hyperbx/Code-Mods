#include "StatisticsProvider.h"

using namespace ScoreGenerations;

static void GetTime(Sonic::CGameDocument* in_pGameDocument, int& out_rMinutes, int& out_rSeconds, int& out_rMilliseconds)
{
	static void* s_funcAddress = (void*)0xD61570;

	__asm
	{
		mov  ecx, out_rMinutes
		mov  edi, out_rSeconds
		mov  esi, out_rMilliseconds
		mov  eax, in_pGameDocument
		call [s_funcAddress]
	}
}

static float GetElapsedTime(Sonic::CGameDocument* in_pGameDocument)
{
	const auto pMember = (uint8_t*)in_pGameDocument->m_pMember;

	return std::max(0.0f, std::max(0.0f, *(float*)(pMember + 0x184)) + *(float*)(pMember + 0x18C));
}

DECLARE_STATIC_HOOK(void, __fastcall, CHudSonicStage_UpdateSerial_StatisticsProvider, 0x1098A50, Sonic::CGameObject* in_pThis, void* EDX, const Hedgehog::Universe::SUpdateInfo& in_rUpdateInfo)
{
	auto& rStatistics = StatisticsProvider::GetStatistics();
	auto* pPlayerSpeedContext = Sonic::Player::CPlayerSpeedContext::GetInstance();

	if (pPlayerSpeedContext)
	{
		auto ringCount = pPlayerSpeedContext->m_RingCount;

		// Update current ring count.
		rStatistics.RingCount = ringCount;

		// Update total ring count.
		if (int(ringCount) > rStatistics.TotalRingCount)
			rStatistics.TotalRingCount = ringCount;
	}

	int minutes{};
	int seconds{};
	int milliseconds{};

	GetTime(**in_pThis->m_pMember->m_pGameDocument, minutes, seconds, milliseconds);

	rStatistics.ElapsedTime = GetElapsedTime(**in_pThis->m_pMember->m_pGameDocument);
	rStatistics.Minutes = minutes;
	rStatistics.Seconds = seconds;
	rStatistics.Milliseconds = milliseconds;

	original_CHudSonicStage_UpdateSerial_StatisticsProvider(in_pThis, EDX, in_rUpdateInfo);
}

Statistics& StatisticsProvider::GetStatistics()
{
	return m_Statistics;
}

void StatisticsProvider::Install()
{
	// Set score format.
	WRITE(0x1095D7D, const char*, Configuration::ScoreFormat.c_str());
}
