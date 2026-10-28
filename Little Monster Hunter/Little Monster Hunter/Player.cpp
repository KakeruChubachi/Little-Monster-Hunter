#include "Player.h"
#include<math.h>

Player::Player()
{
	/***アニメのデータを読み込む***/
	modelHandle = MV1LoadModel("Resource/character.mv1");
	drawAnim = LoadAnim("Resource/Draw A Great Sword 2.mv1");
	attackAnim = LoadAnim("Resource/Great Sword Slash 2.mv1");
	walkAnim = LoadAnim("Resource/Catwalk Walk Forward HighKnees.mv1");
	MV1SetPosition(modelHandle, modelPos);

	/***最初のブレンド率を設定する***/
	MV1SetAttachAnimBlendRate(modelHandle, walkAnim.attach, 1.0f);

	/***右手のフレーム番号を探す***/
	rightHandFrame = MV1SearchFrame(modelHandle, "mixamorig:RightHand");
	
	
}

Player::~Player()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(walkAnim.handle);
	MV1DeleteModel(attackAnim.handle);
	MV1DeleteModel(drawAnim.handle);
}

void Player::Update(float deltaTime)
{
	if(!isAttacking && !isDrawing)
	{
		Move(VGet(0, 0, 0), deltaTime);
	}
	Attack(deltaTime);
	float attackAnimTime = attackProgress * attackAnim.totalTime;
	MV1SetAttachAnimTime(modelHandle, attackAnim.attach, attackAnimTime);
	MV1SetAttachAnimTime(modelHandle, walkAnim.attach, walkTime);
	MV1SetRotationXYZ(modelHandle, VGet(0, yRadius + DX_PI_F, 0));
	judgePos = MV1GetFramePosition(modelHandle, rightHandFrame);
	MATRIX handLine = MV1GetFrameLocalWorldMatrix(modelHandle, rightHandFrame);
	VECTOR worldPos = VTransform(localBladeTip, handLine);
	bladeTip = worldPos;
	if (CheckHitKey(KEY_INPUT_R) && !isDrawing && drawKeyNotPressed && !isAttacking)
	{
		isDrawing = true;
		drawProgress = 0.0f;
		MV1SetAttachAnimBlendRate(modelHandle, drawAnim.attach, 1.0f);
		MV1SetAttachAnimBlendRate(modelHandle, walkAnim.attach, 0.0f);
	}
	if(isDrawing)
	{
		drawProgress += drawAnimSpeed * deltaTime;
		float drawSwordTime = drawProgress * drawAnim.totalTime;
		MV1SetAttachAnimTime(modelHandle, drawAnim.attach, drawSwordTime);
		if (drawProgress >= 1.0)
		{
			isDrawing = false;
			MV1SetAttachAnimBlendRate(modelHandle, drawAnim.attach, 0.0f);
			MV1SetAttachAnimBlendRate(modelHandle, walkAnim.attach, 1.0f);
			drawProgress = 0.0f;
		}
	}
	drawKeyNotPressed = !CheckHitKey(KEY_INPUT_R);
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
	if (IsDecisionValid())
	{
		DrawCapsule3D(judgePos, bladeTip,capsuleRadius, 16, GetColor(0, 255, 255), GetColor(255, 255, 255), FALSE);
	}
	DrawFormatString(10, 30, GetColor(255, 255, 255), "AttackProgress:%.2f", attackProgress);
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
		walkTime += walkAnimSpeed * deltaTime;
		if (walkTime > walkAnim.totalTime)
		{
			walkTime = 0.0f;
		}
		yRadius = atan2f(move.x, move.z);
	}
	else
	{
		walkTime = 0.0f;
	}
	modelPos = VAdd(modelPos, VScale(move, deltaTime));
	MV1SetPosition(modelHandle, modelPos);
}

void Player::Attack(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE) && !isAttacking && attackKeyNotPressed && !isDrawing)
	{
		isAttacking = true;
		MV1SetAttachAnimBlendRate(modelHandle, attackAnim.attach, 1.0f);
		MV1SetAttachAnimBlendRate(modelHandle, walkAnim.attach, 0.0f);
	}
	if (isAttacking)
	{
		attackProgress += attackAnimSpeed * deltaTime;
		if (attackProgress >= 1.0f)
		{
			isAttacking = false;
			MV1SetAttachAnimBlendRate(modelHandle, attackAnim.attach, 0.0f);
			MV1SetAttachAnimBlendRate(modelHandle, walkAnim.attach, 1.0f);
			attackProgress = 0.0f;
		}
	}
	
	attackKeyNotPressed = !CheckHitKey(KEY_INPUT_SPACE);
}

AnimData Player::LoadAnim(const char* path)
{
	AnimData data;
	data.handle = MV1LoadModel(path);
	data.attach = MV1AttachAnim(modelHandle, 0, data.handle);
	data.totalTime = MV1GetAttachAnimTotalTime(modelHandle, data.attach);
	MV1SetAttachAnimBlendRate(modelHandle,data.attach, 0.0f);
	return data;
}

