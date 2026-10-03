#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	DxLib_Init();

	// 3Dï`âÊÇÃê›íË
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	VECTOR cameraPos = VGet(0, 500, -1000);
	VECTOR cameraPoint = VGet(0, 0, 0);
	

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
		ClearDrawScreen();
		SetCameraPositionAndTarget_UpVecY(cameraPos,cameraPoint);
		DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0));
		for(int z = -500; z <= 500; z += 100)
		{
			DrawLine3D(VGet(-500, 0, z), VGet(500, 0, z), GetColor(0, 255, 0));
		}
		for(int x = -500; x <= 500; x += 100)
		{
			DrawLine3D(VGet(x, 0, -500), VGet(x, 0, 500), GetColor(0, 0, 255));
		}
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}