#pragma once
#include "IRenderReserve.h"
class CDrawRectGraphWithBlendReserve : public IRenderReserve {
 protected:
  int Color, Blendmode, value;

 public:
  CDrawRectGraphWithBlendReserve(int GHandle, int Priority, double x, double y,
                                 int color, int Blendmode, int value, int width,
                                 int height);
  void Render() const;
};
