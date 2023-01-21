#include "CDrawRectGraphwithBlendReserve.h"

#include <DxLib.h>

#include <cmath>

CDrawRectGraphWithBlendReserve::CDrawRectGraphWithBlendReserve(
    int GHandle, double Priority, float x, float y, int color, int Blendmode,
    int value, int width, int height)
    : IRenderReserve(GHandle, Priority, x, y, width, height),
      Blendmode(Blendmode),
      value(value),
      Color(color) {}

void CDrawRectGraphWithBlendReserve::Render() const {
  SetDrawBright((Color >> 16) & 0xFF, (Color >> 8) & 0xFF, (Color >> 0) & 0xFF);
  SetDrawBlendMode(Blendmode, value);
  DrawRectGraph(x, y, 0, 0, w, h, GHandle, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  SetDrawBright(0xFF, 0xFF, 0xFF);
}
