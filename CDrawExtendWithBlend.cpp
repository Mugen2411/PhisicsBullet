#include "CDrawExtendWithBlend.h"

#include <DxLib.h>

#include <cmath>

CDrawExtendWithBlendReserve::CDrawExtendWithBlendReserve(
    int GHandle, int Priority, double x1, double y1, double x2, double y2,
    int color, int Blendmode, int value)
    : IRenderReserve(GHandle, Priority, x1, y1, std::abs(x1 - x2),
                     std::abs(y1 - y2)),
      x1(x1),
      y1(y1),
      x2(x2),
      y2(y2),
      Blendmode(Blendmode),
      value(value),
      Color(color) {}

void CDrawExtendWithBlendReserve::Render() const {
  SetDrawBright((Color >> 16) & 0xFF, (Color >> 8) & 0xFF, (Color >> 0) & 0xFF);
  SetDrawBlendMode(Blendmode, value);
  DrawExtendGraphF(float(x1), float(y1), float(x2), float(y2), GHandle, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  SetDrawBright(0xFF, 0xFF, 0xFF);
}
