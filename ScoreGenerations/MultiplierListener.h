#pragma once

class MultiplierListener
{
public:
	/// <summary>
	/// Calculates the homing chain bonus gradually and returns the result.
	/// </summary>
	static int AddHomingChainBonus();

	/// <summary>
	/// Resets the homing chain bonus statistics.
	/// </summary>
	static void ResetHomingChainBonus();

	/// <summary>
	/// Calculates the slam bonus gradually and returns the result.
	/// </summary>
	static int AddSlamBonus();

	/// <summary>
	/// Resets the slam bonus statistics.
	/// </summary>
	static void ResetSlamBonus();
};

