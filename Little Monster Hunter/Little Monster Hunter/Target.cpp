#include "Target.h"

void Target::Draw(bool attack)
{
	int color = GetColor(255, 0, 0); // 通常時の色
	int attackColor = GetColor(255, 255, 0); // 攻撃時の色
	if (attack)
	{
		color = attackColor; // 攻撃時の色に変更
	}
	else
	{
		color = GetColor(255, 0, 0); // 通常時の色に戻す
	}
	DrawSphere3D(targetPos, targetRadius, 16, color, GetColor(255, 255, 255), TRUE);
}

void Target::Update(float deltaTime, VECTOR playerPos)
{
	moveDirection = VSub(playerPos, targetPos); // プレイヤーの位置に向かう方向を計算
	moveDirection.y = 0; // y方向の移動を無効化
	float distance = VSize(moveDirection); // プレイヤーとの距離を計算
	if (distance < stopDistance)
	{
		return; // プレイヤーとの距離が近すぎる場合は移動しない
	}
	moveDirection = VNorm(moveDirection); // 正規化して単位ベクトルにする
	VECTOR moveStep = VScale(moveDirection, moveSpeed * deltaTime); // 移動量を計算
	targetPos = VAdd(targetPos, moveStep); // ターゲットの位置を更新
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
