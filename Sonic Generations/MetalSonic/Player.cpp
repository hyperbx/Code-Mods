bool isBraking = false;
bool isHovering = false;

boost::shared_ptr<void> jetBoostParticleHandle;
boost::shared_ptr<Hedgehog::Sound::CSoundHandle> hoverSoundHandle;

int GetBrakeCollisionSound(Sonic::Player::CPlayerSpeedContext* context)
{
	if (BlueBlurCommon::IsClassic())
		return 2001002;

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
		// Custom bone for the jet particle.
		auto jet = player->m_spCharacterModel->GetNode("Jet");

		BlueBlurCommon::CreateParticle
		(
			player->m_spContext.get(),
			jetBoostParticleHandle,
			&jet,
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
		"Fall",
		"Grind",
		"Jump",
		"Slid",
		"Spin"
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
		context->m_HorizontalVelocity.norm() >= (BlueBlurCommon::IsModern() ? 8.0f : 17.0f) &&
		!IsBlacklistedAnimation(context->GetCurrentAnimationName().c_str())
	)
	{
		if (BlueBlurCommon::IsModern() && !context->m_Grounded)
			goto Kill;

		if (!isHovering)
		{
			// TODO: create a particle for this.
			// CreateJetBoostParticle(context->m_pPlayer);

			if (Configuration::soundEffects)
			{
				// Play hover sound.
				hoverSoundHandle = context->PlaySound(BlueBlurCommon::IsModern() ? 20020820 : 20010820, true);
			}

			isHovering = true;
		}

		isBraking = false;
	}
	else
	{
	Kill:
		// Classic Sonic continues running in mid-air.
		if
		(
			BlueBlurCommon::IsClassic() &&
			!context->m_Grounded &&
			!IsBlacklistedAnimation(context->GetCurrentAnimationName().c_str())
		)
		{
			goto Exit;
		}

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

			if (Configuration::soundEffects)
			{
				// Play brake sound.
				context->PlaySound(BlueBlurCommon::IsModern() ? 20020821 : 20010821, true);
			}

			isHovering = false;
		}
	}

Exit:
	originalCPlayerSpeedUpdateParallel(_this, _, updateInfo);
}

HOOK(int, __fastcall, ImpactManagerGeneric, 0xDFD420, int _this, void* _, int a2)
{
	if (isHovering)
		return -1;

	return originalImpactManagerGeneric(_this, _, a2);
}

HOOK(int, __fastcall, ImpactManagerClassic, 0xDC3400, int _this, void* _, int a2)
{
	if (isHovering)
		return -1;

	return originalImpactManagerClassic(_this, _, a2);
}

void Player::Install()
{
	INSTALL_HOOK(CPlayerSpeedUpdateParallel);
	INSTALL_HOOK(ImpactManagerGeneric);
	INSTALL_HOOK(ImpactManagerClassic);

	if (Configuration::disableDrowning)
	{
		// Disable water bubbles.
		WRITE_JUMP(0xFBCD56, 0xFBCD6A);
		WRITE_JUMP(0xFBCD78, 0xFBCFBE);

		// Disable drowning attention.
		WRITE_NOP(0x119B8F5, 5);

		// Disable drowning countdown.
		WRITE_JUMP(0x119B90F, 0x119B997);

		// Disable drowning.
		WRITE_JUMP(0x119C2C5, 0x119C2F8);
	}
}