void Configuration::Read()
{
	auto ini = cmf::sys::cfg::Ini(INI_FILE);

	ColourType = ini.Get<enum ColourType>("Appearance", "ColourType", ColourType);
	SoundType = ini.Get<enum SoundType>("Appearance", "SoundType", SoundType);
	IsOverrideTailsDashRing = ini.Get<bool>("Appearance", "IsOverrideTailsDashRing", IsOverrideTailsDashRing);
	UseCustomRainbowRings = ini.Get<bool>("Appearance", "UseCustomRainbowRings", UseCustomRainbowRings);
}
