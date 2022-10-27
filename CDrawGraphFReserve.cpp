#include "CDrawGraphFReserve.h"
#include <DxLib.h>

CDrawGraphFReserve::CDrawGraphFReserve(int GHandle, float x, float y, double Priority, int width, int height)
	:IRenderReserve(GHandle, Priority, x, y, width, height)
{
}

void CDrawGraphFReserve::Render() const
{
	DrawGraphF(x, y, GHandle, TRUE);
}
