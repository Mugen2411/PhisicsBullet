#pragma once
#include "IRenderReserve.h"
class CDrawGraphFReserve : public IRenderReserve {
 public:
  CDrawGraphFReserve(int GHandle, double x, double y, int Priority, int width,
                     int height);
  void Render() const;
};
