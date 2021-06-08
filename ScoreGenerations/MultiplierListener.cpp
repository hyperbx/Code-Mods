int homingChainCount = 0;
int multipliedHomingChainBonus = 0;

int MultiplierListener::AddHomingChainBonus(int scoreToReward)
{
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

	return scoreToReward;
}

void MultiplierListener::ResetHomingChainBonus()
{
	homingChainCount = 0;
	multipliedHomingChainBonus = 0;
}