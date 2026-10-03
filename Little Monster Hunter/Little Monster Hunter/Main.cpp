#include "DxLib.h"
#include "GridLine.h"

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

	int mvloadModel = MV1LoadModel("Resource/character.mv1");
	VECTOR modelPos = VGet(0, 0, 0);
	MV1SetPosition(mvloadModel, modelPos);

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
		gridLine.Draw();
		MV1DrawModel(mvloadModel);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "modelHnadle:%d", mvloadModel);
		ScreenFlip();
	}
	MV1DeleteModel(mvloadModel);
	DxLib_End();
	return 0;
}