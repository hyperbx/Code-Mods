#pragma once

#include <gmath/Vector2.hpp>
#include <gmath/Vector3.hpp>
#include <gmath/Quaternion.hpp>

typedef struct
{
	/// <summary>
	/// ランクタイム
	/// </summary>
	uint32_t rankTime[4];

	/// <summary>
	/// 全島ランクタイム
	/// </summary>
	uint32_t rankTimeAll[4];

} BattleRushPhaseRankParameter;

enum BgmType : int8_t
{
    INVALID = -1,
    ENEMY_BATTLE = 0,
    FORCE_BATTLE_FIELD = 1,
    MINIBOSS_CHARGER_BATTLE = 2,
    MINIBOSS_DARUMA_BATTLE = 3,
    MINIBOSS_SPIDER_BATTLE = 4,
    MINIBOSS_BLADE_BATTLE = 5,
    MINIBOSS_FLYER_BATTLE = 6,
    MINIBOSS_TRACKER_BATTLE = 7,
    MINIBOSS_ASHURA_BATTLE = 8,
    MINIBOSS_SKIER_BATTLE = 9,
    MINIBOSS_SUMO_BATTLE = 10,
    MINIBOSS_TYRANT_BATTLE = 11,
    MINIBOSS_STRIDER_BATTLE = 12,
    MINIBOSS_WARSHIP_BATTLE = 13,
    ENEMY_AQUABALL = 14,
    TUTORIAL_BLADE_BATTLE = 15,
};

typedef struct
{
	/// <summary>
	/// フェイズ数
	/// </summary>
	uint32_t numPhases;

	/// <summary>
	/// 各フェイズのリミット時間[sec]
	/// </summary>
	float phaseLimitTime[11];

	/// <summary>
	/// 各フェイズのクリア遷移待機時間[sec]
	/// </summary>
	float phaseClearedTime[11];

	/// <summary>
	/// 各フェイズのリザルト待機時間[sec]
	/// </summary>
	float phaseResultTime[11];

	/// <summary>
	/// 各フェイズのランクタイム[sec]
	/// </summary>
	BattleRushPhaseRankParameter phaseRank[11];

	/// <summary>
	/// 各フェイズのベースBGM
	/// </summary>
	BgmType phaseBgmType[11];

	/// <summary>
	/// 時間:時
	/// </summary>
	uint32_t hour;

	/// <summary>
	/// 時間:分
	/// </summary>
	uint32_t minute;

} BattleRushStageParameter;

typedef struct
{
	/// <summary>
	/// バトルラッシュステージ
	/// </summary>
	BattleRushStageParameter stages[4];

	/// <summary>
	/// フェイズリザルト表示時間
	/// </summary>
	float viewPaseResultTime;

} BattleRushParameter;
