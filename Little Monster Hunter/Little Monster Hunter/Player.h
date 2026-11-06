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
	bool IsAttacking() const { return isAttacking; } // 攻撃中かどうかを取得する関数
	bool IsDecisionValid() const { return (isAttacking && (attackProgress >= attackStartValue) && (attackProgress <= attackEndValue)); }
	VECTOR GetJudgePos() const { return judgePos; } // 攻撃判定の位置を取得する関数
	VECTOR GetWorldBladeTipPos() const { return bladeTip; }
	float GetCapsuleRad() const { return capsuleRadius; }
private:
	/*関数*/
	void Move(VECTOR move, float deltaTime);
	void Attack(float deltaTime);
	AnimData  GetWalkType() const;
	/*アニメのファイルを読み込み、アタッチしてAnimDataで返す*/
	AnimData LoadAnim(const char* path);
	void UpdateDraw(float deltaTime);//抜刀の開始、進行、終了
	void UpdateSheath(float deltaTime);//納刀の開始、進行、終了
	void ApplyAnimTimes();//攻撃と歩行のアニメの時間を設定
	void ApplyRotation();//回転を設定
	void UpdateBladeTip();//手の位置とワールドの剣先を更新

	/*リソース*/
	int modelHandle = -1;// モデルのハンドル
	AnimData drawAnim;//抜刀アニメのデータ
	AnimData attackAnim;//攻撃アニメのデータ
	AnimData walkAnim;//歩行アニメのデータ
	AnimData sheathAnim;//納刀アニメのデータ
	AnimData drawWalkAnim;//抜刀歩行アニメのデータ
	int rightHandFrame = -1;//右手のフレーム番号

	/*位置と向き*/
	float yRadius = 0.0f;// モデルの回転角度
	VECTOR modelPos = VGet(0, 0, 0);// モデルの位置

	/*アニメの再生の状態*/
	float walkTime = 0.0f;// 歩行アニメの現在の時間
	
	/*抜刀の状態*/
	float drawProgress = 0.0f;//抜刀アニメの進行度（０から１）
	bool isDrawing = false;//抜刀アニメを再生中か
	bool isDrawn = false;//抜刀しているか

	/*納刀の状態*/
	float sheathProgress = 0.0f;//納刀アニメの進行度（０から１）
	bool isSheathing = false;//納刀アニメを再生中か

	/*攻撃の状態*/
	bool isAttacking = false; // 攻撃中かどうか
	float attackProgress = 0.0f; // 攻撃の進行度
	VECTOR judgePos = VGet(0, 0, 0); // 攻撃判定の位置
	VECTOR bladeTip = VGet(0, 0, 0);//剣先のワールド座標。毎フレーム更新
	
	/*キー入力の状態*/
	bool drawKeyNotPressed = true;//Rキーが押されてないか
	bool sheathKeyNotPressed = true;//Fキーが押されてないか
	bool attackKeyNotPressed = true; // 攻撃キーが押されていないかどうか

	/*調整用の値*/
	VECTOR localBladeTip = VGet(107, 79, 14);//手のフレームから見た剣先の位置
	float capsuleRadius = 20.0f;//剣の判定（カプセル）の半径
	float normalMoveSpeed = 500.0f; // 移動速度
	float drawMoveSpeed = 250.0f;//抜刀時の移動速度
	float  attackStartValue = 0.48f; //判定が有効になり始める進行度（０から１）
	float attackEndValue = 0.62f; //判定が有効な最後の進行度（０から１）
	float walkAnimSpeed = 27.0f;//毎秒進める歩行アニメの速さ
	float drawWalkAnimSpeed = walkAnimSpeed;//毎秒進める抜刀歩行アニメの速さ
	float attackAnimSpeed = 0.5f;//攻撃アニメの進める速さ(1/秒数)(0.5なら全体で2秒)
	float drawAnimSpeed = 0.5f;//抜刀アニメの進める速さ(1/秒数)(0.5なら全体で2秒)
	float sheathAnimSpeed = 0.5f;//納刀アニメの進める速さ(1/秒数)(0.5なら全体で2秒)
	float Time = 0;
	int meshCount = 0;
	int swordMesh = -1;
};

