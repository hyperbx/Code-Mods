void Patches::PatchDashRingNames(const char* overrideName)
{
	const char* dashRingType = StringHelper::IsEmpty(overrideName) ?
							   Configuration::colourType == Configuration::GreenDiffuse ? "mis_obj_TailsDashring_HD" : "cmn_obj_TailsDashring_HD" :
							   overrideName;

	// Inject custom model name for rainbow rings.
	if (Configuration::useCustomRainbowRings)
		WRITE_MEMORY(0x1A47574, const char*, "rnb_obj_TailsDashring_HD");

	// Inject custom model name for dash rings.
	WRITE_MEMORY(0x1A47578, const char*, dashRingType);

	// Inject custom model name for Tails' dash rings.
	if (Configuration::overrideTailsDashRing)
		WRITE_MEMORY(0x1A4757C, const char*, dashRingType);
}

void Patches::Install()
{
	PatchDashRingNames();

	switch (Configuration::soundType)
	{
		case Configuration::DashRing:
		{
			int sound = 0x3D0CFC;

			WRITE_MEMORY(0x1A6B7FC, uint32_t, sound);

			if (Configuration::overrideTailsDashRing)
				WRITE_MEMORY(0x1A6B800, uint32_t, sound);

			break;
		}

		case Configuration::RainbowRing:
		{
			int sound = 0x3D10E5;

			WRITE_MEMORY(0x1A6B7FC, uint32_t, sound);

			if (Configuration::overrideTailsDashRing)
				WRITE_MEMORY(0x1A6B800, uint32_t, sound);

			break;
		}

		case Configuration::DashPanel:
		{
			int sound = 0x3D10E6;

			WRITE_MEMORY(0x1A6B7FC, uint32_t, sound);

			if (Configuration::overrideTailsDashRing)
				WRITE_MEMORY(0x1A6B800, uint32_t, sound);

			break;
		}

		case Configuration::ClassicSpring:
		{
			int sound = 0x3D10DF;

			WRITE_MEMORY(0x1A6B7FC, uint32_t, sound);

			if (Configuration::overrideTailsDashRing)
				WRITE_MEMORY(0x1A6B800, uint32_t, sound);

			break;
		}

		case Configuration::ModernSpring:
		{
			int sound = 0x3D10DE;

			WRITE_MEMORY(0x1A6B7FC, uint32_t, sound);

			if (Configuration::overrideTailsDashRing)
				WRITE_MEMORY(0x1A6B800, uint32_t, sound);

			break;
		}
	}
}