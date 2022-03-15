void Patches::PatchDashRingNames(const char* overrideName)
{
	const char* dashRingType = StringHelper::IsEmpty(overrideName) ?
							   Configuration::colourType == Configuration::GreenDiffuse ? "mis_obj_TailsDashring_HD" : "cmn_obj_TailsDashring_HD" :
							   overrideName;

#if _DEBUG
	printf("[Tails' Dash Rings in Stages] Current dash ring type = %s\n", dashRingType);
#endif

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

	int sound = 0x3D0CFC;

	switch (Configuration::soundType)
	{
		case Configuration::DashRing:
			sound = 0x3D0CFC;
			break;

		case Configuration::RainbowRing:
			sound = 0x3D10E5;
			break;

		case Configuration::DashPanel:
			sound = 0x3D10E6;
			break;

		case Configuration::ClassicSpring:
			sound = 0x3D10DF;
			break;

		case Configuration::ModernSpring:
			sound = 0x3D10DE;
			break;
	}

	WRITE_MEMORY(0x1A6B7FC, uint32_t, sound);

	if (Configuration::overrideTailsDashRing)
		WRITE_MEMORY(0x1A6B800, uint32_t, sound);
}