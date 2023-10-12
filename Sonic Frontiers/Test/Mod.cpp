EXPORT void OnFrame()
{
	if ((GetAsyncKeyState(VK_F1) & 0x8000) == 0)
		return;

	printf("a");

	auto pGameManager = hh::game::GameManager::GetSingleton();

	if (!pGameManager)
		return;

	printf("b");

	auto pSonic = pGameManager->GetGameObject<app::player::Sonic>();

	if (!pSonic)
		return;

	printf("c");

	auto pGOCPlayerBlackboard = pSonic->GetGOC<app::player::GOCPlayerBlackboard>();

	if (!pGOCPlayerBlackboard)
		return;

	printf("d");

	auto pBlackboardItem = pGOCPlayerBlackboard->pBlackboard->GetBlackboardContent<app::player::BlackboardItem>();

	if (!pBlackboardItem)
		return;

	printf("e");

	printf("Capacity: %d\nCount: %d\n", pBlackboardItem->RingCapacity, pBlackboardItem->RingCount);
}