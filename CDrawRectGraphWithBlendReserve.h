#pragma once
#include "IRenderReserve.h"
class CDrawRectGraphWithBlendReserve : public IRenderReserve {
 protected:
  int Color, Blendmode, value;

 public:
  CDrawRectGraphWithBlendReserve(int GHandle, double Priority, float x, float y,
                                 int color, int Blendmode, int value, int width,
                                 int height);
  void Render() const;
};
