#include "CDrawCircleGauge.h"

#include <DxLib.h>

CDrawCircleGaugeReserve::CDrawCircleGaugeReserve(int GHandle, int priority,
                                                 int x, int y, double ratio,
                                                 int width, int height)
    : IRenderReserve(GHandle, priority, x, y, width, height), ratio(ratio) {}

void CDrawCircleGaugeReserve::Render() const {
  DrawCircleGauge((int)x, (int)y, ratio * 100, GHandle);
}
