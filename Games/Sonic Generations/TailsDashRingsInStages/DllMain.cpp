#include "ResourcePatches.h"

EXPORT void Init()
{
	cmf::sys::Logger::Init();

	Configuration::Read();

	ResourcePatches::Install();
}
