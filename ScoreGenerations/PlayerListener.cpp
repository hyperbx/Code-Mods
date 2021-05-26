// Declare class variables.
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

float PlayerListener::GetVelocity()
{
	/* This is based off code from Skyth's Parameter Editor mod.
       https://github.com/blueskythlikesclouds/DllMods/blob/master/Source/GenerationsParameterEditor/PlayerInfo.cpp */

	if (!IsContextSafe())
		return 0;

	float* velocity = (float*)(GetContext() + 656);

	return sqrtf(velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2]);
}

bool PlayerListener::IsSuper()
{
	if (!IsContextSafe())
		return false;

	return *(int*)(GetContext() + 0x1A0);
}