#include <Quaternion.hpp>
#include <Vector3.hpp>

#pragma once

class PlayerListener
{
public:
    static void** const CSonicContextAddress;
    static bool isGrounded;
	static bool isDead;

    static void Install();
    static bool IsContextSafe();
    static const uint32_t GetContext();
    static float GetVelocity();
    static bool IsSuper();

	struct CSonic
	{
		char padding_1[0x84];
		Vector3 WorldInput;
		char padding_2[0x154];
		float AirTime;
		char padding_3[0xA4];
		Vector3 Velocity;
	};

	struct CMatrixNodeTransform
	{
		char unknown01[0x60]{};
		Quaternion Rotation;
		Vector3 Position;
		char unknown02[0x1c]{};
	};

	struct CSonicContext
	{
		char padding_1[0x10];
		CMatrixNodeTransform* Transform;
		CSonic* Sonic;
		char padding_2;
	};

	struct CSonicStateFlags
	{
		bool eStateFlag_EarthGround;
		bool eStateFlag_HeadToVelocity;
		bool eStateFlag_HeadUpOnly;
		bool eStateFlag_SlowHeadToUpDirection;
		bool eStateFlag_OutOfControl;
		bool eStateFlag_NoLandOutOfControl;
		bool eStateFlag_DisableForwardPathInterpolation;
		bool eStateFlag_ChangePath;
		bool eStateFlag_ChangePathCameraChange;
		bool eStateFlag_WallWalkJump;
		bool eStateFlag_SupportWalkOnCeiling;
		bool eStateFlag_NotifyWalkOnCeiling;
		bool eStateFlag_AlwaysDownForce;
		bool eStateFlag_DisableDownForce;
		bool eStateFlag_Dead;
		bool eStateFlag_Goal;
		bool eStateFlag_Boost;
		bool eStateFlag_FloatingBoost;
		bool eStateFlag_StartingBoost;
		bool eStateFlag_EndBoost;
		bool eStateFlag_DummyBoost;
		bool eStateFlag_EndDummyBoost;
		bool eStateFlag_Homing;
		bool eStateFlag_EnableHomingAttack;
		bool eStateFlag_EnableHomingAttackOnDiving;
		bool eStateFlag_EnableHomingAttackOutOfControl;
		bool eStateFlag_DisableAirBoost;
		bool eStateFlag_EnableAirOnceAction;
		bool eStateFlag_DisableStomping;
		bool eStateFlag_ForceShoesSliding;
		bool eStateFlag_DisableShoesSliding;
		bool eStateFlag_OnWater;
		bool eStateFlag_OnNoDeadWater;
		bool eStateFlag_OnAboveWater;
		bool eStateFlag_OnSurfaceWater;
		bool eStateFlag_OnShallowWater;
		bool eStateFlag_OnWaterSeEnabled;
		bool eStateFlag_TerrainCollisionEnable;
		bool eStateFlag_AirOutOfControl;
		bool eStateFlag_NoPadStopWalk;
		bool eStateFlag_DisableAirAutoDec;
		bool eStateFlag_DisableWallJumpReady;
		bool eStateFlag_GroundDistanceZero;
		bool eStateFlag_NoPitchRollHorzOnAir;
		bool eStateFlag_DisableMoonsault;
		bool eStateFlag_KeepRunning;
		bool eStateFlag_KeepRunningEnableBackForce;
		bool eStateFlag_KeepRunningOnSpiral;
		bool eStateFlag_KeepRunningPause;
		bool eStateFlag_SShapeRunning;
		bool eStateFlag_MoveOnPath;
		bool eStateFlag_IgnoreTerrain;
		bool eStateFlag_UpdateYawByVelocity;
		bool eStateFlag_NoPitchRoll;
		bool eStateFlag_NoUpdateYaw;
		bool eStateFlag_NoUpdateYawRef;
		bool eStateFlag_UpdateYawOnAir;
		bool eStateFlag_NoUpdateAdvancedDirection;
		bool eStateFlag_CameraChagedPadCorrection;
		bool eStateFlag_EnableCameraChagedPadCorrect;
		bool eStateFlag_CameraToCullingBasePosEnabled;
		bool eStateFlag_NoDamage;
		bool eStateFlag_NoDead;
		bool eStateFlag_Damaging;
		bool eStateFlag_Paralyzing;
		bool eStateFlag_ReactinJumpPathChange;
		bool eStateFlag_ForcePitchRollGround;
		bool eStateFlag_EnableAttenuateJump;
		bool eStateFlag_NoGroundFall;
		bool eStateFlag_OnStairs;
		bool eStateFlag_OnBeltConveyor;
		bool eStateFlag_MoveToPositionAndWait;
		bool eStateFlag_StopPositionCount;
		bool eStateFlag_OnNoWallWalkGround;
		bool eStateFlag_ForceLandForCaught;
		bool eStateFlag_Restarting;
		bool eStateFlag_SlidingAndSquatPressOnly;
		bool eStateFlag_SideViewNoPathMove;
		bool eStateFlag_Pushing;
		bool eStateFlag_NoChange2DPath;
		bool eStateFlag_PrepreRestart;
		bool eStateFlag_SetDirectRotation;
		bool eStateFlag_IsTakingBreath;
		bool eStateFlag_OnSpiralGound;
		bool eStateFlag_OnMovableGround;
		bool eStateFlag_OnFakeMovableGround;
		bool eStateFlag_OnMoonsaltDisableGround;
		bool eStateFlag_EnableExceptionalBoost;
		bool eStateFlag_AcceptSlidingCollision;
		bool eStateFlag_AcceptBuoyancyForce;
		bool eStateFlag_AcceptEnvForce;
		bool eStateFlag_DisableAdlibTrick;
		bool eStateFlag_StandbyAdlibTrick;
		bool eStateFlag_StandbyChangeToSpin;
		bool eStateFlag_Pressing;
		bool eStateFlag_FallEnabledInPressing;
		bool eStateFlag_OnIntersectionalWay;
		bool eStateFlag_ObserveBoostInExternalControl;
		bool eStateFlag_ObserveSpinInExternalControl;
		bool eStateFlag_ObserveInputInExternalControl;
		bool eStateFlag_EscapeEnabledInExternalControl;
		bool eStateFlag_NoDamageInExternalControl;
		bool eStateFlag_Slipping;
		bool eStateFlag_InvokeFlameBarrier;
		bool eStateFlag_InvokeAquaBarrier;
		bool eStateFlag_InvokeThunderBarrier;
		bool eStateFlag_InvokeBarrier;
		bool eStateFlag_InvokePreciousTime;
		bool eStateFlag_InvokeHighSpeed;
		bool eStateFlag_InvokeTimeBreak;
		bool eStateFlag_InvokeSkateBoard;
		bool eStateFlag_InvokeSuperSonic;
		bool eStateFlag_InvokePtmRocket;
		bool eStateFlag_InvokePtmSpike;
		bool eStateFlag_InvokeUnbeaten;
		bool eStateFlag_DoubleJumping;
		bool eStateFlag_InvokeFixedMoveOn3D;
		bool eStateFlag_KeepStateAfterChangeDimension;
		bool eStateFlag_KeepPostureAfterChangeDimension;
		bool eStateFlag_CalibrateFrontDir;
		bool eStateFlag_EnableAnimationVelocityDirect;
		bool eStateFlag_EnableGravityControl;
		bool eStateFlag_EnableAirBoostOnGravityControl;
		bool eStateFlag_EnableChaosEnergySetting;
		bool eStateFlag_ChaosEnergySubstractDisabled;
		bool eStateFlag_EnableAutoAim;
		bool eStateFlag_ThroughGoalSignboard;
		bool eStateFlag_AutoBoost;
		bool eStateFlag_MaxSpeedLimited;
		bool eStateFlag_Pause;
		bool eStateFlag_SkateBoardSlowDown;
		bool eStateFlag_ChangeCollisionLocked;
		bool eStateFlag_ReadyGoOpened;
		bool eStateFlag_SpikeSpin;
		bool eStateFlag_ChangePostureInDeadAirEnabled;
		bool eStateFlag_DisableGroundSmoke;
		bool eStateFlag_Drifting;
		bool eStateFlag_DriftingLowSpeed;
		bool eStateFlag_DriftRight;
		bool eStateFlag_Squat;
		bool eStateFlag_LightSpeedDashReady;
		bool eStateFlag_BoostKeep;
		bool eStateFlag_DisableCrashWall;
		bool eStateFlag_WallCorrection;
		bool eStateFlag_Diving;
		bool eStateFlag_DivingFloat;
		bool eStateFlag_HipSliding;
		bool eStateFlag_GrindFullBalance;
		bool eStateFlag_GrindSideJump;
		bool eStateFlag_Freeze;
		bool eStateFlag_DisableBoost;
		bool eStateFlag_NoSquatToSliding;
		bool eStateFlag_IgnorePadInput;
		bool eStateFlag_Rising;
		bool eStateFlag_SpinChargeSliding;
		bool eStateFlag_CombinationAttacking;
		bool eStateFlag_SpinDash;
		bool eStateFlag_LightAttack;
		bool eStateFlag_AtomicSpin;
		bool eStateFlag_Binding;
		bool eStateFlag_ChgPlayerDisabled;
		bool eStateFlag_EndReflection;
		bool eStateFlag_CorrectOnPath;
		bool eStateFlag_DebugDrawGroundHitPosition;
		bool eStateFlag_DebugDrawVelocity;
		bool eStateFlag_DebugDrawPath;
		bool eStateFlag_DebugDrawSpikeInfo;
		bool eStateFlag_DebugExceptionalMove;
	};

	static CSonicStateFlags* GetStateFlagsFromContext(struct CSonicContext* sonicContext);
};