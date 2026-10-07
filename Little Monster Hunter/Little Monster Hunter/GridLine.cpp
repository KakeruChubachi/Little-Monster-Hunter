#include "GridLine.h"
#include "DxLib.h"

void GridLine::Draw()
{
	int maxLines = 2000; // グリッドの最大線数
	int minLines = -2000; // グリッドの最小線数
	DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0));
	for (int z = minLines; z <= maxLines; z += 100)
	{
		DrawLine3D(VGet(minLines, 0, z), VGet(maxLines, 0, z), GetColor(0, 255, 0));
	}
	for (int x = minLines; x <= maxLines; x += 100)
	{
		DrawLine3D(VGet(x, 0, minLines), VGet(x, 0, maxLines), GetColor(0, 0, 255));
	}
}
