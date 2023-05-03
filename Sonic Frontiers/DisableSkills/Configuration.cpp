void Configuration::Read()
{
	INIReader reader(INI_FILE);

	INI_READ_BOOLEAN("Skills", IsNoAirTrick);
	INI_READ_BOOLEAN("Skills", IsNoCrossSlash);
	INI_READ_BOOLEAN("Skills", IsNoCycloneKick);
	INI_READ_BOOLEAN("Skills", IsNoCyloop);
	INI_READ_BOOLEAN("Skills", IsNoGrandSlam);
	INI_READ_BOOLEAN("Skills", IsNoHomingShot);
	INI_READ_BOOLEAN("Skills", IsNoLoopKick);
	INI_READ_BOOLEAN("Skills", IsNoPhantomRush);
	INI_READ_BOOLEAN("Skills", IsNoQuickCyloop);
	INI_READ_BOOLEAN("Skills", IsNoRecoverySmash);
	INI_READ_BOOLEAN("Skills", IsNoSonicBoom);
	INI_READ_BOOLEAN("Skills", IsNoSpinSlash);
	INI_READ_BOOLEAN("Skills", IsNoStompAttack);
	INI_READ_BOOLEAN("Skills", IsNoWildRush);
}