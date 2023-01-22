#pragma once
#include "IRenderReserve.h"
class CDrawCircleGaugeReserve : public IRenderReserve {
 public:
  CDrawCircleGaugeReserve(int GHandle, int priority, int x, int y,
                          double ratio, int width, int height);

  void Render() const;

 private:
  double ratio_;
};
