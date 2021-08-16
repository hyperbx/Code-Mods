int homingChainCount = 0;
int multipliedHomingChainBonus = 0;
int slamCount = 0;
int multipliedSlamBonus = 0;

int MultiplierListener::AddHomingChainBonus()
{
	int scoreToReward = 0;
	int limit = Tables::bonusTable.homingChainBonusLimit;

	if (!PlayerListener::isGrounded)
	{
		if (homingChainCount == 1)
		{
			// Set pre-multiplied bonus total.
			scoreToReward += multipliedHomingChainBonus = Tables::bonusTable.homingChainBonus;
		}
		else if (homingChainCount > 1)
		{
			// Increase by configured multiplier.
			scoreToReward += multipliedHomingChainBonus *= Tables::multiplierTable.homingChainMultiplier;
		}

		// Increment homing chain count.
		homingChainCount++;
	}

#if _DEBUG
	printf("[Score Generations] Homing Chain Bonus = %d\n", scoreToReward);
#endif

	return limit == 0 ? scoreToReward : clamp(scoreToReward, 0, limit);
}

void MultiplierListener::ResetHomingChainBonus()
{
	homingChainCount = 0;
	multipliedHomingChainBonus = 0;
}

int MultiplierListener::AddSlamBonus()
{
	int scoreToReward = 0;
	int limit = Tables::bonusTable.slamBonusLimit;

	if (PlayerListener::isGrounded)
	{
		if (slamCount == 1)
		{
			// Set pre-multiplied bonus total.
			scoreToReward += multipliedSlamBonus = Tables::bonusTable.slamBonus;
		}
		else if (slamCount > 1)
		{
			// Increase by configured multiplier.
			scoreToReward += multipliedSlamBonus *= Tables::multiplierTable.slamMultiplier;
		}

		// Increment slam count.
		slamCount++;
	}

#if _DEBUG
	printf("[Score Generations] Slam Bonus = %d\n", scoreToReward);
#endif

	return limit == 0 ? scoreToReward : clamp(scoreToReward, 0, limit);
}

void MultiplierListener::ResetSlamBonus()
{
	slamCount = 0;
	multipliedSlamBonus = 0;
}