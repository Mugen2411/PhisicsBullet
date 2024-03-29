#include "CDrawGraphReserve.h"

#include <DxLib.h>

CDrawGraphReserve::CDrawGraphReserve(int GHandle, int x, int y, int Priority,
                                     int width, int height)
    : IRenderReserve(GHandle, Priority, x, y, width, height) {}

void CDrawGraphReserve::Render() const { DrawGraph((int)x_, (int)y_, graphic_handle_, TRUE); }
