#include "CDrawGraphReserve.h"
#include <DxLib.h>

CDrawGraphReserve::CDrawGraphReserve(int GHandle, int x, int y, double Priority, int width, int height)
	:IRenderReserve(GHandle, Priority, x, y, width, height)
{
}

void CDrawGraphReserve::Render() const
{
	DrawGraph(x, y, GHandle, TRUE);
}
