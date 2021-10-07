#pragma once

// Creates a pointer to a function from a loaded library.
#define LIB_FUNCTION(returnType, libraryName, procName, ...) \
    typedef returnType _##procName(__VA_ARGS__); \
    _##procName* procName = (_##procName*)GetProcAddress(GetModuleHandle(TEXT(libraryName)), #procName);

class ScoreGenerationsAPI
{
private:
	/// <summary>
	/// Adds score to the current score counter.
	/// </summary>
	/// <param name="scoreToReward">The amount of score to reward.</param>
	LIB_FUNCTION(void, "ScoreGenerations.dll", API_AddScore, int scoreToReward);

	/// <summary>
	/// Sets the current score counter to the input number.
	/// </summary>
	/// <param name="score">Score to set to.</param>
	LIB_FUNCTION(void, "ScoreGenerations.dll", API_SetScore, int score);

	/// <summary>
	/// Returns the current score.
	/// </summary>
	LIB_FUNCTION(int, "ScoreGenerations.dll", API_GetScore);

	/// <summary>
	/// Forces Score Generations to use the configuration from the current mod.
	/// </summary>
	LIB_FUNCTION(void, "ScoreGenerations.dll", API_ForceConfiguration, const char* path);

public:
	/// <summary>
	/// Default implementation of Score Generations SDK for static functions.
	/// </summary>
	static ScoreGenerationsAPI Instance;

	/// <summary>
	/// Adds score to the current score counter.
	/// </summary>
	/// <param name="scoreToReward">The amount of score to reward.</param>
	static void AddScore(int scoreToReward);

	/// <summary>
	/// Sets the current score counter to the input number.
	/// </summary>
	/// <param name="score">Score to set to.</param>
	static void SetScore(int score);

	/// <summary>
	/// Returns the current score.
	/// </summary>
	static int GetScore();

	/// <summary>
	/// Forces Score Generations to use the configuration from the current mod.
	/// </summary>
	static void ForceConfiguration(const char* path);
};

inline ScoreGenerationsAPI ScoreGenerationsAPI::Instance;

inline void ScoreGenerationsAPI::AddScore(int scoreToReward)
{
	if (ScoreGenerationsAPI::Instance.API_AddScore == nullptr)
		return;

	ScoreGenerationsAPI::Instance.API_AddScore(scoreToReward);
}

inline void ScoreGenerationsAPI::SetScore(int score)
{
	if (ScoreGenerationsAPI::Instance.API_SetScore == nullptr)
		return;

	ScoreGenerationsAPI::Instance.API_SetScore(score);
}

inline int ScoreGenerationsAPI::GetScore()
{
	if (ScoreGenerationsAPI::Instance.API_GetScore == nullptr)
		return -1;

	return ScoreGenerationsAPI::Instance.API_GetScore();
}

inline void ScoreGenerationsAPI::ForceConfiguration(const char* path)
{
	if (ScoreGenerationsAPI::Instance.API_ForceConfiguration == nullptr)
		return;

	ScoreGenerationsAPI::Instance.API_ForceConfiguration(path);
}