HOOK(bool, __fastcall, StateSpringJumpHeadLandUpdate, m_SigStateSpringJumpHeadLandUpdate(), int64_t in_pThis, int64_t in_pSonicContext)
{
	auto kinematics = Player::GetKinematics();

	if (kinematics)
	{
		float dot = (kinematics->Rotation * csl::math::Vector3::UnitY()).dot(csl::math::Vector3::UnitY());

		// Exit into StateRun if we're on a steep angle to prevent oddities.
		if (dot < 0.01f)
		{
			Player::SetState(in_pSonicContext, ESonicState_StateRun);
			return true;
		}
	}

	// Exit into StateRun.
	if (IsButtonPressed(EPlayerActionType_PlayerJump) || IsButtonPressed(EPlayerActionType_PlayerAttack))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateRun);
		return true;
	}

	// Exit into StateSliding.
	if (IsButtonPressed(EPlayerActionType_PlayerStomping))
	{
		Player::SetState(in_pSonicContext, ESonicState_StateSliding);
		return true;
	}

	return originalStateSpringJumpHeadLandUpdate(in_pThis, in_pSonicContext);
}

void StateSpringJumpHeadLand::Install()
{
	INSTALL_HOOK(StateSpringJumpHeadLandUpdate);
}