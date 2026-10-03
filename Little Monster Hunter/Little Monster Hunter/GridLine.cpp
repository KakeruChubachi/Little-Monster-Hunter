#include "GridLine.h"
#include "DxLib.h"

void GridLine::Draw()
{
	DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0));
	for (int z = -500; z <= 500; z += 100)
	{
		DrawLine3D(VGet(-500, 0, z), VGet(500, 0, z), GetColor(0, 255, 0));
	}
	for (int x = -500; x <= 500; x += 100)
	{
		DrawLine3D(VGet(x, 0, -500), VGet(x, 0, 500), GetColor(0, 0, 255));
	}
}
