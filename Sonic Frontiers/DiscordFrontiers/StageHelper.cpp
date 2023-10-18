app::level::StageData* StageHelper::GetCurrentStageData()
{
	auto pGameManager = hh::game::GameManager::GetSingleton();

	if (!pGameManager)
		return nullptr;

	auto pLevelInfo = pGameManager->GetService<app::level::LevelInfo>();

	if (!pLevelInfo)
		return nullptr;

	auto pStageData = pLevelInfo->pStageData;

	if (!pStageData)
		return nullptr;

	return pStageData;
}

std::string StageHelper::GetCurrentStageID()
{
	auto pStageData = GetCurrentStageData();

	if (!pStageData)
		return "";

	return std::string(pStageData->Name.begin(), pStageData->Name.end());
}