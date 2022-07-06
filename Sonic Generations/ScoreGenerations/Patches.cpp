void Patches::Install()
{
	// Skip score cap in Casino Night.
	WRITE_JUMP(0x1095D70, (void*)0x1095D77);

	// Skip score cap in results.
	WRITE_JUMP(0x10B4012, (void*)0x10B401E);

	// Remove next rank dialog in results.
	WRITE_JUMP(0x10B66F0, (void*)0x10B6700);
	WRITE_JUMP(0x10B7DAE, (void*)0x10B7DB7);

	// Register negative rank values as D rank.
	WRITE_MEMORY(0x10B92BE, uint8_t, 0x7D);
}