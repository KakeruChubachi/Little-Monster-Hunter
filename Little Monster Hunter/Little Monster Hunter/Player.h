#pragma once
#include "DxLib.h"
class Player
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void Draw();
	VECTOR GetPos();
	void Move(VECTOR move,float deltaTime);
	void Attack(float deltaTime);
	bool IsAttacking() const { return isAttacking; } // 攻撃中かどうかを取得する関数
	VECTOR GetJudgePos() const { return judgePos; } // 攻撃判定の位置を取得する関数
	float GetJudgeRadius() const { return judgeRadius; } // 攻撃判定の半径を取得する関数
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
	float moveSpeed = 1000.0f; // 移動速度
	bool isAttacking = false; // 攻撃中かどうか
	bool AttackKeyNotPressed = true; // 攻撃キーが押されていないかどうか
	float attackProgress = 0.0f; // 攻撃の進行度
	VECTOR judgePos = VGet(0, 0, 0); // 攻撃判定の位置
	float judgeRadius = 10.0f; // 攻撃判定の半径
};

