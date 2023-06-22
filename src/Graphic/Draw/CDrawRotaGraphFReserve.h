#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphFReserve : public IRenderReserve {
 public:
  CDrawRotaGraphFReserve(int GHandle, int Priority, double x, double y,
                         float angle, float extend, int width, int height);
  void Render() const;

 protected:
  float angle_, extend_;
};
