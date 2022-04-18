#pragma once

#include <Helpers.h>
#include <Hedgehog.h>

namespace BlueBlurCommon
{
	typedef void CSonicContext;
	CSonicContext** const PlayerContext = (CSonicContext**)0x1E5E2F0;
	CSonicContext** const ModernSonicContext = (CSonicContext**)0x1E5E2F8;
	CSonicContext** const ClassicSonicContext = (CSonicContext**)0x1E5E304;
	CSonicContext** const SuperSonicContext = (CSonicContext**)0x1E5E310;

	void** const GameDocument = (void**)0x1E0BE5C;

	inline void PlayMusic(char const* cueName, float fadeInTime)
	{
		FUNCTION_PTR(unsigned int, __stdcall, PlayAudioFromCueName, 0xD62440, void* gameDocument, Hedgehog::Base::CSharedString& cueName, float fadeInTime);

		Hedgehog::Base::CSharedString name = Hedgehog::Base::CSharedString(cueName);
		PlayAudioFromCueName(*GameDocument, name, fadeInTime);
	}

	inline void StopMusic(char const* cueName, float fadeOutTime)
	{
		FUNCTION_PTR(int, __stdcall, StopAudioFromCueName, 0xD61E40, void* gameDocument, Hedgehog::Base::CSharedString& cueName, float fadeOutTime);

		Hedgehog::Base::CSharedString name = Hedgehog::Base::CSharedString(cueName);
		StopAudioFromCueName(*GameDocument, name, fadeOutTime);
	}

	inline float* GetBoost()
	{
		if (!*PlayerContext)
			return 0;

		return (float*)((uint32_t)*PlayerContext + 0x5BC);
	}
};