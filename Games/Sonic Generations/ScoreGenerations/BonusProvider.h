#pragma once

namespace ScoreGenerations
{
	class BonusProvider
	{
	public:
		static int GetHomingChainBonus();
		static int GetSlamBonus();
		static int GetTrickBonus(int in_trickScore);

		static void ResetHomingChainBonus();
		static void ResetSlamBonus();
		static void ResetTrickBonus();
	};
}
