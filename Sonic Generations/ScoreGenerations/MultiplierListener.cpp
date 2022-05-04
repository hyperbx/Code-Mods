int homingChainCount = 0;
float multipliedHomingChainBonus = 0;
int slamCount = 0;
float multipliedSlamBonus = 0;

int MultiplierListener::AddHomingChainBonus()
{
	int scoreToReward = 0;
	int limit = TableListener::bonusTable.homingChainBonusLimit;

	if (!CONTEXT->m_Grounded)
	{
		if (homingChainCount == 1)
		{
			// Set pre-multiplied bonus total.
			scoreToReward += multipliedHomingChainBonus = TableListener::bonusTable.homingChainBonus;
		}
		else if (homingChainCount > 1)
		{
			// Increase by configured multiplier.
			scoreToReward += multipliedHomingChainBonus *= TableListener::multiplierTable.homingChainMultiplier;
		}

		// Increment homing chain count.
		homingChainCount++;
	}

#if _DEBUG
	printf("[Score Generations] Homing Chain Bonus = %d\n", scoreToReward);
#endif

	return limit == 0 ? scoreToReward : std::clamp(scoreToReward, 0, limit);
}

void MultiplierListener::ResetHomingChainBonus()
{
	homingChainCount = 0;
	multipliedHomingChainBonus = 0;
}

int MultiplierListener::AddSlamBonus()
{
	int scoreToReward = 0;
	int limit = TableListener::bonusTable.slamBonusLimit;

	if (CONTEXT->m_Grounded)
	{
		if (slamCount == 1)
		{
			// Set pre-multiplied bonus total.
			scoreToReward += multipliedSlamBonus = TableListener::bonusTable.slamBonus;
		}
		else if (slamCount > 1)
		{
			// Increase by configured multiplier.
			scoreToReward += multipliedSlamBonus *= TableListener::multiplierTable.slamMultiplier;
		}

		// Increment slam count.
		slamCount++;
	}

#if _DEBUG
	printf("[Score Generations] Slam Bonus = %d\n", scoreToReward);
#endif

	return limit == 0 ? scoreToReward : std::clamp(scoreToReward, 0, limit);
}

void MultiplierListener::ResetSlamBonus()
{
	slamCount = 0;
	multipliedSlamBonus = 0;
}