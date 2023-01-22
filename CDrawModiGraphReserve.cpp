#include "CDrawModiGraphReserve.h"

#include <DxLib.h>

CDrawModiGraphReserve::CDrawModiGraphReserve(int GHandle, int priority,
                                             double x1, double y1, double x2,
                                             double y2, double x3, double y3,
                                             double x4, double y4)
    : IRenderReserve(GHandle, priority, 0, 0, 0, 0),
      x1_(x1),
      y1_(y1),
      x2_(x2),
      y2_(y2),
      x3_(x3),
      y3_(y3),
      x4_(x4),
      y4_(y4) {}

void CDrawModiGraphReserve::Render() const {
  DrawModiGraphF((float)x1_, (float)y1_, (float)x2_, (float)y2_, (float)x3_,
                 (float)y3_, (float)x4_, (float)y4_, graphic_handle_, TRUE);
}
