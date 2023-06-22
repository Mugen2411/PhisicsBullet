#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphReserve : public IRenderReserve {
 public:
  CDrawRotaGraphReserve(int GHandle, int Priority, int x, int y, float angle,
                        float extend, int width, int height);
  void Render() const;

 protected:
  float angle_, extend_;
};
