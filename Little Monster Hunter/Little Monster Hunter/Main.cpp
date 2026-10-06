#include "DxLib.h"
#include "GridLine.h"
#include <math.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	DxLib_Init();

	// 3D•`‰æ‚ÌÝ’è
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	VECTOR cameraPos = VGet(0, 500, -1000);
	VECTOR cameraPoint = VGet(0, 0, 0);
	
	GridLine gridLine;

	int mvloadModel = MV1LoadModel("Resource/character.mv1");
	int animationHandle = MV1LoadModel("Resource/Catwalk Walk Forward HighKnees.mv1");
	VECTOR modelPos = VGet(0, 0, 0);
	MV1SetPosition(mvloadModel, modelPos);
	int animNum = MV1GetAnimNum(animationHandle);
	int attachNum = MV1AttachAnim(mvloadModel, 0, animationHandle);
	float totalTime = MV1GetAttachAnimTotalTime(mvloadModel, attachNum);
	float currentTime = 0.0f;
	int move = 0;
	float yRadius = 0.0f;

	// ƒƒCƒ“ƒ‹[ƒv
	while (ProcessMessage() == 0)
	{
		MV1SetAttachAnimTime(mvloadModel, attachNum, currentTime);
		currentTime += 0.16f;
		if(currentTime > totalTime)
		{
			currentTime = 0.0f;
		}
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
		if ((move.x != 0)||(move.z != 0))
		{
			yRadius = atan2f(move.x, move.z);
		}
		MV1SetRotationXYZ(mvloadModel, VGet(0, yRadius + DX_PI_F, 0));
		cameraPos = VAdd(cameraPos, move);
		cameraPoint = VAdd(cameraPoint, move);
		modelPos = VAdd(modelPos, move);
		MV1SetPosition(mvloadModel, modelPos);
		ClearDrawScreen();
		SetCameraPositionAndTarget_UpVecY(cameraPos,cameraPoint);
		gridLine.Draw();
		MV1DrawModel(mvloadModel);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "modelHnadle:%d", animNum);
		ScreenFlip();
	}
	MV1DeleteModel(mvloadModel);
	DxLib_End();
	return 0;
}