#include "CDrawModiGraphReserve.h"

#include <DxLib.h>

CDrawModiGraphReserve::CDrawModiGraphReserve(int GHandle, int priority,
                                             double x1, double y1, double x2,
                                             double y2, double x3, double y3,
                                             double x4, double y4)
    : IRenderReserve(GHandle, priority, 0, 0, 0, 0),
      x1(x1),
      y1(y1),
      x2(x2),
      y2(y2),
      x3(x3),
      y3(y3),
      x4(x4),
      y4(y4) {}

void CDrawModiGraphReserve::Render() const {
  DrawModiGraphF((float)x1, (float)y1, (float)x2, (float)y2, (float)x3,
                 (float)y3, (float)x4, (float)y4, GHandle, TRUE);
}
