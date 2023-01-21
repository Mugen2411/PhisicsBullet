#pragma once
#include "IRenderReserve.h"
class CDrawGraphReserve : public IRenderReserve {
 public:
  CDrawGraphReserve(int GHandle, int x, int y, double Priority, int width,
                    int height);
  void Render() const;
};
