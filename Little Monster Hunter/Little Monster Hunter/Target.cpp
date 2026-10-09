#include "Target.h"
#include "DxLib.h"

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
	DrawSphere3D(VGet(0, 0, 0), 50.0f, 16, color, GetColor(255, 255, 255), TRUE);
}
