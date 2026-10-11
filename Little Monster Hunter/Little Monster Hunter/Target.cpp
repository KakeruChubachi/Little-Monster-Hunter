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
