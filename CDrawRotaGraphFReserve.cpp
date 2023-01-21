#include "CDrawRotaGraphFReserve.h"

#include <DxLib.h>

#include <cmath>

CDrawRotaGraphFReserve::CDrawRotaGraphFReserve(int GHandle, int Priority,
                                               double x, double y, float angle,
                                               float extend, int width,
                                               int height)
    : IRenderReserve(
          GHandle, Priority, x, y,
          width * cos(angle) * extend + height * sin(angle) * extend,
          width * sin(angle) * extend + height * cos(angle) * extend),
      angle(angle),
      extend(extend) {}

void CDrawRotaGraphFReserve::Render() const {
  DrawRotaGraphF(float(x), float(y), extend, angle, GHandle, TRUE);
}