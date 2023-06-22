#pragma once
#include "IRenderReserve.h"
class CDrawModiGraphReserve : public IRenderReserve {
 public:
  CDrawModiGraphReserve(int GHandle, int priority, double x1, double y1, double x2,
                        double y2, double x3, double y3, double x4, double y4);
  void Render() const;

 protected:
  double x1_, y1_, x2_, y2_, x3_, y3_, x4_, y4_;
};
