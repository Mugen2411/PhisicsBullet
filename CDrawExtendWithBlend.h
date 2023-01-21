#pragma once
#include "IRenderReserve.h"
class CDrawExtendWithBlendReserve : public IRenderReserve {
 protected:
  double x1, y1, x2, y2;
  int Color, Blendmode, value;

 public:
  CDrawExtendWithBlendReserve(int GHandle, int Priority, double x1, double y1,
                              double x2, double y2, int color, int Blendmode,
                              int value);
  void Render() const;
};