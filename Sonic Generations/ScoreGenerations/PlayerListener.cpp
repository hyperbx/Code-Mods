void** const PlayerListener::CSonicContextAddress = (void**)0x1E5E2F0;
bool PlayerListener::isGrounded = false;
bool PlayerListener::isDead = false;

HOOK(void, __stdcall, SonicMovementContext, 0xE32180, int a1, __m128* a2)
{
	originalSonicMovementContext(a1, a2);

	const DWORD playerContextOffset = *(DWORD*)((int)a1 + 8);

	// Get context from offset...
	PlayerListener::CSonicContext* context = (PlayerListener::CSonicContext*)playerContextOffset;

	// Get flags...
	PlayerListener::isGrounded = *(bool*)(playerContextOffset + 0x360);
	PlayerListener::isDead = PlayerListener::GetStateFlagsFromContext(context)->eStateFlag_Dead;
}

bool PlayerListener::IsContextSafe()
{
	return *CSonicContextAddress;
}

const uint32_t PlayerListener::GetContext()
{
	if (!IsContextSafe())
		return -1;

	return *(uint32_t*)((uint32_t) * (void**)((uint32_t)*CSonicContextAddress + 0x110) + 172);
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

PlayerListener::CSonicStateFlags* PlayerListener::GetStateFlagsFromContext(PlayerListener::CSonicContext* sonicContext)
{
	int* const context = reinterpret_cast<int*>(sonicContext);

	return reinterpret_cast<CSonicStateFlags*>(*reinterpret_cast<int*>(context[0x14D] + 4));
}

void PlayerListener::Install()
{
	// Install hook to check grounded state.
	INSTALL_HOOK(SonicMovementContext);
}