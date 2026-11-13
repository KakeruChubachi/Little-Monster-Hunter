#pragma once
#include "DxLib.h"

enum class TargetAttackState
{
	Moving,
	SetUp,
	Attacking,
};

class Target
{
public:
	void Draw(bool attackHit);
	void Update(float deltaTime, VECTOR playerPos);
	void TargetAttack(float deltaTime, VECTOR playerPos);
	VECTOR GetPos() const { return targetPos; } // ターゲットの位置を取得する関数
	float GetRadius() const { return targetRadius; } // ターゲットの半径を取得する関数
	void TakeDamage(float damage);
	bool IsDead() const { return targetHp <= 0; } // ターゲットが死んでいるかどうかを取得する関数
	void ResetHitFlag() { isHitThisAttack = false; } // ヒットフラグをリセットする関数
	void TargetHpDraw() const { DrawFormatString(10, 50, GetColor(255, 255, 255), "Target HP: %.1f", targetHp); } // ターゲットのHPを描画する関数
private:
	VECTOR targetPos = VGet(0, 50, 100); // ターゲットの位置
	float targetRadius = 50.0f; // ターゲットの半径
	float targetHp = 100.0f; // ターゲットの体力
	bool isHitThisAttack = false; // 今回の攻撃でヒットしたかどうか
	float moveSpeed = 50.0f; // ターゲットの移動速度
	VECTOR moveDirection = VGet(0, 0, 0); // ターゲットの移動方向
	float stopDistance = 80.0f; // プレイヤーとの距離
	TargetAttackState attackState = TargetAttackState::Moving; // ターゲットの攻撃状態
	float stateTime = 0.0f; // 攻撃準備の時間
	float attackStartTime = 0.5f; // 攻撃開始までの時間
	float attackDuration = 0.5f; // 攻撃の持続時間
};

