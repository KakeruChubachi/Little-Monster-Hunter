#include "Player.h"
#include<math.h>

Player::Player()
{
	/***モデルとアニメのデータを読み込む***/
	modelHandle = MV1LoadModel("Resource/character.mv1");
	drawAnim = LoadAnim("Resource/Draw A Great Sword 2.mv1");
	attackAnim = LoadAnim("Resource/Great Sword Slash 2.mv1");
	walkAnim = LoadAnim("Resource/Walking_1.mv1");
	drawWalkAnim = LoadAnim("Resource/Great_Sword_Walk_3.mv1");
	sheathAnim = LoadAnim("Resource/Sheath A Great Sword 1.mv1");
	MV1SetPosition(modelHandle, modelPos);

	/***最初のブレンド率を設定する***/
	MV1SetAttachAnimBlendRate(modelHandle, walkAnim.attach, 1.0f);

	/***右手のフレーム番号を探す***/
	rightHandFrame = MV1SearchFrame(modelHandle, "mixamorig:RightHand");

	meshCount = MV1GetMeshNum(modelHandle);
	swordMesh = 1;
	MV1SetMeshVisible(modelHandle, swordMesh, FALSE);
}

Player::~Player()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(walkAnim.handle);
	MV1DeleteModel(attackAnim.handle);
	MV1DeleteModel(drawAnim.handle);
	MV1DeleteModel(drawWalkAnim.handle);
	MV1DeleteModel(sheathAnim.handle);
}

void Player::Update(float deltaTime)
{
	if(!isAttacking && !isDrawing && !isSheathing)
	{
		Move(VGet(0, 0, 0), deltaTime);
	}
	Attack(deltaTime);
	UpdateDraw(deltaTime);
	UpdateSheath(deltaTime);
	ApplyAnimTimes();
	ApplyRotation();
	UpdateBladeTip();
}


void Player::Draw()
{
	
	MV1DrawModel(modelHandle);
	if (IsDecisionValid())
	{
		DrawCapsule3D(judgePos, bladeTip,capsuleRadius, 16, GetColor(0, 255, 255), GetColor(255, 255, 255), FALSE);
	}
	DrawFormatString(10, 30, GetColor(255, 255, 255), "AttackProgress:%.2f", attackProgress);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "MeshNum: %d", meshCount);
}

void Player::Move(VECTOR move,float deltaTime)
{
	float moveSpeed;
	float walkSpeed;
	if (isDrawn)
	{
		moveSpeed = drawMoveSpeed;
		walkSpeed = drawWalkAnimSpeed;
	}
	else
	{
		moveSpeed = normalMoveSpeed;
		walkSpeed = walkAnimSpeed;
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		move.z += normalMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		move.z -= normalMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		move.x -= normalMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		move.x += normalMoveSpeed;
	}
	if ((move.x != 0) || (move.z != 0))
	{
		VECTOR direction = VNorm(move);
		move = VScale(direction, moveSpeed);
		walkTime += walkSpeed * deltaTime;
		if (walkTime > GetWalkType().totalTime)
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
	if (CheckHitKey(KEY_INPUT_SPACE) && !isAttacking && attackKeyNotPressed && !isDrawing && isDrawn)
	{
		isAttacking = true;
		MV1SetAttachAnimBlendRate(modelHandle, attackAnim.attach, 1.0f);
		MV1SetAttachAnimBlendRate(modelHandle, GetWalkType().attach, 0.0f);
	}
	if (isAttacking)
	{
		attackProgress += attackAnimSpeed * deltaTime;
		if (attackProgress >= 1.0f)
		{
			isAttacking = false;
			MV1SetAttachAnimBlendRate(modelHandle, attackAnim.attach, 0.0f);
			MV1SetAttachAnimBlendRate(modelHandle, GetWalkType().attach, 1.0f);
			attackProgress = 0.0f;
		}
	}
	
	attackKeyNotPressed = !CheckHitKey(KEY_INPUT_SPACE);
}

AnimData Player::GetWalkType() const
{
	if (isDrawn)
	{
		return drawWalkAnim;
	}
	else
	{
		return walkAnim;
	}
	
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

void Player::UpdateDraw(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_R) && !isDrawing && drawKeyNotPressed && !isAttacking && !isDrawn)
	{
		isDrawing = true;
		MV1SetMeshVisible(modelHandle, swordMesh, TRUE);
		drawProgress = 0.0f;
		MV1SetAttachAnimBlendRate(modelHandle, drawAnim.attach, 1.0f);
		MV1SetAttachAnimBlendRate(modelHandle, GetWalkType().attach, 0.0f);
	}
	if (isDrawing)
	{
		drawProgress += drawAnimSpeed * deltaTime;
		float drawSwordTime = drawProgress * drawAnim.totalTime;
		MV1SetAttachAnimTime(modelHandle, drawAnim.attach, drawSwordTime);
		if (drawProgress >= 1.0)
		{
			isDrawing = false;
			isDrawn = true;
			MV1SetAttachAnimBlendRate(modelHandle, drawAnim.attach, 0.0f);
			MV1SetAttachAnimBlendRate(modelHandle, GetWalkType().attach, 1.0f);
			drawProgress = 0.0f;
		}
	}
	drawKeyNotPressed = !CheckHitKey(KEY_INPUT_R);
}

void Player::UpdateSheath(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_F) && !isSheathing && sheathKeyNotPressed && !isAttacking && isDrawn)
	{
		isSheathing = true;
		sheathProgress = 0.0f;
		MV1SetAttachAnimBlendRate(modelHandle, sheathAnim.attach, 1.0f);
		MV1SetAttachAnimBlendRate(modelHandle, GetWalkType().attach, 0.0f);
	}
	if (isSheathing)
	{
		sheathProgress += sheathAnimSpeed * deltaTime;
		float sheathSwordTime = sheathProgress * sheathAnim.totalTime;
		MV1SetAttachAnimTime(modelHandle, sheathAnim.attach, sheathSwordTime);
		if (sheathProgress >= 1.0)
		{
			isSheathing = false;
			isDrawn = false;
			MV1SetMeshVisible(modelHandle, swordMesh, FALSE);
			MV1SetAttachAnimBlendRate(modelHandle, sheathAnim.attach, 0.0f);
			MV1SetAttachAnimBlendRate(modelHandle, GetWalkType().attach, 1.0f);
			sheathProgress = 0.0f;
		}
	}
	sheathKeyNotPressed = !CheckHitKey(KEY_INPUT_F);
}

void Player::ApplyAnimTimes()
{
	float attackAnimTime = attackProgress * attackAnim.totalTime;
	MV1SetAttachAnimTime(modelHandle, attackAnim.attach, attackAnimTime);
	MV1SetAttachAnimTime(modelHandle, GetWalkType().attach, walkTime);
}

void Player::ApplyRotation()
{
	MV1SetRotationXYZ(modelHandle, VGet(0, yRadius + DX_PI_F, 0));
}

void Player::UpdateBladeTip()
{
	judgePos = MV1GetFramePosition(modelHandle, rightHandFrame);
	MATRIX handLine = MV1GetFrameLocalWorldMatrix(modelHandle, rightHandFrame);
	VECTOR worldPos = VTransform(localBladeTip, handLine);
	bladeTip = worldPos;
}

