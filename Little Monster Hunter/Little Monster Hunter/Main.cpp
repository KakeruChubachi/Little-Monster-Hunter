#include "DxLib.h"
#include "GridLine.h"
#include"Player.h"
#include"Target.h"
#include <math.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	DxLib_Init();

	// 3Dï`âÊÇÃê›íË
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

	// ÉÅÉCÉìÉãÅ[Év
	while (ProcessMessage() == 0)
	{
		player.Update();
		bool hitCheck = HitCheck_Sphere_Sphere(player.GetJudgePos(), player.GetJudgeRadius(), target.GetPos(), target.GetRadius());
		bool attack = player.IsAttacking();
		bool attackHit = hitCheck && attack;
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
		target.Draw(attackHit);
		target.TargetHpDraw();
		player.Draw();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}