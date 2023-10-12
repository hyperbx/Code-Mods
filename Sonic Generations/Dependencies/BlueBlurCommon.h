#pragma once

#include "..\Dependencies\BlueBlur\BlueBlur.h"
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
	enum SonicCollisionType : uint32_t
	{
		TypeNoAttack           = 0x1E61B5C,
		TypeRagdoll            = 0x1E61B60,
		TypeSonicSpinCharge    = 0x1E61B64,
		TypeSonicSpin          = 0x1E61B68,
		TypeSonicUnbeaten      = 0x1E61B6C,
		TypeSuperSonic         = 0x1E61B70,
		TypeSonicSliding       = 0x1E61B74,
		TypeSonicHoming        = 0x1E61B78,
		TypeSonicSelectJump    = 0x1E61B7C,
		TypeSonicDrift         = 0x1E61B80,
		TypeSonicBoost         = 0x1E61B84,
		TypeSonicStomping      = 0x1E61B88,
		TypeSonicTrickAttack   = 0x1E61B8C,
		TypeSonicSquatKick     = 0x1E61B90,
		TypeSonicClassicSpin   = 0x1E61B94,
		TypeExplosion          = 0x1E61B98,
		TypeBossAttack         = 0x1E61B9C,
		TypeGunTruckAttack     = 0x1E61BA0,
		TypeRagdollEnemyAttack = 0x1E61BA4,
	};

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
	enum StageMissionType : uint32_t
	{
		ghz100 = 0x00,
		ghz200 = 0x01,
		cpz100 = 0x02,
		cpz200 = 0x03,
		ssz100 = 0x04,
		ssz200 = 0x05,
		sph100 = 0x06,
		sph200 = 0x07,
		cte100 = 0x08,
		cte200 = 0x09,
		ssh100 = 0x0A,
		ssh200 = 0x0B,
		csc100 = 0x0C,
		csc200 = 0x0D,
		euc100 = 0x0E,
		euc200 = 0x0F,
		pla100 = 0x10,
		pla200 = 0x11,
		cnz100 = 0x12,
		emu    = 0x13,
		bms    = 0x14,
		bsd    = 0x15,
		bsl    = 0x16,
		bde    = 0x17,
		bpc    = 0x18,
		bne    = 0x19,
		blb    = 0x1A,
		pam000 = 0x1B,
		fig000 = 0x1C,
		evt041 = 0x1D,
		evt105 = 0x1E,
		evt121 = 0x1F,

		Mission1 = 0x100,
		Mission2 = 0x200,
		Mission3 = 0x300,
		Mission4 = 0x400,
		Mission5 = 0x500,

		BossHard = 0x100,
	};

	// Research by Ahremic.
	enum CameraParamType : uint32_t
	{
		TARGET_FRONT_OFFSET_SCALE                      = 0x1A48B20,
		TARGET_FRONT_OFFSET_SENSITIVE                  = 0x1A48B24,
		SLOPE_SENSITIVE                                = 0x1A48B28,
		SLOPE_SENSITIVE_VELOCITY_SCALE                 = 0x1A48B2C,
		SLOPE_SENSITIVE_VELOCITY_SCALE_VELOCITY_OFFSET = 0x1A48B30,
		SLOPE_SENSITIVE_MAX                            = 0x1A48B34,
		SLOPE_SENSITIVE_AIR                            = 0x1A48B38,
		SLOPE_CAMERAUP_RATE                            = 0x1A48B3C,
		SLOPE_AFFECT_MIN_VELOCITY                      = 0x1A48B40,
		SLOPE_AFFECT_MAX_VELOCITY                      = 0x1A48B44,
		TARGET_UP_OFFSET_IN_AIR                        = 0x1A48B48,
		TARGET_UP_OFFSET_SENSITIVE                     = 0x1A48B4C,
		TARGET_UP_FINAL_OFFSET                         = 0x1A48B50,
		TARGET_UP_SENSITIVE                            = 0x1A48B54,
		TARGET_DOWN_SENSITIVE_GROUND_NEAR              = 0x1A48B58,
		TARGET_DOWN_SENSITIVE_GROUND_FAR_NEAR_BORDER   = 0x1A48B5C,
		CAMERA_MIN_PITCH                               = 0x1A48B64,
		CAMERA_TARGET_PITCH_SENSITIVE                  = 0x1A48B68,
		CAMERA_DISTANCE_MAX_RATE                       = 0x1A48B70,
		CAMERA_DISTANCE_MAX_RATE_WATER                 = 0x1A48B74,
		CAMERA_DISTANCE_SCALE                          = 0x1A48B78,
		CAMERA_DISTANCE_MINIMUM                        = 0x1A48B7C,
		CAMERA_DISTANCE_NEGATIVE_PITCH_SCALE           = 0x1A48B80,
		CAMERA_DISTANCE_POSITIVE_PITCH_SCALE           = 0x1A48B84,
		CAMERA_DISTANCE_BASIC_RANGE                    = 0x1A48B88,
		CAMERA_POSITION_VELOCITY_RATE                  = 0x1A48B8C,
		TARGET_SIDE_OFFSET_SCALE                       = 0x1A48B90,
		TARGET_SIDE_OFFSET_VELOCITY_SCALE              = 0x1A48B94,
		TARGET_SIDE_OFFSET_SENSITIVE                   = 0x1A48B98,
		TARGET_SIDE_OFFSET_RECOVER_SENSITIVE           = 0x1A48B9C,
		TARGET_SENSITIVE                               = 0x1A48BA0,
		TARGET_UP_POSITIVE_SENSITIVE_GROUND            = 0x1A48BA4,
		TARGET_UP_NEGATIVE_SENSITIVE_GROUND            = 0x1A48BA8,
		TARGET_UP_POSITIVE_SENSITIVE_VELSCALE_GROUND   = 0x1A48BAC,
		TARGET_UP_POSITIVE_SENSITIVE_AIR               = 0x1A48BB4,
		TARGET_UP_NEGATIVE_SENSITIVE_AIR               = 0x1A48BB8,
		TARGET_UP_DIFF_POSITIVE_MAX                    = 0x1A48BBC,
		TARGET_UP_DIFF_NEGATIVE_MAX                    = 0x1A48BC0,
		TARGET_SIDE_DIFF_MAX                           = 0x1A48BC4,
		POSITION_SENSITIVE                             = 0x1A48BC8,
		POSITION_UP_POSITIVE_SENSITIVE                 = 0x1A48BCC,
		POSITION_UP_NEGATIVE_SENSITIVE                 = 0x1A48BD0,
		POSITION_UP_DIFF_POSITIVE_MAX                  = 0x1A48BD4,
		POSITION_UP_DIFF_NEGATIVE_MAX                  = 0x1A48BD8,
		DISTANCE_OFFSET_BASE_VELOCITY                  = 0x1A48BDC,
		DISTANCE_OFFSET                                = 0x1A48BE0,
		DISTANCE_OFFSET_MAX                            = 0x1A48BE4,
		DISTANCE_OFFSET1_SENSITIVE                     = 0x1A48BE8,
		DISTANCE_OFFSET2_SENSITIVE                     = 0x1A48BEC,
		DRIFT_YAW_SENSITIVE_BASE                       = 0x1A48BF0,
		DRIFT_YAW_SENSITIVE_SPEED_SCALE                = 0x1A48BF4,
		DRIFT_FINISH_YAW_VELOCITY_SENSITIVE            = 0x1A48BF8,
		COLLISION_RADIUS                               = 0x1A48C00,
		HOMING_ATTACK_TARGET_SENSITIVE                 = 0x1A48C04,
		CAMERA_POSITION_VELOCITY_RATE_IN_DASHMODE      = 0x1A48C08,
		DASHPATH_BINRM_SENSITIVE                       = 0x1A48C0C,
		DASHPATH_EASE_TIME                             = 0x1A48C10,
		TARGET_FRONT_OFFSET_BIAS                       = 0x1E5E1FC,
		TARGET_DOWN_SENSITIVE_GROUND_FAR               = 0x1E5E200,
		DRIFT_YAW_OFFSET                               = 0x1E5E204,
		DRIFT_TARGET_SIDE_OFFSET_SCALE                 = 0x1A48BFC,
		CAMERA_PITCH_MOVE_VELOCITY_MIN                 = 0x1A48B6C,
		CAMERA_MAX_PITCH                               = 0x1A48B60
	};
	
	// Research by Ahremic.
	struct __declspec(align(32)) CPlayer3DNormalCamera
	{
		struct CameraParams
		{
			float m_ParamTargetSideSensitive;
			float m_ParamTargetSideSensitiveInQuickStep;
			float m_ParamDashPathSideMoveRate;
		};

		struct CListener
		{
			void* vftable;

			BB_INSERT_PADDING(0x0C);

			Hedgehog::Math::CVector m_Vector01;
			Hedgehog::Math::CVector m_Vector02;
			Hedgehog::Math::CVector m_Vector03;

			boost::shared_ptr<void> m_spRayCastCollision;
		};

		void* vftable;

		int field_4;
		int m_pContext;
		int m_pStateMachine;

		float m_Time;

		int field_14;

		const char* m_Name;

		int field_1C;

		float field_20;

		uint8_t gap24[64];

		float m_FovInRadians;

		bool field_68;

		int field_6C;

		Hedgehog::Math::CVector m_CameraPositionVisual;
		Hedgehog::Math::CVector m_CameraUpVector;
		Hedgehog::Math::CVector m_CameraTargetPosition;
		Hedgehog::Math::CVector m_CameraPositionInputReference;
		Hedgehog::Math::CVector m_CameraVectorUNK_01;
		Hedgehog::Math::CVector m_CameraRotationQuat;

		char field_D0[16];

		int field_E0;

		char field_E4[28];

		CameraParams* m_pParams;

		char field_104[12];

		void* characterProxy;

		float m_CameraRotationUnknown;
		float m_CameraTargetPositionY;

		int field_11C;

		Hedgehog::Math::CVector m_TargetFrontOffset;
		Hedgehog::Math::CVector m_TargetSideOffset;
		Hedgehog::Math::CVector m_CameraPositionCollision;
		Hedgehog::Math::CVector m_TargetOffsetPosition;
		Hedgehog::Math::CVector m_WorkingUpVector;

		// Sonic::CCharacterProxy* m_CharacterProxy;
		// _CCharacterProxy* m_CharacterProxy;
		BB_INSERT_PADDING(0x04);

		int field_174;

		// Sonic::CBoostCameraPlugin* m_pBoostCameraPlugin;
		BB_INSERT_PADDING(0x04);

		void* unk_void;

		bool m_IsQuickstepping;
		bool m_IsOnBoard;

		__int16 gap182;

		float m_TargetSideQuickstepTimer;
		float m_CameraTargetPitch;
		float m_DistanceOffset1;
		float m_DistanceOffset2;

		char field_194[8];

		int field_19C;

		Hedgehog::Math::CVector field_1A0;

		float m_CameraOrbitX;
		float m_CameraOrbitY;

		char field_1B8[8];

		Hedgehog::Math::CVector m_DashPathRightVector;

		// char m_DashPathEasePositionTarget[32];

		Hedgehog::Math::CVector m_DashPathEasePositionTarget;
		Hedgehog::Math::CVector m_DashPathEasePositionCamera;

		bool m_IsDashPathEasing;
		bool m_IsFacingForward;

		float m_DashPathEaseTime;

		CListener* m_pListener;

		char field_1FC;
		char field_1FD;
		char field_1FE;
		char field_1FF;
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

	static void* SetCollision(Sonic::Player::CPlayerSpeedContext* context, SonicCollisionType collisionType, bool enabled)
	{
		static void* const pEnableFunc  = (void*)0xE65610;
		static void* const pDisableFunc = (void*)0xE655C0;

		__asm
		{
			mov	 edi, context
				 
			mov	 ecx, collisionType
			mov	 ecx, [ecx]
			push ecx

			cmp enabled, 0
			je  Disable

			call [pEnableFunc]
			jmp  Finish

		Disable:
			call [pDisableFunc]

		Finish:
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

	static float GetCameraParam(CameraParamType type)
	{
		return *(float*)type;
	}

	static void SetCameraParam(CameraParamType type, float value)
	{
		WRITE_MEMORY(type, float, value);
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

	static float GetGameSpeed(bool isPlayerAffected = true)
	{
		if (isPlayerAffected)
		{
			READ_POINTER(gameSpeedAddr, 0x1E0BE5C, 8, 0x1A0);

			return *(float*)gameSpeedAddr;
		}
		else
		{
			READ_POINTER(gameSpeedAddr, 0x1E0BE5C, 8, 0x1A4);

			return *(float*)gameSpeedAddr;
		}
	}

	static void SetGameSpeed(float speed, bool isPlayerAffected = true)
	{
		if (isPlayerAffected)
		{
			READ_POINTER(gameSpeedEnableAddr, 0x1E0BE5C, 8, 0x19C);
			READ_POINTER(gameSpeedAddr, 0x1E0BE5C, 8, 0x1A0);

			WRITE_MEMORY(gameSpeedEnableAddr, uint8_t, 0x01);
			WRITE_MEMORY(gameSpeedAddr, float, speed);
		}
		else
		{
			READ_POINTER(gameSpeedEnableAddr, 0x1E0BE5C, 8, 0x19D);
			READ_POINTER(gameSpeedAddr, 0x1E0BE5C, 8, 0x1A4);

			WRITE_MEMORY(gameSpeedEnableAddr, uint8_t, 0x01);
			WRITE_MEMORY(gameSpeedAddr, float, speed);
		}
	}

	static uint32_t GetStageID()
	{
		READ_POINTER(stageIdAddr, 0x1E66B34, 0x04, 0x1B4, 0x80, 0x00);

		return *(uint32_t*)stageIdAddr;
	}

	static const char* GetStageCharID()
	{
		return (const char*)0x1E774D4;
	}

	static bool IsCurrentStageBoss()
	{
		auto stageID = GetStageID();
		{
			stageID &= 0xFF;
		}

		return stageID >= bms && stageID <= blb;
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