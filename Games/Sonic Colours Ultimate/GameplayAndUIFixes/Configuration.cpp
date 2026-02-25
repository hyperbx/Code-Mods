void Configuration::Read()
{
	auto ini = cmf::sys::cfg::Ini(INI_FILE);

	IsTailsSave = ini.Get<std::string>("Main", "IncludeDir2", ".\\ui\\lives\\") != ".\\ui\\lives\\";
	RingLifeType = ini.Get<enum RingLifeType>("Main", "RingLifeType", RingLifeType);
}
