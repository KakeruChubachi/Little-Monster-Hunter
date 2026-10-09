#pragma once
#include "DxLib.h"
class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
	VECTOR GetPos();
	void Move(VECTOR move);
	void Attack();
	bool IsAttacking() const { return isAttacking; } // 攻撃中かどうかを取得する関数
private:
	// モデルのハンドル
	int mvloadModel;// モデルのハンドル
	int animationHandle;// アニメーションのハンドル
	int attachNum;// アニメーションの番号
	int animNum;// アニメーションの数

	// アニメーションの時間
	float totalTime;// アニメーションの総時間
	float currentTime;// アニメーションの現在の時間
	
	float yRadius;// モデルの回転角度
	
	VECTOR modelPos;// モデルの位置
	
	//PlyereStatus
	float moveSpeed = 10.0f; // 移動速度
	bool isAttacking = false; // 攻撃中かどうか
	float attackProgress = 0.0f; // 攻撃の進行度
};

