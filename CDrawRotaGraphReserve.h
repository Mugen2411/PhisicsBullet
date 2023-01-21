#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphReserve : public IRenderReserve {
 protected:
  float angle, extend;

 public:
  CDrawRotaGraphReserve(int GHandle, int Priority, int x, int y, float angle,
                        float extend, int width, int height);
  void Render() const;
};
