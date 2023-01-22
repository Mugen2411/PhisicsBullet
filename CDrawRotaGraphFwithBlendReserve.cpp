#include "CDrawRotaGraphFwithBlendReserve.h"

#include <DxLib.h>

#include <cmath>

CDrawRotaGraphFwithBlendReserve::CDrawRotaGraphFwithBlendReserve(
    int GHandle, int Priority, double x, double y, float angle, float extend,
    int color, int Blendmode, int value, int width, int height)
    : IRenderReserve(
          GHandle, Priority, x, y,
          width * cos(angle) * extend + height * sin(angle) * extend,
          width * sin(angle) * extend + height * cos(angle) * extend),
      angle_(angle),
      extend_(extend),
      blendmode_(Blendmode),
      value_(value),
      color_(color) {}

void CDrawRotaGraphFwithBlendReserve::Render() const {
  SetDrawBright((color_ >> 16) & 0xFF, (color_ >> 8) & 0xFF, (color_ >> 0) & 0xFF);
  SetDrawBlendMode(blendmode_, value_);
  DrawRotaGraphF(float(x_), float(y_), extend_, angle_, graphic_handle_, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  SetDrawBright(0xFF, 0xFF, 0xFF);
}
