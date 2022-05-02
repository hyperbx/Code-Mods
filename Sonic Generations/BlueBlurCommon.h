#pragma once

#include <BlueBlur.h>
#include <Helpers.h>

#define CONTEXT BlueBlurCommon::GetContext()
#define SONIC_CONTEXT BlueBlurCommon::GetSonicContext()
#define SONIC_CLASSIC_CONTEXT BlueBlurCommon::GetSonicClassicContext()
#define SONIC_SUPER_CONTEXT BlueBlurCommon::GetSonicSpContext()

class BlueBlurCommon
{
public:
	static Sonic::Player::CPlayerSpeedContext* GetContext()
	{
		return Sonic::Player::CPlayerSpeedContext::GetInstance();
	}

	static Sonic::Player::CSonicContext* GetSonicContext()
	{
		return Sonic::Player::CSonicContext::GetInstance();
	}

	static Sonic::Player::CSonicClassicContext* GetSonicClassicContext()
	{
		return Sonic::Player::CSonicClassicContext::GetInstance();
	}

	static Sonic::Player::CSonicSpContext* GetSonicSpContext()
	{
		return Sonic::Player::CSonicSpContext::GetInstance();
	}

	static bool HasFlag(Sonic::Player::CPlayerSpeedContext::EStateFlag flag)
	{
		return CONTEXT->m_pStateFlag->m_Flags[flag];
	}

	static bool IsModern()
	{
		return SONIC_CONTEXT != nullptr;
	}

	static bool IsClassic()
	{
		return SONIC_CLASSIC_CONTEXT != nullptr;
	}

	static bool IsSuper()
	{
		return HasFlag(CONTEXT->eStateFlag_InvokeSuperSonic);
	}

	static bool IsBossSuper()
	{
		return SONIC_SUPER_CONTEXT != nullptr;
	}

	static const void PlayMusic(char const* cueName, float fadeInTime)
	{
		FUNCTION_PTR(unsigned int, __stdcall, PlayAudioFromCueName, 0xD62440, Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> gameDocument, Hedgehog::Base::CSharedString& cueName, float fadeInTime);

		Hedgehog::Base::CSharedString name = Hedgehog::Base::CSharedString(cueName);
		PlayAudioFromCueName(CONTEXT->m_pPlayer->GetGameDocument(), name, fadeInTime);
	}

	static const void StopMusic(char const* cueName, float fadeOutTime)
	{
		FUNCTION_PTR(int, __stdcall, StopAudioFromCueName, 0xD61E40, Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> gameDocument, Hedgehog::Base::CSharedString& cueName, float fadeOutTime);

		Hedgehog::Base::CSharedString name = Hedgehog::Base::CSharedString(cueName);
		StopAudioFromCueName(CONTEXT->m_pPlayer->GetGameDocument(), name, fadeOutTime);
	}

	static const char* GetStageID()
	{
		return (const char*)0x1E774D4;
	}

	static const float GetVelocity()
	{
		return CONTEXT->m_Velocity.norm();
	}
};