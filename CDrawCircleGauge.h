#pragma once
#include "IRenderReserve.h"
class CDrawCircleGaugeReserve : public IRenderReserve {
  double ratio;

 public:
  CDrawCircleGaugeReserve(int GHandle, double priority, int x, int y,
                          double ratio, int width, int height);

  void Render() const;
};
