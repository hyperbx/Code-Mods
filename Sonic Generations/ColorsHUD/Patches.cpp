void Patches::Install()
{
	if (!StringHelper::IsEmpty(Configuration::UIType.c_str()))
	{
		// Loop the title screen animations indefinitely (code by Hyper).
		WRITE_MEMORY(0x1A57A3C, uint8_t, 0x00);
		WRITE_MEMORY(0x1A57BBC, uint8_t, 0x00);

		// Disable the title outro animation (code by Skyth).
		WRITE_MEMORY(0x57346F, uint32_t, 0x16A36CC);
	}
}