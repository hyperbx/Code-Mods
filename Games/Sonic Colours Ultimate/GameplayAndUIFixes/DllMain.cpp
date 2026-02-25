#include "Signatures.h"

class CLevelInfo
{
public:
	INSERT_PADDING(0x70);
	int m_LifeCount{};
	int m_RingCount{};
};

static CLevelInfo* g_pCLevelInfo{};
static bool g_isRingLifeReceived{};

DECLARE_FUNCTION_PTR(void, __cdecl, fpReturnToTitle, Sig_ReturnToTitle());

DECLARE_HOOK(CLevelInfo*, __fastcall, CLevelInfo_Ctor, Sig_CLevelInfo_Ctor(), CLevelInfo* in_pThis)
{
	g_pCLevelInfo = in_pThis;
	g_isRingLifeReceived = false;

	return original_CLevelInfo_Ctor(in_pThis);
}

DECLARE_HOOK(CLevelInfo*, __fastcall, CLevelInfo_Dtor, Sig_CLevelInfo_Dtor(), CLevelInfo* in_pThis, uint8_t in_flags)
{
	g_pCLevelInfo = nullptr;

	return original_CLevelInfo_Dtor(in_pThis, in_flags);
}

DECLARE_HOOK(void*, __fastcall, MsgPLNotifyDead_Ctor, Sig_MsgPLNotifyDead_Ctor(), void* in_pThis)
{
	if (!Configuration::IsTailsSave && g_pCLevelInfo)
	{
		if (g_pCLevelInfo->m_LifeCount - 1 != 0)
		{
			--g_pCLevelInfo->m_LifeCount;
		}
		else
		{
			fpReturnToTitle();
		}
	}

	return original_MsgPLNotifyDead_Ctor(in_pThis);
}

DECLARE_HOOK(void*, __fastcall, MsgPlayerPassTailsSaveMarker_Ctor, Sig_MsgPlayerPassTailsSaveMarker_Ctor(), void* in_pThis, uint32_t* a2, float a3, uint8_t a4, uint8_t a5, uint8_t a6)
{
	if (!Configuration::IsTailsSave)
		return in_pThis;

	return original_MsgPlayerPassTailsSaveMarker_Ctor(in_pThis, a2, a3, a4, a5, a6);
}

EXPORT void Init()
{
	cmf::sys::Logger::Init();

	if (!cmf::sys::mem::SignatureScanner::Status.Success)
	{
		LOGFN_ERROR("Error: {}\n{}", cmf::sys::mem::SignatureScanner::Status.pMessage, cmf::sys::mem::SignatureScanner::Status.GetPatternString());
		return;
	}

	Configuration::Read();

	INSTALL_HOOK(CLevelInfo_Ctor);
	INSTALL_HOOK(CLevelInfo_Dtor);
	INSTALL_HOOK(MsgPLNotifyDead_Ctor);
	INSTALL_HOOK(MsgPlayerPassTailsSaveMarker_Ctor);

	// Skip MsgPLNotifyTailsSave in CStateFallingDead.
	if (!Configuration::IsTailsSave)
		WRITE_JUMP((uint8_t*)Sig_CStateFallingDead_SendMsgPLNotifyTailsSave() + 0x34, (uint8_t*)Sig_CStateFallingDead_SendMsgPLNotifyTailsSave() + 0x3D);
}

EXPORT void OnFrame()
{
	if (!g_pCLevelInfo)
		return;

	switch (Configuration::RingLifeType)
	{
		case RingLifeType::Disabled:
			return;

		case RingLifeType::Once:
		{
			if (g_isRingLifeReceived)
			{
				return;
			}
			else
			{
				break;
			}
		}

		case RingLifeType::Enabled:
			g_isRingLifeReceived = false;
			break;
	}

	static int s_ringLifeBonusCapacity = 100;

	// Reset bonus cap if the player loses their rings.
	if (g_pCLevelInfo->m_RingCount == 0)
		s_ringLifeBonusCapacity = 100;

	while (g_pCLevelInfo->m_RingCount >= s_ringLifeBonusCapacity && !g_isRingLifeReceived)
	{
		// Increment life counter.
		g_pCLevelInfo->m_LifeCount += 1;

		// Increase bonus cap for the next 100 rings.
		s_ringLifeBonusCapacity += 100;

		// Set life received flag to cancel
		// the next if using RingLifeType::Once.
		g_isRingLifeReceived = true;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
