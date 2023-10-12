#pragma once

#include <gmath/Vector2.hpp>
#include <gmath/Vector3.hpp>
#include <gmath/Quaternion.hpp>

typedef struct
{
	/// <summary>
	/// 最小攻撃力
	/// </summary>
	uint16_t pointMin;

	/// <summary>
	/// 最大攻撃力
	/// </summary>
	uint16_t pointMax;

	/// <summary>
	/// ダメージランダム変動幅
	/// </summary>
	float damageRandomRate;

	/// <summary>
	/// ダメージランダム変動幅/スパソニ
	/// </summary>
	float damageRandomRateSS;

	/// <summary>
	/// 残像ダメージ値レート
	/// </summary>
	float shapeDamageRate;

	/// <summary>
	/// 残像スタン値レート
	/// </summary>
	float shapeStunRate;

	/// <summary>
	/// 残像怯み値レート
	/// </summary>
	float shapeStaggerRate;

} PlayerParamOffensive;

typedef struct
{
	/// <summary>
	/// 最低防御率
	/// </summary>
	uint8_t rateMin;

	/// <summary>
	/// 最高防御率
	/// </summary>
	uint8_t rateMax;

	/// <summary>
	/// 最低保障リングドロップ数
	/// </summary>
	uint16_t infimumDropRings;

} PlayerParamDefensive;

typedef struct
{
	/// <summary>
	/// 攻撃力
	/// </summary>
	PlayerParamOffensive offensive;

	/// <summary>
	/// 防御力
	/// </summary>
	PlayerParamDefensive defensive;

	/// <summary>
	/// クリティカル時のダメージレート
	/// </summary>
	float criticalDamageRate;

	/// <summary>
	/// クリティカルの発生確率
	/// </summary>
	float criticalRate;

	/// <summary>
	/// クリティカルの発生確率/スパソニ
	/// </summary>
	float criticalRateSS;

	/// <summary>
	/// ダウン中のダメージレート
	/// </summary>
	float downedDamageRate;

} PlayerParamAttackCommon;

enum HitSE : int8_t
{
	SE_None = -1,
	Weak = 0,
	Strong = 1,
	VeryStrong = 2,
};

typedef struct
{
	const char* value;

	INSERT_PADDING(8);

} cstring;

typedef struct
{
	/// <summary>
	/// ダメージレート/ソニック
	/// </summary>
	float damageRate;

	/// <summary>
	/// ダメージレート/スーパーソニック
	/// </summary>
	float damageRateSS;

	/// <summary>
	/// アクセルモード時のダメージ倍率
	/// </summary>
	float damageRateAcceleMode;

	/// <summary>
	/// マニュアルモード時のダメージ倍率
	/// </summary>
	float damageRateManual;

	/// <summary>
	/// スタン値
	/// </summary>
	float stunPoint;

	/// <summary>
	/// よろめき値
	/// </summary>
	float staggerPoint;

	/// <summary>
	/// ダメージ速度
	/// </summary>
	Vector3 velocity;

	/// <summary>
	/// ダメージ速度維持時間
	/// </summary>
	float velocityKeepTime;

	/// <summary>
	/// コンボメーター増加量
	/// </summary>
	float addComboValue;

	/// <summary>
	/// コンボメーター増加量/アクセル時
	/// </summary>
	float addComboValueAccele;

	/// <summary>
	/// コンボメーター増加量/スパソニ
	/// </summary>
	float addComboValueSS;

	/// <summary>
	/// コンボメーター増加量/スパソニアクセル時
	/// </summary>
	float addComboValueAcceleSS;

	/// <summary>
	/// クイックサイループゲージ増加量
	/// </summary>
	float addQuickCyloopEnergy;

	/// <summary>
	/// クイックサイループゲージ増加量/アクセル時
	/// </summary>
	float addQuickCyloopEnergyAccele;

	/// <summary>
	/// クイックサイループゲージ増加量/スパソニ
	/// </summary>
	float addQuickCyloopEnergySS;

	/// <summary>
	/// クイックサイループゲージ増加量/スパソニアクセル時
	/// </summary>
	float addQuickCyloopEnergyAcceleSS;

	/// <summary>
	/// クイックサイループゲージ増加量/ガード時
	/// </summary>
	float addQuickCyloopEnergyGuard;

	/// <summary>
	/// クイックサイループゲージ増加量/ガード&アクセル時
	/// </summary>
	float addQuickCyloopEnergyAcceleGuard;

	/// <summary>
	/// ギミックに与えるダメージ速度
	/// </summary>
	Vector3 gimmickVelocity;

	/// <summary>
	/// ヒット後ターゲットから除外する時間
	/// </summary>
	float ignoreTime;

	/// <summary>
	/// 属性
	/// </summary>
	uint16_t attributes;

	/// <summary>
	/// ヒットSE
	/// </summary>
	HitSE se;

	/// <summary>
	/// ヒットエフェクト/ソニック
	/// </summary>
	cstring hitEffectName;

	/// <summary>
	/// ヒットエフェクト/スーパーソニック
	/// </summary>
	cstring hitEffectNameSS;

	/// <summary>
	/// ヒットストップ/ソニック
	/// </summary>
	cstring hitStopName;

	/// <summary>
	/// ヒットストップ/撃破/ソニック
	/// </summary>
	cstring hitStopNameDead;

	/// <summary>
	/// ヒットストップ/ボス撃破/ソニック
	/// </summary>
	cstring hitStopNameDeadBoss;

	/// <summary>
	/// ヒットストップ/スーパーソニック
	/// </summary>
	cstring hitStopNameSS;

	/// <summary>
	/// ヒットストップ/撃破/スーパーソニック
	/// </summary>
	cstring hitStopNameDeadSS;

	/// <summary>
	/// ヒットカメラ振動/ソニック
	/// </summary>
	cstring hitCameraShakeName;

	/// <summary>
	/// ヒットカメラ振動/撃破/ソニック
	/// </summary>
	cstring hitCameraShakeNameDead;

	/// <summary>
	/// ヒットカメラ振動/ボス撃破/ソニック
	/// </summary>
	cstring hitCameraShakeNameDeadBoss;

	/// <summary>
	/// ヒットカメラ振動/スーパーソニック
	/// </summary>
	cstring hitCameraShakeNameSS;

	/// <summary>
	/// ヒットカメラ振動/撃破/スーパーソニック
	/// </summary>
	cstring hitCameraShakeNameDeadSS;

	/// <summary>
	/// ヒットコントローラ振動/ソニック
	/// </summary>
	cstring hitVibrationName;

	/// <summary>
	/// ヒットコントローラ振動/スーパーソニック
	/// </summary>
	cstring hitVibrationNameSS;

} PlayerParamAttackData;

typedef struct
{
	/// <summary>
	/// 共通
	/// </summary>
	PlayerParamAttackCommon common;

	/// <summary>
	/// Spin Jump
	/// </summary>
	PlayerParamAttackData spinAttack;

	/// <summary>
	/// Spin Dash
	/// </summary>
	PlayerParamAttackData spinDash;

	/// <summary>
	/// Homing Attack
	/// </summary>
	PlayerParamAttackData homingAttack;

	/// <summary>
	/// Aerial Homing Attack
	/// </summary>
	PlayerParamAttackData homingAttackAir;

	/// <summary>
	/// Pursuit Kick
	/// </summary>
	PlayerParamAttackData pursuitKick;

	/// <summary>
	/// Stomping
	/// </summary>
	PlayerParamAttackData stomping;

	/// <summary>
	/// Stomping Attack
	/// </summary>
	PlayerParamAttackData stompingAttack;

	/// <summary>
	/// Bound Stomping Last
	/// </summary>
	PlayerParamAttackData boundStompingLast;

	/// <summary>
	/// Sliding
	/// </summary>
	PlayerParamAttackData sliding;

	/// <summary>
	/// Loop Kick
	/// </summary>
	PlayerParamAttackData loopKick;

	/// <summary>
	/// Crasher
	/// </summary>
	PlayerParamAttackData crasher;

	/// <summary>
	/// Spin Slash Homing
	/// </summary>
	PlayerParamAttackData spinSlashHoming;

	/// <summary>
	/// Spin Slash
	/// </summary>
	PlayerParamAttackData spinSlash;

	/// <summary>
	/// Spin Slash Last
	/// </summary>
	PlayerParamAttackData spinSlashLast;

	/// <summary>
	/// Sonic Boom
	/// </summary>
	PlayerParamAttackData sonicBoom;

	/// <summary>
	/// Cross Slash
	/// </summary>
	PlayerParamAttackData crossSlash;

	/// <summary>
	/// Homing Shot
	/// </summary>
	PlayerParamAttackData homingShot;

	/// <summary>
	/// Charge Attack
	/// </summary>
	PlayerParamAttackData chargeAttack;

	/// <summary>
	/// Charge Attack Last
	/// </summary>
	PlayerParamAttackData chargeAttackLast;

	/// <summary>
	/// Cyloop
	/// </summary>
	PlayerParamAttackData cyloop;

	/// <summary>
	/// Quick Cyloop
	/// </summary>
	PlayerParamAttackData cyloopQuick;

	/// <summary>
	/// Quick Cyloop Aerial
	/// </summary>
	PlayerParamAttackData cyloopAerial;

	/// <summary>
	/// Accele Combo 1
	/// </summary>
	PlayerParamAttackData accele1;

	/// <summary>
	/// Accele Combo 2
	/// </summary>
	PlayerParamAttackData accele2;

	/// <summary>
	/// Accele Combo 1 Aerial
	/// </summary>
	PlayerParamAttackData aerialAccele1;

	/// <summary>
	/// Accele Combo 2 Aerial
	/// </summary>
	PlayerParamAttackData aerialAccele2;

	/// <summary>
	/// Combo Finish
	/// </summary>
	PlayerParamAttackData comboFinish;

	/// <summary>
	/// Combo Finish Front
	/// </summary>
	PlayerParamAttackData comboFinishF;

	/// <summary>
	/// Combo Finish Back
	/// </summary>
	PlayerParamAttackData comboFinishB;

	/// <summary>
	/// Combo Finish Left
	/// </summary>
	PlayerParamAttackData comboFinishL;

	/// <summary>
	/// Combo Finish Right
	/// </summary>
	PlayerParamAttackData comboFinishR;

	/// <summary>
	/// Accele Combo Finish
	/// </summary>
	PlayerParamAttackData acceleComboFinish;

	/// <summary>
	/// Accele Combo Finish Front
	/// </summary>
	PlayerParamAttackData acceleComboFinishF;

	/// <summary>
	/// Accele Combo Finish Back
	/// </summary>
	PlayerParamAttackData acceleComboFinishB;

	/// <summary>
	/// Accele Combo Finish Left
	/// </summary>
	PlayerParamAttackData acceleComboFinishL;

	/// <summary>
	/// Accele Combo Finish Right
	/// </summary>
	PlayerParamAttackData acceleComboFinishR;

	/// <summary>
	/// Smash
	/// </summary>
	PlayerParamAttackData smash;

	/// <summary>
	/// Smash Last
	/// </summary>
	PlayerParamAttackData smashLast;

	/// <summary>
	/// Slingshot
	/// </summary>
	PlayerParamAttackData slingShot;

	/// <summary>
	/// Knuckles Punch1
	/// </summary>
	PlayerParamAttackData knucklesPunch1;

	/// <summary>
	/// Knuckles Punch2
	/// </summary>
	PlayerParamAttackData knucklesPunch2;

	/// <summary>
	/// Knuckles Uppercut
	/// </summary>
	PlayerParamAttackData knucklesUppercut;

	/// <summary>
	/// Amy Tarot Attack
	/// </summary>
	PlayerParamAttackData amyTarotAttack;

	/// <summary>
	/// Amy Tarot Rolling
	/// </summary>
	PlayerParamAttackData amyTarotRolling;

} PlayerParamAttack;

typedef struct
{
	/// <summary>
	/// 水中時の水抵抗係数
	/// </summary>
	float resistRate;

	/// <summary>
	/// 息継ぎ時の減速
	/// </summary>
	float breatheBrake;

	/// <summary>
	/// 息継ぎの拘束時間
	/// </summary>
	float breatheTime;

	/// <summary>
	/// 重力方向にかかる加速度
	/// </summary>
	float breatheGravity;

} PlayerParamWaterAct;

typedef struct
{
	/// <summary>
	/// 法線方向の初速基本値
	/// </summary>
	float baseSpeed;

	/// <summary>
	/// 上方向の初速
	/// </summary>
	float upSpeed;

	/// <summary>
	/// 上方向の初速　空中
	/// </summary>
	float upSpeedAir;

	/// <summary>
	/// エッジからの飛び出しの場合の最低速度
	/// </summary>
	float edgeSpeed;

	/// <summary>
	/// 他の空中アクションへ移行できる時間
	/// </summary>
	float airActionTime;

	/// <summary>
	/// 壁移動へ移行できる時間
	/// </summary>
	float wallMoveTime;

} PlayerParamBaseJump;

typedef struct
{
	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// [通常]斜面滑り力
	/// </summary>
	float slidePower;

	/// <summary>
	/// [通常]ブレーキ力
	/// </summary>
	float brakeForce;

	/// <summary>
	/// [S字内]斜面滑り力
	/// </summary>
	float slidePowerSlalom;

	/// <summary>
	/// [S字内]ブレーキ力
	/// </summary>
	float brakeForceSlalom;

	/// <summary>
	/// 終了速度
	/// </summary>
	float releaseSpeed;

	/// <summary>
	/// 入力方向に対する重力加速度を使用するか
	/// </summary>
	bool useInput;

} PlayerParamBallMove;

typedef struct
{
	/// <summary>
	/// 幅
	/// </summary>
	float width;

	/// <summary>
	/// 距離
	/// </summary>
	float distance;

	/// <summary>
	/// UV:U開始
	/// </summary>
	float u0;

	/// <summary>
	/// UV:U終了
	/// </summary>
	float u1;

} PlayerParamLocusData;

typedef struct
{
	/// <summary>
	/// data
	/// </summary>
	PlayerParamLocusData data[4];

} PlayerParamLocus;

typedef struct
{
	/// <summary>
	/// エフェクトの再生間隔
	/// </summary>
	float effectSpanTime;

	/// <summary>
	/// エフェクトの再生時間
	/// </summary>
	float effectLifeTime;

	/// <summary>
	/// エフェクト発生位置オフセット
	/// </summary>
	float effectOffsetDistance;

	/// <summary>
	/// エフェクトオーバーラップオフセット
	/// </summary>
	float effectOverlapDistance;

} PlayerParamAuraTrain;

typedef struct
{
	/// <summary>
	/// リングレベル段数
	/// </summary>
	uint8_t ringsLevel;

	/// <summary>
	/// スピードレベル段数
	/// </summary>
	uint8_t speedLevel;

	/// <summary>
	/// 攻撃レベル段数
	/// </summary>
	uint8_t offensiveLevel;

	/// <summary>
	/// 防御レベル段数
	/// </summary>
	uint8_t defensiveLevel;

} PlayerParamLevel;

typedef struct
{
	/// <summary>
	/// クールタイム
	/// </summary>
	float coolTime;

} PlayerParamBarrierWall;

typedef struct
{
	/// <summary>
	/// 島別レート
	/// </summary>
	float rates[5];

} PlayerParamDamageRateLevel;

typedef struct
{
	/// <summary>
	/// 難易度
	/// </summary>
	PlayerParamDamageRateLevel diffculties[4];

} PlayerParamDamageRate;

typedef struct
{
	/// <summary>
	/// ダメージ設定
	/// </summary>
	PlayerParamAttack attack;

	/// <summary>
	/// 水中専用挙動
	/// </summary>
	PlayerParamWaterAct wateract;

	/// <summary>
	/// BASEジャンプ
	/// </summary>
	PlayerParamBaseJump basejump;

	/// <summary>
	/// ボール移動
	/// </summary>
	PlayerParamBallMove ballmove;

	/// <summary>
	/// 移動軌跡
	/// </summary>
	PlayerParamLocus locus;

	/// <summary>
	/// オーラトレイン
	/// </summary>
	PlayerParamAuraTrain auratrain;

	/// <summary>
	/// レベル段階数
	/// </summary>
	PlayerParamLevel level;

	/// <summary>
	/// 結界壁
	/// </summary>
	PlayerParamBarrierWall barrierWall;

	/// <summary>
	/// ダメージ倍率
	/// </summary>
	PlayerParamDamageRate damageRate;

} CommonPackage;

typedef struct
{
	/// <summary>
	/// コンボメーター減少速度/通常
	/// </summary>
	float declineSpeed;

	/// <summary>
	/// コンボメーター減少速度/アクセルモード
	/// </summary>
	float declineSpeedAccele;

	/// <summary>
	/// 被ダメージ時の減少量/通常
	/// </summary>
	float lossDamaged;

	/// <summary>
	/// 被ダメージ時の減少量/アクセルモード
	/// </summary>
	float lossDamagedAccele;

	/// <summary>
	/// コンボ水増しレート/アクセルモード
	/// </summary>
	uint32_t comboRateAccele;

} PlayerParamAcceleMode;

enum Condition : int8_t
{
	Time = 0,
	Animation = 1,
};

enum Shape : int8_t
{
	Sphere = 0,
	Cylinder = 1,
	Box = 2,
};

typedef struct
{
	/// <summary>
	/// 判定条件
	/// </summary>
	Condition condition;

	/// <summary>
	/// 判定回数
	/// </summary>
	int8_t count;

	/// <summary>
	/// 間隔時間
	/// </summary>
	float spanTime;

	/// <summary>
	/// 形状
	/// </summary>
	Shape shape;

	/// <summary>
	/// サイズ
	/// </summary>
	Vector3 shapeSize;

	/// <summary>
	/// 位置オフセット
	/// </summary>
	Vector3 shapeOffset;

} PlayerParamAttackCollider;

typedef struct
{
	/// <summary>
	/// ヒット判定
	/// </summary>
	PlayerParamAttackCollider hit;

	/// <summary>
	/// モーション再生速度比率
	/// </summary>
	float motionSpeedRatio;

	/// <summary>
	/// モーション再生速度比率/アクセル
	/// </summary>
	float motionSpeedRatioAccele;

} PlayerParamAcceleCombo;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamAcceleCombo sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamAcceleCombo superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamAcceleCombo superSonic2;

} PlayerParamAcceleComboSet;

typedef struct
{
	/// <summary>
	/// ループ半径
	/// </summary>
	float loopRadius;

	/// <summary>
	/// ループ時間
	/// </summary>
	float loopTime;

	/// <summary>
	/// ループ移動カーブ比率
	/// </summary>
	float loopSpeedCurveRatio;

	/// <summary>
	/// ループ後静止時間
	/// </summary>
	float loopEndStopTime;

	/// <summary>
	/// ループ後最大移動速度
	/// </summary>
	float loopEndSpeed;

	/// <summary>
	/// キック速度
	/// </summary>
	float kickSpeed;

	/// <summary>
	/// キック最大時間
	/// </summary>
	float failSafeTime;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

} PlayerParamLoopKick;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamLoopKick sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamLoopKick superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamLoopKick superSonic2;

} PlayerParamLoopKickSet;

typedef struct
{
	/// <summary>
	/// 開始前待機時間
	/// </summary>
	float startWait;

	/// <summary>
	/// ジグザグポイント毎の距離比率
	/// </summary>
	float distanceRatios[5];

	/// <summary>
	/// ジグザグポイント毎の角度
	/// </summary>
	float angles[5];

	/// <summary>
	/// ジグザグポイント毎の半径
	/// </summary>
	float radii[5];

	/// <summary>
	/// ジグザグ最大距離
	/// </summary>
	float distanceMax;

	/// <summary>
	/// ジグザク移動時間/最初
	/// </summary>
	float zigzagBeginOneStepTime;

	/// <summary>
	/// ジグザク移動時間/最後
	/// </summary>
	float zigzagEndOneStepTime;

	/// <summary>
	/// 突進速度
	/// </summary>
	float crasherSpeed;

	/// <summary>
	/// 突進最大時間
	/// </summary>
	float failSafeTime;

	/// <summary>
	/// カメラ距離
	/// </summary>
	float cameraDistance;

	/// <summary>
	/// カメラオフセット仰角
	/// </summary>
	float cameraOffsetElevation;

	/// <summary>
	/// カメラオフセット方位角
	/// </summary>
	float cameraOffsetAzimuth;

	/// <summary>
	/// カメラRoll
	/// </summary>
	float cameraRoll;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

} PlayerParamCrasher;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamCrasher sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamCrasher superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamCrasher superSonic2;

} PlayerParamCrasherSet;

typedef struct
{
	/// <summary>
	/// ヒット判定
	/// </summary>
	PlayerParamAttackCollider hit;

	/// <summary>
	/// ヒット判定/ラスト
	/// </summary>
	PlayerParamAttackCollider hitLast;

	/// <summary>
	/// 溜め時間
	/// </summary>
	float chargeTime;

	/// <summary>
	/// ホーミング速度
	/// </summary>
	float homingSpeed;

	/// <summary>
	/// バウンス時間
	/// </summary>
	float bounceTime;

	/// <summary>
	/// 回転攻撃半径
	/// </summary>
	float radius;

	/// <summary>
	/// 回転攻撃時間
	/// </summary>
	float slashTime;

	/// <summary>
	/// 回転数
	/// </summary>
	int8_t numSlashs;

	/// <summary>
	/// 回転角度
	/// </summary>
	float angle;

	/// <summary>
	/// ダメージ判定をラストヒットに切り替えるタイミング
	/// </summary>
	float lastHitTime;

	/// <summary>
	/// スロー比率
	/// </summary>
	float slowRatio0;

	/// <summary>
	/// スロー比率/回転中
	/// </summary>
	float slowRatio1;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

	/// <summary>
	/// カメラ名/ヒット後
	/// </summary>
	cstring cameraNamePost;

	/// <summary>
	/// 回転中カメラ振動
	/// </summary>
	cstring cameraShakeName;

} PlayerParamSpinSlash;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamSpinSlash sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamSpinSlash superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamSpinSlash superSonic2;

} PlayerParamSpinSlashSet;

typedef struct
{
	/// <summary>
	/// ヒット判定
	/// </summary>
	PlayerParamAttackCollider hit;

	/// <summary>
	/// ヒット判定/ラスト
	/// </summary>
	PlayerParamAttackCollider hitLast;

	/// <summary>
	/// 空振り無効時間
	/// </summary>
	float ignoreSwingingTime;

	/// <summary>
	/// 上昇中のエネミースロー比率
	/// </summary>
	float riseSlowRatio;

	/// <summary>
	/// 上昇時間
	/// </summary>
	float riseTime;

	/// <summary>
	/// 上昇距離
	/// </summary>
	float riseDistance;

	/// <summary>
	/// 上昇距離2
	/// </summary>
	float preRiseDistance;

	/// <summary>
	/// 上昇距離2/ラストヒット後
	/// </summary>
	float postRiseDistance;

	/// <summary>
	/// 上昇後の打ち上げ速度
	/// </summary>
	float lastVelocity;

	/// <summary>
	/// 螺旋半径
	/// </summary>
	float spiralRadius;

	/// <summary>
	/// 螺旋が最大にまで広がる時間
	/// </summary>
	float spiralRadiusEaseInTime;

	/// <summary>
	/// 螺旋が最小にまで閉じる時間
	/// </summary>
	float spiralRadiusEaseOutTime;

	/// <summary>
	/// 螺旋回転速度
	/// </summary>
	float spiralAngularSpeed;

	/// <summary>
	/// ダメージ判定をラストヒットに切り替えるタイミング
	/// </summary>
	float lastHitTime;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

} PlayerParamChargeAttack;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamChargeAttack sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamChargeAttack superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamChargeAttack superSonic2;

} PlayerParamChargeAttackSet;

typedef struct
{
	/// <summary>
	/// ヒット判定/強化ストンピング
	/// </summary>
	PlayerParamAttackCollider hit;

	/// <summary>
	/// ヒット判定/強化ストンピングラスト
	/// </summary>
	PlayerParamAttackCollider hitLast;

	/// <summary>
	/// 上昇時間
	/// </summary>
	float riseTime;

	/// <summary>
	/// フリップ速度
	/// </summary>
	float flipSpeed;

	/// <summary>
	/// 攻撃モーション時間
	/// </summary>
	float motionTime;

	/// <summary>
	/// ダメージ判定をラストヒットに切り替えるタイミング
	/// </summary>
	float lastHitTime;

	/// <summary>
	/// スロー比率
	/// </summary>
	float slowRatio;

	/// <summary>
	/// 押し込み/最小押し込み時間
	/// </summary>
	float minPressTime;

	/// <summary>
	/// 押し込み/最小押し込み時間になる落下高度
	/// </summary>
	float minPressTimeHeight;

	/// <summary>
	/// 押し込み/最大押し込み時間
	/// </summary>
	float maxPressTime;

	/// <summary>
	/// 押し込み/最大押し込み時間になる落下高度
	/// </summary>
	float maxPressTimeHeight;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// コンボ中ワープ距離/Asura専用
	/// </summary>
	Vector3 offsetAsura;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

	/// <summary>
	/// カメラ名/連撃開始後
	/// </summary>
	cstring cameraNameBarrage;

} PlayerParamStompingAttack;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamStompingAttack sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamStompingAttack superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamStompingAttack superSonic2;

} PlayerParamStompingAttackSet;

typedef struct
{
	/// <summary>
	/// ヒット判定
	/// </summary>
	PlayerParamAttackCollider hit;

	/// <summary>
	/// 空振り無効時間
	/// </summary>
	float ignoreSwingingTime;

} PlayerParamComboFinish;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamComboFinish sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamComboFinish superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamComboFinish superSonic2;

} PlayerParamComboFinishSet;

typedef struct
{
	/// <summary>
	/// 初撃前の待ち時間
	/// </summary>
	float waitTime;

	/// <summary>
	/// 撃ち出し間隔
	/// </summary>
	float spanTime;

	/// <summary>
	/// 落下速度
	/// </summary>
	float fallSpeed;

	/// <summary>
	/// オートコンボ時の持続時間
	/// </summary>
	float autoContinueTime;

	/// <summary>
	/// 弾の移動速度
	/// </summary>
	float speed;

	/// <summary>
	/// 弾の最大移動速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 弾の加速度
	/// </summary>
	float accele;

	/// <summary>
	/// スロー比率
	/// </summary>
	float slowRatio;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

} PlayerParamSonicBoom;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamSonicBoom sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamSonicBoom superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamSonicBoom superSonic2;

} PlayerParamSonicBoomSet;

typedef struct
{
	/// <summary>
	/// 撃ち出し間隔
	/// </summary>
	float spanTime;

	/// <summary>
	/// 攻撃時間
	/// </summary>
	float attackTime;

	/// <summary>
	/// 移動角度
	/// </summary>
	float moveAngle;

	/// <summary>
	/// 回転静止時間
	/// </summary>
	float stopTime;

	/// <summary>
	/// スロー比率
	/// </summary>
	float slowRatio;

	/// <summary>
	/// スピン演出の周期ずれ
	/// </summary>
	float spinPhase;

	/// <summary>
	/// スピン演出の半径
	/// </summary>
	float spinRadius;

	/// <summary>
	/// スピン演出の速度
	/// </summary>
	float spinSpeed;

	/// <summary>
	/// 出現遅延時間
	/// </summary>
	float spawnDelayTime[2];

	/// <summary>
	/// 出現位置ローカルオフセット
	/// </summary>
	Vector3 spawnLocalTranslation[2];

	/// <summary>
	/// 出現回転ローカルオフセット
	/// </summary>
	Vector3 spawnLocalAngle[2];

	/// <summary>
	/// 弾の移動速度
	/// </summary>
	float speed;

	/// <summary>
	/// 弾の最大移動速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 弾の加速度
	/// </summary>
	float accele;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

	/// <summary>
	/// 発射時カメラ振動
	/// </summary>
	cstring launchCameraShakeName;

} PlayerParamCrossSlash;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamCrossSlash sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamCrossSlash superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamCrossSlash superSonic2;

} PlayerParamCrossSlashSet;

typedef struct
{
	/// <summary>
	/// 弾出現演出時間
	/// </summary>
	float appearTime;

	/// <summary>
	/// 弾出現演出位相時間
	/// </summary>
	float appearPhaseTime;

	/// <summary>
	/// 弾回転演出半径
	/// </summary>
	float spinRadius;

	/// <summary>
	/// 弾回転演出速度
	/// </summary>
	float spinSpeed;

	/// <summary>
	/// 弾回転演出速度/発射開始後
	/// </summary>
	float spinSpeedPostLaunch;

	/// <summary>
	/// 溜め時間
	/// </summary>
	float chargeTime;

	/// <summary>
	/// 弾生成遅延時間
	/// </summary>
	float spawnTime;

	/// <summary>
	/// 発射前待機時間
	/// </summary>
	float launchPreWaitTime;

	/// <summary>
	/// 撃ち出し間隔
	/// </summary>
	float spanTime;

	/// <summary>
	/// 射出順のランダム化
	/// </summary>
	bool launchRandomize;

	/// <summary>
	/// 射出後待機時間
	/// </summary>
	float launchWaitTime;

	/// <summary>
	/// 射出方向の傾き
	/// </summary>
	float beginAngleX;

	/// <summary>
	/// 始端の強度
	/// </summary>
	float tangent0;

	/// <summary>
	/// 終端の強度
	/// </summary>
	float tangent1;

	/// <summary>
	/// 螺旋回転開始待機時間
	/// </summary>
	float spiralWaitTime;

	/// <summary>
	/// 螺旋回転速度/初速度
	/// </summary>
	float spiralAngularSpeed;

	/// <summary>
	/// 螺旋回転速度/最大速度
	/// </summary>
	float spiralAngularSpeedMax;

	/// <summary>
	/// 螺旋回転速度/加速度
	/// </summary>
	float spiralAngularSpeedAccele;

	/// <summary>
	/// ショット数
	/// </summary>
	uint8_t numShots;

	/// <summary>
	/// 弾の移動速度
	/// </summary>
	float speed;

	/// <summary>
	/// 弾の最大移動速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 弾の加速度
	/// </summary>
	float accele;

	/// <summary>
	/// ホワイトアウト開始時間
	/// </summary>
	float whiteoutBeginTime;

	/// <summary>
	/// ホワイトアウト開始フェード時間
	/// </summary>
	float whiteoutFadeOutTime;

	/// <summary>
	/// ホワイトアウトフェード維持時間
	/// </summary>
	float whiteoutFadingTime;

	/// <summary>
	/// ホワイトアウト終了フェード時間
	/// </summary>
	float whiteoutFadeInTime;

	/// <summary>
	/// コンボ中ワープ距離
	/// </summary>
	Vector3 offset;

	/// <summary>
	/// カメラ名
	/// </summary>
	cstring cameraName;

} PlayerParamHomingShot;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamHomingShot sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamHomingShot superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamHomingShot superSonic2;

} PlayerParamHomingShotSet;

typedef struct
{
	/// <summary>
	/// ヒット判定1
	/// </summary>
	PlayerParamAttackCollider hit1;

	/// <summary>
	/// ヒット判定2
	/// </summary>
	PlayerParamAttackCollider hit2;

	/// <summary>
	/// スパソニ分身の位置オフセット
	/// </summary>
	Vector3 offsets[16];

} PlayerParamSmash;

typedef struct
{
	/// <summary>
	/// sonic
	/// </summary>
	PlayerParamSmash sonic;

	/// <summary>
	/// superSonic1
	/// </summary>
	PlayerParamSmash superSonic1;

	/// <summary>
	/// superSonic2
	/// </summary>
	PlayerParamSmash superSonic2;

} PlayerParamSmashSet;

typedef struct
{
	/// <summary>
	/// 移動時間
	/// </summary>
	float moveTime;

	/// <summary>
	/// 移動時間/スパソニ
	/// </summary>
	float moveTimeSS;

	/// <summary>
	/// 回り込みの大きさスケール/スパソニ
	/// </summary>
	float tangentScale;

	/// <summary>
	/// 待機時間
	/// </summary>
	float waitTime;

	/// <summary>
	/// カメラ旋回比率
	/// </summary>
	float cameraTurnRatio;

} PlayerParamBehind;

typedef struct
{
	/// <summary>
	/// 長押し判定時間
	/// </summary>
	float longPressTime;

} PlayerParamComboCommon;

enum ComboMoveType : uint8_t
{
	Homing = 0,
	Step = 1,
	None = 2,
};

typedef struct
{
	/// <summary>
	/// タイプ
	/// </summary>
	ComboMoveType moveType;

	/// <summary>
	/// 初速度
	/// </summary>
	float moveInitialSpeed;

	/// <summary>
	/// 最高速度
	/// </summary>
	float moveMaxSpeed;

	/// <summary>
	/// 加速度
	/// </summary>
	float moveAccele;

	/// <summary>
	/// タイムアウト
	/// </summary>
	float timeout;

} PlayerParamComboMove;

typedef struct
{
	/// <summary>
	/// 移動速度
	/// </summary>
	float moveSpeed;

	/// <summary>
	/// 移動回転速度
	/// </summary>
	float rotateSpeed;

} PlayerParamComboMoveCorrection;

enum Action : int8_t
{
	Root = 0,
	HomingAttack = 1,
	AerialHomingAttack = 2,
	Pursuit = 3,
	Stomping = 4,
	LoopKick = 5,
	Crasher = 6,
	SpinSlash = 7,
	SonicBoom = 8,
	CrossSlash = 9,
	HomingShot = 10,
	ChargeAttack = 11,
	QuickCyloop = 12,
	AerialQuickCyloop = 13,
	AcceleCombo1 = 14,
	AcceleCombo2 = 15,
	AcceleCombo3 = 16,
	AcceleCombo4 = 17,
	AerialAcceleCombo1 = 18,
	AerialAcceleCombo2 = 19,
	AerialAcceleCombo3 = 20,
	AerialAcceleCombo4 = 21,
	ComboFinish = 22,
	SpinJump = 23,
	Smash = 24,
	Behind = 25,
	Guarded = 26,
	Avoid = 27,
	AirBoost = 28,
	AfterAirBoost = 29,
	KnucklesPunch1 = 30,
	KnucklesPunch2 = 31,
	KnucklesUppercut = 32,
	KnucklesCyKnuckle = 33,
	KnucklesHeatKnuckle = 34,
	AmyTarotAttack = 35,
	AmyTarotRolling = 36,
	AmyCyHammer = 37,
	ActionNum = 38,
};

typedef struct
{
	/// <summary>
	/// 遷移先/通常
	/// </summary>
	Action transitExistTarget[6];

	/// <summary>
	/// 遷移先/空中
	/// </summary>
	Action transitInAir[6];

	/// <summary>
	/// 遷移先/空打ち
	/// </summary>
	Action transitNotExistTarget[6];

} PlayerParamComboTransit;

typedef struct
{
	/// <summary>
	/// Root
	/// </summary>
	PlayerParamComboTransit root;

	/// <summary>
	/// Homing Attack
	/// </summary>
	PlayerParamComboTransit homingAttack;

	/// <summary>
	/// Aerial Homing Attack
	/// </summary>
	PlayerParamComboTransit aerialHoming;

	/// <summary>
	/// Pursuit Kick
	/// </summary>
	PlayerParamComboTransit pursuit;

	/// <summary>
	/// Stomping
	/// </summary>
	PlayerParamComboTransit stomping;

	/// <summary>
	/// Loop Kick
	/// </summary>
	PlayerParamComboTransit loopKick;

	/// <summary>
	/// Crasher
	/// </summary>
	PlayerParamComboTransit crasher;

	/// <summary>
	/// Spin Slash
	/// </summary>
	PlayerParamComboTransit spinSlash;

	/// <summary>
	/// Sonic Boom
	/// </summary>
	PlayerParamComboTransit sonicBoom;

	/// <summary>
	/// Cross Slash
	/// </summary>
	PlayerParamComboTransit crossSlash;

	/// <summary>
	/// Homing Shot
	/// </summary>
	PlayerParamComboTransit homingShot;

	/// <summary>
	/// Charge Attack
	/// </summary>
	PlayerParamComboTransit chargeAttack;

	/// <summary>
	/// Quick Cyloop
	/// </summary>
	PlayerParamComboTransit quickCyloop;

	/// <summary>
	/// Quick Cyloop Aerial
	/// </summary>
	PlayerParamComboTransit aerialQuickCyloop;

	/// <summary>
	/// Accele Combo 1
	/// </summary>
	PlayerParamComboTransit acceleCombo1;

	/// <summary>
	/// Accele Combo 2
	/// </summary>
	PlayerParamComboTransit acceleCombo2;

	/// <summary>
	/// Accele Combo 3
	/// </summary>
	PlayerParamComboTransit acceleCombo3;

	/// <summary>
	/// Accele Combo 4
	/// </summary>
	PlayerParamComboTransit acceleCombo4;

	/// <summary>
	/// Aerial Accele Combo 1
	/// </summary>
	PlayerParamComboTransit aerialAcceleCombo1;

	/// <summary>
	/// Aerial Accele Combo 2
	/// </summary>
	PlayerParamComboTransit aerialAcceleCombo2;

	/// <summary>
	/// Aerial Accele Combo 3
	/// </summary>
	PlayerParamComboTransit aerialAcceleCombo3;

	/// <summary>
	/// Aerial Accele Combo 4
	/// </summary>
	PlayerParamComboTransit aerialAcceleCombo4;

	/// <summary>
	/// Behind
	/// </summary>
	PlayerParamComboTransit behind;

	/// <summary>
	/// Guarded
	/// </summary>
	PlayerParamComboTransit guarded;

	/// <summary>
	/// Avoid
	/// </summary>
	PlayerParamComboTransit avoid;

	/// <summary>
	/// AirBoost
	/// </summary>
	PlayerParamComboTransit airBoost;

	/// <summary>
	/// AfterAirBoost
	/// </summary>
	PlayerParamComboTransit afterAirBoost;

	/// <summary>
	/// Knuckles Punch1
	/// </summary>
	PlayerParamComboTransit knucklesPunch1;

	/// <summary>
	/// Knuckles Punch2
	/// </summary>
	PlayerParamComboTransit knucklesPunch2;

	/// <summary>
	/// Knuckles Uppercut
	/// </summary>
	PlayerParamComboTransit knucklesUppercut;

	/// <summary>
	/// Knuckles CyKnuckle
	/// </summary>
	PlayerParamComboTransit knucklesCyKnuckle;

	/// <summary>
	/// Knuckles MaximumHeatKnuckle
	/// </summary>
	PlayerParamComboTransit knucklesHeatKnuckle;

	/// <summary>
	/// Amy TarotAttack
	/// </summary>
	PlayerParamComboTransit amyTarotAttack;

	/// <summary>
	/// Amy TarotRolling
	/// </summary>
	PlayerParamComboTransit amyTarotRolling;

	/// <summary>
	/// Amy CyHammer
	/// </summary>
	PlayerParamComboTransit amyCyHammer;

} PlayerParamComboTransitTable;

typedef struct
{
	/// <summary>
	/// コンボ基本
	/// </summary>
	PlayerParamComboCommon common;

	/// <summary>
	/// コンボ間移動/ソニック
	/// </summary>
	PlayerParamComboMove comboMoveSonic;

	/// <summary>
	/// コンボ間移動/スーパーソニック
	/// </summary>
	PlayerParamComboMove comboMoveSupersonic;

	/// <summary>
	/// コンボ移動補正 スーパーソニック時
	/// </summary>
	PlayerParamComboMoveCorrection comboMoveCorrection;

	/// <summary>
	/// コンボルート
	/// </summary>
	PlayerParamComboTransitTable comboTable;

} PlayerParamCombo;

typedef struct
{
	/// <summary>
	/// 円周/分割数
	/// </summary>
	int32_t m_divideCircle;

	/// <summary>
	/// 円周/半径
	/// </summary>
	float m_circleRadius;

	/// <summary>
	/// 円周/半径の揺らぎ周期
	/// </summary>
	float m_circleWaveCycle;

	/// <summary>
	/// 円周/半径の揺らぎ振幅
	/// </summary>
	float m_circleWaveWidth;

	/// <summary>
	/// 円周/半径の揺らぎ速度
	/// </summary>
	float m_circleWaveSpeed;

	/// <summary>
	/// 円周/スケール
	/// </summary>
	Vector2 m_scale;

	/// <summary>
	/// テクスチャ/ファイル名
	/// </summary>
	cstring m_textureName;

	/// <summary>
	/// テクスチャ/流れる速度
	/// </summary>
	float m_flowSpeed;

	/// <summary>
	/// テクスチャ/ひねり周期
	/// </summary>
	float m_twistCycle;

	/// <summary>
	/// テクスチャ/回転周期
	/// </summary>
	float m_rollCycle;

	/// <summary>
	/// テクスチャ/回転位相
	/// </summary>
	float m_rollPhase;

	/// <summary>
	/// テクスチャ/先頭アルファ距離
	/// </summary>
	float m_alphaHeadDistance;

	/// <summary>
	/// テクスチャ/末尾アルファ距離
	/// </summary>
	float m_alphaTailDistance;

	/// <summary>
	/// 位置オフセット/回転周期
	/// </summary>
	float m_offsetCycle;

	/// <summary>
	/// 位置オフセット/回転位相
	/// </summary>
	float m_offsetPhase;

	/// <summary>
	/// 位置オフセット/半径
	/// </summary>
	float m_offsetRadius;

} CyloopSlashEffectBaseParameter;

typedef struct {
	float alpha;

	float red;

	float green;

	float blue;

} colorF;

typedef struct
{
	CyloopSlashEffectBaseParameter cyloopSlashEffectBaseParameter;

	/// <summary>
	/// テクスチャ/色1
	/// </summary>
	colorF m_color0;

	/// <summary>
	/// テクスチャ/色2
	/// </summary>
	colorF m_color1;

	/// <summary>
	/// テクスチャ/輝度
	/// </summary>
	float m_luminance;

	/// <summary>
	/// テクスチャ/フラッシュ色1
	/// </summary>
	colorF m_flashColor0;

	/// <summary>
	/// テクスチャ/フラッシュ色1
	/// </summary>
	colorF m_flashColor1;

	/// <summary>
	/// テクスチャ/フラッシュ輝度
	/// </summary>
	float m_flashLuminance;

	/// <summary>
	/// テクスチャ/フラッシュ時間
	/// </summary>
	float m_flashTime;

} CyloopTransparentLocusParameter;

typedef struct
{
	/// <summary>
	/// スケール
	/// </summary>
	float scale;

	/// <summary>
	/// 速度X
	/// </summary>
	float speedX;

	/// <summary>
	/// 速度Y
	/// </summary>
	float speedY;

} OpaqueLineUvCell;

typedef struct
{
	CyloopSlashEffectBaseParameter cyloopSlashEffectBaseParameter;

	/// <summary>
	/// テクスチャ/色
	/// </summary>
	colorF m_color;

	/// <summary>
	/// テクスチャ/アルファしきい値
	/// </summary>
	float m_alphaThreshold;

	/// <summary>
	/// テクスチャ/ノイズ
	/// </summary>
	OpaqueLineUvCell m_uvCells[2];

	/// <summary>
	/// テクスチャ/ラインスケールX
	/// </summary>
	float m_uvLineScaleX;

	/// <summary>
	/// テクスチャ/ラインスケールY
	/// </summary>
	float m_uvLineScaleY;

	/// <summary>
	/// テクスチャ/フラッシュ色
	/// </summary>
	colorF m_flashColor;

	/// <summary>
	/// テクスチャ/フラッシュ時間
	/// </summary>
	float m_flashTime;

} CyloopOpaqueLocusParameter;

typedef struct
{
	/// <summary>
	/// テクスチャ/パターン
	/// </summary>
	cstring m_textureNamePattern;

	/// <summary>
	/// テクスチャ/歪み
	/// </summary>
	cstring m_textureNameDist;

	/// <summary>
	/// 開始色
	/// </summary>
	colorF startColor;

	/// <summary>
	/// 末端色
	/// </summary>
	colorF endColor;

	/// <summary>
	/// 開始色輝度
	/// </summary>
	float startColorLuminance;

	/// <summary>
	/// 末端色輝度
	/// </summary>
	float endColorLuminance;

	/// <summary>
	/// フラッシュ/開始色
	/// </summary>
	colorF startColorFlash;

	/// <summary>
	/// フラッシュ/末端色
	/// </summary>
	colorF endColorFlash;

	/// <summary>
	/// フラッシュ/開始色輝度
	/// </summary>
	float startColorLuminanceFlash;

	/// <summary>
	/// フラッシュ/末端色輝度
	/// </summary>
	float endColorLuminanceFlash;

	/// <summary>
	/// フラッシュ/時間
	/// </summary>
	float flashTime;

	/// <summary>
	/// パターン/視差
	/// </summary>
	float patternDepth;

	/// <summary>
	/// パターン/スクロール速度
	/// </summary>
	float patternScrollSpeed;

	/// <summary>
	/// パターン/濃さ
	/// </summary>
	float patternDarkness;

	/// <summary>
	/// パターン/タイリング
	/// </summary>
	float patternScale;

	/// <summary>
	/// グリッチ/末端の解像度X
	/// </summary>
	float glitchResX;

	/// <summary>
	/// グリッチ/末端の解像度Y
	/// </summary>
	float glitchResY;

	/// <summary>
	/// グリッチ/末端の各段のズレ量
	/// </summary>
	float glitchOffset;

	/// <summary>
	/// グリッチ/幅が変化する最大の長さ
	/// </summary>
	float glitchMaxLength;

	/// <summary>
	/// グリッチ/先端のスクロール速度
	/// </summary>
	float startGlitchScrollSpeed;

	/// <summary>
	/// グリッチ/先端のノイズ変化速度
	/// </summary>
	float startGlitchChangeSpeed;

	/// <summary>
	/// グリッチ/先端の位置オフセット
	/// </summary>
	float startGlitchShift;

	/// <summary>
	/// グリッチ/先端のコントラスト
	/// </summary>
	float startGlitchContrust;

	/// <summary>
	/// グリッチ/末端のスクロール速度
	/// </summary>
	float endGlitchScrollSpeed;

	/// <summary>
	/// グリッチ/末端のノイズ変化速度
	/// </summary>
	float endGlitchChangeSpeed;

	/// <summary>
	/// グリッチ/末端の位置オフセット
	/// </summary>
	float endGlitchShift;

	/// <summary>
	/// グリッチ/末端のコントラスト
	/// </summary>
	float endGlitchContrust;

	/// <summary>
	/// ライン/幅_モデルの幅
	/// </summary>
	float lineWidth;

	/// <summary>
	/// ライン/幅_表示の幅
	/// </summary>
	float lineDisplayWidth;

	/// <summary>
	/// ライン/境界の幅
	/// </summary>
	float lineBlackEdgeWidth;

	/// <summary>
	/// ライン/境界の色の濃さ
	/// </summary>
	float lineBlackEdgeIntensity;

	/// <summary>
	/// ライン/境界の法線フェード
	/// </summary>
	float lineBlackEdgeNormalFade;

	/// <summary>
	/// 歪み/全体のUVスケール
	/// </summary>
	float distNoiseScale;

	/// <summary>
	/// 歪み/周期低のUVスケール
	/// </summary>
	float distLowNoiseScale;

	/// <summary>
	/// 歪み/周期高のUVスケール
	/// </summary>
	float distHighNoiseScale;

	/// <summary>
	/// 歪み/周波数のブレンド割合
	/// </summary>
	float distNoiseRate;

	/// <summary>
	/// 歪み/スクロール速度
	/// </summary>
	float distScrollSpeed;

	/// <summary>
	/// 歪み/強さ
	/// </summary>
	float distIntensity;

	/// <summary>
	/// 消失/消失比率
	/// </summary>
	float dissolve;

	/// <summary>
	/// 消失/フェードアウト時間比率
	/// </summary>
	float dissolveRate;

	/// <summary>
	/// 位置/高さオフセット
	/// </summary>
	float heightOffset;

} CyloopCrossLineParameter;

typedef struct
{
	/// <summary>
	/// 透明ラインの本数
	/// </summary>
	int32_t m_numTransparentLines;

	/// <summary>
	/// 透明ラインのパラメータ
	/// </summary>
	CyloopTransparentLocusParameter m_transparentLines[3];

	/// <summary>
	/// 不透明ラインの本数
	/// </summary>
	int32_t m_numOpaqueLines;

	/// <summary>
	/// 不透明ラインのパラメータ
	/// </summary>
	CyloopOpaqueLocusParameter m_opaqueLines[3];

	/// <summary>
	/// クロスラインの本数
	/// </summary>
	int32_t m_numCrossLines;

	/// <summary>
	/// クロスラインのパラメータ
	/// </summary>
	CyloopCrossLineParameter m_crossline;

} CyloopLocusParameter;

typedef struct
{
	/// <summary>
	/// ドロップなしのウェイト値
	/// </summary>
	uint32_t noneWeight;

	/// <summary>
	/// 10リングのウェイト値
	/// </summary>
	uint32_t ring10Weight;

	/// <summary>
	/// 力の種のウェイト値
	/// </summary>
	uint32_t powerSeedWeight;

	/// <summary>
	/// 守りの種のウェイト値
	/// </summary>
	uint32_t guardSeedWeight;

	/// <summary>
	/// シーケンスアイテムのウェイト値
	/// </summary>
	uint32_t sequenceItemWeight;

	/// <summary>
	/// ポータルの欠片のウェイト値
	/// </summary>
	uint32_t portalBitWeight;

	/// <summary>
	/// スキルピースのウェイト値
	/// </summary>
	uint32_t skillPieceWeight;

} CyloopDropItemWeightParameter;

typedef struct
{
	/// <summary>
	/// 通常時のウェイト
	/// </summary>
	CyloopDropItemWeightParameter weight;

	/// <summary>
	/// バトル中のウェイト
	/// </summary>
	CyloopDropItemWeightParameter weight2;

	/// <summary>
	/// リングドロップ枚数/単体
	/// </summary>
	uint32_t numRings;

	/// <summary>
	/// リングドロップ枚数/複合
	/// </summary>
	uint32_t numRings2;

	/// <summary>
	/// 10リングドロップ枚数
	/// </summary>
	uint32_t num10Rings;

	/// <summary>
	/// スキルピースドロップ数
	/// </summary>
	uint32_t numSkillPieces;

	/// <summary>
	/// スキルピース1つあたりの経験値量
	/// </summary>
	uint32_t skillPieceExp;

	/// <summary>
	/// レアドロップクールタイム[sec]
	/// </summary>
	float rareDropCoolTime;

} CyloopDropItemParameter;

typedef struct
{
	/// <summary>
	/// ダメージ値倍率
	/// </summary>
	float damageRate;

	/// <summary>
	/// スタン値倍率
	/// </summary>
	float stunRate;

	/// <summary>
	/// 怯み値倍率
	/// </summary>
	float staggerRate;

	/// <summary>
	/// ダメージ速度倍率
	/// </summary>
	float velocityRate;

} CyloopShapeWindCountParameter;

typedef struct
{
	/// <summary>
	/// 多重数別パラメータ
	/// </summary>
	CyloopShapeWindCountParameter param[5];

} CyloopShapeWindEffectParaemter;

typedef struct
{
	/// <summary>
	/// 多重
	/// </summary>
	CyloopShapeWindEffectParaemter wind;

} CyloopShapeEffectParameter;

typedef struct
{
	/// <summary>
	/// 軌跡
	/// </summary>
	CyloopLocusParameter locus;

	/// <summary>
	/// 軌跡/Quick
	/// </summary>
	CyloopLocusParameter locusQuick;

	/// <summary>
	/// 軌跡/スパソニ
	/// </summary>
	CyloopLocusParameter locusSuperSonic;

	/// <summary>
	/// 軌跡/スパソニ/Quick
	/// </summary>
	CyloopLocusParameter locusSuperSonicQuick;

	/// <summary>
	/// オーラカラー
	/// </summary>
	colorF auraColor;

	/// <summary>
	/// ドロップアイテム
	/// </summary>
	CyloopDropItemParameter dropItem;

	/// <summary>
	/// Cyloopを行える最低速度
	/// </summary>
	float needSpeed;

	/// <summary>
	/// 形状効果
	/// </summary>
	CyloopShapeEffectParameter shapeEffect;

	/// <summary>
	/// QuickCyloopのゲージ消費量
	/// </summary>
	float lossQuickCyloopEnergy;

	/// <summary>
	/// QuickCyloopのゲージの時間単位回復量
	/// </summary>
	float recoveryQuickCyloopEnergyByTime;

	/// <summary>
	/// ミニゲーム中のQuickCyloopのゲージの時間単位回復量
	/// </summary>
	float recoveryQuickCyloopEnergyByTimeInMinigame;

} PlayerParamCyloop;

enum Part : int8_t
{
	PunchR = 0,
	PunchL = 1,
	KickR = 2,
	KickL = 3,
};

typedef struct
{
	/// <summary>
	/// 設定名
	/// </summary>
	cstring name;

	/// <summary>
	/// モデル
	/// </summary>
	Part part;

	/// <summary>
	/// 開始位置
	/// </summary>
	Vector3 begin;

	/// <summary>
	/// 終了位置
	/// </summary>
	Vector3 end;

	/// <summary>
	/// スケール
	/// </summary>
	float scale;

	/// <summary>
	/// ロール回転
	/// </summary>
	float roll;

	/// <summary>
	/// 移動時間
	/// </summary>
	float moveTime;

	/// <summary>
	/// フェードアウト時間
	/// </summary>
	float fadeoutTime;

} PlayerParamSuperSonicShapeAttackData;

typedef struct
{
	/// <summary>
	/// 変身に必要なリング数
	/// </summary>
	int32_t numRings;

	/// <summary>
	/// リング1枚消費する時間[sec]
	/// </summary>
	float decreaseSec;

	/// <summary>
	/// リングの吸収範囲半径
	/// </summary>
	float inletRadius;

	/// <summary>
	/// 移動SEを鳴らし始める速度
	/// </summary>
	float moveSoundSpeed;

	/// <summary>
	/// 残像エフェクト設定
	/// </summary>
	PlayerParamSuperSonicShapeAttackData shapeEffects[32];

} PlayerParamSuperSonic;

typedef struct
{
	/// <summary>
	/// 吹き飛ばされ時の減速度
	/// </summary>
	float blowDeceleForce;

	/// <summary>
	/// 吹き飛ばされ着地後の減速度
	/// </summary>
	float blowDeceleForceOnGround;

	/// <summary>
	/// 吹き飛ばされ時の重力スケール
	/// </summary>
	float blowGravityScale;

	/// <summary>
	/// 吹き飛ばされをキャンセル可能になる時間
	/// </summary>
	float blowTransitTime;

	/// <summary>
	/// 吹き飛ばされダウン時間
	/// </summary>
	float blowDownTime;

	/// <summary>
	/// パイロン衝突時の上方向の跳ね上げの大きさ
	/// </summary>
	float pylonBlowUpSize;

	/// <summary>
	/// パイロン衝突時の吹き飛び速度
	/// </summary>
	float pylonBlowSpeed;

	/// <summary>
	/// パイロン衝突時のヒットストップ名
	/// </summary>
	cstring pylonHitStop;

} PlayerParamSandSki;

enum CameraShakeTiming : int8_t
{
	StartCameraInterpolation = 0,
	EndCameraInterpolation = 1,
};

typedef struct
{
	/// <summary>
	/// 移動中のタイムスケール
	/// </summary>
	float timeScaleInMove;

	/// <summary>
	/// ヒット演出を再生するヒットまでの残り時間
	/// </summary>
	float hitStartRestTime;

	/// <summary>
	/// ヒットカメラオフセット
	/// </summary>
	Vector3 hitCameraOffset;

	/// <summary>
	/// ヒットカメラIn補間時間
	/// </summary>
	float hitCameraTimeEaseIn;

	/// <summary>
	/// ヒットカメラFovy角度
	/// </summary>
	float hitCameraFovyAngle;

	/// <summary>
	/// ヒットタイムスケール値
	/// </summary>
	float hitTimeScaleValue;

	/// <summary>
	/// ヒットタイムスケールIn補間時間
	/// </summary>
	float hitTimeScaleTimeEaseIn;

	/// <summary>
	/// カメラ解除遷移時間
	/// </summary>
	float resetCameraEaseOutTime;

	/// <summary>
	/// タイムスケール解除遷移時間
	/// </summary>
	float resetTimeScaleEaseOutTime;

	/// <summary>
	/// ヒットストップを維持する時間
	/// </summary>
	float timeScaleKeepTime;

	/// <summary>
	/// 発射エフェクトのオフセット
	/// </summary>
	float shotEffOffset;

	/// <summary>
	/// ヒットエフェクトのオフセット
	/// </summary>
	float hitEffOffset;

	/// <summary>
	/// カメラシェイク再生タイミング
	/// </summary>
	CameraShakeTiming cameraShakeTiming;

	/// <summary>
	/// カメラシェイク名
	/// </summary>
	cstring cameraShakeName;

} PlayerParamSlingshot;

typedef struct
{
	/// <summary>
	/// 蛇行周期
	/// </summary>
	float meanderCycle;

	/// <summary>
	/// 蛇行角度
	/// </summary>
	float meanderAngle;

	/// <summary>
	/// 最大速度
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 最小速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 逃げ回る時間
	/// </summary>
	float time;

} PlayerParamRunawayBee;

typedef struct
{
	/// <summary>
	/// コダマ数
	/// </summary>
	int32_t numKodamas;

	/// <summary>
	/// 移動初速
	/// </summary>
	float initialSpeed;

	/// <summary>
	/// 移動最小速度
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 移動最大速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// ジャンプ力
	/// </summary>
	float jumpForce;

} PlayerParamRunWithKodamaParam;

typedef struct
{
	/// <summary>
	/// コダマ最大数
	/// </summary>
	int32_t maxKodamas;

	/// <summary>
	/// 重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// コダマ数ごとのパラメータ
	/// </summary>
	PlayerParamRunWithKodamaParam params[8];

} PlayerParamRunWithKodama;

typedef struct
{
	CommonPackage commonPackage;

	/// <summary>
	/// アクセルモード
	/// </summary>
	PlayerParamAcceleMode acceleMode;

	/// <summary>
	/// 攻撃Act / Accele Combo
	/// </summary>
	PlayerParamAcceleComboSet acceleComboSet;

	/// <summary>
	/// 攻撃Act / Loop Kick
	/// </summary>
	PlayerParamLoopKickSet loopKickSet;

	/// <summary>
	/// 攻撃Act / Crasher
	/// </summary>
	PlayerParamCrasherSet crasherSet;

	/// <summary>
	/// 攻撃Act / Spin Slash
	/// </summary>
	PlayerParamSpinSlashSet spinSlashSet;

	/// <summary>
	/// 攻撃Act / Charge Attack
	/// </summary>
	PlayerParamChargeAttackSet chargeAtackSet;

	/// <summary>
	/// 攻撃Act / Stomping
	/// </summary>
	PlayerParamStompingAttackSet stompingAttackSet;

	/// <summary>
	/// 攻撃Act / Combo Finish
	/// </summary>
	PlayerParamComboFinishSet comboFinishSet;

	/// <summary>
	/// 攻撃Act / Sonic Boom
	/// </summary>
	PlayerParamSonicBoomSet sonicboomSet;

	/// <summary>
	/// 攻撃Act / Cross Slash
	/// </summary>
	PlayerParamCrossSlashSet crossSlashSet;

	/// <summary>
	/// 攻撃Act / Homing Shot
	/// </summary>
	PlayerParamHomingShotSet homingShotSet;

	/// <summary>
	/// 攻撃Act / Smash
	/// </summary>
	PlayerParamSmashSet smashSet;

	/// <summary>
	/// 防御Act / Behind
	/// </summary>
	PlayerParamBehind behind;

	/// <summary>
	/// コンボ
	/// </summary>
	PlayerParamCombo combo;

	/// <summary>
	/// Cyloop
	/// </summary>
	PlayerParamCyloop cyloop;

	/// <summary>
	/// スーパーソニック
	/// </summary>
	PlayerParamSuperSonic supersonic;

	/// <summary>
	/// サンドスキー
	/// </summary>
	PlayerParamSandSki sandski;

	/// <summary>
	/// スリングショット
	/// </summary>
	PlayerParamSlingshot slingshot;

	/// <summary>
	/// 蜂逃げ回り
	/// </summary>
	PlayerParamRunawayBee runawayBee;

	/// <summary>
	/// コダマ担ぎ歩き
	/// </summary>
	PlayerParamRunWithKodama runWithKodama;

} CommonPackageSonic;

enum SupportedPlane : int8_t
{
	Flat = 0,
	Slope = 1,
	Wall = 2,
};

typedef struct
{
	/// <summary>
	/// 移動可能な傾斜変化量[deg]
	/// </summary>
	float movableMaxSlope;

	/// <summary>
	/// 地面探索傾斜[deg]
	/// </summary>
	float activeLandingSlope;

	/// <summary>
	/// 地面探索傾斜/ブースト中[deg]
	/// </summary>
	float activeLandingSlopeInBoost;

	/// <summary>
	/// 平面の最大傾斜[deg]
	/// </summary>
	float landingMaxSlope;

	/// <summary>
	/// 斜面の最大傾斜[deg]
	/// </summary>
	float slidingMaxSlope;

	/// <summary>
	/// 壁面の最大傾斜[deg]
	/// </summary>
	float wallAngleMaxSlope;

	/// <summary>
	/// 直立可能なサポート面
	/// </summary>
	SupportedPlane onStand;

	/// <summary>
	/// 空中から走行可能なサポート面
	/// </summary>
	SupportedPlane onRunInAir;

	/// <summary>
	/// 走行可能なサポート面
	/// </summary>
	SupportedPlane onRun;

	/// <summary>
	/// 地面に張り付いて移動するか
	/// </summary>
	bool moveHolding;

	/// <summary>
	/// ブースト中の壁衝突で減速するか
	/// </summary>
	bool wallSlideSlowInBoost;

	/// <summary>
	/// 壁面属性に接地可能か
	/// </summary>
	bool attrWallOnGround;

	/// <summary>
	/// 先行入力時間
	/// </summary>
	float priorityInputTime;

	/// <summary>
	/// リング所持数
	/// </summary>
	int32_t capacityRings;

	/// <summary>
	/// リング所持数/LvMax
	/// </summary>
	int32_t capacityRingsLvMax;

	/// <summary>
	/// リング回収範囲
	/// </summary>
	float collectRingRange;

} PlayerParamCommon;

typedef struct
{
	/// <summary>
	/// 初速
	/// </summary>
	float initial;

	/// <summary>
	/// 最低速度
	/// </summary>
	float min;

	/// <summary>
	/// 最高速度
	/// </summary>
	float max;

	/// <summary>
	/// 旋回中速度
	/// </summary>
	float minTurn;

} PlayerParamSpeedData;

typedef struct
{
	/// <summary>
	/// 最大力
	/// </summary>
	float force;

	/// <summary>
	/// 最大力[最大]
	/// </summary>
	float force2;

	/// <summary>
	/// 速度ダンパー範囲
	/// </summary>
	float damperRange;

	/// <summary>
	/// 最低躍度
	/// </summary>
	float jerkMin;

	/// <summary>
	/// 最高躍度
	/// </summary>
	float jerkMax;

} PlayerParamSpeedAcceleData;

typedef struct
{
	/// <summary>
	/// 最大力
	/// </summary>
	float force;

	/// <summary>
	/// 速度ダンパー範囲
	/// </summary>
	float damperRange;

	/// <summary>
	/// 最低躍度
	/// </summary>
	float jerkMin;

	/// <summary>
	/// 最高躍度
	/// </summary>
	float jerkMax;

} PlayerParamSpeedAcceleData2;

typedef struct
{
	/// <summary>
	/// 通常
	/// </summary>
	PlayerParamSpeedData normal;

	/// <summary>
	/// 通常[最大]
	/// </summary>
	PlayerParamSpeedData normal2;

	/// <summary>
	/// ブースト
	/// </summary>
	PlayerParamSpeedData boost;

	/// <summary>
	/// ブースト[最大]
	/// </summary>
	PlayerParamSpeedData boost2;

	/// <summary>
	/// ブーストLvMax
	/// </summary>
	PlayerParamSpeedData boostLvMax;

	/// <summary>
	/// ブーストLvMax[最大]
	/// </summary>
	PlayerParamSpeedData boostLvMax2;

	/// <summary>
	/// オーバースピード最高速度
	/// </summary>
	float maxSpeedOver;

	/// <summary>
	/// 最大速度リミット[最小]
	/// </summary>
	float opitonMaxSpeedLimitMin;

	/// <summary>
	/// 最大速度リミット[最大]
	/// </summary>
	float opitonMaxSpeedLimitMax;

	/// <summary>
	/// 停止判定速度
	/// </summary>
	float thresholdStopSpeed;

	/// <summary>
	/// 最高落下速度
	/// </summary>
	float maxFallSpeed;

	/// <summary>
	/// 加速度
	/// </summary>
	PlayerParamSpeedAcceleData accele;

	/// <summary>
	/// 減速度
	/// </summary>
	PlayerParamSpeedAcceleData decele;

	/// <summary>
	/// ニュートラル時最小減速度
	/// </summary>
	PlayerParamSpeedAcceleData2 deceleNeutralMin;

	/// <summary>
	/// ニュートラル時最大減速度
	/// </summary>
	PlayerParamSpeedAcceleData2 deceleNeutralMax;

	/// <summary>
	/// 加速度/オートラン
	/// </summary>
	float acceleAuto;

	/// <summary>
	/// 減速度/オートラン
	/// </summary>
	float deceleAuto;

	/// <summary>
	/// 旋回減速/開始角度
	/// </summary>
	float turnDeceleAngleMin;

	/// <summary>
	/// 旋回減速/最大角度
	/// </summary>
	float turnDeceleAngleMax;

	/// <summary>
	/// 斜面加速度
	/// </summary>
	float maxGravityAccele;

	/// <summary>
	/// 斜面減速度
	/// </summary>
	float maxGravityDecele;

	/// <summary>
	/// しゃがみ時の減速度
	/// </summary>
	float deceleSquat;

	/// <summary>
	/// 加速感度
	/// </summary>
	float acceleSensitive;

	/// <summary>
	/// 水中ブースト時のモーションに影響する速度
	/// </summary>
	float boostAnimSpeedInWater;

} PlayerParamSpeed;

typedef struct
{
	/// <summary>
	/// 基本旋回力
	/// </summary>
	float baseRotateForce;

	/// <summary>
	/// 基本旋回力[最大]
	/// </summary>
	float baseRotateForce2;

	/// <summary>
	/// 基本旋回力の基準速度
	/// </summary>
	float baseRotateForceSpeed;

	/// <summary>
	/// 最小旋回力
	/// </summary>
	float minRotateForce;

	/// <summary>
	/// 最大旋回力
	/// </summary>
	float maxRotateForce;

	/// <summary>
	/// 角度比旋回力減衰を常に適用するか
	/// </summary>
	bool angleRotateForceDecayEnabled;

	/// <summary>
	/// 角度比旋回力減衰の正面方向への影響率
	/// </summary>
	float frontRotateRatio;

	/// <summary>
	/// 速度比旋回力減衰の減衰開始速度
	/// </summary>
	float rotationForceDecaySpeed;

	/// <summary>
	/// 速度比旋回力減衰の減衰レート
	/// </summary>
	float rotationForceDecayRate;

	/// <summary>
	/// 速度比旋回力減衰の最大減衰力
	/// </summary>
	float rotationForceDecayMax;

	/// <summary>
	/// オートラン時の旋回力
	/// </summary>
	float autorunRotateForce;

} PlayerParamRotation;

typedef struct
{
	/// <summary>
	/// 歩き速度
	/// </summary>
	float walkSpeed;

	/// <summary>
	/// 忍び歩き速度
	/// </summary>
	float sneakingSpeed;

	/// <summary>
	/// 忍び歩きのアニメーション再生速度
	/// </summary>
	float animSpeedSneak;

	/// <summary>
	/// 歩きのアニメーション再生速度
	/// </summary>
	float animSpeedWalk;

	/// <summary>
	/// 走りのアニメーション再生速度
	/// </summary>
	float animSpeedRun;

	/// <summary>
	/// ブーストのアニメーション再生速度
	/// </summary>
	float animSpeedBoost;

	/// <summary>
	/// 左右傾きの傾きのサンプル時間
	/// </summary>
	float animLRBlendSampleTime;

	/// <summary>
	/// 左右傾きの最小ブレンド角度
	/// </summary>
	float animLRBlendAngleMin;

	/// <summary>
	/// 左右傾きの最大ブレンド角度
	/// </summary>
	float animLRBlendAngleMax;

	/// <summary>
	/// 左右傾きのブレンド速度
	/// </summary>
	float animLRBlendSpeed;

	/// <summary>
	/// 左右傾きが中央に戻る際のブレンド速度
	/// </summary>
	float animLRBlendSpeedToCenter;

	/// <summary>
	/// 最低歩き移行動作時間
	/// </summary>
	float minChangeWalkTime;

	/// <summary>
	/// 落下時に落下アニメーションになる角度
	/// </summary>
	float fallAnimationAngle;

} PlayerParamRunning;

typedef struct
{
	/// <summary>
	/// 前後方向の最小回転速度
	/// </summary>
	float rotateSpeedMinFB;

	/// <summary>
	/// 前後方向の最大回転速度
	/// </summary>
	float rotateSpeedMaxFB;

	/// <summary>
	/// 左右方向の最小回転速度
	/// </summary>
	float rotateSpeedMinLR;

	/// <summary>
	/// 左右方向の最大回転速度
	/// </summary>
	float rotateSpeedMaxLR;

} PlayerParamBalanceData;

typedef struct
{
	/// <summary>
	/// standard
	/// </summary>
	PlayerParamBalanceData standard;

	/// <summary>
	/// loop
	/// </summary>
	PlayerParamBalanceData loop;

} PlayerParamBalance;

typedef struct
{
	/// <summary>
	/// ブレーキ開始時の速度減衰割合
	/// </summary>
	float initialSpeedRatio;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 地上でのブレーキ力
	/// </summary>
	float forceLand;

	/// <summary>
	/// 空中でのブレーキ力
	/// </summary>
	float forceAir;

	/// <summary>
	/// ブレーキを終了する速度
	/// </summary>
	float endSpeed;

	/// <summary>
	/// 停止状態で強制停止するまでの時間
	/// </summary>
	float stopTime;

} PlayerParamBrake;

typedef struct
{
	/// <summary>
	/// クイックターンが可能な速度
	/// </summary>
	float thresholdSpeed;

	/// <summary>
	/// ターン入力と見なす角度
	/// </summary>
	float thresholdAngle;

	/// <summary>
	/// ターン後の走り出し速度
	/// </summary>
	float turnAfterSpeed;

	/// <summary>
	/// ターン中縁から落ちないようにするか
	/// </summary>
	bool stopEdge;

} PlayerParamTurn;

typedef struct
{
	/// <summary>
	/// ボールになるまでの時間
	/// </summary>
	float preActionTime;

	/// <summary>
	/// 最大ジャンプ固定時間[sec]
	/// </summary>
	float longPressTime;

	/// <summary>
	/// 加速時間[sec]
	/// </summary>
	float addForceTime;

	/// <summary>
	/// ジャンプ力
	/// </summary>
	float force;

	/// <summary>
	/// 上昇加速力
	/// </summary>
	float addForce;

	/// <summary>
	/// 最小ジャンプ力
	/// </summary>
	float forceMin;

	/// <summary>
	/// 重力サイズ
	/// </summary>
	float gravitySize;

} PlayerParamJump;

typedef struct
{
	/// <summary>
	/// 水平加速力
	/// </summary>
	float acceleForce;

	/// <summary>
	/// 水平減速力/通常
	/// </summary>
	float deceleForce;

	/// <summary>
	/// 水平減速力/無入力
	/// </summary>
	float deceleNeutralForce;

	/// <summary>
	/// 水平減速力/逆入力
	/// </summary>
	float deceleBackForce;

	/// <summary>
	/// 水平方向の最高速度の最低値
	/// </summary>
	float limitMin;

	/// <summary>
	/// 重力逆方向の初速制限
	/// </summary>
	float limitUpSpeed;

	/// <summary>
	/// 旋回力[deg/sec]
	/// </summary>
	float rotationForce;

	/// <summary>
	/// 速度比旋回力減衰の減衰開始速度
	/// </summary>
	float rotationForceDecaySpeed;

	/// <summary>
	/// 速度比旋回力減衰の減衰レート
	/// </summary>
	float rotationForceDecayRate;

	/// <summary>
	/// 速度比旋回力減衰の最大減衰力
	/// </summary>
	float rotationForceDecayMax;

	/// <summary>
	/// 空気抵抗スケール[最小]
	/// </summary>
	float baseAirDragScaleMin;

	/// <summary>
	/// 空気抵抗スケール[最大]
	/// </summary>
	float baseAirDragScaleMax;

} PlayerParamJumpSpeed;

typedef struct
{
	/// <summary>
	/// 垂直方向の初速
	/// </summary>
	float initialSpeed;

	/// <summary>
	/// 垂直方向の初速(バウンド時)
	/// </summary>
	float bounceSpeed;

	/// <summary>
	/// 水平方向の最高速度の最低値
	/// </summary>
	float limitSpeedMin;

} PlayerParamDoubleJump;

typedef struct
{
	/// <summary>
	/// 落下とみなす垂直速度
	/// </summary>
	float thresholdVertSpeed;

	/// <summary>
	/// ジャンプへの遷移を許容する時間
	/// </summary>
	float tolerateJumpTime;

	/// <summary>
	/// 落下失敗用、カウントダウンが開始される時間
	/// </summary>
	float fallEndDelayTime;

	/// <summary>
	/// 落下失敗用、カウントダウン開始からの猶予時間
	/// </summary>
	float fallEndFadeTime;

	/// <summary>
	/// 加速度[m/sec]
	/// </summary>
	float acceleForce;

	/// <summary>
	/// 減速度[m/sec]
	/// </summary>
	float deceleForce;

	/// <summary>
	/// オーバースピード減速度[m/sec]
	/// </summary>
	float overSpeedDeceleForce;

	/// <summary>
	/// 旋回力[deg/sec]
	/// </summary>
	float rotationForce;

	/// <summary>
	/// 速度比旋回力減衰の減衰開始速度
	/// </summary>
	float rotationForceDecaySpeed;

	/// <summary>
	/// 速度比旋回力減衰の減衰レート
	/// </summary>
	float rotationForceDecayRate;

	/// <summary>
	/// 速度比旋回力減衰の最大減衰力
	/// </summary>
	float rotationForceDecayMax;

} PlayerParamFall;

typedef struct
{
	/// <summary>
	/// 予備無敵時間
	/// </summary>
	float invincibleTime;

} PlayerParamDamageCommon;

typedef struct
{
	/// <summary>
	/// デフォルト水平初速
	/// </summary>
	float initialHorzSpeed;

	/// <summary>
	/// デフォルト垂直初速
	/// </summary>
	float initialVertSpeed;

	/// <summary>
	/// 減速度/空中
	/// </summary>
	float deceleForce;

	/// <summary>
	/// 落下遷移時間
	/// </summary>
	float transitFallTime;

	/// <summary>
	/// 重力スケール
	/// </summary>
	float gravityScale;

} PlayerParamDamageNormal;

typedef struct
{
	/// <summary>
	/// アクション固定時間
	/// </summary>
	float fixedTime;

} PlayerParamDamageTurnBack;

typedef struct
{
	/// <summary>
	/// デフォルト水平初速
	/// </summary>
	float initialHorzSpeed;

	/// <summary>
	/// デフォルト垂直初速
	/// </summary>
	float initialVertSpeed;

	/// <summary>
	/// 減速度/空中
	/// </summary>
	float deceleForceInAir;

	/// <summary>
	/// 減速度/地上
	/// </summary>
	float deceleForceOnGround;

	/// <summary>
	/// 重力スケール
	/// </summary>
	float gravityScale;

	/// <summary>
	/// ダウン時間
	/// </summary>
	float downTime;

	/// <summary>
	/// 次の行動へ割込遷移可能になる時間
	/// </summary>
	float transitTime;

} PlayerParamDamageBlowOff;

typedef struct
{
	/// <summary>
	/// 垂直速度
	/// </summary>
	float vertSpeed;

	/// <summary>
	/// 水平速度
	/// </summary>
	float horzSpeed;

	/// <summary>
	/// 減速度
	/// </summary>
	float deceleForce;

	/// <summary>
	/// 次の行動へ割込遷移可能になる時間
	/// </summary>
	float transitTime;

} PlayerParamDamageGuarded;

typedef struct
{
	/// <summary>
	/// アクション時間
	/// </summary>
	float actionTime;

	/// <summary>
	/// 最小速度
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 減速速度
	/// </summary>
	float lossSpeed;

	/// <summary>
	/// 減速時間
	/// </summary>
	float lossTime;

} PlayerParamDamageRunning;

typedef struct
{
	/// <summary>
	/// デフォルトアクション時間
	/// </summary>
	float actionTime;

} PlayerParamDamageQuake;

typedef struct
{
	/// <summary>
	/// ジャンプ速度
	/// </summary>
	Vector3 jumpVelocity;

	/// <summary>
	/// 重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// 予備無敵時間
	/// </summary>
	float invincibleTime;

	/// <summary>
	/// アクション禁止時間
	/// </summary>
	float noActionTime;

} PlayerParamDamageLava;

typedef struct
{
	/// <summary>
	/// 共通
	/// </summary>
	PlayerParamDamageCommon common;

	/// <summary>
	/// 通常
	/// </summary>
	PlayerParamDamageNormal normal;

	/// <summary>
	/// 仰け反る
	/// </summary>
	PlayerParamDamageTurnBack turnBack;

	/// <summary>
	/// 吹き飛ぶ
	/// </summary>
	PlayerParamDamageBlowOff blowOff;

	/// <summary>
	/// ガードされた
	/// </summary>
	PlayerParamDamageGuarded guarded;

	/// <summary>
	/// ガードされた[スパソニ]
	/// </summary>
	PlayerParamDamageGuarded guardedSS;

	/// <summary>
	/// 走りながら
	/// </summary>
	PlayerParamDamageRunning running;

	/// <summary>
	/// よろける
	/// </summary>
	PlayerParamDamageQuake quake;

	/// <summary>
	/// 溶岩
	/// </summary>
	PlayerParamDamageLava lava;

} PlayerParamDamage;

typedef struct
{
	/// <summary>
	/// 無敵時間
	/// </summary>
	float invincibleTime;

	/// <summary>
	/// デフォルト水平初速
	/// </summary>
	float initialHorzSpeed;

	/// <summary>
	/// デフォルト垂直初速
	/// </summary>
	float initialVertSpeed;

} PlayerParamDeadNormal;

typedef struct
{
	/// <summary>
	/// 通常
	/// </summary>
	PlayerParamDeadNormal normal;

} PlayerParamDead;

typedef struct
{
	/// <summary>
	/// 最低速度
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 終了速度
	/// </summary>
	float endSpeed;

	/// <summary>
	/// 減速躍度
	/// </summary>
	float deceleJerk;

	/// <summary>
	/// ボタン入力中の減速躍度
	/// </summary>
	float deceleJerkContinue;

	/// <summary>
	/// 最大減速度
	/// </summary>
	float deceleForceMax;

	/// <summary>
	/// 基本旋回力
	/// </summary>
	float baseRotateForce;

	/// <summary>
	/// 基本旋回力の基準速度
	/// </summary>
	float baseRotateForceSpeed;

	/// <summary>
	/// 最大旋回力
	/// </summary>
	float maxRotateForce;

	/// <summary>
	/// 正面方向旋回率
	/// </summary>
	float frontRotateRatio;

	/// <summary>
	/// 旋回力[オートラン]
	/// </summary>
	float rotationForceAutoRun;

	/// <summary>
	/// 斜面とみなす傾斜[deg]
	/// </summary>
	float movableMaxSlope;

	/// <summary>
	/// 重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// 最小継続時間
	/// </summary>
	float minContinueTime;

	/// <summary>
	/// オートランでスライディングを継続する最大時間
	/// </summary>
	float maxAutoRunTime;

	/// <summary>
	/// オートラン中のスライディング終了速度
	/// </summary>
	float endSpeedAutoRun;

	/// <summary>
	/// ループキックに遷移する時間
	/// </summary>
	float loopKickTransitTime;

} PlayerParamSliding;

typedef struct
{
	/// <summary>
	/// 落下/初速
	/// </summary>
	float initialSpeed;

	/// <summary>
	/// 落下/初加速度
	/// </summary>
	float initialAccele;

	/// <summary>
	/// 落下/最高加速度
	/// </summary>
	float maxAccele;

	/// <summary>
	/// 落下/躍度
	/// </summary>
	float jerk;

	/// <summary>
	/// 落下/最高落下速度
	/// </summary>
	float maxFallSpeed;

	/// <summary>
	/// 落下/角度
	/// </summary>
	float angle;

	/// <summary>
	/// 着地/割込不能時間
	/// </summary>
	float landingCancelTime;

	/// <summary>
	/// バウンドストンプ3回目のコリジョンサイズスケール
	/// </summary>
	float boundStompingCollisionScale;

} PlayerParamStomping;

typedef struct
{
	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// ブースト最高速度
	/// </summary>
	float maxBoostSpeed;

	/// <summary>
	/// 加速度
	/// </summary>
	float acceleForce;

	/// <summary>
	/// 減速度
	/// </summary>
	float deceleForce;

	/// <summary>
	/// 最低保証速度
	/// </summary>
	float limitSpeedMin;

} PlayerParamGrind;

typedef struct
{
	/// <summary>
	/// 初速
	/// </summary>
	float initialSpeed;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// ブレーキを始める角度
	/// </summary>
	float brakeAngle;

	/// <summary>
	/// 強いブレーキを始める角度
	/// </summary>
	float highBrakeAngle;

	/// <summary>
	/// 坂滑り後の斜面ブレーキ速度
	/// </summary>
	float brakeForce;

	/// <summary>
	/// 坂滑り後の水平面ブレーキ速度
	/// </summary>
	float brakeForceHigh;

	/// <summary>
	/// 重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// 空中重力サイズ
	/// </summary>
	float gravitySizeAir;

	/// <summary>
	/// 前方向滑り終了速度閾値
	/// </summary>
	float endSpeedFront;

	/// <summary>
	/// 後方向滑り終了速度閾値
	/// </summary>
	float endSpeedBack;

	/// <summary>
	/// 逆さま姿勢による落下への遷移時間
	/// </summary>
	float reverseFallTime;

	/// <summary>
	/// 落下から滑りに遷移する閾時間
	/// </summary>
	float fallToSlipTime;

	/// <summary>
	/// 坂滑り開始時のスリップ時間
	/// </summary>
	float slipIdlingTime;

	/// <summary>
	/// 最小スリップ時間
	/// </summary>
	float minSlipTime;

} PlayerParamFallSlope;

typedef struct
{
	/// <summary>
	/// 閾値速度
	/// </summary>
	float thresholdSpeed;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// バックフリップ角度
	/// </summary>
	float flipAngle;

} PlayerParamFallFlip;

typedef struct
{
	/// <summary>
	/// 転倒アクションをするか
	/// </summary>
	bool enabled;

	/// <summary>
	/// 転倒空中が横回転になる傾き
	/// </summary>
	float sideSpinAngle;

	/// <summary>
	/// 転倒空中の初速
	/// </summary>
	float initialVertSpeed;

	/// <summary>
	/// 転倒空中の重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// 転倒空中の重力サイズ[最大]
	/// </summary>
	float gravitySize2;

	/// <summary>
	/// 転倒空中の減速度
	/// </summary>
	float deceleForceInAir;

	/// <summary>
	/// 転倒空中の最低速度
	/// </summary>
	float minSpeedInAir;

	/// <summary>
	/// 左右転倒の旋回開始補間時間
	/// </summary>
	float rotateEaseTimeLeftRight;

	/// <summary>
	/// 前後転倒の旋回開始補間時間
	/// </summary>
	float rotateEaseTimeFrontBack;

	/// <summary>
	/// 左右転倒の最小旋回速度
	/// </summary>
	float rotateSpeedMinLeftRight;

	/// <summary>
	/// 左右転倒の最大旋回速度
	/// </summary>
	float rotateSpeedMaxLeftRight;

	/// <summary>
	/// 前後転倒の最小旋回速度
	/// </summary>
	float rotateSpeedMinFrontBack;

	/// <summary>
	/// 前後転倒の最大旋回速度
	/// </summary>
	float rotateSpeedMaxFrontBack;

	/// <summary>
	/// 転倒判定の左右角度/よろけ
	/// </summary>
	float angleLeftRightStagger;

	/// <summary>
	/// 転倒判定の左右角度/転倒
	/// </summary>
	float angleLeftRightRoll;

	/// <summary>
	/// 転倒判定の前後角度/転倒
	/// </summary>
	float angleFrontBackRoll;

	/// <summary>
	/// 転倒判定が大転倒になる地面の角度
	/// </summary>
	float angleBigRoll;

	/// <summary>
	/// 転倒判定の開始時間1
	/// </summary>
	float inRunTime;

	/// <summary>
	/// 転倒判定の開始時間2
	/// </summary>
	float inAirTime;

	/// <summary>
	/// 転倒時の前方向速度
	/// </summary>
	float rollSpeedFront;

	/// <summary>
	/// 大転倒時の速度減衰率
	/// </summary>
	float bigRollVelocityRatio;

	/// <summary>
	/// ドロップダッシュ移行ホールド時間
	/// </summary>
	float dropDashHoldTime;

	/// <summary>
	/// 垂直エアブレーキがかかる垂直方向速度
	/// </summary>
	float airBrakeVertSpeed;

	/// <summary>
	/// 垂直エアブレーキ力
	/// </summary>
	float airBrakeForce;

	/// <summary>
	/// エアトリック可能な高度
	/// </summary>
	float airTrickHeight;

	/// <summary>
	/// エアトリック可能になるまでの時間
	/// </summary>
	float airTrickTime;

} PlayerParamTumble;

typedef struct
{
	/// <summary>
	/// ジャンプ力
	/// </summary>
	float jumpForce;

	/// <summary>
	/// ジャンプ上昇加速力
	/// </summary>
	float jumpAddForce;

	/// <summary>
	/// 最長加速時間
	/// </summary>
	float addTime;

	/// <summary>
	/// 水平加速力
	/// </summary>
	float acceleForce;

	/// <summary>
	/// 水平減速力
	/// </summary>
	float deceleForce;

	/// <summary>
	/// ブレーキ減速力
	/// </summary>
	float brakeForce;

	/// <summary>
	/// 水平移動最低速度
	/// </summary>
	float limitSpeedMin;

	/// <summary>
	/// 水平移動最高速度
	/// </summary>
	float limitSpeedMax;

} PlayerParamSpinAttack;

typedef struct
{
	/// <summary>
	/// 速度
	/// </summary>
	float speed;

} PlayerParamHomingAttackData;

typedef struct
{
	/// <summary>
	/// ノックバック垂直速度
	/// </summary>
	float bounceVertSpeed;

	/// <summary>
	/// ノックバック水平速度
	/// </summary>
	float bounceHorzSpeed;

	/// <summary>
	/// ノックバック加速度
	/// </summary>
	float bounceAcceleForce;

	/// <summary>
	/// ノックバック減速度
	/// </summary>
	float bounceDeceleForce;

	/// <summary>
	/// ノックバック角度幅
	/// </summary>
	float bounceAngleWidth;

	/// <summary>
	/// ノックバック挙動時間
	/// </summary>
	float bounceTime;

	/// <summary>
	/// 攻撃不能時間
	/// </summary>
	float attackDownTime;

	/// <summary>
	/// ストンピング不能時間
	/// </summary>
	float attackDownTimeForStomp;

} PlayerParamHomingBounceData;

typedef struct
{
	/// <summary>
	/// 攻撃/ソニック
	/// </summary>
	PlayerParamHomingAttackData sonic;

	/// <summary>
	/// 攻撃/スーパーソニック
	/// </summary>
	PlayerParamHomingAttackData supersonic;

	/// <summary>
	/// バウンス/ソニック[強]
	/// </summary>
	PlayerParamHomingBounceData sonicBounce;

	/// <summary>
	/// バウンス/ソニック[弱]
	/// </summary>
	PlayerParamHomingBounceData sonicBounceWeak;

	/// <summary>
	/// バウンス/ソニック[嵐中]
	/// </summary>
	PlayerParamHomingBounceData sonicBounceStorm;

	/// <summary>
	/// バウンス/ソニック[嵐吸い込み中]
	/// </summary>
	PlayerParamHomingBounceData sonicBounceStormSwirl;

	/// <summary>
	/// バウンス/スーパーソニック
	/// </summary>
	PlayerParamHomingBounceData supersonicBounce;

	/// <summary>
	/// ホーミングカメラ開始補間時間
	/// </summary>
	float cameraEaseInTime;

	/// <summary>
	/// ホーミングカメラ終了補間時間
	/// </summary>
	float cameraEaseOutTime;

} PlayerParamHomingAttack;

typedef struct
{
	/// <summary>
	/// ノックバック垂直速度
	/// </summary>
	float bounceVertSpeed;

	/// <summary>
	/// ノックバック水平速度
	/// </summary>
	float bounceHorzSpeed;

	/// <summary>
	/// 攻撃後再攻撃不能時間
	/// </summary>
	float attackDownTime;

	/// <summary>
	/// 攻撃後攻撃可能時間
	/// </summary>
	float enableHomingTime;

} PlayerParamHitEnemy;

typedef struct
{
	/// <summary>
	/// 最高落下速度
	/// </summary>
	float maxVertSpeed;

	/// <summary>
	/// 落下加速度
	/// </summary>
	float acceleVertForce;

	/// <summary>
	/// 最高水平速度
	/// </summary>
	float maxHorzSpeed;

	/// <summary>
	/// 水平移動加速度
	/// </summary>
	float acceleHorzForce;

} SpeedParam;

typedef struct
{
	/// <summary>
	/// 通常
	/// </summary>
	SpeedParam normal;

	/// <summary>
	/// ブースト
	/// </summary>
	SpeedParam fast;

	/// <summary>
	/// ダメージ中
	/// </summary>
	SpeedParam damaged;

	/// <summary>
	/// リングダッシュ中
	/// </summary>
	SpeedParam ringdash;

	/// <summary>
	/// 開始に必要な高度
	/// </summary>
	float startHeight;

	/// <summary>
	/// 開始に必要な落下速度
	/// </summary>
	float startSpeed;

	/// <summary>
	/// 落下減速度
	/// </summary>
	float deceleVertForce;

	/// <summary>
	/// 水平減速度
	/// </summary>
	float deceleHorzForce;

	/// <summary>
	/// 無入力減速度
	/// </summary>
	float deceleNeutralForce;

	/// <summary>
	/// ダメージ時間
	/// </summary>
	float damageTime;

	/// <summary>
	/// リングダッシュ時間
	/// </summary>
	float ringdashTime;

} PlayerParamDiving;

typedef struct
{
	/// <summary>
	/// 垂直方向の速度減衰率
	/// </summary>
	float damperV;

	/// <summary>
	/// 水平方向の速度減衰率
	/// </summary>
	float damperH;

	/// <summary>
	/// ファンからの距離に応じた加速率
	/// </summary>
	float accelRate;

	/// <summary>
	/// スティックによる移動加速度FV
	/// </summary>
	float moveForceFV;

	/// <summary>
	/// スティックによる移動加速度SV
	/// </summary>
	float moveForceSV;

	/// <summary>
	/// ジャンプから移行できる速度
	/// </summary>
	float jumpCheckSpeed;

} PlayerParamFan;

typedef struct
{
	/// <summary>
	/// 上方向初速
	/// </summary>
	float jumpSpeed;

	/// <summary>
	/// 後方向初速
	/// </summary>
	float backSpeed;

	/// <summary>
	/// 重力加速度
	/// </summary>
	float downAccel;

	/// <summary>
	/// 垂直方向ダンパー
	/// </summary>
	float damperV;

	/// <summary>
	/// 水平方向ダンパー
	/// </summary>
	float damperH;

	/// <summary>
	/// 時間
	/// </summary>
	float time;

} PlayerParamBackflip;

typedef struct
{
	/// <summary>
	/// 初速
	/// </summary>
	float startSpeed;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// ダメージ時初速
	/// </summary>
	float damageSpeed;

	/// <summary>
	/// ダメージ時減速度
	/// </summary>
	float damageBrake;

	/// <summary>
	/// 回転速度
	/// </summary>
	float steeringSpeed;

	/// <summary>
	/// 回転速度になる速度
	/// </summary>
	float endSteeringSpeed;

} PlayerParamSlowMove;

typedef struct
{
	/// <summary>
	/// 発動斜度
	/// </summary>
	float startSlopeAngle;

	/// <summary>
	/// 終了斜度
	/// </summary>
	float endSlopeAngle;

	/// <summary>
	/// 発動速度
	/// </summary>
	float startSpeed;

	/// <summary>
	/// 終了速度
	/// </summary>
	float endSpeed;

	/// <summary>
	/// ブレーキ判定スティック角度
	/// </summary>
	float stickAngle;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// スティック入力時の減速度
	/// </summary>
	float forceBrake;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

} PlayerParamSpin;

typedef struct
{
	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 移動速度 基本値
	/// </summary>
	float walkSpeed;

	/// <summary>
	/// 移動速度 最大値
	/// </summary>
	float walkSpeedMax;

	/// <summary>
	/// ダッシュ移動速度 基本値
	/// </summary>
	float runSpeed;

	/// <summary>
	/// ダッシュ移動速度 最大値
	/// </summary>
	float runSpeedMax;

	/// <summary>
	/// 移動速度 変形メッシュ上 基本値
	/// </summary>
	float walkSpeedOnMesh;

	/// <summary>
	/// 移動速度 変形メッシュ上 最大値
	/// </summary>
	float walkSpeedOnMeshMax;

	/// <summary>
	/// ダッシュ移動速度 変形メッシュ上 基本値
	/// </summary>
	float runSpeedOnMesh;

	/// <summary>
	/// ダッシュ移動速度 変形メッシュ上 最大値
	/// </summary>
	float runSpeedOnMeshMax;

	/// <summary>
	/// 壁移動移行最低速度
	/// </summary>
	float minAccessSpeed;

	/// <summary>
	/// スティックで貼り付ける速度
	/// </summary>
	float stickSpeed;

	/// <summary>
	/// 専用重力加速度
	/// </summary>
	float gravity;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel;

	/// <summary>
	/// 減速ブレーキ
	/// </summary>
	float brake;

	/// <summary>
	/// 停止ブレーキ
	/// </summary>
	float stopBrake;

	/// <summary>
	/// 落下移行速度
	/// </summary>
	float fallSpeed;

	/// <summary>
	/// 回転速度1
	/// </summary>
	float steeringSpeed1;

	/// <summary>
	/// 回転速度2
	/// </summary>
	float steeringSpeed2;

	/// <summary>
	/// 回転速度1になる速度
	/// </summary>
	float startSteeringSpeed;

	/// <summary>
	/// 回転速度2になる速度
	/// </summary>
	float endSteeringSpeed;

	/// <summary>
	/// 開始に必要な走行時間
	/// </summary>
	float startTime;

	/// <summary>
	/// 壁移動エネルギー消費速度 ベース
	/// </summary>
	float useEnergySpeedBase;

	/// <summary>
	/// 壁移動エネルギー消費速度 ベース 変形メッシュ上
	/// </summary>
	float useEnergySpeedBaseOnMesh;

	/// <summary>
	/// 壁移動エネルギー消費速度 可変
	/// </summary>
	float useEnergySpeedVal;

	/// <summary>
	/// 壁移動エネルギー消費速度 可変 変形メッシュ上
	/// </summary>
	float useEnergySpeedValOnMesh;

	/// <summary>
	/// 壁移動エネルギー可変角度
	/// </summary>
	float useEnergyAngle;

	/// <summary>
	/// 壁移動エネルギー可変角度 変形メッシュ上
	/// </summary>
	float useEnergyAngleOnMesh;

	/// <summary>
	/// 減速開始エネルギー
	/// </summary>
	float brakeStartEnergy;

	/// <summary>
	/// 減速開始エネルギー 変形メッシュ上
	/// </summary>
	float brakeStartEnergyOnMesh;

	/// <summary>
	/// ホーミング索敵範囲　近
	/// </summary>
	float homingSearchDistanceNear;

	/// <summary>
	/// ホーミング索敵範囲　遠
	/// </summary>
	float homingSearchDistanceFar;

	/// <summary>
	/// 壁の凹凸の高さ 上り
	/// </summary>
	float wallBumpHeightUpper;

	/// <summary>
	/// 壁の凹凸の高さ 下り
	/// </summary>
	float wallBumpHeightUnder;

	/// <summary>
	/// 吹っ飛び移行時のリカバリーターゲット検索時間
	/// </summary>
	float recoveryCheckTime;

} PlayerParamWallMove;

typedef struct
{
	/// <summary>
	/// 張り付き/重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// 張り付き/最小時間
	/// </summary>
	float minTime;

	/// <summary>
	/// 張り付き/最大時間
	/// </summary>
	float maxTime;

	/// <summary>
	/// 張り付き/滑らない時間
	/// </summary>
	float stopTime;

	/// <summary>
	/// 張り付き/最高滑落速度
	/// </summary>
	float maxDownSpeed;

	/// <summary>
	/// 張り付き/落下になる地面までの高さ
	/// </summary>
	float fallGroundDistance;

	/// <summary>
	/// ジャンプ/正面方向速度
	/// </summary>
	float frontForce;

	/// <summary>
	/// ジャンプ/上方向速度
	/// </summary>
	float upForce;

	/// <summary>
	/// ジャンプ/射出時間
	/// </summary>
	float impulseTime;

} PlayerParamWallJump;

typedef struct
{
	/// <summary>
	/// 前方移動速度
	/// </summary>
	float stepSpeedFront;

	/// <summary>
	/// 前方移動速度(ダッシュ時)
	/// </summary>
	float stepSpeedFrontDash;

	/// <summary>
	/// 側方移動速度
	/// </summary>
	float stepSpeedSide;

	/// <summary>
	/// 側方移動速度(ダッシュ時)
	/// </summary>
	float stepSpeedSideDash;

	/// <summary>
	/// 後方移動速度
	/// </summary>
	float stepSpeedBack;

	/// <summary>
	/// ダッシュ時の倍率
	/// </summary>
	float stepDashRate;

	/// <summary>
	/// 移動モーション再生レート 最大値
	/// </summary>
	float maxAnimSpeed;

	/// <summary>
	/// クライミング疲労一定角度
	/// </summary>
	float exhaustAngle;

	/// <summary>
	/// クライミング疲労一定角度 変形メッシュ上
	/// </summary>
	float exhaustAngleOnMesh;

	/// <summary>
	/// クライミング疲労基本量　開始角度時の1mあたりの消費量
	/// </summary>
	float exhaustBase;

	/// <summary>
	/// クライミング疲労基本量　 変形メッシュ上
	/// </summary>
	float exhaustBaseOnMesh;

	/// <summary>
	/// クライミング疲労増加率　角度に比例
	/// </summary>
	float exhaustRate;

	/// <summary>
	/// クライミング疲労増加率　 変形メッシュ上
	/// </summary>
	float exhaustRateOnMesh;

	/// <summary>
	/// 握力ゲージ消費速度
	/// </summary>
	float useGrabGaugeSpeed;

	/// <summary>
	/// 握力ゲージ消費速度  変形メッシュ上
	/// </summary>
	float useGrabGaugeSpeedOnMesh;

	/// <summary>
	/// ターボ時握力ゲージ消費量
	/// </summary>
	float useGrabGaugeTurbo;

	/// <summary>
	/// ターボ時握力ゲージ消費量  変形メッシュ上
	/// </summary>
	float useGrabGaugeTurboOnMesh;

	/// <summary>
	/// ホーミング索敵範囲　近
	/// </summary>
	float homingSearchDistanceNear;

	/// <summary>
	/// ホーミング索敵範囲　遠
	/// </summary>
	float homingSearchDistanceFar;

	/// <summary>
	/// 姿勢の重力上方向リセットが起こる角度
	/// </summary>
	float resetAngle;

	/// <summary>
	/// 吹っ飛び移行時のリカバリーターゲット検索時間
	/// </summary>
	float recoveryCheckTime;

} PlayerParamClimbing;

typedef struct
{
	/// <summary>
	/// 滑落時間
	/// </summary>
	float time;

	/// <summary>
	/// 滑落速度
	/// </summary>
	float speed;

	/// <summary>
	/// 滑落速度 メッシュ上
	/// </summary>
	float speedOnMesh;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 減速度 メッシュ上
	/// </summary>
	float brakeOnMesh;

} PlayerParamSlideDown;

typedef struct
{
	/// <summary>
	/// 消費速度/ソニック
	/// </summary>
	float consumptionRate;

	/// <summary>
	/// 消費速度/スーパーソニック
	/// </summary>
	float consumptionRateSS;

	/// <summary>
	/// 回復速度/ソニック
	/// </summary>
	float recoveryRate;

	/// <summary>
	/// 回復速度/スーパーソニック
	/// </summary>
	float recoveryRateSS;

	/// <summary>
	/// 再点火許容レート
	/// </summary>
	float reigniteRatio;

	/// <summary>
	/// リングによる回復量
	/// </summary>
	float recoveryByRing;

	/// <summary>
	/// 攻撃による回復量
	/// </summary>
	float recoveryByAttack;

	/// <summary>
	/// ブースト中のブラー強度
	/// </summary>
	float blurPowers[3];

	/// <summary>
	/// ブースト開始時のブラー補間時間
	/// </summary>
	float blurEaseInTime;

	/// <summary>
	/// ブースト終了時のブラー補間時間
	/// </summary>
	float blurEaseOutTime;

	/// <summary>
	/// ブースト解除の下限速度
	/// </summary>
	float endSpeed;

	/// <summary>
	/// パワーブースト演出のクールタイム
	/// </summary>
	float powerBoostCoolTime;

	/// <summary>
	/// 無限ブースト時間
	/// </summary>
	float infinityBoostTime;

} PlayerParamBoost;

typedef struct
{
	/// <summary>
	/// 水平方向初速  基本値
	/// </summary>
	float startHSpeed;

	/// <summary>
	/// 水平方向初速  最高値
	/// </summary>
	float startHSpeedMax;

	/// <summary>
	/// 垂直方向初速
	/// </summary>
	float startVSpeed;

	/// <summary>
	/// 水平方向最低速度 基本値
	/// </summary>
	float minHSpeed;

	/// <summary>
	/// 水平方向最低速度 最高値
	/// </summary>
	float minHSpeedMax;

	/// <summary>
	/// 初速から最低速度になるまでの時間
	/// </summary>
	float brakeTime;

	/// <summary>
	/// 最低初速持続時間
	/// </summary>
	float minKeepTime;

	/// <summary>
	/// 最高初速持続時間
	/// </summary>
	float maxKeepTime;

	/// <summary>
	/// 最高持続時間
	/// </summary>
	float maxTime;

	/// <summary>
	/// 重力加速度倍率
	/// </summary>
	float gravityRate;

	/// <summary>
	/// 回転速度
	/// </summary>
	float steeringSpeed;

	/// <summary>
	/// 落下状態になってもAirBoostからの遷移とみなす追加時間
	/// </summary>
	float additionalTransitTime;

	/// <summary>
	/// スパソニのオートラン中入力時の判定時間
	/// </summary>
	float supersonicTime;

} PlayerParamAirBoost;

typedef struct
{
	/// <summary>
	/// 横方向の初速
	/// </summary>
	float initialSideSpeed;

	/// <summary>
	/// 横方向の加速度
	/// </summary>
	float acceleSideForce;

	/// <summary>
	/// 横方向の減速度
	/// </summary>
	float deceleSideForce;

	/// <summary>
	/// 横方向の最高速度
	/// </summary>
	float maxSideSpeed;

} PlayerParamAutorun;

typedef struct
{
	/// <summary>
	/// 側転速度
	/// </summary>
	float speed;

	/// <summary>
	/// 側転ブレーキ力
	/// </summary>
	float brakeForce;

	/// <summary>
	/// モーション速度比率
	/// </summary>
	float motionSpeedRatio;

	/// <summary>
	/// ステップ速度
	/// </summary>
	float stepSpeed;

	/// <summary>
	/// 最大ステップ距離
	/// </summary>
	float maxStepDistance;

	/// <summary>
	/// 最小ステップ距離
	/// </summary>
	float minStepDistance;

	/// <summary>
	/// ステップ距離が最大になる速度
	/// </summary>
	float maxStepSpeed;

	/// <summary>
	/// ステップ距離が最小になる速度
	/// </summary>
	float minStepSpeed;

} PlayerParamSideStep;

typedef struct
{
	/// <summary>
	/// 側転速度
	/// </summary>
	float speed;

	/// <summary>
	/// 側転ブレーキ力
	/// </summary>
	float brakeForce;

	/// <summary>
	/// モーション速度比率
	/// </summary>
	float motionSpeedRatio;

	/// <summary>
	/// ステップ速度
	/// </summary>
	float stepSpeed;

	/// <summary>
	/// 最大ステップ距離
	/// </summary>
	float maxStepDistance;

	/// <summary>
	/// 最小ステップ距離
	/// </summary>
	float minStepDistance;

	/// <summary>
	/// ステップ距離が最大になる速度
	/// </summary>
	float maxStepSpeed;

	/// <summary>
	/// ステップ距離が最小になる速度
	/// </summary>
	float minStepSpeed;

} PlayerParamSideStep2;

typedef struct
{
	/// <summary>
	/// 発動に必要な最低速度
	/// </summary>
	float needSpeed;

	/// <summary>
	/// 前方への加速度
	/// </summary>
	float acceleForce;

	/// <summary>
	/// 移動ラインへの引き込み加速度
	/// </summary>
	float acceleSideForce;

	/// <summary>
	/// サイドステップの初速
	/// </summary>
	float stepInitialSpeed;

	/// <summary>
	/// 壁衝突回避時の加速度
	/// </summary>
	float avoidForce;

	/// <summary>
	/// ジャスト回避時の追加加速度
	/// </summary>
	float justBoostForce;

	/// <summary>
	/// ジャスト回避時の最大速度
	/// </summary>
	float justBoostMax;

	/// <summary>
	/// ジャスト回避時のブースト時間
	/// </summary>
	float justBoostTime;

	/// <summary>
	/// ジャスト回避ブーストの終了時減速度
	/// </summary>
	float justBoostBrake;

} PlayerParamQuickStep;

typedef struct
{
	/// <summary>
	/// 最小受付時間
	/// </summary>
	float minRecieveTime;

	/// <summary>
	/// 最大受付時間
	/// </summary>
	float maxRecieveTime;

	/// <summary>
	/// 失敗時硬直時間
	/// </summary>
	float frozenTime;

	/// <summary>
	/// 短エフェクト開始補間時間
	/// </summary>
	float justEffectEasein;

	/// <summary>
	/// 短エフェクト終了補間時間
	/// </summary>
	float justEffectEaseout;

	/// <summary>
	/// 短エフェクト時間
	/// </summary>
	float justEffectTime;

	/// <summary>
	/// 長エフェクト開始補間時間
	/// </summary>
	float justEffectEasein2;

	/// <summary>
	/// 長エフェクト終了補間時間
	/// </summary>
	float justEffectEaseout2;

	/// <summary>
	/// 長エフェクト時間
	/// </summary>
	float justEffectTime2;

} PlayerParamParry;

typedef struct
{
	/// <summary>
	/// 速度
	/// </summary>
	float speed;

	/// <summary>
	/// 減衰
	/// </summary>
	float damper;

	/// <summary>
	/// パリー可能時間
	/// </summary>
	float parryTime;

	/// <summary>
	/// 無敵時間
	/// </summary>
	float invincibleTime;

} PlayerParamAvoidData;

typedef struct
{
	/// <summary>
	/// アクション時間
	/// </summary>
	float time;

	/// <summary>
	/// アクション固定時間
	/// </summary>
	float fixedTime;

	/// <summary>
	/// 連続回避の先行入力開始時間
	/// </summary>
	float reentryInputPriorityTime;

	/// <summary>
	/// 連続回避の禁止時間
	/// </summary>
	float reentryTime;

	/// <summary>
	/// 前方回避角度
	/// </summary>
	float frontAngle;

	/// <summary>
	/// 後方回避角度
	/// </summary>
	float backAngle;

	/// <summary>
	/// 空中回避の加算落下速度
	/// </summary>
	float addFallSpeed;

	/// <summary>
	/// 移動
	/// </summary>
	PlayerParamAvoidData data[7];

	/// <summary>
	/// 回り込み基準距離
	/// </summary>
	float baseDistance;

	/// <summary>
	/// 回り込み制限角度
	/// </summary>
	float limitAngle;

} PlayerParamAvoid;

typedef struct
{
	/// <summary>
	/// 汎用
	/// </summary>
	PlayerParamCommon common;

	/// <summary>
	/// 速度
	/// </summary>
	PlayerParamSpeed speed;

	/// <summary>
	/// 角速度
	/// </summary>
	PlayerParamRotation rotation;

	/// <summary>
	/// 走りモーション
	/// </summary>
	PlayerParamRunning running;

	/// <summary>
	/// 姿勢回転
	/// </summary>
	PlayerParamBalance balance;

	/// <summary>
	/// ブレーキ
	/// </summary>
	PlayerParamBrake brake;

	/// <summary>
	/// ターン
	/// </summary>
	PlayerParamTurn turn;

	/// <summary>
	/// ジャンプ
	/// </summary>
	PlayerParamJump jump;

	/// <summary>
	/// ジャンプ中速度
	/// </summary>
	PlayerParamJumpSpeed jumpSpeed;

	/// <summary>
	/// 2段ジャンプ
	/// </summary>
	PlayerParamDoubleJump doubleJump;

	/// <summary>
	/// 落下
	/// </summary>
	PlayerParamFall fall;

	/// <summary>
	/// ダメージ
	/// </summary>
	PlayerParamDamage damage;

	/// <summary>
	/// 死亡
	/// </summary>
	PlayerParamDead dead;

	/// <summary>
	/// スライディング
	/// </summary>
	PlayerParamSliding sliding;

	/// <summary>
	/// ストンピング
	/// </summary>
	PlayerParamStomping stomping;

	/// <summary>
	/// グラインド
	/// </summary>
	PlayerParamGrind grind;

	/// <summary>
	/// 坂滑り
	/// </summary>
	PlayerParamFallSlope fallSlope;

	/// <summary>
	/// 坂バックフリップ
	/// </summary>
	PlayerParamFallFlip fallFlip;

	/// <summary>
	/// バンプジャンプ
	/// </summary>
	PlayerParamTumble tumble;

	/// <summary>
	/// スピンアタック
	/// </summary>
	PlayerParamSpinAttack spinAttack;

	/// <summary>
	/// ホーミングアタック
	/// </summary>
	PlayerParamHomingAttack homingAttack;

	/// <summary>
	/// 敵接触
	/// </summary>
	PlayerParamHitEnemy hitEnemy;

	/// <summary>
	/// ダイビング
	/// </summary>
	PlayerParamDiving diving;

	/// <summary>
	/// ファン
	/// </summary>
	PlayerParamFan fan;

	/// <summary>
	/// 後方宙返り
	/// </summary>
	PlayerParamBackflip backflip;

	/// <summary>
	/// 低速移動
	/// </summary>
	PlayerParamSlowMove slowmove;

	/// <summary>
	/// スピン
	/// </summary>
	PlayerParamSpin spin;

	/// <summary>
	/// 壁移動
	/// </summary>
	PlayerParamWallMove wallmove;

	/// <summary>
	/// 壁ジャンプ
	/// </summary>
	PlayerParamWallJump walljump;

	/// <summary>
	/// クライミング
	/// </summary>
	PlayerParamClimbing climbing;

	/// <summary>
	/// 滑落
	/// </summary>
	PlayerParamSlideDown slidedown;

	/// <summary>
	/// ブースト
	/// </summary>
	PlayerParamBoost boost;

	/// <summary>
	/// エアブースト
	/// </summary>
	PlayerParamAirBoost airboost;

	/// <summary>
	/// オートラン
	/// </summary>
	PlayerParamAutorun autorun;

	/// <summary>
	/// サイドステップ
	/// </summary>
	PlayerParamSideStep sidestep;

	/// <summary>
	/// サイドステップ(特殊状況)
	/// </summary>
	PlayerParamSideStep2 sidestep2;

	/// <summary>
	/// クイックステップ
	/// </summary>
	PlayerParamQuickStep quickstep;

	/// <summary>
	/// パリー
	/// </summary>
	PlayerParamParry parry;

	/// <summary>
	/// 回避
	/// </summary>
	PlayerParamAvoid avoid;

} ModePackage;

typedef struct
{
	/// <summary>
	/// 垂直方向の速度減衰率
	/// </summary>
	float damperV;

	/// <summary>
	/// 水平方向の速度減衰率
	/// </summary>
	float damperH;

	/// <summary>
	/// 水平方向の減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 指定高度からの距離に応じた加速率
	/// </summary>
	float accelRate;

	/// <summary>
	/// スティックによる移動加速度
	/// </summary>
	float moveForce;

	/// <summary>
	/// 水平方向の最高速度
	/// </summary>
	float maxSpeedH;

	/// <summary>
	/// 垂直方向の最高速度
	/// </summary>
	float maxSpeedV;

	/// <summary>
	/// 渦の回転速度
	/// </summary>
	float rotateSpeed;

	/// <summary>
	/// 渦の回転角速度
	/// </summary>
	float rotateAngularSpeed;

	/// <summary>
	/// 渦の吸い込み速度最小値
	/// </summary>
	float minDrawSpeed;

	/// <summary>
	/// 渦の吸い込み速度最大値
	/// </summary>
	float maxDrawSpeed;

	/// <summary>
	/// 渦の吸い込み速度最小値になる距離
	/// </summary>
	float minDrawSpeedDistance;

	/// <summary>
	/// 渦の吸い込み速度最大値になる距離
	/// </summary>
	float maxDrawSpeedDistance;

	/// <summary>
	/// ダメージ時間
	/// </summary>
	float damageTime;

	/// <summary>
	/// ダメージ時ブレーキをかけない時間
	/// </summary>
	float damageNoBrakeTime;

	/// <summary>
	/// ホーミングアタックリアクション時の向き変更する力
	/// </summary>
	float forceHomingReaction;

	/// <summary>
	/// ホーミングアタックリアクション時の向き変更する力(巻き込まれ中)
	/// </summary>
	float forceHomingReaction2;

} PlayerParamStorm;

typedef struct
{
	/// <summary>
	/// 加速度[m/sec]
	/// </summary>
	float acceleForce;

	/// <summary>
	/// 減速度[m/sec]
	/// </summary>
	float deceleForce;

	/// <summary>
	/// オーバースピード減速度[m/sec]
	/// </summary>
	float overSpeedDeceleForce;

	/// <summary>
	/// 旋回力[deg/sec]
	/// </summary>
	float rotationForce;

	/// <summary>
	/// 速度比旋回力減衰の減衰開始速度
	/// </summary>
	float rotationForceDecaySpeed;

	/// <summary>
	/// 速度比旋回力減衰の減衰レート
	/// </summary>
	float rotationForceDecayRate;

	/// <summary>
	/// 速度比旋回力減衰の最大減衰力
	/// </summary>
	float rotationForceDecayMax;

} PlayerParamCloudJump;

typedef struct
{
	/// <summary>
	/// 落下加速度
	/// </summary>
	float fallAccel;

	/// <summary>
	/// 水の抵抗係数
	/// </summary>
	float damper;

	/// <summary>
	/// ジャンプ速度
	/// </summary>
	float jumpSpeed;

	/// <summary>
	/// ストンピング速度
	/// </summary>
	float stompingSpeed;

	/// <summary>
	/// バウンド速度
	/// </summary>
	float boundSpeed;

} PlayerParamAquaBall;

typedef struct
{
	/// <summary>
	/// 前方加速力
	/// </summary>
	float frontAccel;

	/// <summary>
	/// 前方減速力
	/// </summary>
	float frontBrake;

	/// <summary>
	/// 横方減速力
	/// </summary>
	float sideBrake;

	/// <summary>
	/// ダメージ時減速力
	/// </summary>
	float damageBrake;

	/// <summary>
	/// 自動進行方向修正速度
	/// </summary>
	float defaultRotateSpeed;

	/// <summary>
	/// 進行方向修正速度
	/// </summary>
	float rotateSpeed;

	/// <summary>
	/// 空中進行方向修正速度
	/// </summary>
	float rotateSpeedAir;

	/// <summary>
	/// 重力加速度
	/// </summary>
	float gravity;

} PlayerParamSlider;

typedef struct
{
	/// <summary>
	/// スキルピース取得時の値
	/// </summary>
	uint32_t amount;

} PlayerParamAirTrick;

typedef struct
{
	/// <summary>
	/// 旋回判定入力角度
	/// </summary>
	float startAngle;

	/// <summary>
	/// 終了速度
	/// </summary>
	float endSpeed;

	/// <summary>
	/// 最低速度 基本値
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 最低速度 最大値
	/// </summary>
	float minSpeedMax;

	/// <summary>
	/// 最高速度 基本値
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 最高速度 最大値
	/// </summary>
	float maxSpeedMax;

	/// <summary>
	/// ブースト時　最低速度 基本値
	/// </summary>
	float minBoostSpeed;

	/// <summary>
	/// ブースト時　最低速度 最大値
	/// </summary>
	float minBoostSpeedMax;

	/// <summary>
	/// ブースト時　最高速度 基本値
	/// </summary>
	float maxBoostSpeed;

	/// <summary>
	/// ブースト時　最高速度 最大値
	/// </summary>
	float maxBoostSpeedMax;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 最大ドリフト角
	/// </summary>
	float maxSteerAngle;

	/// <summary>
	/// 舵加速度
	/// </summary>
	float steerAccel;

	/// <summary>
	/// 最大舵速度
	/// </summary>
	float maxSteerSpeed;

	/// <summary>
	/// 無入力時舵加速度
	/// </summary>
	float neutralSteerAccel;

	/// <summary>
	/// 無入力時最大舵速度
	/// </summary>
	float maxNeutralSteerSpeed;

	/// <summary>
	/// 最大回転速度
	/// </summary>
	float maxRotateSpeed;

	/// <summary>
	/// 走行復帰時間
	/// </summary>
	float recoverTime;

	/// <summary>
	/// 最大チャージ時間
	/// </summary>
	float maxChargeTime;

	/// <summary>
	/// 最低ダッシュ速度
	/// </summary>
	float minDashSpeed;

	/// <summary>
	/// 最大ダッシュ速度
	/// </summary>
	float maxDashSpeed;

	/// <summary>
	/// 最低ダッシュジャンプ速度
	/// </summary>
	float minDashJumpSpeed;

	/// <summary>
	/// 最大ダッシュジャンプ速度
	/// </summary>
	float maxDashJumpSpeed;

	/// <summary>
	/// ジャンプ速度
	/// </summary>
	float jumpSpeed;

	/// <summary>
	/// 落下判定時間
	/// </summary>
	float checkFallTime;

} PlayerParamDrift;

typedef struct
{
	/// <summary>
	/// 旋回判定入力角度
	/// </summary>
	float startAngle;

	/// <summary>
	/// 終了速度
	/// </summary>
	float endSpeed;

	/// <summary>
	/// 最低速度 基本値
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 最高速度 基本値
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 最大ドリフト角
	/// </summary>
	float maxSteerAngle;

	/// <summary>
	/// 舵加速度
	/// </summary>
	float steerAccel;

	/// <summary>
	/// 最大舵速度
	/// </summary>
	float maxSteerSpeed;

	/// <summary>
	/// 無入力時舵加速度
	/// </summary>
	float neutralSteerAccel;

	/// <summary>
	/// 無入力時最大舵速度
	/// </summary>
	float maxNeutralSteerSpeed;

	/// <summary>
	/// 最大回転速度
	/// </summary>
	float maxRotateSpeed;

	/// <summary>
	/// 走行復帰時間
	/// </summary>
	float recoverTime;

} PlayerParamDriftAir;

typedef struct
{
	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 回転速度1
	/// </summary>
	float steeringSpeed1;

	/// <summary>
	/// 回転速度2
	/// </summary>
	float steeringSpeed2;

	/// <summary>
	/// 回転速度1になる速度
	/// </summary>
	float startSteeringSpeed;

	/// <summary>
	/// 回転速度2になる速度
	/// </summary>
	float endSteeringSpeed;

	/// <summary>
	/// 制御不能速度
	/// </summary>
	float outOfControlSpeed;

	/// <summary>
	/// 走行復帰速度
	/// </summary>
	float checkDashSpeed;

	/// <summary>
	/// 走行復帰時間
	/// </summary>
	float checkDashTime;

} PlayerParamDriftDash;

typedef struct
{
	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 最低速度
	/// </summary>
	float minSpeed;

	/// <summary>
	/// ダメージ速度
	/// </summary>
	float damageSpeed;

	/// <summary>
	/// 最低速度への加速度
	/// </summary>
	float accel;

	/// <summary>
	/// ダメージ時減速度
	/// </summary>
	float damageBrake;

	/// <summary>
	/// ダメージ減速時間
	/// </summary>
	float damageBrakeTime;

	/// <summary>
	/// ダメージモーション時間
	/// </summary>
	float damageMotionTime;

	/// <summary>
	/// ダメージ後無敵時間
	/// </summary>
	float damageInvicibleTime;

	/// <summary>
	/// 最高速ダンパー係数
	/// </summary>
	float damper;

	/// <summary>
	/// 空中ダンパー垂直方向
	/// </summary>
	float airDamperV;

	/// <summary>
	/// 空中ダンパー水平方向
	/// </summary>
	float airDamperH;

	/// <summary>
	/// 専用重力加速度
	/// </summary>
	float gravity;

	/// <summary>
	/// 空中ジャンプ速度
	/// </summary>
	float airJumpSpeed;

	/// <summary>
	/// 地上ジャンプ速度
	/// </summary>
	float groundJumpSpeed;

	/// <summary>
	/// 空中加速度
	/// </summary>
	float airAccel;

	/// <summary>
	/// 最高空中加速度
	/// </summary>
	float maxAirAddSpeed;

	/// <summary>
	/// ダウンフォース係数
	/// </summary>
	float downForceRate;

	/// <summary>
	/// 回転速度1
	/// </summary>
	float steeringSpeed1;

	/// <summary>
	/// 回転速度2
	/// </summary>
	float steeringSpeed2;

	/// <summary>
	/// 回転速度3
	/// </summary>
	float steeringSpeed3;

	/// <summary>
	/// 回転速度1になる速度
	/// </summary>
	float startSteeringSpeed;

	/// <summary>
	/// 回転速度2になる速度
	/// </summary>
	float endSteeringSpeed;

	/// <summary>
	/// 開始速度
	/// </summary>
	float startSpeed;

	/// <summary>
	/// 開始斜度
	/// </summary>
	float startSlope;

	/// <summary>
	/// 静止時開始斜度
	/// </summary>
	float staticStartSlope;

	/// <summary>
	/// 終了斜度
	/// </summary>
	float finishSlope;

	/// <summary>
	/// 終了時間
	/// </summary>
	float finishTime;

	/// <summary>
	/// 大着地判定時間
	/// </summary>
	float bigLandTime;

} PlayerParamBoarding;

typedef struct
{
	/// <summary>
	/// 最大チャージ時間
	/// </summary>
	float maxChargeTime;

	/// <summary>
	/// 最低ダッシュ速度 基本値
	/// </summary>
	float minDashSpeed;

	/// <summary>
	/// 最低ダッシュ速度 最大値
	/// </summary>
	float minDashSpeedMax;

	/// <summary>
	/// 最大ダッシュ速度 基本値
	/// </summary>
	float maxDashSpeed;

	/// <summary>
	/// 最大ダッシュ速度 最大値
	/// </summary>
	float maxDashSpeedMax;

	/// <summary>
	/// バンプジャンプからのダッシュ速度
	/// </summary>
	float tumbleDashSpeed;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 回転速度1
	/// </summary>
	float steeringSpeed1;

	/// <summary>
	/// 回転速度2
	/// </summary>
	float steeringSpeed2;

	/// <summary>
	/// 回転速度1になる速度
	/// </summary>
	float startSteeringSpeed;

	/// <summary>
	/// 回転速度2になる速度
	/// </summary>
	float endSteeringSpeed;

	/// <summary>
	/// 制御不能速度
	/// </summary>
	float outOfControlSpeed;

	/// <summary>
	/// 走行復帰速度
	/// </summary>
	float checkDashSpeed;

	/// <summary>
	/// 走行復帰時間
	/// </summary>
	float checkDashTime;

} PlayerParamDropDash;

typedef struct
{
	/// <summary>
	/// 開始落下速度
	/// </summary>
	float startSpeed;

	/// <summary>
	/// ジャンプ倍率　１段目
	/// </summary>
	float jumpRate1;

	/// <summary>
	/// ジャンプ倍率　2段目
	/// </summary>
	float jumpRate2;

	/// <summary>
	/// ジャンプ倍率　3段目
	/// </summary>
	float jumpRate3;

	/// <summary>
	/// ジャンプ不能時間
	/// </summary>
	float inoperableTime;

} PlayerParamBounceJump;

typedef struct
{
	/// <summary>
	/// ダッシュ速度　基本値
	/// </summary>
	float dashSpeed;

	/// <summary>
	/// ダッシュ速度　最大値
	/// </summary>
	float dashSpeedMax;

	/// <summary>
	/// 移動速度　基本値
	/// </summary>
	float speed;

	/// <summary>
	/// 移動速度　最大値
	/// </summary>
	float speedMax;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

} PlayerParamLightDash;

typedef struct
{
	/// <summary>
	/// 時間
	/// </summary>
	float time;

	/// <summary>
	/// 最低速度
	/// </summary>
	float minSpeed;

	/// <summary>
	/// 減速度
	/// </summary>
	float deceleForce;

} PlayerParamSpinDash;

typedef struct
{
	/// <summary>
	/// 初速
	/// </summary>
	float initialSpeed;

	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// 加速度
	/// </summary>
	PlayerParamSpeedAcceleData accele;

	/// <summary>
	/// 減速度
	/// </summary>
	PlayerParamSpeedAcceleData decele;

	/// <summary>
	/// 基本旋回力
	/// </summary>
	float baseRotateForce;

	/// <summary>
	/// 旋回中速度
	/// </summary>
	float minTurnSpeed;

	/// <summary>
	/// 旋回減速/開始角度
	/// </summary>
	float turnDeceleAngleMin;

	/// <summary>
	/// 旋回減速/最大角度
	/// </summary>
	float turnDeceleAngleMax;

} PlayerParamSpinBoostSpeed;

enum AirAccelMode : int8_t
{
	Alawys = 0,
	AirAccelMode_None = 1,
	Speed = 2,
};

typedef struct
{
	/// <summary>
	/// 強制走り時間
	/// </summary>
	float forceRunTime;

	/// <summary>
	/// 初速を維持する時間
	/// </summary>
	float initialRunTime;

	/// <summary>
	/// 通常速度
	/// </summary>
	PlayerParamSpinBoostSpeed speedBall;

	/// <summary>
	/// ブースト速度
	/// </summary>
	PlayerParamSpinBoostSpeed speedBoost;

	/// <summary>
	/// ニュートラル時最小減速度
	/// </summary>
	PlayerParamSpeedAcceleData2 deceleNeutralMin;

	/// <summary>
	/// ニュートラル時最大減速度
	/// </summary>
	PlayerParamSpeedAcceleData2 deceleNeutralMax;

	/// <summary>
	/// 重力サイズ
	/// </summary>
	float gravitySize;

	/// <summary>
	/// 空中/重力開始時間
	/// </summary>
	float gravityBeginTime;

	/// <summary>
	/// 空中/重力最大化時間
	/// </summary>
	float gravityMaxTime;

	/// <summary>
	/// 空中/最小重力サイズ
	/// </summary>
	float gravitySizeMinInAir;

	/// <summary>
	/// 空中/最大重力サイズ
	/// </summary>
	float gravitySizeMaxInAir;

	/// <summary>
	/// 斜面加速度
	/// </summary>
	float maxGravityAccele;

	/// <summary>
	/// 斜面減速度
	/// </summary>
	float maxGravityDecele;

	/// <summary>
	/// スピン状態のまま空中を移動できる時間
	/// </summary>
	float inAirTime;

	/// <summary>
	/// スピンブーストが終了してころころ移動になる速度
	/// </summary>
	float spinBoostEndSpeed;

	/// <summary>
	/// 飛び出し挙動になる角度
	/// </summary>
	float jumpOutAngle;

	/// <summary>
	/// 飛び出し挙動になる速度
	/// </summary>
	float jumpOutSpeed;

	/// <summary>
	/// 丘で飛び出すか
	/// </summary>
	bool humpJumpOut;

	/// <summary>
	/// 空中加速動作
	/// </summary>
	AirAccelMode airAccelMode;

	/// <summary>
	/// 空中加速が可能になる速度の閾値
	/// </summary>
	float airAccelVertSpeedThreshold;

	/// <summary>
	/// チャージ中回頭速度
	/// </summary>
	float chargeRotateForce;

	/// <summary>
	/// チャージ中回頭速度が0になる角度
	/// </summary>
	float chargeRotateForceMinAngle;

	/// <summary>
	/// チャージ中回頭速度が最大になる角度
	/// </summary>
	float chargeRotateForceMaxAngle;

	/// <summary>
	/// チャージ時のカメラシェイク名
	/// </summary>
	cstring cameraShakeName;

} PlayerParamSpinBoost;

typedef struct
{
	/// <summary>
	/// 通常最高速度
	/// </summary>
	float maxSpeed;

	/// <summary>
	/// ダッシュ最高速度
	/// </summary>
	float maxDashSpeed;

	/// <summary>
	/// 通常加速度
	/// </summary>
	float accel;

	/// <summary>
	/// ダッシュ加速度
	/// </summary>
	float dashAccel;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake;

	/// <summary>
	/// 回転速度　速度０の時
	/// </summary>
	float minRotateSpeed;

	/// <summary>
	/// 回転速度　ダッシュ最高速の時
	/// </summary>
	float maxRotateSpeed;

	/// <summary>
	/// 攻撃を受けた時の吹き飛び時間
	/// </summary>
	float blowOffTime;

	/// <summary>
	/// 攻撃を受けた時の角度
	/// </summary>
	float blowOffAngle;

	/// <summary>
	/// 減速度 ターン時
	/// </summary>
	float turnBrake;

	/// <summary>
	/// ターン時の回転速度
	/// </summary>
	float turnRotateSpeed;

	/// <summary>
	/// クイックターン入力と見なす角度
	/// </summary>
	float quickTurnThresholdAngle;

	/// <summary>
	/// クイックターンに移行する速度
	/// </summary>
	float quickTurnStartSpeed;

	/// <summary>
	/// クイックターン時の減速度
	/// </summary>
	float quickTurnBrake;

	/// <summary>
	/// クイックターン時の回転速度
	/// </summary>
	float quickTurnRotateSpeed;

	/// <summary>
	/// コンボ受付時間
	/// </summary>
	float comboTime;

} PlayerParamFly;

typedef struct
{
	/// <summary>
	/// 最高速度
	/// </summary>
	float maxSpeed1D;

	/// <summary>
	/// 加速度
	/// </summary>
	float accel1D;

	/// <summary>
	/// 減速度
	/// </summary>
	float brake1D;

	/// <summary>
	/// コース復帰加速度
	/// </summary>
	float fixAccel1D;

	/// <summary>
	/// コース復帰速度
	/// </summary>
	float fixSpeed1D;

	/// <summary>
	/// コース復帰加速度 高速
	/// </summary>
	float fixAccelQuick;

	/// <summary>
	/// コース復帰速度 高速
	/// </summary>
	float fixSpeedQuick;

	/// <summary>
	/// 向き変更速度
	/// </summary>
	float rotateSpeed1D;

	/// <summary>
	/// 最高速度2D
	/// </summary>
	float maxSpeed2D;

	/// <summary>
	/// 加速度2D
	/// </summary>
	float accel2D;

	/// <summary>
	/// 減速度2D
	/// </summary>
	float brake2D;

	/// <summary>
	/// コース復帰速度2D
	/// </summary>
	float fixSpeed2D;

	/// <summary>
	/// 向き変更速度2D
	/// </summary>
	float rotateSpeed2D;

} PlayerParamLimitedFly;

typedef struct
{
	/// <summary>
	/// 低重力モード/重力スケール
	/// </summary>
	float lowGravityScale;

	/// <summary>
	/// タイムスケールモード/タイムスケール
	/// </summary>
	float timeScale;

	/// <summary>
	/// 最高速チャレンジモード/最大加速力
	/// </summary>
	float accelForce;

	/// <summary>
	/// 最高速チャレンジモード/躍度
	/// </summary>
	float jerk;

	/// <summary>
	/// 最高速チャレンジモード/最高速扱いとする速度
	/// </summary>
	float maxSpeedThreshold;

	/// <summary>
	/// 最高速チャレンジモード/ゲージ回復速度
	/// </summary>
	float recoveryRate;

	/// <summary>
	/// アニマル運搬モード/最低移動速度
	/// </summary>
	float animalMinSpeed;

	/// <summary>
	/// アニマル運搬モード/最高移動速度
	/// </summary>
	float animalMaxSpeed;

	/// <summary>
	/// アニマル運搬モード/初速度
	/// </summary>
	float animalInitialSpeed;

	/// <summary>
	/// アニマル運搬モード/旋回時最低移動速度
	/// </summary>
	float animalMinTurnSpeed;

	/// <summary>
	/// アニマル運搬モード/ジャンプ力
	/// </summary>
	float animalJumpForce;

	/// <summary>
	/// アニマル運搬モード/重力サイズ
	/// </summary>
	float animalGravitySize;

} PlayerParamCyberMode;

typedef struct
{
	ModePackage modePackage;

	/// <summary>
	/// 嵐浮遊挙動
	/// </summary>
	PlayerParamStorm storm;

	/// <summary>
	/// 雲ジャンプ
	/// </summary>
	PlayerParamCloudJump cloudJump;

	/// <summary>
	/// アクアボール内挙動
	/// </summary>
	PlayerParamAquaBall aquaball;

	/// <summary>
	/// スライダー
	/// </summary>
	PlayerParamSlider slider;

	/// <summary>
	/// エアトリック
	/// </summary>
	PlayerParamAirTrick airtrick;

	/// <summary>
	/// ドリフト
	/// </summary>
	PlayerParamDrift drift;

	/// <summary>
	/// 空中ドリフト
	/// </summary>
	PlayerParamDriftAir driftair;

	/// <summary>
	/// ドリフトダッシュ
	/// </summary>
	PlayerParamDriftDash driftDash;

	/// <summary>
	/// 板乗り
	/// </summary>
	PlayerParamBoarding boarding;

	/// <summary>
	/// ドロップダッシュ
	/// </summary>
	PlayerParamDropDash dropDash;

	/// <summary>
	/// バウンドジャンプ
	/// </summary>
	PlayerParamBounceJump bounceJump;

	/// <summary>
	/// ライトダッシュ
	/// </summary>
	PlayerParamLightDash lightDash;

	/// <summary>
	/// スピンダッシュ
	/// </summary>
	PlayerParamSpinDash spindash;

	/// <summary>
	/// スピンブースト
	/// </summary>
	PlayerParamSpinBoost spinBoost;

	/// <summary>
	/// スパソニ飛行
	/// </summary>
	PlayerParamFly fly;

	/// <summary>
	/// スパソニ飛行 範囲制限時
	/// </summary>
	PlayerParamLimitedFly limitedfly;

	/// <summary>
	/// 電脳固有モード
	/// </summary>
	PlayerParamCyberMode cyberMode;

} ModePackageSonic;

typedef struct
{
	/// <summary>
	/// 速度
	/// </summary>
	PlayerParamSpeed speed;

	/// <summary>
	/// ジャンプ
	/// </summary>
	PlayerParamJump jump;

	/// <summary>
	/// ジャンプ中速度
	/// </summary>
	PlayerParamJumpSpeed jumpSpeed;

	/// <summary>
	/// 2段ジャンプ
	/// </summary>
	PlayerParamDoubleJump doubleJump;

	/// <summary>
	/// ブースト
	/// </summary>
	PlayerParamBoost boost;

	/// <summary>
	/// エアブースト
	/// </summary>
	PlayerParamAirBoost airboost;

} WaterModePackage;

typedef struct
{
	/// <summary>
	/// 共通
	/// </summary>
	CommonPackageSonic common;

	/// <summary>
	/// 通常
	/// </summary>
	ModePackageSonic forwardView;

	/// <summary>
	/// 水中
	/// </summary>
	WaterModePackage water;

	/// <summary>
	/// 電脳空間/FV
	/// </summary>
	ModePackageSonic cyberspace;

	/// <summary>
	/// 電脳空間/SV
	/// </summary>
	ModePackageSonic cyberspaceSV;

} SonicParameters;