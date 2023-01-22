#include "CDrawRectGraphwithBlendReserve.h"

#include <DxLib.h>

#include <cmath>

CDrawRectGraphWithBlendReserve::CDrawRectGraphWithBlendReserve(
    int GHandle, int Priority, double x, double y, int color, int Blendmode,
    int value, int width, int height)
    : IRenderReserve(GHandle, Priority, x, y, width, height),
      blendmode_(Blendmode),
      value_(value),
      color_(color) {}

void CDrawRectGraphWithBlendReserve::Render() const {
  SetDrawBright((color_ >> 16) & 0xFF, (color_ >> 8) & 0xFF, (color_ >> 0) & 0xFF);
  SetDrawBlendMode(blendmode_, value_);
  DrawRectGraph(int(x_), int(y_), 0, 0, int(w_), int(h_), graphic_handle_, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  SetDrawBright(0xFF, 0xFF, 0xFF);
}
