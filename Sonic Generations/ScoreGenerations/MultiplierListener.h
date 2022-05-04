#pragma once

class MultiplierListener
{
public:
	/// <summary>
	/// Calculates the homing chain bonus gradually and returns the result.
	/// </summary>
	static int GetHomingChainBonus();

	/// <summary>
	/// Resets the homing chain bonus statistics.
	/// </summary>
	static void ResetHomingChainBonus();

	/// <summary>
	/// Calculates the slam bonus gradually and returns the result.
	/// </summary>
	static int GetSlamBonus();

	/// <summary>
	/// Resets the slam bonus statistics.
	/// </summary>
	static void ResetSlamBonus();

	/// <summary>
	/// Calculates the trick bonus gradually and returns the result.
	/// </summary>
	static int GetTrickBonus(int trickScore);

	/// <summary>
	/// Resets the trick bonus statistics.
	/// </summary>
	static void ResetTrickBonus();
};

