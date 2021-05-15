/* This class is based off code from Skyth's Parameter Editor mod.
   https://github.com/blueskythlikesclouds/DllMods/blob/master/Source/GenerationsParameterEditor/PlayerInfo.cpp */

void** const PlayerListener::context = (void**)0x1E5E2F0;

bool PlayerListener::IsContextSafe()
{
	return *context;
}

const uint32_t PlayerListener::GetContext()
{
	if (!IsContextSafe())
		return -1;

	return *(uint32_t*)((uint32_t) * (void**)((uint32_t)*context + 0x110) + 172);
}

float PlayerListener::GetVelocity()
{
	float* velocity = (float*)(GetContext() + 656);

	return sqrtf(velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2]);
}