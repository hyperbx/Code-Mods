extern "C" __declspec(dllexport) void API_AddScore(int scoreToReward)
{
	ScoreListener::AddClamp(ScoreListener::score, scoreToReward);
}

extern "C" __declspec(dllexport) void API_SetScore(int score)
{
	ScoreListener::score = score;
}

extern "C" __declspec(dllexport) void API_ForceConfiguration(const char* path)
{
	Configuration::Read(path);
}

extern "C" __declspec(dllexport) int API_GetScore()
{
	return ScoreListener::score;
}

extern "C" __declspec(dllexport) int API_GetTotalScore()
{
	return ScoreListener::totalScore;
}

extern "C" __declspec(dllexport) int API_GetRank()
{
	return ResultListener::Rank();
}

extern "C" __declspec(dllexport) bool API_IsStageForbidden()
{
	return HudSonicStage::IsStageForbidden();
}

extern "C" __declspec(dllexport) int API_ComputeTimeBonus()
{
	return LuaCallback::RunAlgorithm(TableListener::bonusTable.timeBonusAlgorithm);
}

extern "C" __declspec(dllexport) int API_ComputeRingBonus()
{
	return LuaCallback::RunAlgorithm(TableListener::bonusTable.ringBonusAlgorithm);
}

extern "C" __declspec(dllexport) int API_ComputeSpeedBonus()
{
	return LuaCallback::RunAlgorithm(TableListener::bonusTable.speedBonusAlgorithm);
}

extern "C" __declspec(dllexport) int API_ComputeUserBonus()
{
	return LuaCallback::RunAlgorithm(TableListener::bonusTable.userAlgorithm);
}

extern "C" __declspec(dllexport) Statistics::Totals API_GetStatistics()
{
	return StatisticsListener::totals;
}

extern "C" __declspec(dllexport) Tables::ScoreTable API_GetScoreTable()
{
	return TableListener::scoreTable;
}

extern "C" __declspec(dllexport) unordered_map<string, Tables::RankTable> API_GetRankTables()
{
	return TableListener::rankTables;
}

extern "C" __declspec(dllexport) Tables::BonusTable API_GetBonusTable()
{
	return TableListener::bonusTable;
}

extern "C" __declspec(dllexport) Tables::MultiplierTable API_GetMultiplierTable()
{
	return TableListener::multiplierTable;
}

extern "C" __declspec(dllexport) Tables::TimerTable API_GetTimerTable()
{
	return TableListener::timerTable;
}
