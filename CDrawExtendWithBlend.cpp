#include "CDrawExtendWithBlend.h"

#include <DxLib.h>

#include <cmath>

CDrawExtendWithBlendReserve::CDrawExtendWithBlendReserve(
    int GHandle, int Priority, double x1, double y1, double x2, double y2,
    int color, int Blendmode, int value)
    : IRenderReserve(GHandle, Priority, x1, y1, std::abs(x1 - x2),
                     std::abs(y1 - y2)),
      x1_(x1),
      y1_(y1),
      x2_(x2),
      y2_(y2),
      blendmode_(Blendmode),
      value_(value),
      color_(color) {}

void CDrawExtendWithBlendReserve::Render() const {
  SetDrawBright((color_ >> 16) & 0xFF, (color_ >> 8) & 0xFF, (color_ >> 0) & 0xFF);
  SetDrawBlendMode(blendmode_, value_);
  DrawExtendGraphF(float(x1_), float(y1_), float(x2_), float(y2_), graphic_handle_, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  SetDrawBright(0xFF, 0xFF, 0xFF);
}
