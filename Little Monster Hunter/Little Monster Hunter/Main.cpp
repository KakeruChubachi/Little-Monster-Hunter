#include "DxLib.h"
#include "GridLine.h"
#include"Player.h"
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
	
	GridLine gridLine;
	Player player;

	// ÉÅÉCÉìÉãÅ[Év
	while (ProcessMessage() == 0)
	{
		VECTOR move = VGet(0, 0, 0);
		if(CheckHitKey(KEY_INPUT_W))
		{
			move.z += 10;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			move.z -= 10;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			move.x -= 10;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			move.x += 10;
		}
		cameraPos = VAdd(cameraPos, move);
		cameraPoint = VAdd(cameraPoint, move);
		player.Update();
		ClearDrawScreen();
		SetCameraPositionAndTarget_UpVecY(cameraPos,cameraPoint);
		gridLine.Draw();
		player.Draw();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}