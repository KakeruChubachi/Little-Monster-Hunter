#include "Target.h"

void Target::Draw(bool attack)
{
	int color = GetColor(255, 0, 0); // 通常時の色
	switch (attackState)
	{
	case TargetAttackState::Moving:
		color = GetColor(255, 0, 0); // 通常時の色
		break;
	case TargetAttackState::SetUp:
		color = GetColor(0, 0, 255); // 青色
		break;
	case TargetAttackState::Attacking:
		color = GetColor(255, 165, 0); // 橙色	
		break;
	default:
		break;
	}
	int attackColor = GetColor(255, 255, 0); // 攻撃時の色
	if (attack)
	{
		color = attackColor; // 攻撃時の色に変更
	}
	DrawSphere3D(targetPos, targetRadius, 16, color, GetColor(255, 255, 255), TRUE);
}

void Target::Update(float deltaTime, VECTOR playerPos)
{
	switch (attackState)
	{
	case TargetAttackState::Moving:
	{
		moveDirection = VSub(playerPos, targetPos); // プレイヤーの位置に向かう方向を計算
		moveDirection.y = 0; // y方向の移動を無効化
		float distance = VSize(moveDirection); // プレイヤーとの距離を計算
		if (distance < stopDistance)
		{
			attackState = TargetAttackState::SetUp;
			break;
		}
		moveDirection = VNorm(moveDirection); // 正規化して単位ベクトルにする
		VECTOR moveStep = VScale(moveDirection, moveSpeed * deltaTime); // 移動量を計算
		targetPos = VAdd(targetPos, moveStep); // ターゲットの位置を更新
		break;
	}
	case TargetAttackState::SetUp:
	{
		stateTime += deltaTime;
		if (stateTime >= attackStartTime)
		{
			attackState = TargetAttackState::Attacking;
			stateTime = 0.0f; // 攻撃準備時間をリセット
		}
		break;
	}
	case TargetAttackState::Attacking:
	{

		stateTime += deltaTime;
		if(stateTime >= attackDuration)
		{
			attackState = TargetAttackState::Moving;
			stateTime = 0.0f; // 攻撃時間をリセット
		}
		break;

	}
	}
}

void Target::TakeDamage(float damage)
{
	if(!isHitThisAttack) //まだヒットしていない場合のみ
	{
		targetHp -= damage;
		if (targetHp < 0)
		{
			targetHp = 0; // HPが0未満にならないようにする
		}
		isHitThisAttack = true; // ヒットフラグを立てる
	}
}
