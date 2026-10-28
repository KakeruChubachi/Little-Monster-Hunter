#pragma once
#include "DxLib.h"

/*アニメ1つ分のデータ(ファイルのハンドル、アタッチ番号、総時間)*/
struct AnimData
{
	int handle = -1;//アニメのファイルのハンドル
	int attach = -1;//アニメのアタッチ番号
	float totalTime = 0.0f;//アニメの総時間
};

class Player
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void Draw();
	VECTOR GetPos() { return modelPos; }
	void Move(VECTOR move,float deltaTime);
	void Attack(float deltaTime);
	bool IsAttacking() const { return isAttacking; } // 攻撃中かどうかを取得する関数
	bool IsDecisionValid() const { return (isAttacking && (attackProgress >= attackStartValue) && (attackProgress <= attackEndValue)); }
	VECTOR GetJudgePos() const { return judgePos; } // 攻撃判定の位置を取得する関数
	VECTOR GetWorldBladeTipPos() const { return bladeTip; }
	float GetCapsuleRad() const { return capsuleRad; }
private:
	/***アニメのファイルを読み込み、アタッチしてAnimDataで返す***/
	AnimData LoadAnim(const char* path);
	AnimData drawAnim;//抜刀アニメのデータ
	AnimData attackAnim;//攻撃アニメのデータ
	AnimData walkAnim;//歩行アニメのデータ
	// モデルのハンドル
	int mvloadModel;// モデルのハンドル
	
	// アニメーションの時間
	float currentTime = 0.0f;// 歩行アニメの現在の時間
	
	
	float yRadius = 0.0f;// モデルの回転角度
	
	VECTOR modelPos = VGet(0, 0, 0);// モデルの位置

	int frameNum;//右手のフレーム番号
	VECTOR localBladeTip = VGet(107, 79, 14);//手のフレームから見た剣先の位置
	VECTOR bladeTip = VGet(0, 0, 0);//剣先のワールド座標。毎フレーム更新
	float capsuleRad = 20;//剣の判定（カプセル）の半径

	float animProgress = 0.0f;//抜刀アニメの進行度（０から１）
	bool isAnimating = false;//抜刀アニメを再生中か
	bool AnimatingKeyNotPressed = true;//Rキーが押されてないか

	//PlayerStatus
	float moveSpeed = 1000.0f; // 移動速度
	bool isAttacking = false; // 攻撃中かどうか
	bool AttackKeyNotPressed = true; // 攻撃キーが押されていないかどうか
	float attackProgress = 0.0f; // 攻撃の進行度
	VECTOR judgePos = VGet(0, 0, 0); // 攻撃判定の位置
	float  attackStartValue = 0.48f; //判定が有効になる攻撃の進行度の範囲（０から１）
	float attackEndValue = 0.62f; //判定が有効になる攻撃の進行度の範囲（０から１）
};

