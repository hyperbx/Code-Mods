#pragma once

#include <Helpers.h>
#include <Hedgehog.h>

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