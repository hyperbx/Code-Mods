#include "ScoreListener.h"
#include "SonicHud.h"

// Declare class variables.
unsigned int ScoreListener::score = 0;

/// <summary>
/// Resets all statistics used for score calculation.
/// </summary>
void ScoreListener::Reset()
{
	SonicHud::elapsedTime = 0;
	SonicHud::totalRingCount = 0;
	SonicHud::ringCount = 0;

	score = 0;

#if _DEBUG
	printf("[Score Generations] Score has been reset...\n");
	printf("[Score Generations] elapsedTime = %d\n", SonicHud::elapsedTime);
	printf("[Score Generations] totalRingCount = %d\n", SonicHud::totalRingCount);
	printf("[Score Generations] ringCount = %d\n", SonicHud::ringCount);
	printf("[Score Generations] score = %d\n", score);
#endif
}

/// <summary>
/// Calculates the bonuses and adds them to the total score.
/// </summary>
void ScoreListener::Bonus()
{
	// Add ring bonus (Forces).
	ScoreListener::score += SonicHud::ringCount * 300;
}

/// <summary>
/// Rewards the player with score based on the input register.
/// </summary>
/// <param name="id">Identifier from ECX.</param>
void __fastcall ScoreListener::Reward(ScoreType type)
{
	int scoreToReward = 0;

	switch (type)
	{
		case Ring:
		case Object:
			scoreToReward = 100;
			break;

		case SuperRing:
			scoreToReward = 1000;
			break;

		case Enemy:
			scoreToReward = 1500;
			break;

		case PointMarker:
		case ItemBox:
			scoreToReward = 5000;
			break;

		case RainbowRing:
			scoreToReward = 10000;
			break;

		case RedRing:
			scoreToReward = 30000;
			break;
	}

	// Clamp the maximum score.
	if ((score + scoreToReward) <= 999999)
		score += scoreToReward;
	else
		score = 999999;

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}