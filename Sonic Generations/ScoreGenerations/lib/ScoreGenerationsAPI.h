#pragma once

// Standard library
#include <string>
#include <unordered_map>

// Internal headers
#include "Statistics.h"
#include "Tables.h"

// Creates a pointer to a function from a loaded library.
#define LIB_FUNCTION(returnType, libraryName, procName, ...) \
    typedef returnType _##procName(__VA_ARGS__); \
    _##procName* procName = (_##procName*)GetProcAddress(GetModuleHandle(TEXT(libraryName)), #procName);

// Creates a void export based on the API's requirements.
#define VOID_EXPORT(libFunctionName, ...) \
	if (GetInstance()->libFunctionName == nullptr) \
		return; \
	GetInstance()->libFunctionName(__VA_ARGS__);

// Creates an integer export based on the API's requirements.
#define INT_EXPORT(libFunctionName, ...) \
	if (GetInstance()->libFunctionName == nullptr) \
		return -1; \
	return GetInstance()->libFunctionName(__VA_ARGS__);

// Creates a Boolean export based on the API's requirements.
#define BOOL_EXPORT(libFunctionName, ...) \
	if (GetInstance()->libFunctionName == nullptr) \
		return false; \
	return GetInstance()->libFunctionName(__VA_ARGS__);

// Creates a generic export based on the API's requirements.
#define GENERIC_EXPORT(returnType, libFunctionName, ...) \
	if (GetInstance()->libFunctionName == nullptr) \
		return returnType(); \
	return GetInstance()->libFunctionName(__VA_ARGS__);

/// <summary>
/// Index-based ranks.
/// </summary>
enum RankType
{
	E = -1,
	D,
	C,
	B,
	A,
	S
};

class ScoreGenerationsAPI
{
private:
	LIB_FUNCTION(void, "ScoreGenerations.dll", API_AddScore, int scoreToReward);

	LIB_FUNCTION(void, "ScoreGenerations.dll", API_SetScore, int score);

	LIB_FUNCTION(void, "ScoreGenerations.dll", API_ForceConfiguration, const char* path);

	LIB_FUNCTION(int, "ScoreGenerations.dll", API_GetScore);

	LIB_FUNCTION(int, "ScoreGenerations.dll", API_GetTotalScore);

	LIB_FUNCTION(RankType, "ScoreGenerations.dll", API_GetRank);

	LIB_FUNCTION(bool, "ScoreGenerations.dll", API_IsStageForbidden);

	LIB_FUNCTION(int, "ScoreGenerations.dll", API_ComputeTimeBonus);

	LIB_FUNCTION(int, "ScoreGenerations.dll", API_ComputeRingBonus);

	LIB_FUNCTION(int, "ScoreGenerations.dll", API_ComputeSpeedBonus);

	LIB_FUNCTION(int, "ScoreGenerations.dll", API_ComputeUserBonus);

	LIB_FUNCTION(Statistics::Totals, "ScoreGenerations.dll", API_GetStatistics);

	LIB_FUNCTION(Tables::ScoreTable, "ScoreGenerations.dll", API_GetScoreTable);

	// C++ was complaining about using a macro for unordered_map, so this'll have to be manual.
	typedef std::unordered_map<std::string, Tables::RankTable> _API_GetRankTables();
	_API_GetRankTables* API_GetRankTables = (_API_GetRankTables*)GetProcAddress(GetModuleHandle(TEXT("ScoreGenerations.dll")), "API_GetRankTables");

	LIB_FUNCTION(Tables::BonusTable, "ScoreGenerations.dll", API_GetBonusTable);

	LIB_FUNCTION(Tables::MultiplierTable, "ScoreGenerations.dll", API_GetMultiplierTable);

	LIB_FUNCTION(Tables::TimerTable, "ScoreGenerations.dll", API_GetTimerTable);

	LIB_FUNCTION(void, "ScoreGenerations.dll", API_SetVisibility, bool isVisible);

	LIB_FUNCTION(bool, "ScoreGenerations.dll", API_GetVisibility);

public:
	/// <summary>
	/// Gets the current instance of the API and creates a new one if it's a null pointer.
	/// </summary>
	static ScoreGenerationsAPI* GetInstance()
	{
		static ScoreGenerationsAPI* instance;

		return instance != nullptr ? instance : instance = new ScoreGenerationsAPI();
	}

	/// <summary>
	/// Adds score to the current score counter.
	/// </summary>
	/// <param name="scoreToReward">The amount of score to reward.</param>
	static void AddScore(int scoreToReward)
	{
		VOID_EXPORT(API_AddScore, scoreToReward);
	}

	/// <summary>
	/// Sets the current score counter to the input number.
	/// </summary>
	/// <param name="score">Score to set to.</param>
	static void SetScore(int score)
	{
		VOID_EXPORT(API_SetScore, score);
	}

	/// <summary>
	/// Forces Score Generations to use the configuration from the current mod.
	/// </summary>
	static void ForceConfiguration(const char* path)
	{
		VOID_EXPORT(API_ForceConfiguration, path);
	}

	/// <summary>
	/// Returns the current score.
	/// </summary>
	static int GetScore()
	{
		INT_EXPORT(API_GetScore);
	}

	/// <summary>
	/// Returns the current total score.
	/// </summary>
	static int GetTotalScore()
	{
		INT_EXPORT(API_GetTotalScore);
	}

	/// <summary>
	/// Returns the current rank based on the total score.
	/// </summary>
	static int GetRank()
	{
		INT_EXPORT(API_GetRank);
	}

	/// <summary>
	/// Determines if the current stage ID is forbidden.
	/// </summary>
	static bool IsStageForbidden()
	{
		BOOL_EXPORT(API_IsStageForbidden);
	}

	/// <summary>
	/// Computes and returns the current time bonus.
	/// </summary>
	static int ComputeTimeBonus()
	{
		INT_EXPORT(API_ComputeTimeBonus);
	}

	/// <summary>
	/// Computes and returns the current ring bonus.
	/// </summary>
	static int ComputeRingBonus()
	{
		INT_EXPORT(API_ComputeRingBonus);
	}

	/// <summary>
	/// Computes and returns the current speed bonus.
	/// </summary>
	static int ComputeSpeedBonus()
	{
		INT_EXPORT(API_ComputeSpeedBonus);
	}

	/// <summary>
	/// Computes and returns the current user bonus.
	/// </summary>
	static int ComputeUserBonus()
	{
		INT_EXPORT(API_ComputeUserBonus);
	}

	/// <summary>
	/// Returns the table of statistics for current totals.
	/// </summary>
	static Statistics::Totals GetStatistics()
	{
		GENERIC_EXPORT(Statistics::Totals, API_GetStatistics);
	}

	/// <summary>
	/// Returns the score table.
	/// </summary>
	static Tables::ScoreTable GetScoreTable()
	{
		GENERIC_EXPORT(Tables::ScoreTable, API_GetScoreTable);
	}

	/// <summary>
	/// Returns the rank tables as an unordered map.
	/// </summary>
	static std::unordered_map<std::string, Tables::RankTable> GetRankTables()
	{
		if (GetInstance()->API_GetRankTables == nullptr)
			return std::unordered_map<std::string, Tables::RankTable>();

		GetInstance()->API_GetRankTables();
	}

	/// <summary>
	/// Returns the bonus table.
	/// </summary>
	static Tables::BonusTable GetBonusTable()
	{
		GENERIC_EXPORT(Tables::BonusTable, API_GetBonusTable);
	}

	/// <summary>
	/// Returns the multiplier table.
	/// </summary>
	static Tables::MultiplierTable GetMultiplierTable()
	{
		GENERIC_EXPORT(Tables::MultiplierTable, API_GetMultiplierTable);
	}

	/// <summary>
	/// Returns the timer table.
	/// </summary>
	static Tables::TimerTable GetTimerTable()
	{
		GENERIC_EXPORT(Tables::TimerTable, API_GetTimerTable);
	}

	/// <summary>
	/// Sets the visibility of the score counter (requires stage reload).
	/// </summary>
	static void SetVisibility(bool isVisible)
	{
		VOID_EXPORT(API_SetVisibility, isVisible);
	}

	/// <summary>
	/// Gets the visibility of the score counter.
	/// </summary>
	static bool GetVisibility()
	{
		BOOL_EXPORT(API_GetVisibility);
	}

	/// <summary>
	/// Checks if the Score Generations module is attached to the current process.
	/// </summary>
	static bool IsAttached()
	{
		if (GetModuleHandle(TEXT("ScoreGenerations.dll")) == nullptr)
			return false;

		return true;
	}
};