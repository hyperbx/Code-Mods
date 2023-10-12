int64_t m_pMesh = 0;

HOOK(int64_t, __fastcall, _StatePluginCyloop_StateEffectCyloopUpdate, m_SigStateEffectCyloopUpdate(), int64_t in_pThis, int64_t a2, float in_deltaTime)
{
	m_pMesh = *(*(int64_t**)(*(int64_t*)(in_pThis + 0x20) + 0x28)) + 0x60 * 4;

	return original_StatePluginCyloop_StateEffectCyloopUpdate(in_pThis, a2, in_deltaTime);
}

HOOK(char, __fastcall, _StatePluginCyloop_SetMeshVisibility, m_SigSetMeshVisiblity(), int64_t in_pMesh, int64_t a2, char a3)
{
	if (in_pMesh == m_pMesh)
	{
		if (StatePluginCyloop::IsForceCyloopAura)
			a2 = 1;
	}

	return original_StatePluginCyloop_SetMeshVisibility(in_pMesh, a2, a3);
}

void StatePluginCyloop::Install()
{
	INSTALL_HOOK(_StatePluginCyloop_StateEffectCyloopUpdate);
	INSTALL_HOOK(_StatePluginCyloop_SetMeshVisibility);
}