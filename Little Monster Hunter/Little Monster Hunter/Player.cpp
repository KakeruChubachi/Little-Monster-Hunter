#include "Player.h"
#include<math.h>

Player::Player()
{
	mvloadModel = MV1LoadModel("Resource/character.mv1");
	attackModelHandle = MV1LoadModel("Resource/Great Sword Slash 2.mv1");
	animationHandle = MV1LoadModel("Resource/Great Sword Walk.mv1");
	drawSwordHandle = MV1LoadModel("Resource/Draw A Great Sword 2.mv1");
	drawSwordNum = MV1GetAnimNum(drawSwordHandle);
	drawSwordAttach = MV1AttachAnim(mvloadModel, 0, drawSwordHandle);
	attackNum =  MV1AttachAnim(mvloadModel, 0, attackModelHandle);
	modelPos = VGet(0, 0, 0);
	MV1SetPosition(mvloadModel, modelPos);
	animNum = MV1GetAnimNum(animationHandle);
	attachNum = MV1AttachAnim(mvloadModel, 0, animationHandle);
	totalTime = MV1GetAttachAnimTotalTime(mvloadModel, attachNum);
	attackTime = MV1GetAttachAnimTotalTime(mvloadModel, attackNum);
	drawTime = MV1GetAttachAnimTotalTime(mvloadModel, drawSwordAttach);
	currentTime = 0.0f;
	yRadius = 0.0f;
	judgePos = VGet(0, 0, 0);
	attackAnimNum = MV1GetAnimNum(attackModelHandle);
	MV1SetAttachAnimBlendRate(mvloadModel, attachNum, 1.0f);
	MV1SetAttachAnimBlendRate(mvloadModel, attackNum, 0.0f);
	MV1SetAttachAnimBlendRate(mvloadModel, drawSwordAttach, 0.0f);
	frameNum = MV1SearchFrame(mvloadModel, "mixamorig:RightHand");
}

Player::~Player()
{
	MV1DeleteModel(mvloadModel);
	MV1DeleteModel(animationHandle);
	MV1DeleteModel(attackModelHandle);
	MV1DeleteModel(drawSwordHandle);
}

void Player::Update(float deltaTime)
{
	if(!isAttacking && !isAnimating)
	{
		Move(VGet(0, 0, 0), deltaTime);
	}
	Attack(deltaTime);
	float attackAnimTime = attackProgress * attackTime;
	MV1SetAttachAnimTime(mvloadModel, attackNum, attackAnimTime);
	MV1SetAttachAnimTime(mvloadModel, attachNum, currentTime);
	MV1SetRotationXYZ(mvloadModel, VGet(0, yRadius + DX_PI_F, 0));
	judgePos = MV1GetFramePosition(mvloadModel, frameNum);
	MATRIX handLine = MV1GetFrameLocalWorldMatrix(mvloadModel, frameNum);
	VECTOR worldPos = VTransform(localBladeTip, handLine);
	bladeTip = worldPos;
	if (CheckHitKey(KEY_INPUT_R) && !isAnimating && AnimatingKeyNotPressed)
	{
		isAnimating = true;
		animProgress = 0.0f;
		MV1SetAttachAnimBlendRate(mvloadModel, drawSwordAttach, 1.0f);
		MV1SetAttachAnimBlendRate(mvloadModel, attachNum, 0.0f);
	}
	if(isAnimating)
	{
		animProgress += 0.5f * deltaTime;
		float drawSwordTime = animProgress * drawTime;
		MV1SetAttachAnimTime(mvloadModel, drawSwordAttach, drawSwordTime);
		if (animProgress >= 1.0)
		{
			isAnimating = false;
			MV1SetAttachAnimBlendRate(mvloadModel, drawSwordAttach, 0.0f);
			MV1SetAttachAnimBlendRate(mvloadModel, attachNum, 1.0f);
			animProgress = 0.0f;
		}
	}
	AnimatingKeyNotPressed = !CheckHitKey(KEY_INPUT_R);
}

void Player::Draw()
{
	MV1DrawModel(mvloadModel);
	if (IsDecisionValid())
	{
		DrawCapsule3D(judgePos, bladeTip,capsuleRad, 16, GetColor(0, 255, 255), GetColor(255, 255, 255), FALSE);
	}
	DrawFormatString(10, 30, GetColor(255, 255, 255), "AttackProgress:%.2f", attackProgress);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "AnimNum:%d", drawSwordNum);
	DrawFormatString(10, 90, GetColor(255, 255,255), "AnimAttach:%d", drawSwordAttach);
	DrawFormatString(10, 110, GetColor(255, 255, 255), "TotalTime:%.2f", drawTime);
}

void Player::Move(VECTOR move,float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		move.z += moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		move.z -= moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		move.x -= moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		move.x += moveSpeed;
	}
	if ((move.x != 0) || (move.z != 0))
	{
		VECTOR direction = VNorm(move);
		move = VScale(direction, moveSpeed);
		currentTime += 26.4f * deltaTime;
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
	modelPos = VAdd(modelPos, VScale(move, deltaTime));
	MV1SetPosition(mvloadModel, modelPos);
}

void Player::Attack(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE) && !isAttacking && AttackKeyNotPressed && !isAnimating)
	{
		isAttacking = true;
		MV1SetAttachAnimBlendRate(mvloadModel, attackNum, 1.0f);
		MV1SetAttachAnimBlendRate(mvloadModel, attachNum, 0.0f);
	}
	if (isAttacking)
	{
		attackProgress += 0.5f * deltaTime;
		if (attackProgress >= 1.0f)
		{
			isAttacking = false;
			MV1SetAttachAnimBlendRate(mvloadModel, attackNum, 0.0f);
			MV1SetAttachAnimBlendRate(mvloadModel, attachNum, 1.0f);
			attackProgress = 0.0f;
		}
	}
	
	AttackKeyNotPressed = !CheckHitKey(KEY_INPUT_SPACE);
}

