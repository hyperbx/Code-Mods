#include "BonusProvider.h"
#include "ScoreHud.h"
#include "ScoreProvider.h"
#include "StatisticsProvider.h"
#include "TableProvider.h"

using namespace ScoreGenerations;

static bool g_isResultsHooked = false;

DECLARE_HOOK(bool, __cdecl, IsPerfectBonus, 0x10B8A90)
{
	if (g_isResultsHooked)
	{
		if (Configuration::PerfectBonusType == PerfectBonusType::Disabled)
		{
			return false;
		}
		else if (Configuration::PerfectBonusType == PerfectBonusType::OnlyForARank)
		{
			return ScoreProvider::GetResults().m_Rank == 3 && original_IsPerfectBonus();
		}
	}

	return original_IsPerfectBonus();
}

DECLARE_HOOK(int*, __cdecl, MsgChangeResultState_Ctor, 0x587C40, void* a1, int* a2, int* in_pRank, int* a4)
{
	DECLARE_FUNCTION_PTR(bool, __cdecl, fpIsPerfectBonus, 0x10B8A90);

	// Set correct rank animation if there's no perfect bonus.
	if (!fpIsPerfectBonus())
		*in_pRank = ScoreProvider::GetResults().m_Rank;

	return original_MsgChangeResultState_Ctor(a1, a2, in_pRank, a4);
}

DECLARE_HOOK(int, __fastcall, CPlayer_ProcessMessage_MsgRestartStage, 0xE76810, int* in_pThis, void* EDX, int* in_pMessage)
{
	auto pPlayerSpeedContext = Sonic::Player::CPlayerSpeedContext::GetInstance();

	auto isUseLastCheckpointScore = (Configuration::IsRestoreLastCheckpointScore &&
		pPlayerSpeedContext->m_pStateFlag->m_Flags[pPlayerSpeedContext->eStateFlag_Dead] &&
		StatisticsProvider::GetStatistics().TotalPointMarkers > 0);

	ScoreProvider::Reset(isUseLastCheckpointScore);

	g_isResultsHooked = !ScoreHud::IsProhibitedStage();

	static const char* s_pCsdProjectDefault = "ui_gameplay_default";
	static const char* s_pCsdProjectLowPadding = "ui_gameplay_low_padding";
	static const char* s_pCsdProjectHighPadding = "ui_gameplay_high_padding";

	const char* pCsdProjectName{ s_pCsdProjectDefault };

	if (!Configuration::IsCustomUI)
	{
		if (cmf::sys::utils::StringHelper::GetDigits(Configuration::ScoreFormat) <= 6)
		{
			// Use Score Generations' HUD XNCP for six digit padding.
			pCsdProjectName = s_pCsdProjectLowPadding;
		}
		else
		{
			// Use Score Generations' HUD XNCP for high amounts of padding.
			pCsdProjectName = s_pCsdProjectHighPadding;
		}
	}

	// Redirect CSD project.
	WRITE(0x109D669, const char*, pCsdProjectName);

	return original_CPlayer_ProcessMessage_MsgRestartStage(in_pThis, EDX, in_pMessage);
}

DECLARE_HOOK(void, __fastcall, CHudSonicStage_UpdateSerial_ScoreHud, 0x1098A50, void* in_pThis, void* EDX, const Hedgehog::Universe::SUpdateInfo& in_rUpdateInfo)
{
	struct CHudSonicStage
	{
		INSERT_PADDING(0x128);
		Chao::CSD::RCPtr<Chao::CSD::CScene> m_rcPinScore{};
	};

	auto pHudSonicStage = (CHudSonicStage*)in_pThis;

	if (!ScoreHud::IsProhibitedStage())
	{
		if (!ScoreHud::IsCasinoNightZone())
		{
			struct MsgSetPinballHud
			{
				INSERT_PADDING(0x10);
				uint32_t m_Flags;
				uint32_t m_Score;
				INSERT_PADDING(0x08);
			};

			DECLARE_FUNCTION_PTR(void, __thiscall, fpProcessMsgSetPinballHud, 0x1095D40, void* in_pThis, const MsgSetPinballHud& in_rMsgSetPinballHud);

			MsgSetPinballHud msgSetPinballHud{};
			msgSetPinballHud.m_Flags = 1;
			msgSetPinballHud.m_Score = ScoreProvider::GetCurrentScore();

			fpProcessMsgSetPinballHud(in_pThis, msgSetPinballHud);
		}

		pHudSonicStage->m_rcPinScore->SetHideFlag(!ScoreHud::IsVisible);
	}

	original_CHudSonicStage_UpdateSerial_ScoreHud(in_pThis, EDX, in_rUpdateInfo);
}

DECLARE_HOOK(bool, __fastcall, CScriptImpl_Init, 0x1105120, void* in_pThis)
{
	return ScoreHud::IsMission = original_CScriptImpl_Init(in_pThis);
}

DECLARE_ASM_HOOK_32(CStateDisplayGameOver_Ctor, 0x584777)
{
	static void* s_interruptAddress = (void*)0x6621A0;
	static void* s_returnAddress = (void*)0x58477C;

	__asm
	{
		call [s_interruptAddress]
		call ScoreProvider::Reset
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(Hud_CPause_CStateWindow_Exit, 0x42AD71)
{
	static void* s_interruptAddress = (void*)0x6AE910;
	static void* s_returnAddress = (void*)0x42AD76;

	__asm
	{
		call [s_interruptAddress]
		call ScoreProvider::Reset
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(CGameplayFlowStage_CStateGoalFadeBefore_CalculateResults, 0xD5A18C)
{
	static void* s_interruptAddress = (void*)0x10B3DB0;
	static void* s_returnAddress = (void*)0xD5A191;

	if (g_isResultsHooked)
	{
		__asm
		{
			call ScoreProvider::ComputeResults
			lea  eax, ScoreProvider::m_Results
		}
	}
	else
	{
		__asm call [s_interruptAddress]
	}

	__asm jmp [s_returnAddress]
}

bool ScoreHud::IsCasinoNightZone()
{
	if (Configuration::IsOverrideCasinoNightZone)
		return false;

	return strcmp(g_pStageID, "cnz100") == 0;
}

bool ScoreHud::IsProhibitedStage()
{
	auto& rRankTables = TableProvider::GetRankTables();

	// Forbid missions, Casino Night and stages lacking rank tables
	// from using the score counter.
	if (IsMission || IsCasinoNightZone() || rRankTables.find(g_pStageID) == rRankTables.end())
		return true;

	// Check if the current stage ID matches any in the prohibition list.
	for (const auto& rStage : Configuration::ProhibitedStages)
	{
		if (strcmp(g_pStageID, rStage.c_str()) == 0)
			return true;
	}

	return false;
}

void ScoreHud::Install()
{
	INSTALL_HOOK(CHudSonicStage_UpdateSerial_ScoreHud);
	INSTALL_HOOK(CScriptImpl_Init);
	INSTALL_HOOK(IsPerfectBonus);
	INSTALL_HOOK(MsgChangeResultState_Ctor);
	INSTALL_HOOK(CPlayer_ProcessMessage_MsgRestartStage);

	INSTALL_ASM_HOOK_32(CStateDisplayGameOver_Ctor);
	INSTALL_ASM_HOOK_32(Hud_CPause_CStateWindow_Exit);
	INSTALL_ASM_HOOK_32(CGameplayFlowStage_CStateGoalFadeBefore_CalculateResults);

	// Always create score counter CSD scene.
	WRITE_NOP(0x109C1DA, 2);

	// Disable score cap in Casino Night Zone.
	WRITE_JUMP(0x1095D70, 0x1095D77);

	// Disable score cap in results.
	WRITE_JUMP(0x10B4012, 0x10B401E);

	// Remove next rank dialog in results.
	WRITE_JUMP(0x10B66F0, 0x10B6700);
	WRITE_JUMP(0x10B7DAE, 0x10B7DB7);

	// Register negative rank values as D rank.
	WRITE(0x10B92BE, uint8_t, 0x7D);
}
