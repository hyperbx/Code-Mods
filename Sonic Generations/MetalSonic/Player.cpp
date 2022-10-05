bool isBraking = false;
bool isHovering = false;

boost::shared_ptr<void> jetBoostParticleHandle;
boost::shared_ptr<Hedgehog::Sound::CSoundHandle> hoverSoundHandle;

int GetBrakeCollisionSound(Sonic::Player::CPlayerSpeedContext* context)
{
	switch (context->m_Field164)
	{
		case 4: // Dirt
		case 7: // Snow
		case 9: // Sand
			return 2002010;

		case 5: // Wood
			return 2002014;

		case 6: // Grass
			return 2002018;

		case 8: // Metal
			return 2002006;

		case 10: // Glass
		case 17: // Pinball Glass
			return 2002087;

		default:
			return 2002002;
	}
}

void CreateJetBoostParticle(Sonic::Player::CPlayer* player)
{
	if (!jetBoostParticleHandle)
	{
		auto spine = player->m_spCharacterModel->GetNode("Spine");

		BlueBlurCommon::CreateParticle
		(
			player->m_spContext.get(),
			jetBoostParticleHandle,
			&spine,
			"",
			1
		);
	}
}

void DestroyJetBoostParticle(Sonic::Player::CPlayer* player)
{
	if (jetBoostParticleHandle)
		BlueBlurCommon::DestroyParticle(player->m_spContext.get(), jetBoostParticleHandle, true);
}

bool IsBlacklistedAnimation(const char* animationName)
{
	const char* blacklist[] =
	{
		"Board",
		"Brake",
		"Grind",
		"Slid"
	};

	for (auto name : blacklist)
	{
		if (StringHelper::ContainsSubstring(animationName, name))
			return true;
	}

	return false;
}

HOOK(void, __fastcall, CPlayerSpeedUpdateParallel, 0xE6BF20, Sonic::Player::CPlayerSpeed* _this, void* _, const hh::fnd::SUpdateInfo& updateInfo)
{
	auto context = _this->GetContext();

	if
	(
		context->m_HorizontalVelocity.norm() >= 8.0f &&
		context->m_Grounded &&
		!IsBlacklistedAnimation(context->GetCurrentAnimationName().c_str())
	)
	{
		if (!isHovering)
		{
			// TODO: create a particle for this.
			// CreateJetBoostParticle(context->m_pPlayer);

			// Play hover sound.
			hoverSoundHandle = context->PlaySound(20020820, true);

			isHovering = true;
		}

		isBraking = false;
	}
	else
	{
		// Stop hover sound.
		hoverSoundHandle.reset();

		if (!isBraking && StringHelper::ContainsSubstring(context->GetCurrentAnimationName().c_str(), "Brake"))
		{
			// Play brake collision sound.
			context->PlaySound(GetBrakeCollisionSound(context), true);

			isBraking = true;
		}

		if (isHovering)
		{
			// TODO: create a particle for this.
			// DestroyJetBoostParticle(context->m_pPlayer);

			// Play brake sound.
			context->PlaySound(20020821, true);

			isHovering = false;
		}
	}

	originalCPlayerSpeedUpdateParallel(_this, _, updateInfo);
}

HOOK(int, __fastcall, ImpactManager, 0xDFD420, int _this, void* _, int a2)
{
	if (isHovering)
		return -1;

	return originalImpactManager(_this, _, a2);
}

void Player::Install()
{
	INSTALL_HOOK(CPlayerSpeedUpdateParallel);
	INSTALL_HOOK(ImpactManager);
}