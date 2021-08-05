#include "CDrawRotaGraphReserve.h"
#include <DxLib.h>

CDrawRotaGraphReserve::CDrawRotaGraphReserve(int GHandle, double Priority, int x, int y, float angle, float extend)
:IRenderReserve(GHandle, Priority), x(x), y(y), angle(angle), extend(extend)
{
}

void CDrawRotaGraphReserve::Render() const
{
	DrawRotaGraph(x, y, extend, angle, GHandle, TRUE);
}
