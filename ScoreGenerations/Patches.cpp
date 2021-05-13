/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void Patches::Install()
{
	if (!Mod::customXNCP)
	{
		// Use Score Generations' HUD XNCP.
		WRITE_MEMORY(0x168E333, uint8_t, "_b\0");
	}
}