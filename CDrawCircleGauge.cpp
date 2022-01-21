#include "CDrawCircleGauge.h"
#include <DxLib.h>

CDrawCircleGaugeReserve::CDrawCircleGaugeReserve(int GHandle, double priority, int x, int y, double ratio)
	:IRenderReserve(GHandle, priority), x(x), y(y), ratio(ratio)
{
}

void CDrawCircleGaugeReserve::Render() const
{
	DrawCircleGauge(x, y, ratio * 100, GHandle);
}
