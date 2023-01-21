#include "CDrawGraphFReserve.h"

#include <DxLib.h>

CDrawGraphFReserve::CDrawGraphFReserve(int GHandle, double x, double y,
                                       int Priority, int width, int height)
    : IRenderReserve(GHandle, Priority, x, y, width, height) {}

void CDrawGraphFReserve::Render() const { DrawGraphF((float)x, (float)y, GHandle, TRUE); }
