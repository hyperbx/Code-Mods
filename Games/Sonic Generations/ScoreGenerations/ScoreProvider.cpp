#include "BonusProvider.h"
#include "LuaSystem.h"
#include "ScoreProvider.h"
#include "StatisticsProvider.h"
#include "TableProvider.h"

using namespace ScoreGenerations;

int& __fastcall ScoreProvider::AddScore(int in_score, bool in_isResult)
{
	auto& rScore = in_isResult
		? m_FinalScore
		: m_CurrentScore;

	// Stop rewarding score if the player is over the maximum time.
	if (!in_isResult && Configuration::IsScoreTimeout && StatisticsProvider::GetStatistics().ElapsedTime > TableProvider::GetRankTables()[g_pStageID].MaxSeconds)
	{
		LOGFN_UTILITY("Time bonus expired! No longer rewarding score.");
		return rScore;
	}

	rScore = std::clamp(rScore + in_score, 0, Configuration::MaxScore);

	return in_isResult ? m_FinalScore : m_CurrentScore;
}

int& __fastcall ScoreProvider::AddScoreByType(ScoreType in_type)
{
	auto score = 0;

	auto& rScoreTable = TableProvider::GetScoreTable();
	auto& rStatistics = StatisticsProvider::GetStatistics();

	switch (in_type)
	{
		case ScoreType::Ring:
			score = rScoreTable.Ring;
			break;

		case ScoreType::Enemy:
			score = rScoreTable.Enemy;
			score += BonusProvider::GetHomingChainBonus();
			score += BonusProvider::GetSlamBonus();
			rStatistics.TotalEnemies++;
			break;

		case ScoreType::Physics:
			score = rScoreTable.Physics;
			rStatistics.TotalPhysics++;
			break;

		case ScoreType::PointMarker:
		{
			score = rScoreTable.PointMarker;

			m_LastCheckpointSpeed = Sonic::Player::CPlayerSpeedContext::GetInstance()->GetVelocity().norm();

			// Update speed record if current speed is higher.
			if (m_LastCheckpointSpeed > rStatistics.HighestSpeed)
				rStatistics.HighestSpeed = m_LastCheckpointSpeed;

			LOGFN_UTILITY("New high speed record: {}", rStatistics.HighestSpeed);

			// Increase total speed for the speed bonus.
			if (Configuration::IsRewardSpeedBonus)
			{
				rStatistics.TotalSpeed += m_LastCheckpointSpeed * TableProvider::GetMultiplierTable().SpeedBonusMultiplier;

				LOGFN_UTILITY("Total speed: {}", rStatistics.TotalSpeed);
			}

			// Store the current score so we can restore it later upon death if requested.
			if (Configuration::IsRestoreLastCheckpointScore)
				m_LastCheckpointScore = score;

			// Increase total checkpoint count.
			rStatistics.TotalPointMarkers++;

			break;
		}

		case ScoreType::RedRing:
			score = rScoreTable.RedRing;
			rStatistics.TotalRedRings++;
			break;

		case ScoreType::RainbowRing:
			score = rScoreTable.RainbowRing;
			rStatistics.TotalRainbowRings++;
			break;

		case ScoreType::ItemBox:
			score = rScoreTable.ItemBox;
			rStatistics.TotalItemBoxes++;
			break;

		case ScoreType::SuperRing:
			score = rScoreTable.SuperRing;
			rStatistics.TotalSuperRings++;
			break;

		case ScoreType::Trick:
		case ScoreType::BoardTrick:
			score = BonusProvider::GetTrickBonus(in_type == ScoreType::Trick ? rScoreTable.Trick : rScoreTable.BoardTrick);
			rStatistics.TotalTricks++;
			break;

		case ScoreType::TrickFinish:
			score = rScoreTable.TrickFinish;
			BonusProvider::ResetTrickBonus();
			rStatistics.TotalTricks++;
			break;

		case ScoreType::Life:
			score = rScoreTable.Life;
			break;

		case ScoreType::DashRing:
			score = rScoreTable.DashRing;
			rStatistics.TotalDashRings++;
			break;

		case ScoreType::QuickStep:
			score = rScoreTable.QuickStep;
			rStatistics.TotalQuickSteps++;
			break;

		case ScoreType::Drift:
			score = rScoreTable.Drift;
			rStatistics.TotalDrifts++;
			break;

		case ScoreType::Balloon:
			score = rScoreTable.Balloon;
			rStatistics.TotalBalloons++;
			break;

		case ScoreType::Super:
			score = rScoreTable.Super;
			break;
	}

	AddScore(score);

	m_FinalScore = m_CurrentScore;

	LOGFN_UTILITY("Added {} points from type {}.", score, int(in_type));

	return m_FinalScore;
}

int& __fastcall ScoreProvider::RemoveScore(int in_score, bool in_isResult)
{
	auto& rScore = in_isResult
		? m_FinalScore
		: m_CurrentScore;

	rScore = std::clamp(rScore - in_score, 0, Configuration::MaxScore);

	return in_isResult ? m_FinalScore : m_CurrentScore;
}

int& ScoreProvider::SetScore(int in_score)
{
	return m_CurrentScore = in_score;
}

int& ScoreProvider::GetCurrentScore()
{
	return m_CurrentScore;
}

int& ScoreProvider::GetFinalScore()
{
	return m_FinalScore;
}

int& ScoreProvider::GetLastCheckpointScore()
{
	return m_LastCheckpointScore;
}

float& ScoreProvider::GetLastCheckpointSpeed()
{
	return m_LastCheckpointSpeed;
}

RankType ScoreProvider::GetRank(bool in_isPerfectBonus)
{
	RankType result{};

	auto& rRankTable = TableProvider::GetRankTables()[g_pStageID];

	auto score = ScoreProvider::GetFinalScore();
	auto S = rRankTable.S;
	auto A = rRankTable.A;
	auto B = rRankTable.B;
	auto C = rRankTable.C;
	auto D = rRankTable.D;

	if (Configuration::PerfectBonusType == PerfectBonusType::Disabled && S != -1 && score > S)
		return RankType::S;

	if (score < A)
	{
		if (score < B)
		{
			if (score < C)
			{
				result = RankType::D;

				if (D != -1 && score < D)
				{
					result = RankType::E;
				}
			}
			else
			{
				result = RankType::C;
			}
		}
		else
		{
			result = RankType::B;
		}
	}
	else
	{
		result = RankType::A;
	}

	return RankType(in_isPerfectBonus && Configuration::PerfectBonusType != PerfectBonusType::Disabled ? int(result) + 1 : int(result));
}

ResultsDescription& ScoreProvider::GetResults()
{
	return m_Results;
}

void ScoreProvider::ComputeResults()
{
	auto& rStatistics = StatisticsProvider::GetStatistics();
	auto& rBonusTable = TableProvider::GetBonusTable();
	auto& rRankTable = TableProvider::GetRankTables()[g_pStageID];

	auto ringBonus = LuaSystem::RunExpression<int>(rBonusTable.pRingBonusExpression);

	AddScore(LuaSystem::RunExpression<int>(rBonusTable.pTimeBonusExpression), true);
	AddScore(ringBonus, true);
	AddScore(LuaSystem::RunExpression<int>(rBonusTable.pSpeedBonusExpression), true);
	AddScore(LuaSystem::RunExpression<int>(rBonusTable.pUserExpression), true);

	m_Results.m_Score = m_FinalScore;
	m_Results.m_Rank = int(GetRank());
	m_Results.m_PerfectRank = int(GetRank(true));

	auto computeProgress = [=](float in_divider)
	{
		switch (RankType(m_Results.m_Rank))
		{
			case RankType::E:
				return 0.0f;

			case RankType::D:
				return (in_divider / float(rRankTable.C)) / 3.0f;

			case RankType::C:
			{
				const float baseScore = float(rRankTable.C);
				return (1.0f / 3.0f) + ((in_divider - baseScore) / ((float)rRankTable.B - baseScore)) / 3.0f;
			}

			case RankType::B:
			{
				const float baseScore = float(rRankTable.B);
				return (2.0f / 3.0f) + ((in_divider - baseScore) / ((float)rRankTable.A - baseScore)) / 3.0f;
			}
		}

		return 1.0f;
	};

	m_Results.m_TimeProgress = computeProgress(float(m_FinalScore - ringBonus));

	m_Results.m_RingProgress = (m_Results.m_TimeProgress >= 1.0f || rStatistics.RingCount == 0)
		? m_Results.m_TimeProgress + 0.0001f
		: computeProgress(float(m_FinalScore + ringBonus) / float(rStatistics.RingCount)) + 0.0001f;
}

void ScoreProvider::Reset(bool in_isUseLastCheckpointScore)
{
	if (!in_isUseLastCheckpointScore)
		m_LastCheckpointScore = 0;

	m_FinalScore = m_CurrentScore = in_isUseLastCheckpointScore
		? m_LastCheckpointScore
		: 0;

	StatisticsProvider::GetStatistics().Reset();
}
