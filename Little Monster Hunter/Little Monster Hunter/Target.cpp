#include "Target.h"
#include "DxLib.h"

void Target::Draw()
{
	DrawSphere3D(VGet(0, 100, 0), 50.0f, 16, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}
