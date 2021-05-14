/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void Patches::Install()
{
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