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
	static void** GetPlayerContextSingleton()
	{
		return (void**)0x1E5E2F0;
	}

public:
	// https://github.com/brianuuu/DllMods/blob/master/Dependencies/Common.h
	enum ImpulseType : uint32_t
	{
		None,
		DashPanel,
		UnknownCase_0x02,
		UnknownCase_0x03,
		UnknownCase_0x04,
		UnknownCase_0x05,
		JumpBoard,
		JumpBoardSpecial,
		DashRing,
		DashRingR,
		LookBack,
		HomingAttackAfter,
		BoardJumpBoard,
		UnknownCase_0x0D,
		BoardJumpAdlibTrickA,
		BoardJumpAdlibTrickB,
		BoardJumpAdlibTrickC
	};

	// https://github.com/brianuuu/DllMods/blob/master/Dependencies/Common.h
	struct MsgApplyImpulse
	{
		INSERT_PADDING(0x10);

		Eigen::Vector3f m_position;

		INSERT_PADDING(0x04);

		Eigen::Vector3f m_impulse;

		INSERT_PADDING(0x04);

		float m_outOfControl;

		INSERT_PADDING(0x04);

		ImpulseType m_impulseType;

		float m_keepVelocityTime;

		bool m_notRelative; // if false, add impulse direction relative to Sonic
		bool m_snapPosition; // snap Sonic to m_position

		INSERT_PADDING(0x03);

		bool m_pathInterpolate; // linked to 80

		INSERT_PADDING(0x0A);

		Eigen::Vector3f m_unknown80; // related to position interpolate?

		INSERT_PADDING(0x04);

		float m_alwaysMinusOne; // seems to be always -1.0f

		INSERT_PADDING(0x0C);
	};

	static Sonic::Player::CPlayerSpeedContext* GetContext()
	{
		return Sonic::Player::CPlayerSpeedContext::GetInstance();
	}

	static Sonic::Player::CSonicContext* GetSonicContext()
	{
		return Sonic::Player::CSonicContext::GetInstance();
	}

	static void* GetSonicContextPointer()
	{
		if (!*GetPlayerContextSingleton())
			return 0;

		return *(void**)((uint32_t)*GetPlayerContextSingleton() + 0x110);
	}

	static Sonic::Player::CSonicClassicContext* GetSonicClassicContext()
	{
		return Sonic::Player::CSonicClassicContext::GetInstance();
	}

	static Sonic::Player::CSonicSpContext* GetSonicSpContext()
	{
		return Sonic::Player::CSonicSpContext::GetInstance();
	}

	static void* GetMatrixNode()
	{
		return (void*)((uint32_t)CONTEXT + 0x30);
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

	static void ProcessImpulse(MsgApplyImpulse const& message)
	{
		FUNCTION_PTR(void, __thiscall, ProcessPlayerMsgAddImpulse, 0xE6CFA0, void* _this, void* message);
		{
			alignas(16) MsgApplyImpulse msgApplyImpulse = message;
			void* player = *(void**)((uint32_t)*GetPlayerContextSingleton() + 0x110);

			ProcessPlayerMsgAddImpulse(player, &msgApplyImpulse);
		}
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

	// https://github.com/brianuuu/DllMods/blob/master/Dependencies/Common.h
	static Hedgehog::Math::CVector GetPosition()
	{
		auto vecResult = Hedgehog::Math::CVector(0, 0, 0);

		if (!*GetPlayerContextSingleton())
			return vecResult;

		const uint32_t result = *(uint32_t*)((uint32_t) * (void**)((uint32_t)*GetPlayerContextSingleton() + 0x110) + 0xAC);
		{
			if (!result)
				return vecResult;
		}

		float* pPos = (float*)(*(uint32_t*)(result + 0x10) + 0x70);
		{
			vecResult.x() = pPos[0];
			vecResult.y() = pPos[1];
			vecResult.z() = pPos[2];
		}

		return vecResult;
	}

	// https://github.com/brianuuu/DllMods/blob/master/Dependencies/Common.h
	static Hedgehog::Math::CQuaternion GetRotation()
	{
		auto vecResult = Hedgehog::Math::CQuaternion(0, 0, 0, 0);

		if (!*GetPlayerContextSingleton())
			return vecResult;

		const uint32_t result = *(uint32_t*)((uint32_t) * (void**)((uint32_t)*GetPlayerContextSingleton() + 0x110) + 0xAC);
		{
			if (!result)
				return vecResult;
		}

		float* pRot = (float*)(*(uint32_t*)(result + 0x10) + 0x60);
		{
			vecResult.x() = pRot[0];
			vecResult.y() = pRot[1];
			vecResult.z() = pRot[2];
			vecResult.w() = pRot[3];
		}

		return vecResult;
	}

	static const float GetVelocity()
	{
		CHECK_CONTEXT_SAFE(0.0f);

		return CONTEXT->GetVelocity().norm();
	}

	static void SetVelocityX(float x)
	{
		auto velocity = CONTEXT->GetVelocity();
		{
			CONTEXT->SetVelocity
			(
				Hedgehog::Math::CVector
				(
					x,
					velocity.y(),
					velocity.z()
				)
			);
		}
	}

	static void SetVelocityY(float y)
	{
		auto velocity = CONTEXT->GetVelocity();
		{
			CONTEXT->SetVelocity
			(
				Hedgehog::Math::CVector
				(
					velocity.x(),
					y,
					velocity.z()
				)
			);
		}
	}

	static void SetVelocityZ(float z)
	{
		auto velocity = CONTEXT->GetVelocity();
		{
			CONTEXT->SetVelocity
			(
				Hedgehog::Math::CVector
				(
					velocity.x(),
					velocity.y(),
					z
				)
			);
		}
	}

	static const char* GetStageID()
	{
		return (const char*)0x1E774D4;
	}

	static const void PlayMusic(char const* cueName, float fadeInTime)
	{
		FUNCTION_PTR(unsigned int, __stdcall, PlayAudioFromCueName, 0xD62440, Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> gameDocument, const Hedgehog::Base::CSharedString& cueName, float fadeInTime);
		{
			PlayAudioFromCueName(CONTEXT->m_pPlayer->GetGameDocument(), cueName, fadeInTime);
		}
	}

	static const void StopMusic(char const* cueName, float fadeOutTime)
	{
		FUNCTION_PTR(int, __stdcall, StopAudioFromCueName, 0xD61E40, Hedgehog::Base::TSynchronizedPtr<Sonic::CGameDocument> gameDocument, const Hedgehog::Base::CSharedString& cueName, float fadeOutTime);
		{
			StopAudioFromCueName(CONTEXT->m_pPlayer->GetGameDocument(), cueName, fadeOutTime);
		}
	}
};