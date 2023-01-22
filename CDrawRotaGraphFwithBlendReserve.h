#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphFwithBlendReserve : public IRenderReserve {
 public:
  CDrawRotaGraphFwithBlendReserve(int GHandle, int Priority, double x, double y,
                                  float angle, float extend, int color,
                                  int Blendmode, int value, int width,
                                  int height);
  void Render() const;

 protected:
  float angle_, extend_;
  int color_, blendmode_, value_;
};
