#include "CDrawRotaGraphReserve.h"

#include <DxLib.h>

#include <cmath>

CDrawRotaGraphReserve::CDrawRotaGraphReserve(int GHandle, int Priority,
                                             int x, int y, float angle,
                                             float extend, int width,
                                             int height)
    : IRenderReserve(
          GHandle, Priority, x, y,
          width * std::cos(angle) * extend + height * std::sin(angle) * extend,
          width * std::sin(angle) * extend + height * std::cos(angle) * extend),
      angle(angle),
      extend(extend) {}

void CDrawRotaGraphReserve::Render() const {
  DrawRotaGraph((int)x, (int)y, extend, angle, GHandle, TRUE);
}
