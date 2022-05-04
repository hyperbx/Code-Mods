int homingChainCount = 0;
float multipliedHomingChainBonus = 0;
int slamCount = 0;
float multipliedSlamBonus = 0;
int trickCount = 0;
float multipliedTrickBonus = 0;
std::string trickAnim;

int MultiplierListener::GetHomingChainBonus()
{
	int scoreToReward = 0;
	int limit = TableListener::bonusTable.homingChainBonusLimit;

	if (!CONTEXT->m_Grounded)
	{
		if (homingChainCount == 1)
		{
			// Set pre-multiplied bonus total.
			scoreToReward = multipliedHomingChainBonus = TableListener::bonusTable.homingChainBonus;
		}
		else if (homingChainCount > 1)
		{
			// Increase by configured multiplier.
			scoreToReward = multipliedHomingChainBonus *= TableListener::multiplierTable.homingChainMultiplier;
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
	homingChainCount		   = 0;
	multipliedHomingChainBonus = 0;
}

int MultiplierListener::GetSlamBonus()
{
	int scoreToReward = 0;
	int limit = TableListener::bonusTable.slamBonusLimit;

	if (CONTEXT->m_Grounded)
	{
		if (slamCount == 1)
		{
			// Set pre-multiplied bonus total.
			scoreToReward = multipliedSlamBonus = TableListener::bonusTable.slamBonus;
		}
		else if (slamCount > 1)
		{
			// Increase by configured multiplier.
			scoreToReward = multipliedSlamBonus *= TableListener::multiplierTable.slamMultiplier;
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
	slamCount			= 0;
	multipliedSlamBonus = 0;
}

int MultiplierListener::GetTrickBonus(int trickScore)
{
	int scoreToReward = 0;
	int limit = TableListener::bonusTable.trickBonusLimit;

	// Remove the last character from the animation string, as it's just an index.
	std::string currentTrickAnim = StringHelper::RemoveLastCharacter(std::string(CONTEXT->GetCurrentAnimationName().c_str()));

	if (trickCount == 0)
	{
		// Set last trick animation, so we can compare for the next trick.
		trickAnim = currentTrickAnim;

		// Set pre-multiplied bonus total.
		scoreToReward = multipliedTrickBonus = trickScore;

		// Increment trick count.
		trickCount++;

		goto Exit;
	}

	/* This checks if the current trick is the same as the last.
	   If so, do not reward any multiplied bonuses. When the player
	   switches to another direction to perform a different trick
	   animation, this bonus will begin to multiply. */
	if (StringHelper::Compare(trickAnim, currentTrickAnim))
	{
		// Reset pre-multiplied bonus total.
		scoreToReward = multipliedTrickBonus = trickScore;
	}
	else
	{
		trickAnim = currentTrickAnim;

		// Increase by configured multiplier.
		scoreToReward = multipliedTrickBonus *= TableListener::multiplierTable.trickMultiplier;
	}

Exit:
#if _DEBUG
	printf("[Score Generations] Trick Bonus = %d\n", scoreToReward);
#endif

	return limit == 0 ? scoreToReward : std::clamp(scoreToReward, 0, limit);
}

void MultiplierListener::ResetTrickBonus()
{
	trickCount = 0;
	trickAnim  = "";
}