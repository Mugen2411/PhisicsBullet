#pragma once
#include "IRenderReserve.h"
class CDrawModiGraphReserve : public IRenderReserve {
 protected:
  float x1, y1, x2, y2, x3, y3, x4, y4;

 public:
  CDrawModiGraphReserve(int GHandle, int priority, float x1, float y1, float x2,
                        float y2, float x3, float y3, float x4, float y4);
  void Render() const;
};
