#pragma once

#include <BlueBlur.h>
#include <Helpers.h>

#define CONTEXT BlueBlurCommon::GetContext()
#define SONIC_CONTEXT BlueBlurCommon::GetSonicContext()
#define SONIC_CLASSIC_CONTEXT BlueBlurCommon::GetSonicClassicContext()
#define SONIC_SUPER_CONTEXT BlueBlurCommon::GetSonicSpContext()

#define CHECK_CONTEXT_SAFE(returnValue) if (CONTEXT == nullptr) return returnValue;

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
		CHECK_CONTEXT_SAFE(false);
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

	static bool IsBossSuper()
	{
		return SONIC_SUPER_CONTEXT != nullptr;
	}

	static bool IsSuper()
	{
		return HasFlag(CONTEXT->eStateFlag_InvokeSuperSonic);
	}

	static bool IsGrounded()
	{
		CHECK_CONTEXT_SAFE(false);
		return CONTEXT->m_Grounded;
	}

	static void* CreateParticle
	(
		void* pContext,
		boost::shared_ptr<void>& handle,
		void* pMatrixTransformNode,
		Hedgehog::Base::CSharedString const& name,
		uint32_t flag
	)
	{
		static void* const pCGlitterCreate = (void*)0xE73890;

		__asm
		{
			push flag
			push name
			push pMatrixTransformNode
			mov  eax, pContext
			mov  esi, handle

			call [pCGlitterCreate]
		}
	}

	static void DestroyParticle
	(
		void* pContext,
		boost::shared_ptr<void>& handle,
		bool instantStop
	)
	{
		static void* const pCGlitterEnd  = (void*)0xE72650;
		static void* const pCGlitterKill = (void*)0xE72570;

		__asm
		{
			mov  eax, [handle]
			mov  ebx, [eax + 4]
			push ebx
			test ebx, ebx
			jz	 noIncrement
			mov	 edx, 1
			add	 ebx, 4
			lock xadd[ebx], edx

		noIncrement:
			mov  ebx, [eax]
			push ebx
			mov  eax, pContext
			cmp  instantStop, 0
			jnz  jump

			call [pCGlitterEnd]

			jmp end

		jump:
			call [pCGlitterKill]

		end:
		}

		handle = nullptr;
	}

	static const float GetVelocity()
	{
		CHECK_CONTEXT_SAFE(0.0f);
		return CONTEXT->m_Velocity.norm();
	}

	static const char* GetStageID()
	{
		return (const char*)0x1E774D4;
	}

	static const void PlayMusic(char const* cueName, float fadeInTime)
	{
		FUNCTION_PTR(unsigned int, __stdcall, PlayAudioFromCueName, 0xD62440, Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> gameDocument, const Hedgehog::Base::CSharedString& cueName, float fadeInTime);
		PlayAudioFromCueName(CONTEXT->m_pPlayer->GetGameDocument(), cueName, fadeInTime);
	}

	static const void StopMusic(char const* cueName, float fadeOutTime)
	{
		FUNCTION_PTR(int, __stdcall, StopAudioFromCueName, 0xD61E40, Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> gameDocument, const Hedgehog::Base::CSharedString& cueName, float fadeOutTime);
		StopAudioFromCueName(CONTEXT->m_pPlayer->GetGameDocument(), cueName, fadeOutTime);
	}
};