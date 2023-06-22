#pragma once
#include "IRenderReserve.h"
class CDrawExtendWithBlendReserve : public IRenderReserve {
 public:
  CDrawExtendWithBlendReserve(int GHandle, int Priority, double x1, double y1,
                              double x2, double y2, int color, int Blendmode,
                              int value);
  void Render() const;

 protected:
  double x1_, y1_, x2_, y2_;
  int color_, blendmode_, value_;
};