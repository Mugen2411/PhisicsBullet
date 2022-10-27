#include "CDrawRotaGraphFReserve.h"
#include <DxLib.h>
#include <cmath>

CDrawRotaGraphFReserve::CDrawRotaGraphFReserve(int GHandle, double Priority, float x, float y, float angle, float extend, int width, int height)
	:IRenderReserve(GHandle, Priority, x, y, width*cos(angle)*extend+height*sin(angle)*extend, width* sin(angle)* extend + height * cos(angle) * extend), angle(angle), extend(extend)
{
}

void CDrawRotaGraphFReserve::Render() const
{
	DrawRotaGraphF(x, y, extend, angle, GHandle, TRUE);
}