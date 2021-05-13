/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void Patches::Install()
{
	if (!Mod::customHUD)
	{
		// Use fixed HUD with moved life counter.
		WRITE_MEMORY(0x168E333, uint8_t, "_b\0");
	}
}