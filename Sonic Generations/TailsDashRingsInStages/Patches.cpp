void Patches::Install()
{
	// Use Tails' dash ring model ID for normal dash rings.
	WRITE_MEMORY(0x115B806, uint8_t, 0x02);

	switch (Configuration::soundType)
	{
		case Configuration::DashRing:
			WRITE_MEMORY(0x1A6B800, uint32_t, 0x3D0CFC);
			break;

		case Configuration::DashPanel:
			WRITE_MEMORY(0x1A6B800, uint32_t, 0x3D10E6);
			break;
	}
}