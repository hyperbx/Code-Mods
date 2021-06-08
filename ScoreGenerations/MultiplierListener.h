#pragma once

class MultiplierListener
{
public:
	/// <summary>
	/// Calculates the homing chain bonus gradually and returns the result.
	/// </summary>
	static int AddHomingChainBonus(int scoreToReward);

	/// <summary>
	/// Resets the homing chain bonus statistics.
	/// </summary>
	static void ResetHomingChainBonus();
};

