#pragma once
#include "IRenderReserve.h"
class CDrawModiGraphReserve : public IRenderReserve {
 protected:
  double x1, y1, x2, y2, x3, y3, x4, y4;

 public:
  CDrawModiGraphReserve(int GHandle, int priority, double x1, double y1, double x2,
                        double y2, double x3, double y3, double x4, double y4);
  void Render() const;
};
