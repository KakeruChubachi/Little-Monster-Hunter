#include "Player.h"
#include<math.h>

Player::Player()
{
	mvloadModel = MV1LoadModel("Resource/character.mv1");
	animationHandle = MV1LoadModel("Resource/Catwalk Walk Forward HighKnees.mv1");
	modelPos = VGet(0, 0, 0);
	MV1SetPosition(mvloadModel, modelPos);
	animNum = MV1GetAnimNum(animationHandle);
	attachNum = MV1AttachAnim(mvloadModel, 0, animationHandle);
	totalTime = MV1GetAttachAnimTotalTime(mvloadModel, attachNum);
	currentTime = 0.0f;
	yRadius = 0.0f;
}

Player::~Player()
{
	MV1DeleteModel(mvloadModel);
	MV1DeleteModel(animationHandle);
}

void Player::Update()
{
	VECTOR move = VGet(0, 0, 0);
	if (CheckHitKey(KEY_INPUT_W))
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
	if ((move.x != 0) || (move.z != 0))
	{
		currentTime += 0.16f;
		if (currentTime > totalTime)
		{
			currentTime = 0.0f;
		}
		yRadius = atan2f(move.x, move.z);
	}
	else
	{
		currentTime = 0.0f;
	}
	modelPos.x += move.x;
	modelPos.z += move.z;
	MV1SetPosition(mvloadModel, modelPos);
	MV1SetAttachAnimTime(mvloadModel, attachNum, currentTime);
	MV1SetRotationXYZ(mvloadModel, VGet(0, yRadius + DX_PI_F, 0));
}

void Player::Draw()
{
	MV1DrawModel(mvloadModel);
}
