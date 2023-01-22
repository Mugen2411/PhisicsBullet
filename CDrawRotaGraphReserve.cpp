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
      angle_(angle),
      extend_(extend) {}

void CDrawRotaGraphReserve::Render() const {
  DrawRotaGraph((int)x_, (int)y_, extend_, angle_, graphic_handle_, TRUE);
}
