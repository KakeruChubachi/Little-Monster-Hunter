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
private:
	int mvloadModel;
	int animationHandle;
	int attachNum;
	int animNum;
	float totalTime;
	float currentTime;
	float yRadius;
	VECTOR modelPos;
};

