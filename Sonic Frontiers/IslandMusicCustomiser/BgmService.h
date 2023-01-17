#pragma once

class BgmService
{
	static Configuration::EBgmType ms_LastBgmType;

public:
	static void Install();

	static Configuration::EBgmType GetRandomBgmType(int in_min, int in_max)
	{
		int result;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(in_min, in_max);

		if (Configuration::s_ExcludedBgm.size() == in_max - in_min || Configuration::s_ExcludedBgm.size() == in_max - in_min + 1)
		{
			printf("[IslandMusicCustomiser] Exclusion list contains entire randomisation source!\n");

			return Configuration::bgm_none;
		}

		// Keep randomising until we have a unique and non-excluded result.
		do
		{
			result = dis(gen);
		}
		while
		(
			std::find
			(
				Configuration::s_ExcludedBgm.begin(),
				Configuration::s_ExcludedBgm.end(),
				result
			)
			!= Configuration::s_ExcludedBgm.end()
		);

		return (Configuration::EBgmType)result;
	}

	static Configuration::EBgmType GetBgmType(Configuration::EBgmType in_bgmType, Configuration::EBgmRandomType in_randomType)
	{
		Configuration::EBgmType result;

		switch (in_randomType)
		{
			case Configuration::Any:
				result = GetRandomBgmType(Configuration::bgm_ending1, Configuration::bgm_w3r01_7);
				break;

			case Configuration::IslandAny:
				result = GetRandomBgmType(Configuration::bgm_w1r02_1, Configuration::bgm_w3r01_7);
				break;

			case Configuration::KronosAny:
				result = GetRandomBgmType(Configuration::bgm_w1r02_1, Configuration::bgm_w1r02_7);
				break;

			case Configuration::AresAny:
				result = GetRandomBgmType(Configuration::bgm_w2r01_1, Configuration::bgm_w2r01_7);
				break;

			case Configuration::ChaosAny:
				result = GetRandomBgmType(Configuration::bgm_w3r01_1, Configuration::bgm_w3r01_7);
				break;

			default:
				return in_bgmType;
		}

		if (result == ms_LastBgmType)
		{
#if _DEBUG
			printf("[IslandMusicCustomiser] Index %d was played previously - rerolling!\n", result);
#endif

			return GetBgmType(in_bgmType, in_randomType);
		}

		ms_LastBgmType = result;

		return result;
	}
};