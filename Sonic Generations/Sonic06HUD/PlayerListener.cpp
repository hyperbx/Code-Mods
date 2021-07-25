/* This class is based off code from Skyth's Parameter Editor mod.
   https://github.com/blueskythlikesclouds/DllMods/blob/master/Source/GenerationsParameterEditor/PlayerInfo.cpp */

void** const PlayerListener::CSonicContext = (void**)0x1E5E2F0;

bool PlayerListener::IsContextSafe()
{
	return *CSonicContext;
}

const uint32_t PlayerListener::GetContext()
{
	if (!IsContextSafe())
		return -1;

	return *(uint32_t*)((uint32_t) * (void**)((uint32_t)*CSonicContext + 0x110) + 172);
}

float* PlayerListener::GetBoost()
{
	if (!IsContextSafe())
		return 0;

	return (float*)(GetContext() + 0x5BC);
}