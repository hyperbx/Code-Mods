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

inline void ScoreGenerationsAPI::AddScore(int scoreToReward)
{
	if (GetInstance()->API_AddScore == nullptr)
		return;

	GetInstance()->API_AddScore(scoreToReward);
}

inline void ScoreGenerationsAPI::SetScore(int score)
{
	if (GetInstance()->API_SetScore == nullptr)
		return;

	GetInstance()->API_SetScore(score);
}

inline int ScoreGenerationsAPI::GetScore()
{
	if (GetInstance()->API_GetScore == nullptr)
		return -1;

	return GetInstance()->API_GetScore();
}

inline void ScoreGenerationsAPI::ForceConfiguration(const char* path)
{
	if (GetInstance()->API_ForceConfiguration == nullptr)
		return;

	GetInstance()->API_ForceConfiguration(path);
}