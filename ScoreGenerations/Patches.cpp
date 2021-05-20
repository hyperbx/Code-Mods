/// <summary>
/// Installs the patches.
/// </summary>
void Patches::Install()
{
	// Disable next rank dialog on results.
	// WRITE_MEMORY(0x10B6DEC, uint8_t, 0x6A, 0x01);

	// Skip score cap in results.
	WRITE_JUMP(0x10B4012, (void*)0x10B401E);

	// Skip score cap in Casino Night.
	WRITE_JUMP(0x1095D70, (void*)0x1095D77);

	if (!Configuration::customXNCP)
	{
		if (StringHelper::GetDigits(Configuration::scoreFormat) <= 6 || StringHelper::Compare(Configuration::scoreFormat, "%d"))
		{
			// Use Score Generations' HUD XNCP for six digit padding (or below).
			WRITE_MEMORY(0x168E333, uint8_t, "_low_padding\0");
		}
		else
		{
			// Use Score Generations' HUD XNCP for high amounts of padding.
			WRITE_MEMORY(0x168E333, uint8_t, "_high_padding\0");
		}
	}
}