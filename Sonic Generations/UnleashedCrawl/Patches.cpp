void Patches::Install()
{
	// Cancel slide exit from standstill.
	WRITE_JUMP(0x11D6CA2, (void*)0x11D6CFF);
}