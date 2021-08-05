#include "CDrawRotaGraphFReserve.h"
#include <DxLib.h>

CDrawRotaGraphFReserve::CDrawRotaGraphFReserve(int GHandle, double Priority, float x, float y, float angle, float extend)
	:IRenderReserve(GHandle, Priority), x(x), y(y), angle(angle), extend(extend)
{
}

void CDrawRotaGraphFReserve::Render() const
{
	DrawRotaGraphF(x, y, extend, angle, GHandle, TRUE);
}