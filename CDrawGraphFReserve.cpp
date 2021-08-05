#include "CDrawGraphFReserve.h"
#include <DxLib.h>

CDrawGraphFReserve::CDrawGraphFReserve(int GHandle, float x, float y, double Priority)
	:IRenderReserve(GHandle, Priority), x(x), y(y)
{
}

void CDrawGraphFReserve::Render() const
{
	DrawGraphF(x, y, GHandle, TRUE);
}
