#include "BonusProvider.h"
#include "ScoreProvider.h"
#include "TableProvider.h"

using namespace ScoreGenerations;

static int g_homingChainCount{};
static float g_homingChainBonus{};

static int g_slamCount{};
static float g_slamBonus{};

static int g_trickCount{};
static float g_trickBonus{};
static std::string g_trickAnim{};

static float g_superSonicDeltaTimer{};
static float g_slamBonusDeltaTimer{};

DECLARE_STATIC_HOOK(void, __fastcall, CHudSonicStage_UpdateSerial_BonusProvider, 0x1098A50, Sonic::CGameObject* in_pThis, void* EDX, const Hedgehog::Universe::SUpdateInfo& in_rUpdateInfo)
{
	auto pPlayerSpeedContext = Sonic::Player::CPlayerSpeedContext::GetInstance();

	if (!pPlayerSpeedContext)
	{
		original_CHudSonicStage_UpdateSerial_BonusProvider(in_pThis, EDX, in_rUpdateInfo);
		return;
	}

	auto& rTimerTable = TableProvider::GetTimerTable();

	g_superSonicDeltaTimer += in_rUpdateInfo.DeltaTime;
	g_slamBonusDeltaTimer += in_rUpdateInfo.DeltaTime;

	if (g_superSonicDeltaTimer > rTimerTable.SuperSonicTimer)
	{
		g_superSonicDeltaTimer = 0;

		// Reward score every two seconds if the player is Super Sonic.
		if (pPlayerSpeedContext->StateFlag(eStateFlag_InvokeSuperSonic))
			ScoreProvider::AddScoreByType(ScoreType::Super);
	}

	if (pPlayerSpeedContext->m_Grounded)
	{
		// Reset bonuses if the player is grounded.
		BonusProvider::ResetHomingChainBonus();
		BonusProvider::ResetTrickBonus();

		if (g_slamBonusDeltaTimer > rTimerTable.SlamTimer)
		{
			g_slamBonusDeltaTimer = 0;

			// Reset the slam bonus if the timer runs out.
			BonusProvider::ResetSlamBonus();
		}
	}
	else
	{
		// Reset the slam bonus if the player isn't grounded.
		BonusProvider::ResetSlamBonus();
	}

	original_CHudSonicStage_UpdateSerial_BonusProvider(in_pThis, EDX, in_rUpdateInfo);
}

int BonusProvider::GetHomingChainBonus()
{
	auto* pPlayerSpeedContext = Sonic::Player::CPlayerSpeedContext::GetInstance();
	auto& rBonusTable = TableProvider::GetBonusTable();

	auto score = 0;
	auto limit = rBonusTable.HomingChainBonusLimit;

	if (pPlayerSpeedContext && !pPlayerSpeedContext->m_Grounded)
	{
		if (g_homingChainCount == 1)
		{
			// Set pre-multiplied bonus total.
			score = g_homingChainBonus = rBonusTable.HomingChainBonus;
		}
		else if (g_homingChainCount > 1)
		{
			// Increase by configured multiplier.
			score = g_homingChainBonus *= TableProvider::GetMultiplierTable().HomingChainMultiplier;
		}

		g_homingChainCount++;
	}

	LOGFN_UTILITY("Homing Chain Bonus: {}", score);

	return limit == 0 ? score : std::clamp(score, 0, limit);
}

int BonusProvider::GetSlamBonus()
{
	auto* pPlayerSpeedContext = Sonic::Player::CPlayerSpeedContext::GetInstance();
	auto& rBonusTable = TableProvider::GetBonusTable();

	auto score = 0;
	auto limit = rBonusTable.SlamBonusLimit;

	if (pPlayerSpeedContext && pPlayerSpeedContext->m_Grounded)
	{
		if (g_slamCount == 1)
		{
			// Set pre-multiplied bonus total.
			score = g_slamBonus = rBonusTable.SlamBonus;
		}
		else if (g_slamCount > 1)
		{
			// Increase by configured multiplier.
			score = g_slamBonus *= TableProvider::GetMultiplierTable().SlamMultiplier;
		}

		g_slamCount++;
	}

	LOGFN_UTILITY("Slam Bonus: {}", score);

	return limit == 0 ? score : std::clamp(score, 0, limit);
}

int BonusProvider::GetTrickBonus(int in_trickScore)
{
	auto pPlayerSpeedContext = Sonic::Player::CPlayerSpeedContext::GetInstance();
	auto score = 0;
	auto limit = TableProvider::GetBonusTable().TrickBonusLimit;

	if (pPlayerSpeedContext)
	{
		auto currentTrickAnim = cmf::sys::utils::StringHelper::RemoveLast(std::string(pPlayerSpeedContext->GetCurrentAnimationName().c_str()));

		if (g_trickCount == 0)
		{
			// Set last trick animation, so we can compare for the next trick.
			g_trickAnim = currentTrickAnim;

			// Set pre-multiplied bonus total.
			score = g_trickBonus = in_trickScore;

			g_trickCount++;
		}
		else
		{
			// This checks if the current trick is the same as the last.
			// If so, do not reward any multiplied bonuses. When the player
			// switches to another direction to perform a different trick
			// animation, this bonus will begin to multiply.
			if (g_trickAnim == currentTrickAnim)
			{
				// Reset pre-multiplied bonus total.
				score = g_trickBonus = in_trickScore;
			}
			else
			{
				g_trickAnim = currentTrickAnim;

				// Increase by configured multiplier.
				score = g_trickBonus *= TableProvider::GetMultiplierTable().TrickMultiplier;
			}
		}
	}

	LOGFN_UTILITY("Trick Bonus: {}", score);

	return limit == 0 ? score : std::clamp(score, 0, limit);
}

void BonusProvider::ResetHomingChainBonus()
{
	g_homingChainCount = 0;
	g_homingChainBonus = 0;
}

void BonusProvider::ResetSlamBonus()
{
	g_slamCount = 0;
	g_slamBonus = 0;
}

void BonusProvider::ResetTrickBonus()
{
	g_trickCount = 0;
	g_trickAnim = "";
}
