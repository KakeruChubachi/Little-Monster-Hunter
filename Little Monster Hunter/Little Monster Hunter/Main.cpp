#include "DxLib.h"
#include "GridLine.h"
#include"Player.h"
#include"Target.h"
#include <math.h>

enum class GameState
{
	Battle,
	Win,
	Lose
};
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	DxLib_Init();

	// 3D描画の設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	VECTOR cameraPos = VGet(0, 500, -1000);
	VECTOR cameraPoint = VGet(0, 0, 0);
	VECTOR offset = VGet(0, 500, -1000);
	VECTOR playerPos = VGet(0, 0, 0);
	
	GridLine gridLine;
	Player player;
	Target target;

	LONGLONG frontFrameTime = GetNowHiPerformanceCount(); // 前フレームの時間
	LONGLONG nowTime = GetNowHiPerformanceCount(); // 現在の時間
	float hitStopTime = 0.0f;//攻撃がヒットしたときに止める時間
	bool isBeforeHit = false;//前フレームでヒットしていたかどうか
	GameState gameState = GameState::Battle;
	bool hitCheck = false;
	bool attack = false;
	bool attackHit = false;

	// メインループ
	while (ProcessMessage() == 0)
	{
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - frontFrameTime) / 1000000.0f; // 前フレームからの経過時間
		frontFrameTime = nowTime;
		if(hitStopTime > 0.0f)
		{
			hitStopTime -= deltaTime;
			deltaTime = 0.0f;
		}
		else
		{
			hitStopTime = 0.0f;
		}
		if (gameState == GameState::Battle)
		{
			player.Update(deltaTime);
			playerPos = player.GetPos();
			hitCheck = HitCheck_Sphere_Capsule(target.GetPos(), target.GetRadius(), player.GetJudgePos(), player.GetWorldBladeTipPos(), player.GetCapsuleRad());
			attack = player.IsAttacking();
			attackHit = player.IshitActive() && hitCheck;
			if (attackHit && !isBeforeHit)
			{
				target.TakeDamage(10.0f);
				hitStopTime = 0.1f;
			}
			else if (!attack)
			{
				target.ResetHitFlag();
			}
			target.Update(deltaTime, playerPos);
			if (target.TargetIsAttacking())
			{
				VECTOR attackDirection = VSub(target.GetPos(), playerPos);
				attackDirection.y = 0;
				float attackDistance = VSize(attackDirection);
				float stopRange = 80;
				if (attackDistance <= stopRange)
				{
					player.TakeDamage(30);
				}
				DrawString(10, 150, "Attacking", GetColor(255, 255, 255));
			}
			else
			{
				player.PlayerResetHit();
			}
		}
		if (target.IsDead() && gameState == GameState::Battle)
		{
			gameState = GameState::Win;
		}
		if (player.IsDead() && gameState == GameState::Battle)
		{
			gameState = GameState::Lose;
		}
		
		cameraPoint = playerPos;
		cameraPos = VAdd(playerPos, offset);
		ClearDrawScreen();
		SetCameraPositionAndTarget_UpVecY(cameraPos,cameraPoint);
		gridLine.Draw();
		DrawFormatString(10, 10, GetColor(255, 255, 255), "Delta Time: %.6f seconds", deltaTime);
		if (gameState == GameState::Win)
		{
			DrawString(325, 10, "You Win", GetColor(255, 255, 0));//黄色
		}
		if (gameState == GameState::Lose)
		{
			DrawString(325, 10, "You Lose", GetColor(255, 0, 0));
		}
		target.Draw(attackHit);
		target.TargetHpDraw();
		player.Draw();
		ScreenFlip();
		isBeforeHit = attackHit;
	}
	DxLib_End();
	return 0;
}