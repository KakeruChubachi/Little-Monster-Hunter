#include "DxLib.h"
#include "GridLine.h"
#include"Player.h"
#include"Target.h"
#include <math.h>

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

	// メインループ
	while (ProcessMessage() == 0)
	{
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - frontFrameTime) / 1000000.0f; // 前フレームからの経過時間
		frontFrameTime = nowTime;
		player.Update(deltaTime);
		bool hitCheck = HitCheck_Sphere_Capsule(target.GetPos(), target.GetRadius(), player.GetJudgePos(), player.GetWorldBladeTipPos(), player.GetCapsuleRad());
		bool attack = player.IsAttacking();
		bool attackHit = player.IsDecisionValid() && hitCheck;
		if(attackHit)
		{
			target.TakeDamage(10.0f);
		}
		else if(!attack)
		{
			target.ResetHitFlag();
		}
		playerPos = player.GetPos();
		cameraPoint = playerPos;
		cameraPos = VAdd(playerPos, offset);
		ClearDrawScreen();
		SetCameraPositionAndTarget_UpVecY(cameraPos,cameraPoint);
		gridLine.Draw();
		DrawFormatString(10, 10, GetColor(255, 255, 255), "Delta Time: %.6f seconds", deltaTime);
		target.Draw(attackHit);
		target.TargetHpDraw();
		player.Draw();
		ScreenFlip();
		//WaitTimer(10);
	}
	DxLib_End();
	return 0;
}