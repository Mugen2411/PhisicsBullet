#include "CDrawGraphReserve.h"
#include <DxLib.h>

CDrawGraphReserve::CDrawGraphReserve(int GHandle, int x, int y, double Priority)
	:IRenderReserve(GHandle, Priority), x(x), y(y)
{
}

void CDrawGraphReserve::Render() const
{
	DrawGraph(x, y, GHandle, TRUE);
}
