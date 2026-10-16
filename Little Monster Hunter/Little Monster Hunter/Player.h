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
	bool IsDecisionValid() const { return (isAttacking && (attackProgress >= attackStartValue) && (attackProgress <= attackEndValue)); }
	VECTOR GetJudgePos() const { return judgePos; } // 攻撃判定の位置を取得する関数
	float GetJudgeRadius() const { return judgeRadius; } // 攻撃判定の半径を取得する関数
private:
	// モデルのハンドル
	int mvloadModel;// モデルのハンドル
	int animationHandle;// アニメーションのハンドル
	int attachNum;// アニメーションの番号
	int animNum;// アニメーションの数
	int attackAnimNum;// 攻撃アニメーションの数
	int attackModelHandle;// 攻撃アニメーションのハンドル
	int attackNum;// 攻撃アニメーションの番号

	// アニメーションの時間
	float totalTime;// アニメーションの総時間
	float currentTime;// アニメーションの現在の時間
	float attackTime;// 攻撃アニメーションの時間
	
	float yRadius;// モデルの回転角度
	
	VECTOR modelPos;// モデルの位置

	int frameNum;
	VECTOR ballPosition = VGet(100, 0, 0);
	VECTOR bladeTip = VGet(107, 79, 14);
	
	//PlyereStatus
	float moveSpeed = 1000.0f; // 移動速度
	bool isAttacking = false; // 攻撃中かどうか
	bool AttackKeyNotPressed = true; // 攻撃キーが押されていないかどうか
	float attackProgress = 0.0f; // 攻撃の進行度
	VECTOR judgePos = VGet(0, 0, 0); // 攻撃判定の位置
	float judgeRadius = 20.0f; // 攻撃判定の半径
	float  attackStartValue = 0.48f; //攻撃の開始値
	float attackEndValue = 0.62f; //攻撃の終わり値
};

