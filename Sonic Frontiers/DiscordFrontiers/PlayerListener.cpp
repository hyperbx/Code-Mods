bool m_isCommittedStatusUpdate = false;
bool m_lastUpdateStatus = false;

HOOK(int64_t, __fastcall, PlayerCtor, m_SigPlayerCtor(), int64_t in_pThis, int64_t a2)
{
	PlayerListener::Commit();

	return originalPlayerCtor(in_pThis, a2);
}

HOOK(int64_t, __fastcall, ChangePlayerVisualToSuperSonic, m_SigChangePlayerVisualToSuperSonic(), int64_t in_pThis)
{
	PlayerListener::IsSuperSonic2 = false;
	PlayerListener::Commit();

	return originalChangePlayerVisualToSuperSonic(in_pThis);
}

HOOK(int64_t, __fastcall, ChangePlayerVisualToSuperSonic2, m_SigChangePlayerVisualToSuperSonic2(), int64_t in_pThis)
{
	PlayerListener::IsSuperSonic2 = true;
	PlayerListener::Commit();

	return originalChangePlayerVisualToSuperSonic2(in_pThis);
}

HOOK(void, __fastcall, PlayerListener_GOCPlayerHsmUpdate, m_SigGOCPlayerHsmUpdate(), hh::game::GOComponent* in_pThis, int in_updatePhase, float* in_pDeltaTime)
{
	bool isSuper = PlayerListener::IsSuper(in_pThis->pOwner);

	if (PlayerListener::GetCharacterIndex() == 0)
	{
		if (m_lastUpdateStatus != isSuper)
			m_isCommittedStatusUpdate = false;
		
		if (!m_isCommittedStatusUpdate)
		{
			PlayerListener::Commit();

			m_lastUpdateStatus = isSuper;
			m_isCommittedStatusUpdate = true;
		}
	}

	return originalPlayerListener_GOCPlayerHsmUpdate(in_pThis, in_updatePhase, in_pDeltaTime);
}

void PlayerListener::Init()
{
	INSTALL_HOOK(PlayerCtor);
	INSTALL_HOOK(ChangePlayerVisualToSuperSonic);
	INSTALL_HOOK(ChangePlayerVisualToSuperSonic2);
	INSTALL_HOOK(PlayerListener_GOCPlayerHsmUpdate);
}

void PlayerListener::Commit()
{
	auto imgSrc = GetCharacterImageSource();

	Discord::CommitSmallImage(std::get<0>(imgSrc));
	Discord::CommitSmallImageText(std::get<1>(imgSrc));
}