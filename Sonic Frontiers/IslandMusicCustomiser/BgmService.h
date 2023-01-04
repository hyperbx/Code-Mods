#pragma once

class BgmService
{
	static Configuration::EBgmType m_bgmStack[7];

public:
	static void Install();

	static int GetRandom(int in_min, int in_max)
	{
		static bool first = true;

		if (first)
		{
			srand(time(0));

			first = false;
		}

		return in_min + rand() % ((in_max + 1) - in_min);
	}

	static void PushBgmType(Configuration::EBgmType in_bgmType)
	{
		for (int i = 5; i >= 0; i--)
		{
			// Shift current array element to the right.
			m_bgmStack[i + 1] = m_bgmStack[i];

			// Push current type to the stack.
			m_bgmStack[i] = in_bgmType;
		}

#if _DEBUG
		for (int i = 0; i <= 5; i++)
			printf("[IslandMusicRandomiser] m_bgmStack[%d]: %d\n", i, m_bgmStack[i]);
#endif
	}

	static bool IsBgmRandomUnique(Configuration::EBgmType in_bgmType)
	{
		for (int i = 0; i <= 5; i++)
		{
			if (m_bgmStack[i] == in_bgmType)
				return false;
		}

		return true;
	}

	static Configuration::EBgmType GetBgmType(Configuration::EBgmType in_bgmType, Configuration::EBgmRandomType in_randomType)
	{
		Configuration::EBgmType result;

		switch (in_randomType)
		{
			case Configuration::Any:
				result = (Configuration::EBgmType)GetRandom(Configuration::bgm_ending1, Configuration::bgm_w3r01_7);
				break;

			case Configuration::IslandAny:
				result = (Configuration::EBgmType)GetRandom(Configuration::bgm_w1r02_1, Configuration::bgm_w3r01_7);
				break;

			case Configuration::KronosAny:
				result = (Configuration::EBgmType)GetRandom(Configuration::bgm_w1r02_1, Configuration::bgm_w1r02_7);
				break;

			case Configuration::AresAny:
				result = (Configuration::EBgmType)GetRandom(Configuration::bgm_w2r01_1, Configuration::bgm_w2r01_7);
				break;

			case Configuration::ChaosAny:
				result = (Configuration::EBgmType)GetRandom(Configuration::bgm_w3r01_1, Configuration::bgm_w3r01_7);
				break;

			default:
				return in_bgmType;
		}

		if (!IsBgmRandomUnique(result))
		{
#if _DEBUG
			printf("[IslandMusicRandomiser] %d is not unique - rerolling!\n", result);
#endif

			// Randomise again so we always have a unique track.
			return GetBgmType(in_bgmType, in_randomType);
		}
		else
		{
			PushBgmType(result);
		}

		return result;
	}
};