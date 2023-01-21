#pragma once
#include "IRenderReserve.h"
class CDrawGraphFReserve : public IRenderReserve {
 public:
  CDrawGraphFReserve(int GHandle, float x, float y, double Priority, int width,
                     int height);
  void Render() const;
};
