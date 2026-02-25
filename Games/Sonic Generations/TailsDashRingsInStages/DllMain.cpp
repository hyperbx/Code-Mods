#include "ResourcePatches.h"

EXPORT void Init()
{
	cmf::sys::Logger::Init();

	Configuration::Read();

	ResourcePatches::Install();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
